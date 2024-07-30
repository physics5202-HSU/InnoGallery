 /**
   Control File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     Control_lib.c
 
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
 #include "Control_lib.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"

//double point_x[12] = {6, 2334, 2809, 4202, 5595, 6833, 13776, 21357, 29885, 36527, 39075, 41942};
//double point_y[12] = {5, 14, 22, 31, 40, 48, 57, 65, 74, 83, 91, 100};

//float point_x[12] = {6, 2334, 2809, 4202, 5595, 6833, 13776, 21357, 29885, 36527, 39075, 41942};
//float point_y[12] = {5, 14, 22, 31, 40, 48, 57, 65, 74, 83, 91, 100};
//float point_x[12] = {4, 19, 23, 34, 45, 55, 112, 173, 242, 296, 317, 340};
//float point_x[12] = {8, 34, 41, 62, 82, 101, 203, 315, 440, 538, 576, 618};
//float point_x[12] = {1600, 6800, 8200, 12400, 16400, 20200, 40600, 63000, 88000, 107600, 115200, 123600};    //window 200
float point_x[12] = {800, 3400, 4100, 6200, 8200, 10100, 20300, 31500, 44000, 53800, 57600, 61800};    //window 100
//float point_x[12] = {160, 680, 820, 1240, 1640, 2020, 4060, 6300, 8800, 10760, 11520, 12360};    //window 20
//float point_x[12] = {80, 340, 410, 620, 820, 1010, 2030, 3150, 4400, 5380, 5760, 6180};    //window 10
//float point_x[12] = {400, 1700, 2050, 3100, 4100, 5050, 10150, 15750, 22000, 26900, 28800, 30900};
//float point_y[12] = {5, 14, 22, 31, 40, 48, 57, 65, 74, 83, 91, 100};
//float point_y[12] = {18, 53, 84, 119, 154, 185, 220, 251, 286, 321, 352, 387};
//float point_y[12] = {18, 53, 84, 119, 154, 185, 220, 251, 286, 321, 352, 392};
float point_y[12] = {18, 34, 38, 50, 62, 74, 135, 202, 277, 336, 359, 392};
//float point_x[5] = {100,200,300,400,500};
//float point_y[5] = {10,20,30,40,50};
uint16_t WINDOW_SIZE = 20;

uint16_t Data_current_ALS = 0;
uint16_t Data[window] = {0};
//uint32_t Diff = 0;
int32_t Diff = 0;
uint32_t moving_average = 0;

 /**
   Section: Control
 */
uint8_t StandbyCheck(void)
{
    IO_RB5_SetLow();   // PSON_out off
    IO_RA2_SetLow();   //BL_EN_out off
    flagBL_Enable = 0;    //20240418
    IO_RB2_SetLow();   //Heater_out off
    //IO_RC0_SetLow();   // Fan off
    PWM5_LoadDutyValue(0x00);   // 0xFA duty 50%  //0x1F3 duty 100% //  0x01  duty 0.2%
    flagBL_i2c_OUT = 0;
    //while(1)
    //{    
    //LM75B_Read_Data = I2C1_Read2ByteRegister (LM75B_Address, NULL);
    Temp_Data = LM75B_Read_Data >> 7;
    if((Temp_Data > Temp_std) & (Temp_Data < Temp_max))       //0xFA  125
    {
        if(IO_RB4_GetValue() == 1)     //PSON_in == 1
        {
          //GPIO_RB5 = 1;  //PSON_out = 1;
          state = State_Running;
          flagBL_Enable = 1;    //20240418
          //break;
          return state;
        }
    }else{
        state = State_PreHeat;
        //break;
        return state;
    }
    //ADC_BL_PWM_Value = ADCC_GetSingleConversion(BL_PWM);  //ADC BL PWM in
    //ADC_BL_PWM_Value = ADCC_GetSingleConversion(BL_PWM);  //ADC BL PWM in
#if 0         
        if( abs(ADC_BL_PWM_Value-preBL_PWM) > 0x10 )
        {
            ADC_BL_PWMtoI2C = ADC_BL_PWM_Value / 4;
            CB_buffer[0] = 0xFE;
            CB_buffer[1] = 0x63;
            //CB_buffer[2] = 0x83;
            //CB_buffer[3] = 0xFF;
            CB_buffer[2] = ADC_BL_PWMtoI2C >> 8;
            CB_buffer[3] = ADC_BL_PWMtoI2C & 0x00FF;            
            BL_I2C1_WriteByteRegister(CBBoard_ADDRESS, CB_buffer, 4);
        }
#endif
#if 0     //20240403
        ADC_Heat_FB_Value = ADCC_GetSingleConversion(Heat_FB); //ADC Heater feedback
    if(ADCC_GetSingleConversion(Heat_FB))
    {
        state = State_HeatNG;
        //break;
        return state;
    }
#endif        
    //}
} 

uint8_t Running(void)
{
    IO_RB2_SetLow();   //Heater_out off
    PWM5_LoadDutyValue(0x00);   // 0xFA duty 50%  //0x1F3 duty 100% //  0x01  duty 0.2%
    //while(1)
    //{    
    if(IO_RB4_GetValue() == 0)     //PSON_in == 0
    {
        state = State_Standby;
        //break;
        return state;
    }

    //IO_RB2_SetLow();   //Heater_out off
    //PWM5_LoadDutyValue(0x00);   // 0xFA duty 50%  //0x1F3 duty 100% //  0x01  duty 0.2%    
    //if(IO_RB5_GetValue() != 1)
    //{
    IO_RB5_SetHigh();  //PSON_out = 1;
    if(flagBL_Enable == 1)
    {
        flagBL_Enable = 0;
        __delay_us(2000000);    // 2 Second
    //}
    //if(IO_RA2_GetValue() != 1)
    //{
        IO_RA2_SetHigh();  //BL_EN_out = 1;
        __delay_us(800000);    // 2 Second
        //flagBL_i2c_OUT = 1;
        CB_buffer[0] = 0xFE;
        CB_buffer[1] = 0x63;
        //CB_buffer[2] = 0x83;
        //CB_buffer[3] = 0xFF;
        CB_buffer[2] = (ADC_BL_PWMtoI2C >> 8) | 0x0080;
        CB_buffer[3] = ADC_BL_PWMtoI2C & 0x00FF;            
        BL_I2C1_WriteByteRegister(CBBoard_ADDRESS, CB_buffer, 4);
        //__delay_us(2000000);    // 2 Second
        flagBL_i2c_OUT = 1;
    //}
    }

    //LM75B_Read_Data = I2C1_Read2ByteRegister (LM75B_Address, NULL);
    Temp_Data = LM75B_Read_Data >> 7;
    //if((Temp_Data > Temp_max) & (Temp_Data < Temp_min)){
    if((Temp_Data > Temp_hight) & (Temp_Data < Temp_max))
    {    
        state = State_TempHOT;
        //break;
        return state;
    }
//c    ADC_BL_PWM_Value = ADCC_GetSingleConversion(BL_PWM);  //ADC BL PWM in
    __delay_us(500000);
#if 0         
        if( abs(ADC_BL_PWM_Value-preBL_PWM) > 0x10 )
        {
            ADC_BL_PWMtoI2C = ADC_BL_PWM_Value / 4;
            CB_buffer[0] = 0xFE;
            CB_buffer[1] = 0x63;
            //CB_buffer[2] = 0x83;
            //CB_buffer[3] = 0xFF;
            CB_buffer[2] = ADC_BL_PWMtoI2C >> 8;
            CB_buffer[3] = ADC_BL_PWMtoI2C & 0x00FF;            
            BL_I2C1_WriteByteRegister(CBBoard_ADDRESS, CB_buffer, 4);
        }
#endif
    
#if 0     //20240403
    ADC_Heat_FB_Value = ADCC_GetSingleConversion(Heat_FB); //ADC Heater feedback
    if(ADCC_GetSingleConversion(Heat_FB))
    {
        state = State_HeatNG;
        //break;
        return state;
    }
#endif    
    //}    
} 

uint8_t preHeat(void)
{
    //while(1)
    //{        
    if(IO_RB4_GetValue())     //PSON_in == 1
    {
        state = State_Running;
        //break;
        return state;
    }
    //if(IO_RB5_GetValue() != 1)
    //{
    IO_RB5_SetHigh();  //PSON_out = 1;
    //}

    IO_RB2_SetHigh(); //HEAT_12V_EN   Heater = 1
#if 1   
    if(Temp_Data > 0x100)
    {    
        if(Temp_Data >= Temp_m10)
        {
            DutyValue_PWM = 0x2C;  //PWM 7%
        }else if((Temp_Data < Temp_m10) & (Temp_Data >= Temp_m20)){
            DutyValue_PWM = 0x90;  //PWM 23%
        }else if((Temp_Data < Temp_m20) & (Temp_Data >= Temp_m30)){
            DutyValue_PWM = 0xE1;  //PWM 36%
        }else if((Temp_Data < Temp_m30) & (Temp_Data >= Temp_m40)){
            DutyValue_PWM = 0x145; //PWM 52%
        }else if(Temp_Data < Temp_m40){
            DutyValue_PWM = 0x196; //PWM 65%
        }  
    }    
    PWM5_LoadDutyValue(DutyValue_PWM);   // 0xFA duty 40% //0x138 duty 50% //0x270 duty 100% //  0x01  duty 0.16%   // for 100Hz
#else
    PWM5_LoadDutyValue(0x145);
#endif    
    //__delay_us(1000000);
    ADC_Heat_FB_Value = ADCC_GetSingleConversion(Heat_FB); //ADC Heater feedback
    if(ADC_Heat_FB_Value >= HeatCheck_max)
    {
        state = State_HeatNG;
        //break;
        return state;
    }

    //LM75B_Read_Data = I2C1_Read2ByteRegister (LM75B_Address, NULL);
    Temp_Data = LM75B_Read_Data >> 7;
    //if(Temp_Data > Temp_max)
    if((Temp_Data > Temp_std) & (Temp_Data < Temp_max))    
    {
        state = State_Standby;
        //break;
        return state;
    }
    //}
} 

uint8_t tempDown(void)
{
    IO_RB2_SetLow();   //Heater_out off
    PWM5_LoadDutyValue(0x00);   // 0xFA duty 50%  //0x1F3 duty 100% //  0x01  duty 0.2%
    //while(1)
    //{    
    //if(IO_RC0_GetValue() != 1)
    //{
    IO_RC0_SetHigh(); //Fan_on  Fan = 1
    //}

    if(IO_RB4_GetValue() == 0)     //PSON_in == 0
    {
        state = State_Standby;
        //break;
        return state;
    }
    //LM75B_Read_Data = I2C1_Read2ByteRegister (LM75B_Address, NULL);
    Temp_Data = LM75B_Read_Data >> 7;
    if(Temp_Data < Temp_std)
    {
        state = State_Running;
        //break;
        return state;
    }

//c    ADC_BL_PWM_Value = ADCC_GetSingleConversion(BL_PWM);  //ADC BL PWM in
#if 0       
        if( abs(ADC_BL_PWM_Value-preBL_PWM) > 0x10 )
        {
            ADC_BL_PWMtoI2C = ADC_BL_PWM_Value / 4;
            CB_buffer[0] = 0xFE;
            CB_buffer[1] = 0x63;
            //CB_buffer[2] = 0x83;
            //CB_buffer[3] = 0xFF;
            CB_buffer[2] = ADC_BL_PWMtoI2C >> 8;
            CB_buffer[3] = ADC_BL_PWMtoI2C & 0x00FF;            
            BL_I2C1_WriteByteRegister(CBBoard_ADDRESS, CB_buffer, 4);
        }
#endif
#if 0     //20240403    
    ADC_Heat_FB_Value = ADCC_GetSingleConversion(Heat_FB); //ADC Heater feedback
    if(ADCC_GetSingleConversion(Heat_FB))
    {
        state = State_HeatNG;
        //break;
        __delay_us(2000000);    // 2 Second
        return state;
    }
#endif    
    //}    
}

void HeatError(void)
{
    IO_RB2_SetLow();   //Heater_out off
    PWM5_LoadDutyValue(0x00);   // 0xFA duty 50%  //0x1F3 duty 100% //  0x01  duty 0.2%

    if(IO_RB4_GetValue() == 0)     //PSON_in == 0
    {
        //if(temperror | BL_PWMerror)
        //{
        state = State_Standby;
        //}
    }else{
        state = State_Running;
    }
}

void CheckNACK(void)
{  
    //if(nackcheck_temp != 1)
    //{
    //LM75B_Read_Data = I2C1_Read2ByteRegister (LM75B_Address, NULL);
    LM75B_Read_Data = Temp_I2C1_Read2ByteRegister (LM75B_Address, NULL);
    if(nackcheck_temp == 1)
    {
        temperror = 1;
        IO_RB2_SetLow();   //Heater_out off
        PWM5_LoadDutyValue(0x00);   // 0xFA duty 50%  //0x1F3 duty 100% //  0x01  duty 0.2%      
    }
    //}

    //if(nackcheck != 1)
    //{
    BL_I2C1_WriteByteRegister(CBBoard_ADDRESS, CB_buffer, 4);
    if(nackcheck == 1)
    {
        BL_PWMerror = 1;
    }
    //}

    if(IO_RB4_GetValue() == 0)     //PSON_in == 0
    {
        //if(temperror | BL_PWMerror)    
        //{
        state = State_Standby;
        //}
    }else{
        state = State_Running;
    }    
    //ADC_BL_PWM_Value = ADCC_GetSingleConversion(BL_PWM);  //ADC BL PWM in
}

uint8_t INNOGL_Running(void)
{
    int i;
    double interpolated_y;      
    IO_RC0_SetHigh();
    if(IO_RA1_GetValue() == 1)     //BLON_in == 1
    {

#if 1   
        if(Open1st == 1)
        {
            IO_RB5_SetHigh();  //PSON_out = 1;
            //__delay_us(1000000);    // 1 Second
            IO_RA2_SetHigh();     //BLON_out == 1
            Open1st = 0;
        }
        if(I2CStart == 1)              
        {
            I2CStart = 0;
            __delay_us(2000000);    // 2 Second
            IO_RA2_SetHigh();     //BLON_out == 1
            __delay_us(800000);    // 2 Second            
            CB_buffer[0] = 0xFE;
            CB_buffer[1] = 0x63;
            CB_buffer[2] = 0x83;
            CB_buffer[3] = 0xFF;
            //CB_buffer[2] = 0x0080;
            //CB_buffer[3] = 0x00FF;
            BL_I2C1_WriteByteRegister(CBBoard_ADDRESS, CB_buffer, 4);
            __delay_us(1000);
        }
#endif         
    }else{
        Open1st = 1;
        IO_RA2_SetLow();      //BLON_out == 0
    }
    if(IO_RC7_GetValue() == 1)     //KEY == 1
    { 
#if 0       
        if(ADC_BL_PWM_Value >= preBL_PWM)
        {
            for(i=0;i<(ADC_BL_PWM_Value-preBL_PWM);i++)
            {
                if((preBL_PWM+i+1) <= 100)
                {            
                PWM5_LoadDutyValue((preBL_PWM+i+1)*4);
                __delay_us(1000);    // 1 ms
                }else{
                    PWM5_LoadDutyValue(0x188);
                }
            }
            //LoadBL_PWM = 
        }else if(ADC_BL_PWM_Value < preBL_PWM)
        {
            for(i=0;i<(preBL_PWM-ADC_BL_PWM_Value);i++)
            {
                if((preBL_PWM-i-1) >= 0)
                {
                    PWM5_LoadDutyValue((preBL_PWM-i-1)*4);
                    __delay_us(1000);    // 1 ms
                }else{
                    PWM5_LoadDutyValue(0x00);
                }
            }    
        }
    preBL_PWM = ADC_BL_PWM_Value;
#endif
    //__delay_us(500000);    // 0.5 Second
    //ADC_BL_PWM_Value = PWM_Data_collection();  
    //PWM5_LoadDutyValue(0xAD);
    //ADC_BL_PWM_Value = ADC_BL_PWM_Value * 3.87;
    //PWM5_LoadDutyValue(ADC_BL_PWM_Value*4);

//PWM5_LoadDutyValue(0xAD);    
    //PWM5_LoadDutyValue(0xC4);   // 0xC4 duty 50%  //0x188 duty 100% //  0x01  duty 0.26%
    //preBL_PWM = LoadBL_PWM;
    }else{     ///ALS調光   需使用幾階調光   MAX? MIN?
        //__delay_us(200000);    // 0.2 Second
        //ALS_moving_average();
    //ALS_Value =  preALS_Value;
        //__delay_us(500000);    // 0.5 Second
#if 0       
        ALS_Value = ALS_Data_collection(); 
        if(ALS_Value <= point_x[0])
        {
            test_y_value = point_y[0];
        }else if(ALS_Value >= point_x[POINTS-1])
        {
            test_y_value = point_y[POINTS-1];
        }else{
            test_y_value = linear_interpolation(ALS_Value);
        }        
        //test_y_value = linear_interpolation(ALS_Value);
        ALS_PWM_Value = test_y_value;
#endif        
#if 0       
        if(ALS_PWM_Value > preALS_PWM_Value)
        {
            for(i=0;i<(ALS_PWM_Value-preALS_PWM_Value);i++)
            {
                if((preALS_PWM_Value-i) != 100)
                {
                    __delay_us(50000);    // 50 ms
                    PWM5_LoadDutyValue((preALS_PWM_Value+i)*4);
                    //__delay_us(10000);    // 10 ms
                }else{
                    PWM5_LoadDutyValue(0x188);
                }
            }
            //LoadBL_PWM = 
        }else if(ALS_PWM_Value < preALS_PWM_Value)
        {
            for(i=0;i<(preALS_PWM_Value-ALS_PWM_Value);i++)
            {
                if((preALS_PWM_Value-i) != 0)
                {
                    __delay_us(30000);    // 30 ms
                    PWM5_LoadDutyValue((preALS_PWM_Value-i)*4);
                    //__delay_us(10000);    // 10 ms
                }else{
                    PWM5_LoadDutyValue(0x00);
                }
            }    
        }
    preALS_PWM_Value = ALS_PWM_Value;
#else
    //__delay_us(2000000);    // 1 Second
    //ALS_PWM_Value = 0x2D;
    //PWM5_LoadDutyValue(ALS_PWM_Value*4);
    //PWM5_LoadDutyValue(0xAD);
#endif    
    }
    
}

void INNOGL_CheckNACK(void)
{ 
   uint16_t ALS_test = 0; 
    //if(nackcheck_als == 1)
    //{
        //ALS_error = 1;   
    //}
   for(int i = 0;i < 3;i++)
   {
       __delay_us(200000);    // 200 ms
        ALS_test = ALS_Read(ALS_1_CTRL_ADDR);
        if(nackcheck_als == 1)
        {
            ALS_error = 1;
            break;
        }else{
            ALS_error = 0;
            break;
        }        
   }
    state = INOG_Running;    
}

double linear_interpolation(double x_value)
{
    uint16_t y_value = 0;
    
    for(int i = 0;i < (POINTS-1);i++)       //POINTS-1    12 POINTS has 11 gap
    {
        if((x_value>=point_x[i]) & (x_value<point_x[i+1]))
        {
            point_index = i;
            break;
            //printf("point_index = %d\n", point_index);
        }
    }

    point_slope = (point_y[point_index+1]-point_y[point_index]) / (point_x[point_index+1]-point_x[point_index]);
    //printf("point_slope = %.2lf\n", point_slope);
    y_value = point_slope*(x_value - point_x[point_index])+point_y[point_index];

    return y_value;   
}

uint16_t GPIO_BL_PWM_Value(void)
{
    uint8_t i,j;
    uint8_t PWM_P = 0;
    uint8_t PWM_N = 0;
    uint16_t PWM_sum = 0;
    uint16_t GPIO_PWM_Value = 0;
    
    //IO_RC0_SetHigh();  // Fan on
    for(j=0;j<4;j++)
    {    
        //IO_RC0_SetHigh();  // Fan on
        for(i=0;i<100;i++)        //100   200     // i==1 1 cycle 50us(commend 17us + delay 33us) ; 200Hz 1 PWM cycle 5ms
        {
            //IO_RC0_SetHigh();  // Fan on
            if(IO_RA0_GetValue()){
                PWM_P++;
                __delay_us(33);   //33   9
            }else{
                PWM_N++;
                __delay_us(33);   //33   9
            }
            //IO_RC0_SetLow();   // Fan off
        }
        //IO_RC0_SetLow();   // Fan off
        __delay_us(1000);
        PWM_sum = PWM_P + PWM_sum;
        PWM_P = 0;
        PWM_N = 0;    
    }

    GPIO_PWM_Value = (PWM_sum >> 2);   // /4 
    //IO_RC0_SetLow();   // Fan off
    return GPIO_PWM_Value;
}

uint16_t PWM_Data_collection(void)
{
    int data_pwm[20] = {0};
    uint16_t PWM_index = 0;
    int count = 0;
    int size = 20;
    int new_pwm = 0;
    for(int i = 0; i < size; i++) {
        //__delay_us(20000);    // 20 ms
        new_pwm = GPIO_BL_PWM_Value();
        data_pwm[PWM_index] = new_pwm;
        PWM_index = (PWM_index + 1) % WINDOW_SIZE;

        if (count < WINDOW_SIZE) {
            count++;
        }
    }
    uint16_t moving_average1 = calculate_moving_average(data_pwm, count);
    //moving_average = moving_average;
    count = 0;
    return moving_average1;
}

uint16_t calculate_moving_average(int *data_pwm_buf, int size)
{
    if(size > WINDOW_SIZE)
        return -1;
    
    long int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += data_pwm_buf[i];
    }
    return (uint16_t)((double)sum / size);
}

uint16_t ALS_Data_collection(void)
{
    int data[20] = {0};
    uint16_t ALS_index = 0;
    int count = 0;
    int size = 20;
    int new_als = 0;
    //__delay_us(50000);    // 50 ms
    for(int i = 0; i < size; i++) {
        new_als = ALS_Read(ALS_1_CTRL_ADDR);
        //__delay_us(1000);    // 1 ms
        data[ALS_index] = new_als;
        ALS_index = (ALS_index + 1) % WINDOW_SIZE;

        if (count < WINDOW_SIZE) {
            count++;
        }
    }
    uint16_t moving_average = calculate_moving_average(data, count);
    //moving_average = moving_average;
    count = 0;
    return moving_average;
}

void ALS_moving_average(void)
{
    int32_t ALS; 
    //__delay_us(500000);    // 500 ms
#if 1                          // 200 ms 取一次
    //if(ALS_error != 1){
        if(counter1 == 0){
            ALS = ALS_Read(ALS_1_CTRL_ADDR);
            //ALS = ALS >> 4;
            //ALS = ALS << 4;
            if(ALS > ALS_Value_Max )
            {
                ALS = ALS_Value_Max;
            }
            counter1 = 1;
        }else{
            counter1 = 0;
        }
    //}
#else
    ALS = ALS_Read(ALS_1_CTRL_ADDR);    
#endif    
    Diff = ALS - Data[Data_current_ALS];
    //Data[Data_current_ALS] = ALS;
    if((Diff < 4) & (Diff > -4))
    {
        Diff = 0;
    }
    moving_average = moving_average - Data[Data_current_ALS];
            
    Data[Data_current_ALS] = Data[Data_current_ALS] + Diff;
    
    moving_average = moving_average + Data[Data_current_ALS];
    
    //moving_average = moving_average + Diff;
    //Data_current_ALS = (Data_current_ALS >= window - 1) ? 0 : Data_current_ALS +1;
    if(Data_current_ALS >= (window - 1))
    {
        Data_current_ALS = 0;
    }else{
        Data_current_ALS++;
    }
            
	ALS_PWM_Value = LUT(moving_average);
	//PWM5_LoadDutyValue(ALS_PWM_Value*4);
    PWM5_LoadDutyValue(ALS_PWM_Value);
}

uint16_t LUT(uint32_t move_average_sum)
{
    //uint16_t move_average;
    uint32_t move_average;
    uint16_t als_pwm_value;
    //move_average = move_average_sum/window;
    //move_average = move_average_sum >> 3;
    move_average = move_average_sum;
    als_pwm_value = linear_interpolation((double) move_average);
    return als_pwm_value;
}
 /**
  End of File
 */

