# Z88DK

## References to Nabu etc

As you read through this code, you will find various references to Nabu,
nabu-lib and other seemingly out of place things.  That's because the Tetris
game included in this repository was originaly made for the Nabu PC.  It was
then ported to the Z80 Retro! and now to the Z180 Nouveau.  Just ignore it.
It's laziness on my part not wanting to change everything.

## Z88DK Requirements

You must have a working version of Z88DK either placed or simlinked in this folder.

The version of Z88DK required is:

```text
commit 492cb971987d88f91d2b046ce99d5bd34f6fadea (HEAD)
Author: dom <dom@suborbital.org.uk>
Date:   Fri Feb 3 20:05:13 2023 +0000

    (widegfx) Missing sdcc export
```

Perhaps other versions will work.  This is the one I used and I know this works
for me.

## Assembly Libs

A collection of essembly libraries are included in the `libnouveau` folder.

Easiest is to symlink to the `libnouveau/lib` path or path to them in you
makefiles.  The associated headers are also included in the
`libnouveau/headers` path.

## Macro Library

A handy `macros.inc` file is included in `libnouveau/headers/macros.inc`.
