exe: main.cpp
	clang++ -pthread -std=c++17 -o exe main.cpp src/Code.cpp src/Init.cpp src/Parser.cpp src/SymbolTable.cpp
