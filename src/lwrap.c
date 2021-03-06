/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"

__attribute__((always_inline)) inline void flinebreak()
{
    if (my.hcolcount <= my.hcolsize)
        return;
    if (my.currdata->val == EOS)
        return;
    if ((my.linebreak = my.currdata->dataindex - my.currdata->wbytecount) < 0)
        my.linebreak += my.databoundry;
    my.lbdata = &my.data[my.linebreak];
    my.hcolcount = my.currdata->wcolcount;
    my.hbytecount = my.currdata->wbytecount;
    my.funicode[my.lbdata->val]->linebreak();
    if (my.currjustify->remain != 0 && my.currjustify->wcount == 0) ;
    else
        my.currjustify = my.currjustify->after;
}

void usage()
{
    printf("%s%s%s", " Usage: ", my.progname,
           " [-c columns] [-j columns][-e][-f text file]\n\
      LANG = countrycode.utf8\n\
      -c:   set number of columns before line break.\n\
      -j:   same as -c but justified lines with ASCII spaces.\n\
      -f:   read input from text file instead of default stdin.\n\
      -e:   line break without ASCII space but a newline only.\n\
      -h:   print usage and exit.\n\
      -d:   output debugging text to /tmp/lwrap.debug file.\n\
      -V:   print version and exit.\n\
      e.g.  -c80 -f foo.txt\n\
      e.g.  -j60 <foo.txt\n\
      e.g.  -e -j60 <foo.txt >result.txt\n\
      use with vim.  :[range]! -j60\n");
}

void version()
{
    printf("%s %s %s\n", VERSION, __TIME__, __DATE__);
}

void delocate()
{
    if (!me)
        return;
    if (my.filep != NULL){
        fclose(my.filep);
    }
    if (my.filedebug != NULL){
        fclose(my.filedebug);
    }
    if (my.data != NULL){
        free(my.data);
    }
    if (my.outindex != NULL)
        free(my.outindex);
    if (my.readindex != NULL)
        free(my.readindex);
    if (my.writebuff != NULL)
        free(my.writebuff);
    if (my.readbuff != NULL)
        free(my.readbuff);
    if (my.justify != NULL)
        free(my.justify);
    if (my.string != NULL)
        free(my.string);
    if (my.funicode != NULL)
        free(my.funicode);
    if (my.call != NULL)
        free(my.call);
    if (my.fring != NULL)
        free(my.fring);
    free(me);
    me = NULL;
}

void lwrap_mlocate(void **p, size_t size)
{
    if (!(*p = malloc(size))) {
        fprintf(stderr, "%s\n", "lwrap_mlocate: memory allocation faild.");
        exit(0);
    }
}

inline void strappend(char *str, char **strp)
{
    *strp = my.currstring;
    while ((*my.currstring++ = *str++) != EOS) ;
}

void option()
{
    while ((my.optchr = getopt(my.argc, my.argv, "hc:dj:ef:v")) != EOF) {
        switch (my.optchr) {
        case 'h':
        case '?':
            my.usage();
            exit(0);
        case 'c':
            if ((my.hcolsize =
                 (int)strtol(optarg, &my.strtolend, 10)) > 0
                && my.hcolsize < my.displaymax) {
                my.writebuffrelay = my.hcolsize * my.justifymultiple;
                break;
            }
            exit(0);
        case 'd':
            my.debug = 1;
            if ((my.filedebug = fopen(my.debugfile, "w")) == NULL)
                my.filedebug = stderr;
            break;
        case 'e':
            my.endingspace = 0;
            break;
        case 'j':
            if ((my.hcolsize =
                 (int)strtol(optarg, &my.strtolend, 10)) > 0
                && my.hcolsize < my.displaymax) {
                my.writebuffrelay = my.hcolsize * my.justifymultiple;
                my.justifying = 1;
                break;
            }
            exit(0);
        case 'f':
            if ((my.filep = fopen(optarg, "r")) != NULL)
                break;
            exit(0);
        case 'v':
            version();
            exit(0);
        }
    }
}
inline void sighandler(int sig)
{
    exit(0);
}
inline void avariable()
{
    atexit(delocate);
    signal(SIGINT,sighandler);
    if(me)
        return;
    lwrap_mlocate((void **)&me, sizeof(self));
    my.displaymax = 236;
    my.justifymultiple = 2;
    my.buffmultiple = 42;
    my.argc = 0;
    my.argv = (char **)NULL;
    my.foutput = &foutput;
    my.usage = &usage;
    my.version = &version;
    my.option = &option;
    my.freadfile = &freadfile;
    my.delocate = &delocate;
    my.fjustify = &fjustify;
    my.alocate = &alocate;
    my.flinebreak = &flinebreak;
    my.hcolsize = 80;
    my.maxwordsize = 28;
    my.readbuffrelay = 2;
    my.writebuffrelay = my.maxwordsize;
    my.callsize = 2;
    my.flinebreaksize = 28;
    my.fmiddlebytesize = 28;
    my.fringboundry = 28;
    my.fringsize = my.fringboundry - 1;
    my.initwritebuff = FINITOUTBUFF;
    my.buffboundry = my.hcolsize * my.buffmultiple + 1;
    my.readbuffsize = my.buffboundry - 1;
    my.databoundry = my.hcolsize * my.buffmultiple + 1;
    my.datasize = my.databoundry - 1;
    my.writebuffboundry = my.hcolsize * my.buffmultiple + 1;
    my.writebuffsize = my.writebuffboundry - 1;
    my.writesize = 3200;
    my.justifyboundry = 40;
    my.justifysize = my.justifyboundry - 1;
    my.hcolcount = 0;
    my.hbytecount = 0;
    my.linebreak = 0;
    my.getchar = 0;
    my.wcolcount = 0;
    my.delimeter = 0;
    my.justifying = 0;
    my.endingspace = 1;
    my.wbytecount = 0;
    my.optchr = 0;
    my.debug = 0;
    my.readsize = 0;
    my.rindex = 0;
    my.oindex = 0;
    my.stringsize = 60;
    my.filesize = 0;
    my.strtolend = (char *)NULL;
    my.filep = stdin;
    my.filedebug = stderr;
    my.data = (data_t *) NULL;
    my.outdata = (data_t *) NULL;
    my.currdata = (data_t *) NULL;
    my.prevdata = (data_t *) NULL;
    my.nextdata = (data_t *) NULL;
    my.readdata = (data_t *) NULL;
    my.lbdata = (data_t *) NULL;
    my.outindex = (index_t *) NULL;
    my.readindex = (index_t *) NULL;
    my.call = (fun) NULL;
    my.justify = (justify_t *) NULL;
    my.funicode = (fun_t **) NULL;
    my.readbuff = (char *)NULL;
    my.writebuff = (char *)NULL;
    my.fring = (fun_t **) NULL;
    lwrap_mlocate((void **)&my.string, (sizeof(char) * my.stringsize));
    for (int i = 0; i < my.stringsize; i++)
        my.string[i] = SPACE;
    my.string[my.stringsize - 1] = EOS;
    my.currstring = &my.string[0];
    strappend("lwrap", &my.progname);
    strappend("/tmp/lwrap.debug", &my.debugfile);
}

inline void acall()
{
    lwrap_mlocate((void **)&my.call, (sizeof(fun) * my.callsize));
    my.call[0] = &finitwritebuff;
    my.call[1] = &fwritebuff;
}

inline void afring()
{
    lwrap_mlocate((void **)&my.fring, (sizeof(fun_t) * my.fringboundry));
    my.fring[0].filter = &nonealnum;
    my.fring[0].linebreak = &lbnonealnum;
    my.fring[1].filter = &alnum;
    my.fring[1].linebreak = &lbalnum;
    my.fring[2].filter = &space;
    my.fring[2].linebreak = &lbspace;
    my.fring[3].filter = &newline;
    my.fring[3].linebreak = &lbnewline;
    my.fring[4].filter = &formfeed;
    my.fring[4].linebreak = &lbformfeed;
    my.fring[5].filter = &middlebyte;
    my.fring[5].linebreak = &lbmiddlebyte;
    my.fring[6].filter = &invalidbyte;
    my.fring[6].linebreak = &lbinvalidbyte;
    my.fring[7].filter = &latinheader;
    my.fring[7].linebreak = &lblatinheader;
    my.fring[8].filter = &ipaheader;
    my.fring[8].linebreak = &lbipaheader;
    my.fring[9].filter = &accentsheader;
    my.fring[9].linebreak = &lbaccentsheader;
    my.fring[10].filter = &greekheader;
    my.fring[10].linebreak = &lbgreekheader;
    my.fring[11].filter = &cyrilheader;
    my.fring[11].linebreak = &lbcyrilheader;
    my.fring[12].filter = &armeniheader;
    my.fring[12].linebreak = &lbarmeniheader;
    my.fring[13].filter = &hebrewheader;
    my.fring[13].linebreak = &lbhebrewheader;
    my.fring[14].filter = &arabicheader;
    my.fring[14].linebreak = &lbarabicheader;
    my.fring[15].filter = &syriacheader;
    my.fring[15].linebreak = &lbsyriacheader;
    my.fring[16].filter = &thaanaheader;
    my.fring[16].linebreak = &lbthaanaheader;
    my.fring[17].filter = &nkoheader;
    my.fring[17].linebreak = &lbnkoheader;
    my.fring[18].filter = &indicheader;
    my.fring[18].linebreak = &lbindicheader;
    my.fring[19].filter = &mischeader;
    my.fring[19].linebreak = &lbmischeader;
    my.fring[20].filter = &symbolheader;
    my.fring[20].linebreak = &lbsymbolheader;
    my.fring[21].filter = &cjkheader;
    my.fring[21].linebreak = &lbcjkheader;
    my.fring[22].filter = &asianheader;
    my.fring[22].linebreak = &lbasianheader;
    my.fring[23].filter = &puaheader;
    my.fring[23].linebreak = &lbpuaheader;
    my.fring[24].filter = &formsheader;
    my.fring[24].linebreak = &lbformsheader;
    my.fring[25].filter = &hangulheader;
    my.fring[25].linebreak = &lbhangulheader;
    my.fring[26].filter = &fourbyteheader;
    my.fring[26].linebreak = &lbfourbyteheader;
}

inline void aunicode()
{
    lwrap_mlocate((void **)&my.funicode, (sizeof(fun_t *) * UNICODESIZE));
    for (int i = 0; i <= NONEALNUMMAX; i++)
        my.funicode[i] = &my.fring[0];
    for (int i = ALNUMMIN; i <= ALNUMMAX; i++)
        my.funicode[i] = &my.fring[1];
    my.funicode[ALNUMMAX + 1] = &my.fring[0];
    my.funicode[SPACE] = &my.fring[2];
    my.funicode[NEWLINE] = &my.fring[3];
    my.funicode[FORMFEED] = &my.fring[4];
    for (int i = MIDDLEBYTEMIN; i <= MIDDLEBYTEMAX; i++)
        my.funicode[i] = &my.fring[5];
    my.funicode[192] = &my.fring[6];
    my.funicode[193] = &my.fring[6];
    for (int i = LATINMIN; i <= LATINMAX; i++)
        my.funicode[i] = &my.fring[7];
    for (int i = IPAMIN; i <= IPAMAX; i++)
        my.funicode[i] = &my.fring[8];
    for (int i = ACCENTSMIN; i <= ACCENTSMAX; i++)
        my.funicode[i] = &my.fring[9];
    for (int i = GREEKMIN; i <= GREEKMAX; i++)
        my.funicode[i] = &my.fring[10];
    for (int i = CYRILMIN; i <= CYRILMAX; i++)
        my.funicode[i] = &my.fring[11];
    my.funicode[ARMENIMIN] = &my.fring[12];
    for (int i = HEBREWMIN; i <= HEBREWMAX; i++)
        my.funicode[i] = &my.fring[13];
    for (int i = ARABICMIN; i <= ARABICMAX; i++)
        my.funicode[i] = &my.fring[14];
    my.funicode[SYRIACMIN] = &my.fring[15];
    my.funicode[THAANAMIN] = &my.fring[16];
    my.funicode[NKOMIN] = &my.fring[17];
    my.funicode[INDICMIN] = &my.fring[18];
    my.funicode[MISCMIN] = &my.fring[19];
    my.funicode[SYMBOLMIN] = &my.fring[20];
    for (int i = CJKMIN; i <= CJKMAX; i++)
        my.funicode[i] = &my.fring[21];
    my.funicode[ASIANMIN] = &my.fring[22];
    my.funicode[PUAMIN] = &my.fring[23];
    my.funicode[FORMSMIN] = &my.fring[24];
    for (int i = HANGULMIN; i <= HANGULMAX; i++)
        my.funicode[i] = &my.fring[25];
    for (int i = THREEBYTEHEADER; i < FOURBYTEHEADER; i++)
        my.funicode[i] = &my.fring[26];
    for (int i = FOURBYTEHEADER; i < UNICODESIZE; i++)
        my.funicode[i] = &my.fring[6];
}

inline void abuff()
{
    lwrap_mlocate((void **)&my.readbuff, (sizeof(char) * my.buffboundry));
    for (int i = 0; i < my.buffboundry; i++)
        my.readbuff[i] = EOS;
    lwrap_mlocate((void **)&my.writebuff, (sizeof(char) * my.writebuffboundry));
    for (int i = 0; i < my.writebuffboundry; i++)
        my.writebuff[i] = EOS;
    lwrap_mlocate((void **)&my.outindex, (sizeof(index_t) * my.writebuffboundry));
    my.outindex[0].val = 0;
    my.outindex[0].decre = &my.outindex[my.writebuffsize];
    my.outindex[my.writebuffsize].incre = &my.outindex[0];
    my.curroutindex = &my.outindex[0];
    for (int i = 1; i < my.writebuffboundry; i++) {
        my.outindex[i].val = i;
        my.outindex[i].decre = &my.outindex[i - 1];
        my.outindex[i - 1].incre = &my.outindex[i];
    }
    lwrap_mlocate((void **)&my.readindex, (sizeof(index_t) * my.buffboundry));
    my.readindex[0].val = 0;
    my.readindex[0].decre = &my.readindex[my.readbuffsize];
    my.readindex[my.readbuffsize].incre = &my.readindex[0];
    my.currreadindex = &my.readindex[0];
    for (int i = 1; i < my.buffboundry; i++) {
        my.readindex[i].val = i;
        my.readindex[i].decre = &my.readindex[i - 1];
        my.readindex[i - 1].incre = &my.readindex[i];
    }
    lwrap_mlocate((void **)&my.data, (sizeof(data_t) * my.databoundry));
    my.data[0].dataindex = 0;
    my.data[0].byteheader = 0;
    my.data[0].wbytecount = 0;
    my.data[0].wcolcount = 0;
    my.data[0].annotation = EOS;
    my.data[0].glyph = ASCII;
    my.data[0].val = EOS;
    my.data[0].before = &my.data[my.datasize];
    my.data[my.datasize].after = &my.data[0];
    for (int i = 1; i < my.databoundry; i++) {
        my.data[i].dataindex = i;
        my.data[i].wcolcount = 0;
        my.data[i].byteheader = 0;
        my.data[i].wbytecount = 0;
        my.data[i].annotation = EOS;
        my.data[i].glyph = ASCII;
        my.data[i].val = EOS;
        my.data[i].before = &my.data[i - 1];
        my.data[i - 1].after = &my.data[i];
    }
    my.currdata = &my.data[0];
    my.prevdata = my.currdata->before;
    my.nextdata = my.currdata->after;
    my.readdata = &my.data[0];
    my.outdata = &my.data[0];
    lwrap_mlocate((void **)&my.justify, (sizeof(justify_t) * my.justifyboundry));
    my.justify[0].remain = 0;
    my.justify[0].index = 0;
    my.justify[0].wcount = 0;
    my.justify[0].before = &my.justify[my.justifysize];
    my.justify[my.justifysize].after = &my.justify[0];
    for (int i = 1; i < my.justifyboundry; i++) {
        my.justify[i].remain = 0;
        my.justify[i].index = i;
        my.justify[i].wcount = 0;
        my.justify[i].before = &my.justify[i - 1];
        my.justify[i - 1].after = &my.justify[i];
    }
    my.currjustify = &my.justify[0];
    my.outjustify = &my.justify[0];
}

inline void alocate()
{
    acall();
    afring();
    aunicode();
    abuff();
}

inline void fjustify()
{
    if (!my.justifying) {
        my.writebuff[my.curroutindex->val] = SPACE;
        my.curroutindex = my.curroutindex->incre;
        return;
    }
    if (my.outjustify->remain == 0) {
        my.writebuff[my.curroutindex->val] = SPACE;
        my.curroutindex = my.curroutindex->incre;
        return;
    }
    if (my.outjustify->wcount < 2) {
        my.writebuff[my.curroutindex->val] = SPACE;
        my.curroutindex = my.curroutindex->incre;
        return;
    }
    if (my.outjustify->remain < 0 || my.outjustify->wcount < 2)
        return;
    int wseparator = my.outjustify->wcount - 1,
        spaces = my.outjustify->remain / wseparator,
        remainder = my.outjustify->remain % wseparator;
    if (remainder)
        spaces++;
    for (int i = 0; i < spaces; i++) {
        my.writebuff[my.curroutindex->val] = SPACE;
        my.curroutindex = my.curroutindex->incre;
    }
    my.writebuff[my.curroutindex->val] = SPACE;
    my.curroutindex = my.curroutindex->incre;
    my.outjustify->remain -= spaces;
    my.outjustify->wcount--;
}
