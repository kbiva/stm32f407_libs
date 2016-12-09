# README #

* lib_STM32F407_StdPeriph

Based on STM32F4xx DSP and Standard Peripherals Library v1.7.1 

With some modifications that were needed to compile for the STM32F4 Discovery board.

At the end of "stm32f4xx.h" file from CMSIS following lines must be added:

```C
#if defined (USE_STDPERIPH_DRIVER)
 #include "stm32f4xx_conf.h"
#endif /* USE_STDPERIPH_DRIVER */
```


