#ifndef _VT100_PARAM_H_
#define _VT100_PARAM_H_

#define VT100_PARAM_QUEUE_SIZE 8
#define VT100_PARAM_DELIMITER ';'

#include <vt100/extern.h>
#include <common.h>

bool_t vt100_param_add();			/* add values in increment order of rx data */
void vt100_param_default(uint8_t, uint8_t);

#define vt100_param_reset() vt100_param_setcount(0)

#define vt100_param_getcount() (vt100.param[0])
#define vt100_param_setcount(c) (vt100.param[0]=c)

/* parameter number start from 0 */
#define vt100_param_get(i) (vt100.param[i+1])
#define vt100_param_set(i,v) (vt100.param[i+1] = v) /* this set values directly */

#endif
