#pragma once

#include <stdint.h>
#define internal static
#define local_persist static
#define global_variable static

#define Pi32 3.14159265359f

#define MAX_CONTROLLERS 4

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

#if HANDMADE_SLOW
#define Assert(Expression)                                                                         \
    if (!(Expression))                                                                             \
    {                                                                                              \
        __builtin_trap();                                                                          \
    }
#else
#define Assert(Expression)
#endif

#define Kilobytes(Value) ((Value) * 1024LL)
#define Megabytes(Value) (Kilobytes(Value) * 1024LL)
#define Gigabytes(Value) (Megabytes(Value) * 1024LL)
#define Terabytes(Value) (Gigabytes(Value) * 1024LL)

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
// TODO: swap, min, max... macros?

#include <math.h>

inline uint32 SafeTruncateUInt64(uint64 Value)
{
    Assert(Value <= 0xFFFFFFFF);
    uint32 Result = (uint32)Value;
    return (Result);
}

// NOTE(casey): Services that the platform layer provides to the game

#if HANDMADE_INTERNAL
struct debug_read_file_result
{
    uint32 ContentsSize;
    void *Contents;
};

internal debug_read_file_result DEBUGPlatformReadEntireFile(char *Filename);

internal void DEBUGPlatformFreeFileMemory(void *BitmapMemory);
internal bool32 DEBUGPlatformWriteEntireFile(char *Filename,
                                             uint32 MemorySize,
                                             void *Memory);
#endif

#ifdef HANDMADE_SDL
#include "sdl_handmade.h"
#endif // HANDMADE_SDL

#include "handmade.h"
