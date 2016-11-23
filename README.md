# arduino-eink-display-progmem
Fork of NOA Labs' E-ink display library that uses less RAM.

When working on a project a with a [SmartPrototyping E-ink display](http://www.smart-prototyping.com/E-ink-E-paper-Display-module-3.3V-2.04-inch-177x72.html) I ran into a problem: importing the library alone used around 90% of the 2kb RAM available in my ATMega328P based Arduino.

As working with ~200 bytes of RAM proved a bit challenging, I did some modifications to the library. The font used for rendering text was saved as an array in the RAM, it has been moved to the program space. Some other arrays were moved as well. 
