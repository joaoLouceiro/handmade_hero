# Lost in compiler land

Even before I started following the stream, this topic sent me into a deep rabbit hole, fighting with `clangd`.

I had spend most of the time I was working on last stream fighting with the `__FILE__` preprocessor. I just couldn't get `open()` to find the damn file. After some debating with Claude, I eventually got to the heart of it: `__FILE__` was giving me a relative path, when I needed a full path. He actually gave me some pretty good tips:

```markdown
- print Filename before open
- print `getcwd(...)`
- print `errno` after failure:
  - `perror("open failed")`
  - or show `errno` (expected 2, `ENOENT`)
- maybe compute absolute path to confirm:
  - `realpath(Filename, ...)` to see resolver behavior
```

Anyway, that's not exactly the point. I eventually bashed a full path onto the string and the damn thing worked. But there was this weird warning that was bugging me out, that actually sent me on a wild goose chase:

```
warning: deprecated conversion from string constant to ‘char*’ [-Wwrite-strings]
```

Lo an behold, as soon as I opened today's episode guide, we are dealing with that damn warning. The solution was to add a set of flags to the compilation script, but I had been triggered.

My main issue was with the `DEBUG*` functions from day 15. They were all showing up errors related to the function being declared, but having no linkage.

```
Function has internal linkage but is not defined
```

Basically, if I have a `static` function declaration, the definition must be somewhere in the same translation unit. Usually, that would mean that if I declared `static void myFunction()` in `myFile.h`, the body definition would be somewhere in `myFile.cpp`. Of course, with our (unity) build, that is not the case: I forward declared the function in `handmade.h`, use it in `handmade.cpp` (because I want it to be called in the same place of the game rendering, independently from the platform layer) but I only define it in `sdl_handmade.cpp` (because it has platform specific code that should only matter to that particular system).

But the program compiles, so what gives? Apparently, this has to do with the fact that `clangd` doesn't exactly like unity builds. It moans a bit, but you can shush it: just add the `-Wno-undefined-internal` flag and you are good to go. Simple.

But... As I was adding the (new) flag to my `.clangd` configuration, I started wondering if there was some better way of doing it. It didn't exactly make sense that I had to manage this in two places forever. Luckily, the hole I had dug myself into had a gem there. [One of the websites](https://www.frogtoss.com/labs/clangd-with-unity-builds.html) I found looking for `.clangd` and `unity builds` had the following:
> You really want to automate this, or you’ll have to maintain two sets of all your compile flags, which sounds like one of the least enjoyable things you could possibly fritter your time away on.

In the example, they use `ninja` and what not, but I am using `clang` and I know that I can generate `compile-commands` with `bear`. So let's try...

```sh
bear -o ../compile_commands.json -- clang -DHANDMADE_SDL=1 [......] -Wno-writable-strings -Wno-pragma-once-outside-header -Wno-undefined-internal
```

Damn! I can't believe. Not only does this output the `compile-commands.json` that I need, it still builds the project. Uff!! And I haven't even started!

So, on to the rest of the flags. `Clang` seems to be a bit more permissive than `gcc`, so we need to adapt our flags a little bit. With `gcc`, apparently we only need the `-Wall` flag for it to detect stuff like a `warning: comparison between signed and unsigned integer expressions`, but with `clang` I need to use `-Wextra`. There's another level to it, `-pedantic`, which I'm very fond of, cause it's pointing out some stuff that, for a beginner like me, seem quite nice, so I'll leave it for now, and remove annoying warnings manually. The last step is to use `-Werror` to make warnings behave like errors and block our build.

Of course, this too took me on a time-consuming side-quest. So, here's the thing: in most IDE's I've used, if there is an error in the project, I can just click the line that says where the error is and I will be teletransported there, but in Neovim it looked like there is no such feature. I was pleased to find that I was (kinda) wrong.

Using `gF` should send me to the correct place. That is because Vim interprets a string with `filename:line:column` as a location in a file, so it can send me where I expect it to (this also means that we can just write the name of a file in the current buffer and use `gF` to be taken there). So hovering over the error message should allow me to go directly to it's location, but the file was not being found. Turns out there was a mismatch between the location of the error message (coming from the `/build` directory) and the actual location of the file (`/handmade/code`). Surely there was a way to solve this, no? Some Claude-fu later, I came up with a nifty vim script that allows for the `cwd` to change to `/build` without affecting the file explorer or so.
