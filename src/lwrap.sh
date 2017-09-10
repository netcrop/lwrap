declare -Ax Lwrap
lwrap.substitute()
{
  local cmd i cmdlist='sed shred perl readlink dirname sudo
  basename cat ls id cut bash man mktemp egrep date env mv
  cp chmod ln chown rm printf touch head mkdir find file
  make autoheader automake autoconf diff gcc dot indent
  which tr wc'
  for cmd in $cmdlist;do
    i="$(which $cmd)"
    if [[ -z $i ]];then
      \builtin \printf "%s\n" "missing $cmd"
    fi
    Lwrap["$cmd"]="${i:-:}"
  done
  Lwrap[perl_version]="$(${Lwrap[perl]} -e 'print $^V')"
  \builtin \source <(${Lwrap[cat]}<<-SUB

lwrap.info()
{
 ${Lwrap[cat]}<<-LWRAPINFO
  https://en.wikipedia.org/wiki/UTF-8
  http://www.utf8-chartable.de/
LWRAPINFO
}
lwrap.config()
{
  ${Lwrap[make]} clean &&\
  ${Lwrap[rm]} -f Makefile Makefile.in configure config.h.in config.h \
    config.log config.status
  ${Lwrap[rm]} -rf autom4te.cache
  ${Lwrap[autoheader]} &&\
  ${Lwrap[automake]} &&\
  ${Lwrap[autoconf]} configure.ac >configure &&\
  ${Lwrap[chmod]} u=rwx configure
  ./configure
}
lwrap.clean()
{
  touch .deps/lwrap.Po
  make clean
  ${Lwrap[rm]} -f Makefile Makefile.in configure config.h.in config.h \
    config.log config.status lwrap.spec lwrap.s lwrap.out \
    lwrap.verbose verify *.*~
  ${Lwrap[rm]} -rf autom4te.cache
}
lwrap.make()
{
  lwrap.indentall
  ${Lwrap[make]} clean
  touch .deps/lwrap.Po
  ${Lwrap[make]} -j4 CFLAGS='-g -O2 -w'
}
lwrap.install()
{
  local binpath=\${1:-lwrap}
  local binfile=\$(${Lwrap[basename]} \$binpath)
  local bindir=\${2:-/usr/local/bin}
  local manfile=\${binfile}.1
  ${Lwrap[cp]} -f \$binpath \$bindir/\$binfile
  ${Lwrap[chmod]} gu=rx \$bindir/\$binfile
  ${Lwrap[chown]} \$USER: \$bindir/\$binfile
  ${Lwrap[cp]} -f \$manfile /usr/local/man/man1/\$manfile
  ${Lwrap[chmod]} gu=r /usr/local/man/man1/\$manfile
  ${Lwrap[chown]} \$USER: /usr/local/man/man1/\$manfile
}
lwrap.uninstall()
{
  local binpath=\${1:-/usr/local/bin/lwrap}
  local manpath=\${2:-/usr/local/man/man1/lwrap.1}
  ${Lwrap[rm]} -f \$binpath
  ${Lwrap[rm]} -f \$manpath
}
lwrap.exclude()
{
  ${Lwrap[cat]}<<-LWRAPEXCLUDE>.git/info/exclude
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
  ${Lwrap[gcc]} -O2 -S -o lwrap.s lwrap.c
}
lwrap.verbose()
{
  ${Lwrap[gcc]} -c -g -O2 -Wa,-ahl=lwrap.verbose lwrap.c
}
lwrap.dot()
{
  local infile=\${1:?[infile gv]}
  local name=\$(basename \${infile/.gv/})
  ${Lwrap[dot]} -Tpng \$infile -o /tmp/\$name.png
  ${Lwrap[chown]} \$USER:users /tmp/\$name.png
  ${Lwrap[chmod]} u=rw,go=r /tmp/\$name.png
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
        ${Lwrap[diff]} -c ../test/\$arg1.\$filename.\$language /tmp/\$prefix1.\$arg1.\$filename.\$language
        ${Lwrap[rm]} -f /tmp/\$prefix1.\$arg1.\$filename.\$language
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
        ./lwrap -\$arg1 <../test/\$prefix1.\$filename.\$language >/tmp/\$prefix1.\$arg1.\$filename.\$language
        ${Lwrap[diff]} -c ../test/\$arg1.\$filename.\$language /tmp/\$prefix1.\$arg1.\$filename.\$language
        ${Lwrap[rm]} -f /tmp/\$prefix1.\$arg1.\$filename.\$language
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
        rest1=\$(${Lwrap[tr]} -d '\n \t\b\f\r\t\v\0' <../test/\$prefix1.\$filename.\$language |wc -c)
        rest2=\$(${Lwrap[tr]} -d '\n ' </tmp/\$prefix1.\$arg1.\$filename.\$language |wc -c)
        ${Lwrap[rm]} -f /tmp/\$prefix1.\$arg1.\$filename.\$language
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
  rest1=\$(${Lwrap[tr]} -d '\n \t\b\f\r\t\v\0' <\$filepath|${Lwrap[wc]} -c)
  rest2=\$(${Lwrap[tr]} -d '\n ' <\$restfile |${Lwrap[wc]} -c)
  ${Lwrap[rm]} -f \$restfile
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
  rest1=\$(${Lwrap[tr]} -d '\n \t\b\f\r\t\v\0' <\$rest1file |wc -c)
  rest2=\$(${Lwrap[tr]} -d '\n ' <\$rest2file |${Lwrap[wc]} -c)
  ${Lwrap[rm]} -f \$rest1file \$rest2file
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
lwrap.indent()
{
  local infile=\${1:?[c,h file]}
  local tmpfile=\$(mktemp)
  indent --linux-style --indent-level2 --no-tabs --tab-size2 \$infile -o \$tmpfile
  local change="\$(${Lwrap[diff]} --brief \$infile \$tmpfile)"
  if [[ X\$change == X ]];then
    ${Lwrap[rm]} -f \$tmpfile
    return
  fi
  ${Lwrap[mv]} \$tmpfile \$infile
  ${Lwrap[rm]} -f \$infile~
}
lwrap.indentall()
{
  local indent=\$(${Lwrap[which]} indent)
  [[ x\$indent == x ]] && return
  [[ -x \$indent ]] || return
  local i;
  for i in *.c *.h;do
    lwrap.indent \$i
  done
}
lwrap.comments()
{
  local infile=\${1:?[infile]}
  local tmpfile=\$(mktemp)
  local i;
  for i in *.c *.h;do
    ${Lwrap[cat]} \$infile \$i > \$tmpfile
    ${Lwrap[mv]} \$tmpfile \$i
  done
}
SUB
)
}
lwrap.substitute
builtin unset -f lwrap.substitute
builtin unset Lwrap
