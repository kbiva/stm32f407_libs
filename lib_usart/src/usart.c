/*
 *  usart.c
 *
 *  Author: Kestutis Bivainis
 *
 *  USART2 support for printf.
 *
 *  Tested with:
 *  Open407V-D board from WaveShare
 *  STM32F4 Discovery board
 *
 */

#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "usart.h"

struct __FILE {int handle;};
FILE __stdout;
FILE __stdin;

void USART1_Init(uint32_t baud) {

  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_AHB1PeriphClockCmd(USART1_PIN_TX_Bus, ENABLE);
  RCC_AHB1PeriphClockCmd(USART1_PIN_RX_Bus, ENABLE);

  GPIO_InitStructure.GPIO_Pin = USART1_PIN_TX|USART1_PIN_RX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(USART1_PIN_TX_Port, &GPIO_InitStructure);

  GPIO_PinAFConfig(USART1_PIN_TX_Port, USART1_PIN_TX_Pinsource, GPIO_AF_USART1);
  GPIO_PinAFConfig(USART1_PIN_RX_Port, USART1_PIN_RX_Pinsource, GPIO_AF_USART1);

  USART_InitStructure.USART_BaudRate = baud;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

  USART_Init(USART1, &USART_InitStructure);

  //Enable USART1
  USART_ClearFlag(USART1,USART_FLAG_TC);
  USART_Cmd(USART1, ENABLE);
}

void USART2_Init(uint32_t baud) {

  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_AHB1PeriphClockCmd(USART2_PIN_TX_Bus, ENABLE);
  RCC_AHB1PeriphClockCmd(USART2_PIN_RX_Bus, ENABLE);

  GPIO_InitStructure.GPIO_Pin = USART2_PIN_TX|USART2_PIN_RX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(USART1_PIN_TX_Port, &GPIO_InitStructure);

  GPIO_PinAFConfig(USART2_PIN_TX_Port, USART2_PIN_TX_Pinsource, GPIO_AF_USART2);
  GPIO_PinAFConfig(USART2_PIN_RX_Port, USART2_PIN_RX_Pinsource, GPIO_AF_USART2);

  USART_InitStructure.USART_BaudRate = baud;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

  USART_Init(USART2, &USART_InitStructure);

  //Enable USART2
  USART_ClearFlag(USART2,USART_FLAG_TC);
  USART_Cmd(USART2, ENABLE);
}

int fputc(int ch, FILE *f) {

  USART2->DR = (ch & (uint16_t)0x01FF);
  while (!(USART2->SR & USART_FLAG_TXE)){};
  return ch;
}

int fgetc(FILE *f) {

  while (!(USART2->SR & USART_FLAG_RXNE)){};
  return ((int)(USART2->DR & 0xFF));
}
