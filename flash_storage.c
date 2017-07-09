#include "flash_storage.h"
#include "remote.h"


volatile uint8_t write_flag = 0;

uint16_t file_id = 0x0000;
uint16_t file_id_clk = 0x0001;

uint16_t fds_rk_init = 0x0001;
uint16_t fds_rk_clock = 0x1111;


uint16_t fds_rk_cor1 = 0x0010;
uint16_t fds_rk_cor2 = 0x0011;
uint16_t fds_rk_cor3 = 0x0012;

uint32_t fds_is_values_init = 0;
uint32_t life_counter = 1;

void fds_evt_handler(fds_evt_t const * const p_fds_evt)
{
    switch (p_fds_evt->id)
    {
        case FDS_EVT_INIT:
            if (p_fds_evt->result != FDS_SUCCESS)
            {
                // Initialization failed.
            }
            break;
				case FDS_EVT_WRITE:
						if (p_fds_evt->result == FDS_SUCCESS)
						{
							write_flag=1;
						}
						break;
        default:
            break;
    }
}



void fds_init_flash(uint32_t* value, uint16_t file_id, uint16_t rec_key)
{
	uint32_t err_code;
	err_code = fds_write_value(value, file_id, rec_key);
	APP_ERROR_CHECK(err_code);
	while(write_flag == 0);
}

void fds_init_values(void)
{
	fds_get_data(&fds_is_values_init, file_id, fds_rk_init);
	if(fds_is_values_init != 1)
	{
		fds_init_flash(&pwm_value, file_id, fds_rk_cor1);
		fds_init_flash(&pwm_value2, file_id, fds_rk_cor2);
		fds_init_flash(&life_counter, file_id, fds_rk_clock);
		fds_is_values_init = 1;
		fds_init_flash(&fds_is_values_init, file_id, fds_rk_init);
		
	}
	else
	{
		SEGGER_RTT_printf(0, "the values already initialized\r\n");
	}
}


ret_code_t fds_write_value(uint32_t* value, uint16_t file_id, uint16_t rec_key)
{
		fds_record_desc_t record_desc;
		fds_record_t        record;
		fds_record_chunk_t  record_chunk;
		// Set up data.
		record_chunk.p_data         = value;
		record_chunk.length_words   = 1;
		// Set up record.
		record.file_id              = file_id;
		record.key              		= rec_key;
		record.data.p_chunks       = &record_chunk;
		record.data.num_chunks   = 1;
		write_flag = 0;
				
	  ret_code_t ret = fds_record_write(&record_desc, &record);
		if (ret != FDS_SUCCESS)
		{
				return ret;
		}
		 SEGGER_RTT_printf(0,"Writing Record ID = %d, value = %d\r\n",record_desc.record_id, *value);
		return NRF_SUCCESS;
}


ret_code_t fds_update_value(uint32_t* value, uint16_t file_id, uint16_t rec_key)
{
		fds_record_desc_t record_desc;
		fds_record_t        record;
		fds_record_chunk_t  record_chunk;
		// Set up data.
		record_chunk.p_data         = value;
		record_chunk.length_words   = 1;
		// Set up record.
		record.file_id              = file_id;
		record.key              		= rec_key;
		record.data.p_chunks     	  = &record_chunk;
		record.data.num_chunks 		  = 1;
		fds_find_token_t    ftok ={0};//Important, make sure you zero init the ftok token
		
		fds_record_find(file_id, rec_key, &record_desc, &ftok);
		ret_code_t ret = fds_record_update(&record_desc, &record);
		if (ret != FDS_SUCCESS)
		{
				return ret;
		}
		SEGGER_RTT_printf(0,"REC = %d, value = %d\r\n",record_desc.record_id, *value);
		return NRF_SUCCESS;
}



ret_code_t fds_read_value (uint32_t* data, uint16_t file_id, uint16_t rec_key)
{
	  fds_record_desc_t record_desc;
		fds_flash_record_t  flash_record;
		fds_find_token_t    ftok ={0};//Important, make sure you zero init the ftok token
		uint32_t err_code;
		
		SEGGER_RTT_printf(0,"Start new searching... \r\n");
		fds_record_find(file_id, rec_key, &record_desc, &ftok);
		err_code = fds_record_open(&record_desc, &flash_record);
		data = (uint32_t *) flash_record.p_data;
				
		SEGGER_RTT_printf(0,"data = \r\n", *data);
		err_code = fds_record_close(&record_desc);
		APP_ERROR_CHECK(err_code);
		
		return NRF_SUCCESS;
}

ret_code_t fds_get_data(uint32_t* value, uint16_t file_id, uint16_t rec_key)
{
	  fds_record_desc_t record_desc;
		fds_flash_record_t  flash_record;
		fds_find_token_t    ftok ={0};//Important, make sure you zero init the ftok token
		uint32_t err_code;
		
		//SEGGER_RTT_printf(0,"Start getting data... \r\n");
		fds_record_find(file_id, rec_key, &record_desc, &ftok);
		err_code = fds_record_open(&record_desc, &flash_record);
		if (err_code != FDS_SUCCESS)
		{
				return err_code;
		}
		*value = *((uint32_t *) flash_record.p_data);
				
		//SEGGER_RTT_printf(0,"I got Data_ = %d", *value);
		//SEGGER_RTT_printf(0,"\r\n");
		err_code = fds_record_close(&record_desc);
		if (err_code != FDS_SUCCESS)
		{
				return err_code;
		}
		return NRF_SUCCESS;
	//	APP_ERROR_CHECK(err_code);
}




//ret_code_t fds_test_find_and_delete (void)
//{
//	
//		//fds_record_desc_t   record_desc;
//		fds_find_token_t    ftok;
//	
//		ftok.page=0;
//		ftok.p_addr=NULL;
//		// Loop and find records with same ID and rec key and mark them as deleted. 
//		while (fds_record_find(file_id, rec_key, &record_desc, &ftok) == FDS_SUCCESS)
//		{
//			fds_record_delete(&record_desc);
//			SEGGER_RTT_printf(0,"Deleted record ID: %d \r\n",record_desc.record_id);
//		}
//		// call the garbage collector to empty them, don't need to do this all the time, this is just for demonstration
//		ret_code_t ret = fds_gc();
//		if (ret != FDS_SUCCESS)
//		{
//				return ret;
//		}
//		return NRF_SUCCESS;
//}

ret_code_t fds_test_init (void)
{
	
	
	
		ret_code_t ret = fds_register(fds_evt_handler);
		if (ret != FDS_SUCCESS)
		{
					return ret;
				
		}
		ret = fds_init();
		if (ret != FDS_SUCCESS)
		{
				return ret;
		}
		
		return NRF_SUCCESS;
		
}

