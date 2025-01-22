#ifndef ROUPA_CONTROLLER_H
#define ROUPA_CONTROLLER_H

// Responsavel por controlar acoes feitas com roupa
#include "../models/Roupa.h"
#include <sqlite3.h>

class RoupaController{
  public:
    RoupaController(sqlite3* _db);
    void adicionarRoupa();
    void lerRoupa();
    void lerTodasRoupas();
    void atualizarQuantidadeRoupa();
    void removerRoupa();

  private:
    sqlite3* db;
};

#endif