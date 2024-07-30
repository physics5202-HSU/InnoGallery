#ifndef _BH1750FVI_H    /* Guard against multiple inclusion */
#define _BH1750FVI_H

#include "mcc_generated_files/examples/i2c1_master_example.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
//#include "mcc_generated_files/examples/i2c1_master_example.h"
//#include "configuration.h"
//#include "definitions.h"
#define ALS_1_CTRL_ADDR     0x23//0100 0110(0x46) --> 0010 0011(0x23))  ADDR="L"
#define ALS_2_CTRL_ADDR     0x5C//1011 1000(0xB8) --> 0101 1100(0x5C))  ADDR="H"   




//bool ALS_Read(uint8_t i2c1_ctrl_addr, uint16_t *i2c1_pData);
uint16_t ALS_Read(uint8_t i2c1_ctrl_addr);

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

#endif /* _BH1750FVI_H */
