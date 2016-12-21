/*
 *  ILI9325.c
 *
 *  Author: Kestutis Bivainis
 *
 *  Tested with:
 *  3.2" TFT LCD Display Module, Model: HY32D from Waveshare
 *  Open407V-D board from WaveShare
 *  STM32F4 Discovery board
 *
 *  Notes:
 *  FSMC pins must use GPIO_Medium_Speed
 *
 */

#include "stm32f4xx_conf.h"
#include "ILI9325.h"
#include "delay.h"
#include "colors.h"
#include "font6x8.h"
#include "font8x8.h"
#include "font8x14.h"
#include <string.h>

static uint32_t ILI9325_text_foreground_color=WHITE;
static uint32_t ILI9325_text_background_color=BLACK;
static FONT_SIZE ILI9325_font_size;

static unsigned char *FontTable[] = {
    (unsigned char *)FONT6x8,
    (unsigned char *)FONT8x8,
    (unsigned char *)FONT8x14
};

static COLOR_MODE ILI9325_color_mode;
static ORIENTATION_MODE ILI9325_orientation_mode;

static uint16_t DISPLAY_WIDTH=320;
static uint16_t DISPLAY_HEIGHT=240;

static PIN pins[]={
  {{DB0_Pin,DB0_Mode,DB0_Speed,DB0_OType,DB0_PuPd},DB0_Port,DB0_Bus,DB0_PinSource},
  {{DB1_Pin,DB1_Mode,DB1_Speed,DB1_OType,DB1_PuPd},DB1_Port,DB1_Bus,DB1_PinSource},
  {{DB2_Pin,DB2_Mode,DB2_Speed,DB2_OType,DB2_PuPd},DB2_Port,DB2_Bus,DB2_PinSource},
  {{DB3_Pin,DB3_Mode,DB3_Speed,DB3_OType,DB3_PuPd},DB3_Port,DB3_Bus,DB3_PinSource},
  {{DB4_Pin,DB4_Mode,DB4_Speed,DB4_OType,DB4_PuPd},DB4_Port,DB4_Bus,DB4_PinSource},
  {{DB5_Pin,DB5_Mode,DB5_Speed,DB5_OType,DB5_PuPd},DB5_Port,DB5_Bus,DB5_PinSource},
  {{DB6_Pin,DB6_Mode,DB6_Speed,DB6_OType,DB6_PuPd},DB6_Port,DB6_Bus,DB6_PinSource},
  {{DB7_Pin,DB7_Mode,DB7_Speed,DB7_OType,DB7_PuPd},DB7_Port,DB7_Bus,DB7_PinSource},
  {{DB8_Pin,DB8_Mode,DB8_Speed,DB8_OType,DB8_PuPd},DB8_Port,DB8_Bus,DB8_PinSource},
  {{DB9_Pin,DB7_Mode,DB9_Speed,DB9_OType,DB9_PuPd},DB9_Port,DB9_Bus,DB9_PinSource},
  {{DB10_Pin,DB10_Mode,DB10_Speed,DB10_OType,DB10_PuPd},DB10_Port,DB10_Bus,DB10_PinSource},
  {{DB11_Pin,DB11_Mode,DB11_Speed,DB11_OType,DB11_PuPd},DB11_Port,DB11_Bus,DB11_PinSource},
  {{DB12_Pin,DB12_Mode,DB12_Speed,DB12_OType,DB12_PuPd},DB12_Port,DB12_Bus,DB12_PinSource},
  {{DB13_Pin,DB13_Mode,DB13_Speed,DB13_OType,DB13_PuPd},DB13_Port,DB13_Bus,DB13_PinSource},
  {{DB14_Pin,DB14_Mode,DB14_Speed,DB14_OType,DB14_PuPd},DB14_Port,DB14_Bus,DB14_PinSource},
  {{DB15_Pin,DB15_Mode,DB15_Speed,DB15_OType,DB15_PuPd},DB15_Port,DB15_Bus,DB15_PinSource},
  {{RW_Pin, RW_Mode, RW_Speed,RW_OType,RW_PuPd}, RW_Port, RW_Bus,RW_PinSource},
  {{RD_Pin, RD_Mode, RD_Speed,RD_OType,RD_PuPd}, RD_Port, RD_Bus,RD_PinSource},
  {{RS_Pin, RS_Mode, RS_Speed,RS_OType,RS_PuPd}, RS_Port, RS_Bus,RS_PinSource},
  {{CS_Pin, CS_Mode, CS_Speed,CS_OType,CS_PuPd}, CS_Port, CS_Bus,CS_PinSource},
};

static void GPIO_Configuration(void) {

  uint32_t i;

  for(i=0;i<sizeof(pins)/sizeof(PIN);i++) {
    RCC_AHB1PeriphClockCmd(pins[i].GPIO_Bus,ENABLE);
    GPIO_Init(pins[i].GPIOx,&pins[i].GPIO_InitStructure);
    if(pins[i].GPIO_InitStructure.GPIO_Mode==GPIO_Mode_AF)
      GPIO_PinAFConfig(pins[i].GPIOx,pins[i].GPIO_PinSource,GPIO_AF_FSMC);
  }
}

static void FSMC_LCD_Init(uint8_t AddressSetupTime,uint8_t DataSetupTime) {

  FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitStructure;

  // Enable the FSMC Clock
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

  FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = AddressSetupTime;
  FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 0x00;
  FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = DataSetupTime;
  FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
  FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0x00;
  FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 0x00;
  FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_B;

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

  // Enable FSMC Bank1_SRAM Bank
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);

}

static __forceinline void wr_cmd(uint16_t index) {
  LCD_REG16 = index;
}

static __forceinline void wr_reg(uint16_t index,uint16_t val) {
  LCD_REG16 = index;
  LCD_DAT16 = val;
}

static __forceinline void wr_dat(uint16_t val) {
  LCD_DAT16 = val;
}

static __forceinline uint16_t rd_reg(uint16_t index) {
  LCD_REG16 = index;
  return (LCD_DAT16);
}

static __forceinline uint16_t rd_dat(void) {
  return (LCD_DAT16);
}

uint8_t ILI9325_Init(uint8_t AddressSetupTime,uint8_t DataSetupTime) {

  uint16_t id;

  GPIO_Configuration();
  FSMC_LCD_Init(AddressSetupTime,DataSetupTime);

  id=rd_reg(0x00); // 9325

  if(id==0x9325) {

    // default parameters when powering up
    ILI9325_color_mode=COLOR_16BIT;
    ILI9325_orientation_mode=ORIENTATION_LANDSCAPE;

    wr_reg(ILI9325_DRIVER_OUTPUT_CTRL,0x0100);
    wr_reg(ILI9325_LCD_DRIVING_CTRL,0x0700);
    wr_reg(ILI9325_ENTRY_MODE,ILI9325_color_mode|ILI9325_orientation_mode);

    wr_reg(0x0004,0x0000);
    wr_reg(ILI9325_DISPLAY_CTRL2,0x0207);
    wr_reg(ILI9325_DISPLAY_CTRL3,0x0000);
    wr_reg(ILI9325_DISPLAY_CTRL4,0x0000);
    wr_reg(ILI9325_RGB_DISPLAY_IF_CTRL1,0x0001);  // 16bit bus
    wr_reg(ILI9325_FRAME_MARKER_POS,0x0000);
    wr_reg(ILI9325_RGB_DISPLAY_IF_CTRL2,0x0000);
    // Power On sequence
    wr_reg(ILI9325_POWER_CTRL1,0x0000);
    wr_reg(ILI9325_POWER_CTRL2,0x0007);
    wr_reg(ILI9325_POWER_CTRL3,0x0000);
    wr_reg(ILI9325_POWER_CTRL4,0x0000);
    wr_reg(ILI9325_DISPLAY_CTRL1,0x0001);
    DWT_Delay(200000);
    wr_reg(ILI9325_POWER_CTRL1,0x1590);
    wr_reg(ILI9325_POWER_CTRL2,0x0227);
    DWT_Delay(50000);
    wr_reg(ILI9325_POWER_CTRL3,0x009c);
    DWT_Delay(50000);
    wr_reg(ILI9325_POWER_CTRL4,0x1900);
    wr_reg(ILI9325_POWER_CTRL7,0x0023);
    wr_reg(ILI9325_FRAME_RATE_COLOR_CTRL,0x000e);
    DWT_Delay(50000);

    wr_reg(ILI9325_GRAM_HORZ_AD,0x000);
    wr_reg(ILI9325_GRAM_VERT_AD,0x000);

    wr_reg(ILI9325_GAMMA_CTRL1,0x0007);
    wr_reg(ILI9325_GAMMA_CTRL2,0x0707);
    wr_reg(ILI9325_GAMMA_CTRL3,0x0006);
    wr_reg(ILI9325_GAMMA_CTRL4,0x0704);
    wr_reg(ILI9325_GAMMA_CTRL5,0x1f04);
    wr_reg(ILI9325_GAMMA_CTRL6,0x0004);
    wr_reg(ILI9325_GAMMA_CTRL7,0x0000);
    wr_reg(ILI9325_GAMMA_CTRL8,0x0706);
    wr_reg(ILI9325_GAMMA_CTRL9,0x0701);
    wr_reg(ILI9325_GAMMA_CTRL10,0x000f);
    DWT_Delay(50000);
    wr_reg(ILI9325_HORZ_START_AD,0x0000);
    wr_reg(ILI9325_HORZ_END_AD,DISPLAY_HEIGHT-1);
    wr_reg(ILI9325_VERT_START_AD,0x0000);
    wr_reg(ILI9325_VERT_END_AD,DISPLAY_WIDTH-1);
    wr_reg(ILI9325_DRIVER_OUTPUT_CTRL2,0xa700);
    wr_reg(ILI9325_BASE_IMAGE_DISPLAY_CTRL,0x0001);
    wr_reg(ILI9325_VERT_SCROLL_CTRL,0x0000);
    wr_reg(ILI9325_PART_IMG1_DISP_POS,0x0000);
    wr_reg(ILI9325_PART_IMG1_START_AD,0x0000);
    wr_reg(ILI9325_PART_IMG1_END_AD,0x0000);
    wr_reg(ILI9325_PART_IMG2_DISP_POS,0x0000);
    wr_reg(ILI9325_PART_IMG2_START_AD,0x0000);
    wr_reg(ILI9325_PART_IMG2_END_AD,0x0000);
    wr_reg(ILI9325_PANEL_IF_CTRL1,0x0010);
    wr_reg(ILI9325_PANEL_IF_CTRL2,0x0600);
    wr_reg(ILI9325_PANEL_IF_CTRL4,0x0110);
    wr_reg(ILI9325_PANEL_IF_CTRL5,0x0000);
    // display on sequence
    wr_reg(ILI9325_DISPLAY_CTRL1,0x0133);

    return ILI9325_OK;
  }

  return ILI9325_ERROR;
}

void ILI9325_ColorMode(COLOR_MODE color_mode) {

  wr_reg(ILI9325_ENTRY_MODE,color_mode|ILI9325_orientation_mode);
  ILI9325_color_mode=color_mode;
}

void ILI9325_OrientationMode(ORIENTATION_MODE orientation_mode) {

  wr_reg(ILI9325_ENTRY_MODE,orientation_mode|ILI9325_color_mode);
  ILI9325_orientation_mode=orientation_mode;
}

void ILI9325_ClearScreen(uint32_t color) {

  ILI9325_Fill(0,0,ILI9325_GetWidth()-1,ILI9325_GetHeight()-1,color);
}

void ILI9325_Fill(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint32_t color) {

  uint32_t i,j=(x1-x0+1)*(y1-y0+1);
  uint16_t b1,b2;

  ILI9325_SetWindow(x0,y0,x1,y1);

  switch(ILI9325_color_mode) {

    case COLOR_16BIT:
      b1=(color & 0xf80000) >> 8 | (color & 0xfc00) >> 5 | (color & 0xf8) >> 3;
      for(i=0;i<j;i++) {
        wr_dat(b1);
      }
      break;
    case COLOR_18BIT:
        b1=color>>22;
        b2=(color & 0xfc0000) >> 6 | (color & 0xfc00) >> 4 | (color & 0xfc) >> 2;
      for(i=0;i<j;i++) {
        wr_dat(b1);
        wr_dat(b2);
      }
      break;
  }
}

void ILI9325_SetWindow(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1) {

  switch(ILI9325_orientation_mode){
    case ORIENTATION_LANDSCAPE:
      wr_reg(ILI9325_HORZ_START_AD,DISPLAY_HEIGHT-1-y1);
      wr_reg(ILI9325_HORZ_END_AD,DISPLAY_HEIGHT-1-y0);
      wr_reg(ILI9325_VERT_START_AD,x0);
      wr_reg(ILI9325_VERT_END_AD,x1);
      wr_reg(ILI9325_GRAM_HORZ_AD,DISPLAY_HEIGHT-1-y0);
      wr_reg(ILI9325_GRAM_VERT_AD,x0);
    break;
    case ORIENTATION_LANDSCAPE_REV:
      wr_reg(ILI9325_HORZ_START_AD,y0);
      wr_reg(ILI9325_HORZ_END_AD,y1);
      wr_reg(ILI9325_VERT_START_AD,DISPLAY_WIDTH-1-x1);
      wr_reg(ILI9325_VERT_END_AD,DISPLAY_WIDTH-1-x0);
      wr_reg(ILI9325_GRAM_HORZ_AD,y0);
      wr_reg(ILI9325_GRAM_VERT_AD,DISPLAY_WIDTH-1-x0);
    break;
    case ORIENTATION_PORTRAIT:
      wr_reg(ILI9325_HORZ_START_AD,DISPLAY_HEIGHT-1-x1);
      wr_reg(ILI9325_HORZ_END_AD,DISPLAY_HEIGHT-1-x0);
      wr_reg(ILI9325_VERT_START_AD,DISPLAY_WIDTH-1-y1);
      wr_reg(ILI9325_VERT_END_AD,DISPLAY_WIDTH-1-y0);
      wr_reg(ILI9325_GRAM_HORZ_AD,DISPLAY_HEIGHT-1-x0);
      wr_reg(ILI9325_GRAM_VERT_AD,DISPLAY_WIDTH-1-y0);
    break;
    case ORIENTATION_PORTRAIT_REV:
      wr_reg(ILI9325_HORZ_START_AD,x0);
      wr_reg(ILI9325_HORZ_END_AD,x1);
      wr_reg(ILI9325_VERT_START_AD,y0);
      wr_reg(ILI9325_VERT_END_AD,y1);
      wr_reg(ILI9325_GRAM_HORZ_AD,x0);
      wr_reg(ILI9325_GRAM_VERT_AD,y0);
    break;
  }
  wr_cmd(ILI9325_RW_GRAM);
}

void ILI9325_FillPixel(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint32_t *color) {

  uint32_t i,j=(x1-x0+1)*(y1-y0+1);

  ILI9325_SetWindow(x0,y0,x1,y1);

  switch(ILI9325_color_mode) {
    case COLOR_16BIT:
      for(i=0;i<j;i++) {
        wr_dat((color[i] & 0xf80000) >> 8 | (color[i] & 0xfc00) >> 5 | (color[i] & 0xf8) >> 3);
      }
      break;
    case COLOR_18BIT:
      for(i=0;i<j;i++) {
        wr_dat(color[i]>>22);
        wr_dat((color[i] & 0xfc0000) >> 6 | (color[i] & 0xfc00) >> 4 | (color[i] & 0xfc) >> 2);
      }
      break;
  }
}

void ILI9325_FillFromBuffer(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint8_t *data) {

  uint32_t i,j=(x1-x0+1)*(y1-y0+1);
  uint16_t p;

  ILI9325_SetWindow(x0,y0,x1,y1);

  switch(ILI9325_color_mode) {
    case COLOR_16BIT:
      for(i=0;i<j;i++) {
        p=(*data++)<<8;
        p|=*data++;
        wr_dat(p);
      }
      break;
    case COLOR_18BIT:
      for(i=0;i<j;i++) {
        p=(*data)>>6;
        wr_dat(p);
        p=(*data++)<<10;
        p|=(*data++)<<4;
        p|=(*data++)>>2;
        wr_dat(p);
      }
      break;
  }
}

void ILI9325_SetPixel(uint16_t x, uint16_t y, uint32_t color) {

  ILI9325_SetWindow(x,y,x,y);

  switch(ILI9325_color_mode) {
    case COLOR_16BIT:
      wr_dat((color & 0xf80000) >> 8 | (color & 0xfc00) >> 5 | (color & 0xf8) >> 3);
      break;
    case COLOR_18BIT:
      wr_dat(color>>22);
      wr_dat((color & 0xfc0000) >> 6 | (color & 0xfc00) >> 4 | (color & 0xfc) >> 2);
      break;
  }
}

void ILI9325_Sleep(void) {

  wr_reg(ILI9325_DISPLAY_CTRL1, 0x0131);
  DWT_Delay(10000);
  wr_reg(ILI9325_DISPLAY_CTRL1, 0x0130);
  DWT_Delay(10000);
  wr_reg(ILI9325_DISPLAY_CTRL1, 0x0000);
  wr_reg(ILI9325_POWER_CTRL1, 0x0080);
  wr_reg(ILI9325_POWER_CTRL2, 0x0000);
  wr_reg(ILI9325_POWER_CTRL3, 0x0000);
  wr_reg(ILI9325_POWER_CTRL4, 0x0000);
  DWT_Delay(10000);
  wr_reg(ILI9325_POWER_CTRL1, 0x0082);
}

void ILI9325_Wakeup(void) {

  wr_reg(ILI9325_POWER_CTRL1, 0x0080);
  wr_reg(ILI9325_POWER_CTRL2, 0x0000);
  wr_reg(ILI9325_POWER_CTRL3, 0x0000);
  wr_reg(ILI9325_POWER_CTRL4, 0x0000);
  wr_reg(ILI9325_DISPLAY_CTRL1, 0x0001);
  DWT_Delay(200000);
  wr_reg(ILI9325_POWER_CTRL1, 0x1590);
  wr_reg(ILI9325_POWER_CTRL2, 0x0227);
  DWT_Delay(50000);
  wr_reg(ILI9325_POWER_CTRL3, 0x009c);
  DWT_Delay(50000);
  wr_reg(ILI9325_POWER_CTRL4, 0x1900);
  wr_reg(ILI9325_POWER_CTRL7, 0x0023);
  DWT_Delay(50000);
  wr_reg(ILI9325_DISPLAY_CTRL1, 0x0133);
}

uint16_t ILI9325_GetWidth(void) {

  uint16_t ret;

  switch(ILI9325_orientation_mode){
    case ORIENTATION_LANDSCAPE:
    case ORIENTATION_LANDSCAPE_REV:
      ret=DISPLAY_WIDTH;
    break;
    case ORIENTATION_PORTRAIT:
    case ORIENTATION_PORTRAIT_REV:
      ret=DISPLAY_HEIGHT;
    break;
  }
  return ret;
}

uint16_t ILI9325_GetHeight(void) {

  uint16_t ret;

  switch(ILI9325_orientation_mode){
    case ORIENTATION_LANDSCAPE:
    case ORIENTATION_LANDSCAPE_REV:
      ret=DISPLAY_HEIGHT;
    break;
    case ORIENTATION_PORTRAIT:
    case ORIENTATION_PORTRAIT_REV:
      ret=DISPLAY_WIDTH;
    break;
  }
  return ret;
}

void ILI9325_SetFont(FONT_SIZE font_size) {

  ILI9325_font_size=font_size;
}

void ILI9325_SetTextColors(uint32_t fColor, uint32_t bColor) {

  ILI9325_text_foreground_color = fColor;
  ILI9325_text_background_color = bColor;
}

void ILI9325_PutChar(char c, uint16_t x, uint16_t y) {

  uint32_t i,j;
  uint32_t nCols;
  uint32_t nRows;
  uint32_t nBytes;
  uint8_t PixelRow;
  uint8_t Mask;
  uint32_t Word0;
  uint32_t Word1;
  unsigned char *pFont;
  unsigned char *pChar;

  // get pointer to the beginning of the selected font table
  pFont = (unsigned char *)FontTable[ILI9325_font_size];

  // get the nColumns, nRows and nBytes
  nCols = *pFont;
  nRows = *(pFont + 1);
  nBytes = *(pFont + 2);

  // get pointer to the first byte of the desired character
  pChar = pFont + (nBytes * (c - 0x1F));

  ILI9325_SetWindow(x,y,x + nCols - 1,y + nRows - 1);

  // loop on each row
  for (i = 0; i < nRows; i++) {

    // copy pixel row from font table and then decrement row
    PixelRow = *pChar++;

    // loop on each pixel in the row (left to right)
    // Note: we do two pixels each loop
    Mask = 0x80;
    for (j = 0; j < nCols; j += 2) {

      // if pixel bit set, use foreground color; else use the background color
      // now get the pixel color for two successive pixels
      if (PixelRow & Mask)
        Word0 = ILI9325_text_foreground_color;
      else
        Word0 = ILI9325_text_background_color;
      Mask >>= 1;

      if (PixelRow & Mask)
        Word1 = ILI9325_text_foreground_color;
      else
        Word1 = ILI9325_text_background_color;
      Mask >>= 1;

      switch(ILI9325_color_mode){
        case COLOR_16BIT:
          wr_dat((Word0 & 0xf80000) >> 8 | (Word0 & 0xfc00) >> 5 | (Word0 & 0xf8) >> 3);
          wr_dat((Word1 & 0xf80000) >> 8 | (Word1 & 0xfc00) >> 5 | (Word1 & 0xf8) >> 3);
          break;
        case COLOR_18BIT:
          wr_dat(Word0>>22);
          wr_dat((Word0 & 0xfc0000) >> 6 | (Word0 & 0xfc00) >> 4 | (Word0 & 0xfc) >> 2);
          wr_dat(Word1>>22);
          wr_dat((Word1 & 0xfc0000) >> 6 | (Word1 & 0xfc00) >> 4 | (Word1 & 0xfc) >> 2);
          break;
      }
    }
  }
}

void ILI9325_PutStr(char *pString, uint16_t x, uint16_t y) {

  if(y+FontTable[ILI9325_font_size][1]>ILI9325_GetHeight())
    return;

  // loop until null-terminator is seen
  while (*pString) {
    if (x+FontTable[ILI9325_font_size][0]>ILI9325_GetWidth()) break;
    // draw the character
    ILI9325_PutChar(*pString++, x, y);
    x+=FontTable[ILI9325_font_size][0];
  }
}

void ILI9325_PutStrCEOL(char *pString, uint16_t x, uint16_t y) {

  if(y+FontTable[ILI9325_font_size][1]>ILI9325_GetHeight())
    return;

  // loop until null-terminator is seen
  while (*pString) {
    if (x+FontTable[ILI9325_font_size][0]>ILI9325_GetWidth()) break;
    // draw the character
    ILI9325_PutChar(*pString++, x, y);
    x+=FontTable[ILI9325_font_size][0];
  }
  while(x+FontTable[ILI9325_font_size][0]<=ILI9325_GetWidth()) {
    ILI9325_PutChar(' ', x, y);
    x+=FontTable[ILI9325_font_size][0];
  }
}

void ILI9325_PutStrCentered(char *pString, uint16_t y) {

  uint32_t length=strlen(pString)*FontTable[ILI9325_font_size][0];

  ILI9325_PutStr(pString,length>ILI9325_GetWidth()?0:(ILI9325_GetWidth()-length)/2,y);
}

void ILI9325_ReadRegister(uint8_t reg,uint8_t length,uint16_t *val) {

  uint8_t i;

  // first read is dummy read
  val[0]=rd_reg(reg);

  for(i=0;i<length;i++) {
    val[i]=rd_dat();
  }
}

uint16_t ILI9325_ReadPixel(uint16_t x0,uint16_t y0) {

  ILI9325_SetWindow(x0,y0,x0,y0);
  // first read is dummy read
  rd_dat();

  switch(ILI9325_color_mode){
    case COLOR_16BIT:
      break;
    case COLOR_18BIT:
      // Controller converts 18bit to 16bit
      // Don't know why, but another dummy read is needed
      rd_dat();
      break;
  }

  return rd_dat();
}
