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
#define COLUMN_9 9 /* LCD column 9 */
#define COLUMN_10 10 /* LCD column 10 */
#define COLUMN_11 11 /* LCD column 11 */
#define COLUMN_12 12 /* LCD column 12 */
#define COLUMN_13 13 /* LCD column 13 */
#define COLUMN_14 14 /* LCD column 14 */
/* For clearing Tens and Hundreds place */
#define CLEAR_TENS_HUNDREDS " "
/* For clearing Hundreds place */
#define CLEAR_HUNDREDS " "

int show = 0;
uint16 voltageRawCount;	
uint16 temp = 0;
uint16 temp_set = 27;
uint16 cold = 9999;

uint8 stateB_1; 
uint8 stateB_2;

void UpdateDisplay(uint16 voltageRawCount, int row);
void UpdateButtonState(uint8 slot_1, uint8 slot_2);

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
* The main function initializes both the ADC and LCD, starts and waits for an
* ADC conversion, then it displays the raw counts to the LCD.
*
* Parameters:
* void
*
* Return:
* void
*
*******************************************************************************/

void main()
{
	CYGlobalIntEnable; /* Enable global interrupts */
	
	ADC_DelSig_1_Start();/* Configure and power up ADC */
	LCD_Char_1_Start(); /* Initialize and clear the LCD */
	
	/* Move the cursor to Row 0 Column 0 */
	LCD_Char_1_Position(ROW_0,COLUMN_0); 
	/* Print Label for the pot voltage raw count */
	LCD_Char_1_PrintString("TEMP NOW:    C");
	
	LCD_Char_1_Position(ROW_1,COLUMN_0);
	LCD_Char_1_PrintString("TEMP SET:    C");
	
	ADC_DelSig_1_StartConvert(); /* Force ADC to initiate a conversion */
	
	/* Start capsense and initialize baselines and enable scan */
	CapSense_Start();
	CapSense_InitializeAllBaselines();
	CapSense_ScanEnabledWidgets();

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
	//Start the pwm;
	PWM_1_Start();
    for(;;)
    {
		/* If scanning is completed update the baseline count and check if sensor is active */
		while(CapSense_IsBusy());
		
		/* Update baseline for all the sensors */
		CapSense_UpdateEnabledBaselines();
		CapSense_ScanEnabledWidgets();
		
		/* Test if button widget is active */
		stateB_1 = CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN);
		stateB_2 = CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN);
	
        /* Wait for end of conversion */
		ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT);
		/* Get converted result */
		voltageRawCount = ADC_DelSig_1_GetResult16();
		//Change voltageRawCount to Temperature;
		temp = voltageRawCount / 3.870 * 0.1017 + 0.5;
		cold = (9999 - (temp > temp_set ? temp - temp_set : 0) * 50);
		if(cold < 1000)
			cold = 1000;
		if(cold > 9999)
			cold = 9999;
		//Change the pwm;
		PWM_1_WriteCompare(cold);
		/* Set range limit */
		if (temp > 0x7FFF)
		{
			temp = 0;
		}
		else
		{
		/* Continue on */
		}
		if(show < 10)
		{
			show++;
		}
		else
		{
			show = 0;
			UpdateDisplay(temp, 0); /* Print result on LCD */
			UpdateButtonState(stateB_1, stateB_2);
		}
    }
}

/*******************************************************************************
* Function Name: UpdateDisplay
********************************************************************************
*
* Summary:
* Print voltage raw count result to the LCD. Clears some characters if
* necessary.
*
* Parameters:
* voltageRawCount: The voltage raw counts being received from the ADC
*
* Return:
* void
*
*******************************************************************************/
void UpdateDisplay (uint16 voltageRawCount, int row)
{
	/* Move the cursor to Row 0 Column 0 */
	LCD_Char_1_Position(ROW_0,COLUMN_0); 
	/* Print Label for the pot voltage raw count */
	LCD_Char_1_PrintString("TEMP NOW:");
	
	LCD_Char_1_Position(ROW_0,COLUMN_13); 
	LCD_Char_1_PrintString("C");
	
	LCD_Char_1_Position(ROW_1,COLUMN_0);
	LCD_Char_1_PrintString("TEMP SET:    C");

	/* Move the cursor to Row 0, Column 10 */
	LCD_Char_1_Position(row,COLUMN_10);
	/* Print the result */
	LCD_Char_1_PrintNumber(voltageRawCount); 
	
	if (voltageRawCount < 10)
	{
		/* Move the cursor to Row 0, Column 11 */
		LCD_Char_1_Position(row,COLUMN_11);
		LCD_Char_1_PrintString(CLEAR_TENS_HUNDREDS); /* Clear last characters */
	}
	else if (voltageRawCount < 100)
	{
		/* Move the cursor to Row 0, Column 12 */
		LCD_Char_1_Position(row,COLUMN_12);
		LCD_Char_1_PrintString(CLEAR_HUNDREDS); /* Clear last characters */
	}
	else
	{
		/* Continue on */
	}
}

void UpdateButtonState(uint8 slot_1, uint8 slot_2)
{
	LCD_Char_1_Position(ROW_0,COLUMN_0);
	
	/* Check the state of the buttons and update the LCD and the temperature setting */
	if (slot_1 && slot_2)
	{
		//do nothing;
	}
	else if (slot_1 || slot_2)
	{
		if (slot_1)
		{
			if(temp_set < 28)
			{
				temp_set++;
			}
		}
		if (slot_2)
		{
			if(temp_set > 18)
			{
				temp_set--;
			}
		}
	}
	else
	{
		//do nothing;
	}
	UpdateDisplay(temp_set, 1);
}

/* [] END OF FILE */
