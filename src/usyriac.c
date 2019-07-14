/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)
void syriacheader()
{
    me->currdata->val = (unsigned char)me->readbuff[me->currreadindex->val];
    me->currdata->byteheader = 20;
    me->currdata->wcolcount = ++me->wcolcount;
    me->currdata->wbytecount = ++me->wbytecount;
    me->hbytecount++;
}

inline void fsyriacmiddlebyte()
{
    me->hbytecount++;
    me->hcolcount++;
    me->currdata->wbytecount = ++me->wbytecount;
    me->currdata->wcolcount = me->wcolcount;
}

inline void lbsyriacheader()
{
    me->currjustify->remain = me->currdata->wcolcount;
}
