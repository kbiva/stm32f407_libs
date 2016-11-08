/*
 *  stm32f4_discovery.c
 *
 *  BSP for STM32F4 Discovery and Open407V-D boards
 *
 *  Author: Kestutis Bivainis
 */

#include "stm32f4_discovery.h"

static GPIO_TypeDef* LED_PORT[LEDn] = {LED3_PORT, LED4_PORT, LED5_PORT, LED6_PORT};
static const uint16_t LED_PIN[LEDn] = {LED3_PIN, LED4_PIN, LED5_PIN, LED6_PIN};
static const uint32_t LED_BUS[LEDn] = {LED3_BUS, LED4_BUS, LED5_BUS, LED6_BUS};

static GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {BUTTON1_PORT,JOYSTICKA_PORT,JOYSTICKB_PORT,JOYSTICKC_PORT,JOYSTICKD_PORT,JOYSTICKCTR_PORT};
static const uint16_t BUTTON_PIN[BUTTONn] = {BUTTON1_PIN,JOYSTICKA_PIN,JOYSTICKB_PIN,JOYSTICKC_PIN,JOYSTICKD_PIN,JOYSTICKCTR_PIN};
static const uint32_t BUTTON_BUS[BUTTONn] = {BUTTON1_BUS,JOYSTICKA_BUS,JOYSTICKB_BUS,JOYSTICKC_BUS,JOYSTICKD_BUS,JOYSTICKCTR_BUS};
static const GPIOPuPd_TypeDef BUTTON_PUPD[BUTTONn] = {BUTTON1_PUPD,JOYSTICKA_PUPD,JOYSTICKB_PUPD,JOYSTICKC_PUPD,JOYSTICKD_PUPD,JOYSTICKCTR_PUPD};
static const uint32_t BUTTON_EXTI_PORTSOURCE[BUTTONn] = {BUTTON1_EXTI_PORTSOURCE,JOYSTICKA_EXTI_PORTSOURCE,JOYSTICKB_EXTI_PORTSOURCE,JOYSTICKC_EXTI_PORTSOURCE,JOYSTICKD_EXTI_PORTSOURCE,JOYSTICKCTR_EXTI_PORTSOURCE};
static const uint32_t BUTTON_EXTI_PINSOURCE[BUTTONn] = {BUTTON1_EXTI_PINSOURCE,JOYSTICKA_EXTI_PINSOURCE,JOYSTICKB_EXTI_PINSOURCE,JOYSTICKC_EXTI_PINSOURCE,JOYSTICKD_EXTI_PINSOURCE,JOYSTICKCTR_EXTI_PINSOURCE};
static const uint32_t BUTTON_EXTI_LINE[BUTTONn] = {BUTTON1_EXTI_LINE,JOYSTICKA_EXTI_LINE,JOYSTICKB_EXTI_LINE,JOYSTICKC_EXTI_LINE,JOYSTICKD_EXTI_LINE,JOYSTICKCTR_EXTI_LINE};
static const uint32_t BUTTON_EXTI_IRQN[BUTTONn] = {BUTTON1_EXTI_IRQN,JOYSTICKA_EXTI_IRQN,JOYSTICKB_EXTI_IRQN,JOYSTICKC_EXTI_IRQN,JOYSTICKD_EXTI_IRQN,JOYSTICKCTR_EXTI_IRQN};

typedef struct {
  uint16_t PLL_N;
  uint8_t PLL_P;
  uint8_t PLL_Q;
} _MODE;

static _MODE modes[] = {
  {288,4,6},// 72 MHz
  {336,4,7},// 84 MHz
  {192,2,4},// 96 MHz
  {240,2,5},// 120 MHz
  {288,2,6},// 144 MHz
  {336,2,7},// 168 MHz
  {384,2,8},// 192 MHz overclocked
};

void BSP_LED_Init(Led_TypeDef Led) {

  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(LED_BUS[Led], ENABLE);

  GPIO_InitStructure.GPIO_Pin = LED_PIN[Led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LED_PORT[Led], &GPIO_InitStructure);

  BSP_LED_Off(Led);
}

void BSP_LEDs_Init(void) {

  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED5);
  BSP_LED_Init(LED6);
}

void BSP_LED_On(Led_TypeDef Led) {

  GPIO_SetBits(LED_PORT[Led],LED_PIN[Led]);
}

void BSP_LED_Off(Led_TypeDef Led) {

  GPIO_ResetBits(LED_PORT[Led],LED_PIN[Led]);
}

void BSP_LED_Toggle(Led_TypeDef Led) {

  LED_PORT[Led]->ODR ^= LED_PIN[Led];
}

void BSP_Button_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode) {

  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(BUTTON_BUS[Button], ENABLE);

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
  GPIO_InitStructure.GPIO_PuPd = BUTTON_PUPD[Button];
  GPIO_InitStructure.GPIO_Pin  = BUTTON_PIN[Button];
  GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);

  if (ButtonMode == BUTTON_MODE_EXTI) {

    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    //Connect EXTI Lines to Button Pins
    SYSCFG_EXTILineConfig(BUTTON_EXTI_PORTSOURCE[Button], BUTTON_EXTI_PINSOURCE[Button]);

    //select EXTI line
    EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[Button];
    //select interrupt mode
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    //generate interrupt on rising edge
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    //enable EXTI line
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    //send values to registers
    EXTI_Init(&EXTI_InitStructure);

    //configure NVIC
    //select NVIC channel to configure
    NVIC_InitStructure.NVIC_IRQChannel = BUTTON_EXTI_IRQN[Button];
    //set priority to lowest
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    //set subpriority to lowest
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    //enable IRQ channel
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //update NVIC registers
    NVIC_Init(&NVIC_InitStructure);
   }
}

void BSP_Buttons_Init(ButtonMode_TypeDef ButtonMode) {

  BSP_Button_Init(BUTTON1,ButtonMode);
  BSP_Button_Init(JOYSTICKA,ButtonMode);
  BSP_Button_Init(JOYSTICKB,ButtonMode);
  BSP_Button_Init(JOYSTICKC,ButtonMode);
  BSP_Button_Init(JOYSTICKD,ButtonMode);
  BSP_Button_Init(JOYSTICKCTR,ButtonMode);

}

uint32_t BSP_Button_GetState(Button_TypeDef Button) {

  return !GPIO_ReadInputDataBit(BUTTON_PORT[Button],BUTTON_PIN[Button]);
}

uint8_t BSP_SetSysClock(MCU_SPEED speed) {

  ErrorStatus err;

  RCC_DeInit();
  // Enable HSE
  RCC_HSEConfig(RCC_HSE_ON);
  // Wait till HSE is ready and if Time out is reached exit
  err = RCC_WaitForHSEStartUp();
  if(err==SUCCESS) {
    // Enable high performance mode, System frequency up to 168 MHz
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_PWREN,ENABLE);
    PWR_MainRegulatorModeConfig(PWR_Regulator_Voltage_Scale1);
    // HCLK = SYSCLK / 1
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    // PCLK2 = HCLK / 2
    RCC_PCLK2Config(RCC_HCLK_Div2);
    // PCLK1 = HCLK / 4
    RCC_PCLK1Config(RCC_HCLK_Div4);
    // Configure the main PLL
    RCC_PLLConfig(RCC_PLLSource_HSE,8,modes[speed].PLL_N,modes[speed].PLL_P,modes[speed].PLL_Q);
    // Enable the main PLL
    RCC_PLLCmd(ENABLE);
    // Wait till the main PLL is ready
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET){};
    // Configure Flash prefetch, Instruction cache, Data cache and wait state
    FLASH_PrefetchBufferCmd(ENABLE);
    FLASH_InstructionCacheCmd(ENABLE);
    FLASH_DataCacheCmd(ENABLE);
    FLASH_SetLatency(FLASH_Latency_5);
    //Select the main PLL as system clock source
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    // Wait till the main PLL is used as system clock source
    while(RCC_GetSYSCLKSource()!=RCC_CFGR_SWS_PLL){};
    SystemCoreClockUpdate();
    return 1;
  }
  else {
    return 0;
  }
}

