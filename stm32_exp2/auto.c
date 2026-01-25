#include "auto.h"

void init_GPIO(unsigned short port,unsigned short pin,unsigned short direc,unsigned short opt)
{
		volatile unsigned long * CR; // pointer to configuration register
	  unsigned short tPIN=pin;   //temp pin
	  unsigned short offset =  0x00;  //to define if we are in CRH or CRL //default =CRL
	
	
		if(pin > 7)
		{
				tPIN = tPIN -8;  //subtracting 8 to get correct index
				offset = 0x01; //next step in memory  //making offset to point to CRH 
		}
		
		if(port==1)
		{
					RCC_APB2ENR |=(1<<2);  //enabling portA //bit 2=IOPEAN
					CR = (volatile unsigned long *) (&GPIO_A + offset);  //setup CR register //assign CR to CRL or CRH depending on offset  //points CR to portA
		}
		
		else if(port==2)
		{
					RCC_APB2ENR |=(1<<3); //enabling portB  //bit 3=IOPBEN
					CR =(volatile unsigned long *) (&GPIO_B + offset); //points CR to portB
		}
		
		else if(port==3)
		{
					RCC_APB2ENR |=(1<<4);//enabling portC  //bit 4= IOPCEN
			    CR =(volatile unsigned long *) (&GPIO_C + offset); //points CR to portC
		}
		
		
		*CR &= ~(0xf<<(tPIN)*4); //reset the target pin //clears 4 bits ,each pin uses 4bits in CRL/CRH  
	  *CR |= ((direc<<(tPIN*4)) | (opt<<(tPIN*4+2)));  //set up direction and option of the pin 
		
	}
		
	int read_GPIO(unsigned short port,unsigned short pin)
	{
		volatile unsigned long * IDR;
		unsigned long offset = 0x02; //1 step from CRH 
		int state;
		
		if(port == 1)
		{
				IDR=(volatile unsigned long *) (&GPIO_A + offset);
		}
		else if(port ==2)
		{
				IDR=(volatile unsigned long *) (&GPIO_B + offset);
		}
		else
		{
				IDR=(volatile unsigned long *) (&GPIO_C + offset);
	  }
		
		state= ((*IDR & (1<<pin)>>pin)); // remove everything else to only get pin direction
		return state;
	}
	
	void write_GPIO(unsigned short port,unsigned short pin,unsigned short state)
	{
		volatile unsigned long *ODR;
		unsigned long offset = 0x03;//1 step from IDR
		
		if(port == 1)
		{
				ODR=(volatile unsigned long *) (&GPIO_A +	offset);
		}
		if(port == 2)
		{
				ODR=(volatile unsigned long *) (&GPIO_B + offset);
		}
		if(port == 3)
		{
				ODR=(volatile unsigned long *) (&GPIO_C + offset);
		}
		if(state == HIGH)
		{
				*ODR |= (state<<pin); //1 left shift pin number //making pin high
			
		}
		else
		{
				*ODR &= ~(1<<pin); //state is low //clears the pin //reverse of high
		}
	}
	
	void toggle_GPIO(unsigned short port,unsigned short pin)
	{
		if(read_GPIO(port,pin))
		{
				write_GPIO(port,pin,0); //call write pin func & pass state LOW
		}
		else
		{
				write_GPIO(port,pin,1); //call write pin func & pass state HIGH
		}
			
	}
	
		