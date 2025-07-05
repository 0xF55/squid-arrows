```text
🎯 Squid Arrows

Squid Arrows is a fast-paced arrow-matching game written in C using raylib.
A sequence of arrow keys appears on screen — press them in the correct order before time runs out.
But be careful: losing might trigger a chaotic surprise 😈

The game generates 8 random directions (Up, Down, Left, Right), and you must press them in the same order under time pressure.
Press the wrong key or take too long, and you lose. If you win, the game congratulates you.
If you lose, the game might... "celebrate" it in its own way.


🛠️ Build and Run

Linux:
  gcc main.c -o squid_arrow -lraylib -lm -ldl -lpthread -lGL
  ./squid_arrow

Windows:
  gcc main.c -o squid_arrow.exe -lraylib -lopengl32 -lgdi32 -lwinmm
  squid_arrow.exe

Make sure raylib is installed correctly and linked during compilation.
Also make sure the 'sounds/' and 'photos/' folders are next to the executable when you run the game.


📁 Project Contents

  main.c       - Full game source code
  sounds/      - .wav sound effects used in gameplay
  photos/      - Optional images used when losing
  README.md    - This file


⚠️ About Break_Pc()

This game includes a chaotic function called Break_Pc() that is triggered randomly when you lose.
It's meant for fun. But here's what it might do:

  - Open many Notepad, Calculator, or Explorer windows
  - Send creepy popup messages (e.g., “I’m coming for you”)
  - Attempt to restart or log off your computer
  - Open local images or random websites
  - Simulate fake Bitcoin mining or console spam

It is recommended to comment out or remove the Break_Pc() call in main.c if you're unsure,
especially if running on a physical machine. This is best tested inside a virtual machine (VM).


📦 Download

Precompiled binaries for Windows and Linux can be found at:
  https://github.com/0xF55/squid-arrows/releases

Make sure to extract all files and keep them in the same folder when running.


👨‍💻 Made by 0xF55

This project is experimental and made purely for fun. Use responsibly.
Feel free to fork, star, or open issues if you have suggestions.
```
