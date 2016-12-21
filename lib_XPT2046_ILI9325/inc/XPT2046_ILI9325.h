/*
 *  XPT2046_ILI9325.h
 *
 *  Author: Kestutis Bivainis
 *
 *  library for the touchpanel with XPT2046 controller
 *  connected to the LCD with ILI9325 controler.
 *
 *  Uses EXTI9_5_IRQHandler interrupt handler.
 *
 *  Tested with:
 *  3.2" TFT LCD Display Module, Model: HY32D from Waveshare
 *  Open407V-D board from WaveShare
 *  STM32F4 Discovery board
 *
 *  Based on work from Andy Brown.
 *  Converted from C++ to C with some modifications.
 */
/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#ifndef _XPT2046_ILI9325_H_
#define _XPT2046_ILI9325_H_

#include "stm32f4xx_conf.h"

// XPT2046 on SPI2

#define XPT2046_SCK_Pin       GPIO_Pin_13
#define XPT2046_SCK_Speed     GPIO_High_Speed
#define XPT2046_SCK_Mode      GPIO_Mode_AF
#define XPT2046_SCK_OType     GPIO_OType_PP
#define XPT2046_SCK_PuPd      GPIO_PuPd_UP
#define XPT2046_SCK_Port      GPIOB
#define XPT2046_SCK_Bus       RCC_AHB1Periph_GPIOB
#define XPT2046_SCK_PinSource GPIO_PinSource13

#define XPT2046_MISO_Pin       GPIO_Pin_14
#define XPT2046_MISO_Speed     GPIO_High_Speed
#define XPT2046_MISO_Mode      GPIO_Mode_AF
#define XPT2046_MISO_OType     GPIO_OType_PP
#define XPT2046_MISO_PuPd      GPIO_PuPd_UP
#define XPT2046_MISO_Port      GPIOB
#define XPT2046_MISO_Bus       RCC_AHB1Periph_GPIOB
#define XPT2046_MISO_PinSource GPIO_PinSource14

#define XPT2046_MOSI_Pin       GPIO_Pin_15
#define XPT2046_MOSI_Speed     GPIO_High_Speed
#define XPT2046_MOSI_Mode      GPIO_Mode_AF
#define XPT2046_MOSI_OType     GPIO_OType_PP
#define XPT2046_MOSI_PuPd      GPIO_PuPd_UP
#define XPT2046_MOSI_Port      GPIOB
#define XPT2046_MOSI_Bus       RCC_AHB1Periph_GPIOB
#define XPT2046_MOSI_PinSource GPIO_PinSource15

#define XPT2046_CS_Pin       GPIO_Pin_4
#define XPT2046_CS_Speed     GPIO_High_Speed
#define XPT2046_CS_Mode      GPIO_Mode_OUT
#define XPT2046_CS_OType     GPIO_OType_PP
#define XPT2046_CS_PuPd      GPIO_PuPd_UP
#define XPT2046_CS_Port      GPIOC
#define XPT2046_CS_Bus       RCC_AHB1Periph_GPIOC
#define XPT2046_CS_PinSource GPIO_PinSource4

#define XPT2046_IRQ_Pin       GPIO_Pin_5
#define XPT2046_IRQ_Speed     GPIO_High_Speed
#define XPT2046_IRQ_Mode      GPIO_Mode_IN
#define XPT2046_IRQ_OType     GPIO_OType_PP
#define XPT2046_IRQ_PuPd      GPIO_PuPd_UP
#define XPT2046_IRQ_Port      GPIOC
#define XPT2046_IRQ_Bus       RCC_AHB1Periph_GPIOC
#define XPT2046_IRQ_PinSource GPIO_PinSource5

#define XPT2046_EXTI_Portsource EXTI_PortSourceGPIOC
#define XPT2046_EXTI_Line       EXTI_Line5
#define XPT2046_EXTI_IRQn       EXTI9_5_IRQn

typedef struct _XPT2046_PIN {
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_TypeDef* GPIOx;
  uint32_t GPIO_Bus;
  uint16_t GPIO_PinSource;
} XPT2046_PIN;

enum ControlBits {
  START = 0x80,
  A2    = 0x40,
  A1    = 0x20,
  A0    = 0x10,
  MODE1 = 0x08,
  MODE0 = 0x04,
  PD1   = 0x02,
  PD0   = 0x01
};

#define  CHX A0
#define  CHY A0|A2

void XPT2046_ILI9325_Init(void);
uint8_t XPT2046_ILI9325_Calibrate(void);
void XPT2046_ILI9325_SetCalibrationValues(float ax,float bx,float dx,float ay,float by,float dy);
void XPT2046_ILI9325_GetCalibrationValues(float *ax,float *bx,float *dx,float *ay,float *by,float *dy);
uint8_t XPT2046_ILI9325_GetCoordinates(int16_t *x, int16_t *y);

#endif
