To run the code :

gcc 2017csb1189_lab6.c -o addresses
./addresses 19986


Calculations :

pageNumber = virtualAddress/(2^12);
offset = virtualAddress - pageNumber * (2^12);