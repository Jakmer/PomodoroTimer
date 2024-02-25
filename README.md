# Pomodor Timer

This program simulates a Pomodoro Timer. To achieve this I used networking and multithreading. Multiple clients may affect **Server's Timer** by running commands: **Start, Stop, Skip, Restart** and change display color from server's side.

## Build and run

To build this project follow these simply steps

    mkdir build
    cd build
    cmake ..
    make

And then in workspace folder go to bin/ and run server

    cd ../bin
    ./server

And then client with 2 command args 

    ./client <command> <color>

Commands:

- **Start**

- **Stop**

- **Skip**

- **Restart**

Colors:

- **Black**
- **Red**
- **Green**
- **Yellow**
- **Blue**
- **Magenta**
- **Cyan**
- **White**