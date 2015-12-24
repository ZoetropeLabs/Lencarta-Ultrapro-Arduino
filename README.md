Lencarta-Ultrapro-Arduino
=========================

An Arduino library used to control Lencarta Ultrapro Flash Heads

This library was created for and tested on the UltraPro 300 series of Lencarta's studio flashes. It is likely to work with other flashes in the UltraPro series and possibly other series of flashes but this has not been tested. It allows the flash heads to be controlled remotely using an arduino with an nRF24L01+ radio. The radio should be attached to the normal arduino SPI pins and the CE and CS pin should be specified in the constructor.

There's a blog article about how this library came to exist [here](https://zoetrope-imaging.co.uk/tech-blog/reverse-engineering-wireless-pro-studio-lighting)

Documentation
-------------
The documentation can be viewed at `lib/lencarta_ultrapro/docs/html/classlencarta__ultrapro.html`. 

Usage
-----
The library is fairly simple to use, there is a short example in the src/ directory. 

Be aware that there should be some delay between commands sent to the flash, if there is no delay the flash may not pick up
the command. 

All library methods can be called using two forms of addressing. Either pass in the id and group of the flash head as the first two arguments or pass an array of [id, group]. This makes using multiple flashes simpler as they can be assigned to an array e.g:

```c
byte someStrobe[2] = {1,2};
byte someOtherStrobe[2] = {5,6};

strobes.fireFlash(someStrobe);
strobes.fireFlash(someOtherStrobe);
```

Credits
-------
Created by Richard Webb for [Zoetrope](http://zoetrope.io) with [Lencarta's](http://lencarta.com/) blessing.

With thanks to TMRh20's [fork](https://github.com/TMRh20) of J. Coliz's RF24 library which is bundled with this library for convienence.
