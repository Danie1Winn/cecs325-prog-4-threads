# Name: Daniel Winn
# Class (CECS 325-02)
# Project Name (Prog 4 - Threads)
# Due Date (11/4/2025)
#
# I certify that this program is my own original work. I did not copy any part of this program from
# any other source. I further certify that I typed each and every line of code in this program.

echo "=======Start======="
date
echo My machine has this many processors
nproc # this is for Windows machines
#sysctl -n hw.ncpu # this is for Mac machines
echo Generating 1000000 random numbers
sleep 1
./generate 1000000 -1000000 1000000 # use 1 million numbers for this run
sleep 1
echo Starting system sort
sleep 1
{ time sort -n numbers.dat > systemsort.out; } 2>> sortrace.log
#{ time sort -n numbers.dat > systemsort.out; } 2>&1>> sortrace.log # modification for Mac
sleep 1
echo Starting my sort
sleep 1
{ time ./mysort numbers.dat mysort.out 16; } 2>> sortrace.log # this line is for Windows
#{ time ./mysort numbers.dat mysort.out 16; } 2>&1>> sortrace.log # modification for Mac computers
sleep 1
ls -l systemsort.out
ls -l mysort.out
echo Comparing systemsort.out to mysort.out
diff systemsort.out mysort.out 2>> sortrace.log
echo All done
echo "=======End======="
date