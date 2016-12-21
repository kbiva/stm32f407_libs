# README #

* lib_XPT2046_ILI9325 

Library for the touchpanel with XPT2046 controller
connected to the LCD with ILI9325 controler.
Uses EXTI9_5_IRQHandler interrupt handler.
Tested with:
* 3.2" TFT LCD Display Module, Model: HY32D from Waveshare
* Open407V-D board from WaveShare
* STM32F4 Discovery board

Based on work from Andy Brown. http://andybrown.me.uk
Converted from C++ to C with some modifications.

### Usage example ###
```C
  int16_t tempx=0,tempy=0
  ...
  // initialize touchpanel
  XPT2046_TouchPanel_ILI9325_Init();
  // initialize LCD
  ILI9325_Init(4,10);
  ILI9325_ColorMode(COLOR_16BIT);
  ILI9325_OrientationMode(ORIENTATION_LANDSCAPE);
  ILI9325_ClearScreen(BLACK);	
  ILI9325_SetFont(FONT_8x14);
  // calibrate
  XPT2046_ILI9325_Calibrate();
  // or set previously saved calibration values
  //XPT2046_ILI9325_SetCalibrationValues(0.087679,-0.001352,-10.763244,-0.000770,-0.063818,252.477448);
  ...
  while(1) {
    // wait for a click, XPT2046_clicked is set in the interrupt handler
    for(XPT2046_clicked=0;!XPT2046_clicked;);
    do {
      if(XPT2046_ILI9325_GetCoordinates(&tempx,&tempy)) {
        // if the click is on screen, plot it. This bounds check is necessary because
        // the touch screen can and does extend past the LCD edges.
        if(tempx>=0 && tempx<=ILI9325_GetWidth() && tempy>=0 && tempy<=ILI9325_GetHeight()) {
          ILI9325_SetPixel(tempx,tempy,WHITE);
        }			 
      }
    } while(!GPIO_ReadInputDataBit(XPT2046_IRQ_Port,XPT2046_IRQ_Pin));	
  }
  ...
```
