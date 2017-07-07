#include "flash_storage.h"

volatile uint8_t write_flag = 0;

uint32_t my_data = 0x41424344;
uint16_t file_id = 0x1111;
uint16_t rec_key = 0x2222;

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

ret_code_t fds_test_write(void)
{
		
		//static uint32_t const m_deadbeef[2] = {0xABCDEFAB,0xBAADF00D};
		//uint32_t m_test = 0xEEEEEEEE;
		fds_record_t        record;
		fds_record_desc_t   record_desc;
		fds_record_chunk_t  record_chunk;
		// Set up data.
		record_chunk.p_data         = &my_data;
		record_chunk.length_words   = 1;
		// Set up record.
		record.file_id              = file_id;
		record.key              		= rec_key;
		record.data.p_chunks       = &record_chunk;
		record.data.num_chunks   = 1;
				
		ret_code_t ret = fds_record_write(&record_desc, &record);
		if (ret != FDS_SUCCESS)
		{
				return ret;
		}
		 SEGGER_RTT_printf(0,"Writing Record ID = %d\r\n",record_desc.record_id);
		return NRF_SUCCESS;
}

ret_code_t fds_read(void)
{
		
		fds_flash_record_t  flash_record;
		fds_record_desc_t   record_desc;
		fds_find_token_t    ftok ={0};//Important, make sure you zero init the ftok token
		uint32_t *data;
		uint32_t err_code;
		
		SEGGER_RTT_printf(0,"Start searching... \r\n");
		// Loop until all records with the given key and file ID have been found.
		while (fds_record_find(file_id, rec_key, &record_desc, &ftok) == FDS_SUCCESS)
		{
				err_code = fds_record_open(&record_desc, &flash_record);
				if ( err_code != FDS_SUCCESS)
				{
					return err_code;		
				}
				
				//SEGGER_RTT_printf(0, "p_header address = %x\r\n",flash_record.p_header); 
				SEGGER_RTT_printf(0, "p_data address = %x\r\n",flash_record.p_data); 
				SEGGER_RTT_printf(0,"Found Record ID = %d\r\n",record_desc.record_id);
				SEGGER_RTT_printf(0,"Data = ");
				data = (uint32_t *) flash_record.p_data;
				
				for (uint8_t i=0;i<flash_record.p_header->tl.length_words;i++)
				{
					SEGGER_RTT_printf(0,"0x%8x ",data[i]);
				}
				
				SEGGER_RTT_printf(0,"\r\n");
				// Access the record through the flash_record structure.
				// Close the record when done.
				err_code = fds_record_close(&record_desc);
				if (err_code != FDS_SUCCESS)
				{
					return err_code;	
				}
		}
		return NRF_SUCCESS;
		
}

ret_code_t fds_test_find_and_delete (void)
{
	
		fds_record_desc_t   record_desc;
		fds_find_token_t    ftok;
	
		ftok.page=0;
		ftok.p_addr=NULL;
		// Loop and find records with same ID and rec key and mark them as deleted. 
		while (fds_record_find(file_id, rec_key, &record_desc, &ftok) == FDS_SUCCESS)
		{
			fds_record_delete(&record_desc);
			SEGGER_RTT_printf(0,"Deleted record ID: %d \r\n",record_desc.record_id);
		}
		// call the garbage collector to empty them, don't need to do this all the time, this is just for demonstration
		ret_code_t ret = fds_gc();
		if (ret != FDS_SUCCESS)
		{
				return ret;
		}
		return NRF_SUCCESS;
}

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

