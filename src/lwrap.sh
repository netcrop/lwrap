lwrap.substitute()
{
    local reslist devlist filename testdir languagelist arglist manfile \
    cmd perl_version i j k binpath binfile bindir prefix mandir manpath \
    cmdlist='sed shred perl readlink dirname sudo paste
    basename cat ls id cut bash man mktemp egrep date env mv
    cp chmod ln chown rm printf touch head mkdir find file
    make autoheader aclocal automake autoconf diff gcc which tr wc'

    declare -A Devlist=(
    [valgrind]='valgrind'
    [gdb]='gdb'
    [dot]='dot'
    [indent]='indent'
    [gprof]='gprof'
    )
    cmdlist="${Devlist[@]} $cmdlist"
    for cmd in $cmdlist;do
        i=($(\builtin type -afp $cmd 2>/dev/null))
        if [[ -z $i ]];then
            if [[ -z ${Devlist[$cmd]} ]];then
                reslist+=" $cmd"
            else
                devlist+=" $cmd"
            fi
        fi
        \builtin eval "local ${cmd//-/_}=${i:-:}"
    done
    [[ -z $reslist ]] ||\
    {
        \builtin printf "%s\n" \
        "$FUNCNAME says: ( $reslist ) These Required Commands are missing."
        return
    }
    [[ -z $devlist ]] ||\
    \builtin printf "%s\n" \
    "$FUNCNAME says: ( $devlist ) These Optional Commands for further development."

    perl_version="$($perl -e 'print $^V')"
    prefix=/usr/local/
    bindir=${prefix}/bin/
    mandir=${prefix}/man/man1/
    testdir='../test/'
    binpath='lwrap'
    binfile="$(basename ${binpath})"
    manpath="${binfile}.1"
    manfile="$(basename ${manpath})"
    filename='starwars'
    arglist="c80 c3 c20 c235"
    languagelist="en sv fr cn jp zh"
    
    \builtin \source <($cat<<-SUB

lwrap.debug()
{
    local args="./${binpath} -j80 -f ${testdir}/c20.starwars.en"
    args=\${@:-\$args}
    $gdb --args \$args
}
lwrap.valgrind()
{
    local args="./${binpath} -j80 -f ${testdir}/c20.starwars.en"
    args=\${@:-\$args}
    $valgrind --leak-check=full --show-leak-kinds=all \${args}
}
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
        config.log config.status gmon.out
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
        lwrap.verbose verify gmon.out *.*~
    $rm -rf autom4te.cache
}
lwrap.callgraph()
{
    local infile=\${1:?[text infile]}
    ./lwrap -j80 -f \${infile} >/dev/null 
    $gprof lwrap gmon.out >/tmp/lwrap.txt
}
lwrap.make.callgraph()
{
    $make clean
    touch .deps/lwrap.Po
    $make -j4 CFLAGS='-g3 -O2 -w -pg'
}
lwrap.make()
{
    $make clean
    touch .deps/lwrap.Po
    $make -j4 CFLAGS='-g3 -O2 -w'
}
lwrap.install()
{
    $sudo $cp -f $binpath $bindir/$binfile
    $sudo $chmod gu=rx,o=rx $bindir/$binfile
    $sudo $chown \$USER: $bindir/$binfile
    $sudo $cp -f $manpath ${mandir}/$manfile
    $sudo $chmod gu=r,o=r ${mandir}/$manfile
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
gmon.out
src/.deps
src/gmon.out
.*
*.o
*~
LWRAPEXCLUDE
}
lwrap.assembly()
{
    $gcc -g3 -O2 -S -o lwrap.s lwrap.c
}
lwrap.verbose()
{
    $gcc -c -g3 -O2 -Wa,-ahl=lwrap.verbose lwrap.c
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
   lwrap.test.justify
}
lwrap.test.justify()
{
    for i in $languagelist;do
        for j in $arglist;do
            for k in $arglist;do
                ./lwrap -\$j <${testdir}/\$k.$filename.\$i |\
                $diff -c ${testdir}/\$j.$filename.\$i - 
            done
        done
    done
}
lwrap.test.wc()
{
    local rest1 rest2
    for i in $languagelist;do
        for j in $arglist;do
            for k in $arglist;do
                ./lwrap -\$j <${testdir}/\$k.$filename.\$i >/tmp/\$k.\$j.$filename.\$i
              rest1=\$($tr -d '\n \t\b\f\r\t\v\0'<${testdir}/\$k.$filename.\$i |wc -c)
                rest2=\$($tr -d '\n ' </tmp/\$k.\$j.$filename.\$i |wc -c)
                $rm -f /tmp/\$k.\$j.$filename.\$i
                [[ \$rest1 -eq \$rest2 ]] && continue;
                builtin echo -e "${testdir}/\$k.$filename.\$i\n/tmp/\$k.\$j.$filename.\$i\n\$rest1:\$rest2"
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
    local rest1file=/tmp/rest1.$filename.comp
    local rest2file=/tmp/rest2.$filename.comp
    local languagelist="en sv fr cn jp zh ger turk sp ned pol ko"
    for lan in \$languagelist;do
        filelist+="${testdir}/$filename.\$lan "
    done
    $paste \$filelist >\$rest1file
    ./lwrap -c1 <\$rest1file >\$rest2file
    rest1=\$($tr -d '\n \t\b\f\r\t\v\0' <\$rest1file |wc -c)
    rest2=\$($tr -d '\n ' <\$rest2file |$wc -c)
    $rm -f \$rest1file \$rest2file
    [[ \$rest1 -eq \$rest2 ]] ||\
        builtin echo -e "\$rest1file\n\$rest2file\n\$rest1:\$rest2"
}
lwrap.testall()
{
    lwrap.test.justify
    lwrap.test.wc
    lwrap.composite.wc
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
