/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)

void fourbyteheader()
{
    my.currdata->val = (unsigned char)my.readbuff[my.currreadindex->val];
    my.currdata->byteheader = 40;
    my.wcolcount = my.wbytecount = 0;
    my.currdata->wcolcount = 1;
    my.currdata->wbytecount = 1;
    my.currjustify->wcount++;
    my.hbytecount++;
}

inline void lbfourbyteheader()
{
    my.currjustify->remain = my.currdata->wcolcount;
}
