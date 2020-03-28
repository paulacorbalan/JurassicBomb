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

void Mundo::Event(sf::Event event,sf::RenderWindow &window){
      switch (event.type) {
        case sf::Event::Closed:
          Contexto::Instance()->Quit();
          window.close();
        break;
        //case sf::Event::MouseButtonPressed:

        case sf::Event::KeyPressed:
              ///Verifico si se pulsa alguna tecla de movimiento
          switch (event.key.code) {
            case 60:
              if(lvlactual<mapas.size()){
                  mapas[lvlactual]->terminar();
              }
                //Cualquier tecla desconocida se imprime por pantalla su código
          default:
            std::cout << " code " << event.key.code << std::endl;
          break;

        }
      }
  //COSAS DEL MUNDO CUANDO PULSAS ALGO
}

void Mundo::Update(sf::RenderWindow &window) {


   if (mapas[lvlactual]->fin())
    {
      std::cout<<"cambiar mapa\n";

      lvlactual++;
      if (!(lvlactual<mapas.size()))
      {
        //RENICIAR MUNDO
        this->renicio();
        //MENU INICIAL
        Menu::Instance()->reinicio();
       ChangeState(Contexto::Instance(),Menu::Instance());
      }
      
      //Reiniciar contador
      hud->reiniciocrono();
    }
    hud->Update(); 
 }

 void Mundo::renicio(){
         std::cout<<dif<<lvls<<lvlactual<<"\n";
   dif=0;
   lvls=0;
   lvlactual=0;
        //vaciar mapas TARREGLAR
        mapas.clear();
         std::cout<<dif<<lvls<<lvlactual<<"\n";
 }

 void Mundo::Draw(sf::RenderWindow &window){
  mapas[lvlactual]->draw(window);
  hud->draw(window);
  
 }