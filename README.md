# Advanced Tool for Log Analysis and Statistics - A.T.L.A.S.
This is a tool for analyzing apache log files and generating statistics.

For each day in the log file, as well as for the entire log file, ATLAS counts the number of requests, the number of
unique uses, the number of received bytes and the number of sent bytes.

The log is read from `stdin`.
If you have actual log file, you can pipe it into `stdin` like this: `$ ./atlas [flags] < access.log`.

The result is printed to `stdout` in a whitespace-separated table.

## Command Line Options
### `--rows=`
Same as `-r=`

Specifies which rows are displayed.
If this option is omitted all rows are displayed.
You can specify any combination of the following flags.

**h** Display the table header.  
**d** Display daily summaries.  
**t** Display total summary.

**Example:** `--rows=ht` Shows the table header and total summary.

### `--columns=`
Same as `-c=`

Specifies which columns are displayed.
If this option is omitted all rows are displayed.
You can specify any combination of the following flags.

**d** Display date-column.  
**r** Display number-of-requests-column.  
**u** Display number-of-unique-users-column.  
**i** Display number-of-bytes-received-column.  
**o** Display number-of-bytes-sent-column.

### `--method=`
Same as `-m=`

Specifies which data structure is used to count the number of unique users.
You can specify _one_ of the following values.

**a** AVL-tree (Counted value is exact. Insertion: O(log(n)), Space: O(n))  
**h** HyperLogLog (Counted value might be a little off. Inserion: O(1), Space: O(log(log(n))), is very good for huge
      log files)

If this option is omitted, AVL-trees are used.
  
### `--days=`
Same as `-d=`

Specifies the maximum number of days in the log file.
The default value is 42 (6 weeks).
If your log file actually contains more days, the excess can not be analysed by ATLAS.
      

## Makefile Targets
### `make all`
Compiles the main program and creates an executable called _atlas_.
The first time you run this command, the AuD library will be donwnloaded from
[here](https://github.com/hmfrank/AuD "AuD").

### `make test`
Compiles the unit test and creates an executable called _utest_.
The first time you run this command, the _Catch Test Framework_ single header file will be downloaded automatically from
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
