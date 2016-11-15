# Advanced Tool for Log Analysis and Statistics - A.T.L.A.S.
This is a tool for analyzing apache log files and generating statistics. This project is still in early development, so
the program can't do very much, for now.

## Building ATLAS
To build ATLAS simply run `./make.py`, which will automatically generate a makefile, run `make` and execute the program.

If you're wondering what the CMakeLists.txt is for: I just need that so CLion works properly but I don't really know
how CMake works so I'm using the Python script. If you know CMake, you can use that, too.

## Running ATLAS
To use ATLAS, simply pipe your log file into stdin like this: `./atlas < mylogfile.log`. ATLAS will print the number of
requests and the number of bytes sent and received for each day.

## Building / Running Unit Tests
Works the same way as building the main project, except that you run `./make.py test`.

**NOTE:** You have to have the _Catch test framework_ single header located at inc/catch.hpp. You can download that one 
[here](https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp "catch.cpp").  
[More information on the Catch test framework here.](https://github.com/philsquared/Catch "catch.cpp")

## Docs, Bro?
The documentation can be generated using [_Doxygen_](http://www.stack.nl/~dimitri/doxygen/). Once you have _Doxygen_
installed, `cd` into the root project folder and run `doxygen`. This will create the documentation pages in the folder
doc/html. Open doc/html/index.html to view the main page of the documentation.

## Log Format
If you're using the Apache web server, this format will work: `%t#%h#%u#%s#%I#%O#%U#%{Referer}i#%m`. There is a more
detailed specification in the documentation of `parseLogEntry()`.

_Version_ 0.2
