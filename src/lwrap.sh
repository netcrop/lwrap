lwrap.info()
{
  cat<<-EOF
  https://en.wikipedia.org/wiki/UTF-8
  http://www.utf8-chartable.de/
EOF
}
lwrap.config()
{
  make clean &&\
  rm -f Makefile Makefile.in configure config.h.in config.h \
  config.log config.status
  rm -rf autom4te.cache
  autoheader &&\
  automake &&\
  autoconf configure.ac >configure &&\
  chmod u=rwx configure
  ./configure
}
lwrap.clean()
{
  touch .deps/lwrap.Po
  make clean
  rm -f Makefile Makefile.in configure config.h.in config.h \
  config.log config.status lwrap.spec lwrap.s lwrap.out lwrap.verbose verify
  rm -rf autom4te.cache
}
lwrap.make()
{
  make clean
  touch .deps/lwrap.Po
  make -j4 CFLAGS='-g -O2 -w'
}
lwrap.install()
{
  local binpath=${1:?[bin file for install]}
  local binfile=$(basename $binpath)
  local bindir=$(dirname $binpath)
  local manfile=${binfile}.1
  cp -f $binpath /usr/local/bin/$binfile
  chmod gu=rx /usr/local/bin/$binfile
  chown :users /usr/local/bin/$binfile
  cp -f $bindir/$manfile /usr/local/man/man1/$manfile
  chmod gu=r /usr/local/man/man1/$manfile
  chown :users /usr/local/man/man1/$manfile
}
lwrap.uninstall()
{
  rm -f /usr/local/bin/lwrap
  rm -f /usr/local/man/man1/lwrap.1
}
lwrap.exclude()
{
  cat<<-EOF>.git/info/exclude
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
EOF
}
lwrap.assembly()
{
  gcc -O2 -S -o lwrap.s lwrap.c
}
lwrap.verbose()
{
  gcc -c -g -O2 -Wa,-ahl=lwrap.verbose lwrap.c
}
lwrap.dot()
{
  local infile=${1:?[infile gv]}
  local name=$(basename ${infile/.gv/})
  dot -Tpng $infile -o /tmp/$name.png
  chown $USER:users /tmp/$name.png
  chmod u=rw,go=r /tmp/$name.png
}
lwrap.test()
{
  local language arg1 prefix1
  local filename=starwars
  local arglist="c80 c3 c20 c235"
  local languagelist="en sv fr cn jp zh"
  for language in $languagelist;do
    for arg1 in $arglist;do
      for prefix1 in $arglist;do
        ./lwrap -$arg1 <../test/$prefix1.$filename.$language >/tmp/$prefix1.$arg1.$filename.$language
        diff -c ../test/$arg1.$filename.$language /tmp/$prefix1.$arg1.$filename.$language
        rm -f /tmp/$prefix1.$arg1.$filename.$language
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
  for language in $languagelist;do
    for arg1 in $arglist;do
      for prefix1 in $arglist;do
        ./lwrap -$arg1 <../test/$prefix1.$filename.$language >/tmp/$prefix1.$arg1.$filename.$language
        diff -c ../test/$arg1.$filename.$language /tmp/$prefix1.$arg1.$filename.$language
        rm -f /tmp/$prefix1.$arg1.$filename.$language
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
  for language in $languagelist;do
    for arg1 in $arglist;do
      for prefix1 in $arglist;do
        ./lwrap -$arg1 <../test/$prefix1.$filename.$language >/tmp/$prefix1.$arg1.$filename.$language
        rest1=$(tr -d '\n \t\b\f\r\t\v\0' <../test/$prefix1.$filename.$language |wc -c)
        rest2=$(tr -d '\n ' </tmp/$prefix1.$arg1.$filename.$language |wc -c)
        rm -f /tmp/$prefix1.$arg1.$filename.$language
        [[ $rest1 -eq $rest2 ]] && continue;
        builtin echo -e "../test/$prefix1.$filename.$languagea\n/tmp/$prefix1.$arg1.$filename.$language\n$rest1:$rest2"
      done
    done
  done
}
lwrap.compare.wc()
{
  local filepath=${1:?[input file]}
  local filename=$(basename $filepath)
  local restfile=/tmp/.$filename
  local rest1 rest2
  ./lwrap <$filepath >$restfile
  rest1=$(tr -d '\n \t\b\f\r\t\v\0' <$filepath|wc -c)
  rest2=$(tr -d '\n ' <$restfile |wc -c)
  rm -f $restfile
  [[ $rest1 -eq $rest2 ]] && continue;
  builtin echo -e "$filepath\n$restfile\n$rest1:$rest2"
}
lwrap.composite.wc()
{
  local lan arg filelist rest1 rest2 rest2file
  local filename=starwars
  local rest1file=/tmp/rest1.$filename.comp
  local rest2file=/tmp/rest2.$filename.comp
  local languagelist="en sv fr cn jp zh ger turk sp ned pol ko"
  for lan in $languagelist;do
    filelist+="../test/$filename.$lan "
  done
  paste $filelist >$rest1file
  ./lwrap -c1 <$rest1file >$rest2file
  rest1=$(tr -d '\n \t\b\f\r\t\v\0' <$rest1file |wc -c)
  rest2=$(tr -d '\n ' <$rest2file |wc -c)
  rm -f $rest1file $rest2file
  [[ $rest1 -eq $rest2 ]] ||\
  builtin echo -e "$rest1file\n$rest2file\n$rest1:$rest2"
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
  local sourcedir=${1:?[source dir][target dir]}
  local targetdir=${2:?[target dir]}
  cp $sourcedir/*.gv $targetdir/
  sed "s;;;g" $sourcedir/lwrap.sh >$targetdir/lwrap.sh
}