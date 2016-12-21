# README #

* lib_usart

USART setup. printf uses USART2.

Tested with:
* Open407V-D board from WaveShare
* STM32F4 Discovery board

### Usage example ###
```C
  ...
  USART2_Init(115200);
  ...
  printf("%s\r\n","Hello");
  ...
```
