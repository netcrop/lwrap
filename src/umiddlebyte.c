/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)

void middlebyte()
{
    me->currdata->val = (unsigned char)me->readbuff[me->currreadindex->val];
    me->currdata->byteheader = me->prevdata->byteheader + 1;
    me->currdata->glyph = me->prevdata->glyph;
    if (me->currdata->byteheader < TWOBYTEMAX) {
        me->hbytecount++;
        me->hcolcount++;
        me->currdata->wbytecount = ++me->wbytecount;
        me->currdata->wcolcount = me->wcolcount;
        return;
    }
    me->hbytecount++;
    me->currdata->wbytecount = me->prevdata->wbytecount + 1;
    me->currdata->wcolcount = 2;
}

inline void lbmiddlebyte()
{
    me->currjustify->remain = me->currdata->wcolcount;
    me->lbdata->annotation = NEWLINE;
}
