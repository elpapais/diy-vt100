#include <setup.h>
#include <param.h>
#include <nokia1100.h>
#include <vt100/buffer.h>

struct __state *setup_state_save;

const struct __state
setup_state_A[] = 
{
	state_noparam	(0, setup_state_worker),
	
	state_select	(ASCII_ESCAPE, setup_state_arrow),
	state_noparam	('5', setup_switch_to_B),
	state_noparam	('6', setup_A_flip),
	state_end()
};

const struct __state
setup_state_B[] = 
{
	state_noparam	(0, setup_state_worker),
	
	state_select	(ASCII_ESCAPE, setup_state_arrow),
	state_noparam	('5', setup_switch_to_A),
	state_noparam	('6', setup_B_flip),
	state_end()
};

const struct __state
setup_state_arrow[] = 
{
	state_noparam	(0, setup_state_worker),
	
	state_select	('O', setup_state_arrow_select),
	state_select	('?', setup_state_arrow_select),
	
	state_noparam	('A', setup_arrow_up),
	state_noparam	('B', setup_arrow_down),
	state_noparam	('C', setup_arrow_right),
	state_noparam	('D', setup_arrow_left),
	state_end		()
};

const struct __state
setup_state_arrow_select[] =
{
	state_noparam	(0, setup_state_worker),
	
	state_noparam	('A', setup_arrow_up),
	state_noparam	('B', setup_arrow_down),
	state_noparam	('C', setup_arrow_right),
	state_noparam	('D', setup_arrow_left),
};

void setup_state_worker()
{	
	switch((int)state_iterate->cb)
	{
		case 0:
		case 1:
			/* ignore (missing or instructed to ignored) */
			if(!(state_current == setup_state_A) 
				&& !(state_current == setup_state_B))
			{
				state_current = setup_state_save;
			}
		return;
		
		case 2:
			if(state_current == setup_state_A 
				|| state_current == setup_state_B)
			{
				setup_state_save = state_current;
				state_current = (struct __state *)state_iterate->arg.state;
			}
		break;
		
		default:
			state_iterate->cb();
			
			/* restore state */
			state_current = setup_state_save;
		break;
	}
}

void setup_arrow_up()
{
	/* increase contrast */
	
	if(setup_setting.contrast < NOKIA1100_CONTRAST_MAX)
	{
		setup_setting.contrast++;
	}
	
	nokia1100_contrast(setup_setting.contrast);
}

void setup_arrow_down()
{
	/* decrease contrast */
	if(setup_setting.contrast > NOKIA1100_CONTRAST_MIN)
	{
		setup_setting.contrast--;
	}
	
	nokia1100_contrast(setup_setting.contrast);
}

void setup_arrow_left()
{
	/* select left value */
}

void setup_arrow_right()
{
	/* select right value */
}

void setup_A_flip()
{
	/* flip values in setup A, 5 was pressed */
}

void setup_B_flip()
{
	/* flip values in setup B, 5 was pressed */
}

void setup_switch_to_A()
{
	state_current = (struct __state *)setup_state_A;
	vt100_buffer_copy(buffer_setupA);
}

void setup_switch_to_B()
{
	state_current = (struct __state *)setup_state_B;
	vt100_buffer_copy(buffer_setupB);
}
