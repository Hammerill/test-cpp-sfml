# TestSFML
My old restored project for testing SFML library

Compile and launch
==============================

```
    g++ -c main.exe -IPath-to-SFML/include

    g++ main.o -LPath-to-SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

    (windows) a
    (unix-like) ./a
```

Also ensure you have binaries (contents of Path-to-SFML/bin) in same directory where executable file locates