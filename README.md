# c-dsp
Digital Signal Processing in C

# TO DO
- [ ] Find a way to record input from the mic
- [ ] Try to do the same, but with the guitar signal
- [ ] Output real time audio
- [ ] Try different DSPs

# Notes
- `parec-simple.c`: Script borrowed from the [Pulseaudio API
  Docs](https://freedesktop.org/software/pulseaudio/doxygen/parec-simple_8c-example.html)

To compile it: `$ gcc parec-simple.c -o parec-simple $(pkg-config --cflags --libs libpulse-simple)`

To write sound from microphone: `$ ./parec-simple > test.raw`

To convert to `.wav`: `$ sox -t raw -b 16 -e signed-integer -r 48000 -c 2 test.raw test.wav` (Note that the arguments
depend on your system!)

- I tried using Pulseaudio API but it had too much latency. I thought about using ALSA, but for the sake of making it a
  little bit more portable I decided to use [Portaudio](https://www.portaudio.com/). I tested a few examples and looks
  good so far. The next step will be to try connecting the guitar and using the fuzz example.

# References
- https://acassis.wordpress.com/2012/10/04/reading-microphone-audio-using-pulseaudio-simple/
