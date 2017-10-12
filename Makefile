
files=main.cc task.cc

O2:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O2 -o main_O2.out ${files} && ./main_O2.out data/knap.inst.dat

O3:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -O3 -o main_O3.out ${files} && ./main_O3.out

Ofast:
	g++ -std=c++11 -g -pedantic -Wall -Wextra -Ofast -o main_Ofast.out ${files} && ./main_Ofast.out
