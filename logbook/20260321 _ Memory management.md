Every time we user memory allocation, we are potentially inserting a failing point. That's why Casey prefers not to use such techniques. Instead, we are going to use a Flat Partition style of memory allocation, whereby we define, at the beginning, all the memory we are going to be using, instead of so-called "Allocation Festivals".

The first step is to extract the game state currently present in our GameUpdateAndRendeer function:

```cpp
internal void GameUpdateAndRender(game_input *Input,
                                  game_offscreen_buffer *Buffer,
                                  game_sound_output_buffer *SoundBuffer)
{
    local_persist int BlueOffset = 0;
    local_persist int GreenOffset = 0;
    local_persist int ToneHz = 256;
    ....
}
```

The typical approach is to dynamically allocate memory by creating something like:

```cpp
internal game_state *GameStartup(void) 
{
    //The 'new' keyword allocates memory in C++. For pure C, we would probably be using some sort of `malloc`
    game_state *GameState = new game_state;
    if (GameState)
    {
        GameState->BlueOffset = 0;
        GameState->GreenOffset = 0;
        GameState->local_persist int ToneHz = 256;
    }
    return(GameState);
}
```

This has a huge drawback. Every memory allocation must be paired with a destructor/call to free:

```cpp
internal void GameShutdown(game_state *GameState)
{
    delete GameState;
}
```

Pretty easy to follow for a short case like what we have, but it quickly gets out of hand when we start adding assets and such.

So the idea we are going for requires that we allocate all memory for the game at startup. That makes it so we don't have weird memory failure points showing up during the game itself, but only on the platform setup.

So, how are we going to setup the memory? We will subdivide it into a few different partitions. Scratch space (not about storing the game, transient, it can go away) and Permanent (what holds the game together, keeps the state from frame to frame).
