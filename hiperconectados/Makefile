CXX=g++

STDFLAGS = -std=c++17 -Wall -Wextra -pedantic -O3 -Ofast

RM=rm -f

BINARIES = hiperconectados  

all: $(BINARIES)

hiperconectados: hiperconectados.o
	$(CXX) $(STDFLAGS) $^ -o hiperconectados

%.o: %.cpp
	$(CXX) $(STDFLAGS) -c $<

clean:
	$(RM) *.o *.txt
	$(RM) $(BINARIES)