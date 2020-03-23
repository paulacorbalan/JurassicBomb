#ifndef CONTEXTO_H
#define CONTEXTO_H

#pragma once
#include "states.h"
#include <iostream>

class Contexto{

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

private:
  // the stack of states
  vector<States*> states;

  bool m_running;
};

#endif