# Advanced Tool for Log Analysis and Statistics - A.T.L.A.S.
This is a tool for analyzing apache log files and generating statistics. This project is still in early development, so
the program can't do very much, for now.

## Makefile Targets
### `make all`
Compiles the main program and creates an executable called _atlas_.

### `make test`
Compiles the unit test and creates an executable called _utest_. The first time you run this command, the _Catch Test
Framework_ single header file will be downloaded automatically from
[here](https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp "catch.cpp").  
[More information on the Catch Test Framework here.](https://github.com/philsquared/Catch "catch.cpp")

### `make doc`
Creates html documentation. The main page is located in _doc/html/index.html_.

**NOTE:** [_Doxygen_](http://www.stack.nl/~dimitri/doxygen/) has to be installed on your system. If you want to see
call- and include-graphs in the generated documentation, you also have to have [_Graphviz_](http://www.graphviz.org/)
installed.

### `make clean`
Deletes all build files (object files and executables).

### `make destroy`
Deletes everything make has ever created (includes downloaded libraries and documentation). After running this command,
your repo should look as if it was freshly cloned from Github.

## Running ATLAS
To use ATLAS, simply pipe your log file into stdin like this: `./atlas < mylogfile.log`. ATLAS will print the number of
requests and the number of bytes sent and received for each day.

## Log Format
If you're using the Apache web server, this format will work: `%%h %%u %%t %%m %%s %%I %%O "%U" "%{Referer}i"`. If you
want a more detailed specification, you have to take a look at the source code of `parseLogEntry()`.

_Version_ 0.4.0
