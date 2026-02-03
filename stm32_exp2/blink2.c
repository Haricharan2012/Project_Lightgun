/*------------------------------------------------------------------

#include "stm32f10x.h"

void Delay(int val);

int main(void)
{
		//Enable Clock for PORTA 
		RCC->APB2ENR |=(1<<2);
	
		//Enable clock for PORTC
		RCC->APB2ENR |=(1<<4);
	
		//Reset GPIOA PORTA 
		GPIOA->CRL &=~(0xF << 0);
	
		//Set PORTA Pin0 in input with pull-up/pull down
		GPIOA->CRL |=(0x8 << 0);
	
		//Reset GPIO PORTC  
		GPIOC->CRH &=~(0xF << 20);
	
		//set PORTC pin13 in output_mode/push-pull
		GPIOC->CRH |=(0x2 << 20);
	
    //set pull up for pin0
	  //GPIOA->ODR |=(1<<0);   //actual role of pull up here?
	
    GPIOC->ODR |=(1 << 13);
	
	 
	
		while(1)
		{
				if((GPIOA->IDR & (1<<0)))  //if button pressed   //alternate ways? //logic inversion due to pull up being set
				{
					Delay(10);
 					GPIOC->ODR ^= (1 << 13);   //toggle pin13 to blink  //13th bit is 1 all others 0
 					Delay(10);
				}
				
		   else
				{
					GPIOC->ODR |=(1 << 13);  // HIGH //1=OFF //13th bit is 1 all others 0 //shouldn't toggle flip btw states
				}  
				
			} 
}
		void Delay(int time)
			{
				int t;
				for(;time>0;time--)
				 {
					 for(t=0;t<100000;t++);
				 }
			 }
			
					 
-----------------------------------------------------------------------------*/

