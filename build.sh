#!/bin/bash
set -xe

gcc -std=c17 -W -Wall -Wextra -pedantic -o main main.c -Iinclude -lpthread -Llib -lSDL2_ttf -lSDL2 -lSDL2main $(sdl2-config --cflags --libs)
