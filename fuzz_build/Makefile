
FLAGS=-fsanitize=fuzzer,address,undefined  -fno-omit-frame-pointer

all: ../src/Details/*.cpp ../src/fuzzing/*.cpp
	clang++ -I"../3rdparty/GSL/include" -std=c++17 -g -O1 $(FLAGS) ../src/Details/*.cpp ../src/fuzzing/*.cpp -o n_indexedfuzzer

