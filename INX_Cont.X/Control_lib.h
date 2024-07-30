/* 
 * File:   Control_lib.h
 * Author: USER
 *
 * Created on 2024年1月24日, 上午 9:08
 */

#ifndef CONTROL_LIB_H
#define	CONTROL_LIB_H

#include <xc.h>
#include <stdint.h>

#define LM75B_Address 0x48
#define LM75B_REG_TA 0x01
#define LM75B_Register 0x60
#define LM75B_Start 0x00

#define EEPROM_ADDRESS_1   0x50//1010 0000(A0) -- 0101 0000(50)
#define EEPROM_ADDRESS_2   0x51//1010 0010(A2) -- 0101 0001(51)
#define EEPROM_PAGE_ADDRESS_1   0x58//1011 0000(B0) -- 0101 1000(58)
#define EEPROM_PAGE_ADDRESS_2   0x59//1011 0010(B2) -- 0101 1001(59)
#define PAGE_NUM 128

#define CBBoard_ADDRESS 0x61

#define ALS_1_CTRL_ADDR     0x23//0100 0110(0x46) --> 0010 0011(0x23))  ADDR="L"
#define ALS_2_CTRL_ADDR     0x5C//1011 1000(0xB8) --> 0101 1100(0x5C))  ADDR="H" 

#define Temp_min 0x192
#define Temp_max 0x0FA//40//36//
#define Temp_std 0x028//00
#define Temp_hight 0x078//19
#define Temp_m10 0x1EA
#define Temp_m20 0x1D6
#define Temp_m30 0x1C2
#define Temp_m40 0x1AE

#define MAX_POINTS 12
#define POINTS 12
#define window 100

uint16_t point_index;
float point_slope;
uint16_t test_y_value;

uint16_t DutyValue_PWM;
uint16_t LM75B_Read_Data;
uint16_t Temp_Data;
uint16_t ADC_Heat_FB_Value;
uint16_t HeatCheck_max;
uint16_t ADC_BL_PWM_Value;
uint16_t ADC_BL_PWMtoI2C;
uint16_t preBL_PWM;
uint16_t preALS_PWM_Value;
uint16_t LoadBL_PWM;
uint16_t ALS_Value;
uint16_t ALS_PWM_Value;
uint16_t ALS_Value_Max;
uint8_t e_buffer[PAGE_NUM];
uint8_t CB_buffer[4];
uint8_t UART_TX_buffer[8];
uint8_t UART_RX_buffer[8];
uint8_t counter;
uint8_t I2CStart;
uint8_t Open1st;
uint8_t state;
uint8_t temperror;
uint8_t ALS_error;
uint8_t BL_PWMerror;
uint8_t TempCount;

uint8_t flagBL_Enable;
uint8_t flagBL_i2c_OUT;

uint16_t Data_current_ALS;
uint16_t Data[window];
//uint32_t Diff;
int32_t Diff;
uint32_t moving_average;
uint8_t counter1;

#ifdef	__cplusplus
extern "C" {
#endif
enum {
	State_Standby=0,
	State_Running,
	State_PreHeat,
	State_TempHOT,
    State_HeatNG,
    State_NACK,
};

enum {
	INOG_Running=0,
    INOG_NACK,
};

uint8_t StandbyCheck(void);
uint8_t Running(void);
uint8_t preHeat(void);
uint8_t tempDown(void);
void HeatError(void);
void CheckNACK(void);
uint8_t INNOGL_Running(void);
void INNOGL_CheckNACK(void);
double linear_interpolation(double x_value);
uint16_t GPIO_BL_PWM_Value(void);
uint16_t PWM_Data_collection(void);
uint16_t calculate_moving_average(int *data, int size);
uint16_t ALS_Data_collection(void);
void ALS_moving_average(void);
uint16_t LUT(uint32_t move_average_sum);

#define eusartRxCount (UART1_is_rx_ready())
//uint8_t EUSART_Read(void);
//void EUSART_Write(uint8_t txData);

#ifdef	__cplusplus
}
#endif

#endif	/* CONTROL_LIB_H */

