# README #

* lib_ILI9325

ILI9325 LCD library. Depends on lib_delay.
Tested with 3.2" TFT LCD Display Module HY32D from Waveshare.
LCD size is 320x240. Connected through 16bit FSMC peripheral. 
Supports 16bit and 18bit color, landscape and portrait orientation.

### How do I get set up? ###

  See code example below

### Usage example ###
```C
  ... 
  ILI9325_Init();
  ILI9325_ColorMode(COLOR_18BIT);
  ILI9325_OrientationMode(ORIENTATION_LANDSCAPE);
  ILI9325_ClearScreen(BLACK);
  ...
```