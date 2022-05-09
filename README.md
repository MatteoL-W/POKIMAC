# POKIMAC - IMAC 1 project

Developped by [Emily-Rose Stritch](https://github.com/emilyrosest) and [Mattéo Leclercq](https://github.com/MatteoL-W)

Checkout the CMAKE branch to have an easier install :)

## Installation

Library needed:

- SDL2
- SDL2_Image
- SDL2_TTF

How to install on Windows ?

Move the content of SDL_MinGW into the C:/MinGW folder and [add C:/MinGW/bin into your environment variable path](https://docs.microsoft.com/en-us/previous-versions/office/developer/sharepoint-2010/ee537574(v=office.14)#:~:text=To%20add%20a%20path%20to%20the%20PATH%20environment%20variable&text=In%20the%20System%20dialog%20box,to%20Path%20and%20select%20it.)

When you have cloned the repo, you can build:

```
make init
make
make st
```

or if you use mingw:

```
mingw32-make init
mingw32-make
mingw32-make st
```

## You can change the window size by modifying these values (Game.hpp):

```
static const int WINDOW_WIDTH = 750;
static const int WINDOW_HEIGHT = 750;
```

The game is design to be 750x750.
The makefile has the mingw32 compilation flag by default. You can remove it in the Makefile.
So far, the non-Windows part of the Makefile has not been tested. Sorry!

## How to play?

Just have fun!

## Commands

You can move with Z,S,Q,D or with arrows. You can swap the camera with M. You can access the inventory by pressing I.

## Thanks

- **Carl Brich** from https://www.youtube.com/c/CarlBirch
- https://www.spriters-resource.com/
