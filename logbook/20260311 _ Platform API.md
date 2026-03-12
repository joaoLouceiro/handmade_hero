# Platform API, unity builds, and wrapping my head around guard macros

First of all, we should be very conscious as to what is platform-specific code, and name the files accordingly. Naming something as "win32_myfile.cpp" (or, in my case, "sdl_myfile.cpp") makes the task of porting a program to another platform a lot easier.

So, what would the platform-specific part of the program be? For a video-game, we can point to the graphics and audio buffers, basic I/O (control and file, which we will take care of this week) and performance monitoring.

Our code is currently not deliverable-quality code. There's still a lot we need to go over, but there's a couple of things we can point out that we are missing:
- Saved game locations
- Getting a handle to our own executable file
- Asset loading path
- Threading (launch a thread)
- Raw Input (support for multiple keyboards)
- Sleep/timeBeginPeriod (so we don't melt the CPU)
- ClipCursor() (for multimonitor support)
- Fullscreen support
- WM_SETCURSOR (control cursor visibility)
- QueryCancelAutoplay
- WM_ACTIVATEAPP (for when we are not the active application)
- Blit speed improvements (BilBlt)
- Hardware accelaration (OpenGL or Direct3D or both)
- GetKeyboardLayout (for international keyboards)

So, removing the platform agnostic code was not hard at all. Create a `game_offscreen_buffer` that'll sit in a new `handmade.h` file, add a generic `GameUpdateAndRender()` function and move the `RenderWeirdGradient()` tool into a `handmade.cpp`. Pretty straightforward.

Now, `clangd`? Oh my god, `clangd`... `clangd` doesn't like unity builds. It doesn't really know what to do with them. So we need to tweak the project a bit. Luckily, the folks at Handmade Network have been going through the series again, so there's some activity in their forums and discord, so I found [this link](https://handmade.network/forums/t/8672-clangd_on_windows_in_neovim) that helped me out.
The idea is that you create a file where you dump all the definitions, forwards declarations, header inclusions and more in a single file. That is the file that will be compiled.
This was a big "oooooooh, that's it" moment: I spent a lot of time trying to understand how the inclusions for `handmade.h` were working, cause I felt like there were bound to be some circular definitions. Duh, I forgot about the guard macros: `#if !HANDMADE_H`, `#ifndef` and `#pragma once`, they basically do the same: if that file was defined, don't redefine it.

User-defined headers should always be included before native headers, especially on Windows, because they may overwrite some custom function or type we defined.
