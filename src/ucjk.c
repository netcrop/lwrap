/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"

void cjkheader()
{
    my.currdata->val = (unsigned char)my.readbuff[my.currreadindex->val];
    my.currdata->byteheader = 30;
    my.currdata->glyph = CJK;
    my.wcolcount = my.wbytecount = 0;
    my.currdata->wcolcount = 2;
    my.currdata->wbytecount = 1;
    my.currjustify->wcount++;
    my.hcolcount += 2;
    my.hbytecount++;
}

inline void lbcjkheader()
{
    my.currjustify->remain = my.currdata->wcolcount;
}
