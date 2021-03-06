/*******************************************************************************
* File Name: CapSense_1_CompCH0_PM.c  
* Version 1.70
*
*  Description:
*     This file provides the power management source code APIs for the
*     Comparator.  
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include "CapSense_1_CompCH0.h"

static CapSense_1_CompCH0_backupStruct CapSense_1_CompCH0_backup;


/*******************************************************************************
* Function Name: CapSense_1_CompCH0_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_1_CompCH0_SaveConfig(void)
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: CapSense_1_CompCH0_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_1_CompCH0_RestoreConfig(void)
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: CapSense_1_CompCH0_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  CapSense_1_CompCH0_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_1_CompCH0_Sleep(void)
{
    /* Save Comp's enable state */    
    if(CapSense_1_CompCH0_ACT_PWR_EN == (CapSense_1_CompCH0_PWRMGR & CapSense_1_CompCH0_ACT_PWR_EN))
    {
        /* Comp is enabled */
        CapSense_1_CompCH0_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        CapSense_1_CompCH0_backup.enableState = 0u;
    }    
    
    CapSense_1_CompCH0_Stop();
    CapSense_1_CompCH0_SaveConfig();
}


/*******************************************************************************
* Function Name: CapSense_1_CompCH0_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  CapSense_1_CompCH0_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void CapSense_1_CompCH0_Wakeup(void) 
{
    CapSense_1_CompCH0_RestoreConfig();
    
    if(CapSense_1_CompCH0_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        CapSense_1_CompCH0_Enable();

    } /* Do nothing if Comp was disabled before */    
    
}


/* [] END OF FILE */
