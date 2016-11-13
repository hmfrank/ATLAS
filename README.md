# Advanced Tool for Log Analysis and Statistics - A.T.L.A.S.
This is a tool for analyzing apache log files and generating statistics. There is no working release yet, so don't use
this tool for now.

# Building ATLAS
To build ATLAS simply run `./make.py`, which will automatically generate a makefile, run `make` and execute the program.

If you're wondering what the CMakeLists.txt is for: I just need that so CLion works properly but I don't really know
how CMake works so I'm using the Python script. If you know CMake, you can use that, too.

# Running Unit Tests
Works the same way as building the main project, except that you run `./make.py test`.

**NOTE:** You have to have the Catch test framework single header located at inc/catch.hpp. You can download that one 
[here](https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp "catch.cpp").  
[More information on the Catch test framework here.](https://github.com/philsquared/Catch "catch.cpp")

_Version_ 0.1
