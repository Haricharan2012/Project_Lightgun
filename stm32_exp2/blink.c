/* #include "stm32f10x.h"

void delay(int val);

int main(void)
{
    RCC->APB2ENR |= (1 << 4);      // GPIOC clock enable

    GPIOC->CRH &= ~(0xF << 20);   // Clear PC13 config
    GPIOC->CRH |=  (0x3 << 20);   // Output push-pull

	
  while (1)
    {
        GPIOC->ODR &= ~(1 << 13); // LED ON (PC13 = 0)
        delay(10);

        GPIOC->ODR |=  (1 << 13); // LED OFF (PC13 = 1)
        delay(10);
    } 
		
}

void delay(int val)
{
    volatile int i;
    while (val--)
    {
        for (i = 0; i < 100000; i++);
    }
} 
*/



