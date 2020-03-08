#include "mimodulo2.h"

#include <iostream>

MiModulo2::MiModulo2(string s) {
  std::cout << "Creando mi modulo2...";
  TiXmlDocument mapa(s);
  mapa.LoadFile();
  mapa.Print();
}