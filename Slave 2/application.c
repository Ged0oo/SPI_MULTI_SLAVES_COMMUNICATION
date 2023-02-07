/* 
 * File:   ecu_seven_segment.c
 * Author: Mohamed_Nagy
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 27, 2022, 8:41 PM
 */


#include "application.h"
#include "MCAL_Layer/SPI/hal_spi.h"

/* Slave 2 Configrations */
Std_ReturnType ret = E_NOT_OK;
uint8 retValue;

led_t led_1 =
{
    .led_status = LED_OFF,
    .pin = GPIO_PIN0,
    .port_name = PORTD_INDEX
};

pin_config_t SPI_SS =
{
    .port = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

SPI_Config SPI_Obj =
{
    .spi_mode = SPI_SLAVE_SS_DISABLE,
    .spi_config.ClockPolarity = SPI_IDLE_STATE_LOW_LEVEL,
    .spi_config.ClockSelect = SPI_TRANSMIT_IDLE_TO_ACTIVE,
    .spi_config.SampleSelect = SPI_DATA_SAMPLE_MIDDLE
};

int main() 
{ 
    ret = SPI_Init(&SPI_Obj);
    ret = led_initialize(&led_1);
    ret = gpio_pin_intialize(&SPI_SS);
    
    while(1)
    {  
        ret = SPI_Read_Byte(&SPI_Obj , &retValue);
        if('b' == retValue)
        {
            ret = led_turn_on(&led_1);
        }
        else if('d' == retValue)
        {
            ret = led_turn_off(&led_1);
        }
    }
    return (EXIT_SUCCESS);
}
