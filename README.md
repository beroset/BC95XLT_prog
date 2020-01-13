# BC95XLT Programmer
This is open source software for programming the channels of a Uniden BC95XLT handheld radio scanner.

The protocol for the device is quite simple.  It uses 9600-N-8-1 with no flow control and simple ASCII commands terminating each line with a CR (`\r`) character.  Here is a list of the commands without argument:

| cmd   | response      | description          |
|-------+---------------+----------------------|
| PRG\r | PRG^OK\r      | Program mode enter   |
| EPG\r | EPG^OK\r      | Exit program mode    |
| MDL\r | MDL^BC95XLT\r | Get model name       |
| VER\r | VER^V1.04\r   | Get software version |

There are also two commands with arguments which are `RCM` and `PCM` which are Read Channel Memmory and Program channel Memory respectively.  

## RCM
Read Channel Memory takes a single argument which is a channel number.

| delimiter | description      | format   | range                    |
|-----------+------------------+----------+--------------------------|
| ^C        | channel number   | xxx      | 1 to 200 inclusive       |

It returns the following parameters.

| delimiter | description      | format   | range                    |
|-----------+------------------+----------+--------------------------|
| ^C        | channel number   | xxx      | 1 to 200 inclusive       |
| ^F        | frequency in MHz | xxx.xxxx |                          |
| ^L        | channel lockout  | S|R      | S = lockout, R = unlock  |
| ^P        | priority         | S|R      | S = priority, R = normal |
| ^D        | delay            | S|R      | S = on, R = off          |

### Example
    
    RCM^C10^F122.7875^LR^PR^DS\r

This is channel 10, 122.7875 MHz, Lockout unlock, priority off, delay on.

## PCM
Program Channel Memory takes the following arguments:

| delimiter | description      | format   | range                    |
|-----------+------------------+----------+--------------------------|
| ^C        | channel number   | xxx      | 1 to 200 inclusive       |
| ^F        | frequency in MHz | xxx.xxxx |                          |
| ^L        | channel lockout  | S|R      | S = lockout, R = unlock  |
| ^P        | priority         | S|R      | S = priority, R = normal |
| ^D        | delay            | S|R      | S = on, R = off          |

It returns one of the following responses:

| response | meaning                        |
|----------+--------------------------------|
| PCM^OK\r | completed without error        |
| PCM^ER\r | parameter error                |
| PCM^NG\r | scanner is not in program mode |

### Example
    
    RCM^C10^F122.7875^LR^PR^DS\r

This is channel 10, 122.7875 MHz, Lockout unlock, priority off, delay on.





