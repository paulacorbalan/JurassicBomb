#ifndef CONTEXTO_H
#define CONTEXTO_H

#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class States;

class Contexto{

  private:
    // the stack of states
    std::vector<States*> states;

    bool m_running;

  public:
    
    void Init();
    void Cleanup();

    void ChangeState(States* state);
    void PushState(States* state);
    void PopState();

    void HandleEvents();
    void Update();
    void Draw();

    bool Running() { return m_running; }
    void Quit() { m_running = false; }

};

#endif