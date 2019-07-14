/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
void alnum()
{
    if (my.prevdata->byteheader > TWOBYTEMAX) {
        my.currdata->val = (unsigned char)my.readbuff[my.currreadindex->val];
        my.currdata->byteheader = 10;
        my.hbytecount++;
        my.hcolcount++;
        my.currjustify->wcount++;
        my.currdata->wbytecount = my.wbytecount = 1;
        my.currdata->wcolcount = my.wcolcount = 1;
        return;
    }
    my.currdata->val = (unsigned char)my.readbuff[my.currreadindex->val];
    my.currdata->byteheader = 10;
    my.hbytecount++;
    my.hcolcount++;
    my.currdata->wbytecount = ++my.wbytecount;
    my.currdata->wcolcount = ++my.wcolcount;
}

void space()
{
    if (my.prevdata->val == SPACE) {
        my.wbytecount = 0;
        my.wcolcount = 0;
        return;
    }
    if (my.prevdata->val == NEWLINE
        && (unsigned char)my.readbuff[my.currreadindex->incre->val] !=
        SYMBOLMIN) {
        my.wbytecount = 0;
        my.wcolcount = 0;
        return;
    }
    if ((unsigned char)my.readbuff[my.currreadindex->incre->val] == SPACE) {
        my.wbytecount = 0;
        my.wcolcount = 0;
        return;
    }
    my.currdata->val = SPACE;
    my.currdata->byteheader = 10;
    my.hbytecount++;
    my.hcolcount++;
    my.currjustify->wcount++;
    my.currdata->wbytecount = my.wbytecount = 0;
    my.currdata->wcolcount = my.wcolcount = 0;
}

void formfeed()
{
    my.currdata->byteheader = 10;
    my.currdata->val = NEWLINE;
    my.hbytecount++;
    my.hcolcount = my.hcolsize + 1;
    my.currdata->wbytecount = my.wbytecount = 0;
    my.currdata->wcolcount = my.wcolcount = 0;
}

void newline()
{
    if (my.prevdata->val == NEWLINE) {
        my.currdata->val = NEWLINE;
        my.currdata->byteheader = 10;
        my.currjustify->wcount = 0;
        my.hbytecount++;
        my.hcolcount = my.hcolsize + 1;
        my.currdata->wbytecount = my.wbytecount = 0;
        my.currdata->wcolcount = my.wcolcount = 0;
        return;
    }
    if ((unsigned char)my.readbuff[my.currreadindex->incre->val] == NEWLINE) {
        my.currdata->val = NEWLINE;
        my.currdata->byteheader = 10;
        my.currjustify->wcount = 0;
        my.hbytecount++;
        my.hcolcount = my.hcolsize + 1;
        my.currdata->wbytecount = my.wbytecount = 0;
        my.currdata->wcolcount = my.wcolcount = 0;
        return;
    }
    if ((unsigned char)my.readbuff[my.currreadindex->incre->val] == EOS) {
        my.currdata->val = NEWLINE;
        my.currdata->byteheader = 10;
        my.hbytecount++;
        my.hcolcount = my.hcolsize + 1;
        my.currdata->wbytecount = my.wbytecount = 0;
        my.currdata->wcolcount = my.wcolcount = 0;
        return;
    }
    my.wbytecount = 0;
    my.wcolcount = 0;
}

void nonealnum()
{
    my.wbytecount = 0;
    my.wcolcount = 0;
}

void invalidbyte()
{
    my.wbytecount = 0;
    my.wcolcount = 0;
}

inline void lbspace()
{
    my.currjustify->remain = my.currdata->wcolcount;
    if (my.endingspace == 1) {
        my.lbdata->annotation = NEWLINE;
        return;
    }
    my.lbdata->val = NEWLINE;
}

inline void lbnewline()
{
    my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbnonealnum()
{
    my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbalnum()
{
    my.currjustify->remain = my.currdata->wcolcount;
    my.lbdata->annotation = NEWLINE;
}

inline void lbformfeed()
{
    my.currjustify->remain = my.currdata->wcolcount;
    my.lbdata->annotation = NEWLINE;
}

inline void lbinvalidbyte()
{
    my.currjustify->remain = my.currdata->wcolcount;
}
