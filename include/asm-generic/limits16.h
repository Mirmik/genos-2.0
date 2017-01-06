#ifndef ASM_GENERIC_LIMITS16_H_
#define ASM_GENERIC_LIMITS16_H_

#ifndef __ASSEMBLER__

#include "asm-generic/limits.h"

#define CHAR_BIT 	8
#define CHAR_MIN 	SCHAR_MIN
#define CHAR_MAX 	SCHAR_MAX
#define SCHAR_MIN 	INT8_MIN
#define SCHAR_MAX 	INT8_MAX
#define UCHAR_MAX 	UINT8_MAX

#define WORD_BIT 	16
#define INT_MIN		INT16_MIN
#define INT_MAX		INT16_MAX
#define UINT_MAX	UINT16_MAX

#define SHRT_MIN	(-32768)
#define SHRT_MAX	32767
#define USHRT_MAX	65535

#define LONG_BIT	32
#define LONG_MIN	(-LONG_MAX - 1)
#define LONG_MAX	2147483647L
#define ULONG_MAX	4294967295UL

#define LLONG_MIN	(-LLONG_MAX - 1)
#define LLONG_MAX	9223372036854775807LL

#define ULLONG_MAX	18446744073709551615ULL

#endif /* __ASSEMBLER__ */

#endif /* ASM_GENERIC_LIMITS16_H_ */