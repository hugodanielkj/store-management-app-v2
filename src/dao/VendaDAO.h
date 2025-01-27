#ifndef VENDA_DAO_H
#define VENDA_DAO_H

#include <sqlite3.h>
#include "../models/Venda.h"

class VendaDAO{
  public:
    VendaDAO(sqlite3* _db);

    // Operacoes CRUD Essenciais
    bool salvar(const Venda& venda);
    Venda capturar(std::string cliente);
    bool atualizar(std::string cliente);

    // Operacoes auxiliares
    int getUltimoId();

  private:
    sqlite3* db;
};

#endif