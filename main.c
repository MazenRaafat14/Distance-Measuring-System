#include "ultrasonic.h"
#include "lcd.h"
#include "gpio.h"
#include <util/delay.h>
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>


int main()
{
	SREG|=(1<<7); /*Enabling the I-bit (Global Interrupt Enable)*/

	/*
	  Make Buzzer and LEDS Output pins
	 */

	GPIO_setupPinDirection(PORTC_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PIN2_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PIN5_ID,PIN_OUTPUT);



	PORTC&=0b11011000; //LEDS and Buzzer Initially OFF



	uint16 distance=0;

/*
 Initialize the Ultrasonic and the LCD
 */
	Ultrasonic_init();
	LCD_init();


	while(1)
	{
		distance = Ultrasonic_readDistance();

/*
 Showing the distance on the LCD
 */
		LCD_displayStringRowColumn(0,0, "Distance= ");
		LCD_intgerToString(distance);
		LCD_displayString("cm");
		LCD_displayCharacter(' ');
		if(distance <= 5)
		{

			GPIO_writePin(PORTC_ID,PIN0_ID,LOGIC_HIGH);
			GPIO_writePin(PORTC_ID,PIN1_ID,LOGIC_HIGH);
			GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_HIGH);
			GPIO_writePin(PORTC_ID,PIN5_ID,LOGIC_HIGH);

			_delay_ms(250);
			GPIO_writePin(PORTC_ID,PIN0_ID,LOGIC_LOW);
			GPIO_writePin(PORTC_ID,PIN1_ID,LOGIC_LOW);
			GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_LOW);
			GPIO_writePin(PORTC_ID,PIN5_ID,LOGIC_LOW);


		}
		else
		{
			PORTC&=0b11011000;
		}



	}


}
