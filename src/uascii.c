/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)

void alnum(self ** me)
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

void space(self ** me)
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

void formfeed(self ** me)
{
  my.currdata->byteheader = 10;
  my.currdata->val = NEWLINE;
  my.hbytecount++;
  my.hcolcount = my.hcolsize + 1;
  my.currdata->wbytecount = my.wbytecount = 0;
  my.currdata->wcolcount = my.wcolcount = 0;
}

void newline(self ** me)
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

void nonealnum(self ** me)
{
  my.wbytecount = 0;
  my.wcolcount = 0;
}

void invalidbyte(self ** me)
{
  my.wbytecount = 0;
  my.wcolcount = 0;
}

void middlebyte(self ** me)
{
  my.currdata->val = (unsigned char)my.readbuff[my.currreadindex->val];
  my.currdata->byteheader = my.prevdata->byteheader + 1;
  my.currdata->glyph = my.prevdata->glyph;
  if (my.currdata->byteheader < TWOBYTEMAX) {
    my.hbytecount++;
    my.hcolcount++;
    my.currdata->wbytecount = ++my.wbytecount;
    my.currdata->wcolcount = my.wcolcount;
    return;
  }
  my.hbytecount++;
  my.currdata->wbytecount = my.prevdata->wbytecount + 1;
  my.currdata->wcolcount = 2;
}

void fourbyteheader(self ** me)
{
  my.currdata->val = (unsigned char)my.readbuff[my.currreadindex->val];
  my.currdata->byteheader = 40;
  my.wcolcount = my.wbytecount = 0;
  my.currdata->wcolcount = 1;
  my.currdata->wbytecount = 1;
  my.currjustify->wcount++;
  my.hbytecount++;
}

inline void lbspace(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
  if (my.endingspace == 1) {
    my.lbdata->annotation = NEWLINE;
    return;
  }
  my.lbdata->val = NEWLINE;
}

inline void lbnewline(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbnonealnum(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbalnum(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
  my.lbdata->annotation = NEWLINE;
}

inline void lbformfeed(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
  my.lbdata->annotation = NEWLINE;
}

inline void lbinvalidbyte(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbmiddlebyte(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
  my.lbdata->annotation = NEWLINE;
}

inline void lbfourbyteheader(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}
