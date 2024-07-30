#include "BH1750FVI.h"
//#include "mcc_generated_files/examples/i2c1_master_example.h"
typedef struct
{
  i2c1_address_t address;
  bool present;
} address_present_t_als;

static i2c1_operations_t rd2RegCompleteHandler_ALS(void *ptr)
{
    I2C1_SetBuffer(ptr,2);
    I2C1_SetDataCompleteCallback(NULL,NULL);
    return I2C1_RESTART_READ;
}
//bool ALS_Read(uint8_t i2c1_ctrl_addr, uint16_t *i2c1_pData)
uint16_t ALS_Read(uint8_t i2c1_ctrl_addr)
{    
//    SYS_CONSOLE_PRINT("ALS_Read [address:0x%02x]  \r\n",i2c1_ctrl_addr);
//    volatile I2C1_TRANSFER_STATUS transferStatusCmd = I2C1_TRANSFER_STATUS_ERROR;
//    int count=0;
//    SERCOM7_I2C_CallbackRegister( I2C1_Callback, (uintptr_t)&transferStatusCmd );
    uint16_t returnValue =0x00; // returnValue is little endian
    address_present_t_als present;
    //------------power on--------------
    uint8_t pwron[1];
    pwron[0] = 0x01;
    while(!I2C1_Open(i2c1_ctrl_addr)); // sit here until we get the bus..
    I2C1_SetDataCompleteCallback(rd2RegCompleteHandler_ALS,&returnValue);
    I2C1_SetBuffer(&pwron[0],1);
    I2C1_SetAddressNackCallback(callbackAddrNak,&present); //NACK polling?
    I2C1_MasterWrite();
    while(I2C1_BUSY == I2C1_Close()); // sit here until finished.    
    
    //------------One Time Measure 4Lx, 16ms--------------
    uint8_t onetimemeasure[1];    
    onetimemeasure[0] = 0x23;
    while(!I2C1_Open(i2c1_ctrl_addr)); // sit here until we get the bus..
    I2C1_SetDataCompleteCallback(rd2RegCompleteHandler_ALS,&returnValue);
    I2C1_SetBuffer(&onetimemeasure[0],1);
    I2C1_SetAddressNackCallback(callbackAddrNak,&present); //NACK polling?
    I2C1_MasterWrite();
    while(I2C1_BUSY == I2C1_Close()); // sit here until finished. 

    //------------Get(Read) Data--------------
    uint8_t myData [2];
    while(!I2C1_Open(i2c1_ctrl_addr)); // sit here until we get the bus..
    I2C1_SetBuffer(&myData[0],2);
    I2C1_MasterRead();
    while(I2C1_BUSY == I2C1_Close()); // sit here until finished.
    
    uint16_t p_value = ((uint16_t)myData[0] << 8) | myData[1];  
    return p_value;
}