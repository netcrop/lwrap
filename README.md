# lwrap
Line wrap text input according to user defined line width.

## Compile install and uninstall

* For linux/unix system:  
required header files:  
stdio.h  
stdlib.h  
unistd.h  
```
For best security precaution,
following commands do Not use sudo
> cd src/
> source lwrap.sh
> lwrap.config
> lwrap.make
> lwrap.install
> man lwrap
> lwrap.uninstall
```
## Using lwrap

   The most flexible way of using lwrap is to  
testing with different line width back and forth  
inside vim with e.g. command: `:[range]!lwrap -j50`.

![Alt text](misc/lwrap.gif?raw=true "")

## Examples

* Output screenshots in different natural languages.

  lwrap support unicode utf-8 codepage. The actual  
line width consistency depends on the input language  
font glyph width.

  The default line break is ascii space plus newline,  
which can be changed with command option to a single  
newline. This is because ascii space occasionally  
been used as word and name separator in asian languages.

![Alt text](misc/examples.gif?raw=true "")

## For developers

* Function calls

  One 255 elements array been created as a "filter" for each  
input byte. Each element is a struct pointer that pointing  
to one of 16 structs, which in turn contains functions that  
process each input byte.  
By doing this we avoid as many as possible if-else cluster.  
And keep the functions in minimal size.

  The same filter applys for the last byte before each line  
break. This time the struct pointer will execute another  
function call.

  It seems we introduced a lot of overhead by doing many  
function calls. But the benefits of decreased if-else cluster  
and maintainbility of functions overcome some hundred  
millisecounds in lost speed efficiency.

<img src="misc/functions.png" height="282" width="282">

* Timeline

  Three buffers been created for handling input bytes.  
We use library functions `fread` and `fwrite` to minimize  
the number of function calls. A short time delay been  
introduced for the first occurence of line break.  
And another one for initiation of write buffer.  
The big "O" notation of input stream through  
the entire program is constant.

<img src="misc/timeline.png" height="232" width="382">


* Test cases

  A subset combination of line breaks and languages  
based on  reference text files been created for each  
test run.  
`coreutils` commands `diff`,`tr`,and `wc` been used to  
calculate and compare the total number of bytes from  
input stream with output generated by `lwrap`.  
`valgrind` and `gdb` been used for detecting memory leak  
and debugging the source code.  
`graphviz` or `dot` been used to generate graphs.  

* Coding style

  The most flexible way is keep your preferred coding style  
and use the following command for all of your source code  
before commit and change back to your preferred style  
after your checkout:  
`> indent --linux-style --indent-level2 --no-tabs`  
```
Or use this bash function:
> cd src/
> source lwrap.sh
> lwrap.indentall
```

## Reporting a bug and security issues

github.com/netcrop/lwrap/issues

## License

[GNU General Public License version 2 (GPLv2)](https://github.com/netcrop/lwrap/COPYING)
