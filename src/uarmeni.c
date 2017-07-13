/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)
void uarmeniheader(self ** me)
{
  my.currdata->val = (unsigned char)my.readbuff[my.currreadindex->val];
  my.currdata->byteheader = 20;
  my.currdata->wcolcount = ++my.wcolcount;
  my.currdata->wbytecount = ++my.wbytecount;
  my.hbytecount++;
}

inline void fuarmenimiddlebyte(self ** me)
{
  my.hbytecount++;
  my.hcolcount++;
  my.currdata->wbytecount = ++my.wbytecount;
  my.currdata->wcolcount = my.wcolcount;
}

inline void lbuarmeniheader(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}
