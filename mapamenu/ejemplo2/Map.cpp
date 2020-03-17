#include "Map.h"
#include "SFML/Graphics.hpp"
#include <iostream>


Map::Map(string s) {

//PARA EL MAPA
std::cout << "Creando mi Map..."<< endl ;
TiXmlDocument mapa(s);
  bool loadOkay =mapa.LoadFile();
  if (loadOkay)
	{std::cout<<"cargado"<< endl;}else{std::cout<<"no cargado";}
//datos
  TiXmlElement * data= mapa.FirstChildElement("map");
  data->QueryIntAttribute("width",&_width);
  std::cout<<_width<<endl;
    data->QueryIntAttribute("height",&_height);
    std::cout<<_height<<endl;
      data->QueryIntAttribute("tilewidth",&_tilewidth);
      std::cout<<_tilewidth<<endl;
        data->QueryIntAttribute("tileheight",&_tileheigh);
        std::cout<<_tileheigh<<endl;


//image
std::cout<<"img"<<endl;
TiXmlElement *img=data->FirstChildElement("tileset")->FirstChildElement("image");
const char *filename=img->Attribute("source");
std::cout<<filename<<endl;

_tilesettexture.loadFromFile("resources/tilebase.png");
//capas
  TiXmlElement *layer = data->FirstChildElement("layer");
    while (layer)
    {
      _numlayers++;
      layer=layer->NextSiblingElement("layer");
    }

std::cout<<"layers"<<endl;

data=data->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
//reservando memoria para mapa
_tilemap=new int**[_numlayers];
for(int i=0;i<_numlayers;i++){
  _tilemap[i]=new int*[_height];
}
for(int l=0;l<_numlayers;l++){
  for (int y= 0; y < _height; y++){
  _tilemap[l][y]=new int[_width];
  }
}
//reserva memoria Sprites
_tilemapSprite=new sf::Sprite***[_numlayers];
for(int i=0;i<_numlayers;i++){
  _tilemapSprite[i]=new sf::Sprite**[_height];
}
for(int i=0;i<_numlayers;i++){
  for(int y=0;y<_height;y++){
    _tilemapSprite[i][y]=new sf::Sprite*[_width];
    for(int x=0;x<_width;x++){
      _tilemapSprite[i][y][x]=new sf::Sprite();
    }
  }
}
std::cout<<"reservado"<<endl;
//cargando los gids
for(int l=0; l<_numlayers;l++){
  for(int y=0; y<_height;y++){
    for(int x=0; x<_width;x++){
      data->QueryIntAttribute("gid", &_tilemap[l][y][x]);
      //siguiente tile
      data=data->NextSiblingElement("tile");

    }
  }
}
int cont=0;
std::cout<<"gids"<<endl;
  //arraysprites
  for(int l=0; l<_numlayers;l++){
    for(int y=0; y<_height;y++){
      for(int x=0; x<_width;x++){
        int gid=_tilemap [l][y][x]-1;

        
          std::cout<<"gid>0"<<endl;
          _tilemapSprite[l][y][x]=new sf::Sprite(_tilesettexture,{0+(gid*32),0+(gid*32),32,32});
          std::cout<<"gid>0"<<endl;
          _tilemapSprite[l][y][x]->setPosition(112+(x*_tilewidth),64+(y*_tileheigh));
          cont++;
        
      }
    }
  }
  std::cout<< cont<<endl;
std::cout<<"arraysprites"<<endl;
}
void Map::setactivelayer(int layer){
  _activelayer=layer;
}

void Map::draw(sf::RenderWindow& window){

    for(int y=0; y<_height;y++){
      for(int x=0; x<_width;x++){
        if(_tilemapSprite[_activelayer][y][x]!=NULL){
          window.draw(*(_tilemapSprite[_activelayer][y][x]));
        }
      }
    }
  
}