#include "adc_drive.h"       // Include the ADC driver header file.

/*
PA0 -> ADC12_IN0             // PA0 corresponds to ADC channel 0.
PA1 -> ADC12_IN1             // PA1 corresponds to ADC channel 1.
PA2 -> ADC12_IN2             // PA2 corresponds to ADC channel 2.
PA3 -> ADC12_IN3             // PA3 corresponds to ADC channel 3.
PA4 -> ADC12_IN4             // PA4 corresponds to ADC channel 4.
PA5 -> ADC12_IN5             // PA5 corresponds to ADC channel 5.
PA6 -> ADC12_IN6             // PA6 corresponds to ADC channel 6.
PA7 -> ADC12_IN7             // PA7 corresponds to ADC channel 7.

PB0 -> ADC12_IN8             // PB0 corresponds to ADC channel 8.
PB1 -> ADC12_IN9             // PB1 corresponds to ADC channel 9.

PC0 -> ADC12_IN10            // PC0 corresponds to ADC channel 10.
PC1 -> ADC12_IN11            // PC1 corresponds to ADC channel 11.
PC2 -> ADC12_IN12            // PC2 corresponds to ADC channel 12.
PC3 -> ADC12_IN13            // PC3 corresponds to ADC channel 13.
PC4 -> ADC12_IN14            // PC4 corresponds to ADC channel 14.
PC5 -> ADC12_IN15            // PC5 corresponds to ADC channel 15.

ADC12_IN16 input channel which is used to convert the sensor output
voltage into a digital value.
*/

// Initializing the ADC for the STM32F1
char adc_init(char adc, short port, short pin)       // Function to initialize a particular ADC channel.
{
    char channel;                                    // Stores the ADC channel number.
    char result = 0;                                 // Initially assume that the given port/pin is invalid.

    if(port == PA)                                  // Check whether the selected port is Port A.
    {
        if(pin < 8)                                 // Check whether the pin is between PA0 and PA7.
        {
            result = 1;                             // Mark the port/pin combination as valid.
            channel = pin;                          // For PA, ADC channel number is equal to the pin number.
        }
    }

    else if (port == PB)                            // If it wasn't Port A, check whether it is Port B.
    {
        if(pin < 2)                                 // Only PB0 and PB1 are ADC inputs.
        {
            result = 1;                             // Mark the port/pin combination as valid.
            channel = 8 + pin;                      // PB0 -> channel 8, PB1 -> channel 9.
        }
    }

    else if (port == PC)                            // If not A/B, check whether it is Port C.
    {
        if(pin < 6)                                 // Only PC0 through PC5 are ADC inputs.
        {
            result = 1;                             // Mark the port/pin combination as valid.
            channel = 10 + pin;                     // PC0 -> channel 10, PC5 -> channel 15.
        }
    }

    if(result)                                      // Continue only if the port/pin was valid.
    {
        init_GP(port,pin,IN,I_AN);                  // Configure the GPIO pin as an analog input.

        if(adc == adc1)                             // Check whether ADC1 was requested.
        {
            RCC->APB2ENR |= 0x201;                  // Enable the required clocks for GPIO/ADC1.

            ADC1->CR2 = 0;                          // Clear/reset ADC1 control register 2.

            ADC1->SQR3 = channel;                   // Select the ADC channel for the first conversion.

            ADC1->CR2 |= 1;                         // Set ADON bit: turn ADC1 ON.

            DelayMs(100);                           // Wait 100 ms for the ADC to stabilize.

            ADC1->CR2 |= 1;                         // Set ADON again; on STM32F1 this starts conversion.

            ADC1->CR2 |= 2;                         // Set the SWSTART bit to start software conversion.
        }

        else if(adc == adc2)                        // Otherwise, check whether ADC2 was requested.
        {
            RCC->APB2ENR |= 0x401;                  // Enable the required clocks for GPIO/ADC2.

            ADC2->CR2 = 0;                          // Clear/reset ADC2 control register 2.

            ADC2->SQR3 = channel;                   // Select the ADC channel for the first conversion.

            ADC2->CR2 |= 1;                         // Set ADON bit: turn ADC2 ON.

            DelayMs(100);                           // Wait 100 ms for the ADC to stabilize.

            ADC2->CR2 |= 1;                         // Set ADON again; on STM32F1 this starts conversion.

            ADC2->CR2 |= 2;                         // Set SWSTART bit to start software conversion.
        }
    }

    return result;                                  // Return 1 if valid, otherwise return 0.
}


// Reading the flag that says the data is ready
char adc_check(char adc, short port, short pin)      // Check whether ADC conversion is complete.
{
    char check = 0;                                 // Initially assume conversion is not complete.

    if(adc == adc1)                                 // Check whether ADC1 is being used.
    {
        if(ADC1->SR & 2)                            // Check ADC1 status register's EOC bit.
        {
            check = 1;                              // EOC = 1 means conversion is complete.
        }
    }

    else if(adc == adc2)                            // Otherwise, check whether ADC2 is being used.
    {
        if(ADC2->SR & 2)                            // Check ADC2 status register's EOC bit.
        {
            check = 1;                              // EOC = 1 means conversion is complete.
        }
    }

    return check;                                   // Return 1 if conversion is complete, otherwise 0.
}


// Reading the ADC value
int adc_rx(char adc, short port, short pin)          // Read the converted ADC value.
{
    int result = 0;                                 // Variable that will store the final result.
    int data = 0;                                   // Variable that will store the raw ADC value.

    if(adc == adc1)                                 // Check whether ADC1 is being used.
    {
        data = ADC1->DR;                            // Read the converted ADC value from ADC1 data register.
    }

    else if(adc == adc2)                            // Otherwise, check whether ADC2 is being used.
    {
        data = ADC2->DR;                            // Read the converted ADC value from ADC2 data register.
    }

    result = (data * 1000) / 0xfff;                 // Convert 12-bit ADC value (0-4095) into 0-1000.

    return result;                                  // Return the scaled ADC value.
}

