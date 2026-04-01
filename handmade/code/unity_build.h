#pragma once

#include <stdint.h>
#define internal static
#define local_persist static
#define global_variable static

#define Pi32 3.14159265359f

#define MAX_CONTROLLERS 4

#define Kilobytes(Value) ((Value) * 1024LL)
#define Megabytes(Value) (Kilobytes(Value) * 1024LL)
#define Gigabytes(Value) (Megabytes(Value) * 1024LL)
#define Terabytes(Value) (Gigabytes(Value) * 1024LL)

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
// TODO: swap, min, max... macros?

#if HANDMADE_SLOW
#define Assert(Expression)                                                                         \
    if (!(Expression))                                                                             \
    {                                                                                              \
        __builtin_trap();                                                                          \
    }
#else
#define Assert(Expression)
#endif

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float real32;
typedef double real64;

typedef uint32_t bool32;

#include <math.h>

#ifdef HANDMADE_SDL
#include "sdl_handmade.h"
#endif // HANDMADE_SDL

#include "handmade.h"
