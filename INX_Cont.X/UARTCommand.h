/* 
 * File:   UARTCommand.h
 * Author: USER
 *
 * Created on 2024年2月1日, 上午 8:53
 */

#ifndef UARTCOMMAND_H
#define	UARTCOMMAND_H

#include <xc.h>
#include <stdint.h>

uint8_t UART_counter;

#ifdef	__cplusplus
extern "C" {
#endif
    
void UART_Read(uint8_t* pRdBuffer, const size_t size );
void UART_Write(uint8_t* pWrBuffer, const size_t size );

#ifdef	__cplusplus
}
#endif

#endif	/* UARTCOMMAND_H */

