#include "stm32f10x.h"                  // Device header

int main(void)
{
	RCC->APB2ENR |=0x10; //0b10000
	GPIOC->CRH &=0XFF0FFFFF;
	GPIOC->CRH |=0X00300000;
}
