#!/bin/bash
set -xe

gcc -W -Wall -Wextra -pedantic -o main main.c -Iinclude -lpthread -Llib -lSDL2 -lSDL2main
