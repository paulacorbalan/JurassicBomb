#include "mundo.h"



Mundo* Mundo::jinstance=0;

  Mundo* Mundo::Instance() {
    if(jinstance==0){
      jinstance=new Mundo;
        std::cout<<"mundooinstance"; 
    }
    return jinstance;
  }

void Mundo::Inicializar() {
  std::cout<<"mundoiniciado\n";
  //crear mundo
    int dif=Menu::Instance()->GetDif();
    int lvls=Menu::Instance()->GetLvls();
    hud=new Tile();
    if(dif==0){

    }else if(dif==1){

    }else
    {
      for(int a=0;a<lvls;a++){
        string s="resources/"+to_string(dif)+"mapa"+to_string(a)+".tmx";
        std::cout<<s<<endl;

        std::cout<<"premap";
        Map* m=new Map(s);
        std::cout<<"prepush";
        mapas.push_back(m);

        std::cout<<"postpush";

      }

    }
    
}

void Mundo::Update(sf::Event event,sf::RenderWindow &window) {
   /* if (mapas[lvlactual]->fin())
    {
        std::cout<<"fin\n";
      lvlactual++;
      //Reiniciar contador
    }*/
  hud->Update();
 }

 void Mundo::Draw(sf::RenderWindow &window){
  mapas[lvlactual]->draw(window);
  hud->draw(window);
  
 }