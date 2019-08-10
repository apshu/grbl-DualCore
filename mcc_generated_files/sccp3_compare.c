/**
  SCCP3 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    sccp3.c

  @Summary
    This is the generated driver implementation file for the SCCP3 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for SCCP3. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.125
        Device            :  dsPIC33CH128MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36B
        MPLAB             :  MPLAB X v5.20
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "sccp3_compare.h"

/** OC Mode.

  @Summary
    Defines the OC Mode.

  @Description
    This data type defines the OC Mode of operation.

*/

static uint16_t         gSCCP3Mode;

/**
  Section: Driver Interface
*/


void SCCP3_COMPARE_Initialize (void)
{
    // CCPON disabled; MOD Dual Edge Compare; CCSEL disabled; CCPSIDL disabled; TMR32 16 Bit; CCPSLP disabled; TMRPS 1:1; CLKSEL FOSC/2; TMRSYNC disabled; 
    CCP3CON1L = (0x04 & 0x7FFF); //Disabling CCPON bit
    //RTRGEN enabled; ALTSYNC disabled; ONESHOT enabled; TRIGEN enabled; IOPS Each Time Base Period Match; SYNC SCCP2; OPSRC Special Event Trigger; 
    CCP3CON1H = 0xC0C3;
    //ASDGM disabled; SSDG disabled; ASDG 0; PWMRSEN disabled; 
    CCP3CON2L = 0x00;
    //ICGSM Level-Sensitive mode; ICSEL IC3; AUXOUT Disabled; OCAEN disabled; OENSYNC disabled; 
    CCP3CON2H = 0x00;
    //OETRIG disabled; OSCNT None; POLACE disabled; PSSACE Tri-state; 
    CCP3CON3H = 0x00;
    //ICDIS disabled; SCEVT disabled; TRSET disabled; ICOV disabled; ASEVT disabled; TRIG disabled; ICGARM disabled; TRCLR disabled; 
    CCP3STATL = 0x00;
    //TMR 0; 
    CCP3TMRL = 0x00;
    //TMR 0; 
    CCP3TMRH = 0x00;
    //PR 65535; 
    CCP3PRL = 0xFFFF;
    //PR 0; 
    CCP3PRH = 0x00;
    //CMP 0; 
    CCP3RAL = 0x00;
    //CMP 65535; 
    CCP3RBL = 0xFFFF;
    //BUF 0; 
    CCP3BUFL = 0x00;
    //BUF 0; 
    CCP3BUFH = 0x00;


    gSCCP3Mode = CCP3CON1Lbits.MOD;
    // Clearing IF flag before enabling the interrupt.
    IFS2bits.CCP3IF = 0;
    // Enabling SCCP3 interrupt.
    IEC2bits.CCP3IE = 1;

    // Clearing IF flag before enabling the interrupt.
    IFS2bits.CCT3IF = 0;
    // Enabling SCCP3 interrupt.
    IEC2bits.CCT3IE = 1;
}

void __attribute__ ((weak)) SCCP3_COMPARE_CallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _CCP3Interrupt ( void )
{
    if(IFS2bits.CCP3IF)
    {
		// SCCP3 COMPARE callback function 
		SCCP3_COMPARE_CallBack();
		
        IFS2bits.CCP3IF = 0;
    }
}

void __attribute__ ((weak)) SCCP3_COMPARE_TimerCallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _CCT3Interrupt ( void )
{
    if(IFS2bits.CCT3IF)
    {
		// SCCP3 COMPARE Timer callback function 
		SCCP3_COMPARE_TimerCallBack();
	
        IFS2bits.CCT3IF = 0;
    }
}

void SCCP3_COMPARE_Start( void )
{
    /* Start the Timer */
    CCP3CON1Lbits.CCPON = true;
}

void SCCP3_COMPARE_Stop( void )
{
    /* Start the Timer */
    CCP3CON1Lbits.CCPON = false;
}

void SCCP3_COMPARE_SingleCompare16ValueSet( uint16_t value )
{   
    CCP3RAL = value;
}


void SCCP3_COMPARE_DualCompareValueSet( uint16_t priVal, uint16_t secVal )
{

    CCP3RAL = priVal;

    CCP3RBL = secVal;
}

void SCCP3_COMPARE_DualEdgeBufferedConfig( uint16_t priVal, uint16_t secVal )
{

    CCP3RAL = priVal;

    CCP3RBL = secVal;
}

void SCCP3_COMPARE_CenterAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{

    CCP3RAL = priVal;

    CCP3RBL = secVal;
}

void SCCP3_COMPARE_EdgeAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{

    CCP3RAL = priVal;

    CCP3RBL = secVal;
}

void SCCP3_COMPARE_VariableFrequencyPulseConfig( uint16_t priVal )
{
    CCP3RAL = priVal;
}

bool SCCP3_COMPARE_IsCompareCycleComplete( void )
{
    return(IFS2bits.CCP3IF);
}

bool SCCP3_COMPARE_TriggerStatusGet( void )
{
    return( CCP3STATLbits.TRIG );
    
}

void SCCP3_COMPARE_TriggerStatusSet( void )
{
    CCP3STATLbits.TRSET = 1;
}

void SCCP3_COMPARE_TriggerStatusClear( void )
{
    /* Clears the trigger status */
    CCP3STATLbits.TRCLR = 0;
}

bool SCCP3_COMPARE_SingleCompareStatusGet( void )
{
    return( CCP3STATLbits.SCEVT );
}

void SCCP3_COMPARE_SingleCompareStatusClear( void )
{
    /* Clears the trigger status */
    CCP3STATLbits.SCEVT = 0;
    
}
/**
 End of File
*/
