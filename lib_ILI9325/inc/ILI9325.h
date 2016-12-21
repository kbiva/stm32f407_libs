/*
 *  ILI9325.h
 *
 *  Author: Kestutis Bivainis
 *
 *  Tested with:
 *  3.2" TFT LCD Display Module, Model: HY32D from Waveshare
 *  Open407V-D board from WaveShare
 *  STM32F4 Discovery board
 *
 */

#ifndef ILI9325_H
#define ILI9325_H

#include "stm32f4xx_conf.h"

typedef enum _COLOR_MODE {
  COLOR_16BIT = 0x1000,
  COLOR_18BIT = 0xD000
} COLOR_MODE;

typedef enum _ORIENTATION_MODE {
  ORIENTATION_PORTRAIT = 0x0000,
  ORIENTATION_LANDSCAPE = 0x0028,
  ORIENTATION_PORTRAIT_REV = 0x0030,
  ORIENTATION_LANDSCAPE_REV = 0x0018
} ORIENTATION_MODE;

typedef enum _FONT_SIZE {
  FONT_6x8 = 0,
  FONT_8x8 = 1,
  FONT_8x14 = 2
} FONT_SIZE;

enum {
  ILI9325_OK = 1,
  ILI9325_ERROR = 0
};

#define DB0_Pin   GPIO_Pin_14
#define DB0_Speed GPIO_Medium_Speed
#define DB0_Mode  GPIO_Mode_AF
#define DB0_OType GPIO_OType_PP
#define DB0_PuPd  GPIO_PuPd_DOWN
#define DB0_Port  GPIOD
#define DB0_Bus   RCC_AHB1Periph_GPIOD
#define DB0_PinSource GPIO_PinSource14

#define DB1_Pin   GPIO_Pin_15
#define DB1_Speed GPIO_Medium_Speed
#define DB1_Mode  GPIO_Mode_AF
#define DB1_OType GPIO_OType_PP
#define DB1_PuPd  GPIO_PuPd_DOWN
#define DB1_Port  GPIOD
#define DB1_Bus   RCC_AHB1Periph_GPIOD
#define DB1_PinSource GPIO_PinSource15

#define DB2_Pin   GPIO_Pin_0
#define DB2_Speed GPIO_Medium_Speed
#define DB2_Mode  GPIO_Mode_AF
#define DB2_OType GPIO_OType_PP
#define DB2_PuPd  GPIO_PuPd_DOWN
#define DB2_Port  GPIOD
#define DB2_Bus   RCC_AHB1Periph_GPIOD
#define DB2_PinSource GPIO_PinSource0

#define DB3_Pin   GPIO_Pin_1
#define DB3_Speed GPIO_Medium_Speed
#define DB3_Mode  GPIO_Mode_AF
#define DB3_OType GPIO_OType_PP
#define DB3_PuPd  GPIO_PuPd_DOWN
#define DB3_Port  GPIOD
#define DB3_Bus   RCC_AHB1Periph_GPIOD
#define DB3_PinSource GPIO_PinSource1

#define DB4_Pin   GPIO_Pin_7
#define DB4_Speed GPIO_Medium_Speed
#define DB4_Mode  GPIO_Mode_AF
#define DB4_OType GPIO_OType_PP
#define DB4_PuPd  GPIO_PuPd_DOWN
#define DB4_Port  GPIOE
#define DB4_Bus   RCC_AHB1Periph_GPIOE
#define DB4_PinSource GPIO_PinSource7

#define DB5_Pin   GPIO_Pin_8
#define DB5_Speed GPIO_Medium_Speed
#define DB5_Mode  GPIO_Mode_AF
#define DB5_OType GPIO_OType_PP
#define DB5_PuPd  GPIO_PuPd_DOWN
#define DB5_Port  GPIOE
#define DB5_Bus   RCC_AHB1Periph_GPIOE
#define DB5_PinSource GPIO_PinSource8

#define DB6_Pin   GPIO_Pin_9
#define DB6_Speed GPIO_Medium_Speed
#define DB6_Mode  GPIO_Mode_AF
#define DB6_OType GPIO_OType_PP
#define DB6_PuPd  GPIO_PuPd_DOWN
#define DB6_Port  GPIOE
#define DB6_Bus   RCC_AHB1Periph_GPIOE
#define DB6_PinSource GPIO_PinSource9

#define DB7_Pin   GPIO_Pin_10
#define DB7_Speed GPIO_Medium_Speed
#define DB7_Mode  GPIO_Mode_AF
#define DB7_OType GPIO_OType_PP
#define DB7_PuPd  GPIO_PuPd_DOWN
#define DB7_Port  GPIOE
#define DB7_Bus   RCC_AHB1Periph_GPIOE
#define DB7_PinSource GPIO_PinSource10

#define DB8_Pin   GPIO_Pin_11
#define DB8_Speed GPIO_Medium_Speed
#define DB8_Mode  GPIO_Mode_AF
#define DB8_OType GPIO_OType_PP
#define DB8_PuPd  GPIO_PuPd_DOWN
#define DB8_Port  GPIOE
#define DB8_Bus   RCC_AHB1Periph_GPIOE
#define DB8_PinSource GPIO_PinSource11

#define DB9_Pin   GPIO_Pin_12
#define DB9_Speed GPIO_Medium_Speed
#define DB9_Mode  GPIO_Mode_AF
#define DB9_OType GPIO_OType_PP
#define DB9_PuPd  GPIO_PuPd_DOWN
#define DB9_Port  GPIOE
#define DB9_Bus   RCC_AHB1Periph_GPIOE
#define DB9_PinSource GPIO_PinSource12

#define DB10_Pin   GPIO_Pin_13
#define DB10_Speed GPIO_Medium_Speed
#define DB10_Mode  GPIO_Mode_AF
#define DB10_OType GPIO_OType_PP
#define DB10_PuPd  GPIO_PuPd_DOWN
#define DB10_Port  GPIOE
#define DB10_Bus   RCC_AHB1Periph_GPIOE
#define DB10_PinSource GPIO_PinSource13

#define DB11_Pin   GPIO_Pin_14
#define DB11_Speed GPIO_Medium_Speed
#define DB11_Mode  GPIO_Mode_AF
#define DB11_OType GPIO_OType_PP
#define DB11_PuPd  GPIO_PuPd_DOWN
#define DB11_Port  GPIOE
#define DB11_Bus   RCC_AHB1Periph_GPIOE
#define DB11_PinSource GPIO_PinSource14

#define DB12_Pin   GPIO_Pin_15
#define DB12_Speed GPIO_Medium_Speed
#define DB12_Mode  GPIO_Mode_AF
#define DB12_OType GPIO_OType_PP
#define DB12_PuPd  GPIO_PuPd_DOWN
#define DB12_Port  GPIOE
#define DB12_Bus   RCC_AHB1Periph_GPIOE
#define DB12_PinSource GPIO_PinSource15

#define DB13_Pin   GPIO_Pin_8
#define DB13_Speed GPIO_Medium_Speed
#define DB13_Mode  GPIO_Mode_AF
#define DB13_OType GPIO_OType_PP
#define DB13_PuPd  GPIO_PuPd_DOWN
#define DB13_Port  GPIOD
#define DB13_Bus   RCC_AHB1Periph_GPIOD
#define DB13_PinSource GPIO_PinSource8

#define DB14_Pin   GPIO_Pin_9
#define DB14_Speed GPIO_Medium_Speed
#define DB14_Mode  GPIO_Mode_AF
#define DB14_OType GPIO_OType_PP
#define DB14_PuPd  GPIO_PuPd_DOWN
#define DB14_Port  GPIOD
#define DB14_Bus   RCC_AHB1Periph_GPIOD
#define DB14_PinSource GPIO_PinSource9

#define DB15_Pin   GPIO_Pin_10
#define DB15_Speed GPIO_Medium_Speed
#define DB15_Mode  GPIO_Mode_AF
#define DB15_OType GPIO_OType_PP
#define DB15_PuPd  GPIO_PuPd_DOWN
#define DB15_Port  GPIOD
#define DB15_Bus   RCC_AHB1Periph_GPIOD
#define DB15_PinSource GPIO_PinSource10

#define RW_Pin    GPIO_Pin_5
#define RW_Speed  GPIO_Medium_Speed
#define RW_Mode   GPIO_Mode_AF
#define RW_OType  GPIO_OType_PP
#define RW_PuPd   GPIO_PuPd_DOWN
#define RW_Port   GPIOD
#define RW_Bus    RCC_AHB1Periph_GPIOD
#define RW_PinSource GPIO_PinSource5

#define RD_Pin    GPIO_Pin_4
#define RD_Speed  GPIO_Medium_Speed
#define RD_Mode   GPIO_Mode_AF
#define RD_OType  GPIO_OType_PP
#define RD_PuPd   GPIO_PuPd_DOWN
#define RD_Port   GPIOD
#define RD_Bus    RCC_AHB1Periph_GPIOD
#define RD_PinSource GPIO_PinSource4

#define RS_Pin    GPIO_Pin_11
#define RS_Speed  GPIO_Medium_Speed
#define RS_Mode   GPIO_Mode_AF
#define RS_OType  GPIO_OType_PP
#define RS_PuPd   GPIO_PuPd_NOPULL
#define RS_Port   GPIOD
#define RS_Bus    RCC_AHB1Periph_GPIOD
#define RS_PinSource GPIO_PinSource11

#define CS_Pin    GPIO_Pin_7
#define CS_Speed  GPIO_Medium_Speed
#define CS_Mode   GPIO_Mode_AF
#define CS_OType  GPIO_OType_PP
#define CS_PuPd   GPIO_PuPd_NOPULL
#define CS_Port   GPIOD
#define CS_Bus    RCC_AHB1Periph_GPIOD
#define CS_PinSource GPIO_PinSource7

typedef struct _PIN {
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_TypeDef* GPIOx;
  uint32_t GPIO_Bus;
  uint16_t GPIO_PinSource;
} PIN;

typedef enum _COMMANDS {
  ILI9325_DRIVER_OUTPUT_CTRL = 0x01,
  ILI9325_LCD_DRIVING_CTRL = 0x02,
  ILI9325_ENTRY_MODE = 0x03,
  ILI9325_16BITS_DATA_FORMAT_CTRL = 0x05,
  ILI9325_DISPLAY_CTRL1 = 0x07,
  ILI9325_DISPLAY_CTRL2 = 0x08,
  ILI9325_DISPLAY_CTRL3 = 0x09,
  ILI9325_DISPLAY_CTRL4 = 0x0A,
  ILI9325_RGB_DISPLAY_IF_CTRL1 = 0x0C,
  ILI9325_FRAME_MARKER_POS = 0x0D,
  ILI9325_RGB_DISPLAY_IF_CTRL2 = 0x0F,
  ILI9325_POWER_CTRL1 = 0x10,
  ILI9325_POWER_CTRL2 = 0x11,
  ILI9325_POWER_CTRL3 = 0x12,
  ILI9325_POWER_CTRL4 = 0x13,
  ILI9325_GRAM_HORZ_AD = 0x20,
  ILI9325_GRAM_VERT_AD = 0x21,
  ILI9325_RW_GRAM = 0x22,
  ILI9325_POWER_CTRL7 = 0x29,
  ILI9325_FRAME_RATE_COLOR_CTRL = 0x2B,
  ILI9325_GAMMA_CTRL1 = 0x30,
  ILI9325_GAMMA_CTRL2 = 0x31,
  ILI9325_GAMMA_CTRL3 = 0x32,
  ILI9325_GAMMA_CTRL4 = 0x35,
  ILI9325_GAMMA_CTRL5 = 0x36,
  ILI9325_GAMMA_CTRL6 = 0x37,
  ILI9325_GAMMA_CTRL7 = 0x38,
  ILI9325_GAMMA_CTRL8 = 0x39,
  ILI9325_GAMMA_CTRL9 = 0x3C,
  ILI9325_GAMMA_CTRL10 = 0x3D,
  ILI9325_HORZ_START_AD = 0x50,
  ILI9325_HORZ_END_AD = 0x51,
  ILI9325_VERT_START_AD = 0x52,
  ILI9325_VERT_END_AD = 0x53,
  ILI9325_DRIVER_OUTPUT_CTRL2 = 0x60,
  ILI9325_BASE_IMAGE_DISPLAY_CTRL = 0x61,
  ILI9325_VERT_SCROLL_CTRL = 0x6A,
  ILI9325_PART_IMG1_DISP_POS = 0x80,
  ILI9325_PART_IMG1_START_AD = 0x81,
  ILI9325_PART_IMG1_END_AD = 0x82,
  ILI9325_PART_IMG2_DISP_POS = 0x83,
  ILI9325_PART_IMG2_START_AD = 0x84,
  ILI9325_PART_IMG2_END_AD = 0x85,
  ILI9325_PANEL_IF_CTRL1 = 0x90,
  ILI9325_PANEL_IF_CTRL2 = 0x92,
  ILI9325_PANEL_IF_CTRL4 = 0x95,
  ILI9325_PANEL_IF_CTRL5 = 0x97,
} COMMANDS;

#define LCD_REG16     (*((volatile uint16_t*)0x60000000))
#define LCD_DAT16     (*((volatile uint16_t*)0x60020000))

uint8_t ILI9325_Init(uint8_t AddressSetupTime,uint8_t DataSetupTime);
void ILI9325_ColorMode(COLOR_MODE color_mode);
void ILI9325_OrientationMode(ORIENTATION_MODE orientation_mode);

void ILI9325_ClearScreen(uint32_t color);
void ILI9325_SetPixel(uint16_t x, uint16_t y, uint32_t color);
void ILI9325_FillPixel(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint32_t *color);
void ILI9325_Fill(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint32_t color);
void ILI9325_FillFromBuffer(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint8_t *data);

void ILI9325_Sleep(void);
void ILI9325_Wakeup(void);

void ILI9325_SetWindow(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1);
uint16_t ILI9325_GetWidth(void);
uint16_t ILI9325_GetHeight(void);

void ILI9325_SetFont(FONT_SIZE font_size);
void ILI9325_SetTextColors(uint32_t fColor, uint32_t bColor);
void ILI9325_PutChar(char c, uint16_t x, uint16_t y);
void ILI9325_PutStr(char *pString, uint16_t x, uint16_t y);
void ILI9325_PutStrCEOL(char *pString, uint16_t x, uint16_t y);
void ILI9325_PutStrCentered(char *pString, uint16_t y);

void ILI9325_ReadRegister(uint8_t reg,uint8_t length,uint16_t *val);
uint16_t ILI9325_ReadPixel(uint16_t x0,uint16_t y0);

#endif
