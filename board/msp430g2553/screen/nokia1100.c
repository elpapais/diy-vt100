#include <diy-vt100/hardware/screen/nokia1100.h>
#include <diy-vt100/hardware.h>

#include <diy-vt100/screen.h>
#include <diy-vt100/setup.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/font/simple.h>

#include <diy-vt100/vt100/cursor.h>

#define CURSOR_STATE HW_PRIV0

/* ============================================================== */

#define _contrast 0x7F

/* VERT ADDR */
#define nokia1100_gotoy(addr) nokia1100_send_cmd(0xB0 | (addr & 0x0F))

#define nokia1100_gotox(addr) \
			/* HORZ ADDR LSB */ \
			nokia1100_send_cmd(0x00 | (addr & 0x0F)); \
			/* HORZ ADDR MSB */ \
			nokia1100_send_cmd(0x18 | ( (addr>>4)))

#define nokia1100_gotoyx(yaddr, xaddr) \
			nokia1100_gotoy(yaddr); \
			nokia1100_gotox(xaddr)

/* INITAL DISPLAY LINE */
#define nokia1100_setinitrow_zero()	nokia1100_send_cmd(0x40  | 0x00)

/* DISPLAY POWER */
#define nokia1100_showpixel_on() nokia1100_send_cmd(0xAE | 0x01)

/* DISPLAY POWER */
#define nokia1100_showpixel_off() nokia1100_send_cmd(0xAE | 0x00); 

#define nokia1100_power_on() \
			nokia1100_showpixel_on(); \
			nokia1100_allpixel_off(); \
			nokia1100_invertpixel_off()

#define nokia1100_power_off() \
			nokia1100_showpixel_off(); \
			nokia1100_allpixel_on()

#define nokia1100_power_partialoff() \
			nokia1100_showpixel_off(); \
			nokia1100_allpixel_off()

/* PIXEL INVERT */
#define nokia1100_invertpixel_on() 	nokia1100_send_cmd(0xA6 | 0x01)

/* PIXEL INVERT */
#define nokia1100_invertpixel_off() nokia1100_send_cmd(0xA6 | 0x00)

/* PIXEL ALL */
#define nokia1100_allpixel_on() nokia1100_send_cmd(0xA4 | 0x01)

/* PIXEL ALL */
#define nokia1100_allpixel_off() nokia1100_send_cmd(0xA4 | 0x00)

#define nokia1100_contrast(value) \
			/* VOP-MSB */ \
			nokia1100_send_cmd(0x20 | (value >> 5)); \
			/* VOP-LSB */ \
			nokia1100_send_cmd(0x80 | (value & 0x1F)) 

/* CHARGE PUMP CONTROL */
#define nokia1100_chargepump_on() nokia1100_send_cmd(0x2F)

/* CHARGE PUMP */
#define nokia1100_chargepump(value) \
			nokia1100_send_cmd(0x3D ); \
			nokia1100_send_cmd(value & 0x03)

/* CHARGE PUMP CONTROL */
#define nokia1100_chargepump_off() nokia1100_send_cmd(0x28 | 0x02)

/* RAM ADDRESSING */
#define nokia1100_addressingmode_vertical() nokia1100_send_cmd(0xAA  | 0x01)

/* RAM ADDRESSING */
#define nokia1100_addressingmode_horizontal() nokia1100_send_cmd(0xAA | 0x00)


void nokia1100_send_cmd (const uint8_t data);
void nokia1100_send_data(const uint8_t *data_array, const uint8_t size);
void nokia1100_full_clear(void);
/* ================================================================ */

const screench_t _E = {'E'};
const screench_t _zeroed = {0};

screench_t nokia1100_buffer[SCREEN_ROW][SCREEN_COL];

static inline uint8_t _nokia1100_char_designer(const col_t i, const row_t j, const uint8_t k);

void
screen_gotorow(row_t r)
{
	nokia1100_gotoy(r);
}

void
screen_gotocol(col_t c)
{
	nokia1100_gotox(c * SCREEN_CHAR_WIDTH);
}

void
screen_splash()
{
	/*const static struct __vt100_char splash_message[SCREEN_ROW][SCREEN_COL] = 
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
	
	nokia1100_buffer_copy(splash_message);
*/
	screen_full_clear();
	
	const static rowprop_t rowp_null;
	const static rowprop_t rowp_0 = {.double_height = TRUE, .double_height_pos = TRUE};
	const static rowprop_t rowp_1 = {.double_height = TRUE, .double_height_pos = FALSE};
	
	for(register row_t i=2; i < SCREEN_ROW; i++)
	{
		vt100_rowprop[i] = rowp_null;
	}
	
	vt100_rowprop[0] = rowp_0;
	vt100_rowprop[1] = rowp_1;
	
	const static uint8_t row_0_1[SCREEN_COL] = {' ', ' ', ' ', ' ', 'd', 'i', 'y', '-', 'v', 't', '1', '0', '0'};
	const static uint8_t row_2[SCREEN_COL] = {' ', 'I', 'R', 'C', ' ', '#', 'd', 'i', 'y', '-','v', 't', '1', '0', '0'};
	
	for(register col_t j=0; j < SCREEN_COL; j++)
	{
		nokia1100_buffer[0][j].data = row_0_1[j];
		nokia1100_buffer[1][j].data = row_0_1[j];
		nokia1100_buffer[2][j].data = row_2[j];
	}

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
	/*row_t i;
	col_t j;
	uint8_t value_no = 0;
	
	bool_t readed_values[16] =
	{
		setting_ishigh(SETTING_DECSCLM), setting_ishigh(SETTING_DECARM), setting_ishigh(SETTING_DECSCNM), setting_ishigh(SETTING_CURSOR),
		setting_ishigh(SETTING_MARGINBELL), setting_ishigh(SETTING_KEYCLICK), setting_ishigh(SETTING_DECANM), setting_ishigh(SETTING_AUTOX),
		setting_ishigh(SETTING_SHIFTED), setting_ishigh(SETTING_DECAWM), setting_ishigh(SETTING_LNM), setting_ishigh(SETTING_DECINLM),
		setting_ishigh(SETTING_PARITYSENSE), setting_ishigh(SETTING_PARITY), setting_ishigh(SETTING_BPC),  0 // setting_ishigh(SETTING_POWER)
	};
	
	for(i = 6; i < 8; i++)
	{
		for(j=2; j < 13; j++)
		{
			if(j > 5 && j < 9)
			{
				continue;
			}
			
			nokia1100_buffer[i][j].data = readed_values[value_no] ? '1' : '0';
			
			if(value_no++ == setup_number)
			{
				vt100_cursor.row = i;
				vt100_cursor.col = j;
			}
		}
		
		vt100_rowprop[i].touch = TRUE;
	}
	
	vt100_rowprop[4].touch = TRUE;
	vt100_rowprop[5].touch = TRUE;
	
	uint8_t bitrate_size = (uint8_t)uart_speed[setting.uart_rx].bitrate[0];
	uint8_t *bitrate = (uint8_t *)uart_speed[setting.uart_rx].bitrate + 1;
	
	for(j=0; j < 6; j++)
	{
		nokia1100_buffer[5][j + 8].data = (j < bitrate_size) ? bitrate[j] : ' ';
	}
	
	
	bitrate_size = (uint8_t)uart_speed[setting.uart_tx].bitrate[0];
	bitrate = (uint8_t *)uart_speed[setting.uart_tx].bitrate + 1;
	
	for(j=0; j < 6; j++)
	{
		nokia1100_buffer[4][j + 8].data = (j < bitrate_size) ? bitrate[j] : ' ';
	}*/
	
#define readvalue_setng(no, i,j, setting) \
	if(setup_number == no) \
	{ \
		vt100_cursor.row = i; \
		vt100_cursor.col = j; \
	}\
	nokia1100_buffer[i][j].data = setting ? '1' : '0'
	
	/* end of macro */
	
	readvalue_setng(0, 6, 2, setting.bits.DECSCLM);
	readvalue_setng(1, 6, 3, setting.bits.DECARM);
	readvalue_setng(2, 6, 4, setting.bits.DECSCNM);
	readvalue_setng(3, 6, 5, setting.bits.CURSOR);
	
	readvalue_setng(4, 6, 9, setting.bits.MARGINBELL);
	readvalue_setng(5, 6, 10, setting.bits.KEYCLICK);
	readvalue_setng(6, 6, 11, setting.bits.DECANM);
	readvalue_setng(7, 6, 12, setting.bits.AUTOX);

	readvalue_setng(8, 7, 2, setting.bits.SHIFTED);
	readvalue_setng(9, 7, 3, setting.bits.DECAWM);
	readvalue_setng(10, 7, 4, setting.bits.LNM);
	readvalue_setng(11, 7, 5, setting.bits.DECINLM);
	
	readvalue_setng(12, 7, 9, setting.bits.PARITYSENSE);
	readvalue_setng(13, 7, 10, setting.bits.PARITY);
	readvalue_setng(14, 7, 11, setting.bits.BPC);
	
	//readvalue_setng(15,7, 11 setting.bits.POWER);
	if(setup_number == 15)
	{
		vt100_cursor.row = 7;
		vt100_cursor.col = 12;
	}
	nokia1100_buffer[7][12].data = '0';
	
	
	uint8_t bitrate_size = (uint8_t)uart_speed[setting.uart_rx].bitrate[0];
	uint8_t *bitrate = (uint8_t *)uart_speed[setting.uart_rx].bitrate + 1;
	
	col_t j;
	
	for(j=0; j < 6; j++)
	{
		nokia1100_buffer[5][j + 8].data = (j < bitrate_size) ? bitrate[j] : ' ';
	}
	
	bitrate_size = (uint8_t)uart_speed[setting.uart_tx].bitrate[0];
	bitrate = (uint8_t *)uart_speed[setting.uart_tx].bitrate + 1;
	
	for(j=0; j < 6; j++)
	{
		nokia1100_buffer[4][j + 8].data = (j < bitrate_size) ? bitrate[j] : ' ';
	}
}

void setupA_refresh()
{
	/* limit to 16 only */
	
	vt100_cursor.row = 6;
	vt100_cursor.col = setup_number;
	
	for(register col_t j=0; j < SCREEN_COL; j++)
	{
		nokia1100_buffer[6][j].data = setting_tab_ishigh(j) ? 'T' : ' ';
	}		
}

void setup_show_wait()
{
	nokia1100_buffer[3][0].data = 'w';
	nokia1100_buffer[3][1].data = 'a';
	nokia1100_buffer[3][2].data = 'i';
	nokia1100_buffer[3][3].data = 't';
}

void setupA_load()
{
	/*const static struct __vt100_char buf[SCREEN_ROW][SCREEN_COL] =  
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
	
	screen_full_copy(buf);*/

	screen_full_clear();
	
	const static rowprop_t rowp_null;
	const static rowprop_t rowp_0 = {.double_height = TRUE, .double_height_pos = TRUE, .double_width = TRUE};
	const static rowprop_t rowp_1 = {.double_height = TRUE, .double_height_pos = FALSE, .double_width = TRUE};
	
	for(register row_t i=2; i < SCREEN_ROW; i++)
	{
		vt100_rowprop[i] = rowp_null;
	}
	
	vt100_rowprop[0] = rowp_0;
	vt100_rowprop[1] = rowp_1;
	
	const static uint8_t data_row_0_1[SCREEN_COL/2] = {'S', 'E', 'T', '-', 'U', 'P', ' ', 'A'};
	register col_t j;
	
	for(j=0; j < SCREEN_COL/2; j++)
	{
		/* ROW 0 */
		nokia1100_buffer[0][j].data = data_row_0_1[j];
		
		/* ROW 1 */
		nokia1100_buffer[1][j].data = data_row_0_1[j];
	}
	
	
	const static uint8_t data_row_2[SCREEN_COL] = {'T', 'O', ' ', 'E', 'X', 'I', 'T', ' ', 'P', 'R', 'E', 'S', 'S', ' ', 'F', '5'};
	const static uint8_t data_row_7[SCREEN_COL] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '1', '2', '3', '4', '5', '6'};
	for(j=0; j < SCREEN_COL; j++)
	{
		/* ROW 2 */
		nokia1100_buffer[2][j].data = data_row_2[j];
		nokia1100_buffer[2][j].prop.underline = TRUE;
		
		/* ROW 6 */
		nokia1100_buffer[6][j].data = '*';
		
		/* ROW 7 */
		nokia1100_buffer[7][j].data = data_row_7[j];
		
		if(!(j < 10))
		{
			nokia1100_buffer[7][j].prop.invert = TRUE;
		}
	}
}

void setupB_load()
{
	/*const static struct __vt100_char buf[SCREEN_ROW][SCREEN_COL] =  
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
	
	screen_full_copy(buf);*/

	screen_full_clear();
	
	const static rowprop_t rowp_null;
	const static rowprop_t rowp_0 = {.double_height = TRUE, .double_height_pos = TRUE, .double_width = TRUE};
	const static rowprop_t rowp_1 = {.double_height = TRUE, .double_height_pos = FALSE, .double_width = TRUE};
	
	for(register row_t i=2; i < SCREEN_ROW; i++)
	{
		vt100_rowprop[i] = rowp_null;
	}
	
	vt100_rowprop[0] = rowp_0;
	vt100_rowprop[1] = rowp_1;
	
	const static uint8_t data_row_0_1[SCREEN_COL/2] = {'S', 'E', 'T', '-', 'U', 'P', ' ', 'B'};
	
	register col_t j;
	
	for(j=0; j < SCREEN_COL/2; j++)
	{
		/* ROW 0 */
		nokia1100_buffer[0][j].data = data_row_0_1[j];
		
		/* ROW 1 */
		nokia1100_buffer[1][j].data = data_row_0_1[j];
	}
	
	const static uint8_t data_row_2[SCREEN_COL] = {'T', 'O', ' ', 'E', 'X', 'I', 'T', ' ', 'P', 'R', 'E', 'S', 'S', ' ', 'F', '5'};
	const static uint8_t data_row_4[SCREEN_COL] = {'T', ' ', 'S', 'P', 'E', 'E', 'D', ' ', '*', '*', '*', '*', '*', '*', '*', '*'};
	const static uint8_t data_row_5[SCREEN_COL] = {'R', ' ', 'S', 'P', 'E', 'E', 'D', ' ', '*', '*', '*', '*', '*', '*', '*', '*'};
	const static uint8_t data_row_6[SCREEN_COL] = {'1', ' ', '*', '*', '*', '*', ' ', '2', ' ', '*', '*', '*', '*', ' ', ' ', ' '};
	const static uint8_t data_row_7[SCREEN_COL] = {'3', ' ', '*', '*', '*', '*', ' ', '4', ' ', '*', '*', '*', '*', ' ', ' ', ' '};
	
	for(j=0; j < SCREEN_COL; j++)
	{
		/* ROW 2 */
		nokia1100_buffer[2][j].data = data_row_2[j];
		nokia1100_buffer[2][j].prop.underline = TRUE;
		
		/* ROW 4 */
		nokia1100_buffer[4][j].data = data_row_4[j];
		
		/* ROW 5 */
		nokia1100_buffer[5][j].data = data_row_5[j];
		
		/* ROW 6 */
		nokia1100_buffer[6][j].data = data_row_6[j];
		
		/* ROW 7 */
		nokia1100_buffer[7][j].data = data_row_7[j];
	}
}
/*
void screen_gotocol(col_t col)
{
	vt100_cursor.col = col;
}

void screen_gotorow(row_t row)
{
	vt100_cursor.row = row;
}*/

void screen_putch(uint8_t data, dataprop_t prop)
{
	/* save data */
	nokia1100_buffer[vt100_cursor.row][vt100_cursor.col].data = data;
	nokia1100_buffer[vt100_cursor.row][vt100_cursor.col].prop = prop;
	
	/* mark as to be printed */
	vt100_rowprop[vt100_cursor.row].touch = TRUE;
}

void screen_refresh()
{
	register row_t i;
	register col_t j;
	register uint8_t k;

	static uint8_t tmp_buffer;//[SCREEN_CHAR_WIDTH];
	
	for(i=0; i < SCREEN_ROW; i++)
	{
		//if(vt100_rowprop[i].touch)
		//{
			screen_gotorow(i);
			screen_gotocol(0);
			
			if(vt100_rowprop[i].double_width)
			{
				for(j=0; j < SCREEN_COL/2; j++)
				{
					/*for(k=0; k < SCREEN_CHAR_WIDTH/2; k++)
					{
						tmp_buffer[(j*SCREEN_CHAR_WIDTH) + (2 * k)] = 
							tmp_buffer[(j*SCREEN_CHAR_WIDTH) + (2 * k) + 1] = 
									_nokia1100_char_designer(i, j, k);
					}
					
					nokia1100_send_data(tmp_buffer, SCREEN_WIDTH);
					
					for(k=0; k < SCREEN_CHAR_WIDTH/2; k++)
					{
						tmp_buffer[(j*SCREEN_CHAR_WIDTH) + (2 * k)] = 
							tmp_buffer[(j*SCREEN_CHAR_WIDTH) + (2 * k) + 1] = 
									_nokia1100_char_designer(i, j, k + (SCREEN_CHAR_WIDTH/2));
					}
					
					nokia1100_send_data(tmp_buffer, SCREEN_WIDTH);*/
					
					for(k=0; k < SCREEN_CHAR_WIDTH; k++)
					{
						//tmp_buffer[(j*SCREEN_CHAR_WIDTH) + k] = _nokia1100_char_designer(i, j, k);
						tmp_buffer = _nokia1100_char_designer(i, j, k);
						nokia1100_send_data(&tmp_buffer, 1);
						nokia1100_send_data(&tmp_buffer, 1);
					}
				}
			}
			else
			{
				for(j=0; j < SCREEN_COL; j++)
				{
					for(k=0; k < SCREEN_CHAR_WIDTH; k++)
					{
						//tmp_buffer[(j*SCREEN_CHAR_WIDTH) + k] = _nokia1100_char_designer(i, j, k);
						tmp_buffer = _nokia1100_char_designer(i, j, k);
						nokia1100_send_data(&tmp_buffer, 1);
					}
					
					//nokia1100_send_data(tmp_buffer, SCREEN_CHAR_WIDTH);
				}
			}
			vt100_rowprop[i].touch = FALSE;
		//}
	}
}

static inline uint8_t _nokia1100_char_designer(const col_t i, const row_t j, const uint8_t k)
{
	register uint8_t send, tmp;
	
	/* design the char */
	send = font_simple_get(nokia1100_buffer[i][j].data, k);
	
	if(vt100_rowprop[i].double_height)
	{
		if(vt100_rowprop[i].double_height_pos)
		{
			tmp = send;
			send = 0x00;
			if(__read(tmp,BIT3))
			{
				__high(send, BIT7|BIT6);
			}
			
			if(__read(tmp,BIT2))
			{
				__high(send, BIT5|BIT4);
			}
			
			if(__read(tmp,BIT1))
			{
				__high(send, BIT3|BIT2);
			}
			
			if(__read(tmp,BIT0))
			{
				__high(send, BIT1|BIT0);
			}
		}
		else
		{
			tmp = send;
			send = 0x00;
			
			if(__read(tmp,BIT4))
			{
				__high(send, BIT1|BIT0);
			}
			
			if(__read(tmp,BIT5))
			{
				__high(send, BIT3|BIT2);
			}
			
			if(__read(tmp,BIT6))
			{
				__high(send, BIT5|BIT4);
			}
			
			if(__read(tmp,BIT7))
			{
				__high(send, BIT7|BIT6);
			}
		}
	}
	
	if(nokia1100_buffer[i][j].prop.underline)
	{
		send |= 0x80;
	}
	
	if(nokia1100_buffer[i][j].prop.invert)
	{
		send ^= 0xFF;
	}
	
	if(j == vt100_cursor.col
		&& setting.bits.CURSOR_STATE 
		&& i == vt100_cursor.row)
	{
		send ^= parm_setting.bits.CURSOR ? 0xFF : 0x80;
	}
	
	return send;
}

void screen_shiftup()
{
	register row_t i;
	register col_t j;
	
	/* shift down data */
	for(i=0; i < SCREEN_ROW - 1; i++)
	{
		for(j=0; j < SCREEN_COL; j++)
		{
			nokia1100_buffer[i][j] = nokia1100_buffer[i + 1][j];
		}
		vt100_rowprop[i] = vt100_rowprop[i + 1];
		vt100_rowprop[i].touch = TRUE;
	}
	
	/* clear first row */
	screen_row_clear(i);
}

void screen_shiftdown()
{
	register row_t i;
	register col_t j;
	
	/* shift down data */
	for(i=SCREEN_COL - 1; i > 0; i--)
	{
		for(j=0; j < SCREEN_COL; j++)
		{
			nokia1100_buffer[i][j] = nokia1100_buffer[i - 1][j];
		}
		vt100_rowprop[i] = vt100_rowprop[i - 1];
		vt100_rowprop[i].touch = TRUE;
	}
	
	/* clear first row */
	screen_row_clear(0);
}

void screen_row_clear(const row_t i)
{
	screen_segment_clear(i, 0, SCREEN_COL - 1);
	nokia1100_gotox(0);
	nokia1100_gotoy(0);
}

void screen_segment_clear(const row_t i, const col_t j_start, const col_t j_end)
{	
	for(col_t j=j_start; j <= j_end; j++)
	{
		nokia1100_buffer[i][j] = _zeroed;
	}
	
	vt100_rowprop[i].touch = TRUE;	
}

void screen_full_clear()
{
	register row_t i;
	register col_t j;

	for(i=0; i < SCREEN_ROW; i++)
	{
		for(j=0; j <= SCREEN_COL; j++)
		{
			nokia1100_buffer[i][j] = _zeroed;
		}
	}
	
	nokia1100_full_clear();
}

void screen_full_E()
{
	register row_t i;
	register col_t j;
	
	for(i=0; i < SCREEN_ROW; i++)
	{
		for(j=0; j < SCREEN_COL; j++)
		{
			nokia1100_buffer[i][j] = _E;
		}
		
		vt100_rowprop[i].touch = TRUE;
	}
}
