/*******************************************************************************
* File Name: COLD.h  
* Version 1.60
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_COLD_H) /* Pins COLD_H */
#define CY_PINS_COLD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "COLD_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    COLD_Write(uint8 value) ;
void    COLD_SetDriveMode(uint8 mode) ;
uint8   COLD_ReadDataReg(void) ;
uint8   COLD_Read(void) ;
uint8   COLD_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define COLD_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define COLD_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define COLD_DM_RES_UP          PIN_DM_RES_UP
#define COLD_DM_RES_DWN         PIN_DM_RES_DWN
#define COLD_DM_OD_LO           PIN_DM_OD_LO
#define COLD_DM_OD_HI           PIN_DM_OD_HI
#define COLD_DM_STRONG          PIN_DM_STRONG
#define COLD_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define COLD_MASK               COLD__MASK
#define COLD_SHIFT              COLD__SHIFT
#define COLD_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define COLD_PS                     (* (reg8 *) COLD__PS)
/* Data Register */
#define COLD_DR                     (* (reg8 *) COLD__DR)
/* Port Number */
#define COLD_PRT_NUM                (* (reg8 *) COLD__PRT) 
/* Connect to Analog Globals */                                                  
#define COLD_AG                     (* (reg8 *) COLD__AG)                       
/* Analog MUX bux enable */
#define COLD_AMUX                   (* (reg8 *) COLD__AMUX) 
/* Bidirectional Enable */                                                        
#define COLD_BIE                    (* (reg8 *) COLD__BIE)
/* Bit-mask for Aliased Register Access */
#define COLD_BIT_MASK               (* (reg8 *) COLD__BIT_MASK)
/* Bypass Enable */
#define COLD_BYP                    (* (reg8 *) COLD__BYP)
/* Port wide control signals */                                                   
#define COLD_CTL                    (* (reg8 *) COLD__CTL)
/* Drive Modes */
#define COLD_DM0                    (* (reg8 *) COLD__DM0) 
#define COLD_DM1                    (* (reg8 *) COLD__DM1)
#define COLD_DM2                    (* (reg8 *) COLD__DM2) 
/* Input Buffer Disable Override */
#define COLD_INP_DIS                (* (reg8 *) COLD__INP_DIS)
/* LCD Common or Segment Drive */
#define COLD_LCD_COM_SEG            (* (reg8 *) COLD__LCD_COM_SEG)
/* Enable Segment LCD */
#define COLD_LCD_EN                 (* (reg8 *) COLD__LCD_EN)
/* Slew Rate Control */
#define COLD_SLW                    (* (reg8 *) COLD__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define COLD_PRTDSI__CAPS_SEL       (* (reg8 *) COLD__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define COLD_PRTDSI__DBL_SYNC_IN    (* (reg8 *) COLD__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define COLD_PRTDSI__OE_SEL0        (* (reg8 *) COLD__PRTDSI__OE_SEL0) 
#define COLD_PRTDSI__OE_SEL1        (* (reg8 *) COLD__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define COLD_PRTDSI__OUT_SEL0       (* (reg8 *) COLD__PRTDSI__OUT_SEL0) 
#define COLD_PRTDSI__OUT_SEL1       (* (reg8 *) COLD__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define COLD_PRTDSI__SYNC_OUT       (* (reg8 *) COLD__PRTDSI__SYNC_OUT) 


#if defined(COLD__INTSTAT)  /* Interrupt Registers */

    #define COLD_INTSTAT                (* (reg8 *) COLD__INTSTAT)
    #define COLD_SNAP                   (* (reg8 *) COLD__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins COLD_H */


/* [] END OF FILE */
