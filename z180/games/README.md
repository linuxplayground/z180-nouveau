# Port of Tetris from Nabu Games to Z180 for the Nouveau

## Tetris

Fairly typical tetris clone.  Every 10 lines completed advances your level.  The
game speeds up every time you level up.  If you clear 4 lines at once, you earn
10 bonus points.

Controls:

z rotate counter clockwise
x rotate clockwise
, move left
. move right
SPACE drop

## z180nouveau-lib

A port of NABU-LIB is available at and is used in this project to cross-compile
these games for the z180-Nouveau.

## BUILDING

The code in these games is quite old now.  The Z88DK compiler has to be one of
the last stable projects I have had the misfortune to deal with.  As far as I
can tell, my code can only be built by a version that includes zsdcc version
r13131.

commit id: `492cb971987d88f91d2b046ce99d5bd34f6fadea`

Basically whatever is needed to make it work for the nabu.  Otherwise
you get errors that make no sense and are very frustrating to deal with.

Seriously - (talking to future me now) - I know you are going to want to fix
this.  Don't even bother.  Unless you're planning on migrating the code to a
different compiler like the FUZIX-Compiler-Kit.  But you know that in order to
do that, you will first have to finish your CPM library project for that
compiler.

 -- Productiondave
