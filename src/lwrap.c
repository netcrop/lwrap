/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)

inline void flinebreak()
{
    if (me->hcolcount <= me->hcolsize)
        return;
    if (me->currdata->val == EOS)
        return;
    if ((me->linebreak = me->currdata->dataindex - me->currdata->wbytecount) < 0)
        me->linebreak += me->databoundry;
    me->lbdata = &me->data[me->linebreak];
    me->hcolcount = me->currdata->wcolcount;
    me->hbytecount = me->currdata->wbytecount;
    me->funicode[me->lbdata->val]->linebreak(me);
    if (me->currjustify->remain != 0 && me->currjustify->wcount == 0) ;
    else
        me->currjustify = me->currjustify->after;
}

void usage()
{
    printf("%s%s%s", " Usage: ", me->progname,
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
    if (me->filep != NULL)
        fclose(me->filep);
    if (me->filedebug != NULL)
        fclose(me->filedebug);
    if (*me != NULL) {
        if (me->data != NULL)
            free(me->data);
        if (me->outindex != NULL)
            free(me->outindex);
        if (me->readindex != NULL)
            free(me->readindex);
        if (me->writebuff != NULL)
            free(me->writebuff);
        if (me->readbuff != NULL)
            free(me->readbuff);
        if (me->justify != NULL)
            free(me->justify);
        if (me->string != NULL)
            free(me->string);
        if (me->funicode != NULL)
            free(me->funicode);
        if (me->call != NULL)
            free(me->call);
        if (me->fring != NULL)
            free(me->fring);
        free(*me);
    }
}

void mlocate(void **p, size_t size)
{
    if (!(*p = malloc(size))) {
        fprintf(stderr, "%s\n", "mlocate: memory allocation faild.");
        exit(0);
    }
}

inline void strappend(char *str, char **strp, )
{
    *strp = me->currstring;
    while ((*me->currstring++ = *str++) != EOS) ;
}

void option()
{
    while ((me->optchr = getopt(me->argc, me->argv, "hc:dj:ef:v")) != EOF) {
        switch (me->optchr) {
        case 'h':
        case '?':
            me->usage(me);
            delocate(me);
            exit(0);
        case 'c':
            if ((me->hcolsize =
                 (int)strtol(optarg, &me->strtolend, 10)) > 0
                && me->hcolsize < me->displaymax) {
                me->writebuffrelay = me->hcolsize * me->justifymultiple;
                break;
            }
            delocate(me);
            exit(0);
        case 'd':
            me->debug = 1;
            if ((me->filedebug = fopen(me->debugfile, "w")) == NULL)
                me->filedebug = stderr;
            break;
        case 'e':
            me->endingspace = 0;
            break;
        case 'j':
            if ((me->hcolsize =
                 (int)strtol(optarg, &me->strtolend, 10)) > 0
                && me->hcolsize < me->displaymax) {
                me->writebuffrelay = me->hcolsize * me->justifymultiple;
                me->justifying = 1;
                break;
            }
            delocate(me);
            exit(0);
        case 'f':
            if ((me->filep = fopen(optarg, "r")) != NULL)
                break;
            delocate(me);
            exit(0);
        case 'v':
            version(me);
            delocate(me);
            exit(0);
        }
    }
}

inline void avariable()
{
    mlocate((void **)me, sizeof(self));
    me->displaymax = 236;
    me->justifymultiple = 2;
    me->buffmultiple = 42;
    me->argc = 0;
    me->argv = (char **)NULL;
    me->foutput = &foutput;
    me->usage = &usage;
    me->version = &version;
    me->option = &option;
    me->freadfile = &freadfile;
    me->delocate = &delocate;
    me->fjustify = &fjustify;
    me->alocate = &alocate;
    me->flinebreak = &flinebreak;
    me->hcolsize = 80;
    me->maxwordsize = 28;
    me->readbuffrelay = 2;
    me->writebuffrelay = me->maxwordsize;
    me->callsize = 2;
    me->flinebreaksize = 28;
    me->fmiddlebytesize = 28;
    me->fringboundry = 28;
    me->fringsize = me->fringboundry - 1;
    me->initwritebuff = FINITOUTBUFF;
    me->buffboundry = me->hcolsize * me->buffmultiple + 1;
    me->readbuffsize = me->buffboundry - 1;
    me->databoundry = me->hcolsize * me->buffmultiple + 1;
    me->datasize = me->databoundry - 1;
    me->writebuffboundry = me->hcolsize * me->buffmultiple + 1;
    me->writebuffsize = me->writebuffboundry - 1;
    me->writesize = 3200;
    me->justifyboundry = 40;
    me->justifysize = me->justifyboundry - 1;
    me->hcolcount = 0;
    me->hbytecount = 0;
    me->linebreak = 0;
    me->getchar = 0;
    me->wcolcount = 0;
    me->delimeter = 0;
    me->justifying = 0;
    me->endingspace = 1;
    me->wbytecount = 0;
    me->optchr = 0;
    me->debug = 0;
    me->readsize = 0;
    me->rindex = 0;
    me->oindex = 0;
    me->stringsize = 60;
    me->filesize = 0;
    me->strtolend = (char *)NULL;
    me->filep = stdin;
    me->filedebug = stderr;
    me->data = (data_t *) NULL;
    me->outdata = (data_t *) NULL;
    me->currdata = (data_t *) NULL;
    me->prevdata = (data_t *) NULL;
    me->nextdata = (data_t *) NULL;
    me->readdata = (data_t *) NULL;
    me->lbdata = (data_t *) NULL;
    me->outindex = (index_t *) NULL;
    me->readindex = (index_t *) NULL;
    me->call = (fun) NULL;
    me->justify = (justify_t *) NULL;
    me->funicode = (fun_t **) NULL;
    me->readbuff = (char *)NULL;
    me->writebuff = (char *)NULL;
    me->fring = (fun_t **) NULL;
    mlocate((void **)&me->string, (sizeof(char) * me->stringsize));
    for (int i = 0; i < me->stringsize; i++)
        me->string[i] = SPACE;
    me->string[me->stringsize - 1] = EOS;
    me->currstring = &me->string[0];
    strappend("lwrap", &me->progname, me);
    strappend("/tmp/lwrap.debug", &me->debugfile, me);
}

inline void acall()
{
    mlocate((void **)&me->call, (sizeof(fun) * me->callsize));
    me->call[0] = &finitwritebuff;
    me->call[1] = &fwritebuff;
}

inline void afring()
{
    mlocate((void **)&me->fring, (sizeof(fun_t) * me->fringboundry));
    me->fring[0].filter = &nonealnum;
    me->fring[0].linebreak = &lbnonealnum;
    me->fring[1].filter = &alnum;
    me->fring[1].linebreak = &lbalnum;
    me->fring[2].filter = &space;
    me->fring[2].linebreak = &lbspace;
    me->fring[3].filter = &newline;
    me->fring[3].linebreak = &lbnewline;
    me->fring[4].filter = &formfeed;
    me->fring[4].linebreak = &lbformfeed;
    me->fring[5].filter = &middlebyte;
    me->fring[5].linebreak = &lbmiddlebyte;
    me->fring[6].filter = &invalidbyte;
    me->fring[6].linebreak = &lbinvalidbyte;
    me->fring[7].filter = &latinheader;
    me->fring[7].linebreak = &lblatinheader;
    me->fring[8].filter = &ipaheader;
    me->fring[8].linebreak = &lbipaheader;
    me->fring[9].filter = &accentsheader;
    me->fring[9].linebreak = &lbaccentsheader;
    me->fring[10].filter = &greekheader;
    me->fring[10].linebreak = &lbgreekheader;
    me->fring[11].filter = &cyrilheader;
    me->fring[11].linebreak = &lbcyrilheader;
    me->fring[12].filter = &armeniheader;
    me->fring[12].linebreak = &lbarmeniheader;
    me->fring[13].filter = &hebrewheader;
    me->fring[13].linebreak = &lbhebrewheader;
    me->fring[14].filter = &arabicheader;
    me->fring[14].linebreak = &lbarabicheader;
    me->fring[15].filter = &syriacheader;
    me->fring[15].linebreak = &lbsyriacheader;
    me->fring[16].filter = &thaanaheader;
    me->fring[16].linebreak = &lbthaanaheader;
    me->fring[17].filter = &nkoheader;
    me->fring[17].linebreak = &lbnkoheader;
    me->fring[18].filter = &indicheader;
    me->fring[18].linebreak = &lbindicheader;
    me->fring[19].filter = &mischeader;
    me->fring[19].linebreak = &lbmischeader;
    me->fring[20].filter = &symbolheader;
    me->fring[20].linebreak = &lbsymbolheader;
    me->fring[21].filter = &cjkheader;
    me->fring[21].linebreak = &lbcjkheader;
    me->fring[22].filter = &asianheader;
    me->fring[22].linebreak = &lbasianheader;
    me->fring[23].filter = &puaheader;
    me->fring[23].linebreak = &lbpuaheader;
    me->fring[24].filter = &formsheader;
    me->fring[24].linebreak = &lbformsheader;
    me->fring[25].filter = &hangulheader;
    me->fring[25].linebreak = &lbhangulheader;
    me->fring[26].filter = &fourbyteheader;
    me->fring[26].linebreak = &lbfourbyteheader;
}

inline void aunicode()
{
    mlocate((void **)&me->funicode, (sizeof(fun_t *) * UNICODESIZE));
    for (int i = 0; i <= NONEALNUMMAX; i++)
        me->funicode[i] = &me->fring[0];
    for (int i = ALNUMMIN; i <= ALNUMMAX; i++)
        me->funicode[i] = &me->fring[1];
    me->funicode[ALNUMMAX + 1] = &me->fring[0];
    me->funicode[SPACE] = &me->fring[2];
    me->funicode[NEWLINE] = &me->fring[3];
    me->funicode[FORMFEED] = &me->fring[4];
    for (int i = MIDDLEBYTEMIN; i <= MIDDLEBYTEMAX; i++)
        me->funicode[i] = &me->fring[5];
    me->funicode[192] = &me->fring[6];
    me->funicode[193] = &me->fring[6];
    for (int i = LATINMIN; i <= LATINMAX; i++)
        me->funicode[i] = &me->fring[7];
    for (int i = IPAMIN; i <= IPAMAX; i++)
        me->funicode[i] = &me->fring[8];
    for (int i = ACCENTSMIN; i <= ACCENTSMAX; i++)
        me->funicode[i] = &me->fring[9];
    for (int i = GREEKMIN; i <= GREEKMAX; i++)
        me->funicode[i] = &me->fring[10];
    for (int i = CYRILMIN; i <= CYRILMAX; i++)
        me->funicode[i] = &me->fring[11];
    me->funicode[ARMENIMIN] = &me->fring[12];
    for (int i = HEBREWMIN; i <= HEBREWMAX; i++)
        me->funicode[i] = &me->fring[13];
    for (int i = ARABICMIN; i <= ARABICMAX; i++)
        me->funicode[i] = &me->fring[14];
    me->funicode[SYRIACMIN] = &me->fring[15];
    me->funicode[THAANAMIN] = &me->fring[16];
    me->funicode[NKOMIN] = &me->fring[17];
    me->funicode[INDICMIN] = &me->fring[18];
    me->funicode[MISCMIN] = &me->fring[19];
    me->funicode[SYMBOLMIN] = &me->fring[20];
    for (int i = CJKMIN; i <= CJKMAX; i++)
        me->funicode[i] = &me->fring[21];
    me->funicode[ASIANMIN] = &me->fring[22];
    me->funicode[PUAMIN] = &me->fring[23];
    me->funicode[FORMSMIN] = &me->fring[24];
    for (int i = HANGULMIN; i <= HANGULMAX; i++)
        me->funicode[i] = &me->fring[25];
    for (int i = THREEBYTEHEADER; i < FOURBYTEHEADER; i++)
        me->funicode[i] = &me->fring[26];
    for (int i = FOURBYTEHEADER; i < UNICODESIZE; i++)
        me->funicode[i] = &me->fring[6];
}

inline void abuff()
{
    mlocate((void **)&me->readbuff, (sizeof(char) * me->buffboundry));
    for (int i = 0; i < me->buffboundry; i++)
        me->readbuff[i] = EOS;
    mlocate((void **)&me->writebuff, (sizeof(char) * me->writebuffboundry));
    for (int i = 0; i < me->writebuffboundry; i++)
        me->writebuff[i] = EOS;
    mlocate((void **)&me->outindex, (sizeof(index_t) * me->writebuffboundry));
    me->outindex[0].val = 0;
    me->outindex[0].decre = &me->outindex[me->writebuffsize];
    me->outindex[me->writebuffsize].incre = &me->outindex[0];
    me->curroutindex = &me->outindex[0];
    for (int i = 1; i < me->writebuffboundry; i++) {
        me->outindex[i].val = i;
        me->outindex[i].decre = &me->outindex[i - 1];
        me->outindex[i - 1].incre = &me->outindex[i];
    }
    mlocate((void **)&me->readindex, (sizeof(index_t) * me->buffboundry));
    me->readindex[0].val = 0;
    me->readindex[0].decre = &me->readindex[me->readbuffsize];
    me->readindex[me->readbuffsize].incre = &me->readindex[0];
    me->currreadindex = &me->readindex[0];
    for (int i = 1; i < me->buffboundry; i++) {
        me->readindex[i].val = i;
        me->readindex[i].decre = &me->readindex[i - 1];
        me->readindex[i - 1].incre = &me->readindex[i];
    }
    mlocate((void **)&me->data, (sizeof(data_t) * me->databoundry));
    me->data[0].dataindex = 0;
    me->data[0].byteheader = 0;
    me->data[0].wbytecount = 0;
    me->data[0].wcolcount = 0;
    me->data[0].annotation = EOS;
    me->data[0].glyph = ASCII;
    me->data[0].val = EOS;
    me->data[0].before = &me->data[me->datasize];
    me->data[me->datasize].after = &me->data[0];
    for (int i = 1; i < me->databoundry; i++) {
        me->data[i].dataindex = i;
        me->data[i].wcolcount = 0;
        me->data[i].byteheader = 0;
        me->data[i].wbytecount = 0;
        me->data[i].annotation = EOS;
        me->data[i].glyph = ASCII;
        me->data[i].val = EOS;
        me->data[i].before = &me->data[i - 1];
        me->data[i - 1].after = &me->data[i];
    }
    me->currdata = &me->data[0];
    me->prevdata = me->currdata->before;
    me->nextdata = me->currdata->after;
    me->readdata = &me->data[0];
    me->outdata = &me->data[0];
    mlocate((void **)&me->justify, (sizeof(justify_t) * me->justifyboundry));
    me->justify[0].remain = 0;
    me->justify[0].index = 0;
    me->justify[0].wcount = 0;
    me->justify[0].before = &me->justify[me->justifysize];
    me->justify[me->justifysize].after = &me->justify[0];
    for (int i = 1; i < me->justifyboundry; i++) {
        me->justify[i].remain = 0;
        me->justify[i].index = i;
        me->justify[i].wcount = 0;
        me->justify[i].before = &me->justify[i - 1];
        me->justify[i - 1].after = &me->justify[i];
    }
    me->currjustify = &me->justify[0];
    me->outjustify = &me->justify[0];
}

inline void alocate()
{
    acall(me);
    afring(me);
    aunicode(me);
    abuff(me);
}

inline void fjustify()
{
    if (!me->justifying) {
        me->writebuff[me->curroutindex->val] = SPACE;
        me->curroutindex = me->curroutindex->incre;
        return;
    }
    if (me->outjustify->remain == 0) {
        me->writebuff[me->curroutindex->val] = SPACE;
        me->curroutindex = me->curroutindex->incre;
        return;
    }
    if (me->outjustify->wcount < 2) {
        me->writebuff[me->curroutindex->val] = SPACE;
        me->curroutindex = me->curroutindex->incre;
        return;
    }
    if (me->outjustify->remain < 0 || me->outjustify->wcount < 2)
        return;
    int wseparator = me->outjustify->wcount - 1,
        spaces = me->outjustify->remain / wseparator,
        remainder = me->outjustify->remain % wseparator;
    if (remainder)
        spaces++;
    for (int i = 0; i < spaces; i++) {
        me->writebuff[me->curroutindex->val] = SPACE;
        me->curroutindex = me->curroutindex->incre;
    }
    me->writebuff[me->curroutindex->val] = SPACE;
    me->curroutindex = me->curroutindex->incre;
    me->outjustify->remain -= spaces;
    me->outjustify->wcount--;
}
