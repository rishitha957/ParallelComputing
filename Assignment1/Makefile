all: dump_graph 1

dump_graph: rand_graph.cpp
	g++ -o dump_graph rand_graph.cpp

1: 1.cpp
	mpic++ -o 1 1.cpp

clean:
	rm dump_graph 1