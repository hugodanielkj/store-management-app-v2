#ifndef ITEMDIVERSO_DAO_H
#define ITEMDIVERSO_DAO_H

#include "../../app/sqlite3.h"
#include "../models/ItemDiverso.h"
#include <vector>

class ItemDiversoDAO{
  public:
    ItemDiversoDAO(sqlite3* _db);

    // Operacoes CRUD Essenciais
    bool salvar(const ItemDiverso& itemDiverso);
    ItemDiverso capturarId(int id);
    ItemDiverso capturarNome(const std::string& nome);
    bool atualizar(const ItemDiverso& itemDiverso);   // Atualiza atributos de uma roupa
    bool deletar(const std::string& nome);
    std::vector<int> obterIdsValidos();

    // Operacoes auxiliares
    int getUltimoId();
    bool existeEsseItemDiverso(std::string& nome);

    private:
      sqlite3* db;
};

#endif