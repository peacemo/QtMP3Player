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

notice that this player is based on "mplayer" and please name the input MP3 file as
1. Golden Slumbers - The Beatles.mp3
2. Hey Jude - The Beatles.mp3
3. Let It Be - The Beatles.mp3
or just modify the source code to fit the input MP3 files.

to avoid storage abuse on Github, the MP3 files are not uploaded!!


