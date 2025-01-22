#include "RoupaDAO.h"
#include <iostream>

RoupaDAO::RoupaDAO(sqlite3* _db): db(_db) {}

bool RoupaDAO::salvar(const Roupa& roupa){
  std::string sql = "INSERT INTO roupas (nome, quantidade, tamanho) VALUES('" + roupa.getNome() + "', " + std::to_string(roupa.getQuantidade()) +", '" + roupa.getTamanho() + "');";

  char* mensagemErro = nullptr;
  int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &mensagemErro);
  if(exit != SQLITE_OK){
    std::cerr << "Erro para adicionar roupa: " << mensagemErro << std::endl;
    sqlite3_free(mensagemErro);
    return false;
  }

  std::cout << "Roupa adicionada com sucesso!" << std::endl;
  return true;
}

Roupa RoupaDAO::capturar(int id){
  std::string sql = "SELECT * FROM roupas WHERE id = ?;";

  sqlite3_stmt* stmt;
  if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
    std::cerr << "Erro ao fazer insercao: " << sqlite3_errmsg(db) << std::endl;
    throw std::runtime_error("Erro ao capturar roupas para mostrar ao usuario.");
  }

  if(sqlite3_bind_int(stmt, 1, id) != SQLITE_OK){
    std::cerr << "Erro ao dar bind_text: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    throw std::runtime_error("Erro ao capturar roupas para mostrar ao usuario.");
  }

  Roupa roupa;

  if(sqlite3_step(stmt) == SQLITE_ROW){
    roupa.setNome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    roupa.setQuantidade(sqlite3_column_int(stmt, 2));
    roupa.setTamanho(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
  } else {
    std::cerr << "Erro: Nenhuma roupa encontrada com o ID fornecido." << std::endl;
    sqlite3_finalize(stmt);
    throw std::runtime_error("Roupa não encontrada");
  }
  sqlite3_finalize(stmt);

  return roupa;
}

int RoupaDAO::getUltimoId(){
  std::string sql = "SELECT MAX(id) FROM roupas;";
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

/*
Roupa RoupaDAO::capturar(std::string nome){

}
*/