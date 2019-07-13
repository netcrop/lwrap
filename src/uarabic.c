/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)
void arabicheader(self ** me)
{
    my.currdata->val = (unsigned char)my.readbuff[my.currreadindex->val];
    my.currdata->byteheader = 20;
    my.currdata->wcolcount = ++my.wcolcount;
    my.currdata->wbytecount = ++my.wbytecount;
    my.hbytecount++;
}

inline void farabicmiddlebyte(self ** me)
{
    my.hbytecount++;
    my.hcolcount++;
    my.currdata->wbytecount = ++my.wbytecount;
    my.currdata->wcolcount = my.wcolcount;
}

inline void lbarabicheader(self ** me)
{
    my.currjustify->remain = my.currdata->wcolcount;
}
