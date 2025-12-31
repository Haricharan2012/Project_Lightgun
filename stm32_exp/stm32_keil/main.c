#include "stm32f10x.h"                  // Device header

int main(void)
{
	RCC->APB2ENR |=0x0C; //0b10000
	
}
