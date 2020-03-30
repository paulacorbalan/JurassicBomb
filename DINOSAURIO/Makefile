LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: jurassic_boom

mapa.o: mapa.cpp
		g++ -c "mapa.cpp" -o mapa.o -std=c++11

dinosaurio.o: dinosaurio.cpp
		g++ -c "dinosaurio.cpp" -o dinosaurio.o -std=c++11

jurassic_boom: dinosaurio.o mapa.o
		@echo "** Construyendo..."
		g++ -o jurassic_boom dinosaurio.o mapa.o $(LIBS)