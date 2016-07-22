## Overview

Blind Jump is a procedurally generated space adventure game that I've been working on off and on in my free time. The object of the game is to get to the teleporter at the end of each level, while battling monsters and evil robots.

## Reading the Code

I began this project as a way of learning C++ syntax, so some older parts of the code suffer from bad design. The most readable parts are the newer ones, like the files in the src/framework/ folder, userInterface.cpp, and easingTemplates.cpp. scene.cpp and player.cpp have some older parts, but they're pretty readable too, and are probably the most important files in terms of understanding how everything works. Don't be intimidated by the number of files in the src/ folder, I like to work with small files, so almost all source files in the project contain the implementation of only one class or function (with the exception of function templates, in some instances I have grouped multiple into single headers).

## Installation

This project uses make and makedepend as a build system. Currently, the game is Mac only, but uses cross-platform libraries and could easily be ported (uses SFML 2.3, required to compile project). In bash:

Resolve dependencies
```bash
make depend
```

Compile
```bash
make macOS
```
This will create a .app package in the prod folder.

## Bugs

Please report any bugs that you find.
Known bugs: Orb enemies stuck in walls.