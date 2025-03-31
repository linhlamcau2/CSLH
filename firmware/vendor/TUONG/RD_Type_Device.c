/*
 * RD_Type_Device.c
 *
 *  Created on: Sep 24, 2024
 *      Author: PC5
 */

#include "RD_Type_Device.h"
#include "RD_MessData.h"
#include "../mesh/RD_Lib.h"


Flash_Save_Type_GW Flash_Save_Type_Val;
Flash_Save_MS58_t  Flash_Save_MS58 = {{0}};
Flash_Save_Training flash_save_training = {{0}};

void RD_Flash_Save_GW(uint16_t GW_ADDR){
	Flash_Save_Type_Val.GWID[1] = (uint8_t) (GW_ADDR>>8 & 0xff);
	Flash_Save_Type_Val.GWID[0] = (uint8_t) (GW_ADDR & 0xff);

	flash_erase_sector(RD_GW_FLASH_AREA);
	flash_write_page(RD_GW_FLASH_AREA, sizeof(Flash_Save_Type_Val), (uint8_t *) (&Flash_Save_Type_Val.Used[0]));
}

void RD_Flash_Save_Type(uint8_t MainType, uint8_t Feature, uint8_t Name){
	Flash_Save_Type_Val.MainType = MainType;
	Flash_Save_Type_Val.Feature = Feature;
	Flash_Save_Type_Val.Name = Name;

	flash_erase_sector(RD_GW_FLASH_AREA);
	flash_write_page(RD_GW_FLASH_AREA, sizeof(Flash_Save_Type_Val), (uint8_t *) (&Flash_Save_Type_Val.Used[0]));
}

void RD_Clean_Flash_Type(void){
	Flash_Save_Type_Val.Used[0] = RD_CHECK_FLASH_H;
	Flash_Save_Type_Val.Used[1] = RD_CHECK_FLASH_L;
	Flash_Save_Type_Val.Used[2] = RD_CHECK_FLASH_H;
	Flash_Save_Type_Val.Used[3] = RD_CHECK_FLASH_L;

	Flash_Save_Type_Val.GWID[1] = (uint8_t) (RD_GATEWAY_ADDR>>8 & 0xff);
	Flash_Save_Type_Val.GWID[0] = (uint8_t) (RD_GATEWAY_ADDR & 0xff);
	Flash_Save_Type_Val.MainType = MAINTYPE;
	Flash_Save_Type_Val.Feature = FEATURE;
	Flash_Save_Type_Val.Name = NAME;

	flash_erase_sector(RD_GW_FLASH_AREA);
	flash_write_page(RD_GW_FLASH_AREA, sizeof(Flash_Save_Type_Val), (uint8_t *) (&Flash_Save_Type_Val.Used[0]));
}

void RD_Flash_Type_Init(void){
	flash_read_page(RD_GW_FLASH_AREA, sizeof(Flash_Save_Type_Val), (uint8_t *) (&Flash_Save_Type_Val.Used[0]));
	if(Flash_Save_Type_Val.Used[0] != RD_CHECK_FLASH_H && Flash_Save_Type_Val.Used[1] != RD_CHECK_FLASH_L
		&& Flash_Save_Type_Val.Used[2] != RD_CHECK_FLASH_H && Flash_Save_Type_Val.Used[3] != RD_CHECK_FLASH_L){
		RD_Clean_Flash_Type();
	}else{
		RD_GATEWAY_ADDR = Flash_Save_Type_Val.GWID[1] << 8 | Flash_Save_Type_Val.GWID[0];

	}
}

void RD_Flash_Clean_Training(void){
	flash_save_training.User[0] = RD_CHECK_FLASH_H;
	flash_save_training.User[1] = RD_CHECK_FLASH_L;
	flash_save_training.User[2] = RD_CHECK_FLASH_H;
	flash_save_training.User[3] = RD_CHECK_FLASH_L;

	flash_save_training.minute = 0;
	flash_save_training.step = 1;
	flash_save_training.rd_flag_test_mode = 1;

	flash_erase_sector(RD_TRAINING_FLASH_AREA);
	flash_write_page(RD_TRAINING_FLASH_AREA, RD_TRAINING_FLASH_SIZE, (unsigned char *)(&flash_save_training.User[0]));
}

void Init_Flash_Training(void){
#if TRAINING_EN
	flash_read_page(RD_TRAINING_FLASH_AREA, RD_TRAINING_FLASH_SIZE, (unsigned char *)(&flash_save_training.User[0]));
	if(flash_save_training.User[0] != RD_CHECK_FLASH_H && flash_save_training.User[1] != RD_CHECK_FLASH_L &&
		flash_save_training.User[2] != RD_CHECK_FLASH_H && flash_save_training.User[3] != RD_CHECK_FLASH_L){
		RD_Flash_Clean_Training();
	}

	RD_LOG("time minute start: %d\n",flash_save_training.minute);
#else
	flash_save_training.rd_flag_test_mode = 0;
#endif

}

void RD_Write_Flash_Training(void){
	flash_erase_sector(RD_TRAINING_FLASH_AREA);
	flash_write_page(RD_TRAINING_FLASH_AREA, RD_TRAINING_FLASH_SIZE, (unsigned char *)(&flash_save_training.User[0]));
}

//RD_EDIT LOG UART
void RD_LOG(const char *format, ...){
	char out[256];
	char *p = &out[0];
	va_list args;
	va_start( args, format );
	print(&p, format, args);
	uart_Csend(out);
}
