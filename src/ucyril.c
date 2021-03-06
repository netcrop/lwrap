/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"

void cyrilheader()
{
    my.currdata->val = (unsigned char)my.readbuff[my.currreadindex->val];
    my.currdata->byteheader = 20;
    my.currdata->wcolcount = ++my.wcolcount;
    my.currdata->wbytecount = ++my.wbytecount;
    my.hbytecount++;
}

inline void fcyrilmiddlebyte()
{
    my.hbytecount++;
    my.hcolcount++;
    my.currdata->wbytecount = ++my.wbytecount;
    my.currdata->wcolcount = my.wcolcount;
}

inline void lbcyrilheader()
{
    my.currjustify->remain = my.currdata->wcolcount;
}
