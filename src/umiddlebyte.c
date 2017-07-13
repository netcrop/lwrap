/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)

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

inline void lbmiddlebyte(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
  my.lbdata->annotation = NEWLINE;
}
