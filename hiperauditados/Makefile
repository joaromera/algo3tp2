CXX=g++

STDFLAGS = -std=c++17 -Wall -Wextra -pedantic -O3 -Ofast

RM=rm -f

BINARIES = generator euclideangraphs hiperauditados

all: $(BINARIES)

generator: generator.o
	$(CXX) $(STDFLAGS) $^ -o generator

euclideangraphs: euclideangraphs.o
	$(CXX) $(STDFLAGS) $^ -o euclideangraphs

hiperauditados: hiperauditados.o
	$(CXX) $(STDFLAGS) $^ -o hiperauditados

%.o: %.cpp
	$(CXX) $(STDFLAGS) -c $<

clean:
	$(RM) *.o *.txt
	$(RM) $(BINARIES)
