#ifndef VENDA_CONTROLLER_H
#define VENDA_CONTROLLER_H

#include "../models/Venda.h"
#include <sqlite3.h>

class VendaController{
  public:
    VendaController(sqlite3* _db);
    void comecarVenda();
    void exibirVenda();

  private:
    sqlite3* db;
};

#endif