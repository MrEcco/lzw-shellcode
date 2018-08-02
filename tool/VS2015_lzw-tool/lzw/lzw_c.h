#ifndef _LZW_C_H_
#define _LZW_C_H_

#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t ushort;

#ifdef __cplusplus
extern "C" {
#endif
	int c_main(int argc, char * argv[]);
	byte * lzw_encode(byte *in);
	byte * lzw_decode(byte *in);
	byte * lzw_decode_shellcode(byte * in, size_t insize, byte * out);
#ifdef __cplusplus
}
#endif
#endif