#include "stm32f10x.h"   // Device header (register definitions)

/* ================= DELAY ================= */
// crude delay (not accurate, but enough for LCD init timing)
void delay(int t) {
    for(int i = 0; i < t * 1000; i++);
}

/* ================= GPIO CONTROL MACROS ================= */
// Control pins connected to GPIOA

#define CS_LOW   GPIOA->BRR  = (1<<4)   // Pull CS LOW (select LCD)
#define CS_HIGH  GPIOA->BSRR = (1<<4)   // Pull CS HIGH (deselect LCD)

#define DC_LOW   GPIOA->BRR  = (1<<3)   // Command mode
#define DC_HIGH  GPIOA->BSRR = (1<<3)   // Data mode

#define RST_LOW  GPIOA->BRR  = (1<<2)   // Reset LCD
#define RST_HIGH GPIOA->BSRR = (1<<2)

/* ================= SPI INIT ================= */
void SPI1_Init() {

    RCC->APB2ENR |= (1<<2);   // Enable clock for GPIOA
    RCC->APB2ENR |= (1<<12);  // Enable clock for SPI1

    /* Configure PA5 (SCK) and PA7 (MOSI) as Alternate Function Push-Pull */
    GPIOA->CRL &= ~(0xFF << 20);   // Clear bits for PA5 & PA7
    GPIOA->CRL |=  (0xBB << 20);   // Set AF output, 50 MHz

    /* Configure PA4 (CS), PA3 (DC), PA2 (RST) as Output */
    GPIOA->CRL &= ~(0xFFF << 8);   // Clear bits
    GPIOA->CRL |=  (0x333 << 8);   // General purpose output

    /* SPI configuration */
    SPI1->CR1 = 0;              // Clear control register

    SPI1->CR1 |= (1<<2);        // Set as MASTER mode
    SPI1->CR1 |= (0b010 << 3);  // Baud rate = PCLK / 8 (adjust later for speed)
    SPI1->CR1 |= (1<<9);        // Software slave management (SSM)
    SPI1->CR1 |= (1<<8);        // Internal slave select (SSI)

    SPI1->CR1 |= (1<<6);        // Enable SPI
}

/* ================= SPI WRITE ================= */
void SPI_Write(uint8_t data) {

    while(!(SPI1->SR & (1<<1))); // Wait until TX buffer empty (TXE)
    SPI1->DR = data;             // Send data

    while(SPI1->SR & (1<<7));    // Wait until SPI not busy (BSY)
}

/* ================= LCD COMMAND ================= */
void LCD_Command(uint8_t cmd) {
    DC_LOW;      // Command mode
    CS_LOW;      // Select LCD

    SPI_Write(cmd);  // Send command byte

    CS_HIGH;     // Deselect LCD
}

/* ================= LCD DATA ================= */
void LCD_Data(uint8_t data) {
    DC_HIGH;     // Data mode
    CS_LOW;

    SPI_Write(data);  // Send data byte

    CS_HIGH;
}

/* ================= LCD INIT ================= */
void LCD_Init() {

    /* Hardware reset */
    RST_LOW;
    delay(100);
    RST_HIGH;
    delay(100);

    LCD_Command(0x01);   // Software reset
    delay(100);

    LCD_Command(0x11);   // Sleep OUT
    delay(120);

    LCD_Command(0x3A);   // Pixel format set
    LCD_Data(0x66);      // 18-bit color (R,G,B each 6-bit)

    LCD_Command(0x36);   // Memory Access Control
    LCD_Data(0x48);      // Orientation (try changing if rotated)

    LCD_Command(0x29);   // Display ON
}

/* ================= SET DRAW AREA ================= */
void LCD_SetAddr(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {

    LCD_Command(0x2A);  // Column address set
    LCD_Data(x0 >> 8);  // High byte of x0
    LCD_Data(x0 & 0xFF);// Low byte
    LCD_Data(x1 >> 8);  
    LCD_Data(x1 & 0xFF);

    LCD_Command(0x2B);  // Row address set
    LCD_Data(y0 >> 8);
    LCD_Data(y0 & 0xFF);
    LCD_Data(y1 >> 8);
    LCD_Data(y1 & 0xFF);

    LCD_Command(0x2C);  // Memory write (start sending pixels)
}

/* ================= FILL SCREEN ================= */
void LCD_Fill(uint8_t r, uint8_t g, uint8_t b) {

    LCD_SetAddr(0, 0, 319, 479); // Full screen (320x480)

    DC_HIGH;   // Data mode
    CS_LOW;    // Keep CS LOW for continuous transfer (important for speed)

    for(int i = 0; i < 320 * 480; i++) {
        SPI_Write(r);  // Red
        SPI_Write(g);  // Green
        SPI_Write(b);  // Blue
    }

    CS_HIGH;
}

/* ================= MAIN ================= */
int main() {

    SPI1_Init();   // Initialize SPI + GPIO
    LCD_Init();    // Initialize LCD

    LCD_Fill(0xFF, 0x00, 0x00);  // Fill screen RED

    while(1);     // Infinite loop
}
