/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>

/* LCD specific */
#define ROW_0 0 /* LCD row 0 */
#define ROW_1 1 /* LCD row 1 */
#define COLUMN_0 0 /* LCD column 0 */
#define NUM_CHARACTERS 16 /* Number of characters on LCD */
/* For clearing a row of the LCD*/
#define CLEAR_ROW_STR " "
/* Button 1 only string for row 0 of the LCD */
#define BUTTON_1_STR "Button1 "
/* Button 2 only string for row 0 of the LCD */
#define BUTTON_2_STR " Button2"
/* Button 1 and 2 string for row 0 of the LCD */
#define BUTTON_1_2_STR "Button1 Button2"
/* Default string for button row of the LCD */
#define DEFAULT_ROW_0_STR "Touch Buttons "
/* Default string for slider row of the LCD */
#define DEFAULT_ROW_1_STR "Touch The Slider"

/* LED specific */
#define LED_ON 1 /* For setting LED pin high */
#define LED_OFF 0 /* For setting LED pin low */

/* CapSense specific */
#define SLIDER_RESOLUTION 80
//extern const uint8 LCD_Char_1_customFonts[];
void UpdateButtonState(uint8 slot_1, uint8 slot_2);
void UpdateSliderPosition(uint8 value);

void main()
{
	uint8 pos; /* Slider Position */
	uint8 stateB_1; /* Button1 State */
	uint8 stateB_2; /* Button2 State */
	
	/* Enable global interrupts */
	CYGlobalIntEnable; 
	
	/* LCD Initialization */
	LCD_Char_1_Start();
	
	/* For Bargraph display on LCD */
	// LCD_Char_1_LoadCustomFonts(LCD_Char_1_customFonts);
	/* Start capsense and initialize baselines and enable scan */
	CapSense_Start();
	CapSense_InitializeAllBaselines();
	CapSense_ScanEnabledWidgets();
	
	while(1)
	{
		/* If scanning is completed update the baseline count and check if sensor is active */
		while(CapSense_IsBusy());
		
		/* Update baseline for all the sensors */
		CapSense_UpdateEnabledBaselines();
		CapSense_ScanEnabledWidgets();
		
		PWM_1_Start();
		
		/* Test if button widget is active */
		stateB_1 = CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN);
		stateB_2 = CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN);
		pos =(uint8)CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);
		
		/* Update LCD and LED's with current Button and Linear Slider states */
		UpdateButtonState(stateB_1, stateB_2);
		UpdateSliderPosition(pos);
		//PWM_1_WriteCount(0);
		PWM_1_WriteCompare(80-pos);
	}
}
void UpdateButtonState(uint8 slot_1, uint8 slot_2)
{
	LCD_Char_1_Position(ROW_0,COLUMN_0);
	/* Check the state of the buttons and update the LCD and LEDs */
	if (slot_1 && slot_2)
	{
		/* Display both Button strings on LCD if both button slots are active */
		LCD_Char_1_PrintString(BUTTON_1_2_STR);
		/* Both LED's are on in this state */
		LED_1_Write(LED_ON);
		//LED_2_Write(LED_ON);
	}
	else if (slot_1 || slot_2)
	{
		if (slot_1)
		{
			/* Display Button 1 state on LCD and LED1 */
			LCD_Char_1_PrintString(BUTTON_1_STR);
			LED_1_Write(LED_ON);
			/* Button 2 is not active */
			//LED_2_Write(LED_OFF);
		}
		if (slot_2)
		{
			/* Display Button 2 state on LCD and LED2 */
			LCD_Char_1_PrintString(BUTTON_2_STR);
			//LED_2_Write(LED_ON);
			/* Button 1 is not active */
			LED_1_Write(LED_OFF);
		}
	}
		else
		{
			/* Display default string on LCD and set LED's to off */
			LCD_Char_1_PrintString(DEFAULT_ROW_0_STR);
			/* Set both LED's off in this state */
			LED_1_Write(LED_OFF);
			//LED_2_Write(LED_OFF);
		}
}
void UpdateSliderPosition(uint8 value)
{
	/* The slider position is 0xFF if there is no finger present on the slider */
	if (value > SLIDER_RESOLUTION)
	{
		/* Clear old slider position (2nd row of LCD) */
		LCD_Char_1_Position(ROW_1, COLUMN_0);
		LCD_Char_1_PrintString(DEFAULT_ROW_1_STR);
	}
	else
	{
		/* Update the bargraph with the current finger position */
		LCD_Char_1_DrawHorizontalBG(ROW_1, COLUMN_0, NUM_CHARACTERS, value +1);
	}
}
/* [] END OF FILE */
