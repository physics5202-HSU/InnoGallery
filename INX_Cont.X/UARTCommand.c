 /**
   UARTCommand File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     UARTCommand.c
 
   @Summary
     This is the Control file for the Control using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This source file provides implementations for driver APIs for Control.
     Generation Information :
         Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
         Device            :  PIC18F27K42
         Driver Version    :  2.01
     The generated drivers are tested against the following:
         Compiler          :  XC8 2.36 and above or later
         MPLAB             :  MPLAB X 6.00
 */ 

 /*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/
 
 /**
   Section: Included Files
 */

#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "UARTCommand.h"
#include "mcc_generated_files/uart1.h"


 /**
   Section: Control
 */

void UART_Read(uint8_t* pRdBuffer, const size_t size )
{
    uint8_t i;
    for(i=0;i<size;i++)
    {    
        if(UART1_is_rx_ready())
        {
            pRdBuffer[i] = UART1_Read();
            //__delay_us(1000);
            //if(UART_counter == 7)
            //{
                //UART_counter = 0;
            //}else{
                //UART_counter++;
            //}        
        }
    }
#if 0    
    //uint8_t i;
    //for(i=0;i<size;i++)
    //{
        pRdBuffer[0] = UART1_Read();
        __delay_us(1000);
    //}
#endif        
}


void UART_Write(uint8_t* pWrBuffer, const size_t size )
{
    uint8_t i;
    for(i=0;i<size;i++)
    {    
        if(UART1_is_tx_ready())
        {
            UART1_Write(pWrBuffer[i]);
            //__delay_us(1000);
            //if(UART_counter == 7)
            //{
                //UART_counter = 0;
            //}else{
                //UART_counter++;
            //}        
        }
    }
#if 0     
    uint8_t i;
    for(i=0;i<size;i++)
    {
        UART1_Write(pWrBuffer[i]);
        __delay_us(1000);
    }
#endif
}

 /**
  End of File
 */


