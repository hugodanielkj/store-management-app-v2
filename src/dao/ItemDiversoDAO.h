#ifndef ITEMDIVERSO_DAO_H
#define ITEMDIVERSO_DAO_H

#include <sqlite3.h>
#include "../models/ItemDiverso.h"

class ItemDiversoDAO{
  public:
    ItemDiversoDAO(sqlite3* _db);

    // Operacoes CRUD Essenciais
    bool salvar(const ItemDiverso& itemDiverso);
    ItemDiverso capturar(int id);
    ItemDiverso capturar(std::string nome);
    bool atualizar(const ItemDiverso& itemDiverso);   // Atualiza atributos de uma roupa
    bool deletar(std::string nome);

    // Operacoes auxiliares
    int getUltimoId();
    bool existeEsseItemDiverso(std::string nome);

    private:
      sqlite3* db;
};

#endif