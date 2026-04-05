#include "unity_build.h"

internal void GameOutputSound(game_sound_output_buffer *SoundBuffer,
                              int ToneHz)
{
    local_persist real32 tSine;
    int16 ToneVolume = 3000;
    int WavePeriod = SoundBuffer->SamplesPerSecond / ToneHz;

    int16 *SampleOut = (int16_t *)SoundBuffer->Samples;
    for (int SampleIndex = 0; SampleIndex < SoundBuffer->SampleCount; ++SampleIndex)
    {

        // TODO(casey): Draw this out for people
        real32 SineValue = sinf(tSine);
        int16 SampleValue = (int16)(SineValue * ToneVolume);
        *SampleOut++ = SampleValue;
        *SampleOut++ = SampleValue;

        tSine += 2.0f * Pi32 * 1.0f / (real32)WavePeriod;
    }
}

internal void RenderWeirdGradient(game_offscreen_buffer *Buffer,
                                  int BlueOffset,
                                  int GreenOffset)
{
    uint8 *Row = (uint8 *)Buffer->Memory;
    for (int Y = 0; Y < Buffer->Height; ++Y)
    {
        uint32 *Pixel = (uint32 *)Row;
        for (int X = 0; X < Buffer->Width; ++X)
        {
            uint8 Blue = (X + BlueOffset);
            uint8 Green = (Y + GreenOffset);

            *Pixel++ = ((Green << 8) | Blue);
        }

        Row += Buffer->Pitch;
    }
}

internal void GameUpdateAndRender(game_memory *Memory,
                                  game_input *Input,
                                  game_offscreen_buffer *Buffer,
                                  game_sound_output_buffer *SoundBuffer)
{
    Assert(sizeof(game_state) <= Memory->PermanentStorageSize);

    game_state *GameState = (game_state *)Memory;
    if (!Memory->IsInitialized)
    {
        char *Filename = "/home/jlouceiro/projects/handmade_hero/handmade/code/sdl_handmade.cpp";

        debug_read_file_result File = DEBUGPlatformReadEntireFile(Filename);
        if (File.Contents)
        {
            DEBUGPlatformWriteEntireFile("test.out", File.ContentsSize, File.Contents);
            DEBUGPlatformFreeFileMemory(File.Contents);
        }

        GameState->ToneHz = 256;

        // TODO(casey): This may be more appropriate to do in the platform layer
        Memory->IsInitialized = true;
    }
    for (int ControllerIndex = 0; ControllerIndex < ArrayCount(Input->Controllers);
         ControllerIndex++)
    {
        game_controller_input *Controller = &Input->Controllers[ControllerIndex];

        if (Controller->IsAnalog)
        {
            // NOTE: (casey): use analog movement tuning
            GameState->BlueOffset += (int)4.0f * (Controller->StickAverageX);
            GameState->ToneHz = 256 + (int)(128.0f * (Controller->StickAverageY));
        }
        else
        {
            // NOTE: (casey): use digital movement tuning
            if (Controller->MoveDown.EndedDown)
            {
                GameState->GreenOffset += 1;
            }
            if (Controller->MoveUp.EndedDown)
            {
                GameState->GreenOffset -= 1;
            }
        }
    }
    // TODO(casey): Allow jsample offsets here for more robust platform options
    GameOutputSound(SoundBuffer, GameState->ToneHz);
    RenderWeirdGradient(Buffer, GameState->BlueOffset, GameState->GreenOffset);
}
