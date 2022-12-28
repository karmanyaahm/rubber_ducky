# Real Shell injection thing with Digispark

`oreoin.png` is the background image.
Run `./upload.sh` to inject `script.ps1` (the background setting script) into the image and output `oreo2.png`. `polyglot.py` does that magic. `upload.sh` then uploads it to my IPFS server (of course, you won't have the keys for that) and sets the IPFS CID to `VAR.h`, which is what tells the Digispark program where the image is.

`curl ipfs.io...` just primes ipfs.io's cache with our payload image.

`win/win.ino` contains the real sauce injection program. Basically, it escapes out of any current context menus, presset `Ctrl+X I` to run Powershell and pastes our script (download payload image from IPFS and execute it) into the shell. Then, it minimizes the window and our script sneakily changes things in the background.

