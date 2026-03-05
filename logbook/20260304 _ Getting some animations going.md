# Rendering squares and fixing the launcher
I got side tracked installing a new OS on another machine, so I spent a couple of days with that.

I'm not going deep into the content of the videos, cause that's what they are there for.

From day 2 to day 4, Casey gets a window showing up, renders some squares by setting each pixel's RGB channels. That works by offsetting some bytes and what not, but, honestly, it's too much to put here.

What I did stumble upon which was pretty interesting to me was that, contrary to what I thought, `nvim-dap` does not recognize the `preLaunchTask` attribute. So, if I want to launch my code from NeoVim, I need to first manually run the `build.sh` script.

That came about because I had noticed that VS Code (my prized debugger) was launching the program even if the compilation phase didn't complete, which meant that I was looking at a previous version of whatever code I was trying to debug. Easy enough fix, I simply had to add `set -e` so that the script returns any error it finds. VS Code is set up to abort the execution (or at least warn the user) if the `preLaunchTask` finds any errors.

Another win for VS Code's debugger.

Other than that, I have just been following the series as is. I got a bit lost on day 3 and had to copy all the code from Handmade Penguin's link. Basically, I was going through the whole video, than looking at the Penguin's guide, and not everything was matching up. I figured out that I need to have the three things in sight: Casey's video, Handmade Penguin and my own code, and go back and forth between those three.

I guess that's it for today!
