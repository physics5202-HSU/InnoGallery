/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F27K42
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "Control_lib.h"
#include "stdio.h"

//#define LM75B_Address 0x48
//#define LM75B_REG_TA 0x01
//#define LM75B_Register 0x60
//#define LM75B_Start 0x00

//#define EEPROM_ADDRESS_1   0x50//1010 0000(A0) -- 0101 0000(50)
//#define EEPROM_ADDRESS_2   0x51//1010 0010(A2) -- 0101 0001(51)
//#define EEPROM_PAGE_ADDRESS_1   0x58//1011 0000(B0) -- 0101 1000(58)
//#define EEPROM_PAGE_ADDRESS_2   0x59//1011 0010(B2) -- 0101 1001(59)
//#define PAGE_NUM 128

//#define CBBoard_ADDRESS 0x61

/*
                         Main application
 */
//uint16_t LM75B_Read_Data;
//uint16_t ADC_Heat_FB_Value=0;
//uint16_t ADC_BL_PWM_Value=0;
//uint8_t e_buffer[PAGE_NUM];
//uint8_t CB_buffer[4];
//uint8_t counter = 0;
uint8_t I2CStart = 1;
//uint8_t state = 0;
void Timer1S_callback(void);

//uint8_t EUSART_Read(void){ return UART1_Read(); }
//void EUSART_Write(uint8_t txData){ UART1_Write(txData); }

void main(void)
{
    uint8_t i;
    // Initialize the device
    SYSTEM_Initialize();
    //I2C1_Write1ByteRegister(LM75B_Address, LM75B_REG_TA, LM75B_Register);
    //__delay_us(100);
    //I2C1_Write1ByteRegister(LM75B_Address, LM75B_Start, 0x00);
    //__delay_us(100);
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:
    TMR0_SetInterruptHandler(&Timer1S_callback);
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    HeatCheck_max = 3;
    ADC_Heat_FB_Value=0;
    ADC_BL_PWM_Value=0;
    preBL_PWM = 0;
    ALS_Value = 0;
    ALS_Value_Max = 0x26A;
    counter = 0;
    I2CStart = 0;
    Open1st = 1;
    state = 0;      //b test
    temperror = 0;
    BL_PWMerror = 0;
    TempCount = 0;
    CB_buffer[0] = 0xFE;
    CB_buffer[1] = 0x63;
    CB_buffer[2] = 0x83;
    CB_buffer[3] = 0xFF;
    flagBL_Enable = 1;
    flagBL_i2c_OUT = 0;
    counter1 = 0;
    //CB_DATA = (CB_DATA & 0x8000) | 0x3FF;
    //CB_DATA[0] = 0x83;
    //CB_DATA[1] = 0xff;
    //CB_DATA[0] = (CB_DATA[0] & 0x83);
    //CB_DATA[1] = (CB_DATA[1] & 0xFF);
    __delay_us(2000000);
    //SWDTEN = 1; //enable WDT
    //preBL_PWM = ADCC_GetSingleConversion(BL_PWM);  //ADC BL PWM in
    
    while (1)
    {
        // Add your application code
        //Heater
        //IO_RB2_SetHigh();
        //PWM5CON = 0x00;  //close PWM
        //PWM5CON = 0x80;  //open PWM
        //PWM5_LoadDutyValue(0x2D);
        //PWM5_LoadDutyValue(0xAD);
//        PWM5_LoadDutyValue(0x138);   //0x9C duty 50%// 0xFA duty 80%  //0x138 duty 100%    // for 200Hz
                                    // 0xFA duty 40% //0x138 duty 50% //0x270 duty 100% //  0x01  duty 0.16%   // for 100Hz
        //ADC_Heat_FB_Value = ADCC_GetSingleConversion(Heat_FB); //ADC Heater feedback
        //__delay_us(2000000);    // 2 Second
        //CLRWDT();  //Clear WDT
        //Temper
        //LM75B_Read_Data = I2C1_Read2ByteRegister (LM75B_Address, NULL);
        //LM75B_Read_Data = Temp_I2C1_Read2ByteRegister(LM75B_Address, NULL);
        //__delay_us(2000000);
        //BL
//        if(IO_RA1_GetValue())
//        {
//           IO_RA2_SetHigh();
//        }
        //IO_RA1_GetValue();  //BL_EN_in
        //IO_RA2_SetLow();  //BL_EN_out off
        //IO_RA2_SetHigh(); //BL_EN_out on
        //ADC_BL_PWM_Value = ADCC_GetSingleConversion(BL_PWM);  //ADC BL PWM in
        
        //IO_RB4_GetValue();   // PSON_in
        
        //IO_RB5_SetLow();   // PSON_out off
        //IO_RB5_SetHigh();  // PSON_out on
        
        //IO_RC0_SetLow();   // Fan off
        //IO_RC0_SetHigh();  // Fan on

        //IO_RC5_SetLow();   // EEPROM WC off
        //IO_RC5_SetHigh();  // EEPROM WC on 
        
        //if((nackcheck == 0) & (counter == 0))
#if 0
          IO_RA2_SetHigh();  //BL_EN_out = 1;
        __delay_us(2000000);    // 2 Second      
        if(I2CStart == 1)              
        {
            I2CStart = 0;
            BL_I2C1_WriteByteRegister(CBBoard_ADDRESS, CB_buffer, 4);
            __delay_us(1000);
        }else{
            if(nackcheck == 1)
            {
                if(counter<2)
                {
                    BL_I2C1_WriteByteRegister(CBBoard_ADDRESS, CB_buffer, 4);
                    counter++;
                    __delay_us(1000);
                }
            }
        }
#endif        
        //IO_RB4_GetValue();   // PSON_in
  ///////////////////////////////////////////////////////////
#if 1        
        switch(state)
        {
            case INOG_Running:
                INNOGL_Running();
                break;                                
            case INOG_NACK:
                INNOGL_CheckNACK();
                break;            
/*            
            case State_Standby:
                StandbyCheck();
                break;
            case State_Running:
                Running();
                break;                
            case State_PreHeat:
                preHeat();
                break;                
            case State_TempHOT:
                tempDown();
                break;                
            case State_HeatNG:
                HeatError();
                break;                
            case State_NACK:
                CheckNACK();
                break;
*/                
            default:
                //do
                break;
        }

////////////////////////////////////////////////////////////
#if 0        
        if( abs(ADC_BL_PWM_Value-preBL_PWM) > 0x64 )
        {
            ADC_BL_PWMtoI2C = ADC_BL_PWM_Value / 4;
            CB_buffer[0] = 0xFE;
            CB_buffer[1] = 0x63;
            //CB_buffer[2] = 0x83;
            //CB_buffer[3] = 0xFF;
            CB_buffer[2] = ADC_BL_PWMtoI2C >> 8;
            CB_buffer[3] = ADC_BL_PWMtoI2C & 0x00FF;            
            BL_I2C1_WriteByteRegister(CBBoard_ADDRESS, CB_buffer, 4);
            __delay_us(1000);
        }
#endif        
///////////////////////////////////////////////////////////////////////
#if 0       
        if(!(BL_PWMerror == 1))
        {
            if(nackcheck == 1)
            {
                state = State_NACK;
            }
        }
#endif        
#if 0       
        //if(UART1_is_rx_ready())
        //{    
            UART_Read(&UART_RX_buffer, 1 );
            __delay_us(1000);
        //}        
        UART_TX_buffer[0] = UART_RX_buffer[0];
        UART_TX_buffer[1] = 0x02;
        UART_TX_buffer[2] = 0x03;
        UART_TX_buffer[3] = 0x04;

        UART_Write(&UART_TX_buffer, 4 );
        __delay_us(1000);
#endif
#if 0        
        if(UART1_is_rx_ready())
        {
            UART_Read(&UART_RX_buffer, 8 );
            UART_Write(&UART_RX_buffer, 8 );
        }
#endif        
#if 0        
        if(UART1_is_rx_ready())
        {
            UART_RX_buffer[UART_counter] = UART1_Read();
            if(UART1_is_tx_ready())
            {
                UART1_Write(UART_RX_buffer[UART_counter]);
            }
            if(UART_counter == 7)
            {
                UART_counter = 0;
            }else{
                UART_counter++;
            }        
        }
#endif        
///////////////////////////////////////////////
#if 0        
        for(i=0;i<8;i++)
        {
            if(UART1_is_rx_ready())
            {
                UART_RX_buffer[i] = UART1_Read();
                __delay_us(500);
            }
        }
        for(i=0;i<8;i++)
        {
            if(UART1_is_tx_ready())
            {
                UART1_Write(UART_RX_buffer[i]);
                __delay_us(500);
            }
        }        
        //IO_RB4_GetValue();   // PSON_in
#endif        
#endif
    }
}

void Timer1S_callback(void)      //0.5S
{
    //uint16_t ADC_DataBuf[20];
    //uint16_t ADC_DataBuf;
    //uint16_t ADC_DataStd_p = 0x800;
    //uint16_t ADC_DataStd_n = 0x500;
#if 0    
    uint8_t i,j;
    uint8_t PWM_P = 0;
    uint8_t PWM_N = 0;
    uint16_t PWM_sum = 0;
    //uint16_t PWM_sumavg = 0;
    //IO_RC5_Toggle();
    //LM75B_Read_Data = I2C1_Read2ByteRegister (LM75B_Address, NULL);
    //LM75B_Read_Data = Temp_I2C1_Read2ByteRegister (LM75B_Address, NULL);
    //__delay_us(1000);
    IO_RC0_SetHigh();  // Fan on
    for(j=0;j<4;j++)
    {    
        //IO_RC0_SetHigh();  // Fan on
        for(i=0;i<100;i++)        //100   200
        {
            if(IO_RA0_GetValue()){
                PWM_P++;
                __delay_us(33);   //33   9
            }else{
                PWM_N++;
                __delay_us(33);   //33   9
            }
        }
        //IO_RC0_SetLow();   // Fan off
        __delay_us(1000);
        PWM_sum = PWM_P + PWM_sum;
        PWM_P = 0;
        PWM_N = 0;    
    }

    ADC_BL_PWM_Value = (PWM_sum >> 2);   // /4 
    IO_RC0_SetLow();   // Fan off
    //PWM_sum = PWM_sum;
    //PWM_sumavg = 2;
    //PWM_sumavg = 1;
#endif
    //IO_RC0_SetHigh();
    //ADC_BL_PWM_Value = PWM_Data_collection();    
////////////////////////////////////////////////////////////
    //if( (ADC_BL_PWM_Value != preBL_PWM) & (flagBL_i2c_OUT == 1)  )
    //{
#if 0       
        ADC_BL_PWMtoI2C = (ADC_BL_PWM_Value * 10) + 24;
        CB_buffer[0] = 0xFE;
        CB_buffer[1] = 0x63;
        //CB_buffer[2] = 0x83;
        //CB_buffer[3] = 0xFF;
        CB_buffer[2] = (ADC_BL_PWMtoI2C >> 8) | 0x0080;
        CB_buffer[3] = ADC_BL_PWMtoI2C & 0x00FF;            
        BL_I2C1_WriteByteRegister(CBBoard_ADDRESS, CB_buffer, 4);
        __delay_us(1000);
#endif
        //PWM
        //PWM5_LoadDutyValue(0x00);   // 0xFA duty 50%  //0x1F3 duty 100% //  0x01  duty 0.2%
    //}
    //preBL_PWM = ADC_BL_PWM_Value;
    
///////////////////////////////////////////////////////////////////////
//ALS Value
    //ALS_Value = ALS_Data_collection();    
    //ALS_Value = ALS_Read(ALS_1_CTRL_ADDR);
    if(IO_RC7_GetValue() == 0)     //KEY == 0
    {    
        ALS_moving_average();
    }else{                         //KEY == 1
        ADC_BL_PWM_Value = PWM_Data_collection();
        PWM5_LoadDutyValue(ADC_BL_PWM_Value*4);
    }
        
    if(nackcheck_als == 1)
    {
        ALS_error = 1;
        //state = State_NACK;
    }
    //IO_RC0_SetLow();    
///////// PWM ADC transfer ///////////////////////////////////////////   
#if 0   
   // preBL_PWM = ADCC_GetSingleConversion(BL_PWM);  //ADC BL PWM in  200Hz
    PWM_sum = 0;
    __delay_us(1000);
    for(j=0;j<5;j++)
    {    
    IO_RC0_SetHigh();  // Fan on
    for(i=0;i<50;i++)
    {
        ADC_DataBuf = ADCC_GetSingleConversion(BL_PWM);  //ADC BL PWM in  200Hz
        if(ADC_DataBuf >= ADC_DataStd_p){
            PWM_P++;
        }else if(ADC_DataBuf < ADC_DataStd_p){
            PWM_N++;
        }            
    }
    IO_RC0_SetLow();   // Fan off
    __delay_us(1000);
        PWM_sum = PWM_P + PWM_sum;
        PWM_P = 0;
        PWM_N = 0;
    }
    PWM_avg = PWM_sum / 5;
    preBL_PWM = abs(PWM_P - PWM_N)%(PWM_P + PWM_N);
#endif    
///////////////////////////////////////////////////////////////////////    
#if 0   
    if(!(temperror == 1))
    {
        if(nackcheck_temp == 1)
        {
            state = State_NACK;
        }
    }
#endif    
}
/**
 End of File
*/