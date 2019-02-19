/*
 * Toggle an active buzzer connected to GPIO.
 *
 * Author: Leonardo Lai
 * */

#include "stm32f4xx.h"
#include "buzzer.h"

#define AHB_PERIPH	RCC_AHB1Periph_GPIOE
#define PERIPH		GPIOE
#define PIN			GPIO_Pin_4


GPIO_InitTypeDef GPIO_InitStructure;


/* Initialize the buzzer */
void buzzer_init()
{
	RCC_AHB1PeriphClockCmd(AHB_PERIPH, ENABLE);
	GPIO_InitStructure.GPIO_Pin = PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(PERIPH, &GPIO_InitStructure);
}


/* Silence the buzzer */
void buzzer_mute()
{
	GPIO_ResetBits(PERIPH, PIN);
}


/* Trigger the buzzer */
void buzzer_unmute()
{
	GPIO_SetBits(PERIPH, PIN);
}

