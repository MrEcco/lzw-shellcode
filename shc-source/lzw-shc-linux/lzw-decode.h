#include <stdint.h>
#include <stdlib.h>

typedef uint8_t byte;
typedef uint16_t ushort;

extern size_t lzw_decode(byte * in, size_t insize, byte * out);