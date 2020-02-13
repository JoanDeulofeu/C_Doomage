# DOOM_NUKEM
Creation of a 3D engine and a Doom-like game

## Description

The goal of the project is to create from scratch a 3D engine, an game editor and a level. 
It was written in C and uses only a few functions of the SDL.

<img src="https://donsefactory.files.wordpress.com/2020/02/doom_05-1.gif" width=500 height=500/>

Main features:
* Creation of concav sectors
* Portals can be added to navigate through sectors independently of their orientation
* Non-Euclidian geometry handled
* Sprites can be added in the editor
* Sector's floor and ceiling can be resized
* Fly with a jetpack
* Wall's texture can be changed
* Several weapons with different power/range
* Maps can be saved and loaded
* Multithreading

<img src="https://donsefactory.files.wordpress.com/2020/02/doom_00.gif" width=500 height=500/>
<img src="https://donsefactory.files.wordpress.com/2020/02/doom_02.gif" width=500 height=500/>
<img src="https://donsefactory.files.wordpress.com/2020/02/doom_03.gif" width=500 height=500/>

## Installation
***Only works on MacOS with provided library***<br/>
To install simply type: <br/>
`make`

SDL will install automatically.

## Usage
`./doom-nukem`
To load a specific map, use
`./doom-nukem [path_to_the_map]`
