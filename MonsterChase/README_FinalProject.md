# Final Project Read Me 

## How To Test it

* Build and Run the Project `MonsterChase`.

## Introduction

### Rule 

Basically, The final project is a **2D Pong**. And there are two players who can control the bat to hit the ball.  The aim for this game is to get the ball touch the wall(**red wall**) behind the other player.

### Control

* One player uses the `W`,`S` to move the bat : `W` for move up, 'S' for move down.
* The other player uses the `O`,`K` to move the bat:  `O` for move up, `K` for move down.
* Press the `Space Bar` to start the game any time.

### Game Flow

`Enter the Game` -> `Idle State`->`Press 'Space Bar' to start the game` -> `Once the ball touches the left or right wall` -> `Idle State`.

PS: When you press the `Space Bar` any time in the game, it will restart the game manually

## Features

* Used `HashedString` to wrap up most of string get a performance perk.
* Added some custom properties into `lua`file to make it more scalable.
* Tweaked `GLib` a little bit to make it fit for drawing custom size sprite.(But it seems it still a lot of upgrade work to do, such as `drawing text` and support for `debugging drawing`).

## Some Issues

* Cannot use the window `cross mark` to close the application normally. It seems some problem about the reference counting part. Still need to debug a little bit.

  PS: you can use the `debug stop` button to stop the application.

* Maybe there will be some build issues(already asked for joe for help!).

* There is still some collision detection problems.

* Occasionally, there will be a crush when you start the program, which throws an exception in `GLib Message part`.

## Contact

If there is any question or issue, please slack **@Tezika Zhou** or email to tezikazhou@gmail.com, Thanks

