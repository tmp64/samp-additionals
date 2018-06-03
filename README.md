# SAMP Additionals
This plugin contains various functions for GTA SAMP.

## Natives
> native GetUnixDate(unixtime, &year=0, &month=0, &day=0, &hour=0, &minute=0, &second=0);

The function parses UNIX timestamp and returns date and time in separate variables
* unixtime - (int) UNIX timestamp (number of seconds since 1 Jan 1970)
* year     - (int) variable to store the year
* month    - (int) variable to store the month
* day      - (int) variable to store the day
* hour     - (int) variable to store the hour
* minute   - (int) variable to store the minute
* second   - (int) variable to store the second

Example:
```
new buffer[255];
new year, month, day, hours, minutes, seconds;
GetUnixDate(gettime(), year, month, day, hours, minutes, seconds);
format(buffer, sizeof(buffer), "Current GetUnixDate: %i.%i.%i %i:%i:%i", year, month, day, hours, minutes, seconds);
SendClientMessage(playerid, -1, buffer);

Output:
Current GetUnixDate: 2017.1.29 22:00:00
```

> native FormatUnixDate(output[], len, const format[], unixtime);

The function parses UNIX timestamp and returns formatted string
* output   - (string) string to put the formatted date
* len      - (int) size of the string
* foramt   - (string) format
* unixtime - (int) UNIX timestamp (number of seconds since 1 Jan 1970)

Example:
```
new buffer[255];
FormatUnixDate(buffer, sizeof(buffer), "Current FormatUnixDate: %c", gettime());
SendClientMessage(playerid, -1, buffer);

Output:
Current FormatUnixDate: Sun Jan 29 22:00:00 2017
```

## Building guide
Windows - download the source files and use Microsoft Visual Studio 2015 (older versions may work, but I use this one) to compile.

Linux - `git clone` the repository and then use `make`. Don't forget to install g++:i386 and i386 libraries.

## TODO
* More functions
* Add timezone support

## Thanks to:
* SA-MP Forums - for plugin development guide
* Google the Search Engine
* Stack Overflow
* SA-MP Development Team - for making the game
* Timerfix plugin - I used its Makefile :D
