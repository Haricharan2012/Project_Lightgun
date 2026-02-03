#include "stm32f10x.h"
#include "auto.h"
void Delay(int val);

int signal =0 ; //used to decide LED behaviour

int main(void)
{

	/*
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
	
		//set PORTA pin13 in output_mode/push-pull
		GPIOC->CRH |=(0x2 << 20);
	
    //set pull up for pin0
	  //GPIOA->ODR |=(1<<0);   //actual role of pull up here?
		
     */
		
		 init_GPIO(portA,0,IN,IN_pp);
		 init_GPIO(portC,13,OUT50,OUT_GP_PP);
		 init_GPIO (portA,12,OUT50,OUT_GP_PP);  
	
    // GPIOC->ODR |=(1 << 13);
	 
	 
		 __disable_irq();  //disable interrupts
		 AFIO->EXTICR[0]=0x0000; //activate pin Map EXTI line 0 to PA0
		 EXTI->IMR |= 1; //allows to trigger EXTI0 interrupt
		 EXTI->RTSR |= 1; //select rising edge for triggering interrupt (low->high =interrupt triggered)
		 NVIC_EnableIRQ(EXTI0_IRQn); // helps the interrupt reach the cpu through NVIC
		 __enable_irq();  //enables the interrupts
	
		while(1)
		{
			//if((GPIOA->IDR & (1<<0)))  //if button pressed   //alternate ways? //logic inversion due to pull up being set
			//if((read_GPIO(portA,0)==1))
			write_GPIO(portA,12,signal); //set PA12 to same value as signal 
			if(signal)
				{
					Delay(10);
					//	GPIOC->ODR ^= (1 << 13);   //toggle pin13 to blink  //13th bit is 1 all others 0
					toggle_GPIO(portC,13);
 					Delay(10);
				}
				
		   else
				{
					//	GPIOC->ODR |=(1 << 13);  // HIGH //1=OFF //13th bit is 1 all others 0 //shouldn't toggle flip btw states
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
			
			 
			void EXTI0_IRQHandler()
			{
					EXTI->PR |= 1; // clear pending interrupt flag to prevent retriggering 
				
				if(signal)    //on button press toggle state
				{
					(signal=0);
				}
				else
				{
					(signal=1);
				}
			}
			
			
					 
					
					
			
	
	