#include <diy-vt100/screen.h>
#include <diy-vt100/setup.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/screen/nokia1100.h>
#include <diy-vt100/vt100/buffer.h>
#include <diy-vt100/vt100/cursor.h>
#include <diy-vt100/uart.h>

const uint8_t _contrast = 0x7F;

const bool_t screen_support_invert = TRUE;

void
screen_gotorow(row_t r)
{
	nokia1100_gotoy(r);
}

void
screen_gotocol(col_t c)
{
	nokia1100_gotox(c * screen_char_width);
}

void
screen_splash()
{
	const static struct __vt100_char splash_message[screen_row][screen_col] = 
	{
		{{' ', ROW_DOUBLE_HEIGHT_TOP | ROW_TOUCH}, {}, {}, {}, {'d'}, {'i'}, {'y'}, {'-'}, {'v'}, {'t'}, {'1'}, {'0'}, {'0'}, {' '}, {' '}, {' '}},
		{{' ', ROW_DOUBLE_HEIGHT_BOT | ROW_TOUCH}, {}, {}, {}, {'d'}, {'i'}, {'y'}, {'-'}, {'v'}, {'t'}, {'1'}, {'0'}, {'0'}, {' '}, {' '}, {' '}},
		{{0, ROW_TOUCH}, {'I'}, {'R'}, {'C'}, {' '}, {'#'}, {'d'}, {'i'}, {'y'}, {'-'}, {'v'}, {'t'}, {'1'}, {'0'}, {'0'}},
		{{0, ROW_TOUCH}},
		{{0, ROW_TOUCH}},
		{{0, ROW_TOUCH}},
		{{0, ROW_TOUCH}},
		{{0, ROW_TOUCH}}
	};
	
	//"   diy-vt100    ",
	//"   diy-vt100    ",
	//" IRC #diy-vt100 "
	
	vt100_buffer_copy(splash_message);

	vt100_cursor.col = 0;
	vt100_cursor.row = 3;
}

void screen_init()
{
	/* charge pump on */
	nokia1100_send_cmd(0x2F);

	/* set contrast */
	nokia1100_send_cmd(0x20 | (_contrast >> 5)); /* VOP-MSB */
	nokia1100_send_cmd(0x80 | (_contrast & 0x1F)); /* VOP-LSB */

	/* power on */
	nokia1100_send_cmd(0xAE | 0x01); /* show pixel on */
	nokia1100_send_cmd(0xA4 | 0x00); /* all pixel off */
	nokia1100_send_cmd(0xA6 | 0x00); /* invert pixel on */
}

void screen_invert(bool_t b)
{
	nokia1100_send_cmd(0xA6 | (b ? 0x01 : 0x00));
}

void setupB_refresh()
{
	row_t i;
	col_t j;
	uint8_t value_no = 0;
	
	
	bool_t readed_values[16] =
	{
		setting_ishigh(SETTING_DECSCLM), setting_ishigh(SETTING_DECARM), setting_ishigh(SETTING_DECSCNM), setting_ishigh(SETTING_CURSOR),
		setting_ishigh(SETTING_MARGINBELL), setting_ishigh(SETTING_KEYCLICK), setting_ishigh(SETTING_DECANM), setting_ishigh(SETTING_AUTOX),
		setting_ishigh(SETTING_SHIFTED), setting_ishigh(SETTING_DECAWM), setting_ishigh(SETTING_LNM), setting_ishigh(SETTING_DECINLM),
		setting_ishigh(SETTING_PARITYSENSE), setting_ishigh(SETTING_PARITY), setting_ishigh(SETTING_BPC), /* setting_ishigh(SETTING_POWER) */ 0
	};
	
	for(i = 6; i < 8; i++)
	{
		for(j=2; j < 13; j++)
		{
			if(j > 5 && j < 9)
			{
				continue;
			}
			
			vt100_buffer[i][j].data = readed_values[value_no] ? '1' : '0';
			
			if(value_no++ == setup_number)
			{
				vt100_cursor.row = i;
				vt100_cursor.col = j;
			}
		}
		
		vt100_buffer_row_touch(i);
	}
	
	vt100_buffer_row_touch(4);
	vt100_buffer_row_touch(5);
	
	uint8_t bitrate_size = (uint8_t)uart_speed[setting.uart_rx].bitrate[0];
	uint8_t *bitrate = (uint8_t *)uart_speed[setting.uart_rx].bitrate + 1;
	
	for(j=0; j < 6; j++)
	{
		vt100_buffer[5][j + 8].data = (j < bitrate_size) ? bitrate[j] : ' ';
	}
	
	
	bitrate_size = (uint8_t)uart_speed[setting.uart_tx].bitrate[0];
	bitrate = (uint8_t *)uart_speed[setting.uart_tx].bitrate + 1;
	
	for(j=0; j < 6; j++)
	{
		vt100_buffer[4][j + 8].data = (j < bitrate_size) ? bitrate[j] : ' ';
	}
}

void setupA_refresh()
{
	col_t j;
	vt100_cursor.row = 6;
	vt100_cursor.col = setup_number;
	
	for(j=0; j < 16; j++)
	{
		vt100_buffer[6][j].data = setting_tab_ishigh(j) ? 'T' : ' ';
	}		
}

void setup_save()
{
	col_t j = 0;
	const static struct __vt100_char saving_message[screen_col] = {{'S', ROW_TOUCH}, {'a'}, {'v'}, {'e'}, {'d'}, {'.'}};

	/* start saving */
	setting_store();

	for(j = 0; j < screen_col; j++)
	{
		vt100_buffer[3][j] = saving_message[j];
	}
}

void setupA_load()
{
	const static struct __vt100_char buf[screen_row][screen_col] =  
	{
		{{'S', ROW_DOUBLE_WIDTH|ROW_DOUBLE_HEIGHT_TOP|ROW_TOUCH}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'A'}},
		{{'S', ROW_DOUBLE_WIDTH|ROW_DOUBLE_HEIGHT_BOT|ROW_TOUCH}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'A'}},
		{{'T', DATA_UNDERLINE|ROW_TOUCH}, {'O', DATA_UNDERLINE}, {' ', DATA_UNDERLINE}, {'E', DATA_UNDERLINE}, {'X', DATA_UNDERLINE}, {'I', DATA_UNDERLINE}, {'T', DATA_UNDERLINE}, {' ', DATA_UNDERLINE}, {'P', DATA_UNDERLINE}, {'R', DATA_UNDERLINE}, {'E', DATA_UNDERLINE}, {'S', DATA_UNDERLINE}, {'S', DATA_UNDERLINE}, {' ', DATA_UNDERLINE}, {'S', DATA_UNDERLINE}, {'2', DATA_UNDERLINE}},
		{{0, ROW_TOUCH}},
		{{0, ROW_TOUCH}},
		{{0, ROW_TOUCH}},
		{{'*', ROW_TOUCH}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}},
		{{'1', ROW_TOUCH}, {'2'}, {'3'}, {'4'}, {'5'}, {'6'}, {'7'}, {'8'}, {'9'}, {'0'}, {'1', DATA_INVERSE}, {'2', DATA_INVERSE}, {'3', DATA_INVERSE}, {'4', DATA_INVERSE}, {'5', DATA_INVERSE}, {'6', DATA_INVERSE}}
	};
	
	vt100_buffer_copy(buf);
}

void setupB_load()
{
	const static struct __vt100_char buf[screen_row][screen_col] =  
	{
		{{'S', ROW_DOUBLE_WIDTH|ROW_DOUBLE_HEIGHT_TOP|ROW_TOUCH}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'B'}},
		{{'S', ROW_DOUBLE_WIDTH|ROW_DOUBLE_HEIGHT_BOT|ROW_TOUCH}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'B'}},
		{{'T', DATA_UNDERLINE|ROW_TOUCH}, {'O', DATA_UNDERLINE}, {' ', DATA_UNDERLINE}, {'E', DATA_UNDERLINE}, {'X', DATA_UNDERLINE}, {'I', DATA_UNDERLINE}, {'T', DATA_UNDERLINE}, {' ', DATA_UNDERLINE}, {'P', DATA_UNDERLINE}, {'R', DATA_UNDERLINE}, {'E', DATA_UNDERLINE}, {'S', DATA_UNDERLINE}, {'S', DATA_UNDERLINE}, {' ', DATA_UNDERLINE}, {'S', DATA_UNDERLINE}, {'2', DATA_UNDERLINE}},
		{{0, ROW_TOUCH}},
		{{'T', ROW_TOUCH}, {' '}, {'S'}, {'P'}, {'E'}, {'E'}, {'D'}, {' '}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'} },
		{{'R', ROW_TOUCH}, {' '}, {'S'}, {'P'}, {'E'}, {'E'}, {'D'}, {' '}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'} },
		{{'1', ROW_TOUCH}, {' '}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {' '}, {'2'}, {' '}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE} },
		{{'3', ROW_TOUCH}, {' '}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {' '}, {'4'}, {' '}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE} }
	};
	
	vt100_buffer_copy(buf);
}
