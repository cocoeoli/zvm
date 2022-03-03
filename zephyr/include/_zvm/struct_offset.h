
/* below code may have copyright risk */
/* ---------------------------------- */

#ifndef __STRUCT_OFFSET_H_
#define __STRUCT_OFFSET_H_

#define 

#define DEFINE(sym, val) \
	asm volatile("\n.ascii \"->" #sym " %0 " #val "\"" : : "i" (val))


#endif
