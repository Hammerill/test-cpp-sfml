# TestSFML
My old restored project for testing SFML library

WARNING: this project haven't restored fully, so it cannot do what should.

Compile and launch
==============================

Below is instruction to launch with MinGW, so you need to install its tools to compile project

Also prepare SFML directory for your OS somewhere and type path to it in commands below instead of Path-to-SFML

```
    g++ -c main.exe -IPath-to-SFML/include

    g++ main.o -LPath-to-SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

    (windows) a
    (unix-like) ./a
```

Also ensure you have binaries (contents of Path-to-SFML/bin) in same directory where executable file locates
