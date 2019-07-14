/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)
void greekheader()
{
    me->currdata->val = (unsigned char)me->readbuff[me->currreadindex->val];
    me->currdata->byteheader = 20;
    me->currdata->wcolcount = ++me->wcolcount;
    me->currdata->wbytecount = ++me->wbytecount;
    me->hbytecount++;
}

inline void fgreekmiddlebyte()
{
    me->hbytecount++;
    me->hcolcount++;
    me->currdata->wbytecount = ++me->wbytecount;
    me->currdata->wcolcount = me->wcolcount;
}

inline void lbgreekheader()
{
    me->currjustify->remain = me->currdata->wcolcount;
}
