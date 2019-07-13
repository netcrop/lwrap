lwrap.substitute()
{
    local cmd perl_version i cmdlist='sed shred perl readlink dirname sudo
    basename cat ls id cut bash man mktemp egrep date env mv
    cp chmod ln chown rm printf touch head mkdir find file
    make autoheader aclocal automake autoconf diff gcc dot indent
    which tr wc'
    for cmd in $(which $cmdlist);do
        \builtin eval "${cmd##*/}=${cmd}"
    done
    perl_version="$($perl -e 'print $^V')"
    prefix=/usr/local/
    bindir=${prefix}/bin/
    mandir=${prefix}/man/man1/
    binpath='lwrap'
    binfile="$(basename ${binpath})"
    manpath="${binfile}.1"
    manfile="$(basename ${manpath})"
    \builtin \source <($cat<<-SUB

lwrap.info()
{
    $cat<<-LWRAPINFO
    https://en.wikipedia.org/wiki/UTF-8
    http://www.utf8-chartable.de/
LWRAPINFO
}
lwrap.config()
{
    $make clean &&\
    $rm -f Makefile Makefile.in configure config.h.in config.h \
        config.log config.status
    $rm -rf autom4te.cache
    $aclocal &&\
    $autoheader &&\
    $automake &&\
    $autoconf &&\
    $chmod u=rwx configure
    ./configure
}
lwrap.clean()
{
    touch .deps/lwrap.Po
    make clean
    $rm -f Makefile Makefile.in configure config.h.in config.h \
        config.log config.status lwrap.spec lwrap.s lwrap.out \
        lwrap.verbose verify *.*~
    $rm -rf autom4te.cache
}
lwrap.make()
{
    $make clean
    touch .deps/lwrap.Po
    $make -j4 CFLAGS='-g -O2 -w'
}
lwrap.install()
{
    $sudo $cp -f $binpath $bindir/$binfile
    $sudo $chmod gu=rx $bindir/$binfile
    $sudo $chown \$USER: \$bindir/$binfile
    $sudo $cp -f $manpath ${mandir}/$manfile
    $sudo $chmod gu=r ${mandir}/$manfile
    $sudo $chown \$USER: ${mandir}/$manfile
}
lwrap.uninstall()
{
    $sudo $rm -f $binfille
    $sudo $rm -f $manpath
}
lwrap.exclude()
{
    $cat<<-LWRAPEXCLUDE>.git/info/exclude
Makefile
Makefile.in
configure
config.log
config.status
autom4te.cache/
config.h
config.h.in
lwrap
lwrap.spec
lwrap.s
lwrap.verbose
lwrap.out
.*
*.o
*~
LWRAPEXCLUDE
}
lwrap.assembly()
{
    $gcc -O2 -S -o lwrap.s lwrap.c
}
lwrap.verbose()
{
    $gcc -c -g -O2 -Wa,-ahl=lwrap.verbose lwrap.c
}
lwrap.dot()
{
    local infile=\${1:?[infile gv]}
    local name=\$(basename \${infile/.gv/})
    $dot -Tpng \$infile -o /tmp/\$name.png
    $chown \$USER:users /tmp/\$name.png
    $chmod u=rw,go=r /tmp/\$name.png
}
lwrap.test()
{
    local language arg1 prefix1
    local filename=starwars
    local arglist="c80 c3 c20 c235"
    local languagelist="en sv fr cn jp zh"
    for language in \$languagelist;do
        for arg1 in \$arglist;do
            for prefix1 in \$arglist;do
                ./lwrap -\$arg1 <../test/\$prefix1.\$filename.\$language >/tmp/\$prefix1.\$arg1.\$filename.\$language
                $diff -c ../test/\$arg1.\$filename.\$language /tmp/\$prefix1.\$arg1.\$filename.\$language
                $rm -f /tmp/\$prefix1.\$arg1.\$filename.\$language
            done
        done
    done
}
lwrap.test.justify()
{
    local language arg1 prefix1
    local filename=starwars
    local arglist="j80 j3 j20 j235"
    local languagelist="en sv fr cn jp zh"
    for language in \$languagelist;do
        for arg1 in \$arglist;do
            for prefix1 in \$arglist;do
                ./lwrap -\$arg1 <../test/\$prefix1.\$filename.\$language  >/tmp/\$prefix1.\$arg1.\$filename.\$language
                $diff -c ../test/\$arg1.\$filename.\$language /tmp/\$prefix1.\$arg1.\$filename.\$language
                $rm -f /tmp/\$prefix1.\$arg1.\$filename.\$language
            done
        done
    done
}
lwrap.test.wc()
{
    local language arg1 prefix1
    local filename=starwars
    local arglist="c80 c3 c20 c235"
    local languagelist="en sv fr cn jp zh"
    local rest1 rest2
    for language in \$languagelist;do
        for arg1 in \$arglist;do
            for prefix1 in \$arglist;do
                ./lwrap -\$arg1 <../test/\$prefix1.\$filename.\$language >/tmp/\$prefix1.\$arg1.\$filename.\$language
                rest1=\$($tr -d '\n \t\b\f\r\t\v\0' <../test/\$prefix1.\$filename.\$language |wc -c)
                rest2=\$($tr -d '\n ' </tmp/\$prefix1.\$arg1.\$filename.\$language |wc -c)
                $rm -f /tmp/\$prefix1.\$arg1.\$filename.\$language
                [[ \$rest1 -eq \$rest2 ]] && continue;
                builtin echo -e "../test/\$prefix1.\$filename.\$languagea\n/tmp/\$prefix1.\$arg1.\$filename.\$language\n\$rest1:\$rest2"
            done
        done
    done
}
lwrap.compare.wc()
{
    local filepath=\${1:?[input file]}
    local filename=\$(basename \$filepath)
    local restfile=/tmp/.\$filename
    local rest1 rest2
    ./lwrap <\$filepath >\$restfile
    rest1=\$($tr -d '\n \t\b\f\r\t\v\0' <\$filepath|$wc -c)
    rest2=\$($tr -d '\n ' <\$restfile |$wc -c)
    $rm -f \$restfile
    [[ \$rest1 -eq \$rest2 ]] && continue;
    builtin echo -e "\$filepath\n\$restfile\n\$rest1:\$rest2"
}
lwrap.composite.wc()
{
    local lan arg filelist rest1 rest2 rest2file
    local filename=starwars
    local rest1file=/tmp/rest1.\$filename.comp
    local rest2file=/tmp/rest2.\$filename.comp
    local languagelist="en sv fr cn jp zh ger turk sp ned pol ko"
    for lan in \$languagelist;do
        filelist+="../test/\$filename.\$lan "
    done
    paste \$filelist >\$rest1file
    ./lwrap -c1 <\$rest1file >\$rest2file
    rest1=\$($tr -d '\n \t\b\f\r\t\v\0' <\$rest1file |wc -c)
    rest2=\$($tr -d '\n ' <\$rest2file |$wc -c)
    $rm -f \$rest1file \$rest2file
    [[ \$rest1 -eq \$rest2 ]] ||\
        builtin echo -e "\$rest1file\n\$rest2file\n\$rest1:\$rest2"
}
lwrap.testall()
{
    lwrap.test
    lwrap.test.justify
    lwrap.test.wc
    lwrap.composite.wc
}
lwrap.release()
{
    local branch=\${1:-alpha}
    g.push origin alpha
}
lwrap.indentall()
{
    $indent --linux-style --indent-level4 --no-tabs --tab-size4 \
    --line-length80 *.[c,h]
}
SUB
)
}
lwrap.substitute
builtin unset -f lwrap.substitute
