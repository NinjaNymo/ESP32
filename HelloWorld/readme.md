# ESP32/HelloWorld
As stripped down as a ESP32 project can get.

An interesting twirk is that ```printf()``` requires ```\n``` to print as ```stdout``` is _buffered_ by default.

Without ```\n```, the ```stdout``` buffer can be flushed using ```fflush(stdout)```.