#include "ItemDiversoDAO.h"
#include <iostream>

ItemDiversoDAO::ItemDiversoDAO(sqlite3* _db): db(_db) {}

bool ItemDiversoDAO::salvar(const ItemDiverso& ItemDiverso){
  std::string sql = "INSERT INTO ItemDiversos (nome, quantidade, tipo) VALUES('" + ItemDiverso.getNome() + "', " + std::to_string(ItemDiverso.getQuantidade()) +", '" + ItemDiverso.getTipo() + "');";

  char* mensagemErro = nullptr;
  int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &mensagemErro);
  if(exit != SQLITE_OK){
    std::cerr << "Erro para adicionar ItemDiverso: " << mensagemErro << std::endl;
    sqlite3_free(mensagemErro);
    return false;
  }

  std::cout << "ItemDiverso adicionada com sucesso!" << std::endl;
  return true;
}

ItemDiverso ItemDiversoDAO::capturar(int id){
  std::string sql = "SELECT * FROM ItemDiversos WHERE id = ?;";

  sqlite3_stmt* stmt;
  if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
    std::cerr << "Erro ao fazer insercao: " << sqlite3_errmsg(db) << std::endl;
    throw std::runtime_error("Erro ao capturar ItemDiversos para mostrar ao usuario.");
  }

  if(sqlite3_bind_int(stmt, 1, id) != SQLITE_OK){
    std::cerr << "Erro ao dar bind_text: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    throw std::runtime_error("Erro ao capturar ItemDiversos para mostrar ao usuario.");
  }

  ItemDiverso ItemDiverso;

  if(sqlite3_step(stmt) == SQLITE_ROW){
    ItemDiverso.setNome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    ItemDiverso.setQuantidade(sqlite3_column_int(stmt, 2));
    ItemDiverso.setTipo(reinterpret_cast<const char*>(sqlite3_column_text(stmt,3)));
  } else {
    std::cerr << "Erro: Nenhuma ItemDiverso encontrada com o ID fornecido." << std::endl;
    sqlite3_finalize(stmt);
    throw std::runtime_error("ItemDiverso não encontrada");
  }
  sqlite3_finalize(stmt);

  return ItemDiverso;
}

int ItemDiversoDAO::getUltimoId(){
  std::string sql = "SELECT MAX(id) FROM ItemDiversos;";
  sqlite3_stmt* stmt;

  if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
    throw std::runtime_error("Erro ao preparar consulta para obter o último ID.");
  }

  // Executar a consulta e obter o resultado
  int ultimoID = -1;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    // Verificar se o resultado não é NULL
    if (sqlite3_column_type(stmt, 0) != SQLITE_NULL) {
        ultimoID = sqlite3_column_int(stmt, 0); // Recuperar o valor do ID
    } else {
        std::cerr << "Tabela está vazia, nenhum ID encontrado." << std::endl;
    }
  } else {
    std::cerr << "Erro ao executar consulta: " << sqlite3_errmsg(db) << std::endl;
  }

  sqlite3_finalize(stmt);   // Finalizar consulta

  return ultimoID;
}