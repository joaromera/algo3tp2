CXX=g++

STDFLAGS = -std=c++17 -Wall -Wextra -pedantic -O3 -Ofast

RM=rm -f

BINARIES = generator euclideangraphs hiperauditados astarvsdpq

all: $(BINARIES)

generator: generator.o
	$(CXX) $(STDFLAGS) $^ -o generator

euclideangraphs: euclideangraphs.o
	$(CXX) $(STDFLAGS) $^ -o euclideangraphs

hiperauditados: hiperauditados.o dijkstraold.o dijkstra.o dijkstrapq.o bellmanford.o floydwarshall.o dantzig.o
	$(CXX) $(STDFLAGS) $^ -o hiperauditados

astarvsdpq: astarvsdpq.o dijkstrapq.o
	$(CXX) $(STDFLAGS) $^ -o astarvsdpq

%.o: %.cpp
	$(CXX) $(STDFLAGS) -c $<

clean:
	$(RM) *.o *.txt
	$(RM) $(BINARIES)