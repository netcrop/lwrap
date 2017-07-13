/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)
void armeniheader(self ** me)
{
  my.currdata->val = (unsigned char)my.readbuff[my.currreadindex->val];
  my.currdata->byteheader = 20;
  my.currdata->wcolcount = ++my.wcolcount;
  my.currdata->wbytecount = ++my.wbytecount;
  my.hbytecount++;
}

inline void farmenimiddlebyte(self ** me)
{
  my.hbytecount++;
  my.hcolcount++;
  my.currdata->wbytecount = ++my.wbytecount;
  my.currdata->wcolcount = my.wcolcount;
}

inline void lbarmeniheader(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}
