/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)

void alnum()
{
    if (me->prevdata->byteheader > TWOBYTEMAX) {
        me->currdata->val = (unsigned char)me->readbuff[me->currreadindex->val];
        me->currdata->byteheader = 10;
        me->hbytecount++;
        me->hcolcount++;
        me->currjustify->wcount++;
        me->currdata->wbytecount = me->wbytecount = 1;
        me->currdata->wcolcount = me->wcolcount = 1;
        return;
    }
    me->currdata->val = (unsigned char)me->readbuff[me->currreadindex->val];
    me->currdata->byteheader = 10;
    me->hbytecount++;
    me->hcolcount++;
    me->currdata->wbytecount = ++me->wbytecount;
    me->currdata->wcolcount = ++me->wcolcount;
}

void space()
{
    if (me->prevdata->val == SPACE) {
        me->wbytecount = 0;
        me->wcolcount = 0;
        return;
    }
    if (me->prevdata->val == NEWLINE
        && (unsigned char)me->readbuff[me->currreadindex->incre->val] !=
        SYMBOLMIN) {
        me->wbytecount = 0;
        me->wcolcount = 0;
        return;
    }
    if ((unsigned char)me->readbuff[me->currreadindex->incre->val] == SPACE) {
        me->wbytecount = 0;
        me->wcolcount = 0;
        return;
    }
    me->currdata->val = SPACE;
    me->currdata->byteheader = 10;
    me->hbytecount++;
    me->hcolcount++;
    me->currjustify->wcount++;
    me->currdata->wbytecount = me->wbytecount = 0;
    me->currdata->wcolcount = me->wcolcount = 0;
}

void formfeed()
{
    me->currdata->byteheader = 10;
    me->currdata->val = NEWLINE;
    me->hbytecount++;
    me->hcolcount = me->hcolsize + 1;
    me->currdata->wbytecount = me->wbytecount = 0;
    me->currdata->wcolcount = me->wcolcount = 0;
}

void newline()
{
    if (me->prevdata->val == NEWLINE) {
        me->currdata->val = NEWLINE;
        me->currdata->byteheader = 10;
        me->currjustify->wcount = 0;
        me->hbytecount++;
        me->hcolcount = me->hcolsize + 1;
        me->currdata->wbytecount = me->wbytecount = 0;
        me->currdata->wcolcount = me->wcolcount = 0;
        return;
    }
    if ((unsigned char)me->readbuff[me->currreadindex->incre->val] == NEWLINE) {
        me->currdata->val = NEWLINE;
        me->currdata->byteheader = 10;
        me->currjustify->wcount = 0;
        me->hbytecount++;
        me->hcolcount = me->hcolsize + 1;
        me->currdata->wbytecount = me->wbytecount = 0;
        me->currdata->wcolcount = me->wcolcount = 0;
        return;
    }
    if ((unsigned char)me->readbuff[me->currreadindex->incre->val] == EOS) {
        me->currdata->val = NEWLINE;
        me->currdata->byteheader = 10;
        me->hbytecount++;
        me->hcolcount = me->hcolsize + 1;
        me->currdata->wbytecount = me->wbytecount = 0;
        me->currdata->wcolcount = me->wcolcount = 0;
        return;
    }
    me->wbytecount = 0;
    me->wcolcount = 0;
}

void nonealnum()
{
    me->wbytecount = 0;
    me->wcolcount = 0;
}

void invalidbyte()
{
    me->wbytecount = 0;
    me->wcolcount = 0;
}

inline void lbspace()
{
    me->currjustify->remain = me->currdata->wcolcount;
    if (me->endingspace == 1) {
        me->lbdata->annotation = NEWLINE;
        return;
    }
    me->lbdata->val = NEWLINE;
}

inline void lbnewline()
{
    me->currjustify->remain = me->currdata->wcolcount;
}

inline void lbnonealnum()
{
    me->currjustify->remain = me->currdata->wcolcount;
}

inline void lbalnum()
{
    me->currjustify->remain = me->currdata->wcolcount;
    me->lbdata->annotation = NEWLINE;
}

inline void lbformfeed()
{
    me->currjustify->remain = me->currdata->wcolcount;
    me->lbdata->annotation = NEWLINE;
}

inline void lbinvalidbyte()
{
    me->currjustify->remain = me->currdata->wcolcount;
}
