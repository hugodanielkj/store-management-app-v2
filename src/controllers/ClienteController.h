#ifndef CLIENTE_CONTROLLER_H
#define CLIENTE_CONTROLLER_H

// Responsavel por controlar acoes feitas com cliente
#include "../models/Cliente.h"
#include <sqlite3.h>

class ClienteController {
  public:
    ClienteController(sqlite3* _db);
    void adicionarCliente();
    void lerCliente();
    void lerTodosClientes();
    void atualizarDadosCliente();
    void removerCliente();

  private:
    sqlite3* db;
};

#endif
