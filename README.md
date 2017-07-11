# lwrap
Line wrap text input according to user defined line width.

## Compile install and uninstall

* For linux/unix system:  
required header files:  
stdio.h  
stdlib.h  
unistd.h  
These commands do Not use ```sudo``` for best security concern.
```
> cd src/
> source lwrap.sh
> lwrap.config
> lwrap.make
> lwrap.install
> man lwrap
> lwrap.uninstall
```
## Use with vim
:[range]!lwrap -j60

![Alt text](misc/lwrap.gif?raw=true "")

## Examples

Output screenshots in different natural languages.

![Alt text](misc/examples.gif?raw=true "")

## For developers

Function calls

<img src="misc/functions.png" height="282" width="282">

Timeline

<img src="misc/timeline.png" height="232" width="382">

## Reporting a bug and security issues

github.com/netcrop/lwrap/issues

## License

[GNU General Public License version 2 (GPLv2)](https://github.com/netcrop/lwrap/COPYING)
