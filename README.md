# JSJZCYLCourseDesign

insgtall mplayer
```shell
sudo apt install mplayer
```

install gtk 2.0
```shell
sudo apt install libgtk2.0-dev
```

编译命令

```shell
gcc musicPlayerTest.c loadGUI.c -o ../out/musicPlayerTest `pkg -config --libs --cflags gtk+-2.0`
```

