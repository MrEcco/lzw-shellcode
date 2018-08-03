#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <syscall.h>

#include "lzw-decode.h"

//https://sourceforge.net/p/predef/wiki/Architectures/
#ifdef __i386__
    #ifndef _MY_MMAP_DEFINED
		#include "my_mmap_i386.h"
        #define _MY_MMAP_DEFINED
    #else
        #error Some fck with arch selecting...
    #endif
#endif
#ifdef __amd64__
    #ifndef _MY_MMAP_DEFINED
		#include "my_mmap_x86_64.h"
        #define _MY_MMAP_DEFINED
    #else
        #error Some fck with arch selecting...
    #endif
#endif
// May be you want to expand this list? I'll wait your commit like hatiko...

#define M_CLR 256
#define M_EOD 257
#define M_NEW 258

typedef struct {
	ushort next[256];
} lzw_enc_t;
typedef struct {
	ushort prev, back;
	byte c;
} lzw_dec_t;

static void _MEMSET_(void *_dst, int _val, size_t _sz);
static void _MEMCPY_(void *_dst, void *_src, size_t _sz);

size_t lzw_decode(byte * in, size_t insize, byte * out)
{
	size_t * x_ptr, *t_ptr;

	int out_len = 0;
	lzw_dec_t * d_table;
	x_ptr = (size_t *)my_mmap(NULL, sizeof(size_t) * 2 + 512 * sizeof(lzw_dec_t), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	_MEMSET_(x_ptr, 0, sizeof(size_t) * 2 + 512 * sizeof(lzw_dec_t));
	x_ptr[0] = sizeof(lzw_dec_t);
	x_ptr[1] = 512;
	d_table = (lzw_dec_t *)(x_ptr + 2);

	int len, j, next_shift = 512, bits = 9, n_bits = 0;
	ushort code, c, t, next_code = M_NEW;

	uint32_t tmp = 0;

	for (j = 0; j < 256; j++)
		d_table[j].c = j;
	next_code = M_NEW;
	next_shift = 512;
	bits = 9;
	for (len = insize; len;) {
		while (n_bits < bits) {
			if (len > 0) {
				len--;
				tmp = (tmp << 8) | *(in++);
				n_bits += 8;
			}
			else {
				tmp = tmp << (bits - n_bits);
				n_bits = bits;
			}
		}
		n_bits -= bits;
		code = tmp >> n_bits;
		tmp &= (1 << n_bits) - 1;
		if (code == M_EOD) break;
		if (code == M_CLR) {
			x_ptr = (size_t *)d_table - 2;
			_MEMSET_(d_table, 0, x_ptr[0] * x_ptr[1]);
			for (j = 0; j < 256; j++)
				d_table[j].c = j;
			next_code = M_NEW;
			next_shift = 512;
			bits = 9;
			continue;
		}

		if (code >= next_code) {
			goto bail;
		}

		c = code;
		d_table[next_code].prev = code;

		while (c > 255) {
			t = d_table[c].prev;
			d_table[t].back = c;
			c = t;
		}

		d_table[next_code - 1].c = c;

		while (d_table[c].back) {
			out[out_len++] = (byte)(d_table[c].c);
			t = d_table[c].back; d_table[c].back = 0; c = t;
		}
		out[out_len++] = (byte)(d_table[c].c);
		if (++next_code >= next_shift) {
			if (++bits > 16) {
				goto bail;
			}
			next_shift *= 2;
			x_ptr = (size_t*)d_table - 2;
			t_ptr = (size_t *)my_mmap(NULL, sizeof(size_t) * 2 + *x_ptr * next_shift, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
			_MEMCPY_(t_ptr, x_ptr, next_shift > x_ptr[1] ? sizeof(size_t) * 2 + *x_ptr * x_ptr[1] : sizeof(size_t) * 2 + x_ptr[0] * next_shift);
			my_munmap(x_ptr, sizeof(size_t) * 2 + *x_ptr * x_ptr[1]);
			x_ptr = t_ptr;
			x_ptr[1] = next_shift;
			d_table = (lzw_dec_t *)(x_ptr + 2);
		}
	}
 bail:
	my_munmap((size_t *)d_table - 2, *((size_t *)d_table - 2) * *((size_t *)d_table - 1));
	return (size_t)out_len;
}

static void _MEMSET_(void *_dst, int _val, size_t _sz)
{
	while (_sz) ((byte *)_dst)[--_sz] = _val;
}

static void _MEMCPY_(void *_dst, void *_src, size_t _sz)
{
	while (_sz--) ((byte *)_dst)[_sz] = ((byte *)_src)[_sz];
}

#undef _MY_MMAP_DEFINED

