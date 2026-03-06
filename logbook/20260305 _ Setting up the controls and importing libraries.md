This is where the fun begins. We can finally interact with what's on the screen!

Getting things running is surprisingly easy, compared to all the fuss Casey has got to go through to get stuff working on a Windows machine. Specifically, there's this whole library import mumbo-jumbo that he goes through that we don't need to do, because SDL is that good. Still, it's worth noting that the Handmade Penguin guide has all the information there if we ever need to do something similar in our operating system.

On the other hand, setting up the controls was not as easy. There's a lot of things that XInput takes care of that SDL does not do automatically. Still, this was pretty easy. Just a bunch of if/else and new cases in out HandleEvent function. Not much.

There's a very cool trick that Casey uses to redefine some Windows functions that I think will be handy down the line. He explains it well by 1:30h.
First, he creates a parameterized macro to rename Windows' `XInputGetState`, taking the functions' prototype as the replacement text, which allows him to create as many differently named functions as he wants to.
He then uses a `typedef` to basically name the function's signature.
Then, he does the same thing, but to define the body, which he calls a "stub".
Finally, he declares a global variable that points to that body, and he (re)defines `XInputGetState` to point to his new function, since he couldn't undefine Windows'.

```C
#define X_INPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
typedef X_INPUT_GET_STATE(x_input_get_state);
X_INPUT_GET_STATE(XInputGetStateStub)
{
    return(0);
}
global_variable x_input_get_state *XInputGetState_ = XInputGetStateStub;
#define XInputGetState XInputGetState_
```

Amazing.
