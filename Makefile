a.out: main.o
	g++ main.o -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp magic.hh readmap.hh mapgraphic.hh textgraphic.hh agentgraphic.hh
	g++ -c main.cpp

clean:
	rm *.o a.out

run:
	./a.out
