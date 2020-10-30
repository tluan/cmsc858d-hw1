# cmsc858d-hw1
https://rob-p.github.io/CMSC858D_F20/assignments/02_homework_01
Tu Luan 
Compile note: 
MakeLists.txt please add the dirctory for boost and divsufsort
bwocc.cpp is the driver file. 
I compile it from IDE so I do not haven makefile .


for the backward search, if only macthing found is in the last row of BWT, the b in [a,b) will go out of range, but a will remain to be the pointer to the right position 
