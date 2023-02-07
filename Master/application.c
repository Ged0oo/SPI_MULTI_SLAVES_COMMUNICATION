/* 
 * File:   ecu_seven_segment.c
 * Author: Mohamed_Nagy
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 27, 2022, 8:41 PM
 */


#include "application.h"
#include "MCAL_Layer/SPI/hal_spi.h"

/* Master Configrations */
Std_ReturnType ret = E_NOT_OK;

pin_config_t SPI_SS2 =
{
    .port = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

pin_config_t SPI_SS1 =
{
    .port = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

SPI_Config SPI_Obj =
{
    .spi_mode = SPI_MASTER_FOSC_DIV4,
    .spi_config.ClockPolarity = SPI_IDLE_STATE_LOW_LEVEL,
    .spi_config.ClockSelect = SPI_TRANSMIT_IDLE_TO_ACTIVE,
    .spi_config.SampleSelect = SPI_DATA_SAMPLE_MIDDLE
};

int main() 
{ 
    ret = SPI_Init(&SPI_Obj);
    ret = gpio_pin_intialize(&SPI_SS1);
    ret = gpio_pin_intialize(&SPI_SS2);
    while(1)
    {  
        ret = gpio_pin_write_logic(&SPI_SS1 , GPIO_LOW);
        ret = SPI_Send_Byte(&SPI_Obj, 'a');
        __delay_ms(250);
        ret = SPI_Send_Byte(&SPI_Obj, 'c');
        __delay_ms(250);
        ret = gpio_pin_write_logic(&SPI_SS1 , GPIO_HIGH);        
        ret = gpio_pin_write_logic(&SPI_SS2 , GPIO_LOW);
        ret = SPI_Send_Byte(&SPI_Obj, 'b');
        __delay_ms(250);
        ret = SPI_Send_Byte(&SPI_Obj, 'd');
        ret = gpio_pin_write_logic(&SPI_SS2 , GPIO_HIGH);
        __delay_ms(250);
    }
    return (EXIT_SUCCESS);
}
