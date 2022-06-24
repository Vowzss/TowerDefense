# Project Tower Defense
## Presentation
---------------
This project aims at recreating a tower defense game in C++ language with Raylib library for the visuals.\
The second goal of this project is to become more familiar with code structuring and math applied to video games and POO.

## Infomation about the project
---------------
Project start : 11/23/2021\
Project end : 12/17/2021\
Version : 1.0 - GOLD\
Date last version : 12/17/2021\

## Building
---------------
### Create an executable
```sh
$ make
```
### Run
```sh
$ ./TowerDefense
```
### Clean the project
```sh
$ make clean
```
## Project structure
---------------
```sh
.
├── assets
│   ├── Animations
│   ├── Backgrounds
│   ├── Buttons
│   ├── Enemies
│   ├── Map
│   ├── Menu
│   └── Sounds
│       └── MenuSounds
├── Makefile
├── memoryleak
├── README.md
├── save
├── src
│   ├── gameManager
│   │   ├── gameEnemies.cpp
│   │   ├── gameEnemies.hpp
│   │   ├── gamePlayer.cpp
│   │   ├── gamePlayer.hpp
│   │   ├── gameSounds.cpp
│   │   ├── gameSounds.hpp
│   │   ├── gameTextures.cpp
│   │   ├── gameTextures.hpp
│   │   ├── gameTowerManager.cpp
│   │   ├── gameTowers.cpp
│   │   ├── gameTowers.hpp
│   │   ├── gameWaves.cpp
│   │   └── gameWaves.hpp
│   │
│   ├── gameScenes
│   │   ├── game.cpp
│   │   ├── gameCredits.cpp
│   │   ├── gameCredits.hpp
│   │   ├── gameHowToPlay.cpp
│   │   ├── gameHowToPlay.hpp
│   │   ├── game.hpp
│   │   ├── gameOver.cpp
│   │   ├── gameOver.hpp
│   │   ├── gameSelector.cpp
│   │   ├── gameSelector.hpp
│   │   ├── gameWinner.cpp
│   │   ├── gameWinner.hpp
│   │   ├── menu.cpp
│   │   └── menu.hpp
│   │
│   ├── levelEditor
│   │   ├── levelEditor.cpp
│   │   └── levelEditor.hpp
│   │
│   ├── libs
│   │   ├── myList.hpp
│   │   └── myMathLib.hpp
│   │
│   ├── main.cpp
│   │
│   └── System
│       ├── gameAnimator.cpp
│       ├── gameAnimator.hpp
│       ├── scene.cpp
│       ├── scene.hpp
│       ├── UIElement.cpp
│       └── UIElement.hpp
│
└── third_party
```

## Game Preview
---------------
# EDITOR MENU
- ![PNG](./screenshots/editorMenu.png)
# GAME MENU
- ![PNG](./screenshots/gameMenu.png)
# GAME OVER MENU
- ![PNG](./screenshots/gameOver.png)
# GAME RULES MENU
- ![PNG](./screenshots/gameRules.png)
# GAME
- ![PNG](./screenshots/playGame.png)
# GAME PLAY MENU
- ![PNG](./screenshots/playMenu.png)
# LEVEL SELECTED MENU
- ![PNG](./screenshots/selectLevelMenu.png)

## Asset Credits
---------------
- Asset tower : Kenney https://www.kenney.nl/assets/tower-defense-top-down
- Asset sprite and enemy : Pixel Boy https://pixel-boy.itch.io/ninja-adventure-asset-pack 
- Sound : Pixel Boy https://pixel-boy.itch.io/ninja-adventure-asset-pack
- FX : Pixel Boy https://pixel-boy.itch.io/ninja-adventure-asset-pack
