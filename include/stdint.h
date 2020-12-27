#ifndef __PHANTOMOS_STDINT_H_2020_12_17_17_19_45 
#define __PHANTOMOS_STDINT_H_2020_12_17_17_19_45

typedef unsigned char uint8_t;
typedef signed char int8_t;

typedef unsigned short uint16_t;
typedef signed short int16_t;

typedef unsigned int uint32_t;
typedef signed int int32_t;


typedef unsigned long long uint64_t;
typedef signed long long int64_t;
#define UINT64_C(v) v ## ull
#define INT64_C(v) v ## ll

typedef uint64_t uintmax_t;
typedef int64_t intmax_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

#define INT8_C(v) ((int8_t)v)
#define INT16_C(v) ((int16_t)v)
#define INT32_C(v) ((int32_t)v)

#define UINT8_C(v) ((uint8_t)v ## u)
#define UINT16_C(v) ((uint16_t)v ## u)
#define UINT32_C(v) ((uint32_t)v ## u)

#define INTMAX_C(v) INT64_C(v)
#define UINTMAX_C(v) UINT64_C(v)

#define INT8_MIN  INT8_C(-128)
#define INT8_MAX  INT8_C(127)
#define UINT8_MAX UINT8_C(255)


#define INT16_MIN  INT16_C(-32768)
#define INT16_MAX  INT16_C(32767)
#define UINT16_MAX UINT16_C(65535)

#define INT32_MIN  INT32_C(-2147483648)
#define INT32_MAX  INT32_C(2147483647)
#define UINT32_MAX UINT32_C(4294967295)

#define INT64_MIN  INT64_C(-9223372036854775808)
#define INT64_MAX  INT64_C(9223372036854775807)
#define UINT64_MAX UINT64_C(18446744073709551616)

#define INTMAX_MIN INT64_MIN
#define INTMAX_MAX INT64_MAX
#define UINTMAX_MAX UINT64_MAX

#define  INT_LEAST8_MIN  INT8_MIN
#define  INT_LEAST8_MAX  INT8_MAX
#define UINT_LEAST8_MAX UINT8_MAX


#define  INT_LEAST16_MAX  INT16_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define  INT_LEAST16_MIN  INT16_MIN

#define  INT_LEAST32_MIN  INT8_MIN
#define  INT_LEAST32_MAX  INT8_MAX
#define UINT_LEAST32_MAX UINT8_MAX

#define  INT_LEAST64_MIN  INT8_MIN
#define  INT_LEAST64_MAX  INT8_MAX
#define UINT_LEAST64_MAX UINT8_MAX

#define  INT_FAST8_MIN  INT8_MIN
#define  INT_FAST8_MAX  INT8_MAX
#define UINT_FAST8_MAX UINT8_MAX


#define  INT_FAST16_MAX  INT16_MAX
#define UINT_FAST16_MAX UINT16_MAX
#define  INT_FAST16_MIN  INT16_MIN

#define  INT_FAST32_MIN  INT8_MIN
#define  INT_FAST32_MAX  INT8_MAX
#define UINT_FAST32_MAX UINT8_MAX

#define  INT_FAST64_MIN  INT8_MIN
#define  INT_FAST64_MAX  INT8_MAX
#define UINT_FAST64_MAX UINT8_MAX


#endif