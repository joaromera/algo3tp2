CXX=g++

STDFLAGS = -std=c++11 -O3 -Ofast

RM=rm -f

BINARIES = generator hiperconectados  

all: $(BINARIES)

generator: generator.o
	$(CXX) $(STDFLAGS) $^ -o generator

hiperconectados: hiperconectados.o prim.o kruskal.o kruskalpc.o
	$(CXX) $(STDFLAGS) $^ -o hiperconectados

%.o: %.cpp
	$(CXX) $(STDFLAGS) -c $<

clean:
	$(RM) *.o *.txt
	$(RM) $(BINARIES)