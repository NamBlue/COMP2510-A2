Some tests for assignment 2
---------------------------
There are 2 input files: input & input2

The following are the commands used to generate the output files
under Linux.  (It assumes that the program can be invoked as ./a2.)

# both sets of the same size
./a2 abc xyz < input > my-out01
./a2 ab bc < input > my-out02
./a2 abaca vwxyz < input > my-out03

# 2nd set is larger
./a2 aei vwxyz < input > my-out04

# 1st set is larger
./a2 abcdef xyz < input > my-out05
./a2 abacaba vwxyz < input > my-out06

# with escape characters:
./a2 '\n' x < input > my-out07
./a2 'a\nc' xyz < input > my-out08
./a2 'a\t\nc' wxyz < input > my-out09
./a2 '\\n' ab < input2 > my-out10
./a2 ei 'x\n' < input2 > my-out11
./a2 '\tu' 'x\n' < input2 > my-out12

# with ranges:
./a2 a-z A-Z < input > my-out13
./a2 A-Z a-z < input > my-out14
./a2 a-e xyz < input > my-out15

Notes:
- All input & output files are in Unix format
- The single quotes around arguments that use escape characters may or may
  not be necessary in cygwin
- The given tests are not exhaustive.  In particular, there are no tests
  that use both escape characters & ranges.

- You may be able to use the runtests script to run the tests in Linux or 
  cygwin.  Put your executable program (which must be named a2 in Linux or
  a2.exe in cygwin) in this directory (the a2tests directory) & type:

  ./runtests

  Note that the cmp program must be installed in order for this to work.  

aw
