/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)
void hangulheader()
{
    me->currdata->val = (unsigned char)me->readbuff[me->currreadindex->val];
    me->currdata->byteheader = 30;
    me->currdata->glyph = HANGUL;
    me->wcolcount = me->wbytecount = 0;
    me->currdata->wcolcount = 2;
    me->currdata->wbytecount = 1;
    me->currjustify->wcount++;
    me->hcolcount += 2;
    me->hbytecount++;
}

inline void lbhangulheader()
{
    me->currjustify->remain = me->currdata->wcolcount;
}
