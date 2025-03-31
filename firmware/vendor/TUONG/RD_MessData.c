/*
 * RD_MessData.c
 *
 *  Created on: Sep 9, 2024
 *      Author: PC5
 */

#include "RD_MessData.h"
#include "RD_Secure.h"
#include "../common/light.h"
#include "../common/lighting_model.h"
#include "../mesh/RD_Lib.h"
#include "RD_Type_Device.h"

#include "../common/generic_model.h"

RD_Type_Device_Message *RD_Mess_Temp_Receive;
RD_Type_Device_Message RD_Mess_Recevie;
RD_Save_GW_Address RD_Save_GW_Addr;
RD_Rsp_GW_Address RD_Rsp_GW_Addr;


uint8_t *BuffRec;
uint16_t RD_GATEWAY_ADDR = 0x0001;

_Bool flag_kickout_all = FALSE;


u16 rd_time_sche = 0;
u32 rd_time_start_sche = 0;

int RD_Messenger_Mess(u8 *par, int par_len, mesh_cb_fun_par_t * cb_par) {
	RD_Mess_Temp_Receive = (RD_Type_Device_Message *) (&par[0]);
	RD_Mess_Recevie = *RD_Mess_Temp_Receive;
	u16 Header = RD_Mess_Recevie.Header[1] << 8 | RD_Mess_Recevie.Header[0];
	switch (Header) {

	case RD_SET_TYPE_DEVICE:
		//RD_LOG("SET TYPE DEVICE Name: 0x%04X", NAME);
		RD_Mess_Recevie.Header[0] = 0x01;
		RD_Mess_Recevie.Header[1] = 0x00;
		RD_Mess_Recevie.MainType = MAINTYPE;
		RD_Mess_Recevie.Feature = FEATURE;
		RD_Mess_Recevie.Name = NAME;
		RD_Mess_Recevie.Future[0] = 0x00;
		RD_Mess_Recevie.Future[1] = VERSION_MAIN;
		RD_Mess_Recevie.Future[2] = VERSION_SUB;

		RD_Flash_Save_Type(RD_Mess_Recevie.MainType, RD_Mess_Recevie.Feature,
				RD_Mess_Recevie.Name);

		BuffRec = (uint8_t *) (&RD_Mess_Recevie.Header[0]);
		mesh_tx_cmd2normal_primary(cb_par->op_rsp, BuffRec, 8, cb_par->adr_src,
				2);
		break;
	case RD_SAVE_GATEWAY_ADDRESS:
		//RD_LOG("SAVE GW\n");
		RD_GATEWAY_ADDR = saveGatewayAddr(&par[2], cb_par->adr_src);
		RD_Save_GW_Addr.GWID[0] = (uint8_t) (RD_GATEWAY_ADDR & 0xff);
		RD_Save_GW_Addr.GWID[1] = (uint8_t) (RD_GATEWAY_ADDR >> 8 & 0xff);
		RD_Flash_Save_GW(RD_GATEWAY_ADDR);

		RD_Rsp_GW_Addr.Header[0] = 0x02;
		RD_Rsp_GW_Addr.Header[1] = 0x00;
		RD_Rsp_GW_Addr.GWID[0] = RD_Save_GW_Addr.GWID[0];
		RD_Rsp_GW_Addr.GWID[1] = RD_Save_GW_Addr.GWID[1];
		RD_Rsp_GW_Addr.Future[0] = PROVIDER_MAIN;
		RD_Rsp_GW_Addr.Future[1] = PROVIDER_SUB;
		RD_Rsp_GW_Addr.Future[2] = 0x00;
		RD_Rsp_GW_Addr.Future[3] = 0x00;

		BuffRec = (uint8_t *) (&RD_Rsp_GW_Addr.Header[0]);
		mesh_tx_cmd2normal_primary(cb_par->op_rsp, BuffRec, 8, cb_par->adr_src, 2);
		break;
	case RD_KICKOUT_ALL:
		if (is_provision_success()) {
			flag_kickout_all = TRUE;
		}
		break;
	case RD_PROVISION_AES:
		//RD_LOG("KIEM TRA BAO MAT\n");
		if (is_provision_success()) {
			flash_save_secure.flag_check_mess = 1;
			if (RD_AesreCheck(cb_par->adr_dst, &par[2])) {
				flash_save_secure.flag_process_aes = ENCRYPT_OK;
				//RD_LOG("OK HC\n");

				RD_Mess_Recevie.Header[0] = 0x03;
				RD_Mess_Recevie.Header[1] = 0x00;
				RD_Mess_Recevie.MainType = MAINTYPE;
				RD_Mess_Recevie.Feature = FEATURE;
				RD_Mess_Recevie.Name = NAME; // NAME
				RD_Mess_Recevie.Future[0] = 0x00;
				RD_Mess_Recevie.Future[1] = VERSION_MAIN;
				RD_Mess_Recevie.Future[2] = VERSION_SUB;

				BuffRec = (uint8_t *) (&RD_Mess_Recevie.Header[0]);
				mesh_tx_cmd2normal_primary(cb_par->op_rsp, BuffRec, 8,
						cb_par->adr_src, 2);

			} else {
				flash_save_secure.flag_process_aes = ENCRYPT_ERR;
				//RD_LOG("MA HOA SAI\n");

				RD_Mess_Recevie.Header[0] = 0x03;
				RD_Mess_Recevie.Header[1] = 0x00;
				RD_Mess_Recevie.MainType = 0xff;
				RD_Mess_Recevie.Feature = 0xfe;
				RD_Mess_Recevie.Name = 0xff; // NAME
				RD_Mess_Recevie.Future[0] = 0xfe;
				RD_Mess_Recevie.Future[1] = 0xff;
				RD_Mess_Recevie.Future[2] = 0xfe;

				BuffRec = (uint8_t *) (&RD_Mess_Recevie.Header[0]);
				mesh_tx_cmd2normal_primary(cb_par->op_rsp, BuffRec, 8,
						cb_par->adr_src, 2);
			}
			//RD_LOG("check_provision: %d\n", flash_save_secure.flag_process_aes);
		}

		break;
	}
	return 0;
}

void Remote_Control(u8 *par, int len,u8 need_rsp, u16 addr_rsp)
{
	u8 mode = par[1];
	u8 up_down = par[3];
	u8 delta = par[4];
	if(mode == REMOTE_CONTROL_DIM)
	{
		u16 light_set = 0;
		u16 light_cur = light_g_level_present_get_u16(0, 0);
//		u16 cct_cur = light_ctl_temp_prensent_get(0);
		u16 cct_cur = 0;
		if(up_down == REMOTE_CONTROL_UP)
		{
			light_set = ((0xffff - light_cur ) > (delta * 0xffff ) / 100) ?  (light_cur + (delta * 0xffff ) / 100) : 0xffff;
		}
		else if(up_down == REMOTE_CONTROL_DOWN)
		{
			light_set = (light_cur - (delta * 0xffff ) / 100 > RD_LIGHT_30_PERCENT)  ? (light_cur - (delta * 0xffff ) / 100) : RD_LIGHT_30_PERCENT;
		}

		u8 buff[8];
		buff[0] = RD_REMOTE_CONTROL;
		buff[1] = ct_flag;
		buff[2] = up_down;
		buff[3] = delta;
		buff[4] = light_set & 0xff;
		buff[5] = light_set >> 8;
		buff[6] = cct_cur & 0xff;
		buff[7] = cct_cur >> 8;

		if(need_rsp)
		{
			mesh_tx_cmd2normal_primary(LIGHTNESS_LINEAR_STATUS, buff, 8, addr_rsp, 2);
		}
		st_pub_list_t pub_list = {{0}};
		mesh_cmd_lightness_set_t p_set_light;
		p_set_light.lightness = light_set;

		lightness_set(&p_set_light, 3, 0, 0, 0, &pub_list);
	}
}

void Answer_Info(u8 *par, int len, u16 addr_rsp)
{
	u8 buff[8] = {0};
	u8 stt = light_g_onoff_present_get(0);
	u16 dim = light_g_level_present_get_u16(0, 0);
	u16 cct = 0;
	buff[0] = RD_HC_REQUEST_INFO;
	buff[1] = stt << 4 | 0x01;
	buff[2] = dim & 0xff;
	buff[3] = dim >> 8;
	buff[4] = cct & 0xff;
	buff[5] = cct >> 8;

	mesh_tx_cmd2normal_primary(LIGHTNESS_LINEAR_STATUS, buff, 8, addr_rsp, 2);
}

void Remote_Sched(u8 *par, int len,u8 need_rsp, u16 addr_rsp)
{
	u8 enable_sche = par[1];
	rd_time_sche = enable_sche ? (par[3] << 8 | par[4]) : 0;
	rd_time_start_sche = clock_time_s();

	if(need_rsp)
	{
		mesh_tx_cmd2normal_primary(LIGHTNESS_LINEAR_STATUS, par, 8, addr_rsp, 2);
	}
}

void rd_handle_schedule_off()
{
	if(rd_time_sche)
	{
		if(clock_time_s() - rd_time_start_sche > 60 * rd_time_sche)
		{
			rd_time_sche = 0;
			st_pub_list_t pub_list = {{0}};
			mesh_cmd_g_onoff_set_t p_set;
			p_set.onoff = 0;

			g_onoff_set(&p_set, 2, 0, 0, 0, &pub_list);
		}
	}
}

int RD_mesh_cmd_sig_lightness_linear_set(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
	u8 Header = par[0];
	u8 need_rsp = (cb_par->op_rsp != STATUS_NONE) ? 1: 0;

	RD_LOG("header: %d\n",Header);
	switch(Header){
		case RD_REMOTE_CONTROL:
			Remote_Control(par,par_len,need_rsp,cb_par ->adr_src);
			break;
		case RD_HC_REQUEST_INFO:
			Answer_Info(par,par_len,cb_par ->adr_src);
		break;

		case RD_REMOTE_CTL_MODE:
			par[1] = 0;
		    if(need_rsp){
				mesh_tx_cmd2normal_primary(LIGHTNESS_LINEAR_STATUS, par, 8, cb_par ->adr_src, 2);
		    }
		break;
		case RD_REMOTE_SCHED:
			Remote_Sched(par,par_len,need_rsp,cb_par ->adr_src);
			break;
	}
	return 0;
}
uint16_t saveGatewayAddr(uint8_t *para, uint16_t srcAddr) {
	uint16_t GW_Addr = 0x0001;
	if (para[0] || para[1]) {
		GW_Addr = para[1] << 8 | para[0];
	} else {
		GW_Addr = srcAddr;
	}
	return GW_Addr;
}


