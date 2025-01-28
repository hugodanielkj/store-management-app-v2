#ifndef CLIENTE_DAO_H
#define CLIENTE_DAO_H

#include "../../app/sqlite3.h"
#include "../models/Cliente.h"

class ClienteDAO {
  public:
    ClienteDAO(sqlite3* _db);

    // Operacoes CRUD Essenciais
    bool salvar(const Cliente& cliente);
    Cliente capturar(int id);
    Cliente capturar(std::string nome);
    bool atualizar(const Cliente& cliente);   // Atualiza atributos de um cliente
    bool deletar(std::string nome);

    // Operacoes auxiliares
    int getUltimoId();
    bool existeEsseCliente(std::string nome);

  private:
    sqlite3* db;
};

#endif
