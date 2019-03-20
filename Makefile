 main:
	g++ test/main.cpp src/Node/Node.cpp src/Graph/Graph.cpp -o test/test -std=c++11
	./test/test