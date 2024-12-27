#ifndef ROUPA_CONTROLLER_H
#define ROUPA_CONTROLLER_H

// Responsavel por controlar acoes feitas com roupa
#include "Roupa.h"

class RoupaController{
  public:
    void adicionarRoupa();
    void lerRoupa();
    void lerTodasRoupas();
    void atualizarQuantidadeRoupa();
    void removerRoupa();
};

#endif