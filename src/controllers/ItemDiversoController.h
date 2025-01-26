#ifndef ITEMDIVERSO_CONTROLLER_H
#define ITEMDIVERSO_CONTROLLER_H

// Responsavel por controlar acoes feitas com roupa
#include "../models/ItemDiverso.h"
#include <sqlite3.h>

class ItemDiversoController{
  public:
    ItemDiversoController(sqlite3* _db);
    void adicionarItemDiverso();
    void lerItemDiverso();
    void atualizarQuantidadeItemDiverso();
    void lerTodosItemDiversos();
    void removerItemDiverso();

  private:
    sqlite3* db;
};

#endif