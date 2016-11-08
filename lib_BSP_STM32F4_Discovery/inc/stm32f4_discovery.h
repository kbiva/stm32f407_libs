/*
 *  stm32f4_discovery.h
 *
 *  BSP for STM32F4 Discovery and Open407V-D boards
 *
 *  Author: Kestutis Bivainis
 */

#ifndef __STM32F4_DISCOVERY_H
#define __STM32F4_DISCOVERY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_conf.h"

typedef enum {
  LED3 = 0,
  LED_ORANGE = 0,
  LED4 = 1,
  LED_GREEN = 1,
  LED5 = 2,
  LED_RED = 2,
  LED6 = 3,
  LED_BLUE = 3,
} Led_TypeDef;

typedef enum {
  BUTTON1 = 0,
  JOYSTICKA,
  JOYSTICKB,
  JOYSTICKC,
  JOYSTICKD,
  JOYSTICKCTR,
} Button_TypeDef;

typedef enum {
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

#define LEDn 4

#define LED3_PIN  GPIO_Pin_13
#define LED3_PORT GPIOD
#define LED3_BUS  RCC_AHB1Periph_GPIOD

#define LED4_PIN  GPIO_Pin_12
#define LED4_PORT GPIOD
#define LED4_BUS  RCC_AHB1Periph_GPIOD

#define LED5_PIN  GPIO_Pin_14
#define LED5_PORT GPIOD
#define LED5_BUS  RCC_AHB1Periph_GPIOD

#define LED6_PIN  GPIO_Pin_15
#define LED6_PORT GPIOD
#define LED6_BUS  RCC_AHB1Periph_GPIOD

#define BUTTONn 6

#define BUTTON1_PIN             GPIO_Pin_0
#define BUTTON1_PORT            GPIOA
#define BUTTON1_BUS             RCC_AHB1Periph_GPIOA
#define BUTTON1_PUPD            GPIO_PuPd_NOPULL
#define BUTTON1_EXTI_PORTSOURCE EXTI_PortSourceGPIOA
#define BUTTON1_EXTI_PINSOURCE  GPIO_PinSource0
#define BUTTON1_EXTI_LINE       EXTI_Line0
#define BUTTON1_EXTI_IRQN       EXTI0_IRQn

#define JOYSTICKA_PIN             GPIO_Pin_4
#define JOYSTICKA_PORT            GPIOA
#define JOYSTICKA_BUS             RCC_AHB1Periph_GPIOA
#define JOYSTICKA_PUPD            GPIO_PuPd_UP
#define JOYSTICKA_EXTI_PORTSOURCE EXTI_PortSourceGPIOA
#define JOYSTICKA_EXTI_PINSOURCE  GPIO_PinSource4
#define JOYSTICKA_EXTI_LINE       EXTI_Line4
#define JOYSTICKA_EXTI_IRQN       EXTI4_IRQn

#define JOYSTICKB_PIN             GPIO_Pin_6
#define JOYSTICKB_PORT            GPIOA
#define JOYSTICKB_BUS             RCC_AHB1Periph_GPIOA
#define JOYSTICKB_PUPD            GPIO_PuPd_UP
#define JOYSTICKB_EXTI_PORTSOURCE EXTI_PortSourceGPIOA
#define JOYSTICKB_EXTI_PINSOURCE  GPIO_PinSource6
#define JOYSTICKB_EXTI_LINE       EXTI_Line6
#define JOYSTICKB_EXTI_IRQN       EXTI9_5_IRQn

#define JOYSTICKC_PIN             GPIO_Pin_15
#define JOYSTICKC_PORT            GPIOB
#define JOYSTICKC_BUS             RCC_AHB1Periph_GPIOB
#define JOYSTICKC_PUPD            GPIO_PuPd_UP
#define JOYSTICKC_EXTI_PORTSOURCE EXTI_PortSourceGPIOB
#define JOYSTICKC_EXTI_PINSOURCE  GPIO_PinSource15
#define JOYSTICKC_EXTI_LINE       EXTI_Line15
#define JOYSTICKC_EXTI_IRQN       EXTI15_10_IRQn

#define JOYSTICKD_PIN             GPIO_Pin_6
#define JOYSTICKD_PORT            GPIOC
#define JOYSTICKD_BUS             RCC_AHB1Periph_GPIOC
#define JOYSTICKD_PUPD            GPIO_PuPd_UP
#define JOYSTICKD_EXTI_PORTSOURCE EXTI_PortSourceGPIOC
#define JOYSTICKD_EXTI_PINSOURCE  GPIO_PinSource6
#define JOYSTICKD_EXTI_LINE       EXTI_Line6
#define JOYSTICKD_EXTI_IRQN       EXTI9_5_IRQn

#define JOYSTICKCTR_PIN             GPIO_Pin_7
#define JOYSTICKCTR_PORT            GPIOC
#define JOYSTICKCTR_BUS             RCC_AHB1Periph_GPIOC
#define JOYSTICKCTR_PUPD            GPIO_PuPd_UP
#define JOYSTICKCTR_EXTI_PORTSOURCE EXTI_PortSourceGPIOC
#define JOYSTICKCTR_EXTI_PINSOURCE  GPIO_PinSource7
#define JOYSTICKCTR_EXTI_LINE       EXTI_Line7
#define JOYSTICKCTR_EXTI_IRQN       EXTI9_5_IRQn

typedef enum _MCU_SPEED {
  _72MHZ,
  _84MHZ,
  _96MHZ,
  _120MHZ,
  _144MHZ,
  _168MHZ,
  _192MHZ,
} MCU_SPEED;

void BSP_LED_Init(Led_TypeDef Led);
void BSP_LEDs_Init(void);
void BSP_LED_On(Led_TypeDef Led);
void BSP_LED_Off(Led_TypeDef Led);
void BSP_LED_Toggle(Led_TypeDef Led);

void BSP_Button_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
void BSP_Buttons_Init(ButtonMode_TypeDef ButtonMode);
uint32_t BSP_Button_GetState(Button_TypeDef Button);

uint8_t BSP_SetSysClock(MCU_SPEED speed);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4_DISCOVERY_H */
