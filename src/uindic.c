#include "lwrap.h"
#define my (**me)
void indicheader(self **me)
{
  my.currdata->val=(unsigned char)my.readbuff[my.currreadindex->val];
  my.currdata->byteheader=30;
  my.wcolcount=my.wbytecount=0;
  my.currdata->wcolcount=2;
  my.currdata->wbytecount=1;
  my.currjustify->wcount++;
  my.hcolcount+=2;
  my.hbytecount++;
}