# BC95XLT Programmer
This is open source software for programming the channels of a Uniden BC95XLT handheld radio scanner.

### Building the software
This software uses CMake to create a build system.  Under Linux, to configure a build from the main directory:

`cmake -DCMAKE_BUILD_TYPE=Release -S . -B build`

That will create a `build` subdirectory with all of the needed files in it.  To then build we can use CMake again:

`cmake --build build`

The software will then be built and if all goes well, it will create an executable file named `BC95XLT_prog` in the `build/src` directory.  You can also install the software if desired:

`cmake --build build -t install`

### Using the software

The software is a very simple command line program.  If you run it without command line arguments, it will describe its own usage:

```
Usage: BC95XLT_prog R|W serialport
Examples:
BC95XLT_prog R /dev/ttyUSB1 > channel.txt
BC95XLT_prog W /dev/ttyUSB1 < channel.txt
```

The *serialport* argument is as shown above, `/dev/ttyUSB1` for Linux, or something like `COM4` for Windows.

The `R` or `W` arguments are case sensitive and stand for Read and Write.  In Read mode, it will read all 200 channels from the scanner and print them, with some addtional information to `stdout`.  In the examples shown above we redirect this output to a file.  The first few lines on my scanner look like this:

```
# model: MDL^BC95XLT
# version: VER^V1.02
1,453.8000,R,S,S
2,460.4125,R,S,S
3,162.5500,S,R,R
```
Any line with `#` in the first position is a comment and will be ignored when read, so the first two lines showing the model and version are solely for information and are not used by the program.  Those first lines show exactly what was received by the software from the scanner.  All of the other lines show the currently programmed information for each of the 200 channels.  The format is:

*channel_number*,*frequency*,*lockout*,*priority*,*delay*

Note that spaces are not allowed.  The data is a direct mapping to the data read/programmed by the [RCM](#RCM) and [PCM](#PCM) commands as shown below.

It's recommended to read all of the channels first, then modify the text file using a text editor, and then write it back using Write mode.  Because lines beginning with `#` are comment lines, it can be handy to use that to document the channels like this:

```
# model: MDL^BC95XLT
# version: VER^V1.02
# County Sheriff dispatch
1,453.8000,R,S,S
# County Sheriff tactical
2,460.4125,R,S,S
# Weather
3,162.5500,S,R,R
```

To write the configuration into the scanner, simply use the `W` option as shown above.  Note that for Read mode, all 200 channels will be read and in order, but in Write mode, only the channels listed in the file will be written and they may be in any order.  If the same channel number appears multiple times, only the last one will have effect.

## Serial protocol details

The protocol for the device is quite simple.  It uses 9600-N-8-1 with no flow control and simple ASCII commands terminating each line with a CR (`\r`) character.  Here is a list of the commands without argument:

| cmd   | response      | description          |
|-------|---------------|----------------------|
| PRG\r | PRG^OK\r      | Program mode enter   |
| EPG\r | EPG^OK\r      | Exit program mode    |
| MDL\r | MDL^BC95XLT\r | Get model name       |
| VER\r | VER^V1.04\r   | Get software version |

There are also two commands with arguments which are `RCM` and `PCM` which are Read Channel Memory and Program channel Memory respectively.  

### RCM
Read Channel Memory takes a single argument which is a channel number.

| delimiter | description      | format   | range                    |
|-----------|------------------|----------|--------------------------|
| ^C        | channel number   | xxx      | 1 to 200 inclusive       |

It returns the following parameters.

| delimiter | description      | format   | range                    |
|-----------|------------------|----------|--------------------------|
| ^C        | channel number   | xxx      | 1 to 200 inclusive       |
| ^F        | frequency in MHz | xxx.xxxx |                          |
| ^L        | channel lockout  | S|R      | S = lockout, R = unlock  |
| ^P        | priority         | S|R      | S = priority, R = normal |
| ^D        | delay            | S|R      | S = on, R = off          |

#### Example
    
    RCM^C10^F122.7875^LR^PR^DS\r

This is channel 10, 122.7875 MHz, Lockout unlock, priority off, delay on.

### PCM
Program Channel Memory takes the following arguments:

| delimiter | description      | format   | range                    |
|-----------|------------------|----------|--------------------------|
| ^C        | channel number   | xxx      | 1 to 200 inclusive       |
| ^F        | frequency in MHz | xxx.xxxx |                          |
| ^L        | channel lockout  | S|R      | S = lockout, R = unlock  |
| ^P        | priority         | S|R      | S = priority, R = normal |
| ^D        | delay            | S|R      | S = on, R = off          |

It returns one of the following responses:

| response | meaning                        |
|----------|--------------------------------|
| PCM^OK\r | completed without error        |
| PCM^ER\r | parameter error                |
| PCM^NG\r | scanner is not in program mode |

#### Example
    
    RCM^C10^F122.7875^LR^PR^DS\r

This is channel 10, 122.7875 MHz, Lockout unlock, priority off, delay on.
