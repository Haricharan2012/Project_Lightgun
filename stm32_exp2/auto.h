#define RCC_APB2ENR  (*((volatile unsigned long *) 0x40021018))
#define GPIO_A        (*((volatile unsigned long *) 0x40010800))  //by using this macro we access the base address of portA
#define GPIO_B        (*((volatile unsigned long *) 0x40010C00))
#define GPIO_C        (*((volatile unsigned long *) 0x40011000))

//defining ports

#define portA 1
#define portB 2
#define portC 3

//defining directions 

#define IN 0
#define OUT10 1
#define OUT2  2
#define OUT50 3

//defining direction options for input

#define IN_AN 0
#define IN_FI 1
#define IN_pp 2

//defining direction options for output

#define OUT_GP_PP 0
#define OUT_GP_OP 1
#define OUT_AF_pp 2
#define OUT_AF_OP 3

//define status

#define LOW 0
#define HIGH 1

//port= A,B or C ,pin = pin number ,direc = input or output , options = input mode options or output mode options
void init_GPIO(unsigned short port,unsigned short pin,unsigned short direc,unsigned short opt); 
int read_GPIO(unsigned short port,unsigned short pin);
void write_GPIO(unsigned short port,unsigned short pin, unsigned short state);
void toggle_GPIO(unsigned short port,unsigned short pin);

