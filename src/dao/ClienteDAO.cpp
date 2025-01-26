#include "ClienteDAO.h"
#include <iostream>

ClienteDAO::ClienteDAO(sqlite3* _db): db(_db) {}

bool ClienteDAO::salvar(const Cliente& cliente){
  std::string sql = "INSERT INTO clientes (nome, telefone, email) VALUES('" + cliente.getNome() + "', '" + cliente.getTelefone() + "', '" + cliente.getEmail() + "');";

  char* mensagemErro = nullptr;
  int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &mensagemErro);
  if(exit != SQLITE_OK){
    std::cerr << "Erro para adicionar cliente: " << mensagemErro << std::endl;
    sqlite3_free(mensagemErro);
    return false;
  }

  std::cout << "Cliente adicionado com sucesso!" << std::endl;
  return true;
}

Cliente ClienteDAO::capturar(int id){
  std::string sql = "SELECT * FROM clientes WHERE id = ?;";

  sqlite3_stmt* stmt;
  if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
    std::cerr << "Erro ao fazer insercao: " << sqlite3_errmsg(db) << std::endl;
    throw std::runtime_error("Erro ao capturar clientes para mostrar ao usuario.");
  }

  if(sqlite3_bind_int(stmt, 1, id) != SQLITE_OK){
    std::cerr << "Erro ao dar bind_text: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    throw std::runtime_error("Erro ao capturar clientes para mostrar ao usuario.");
  }

  Cliente cliente;

  if(sqlite3_step(stmt) == SQLITE_ROW){
    cliente.setNome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    cliente.setTelefone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    cliente.setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
  } else {
    std::cerr << "Erro: Nenhum cliente encontrado com o ID fornecido." << std::endl;
    sqlite3_finalize(stmt);
    throw std::runtime_error("Cliente não encontrado");
  }
  sqlite3_finalize(stmt);

  return cliente;
}

int ClienteDAO::getUltimoId(){
  std::string sql = "SELECT MAX(id) FROM clientes;";
  sqlite3_stmt* stmt;

  if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
    throw std::runtime_error("Erro ao preparar consulta para obter o último ID.");
  }

  int ultimoID = -1;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    if (sqlite3_column_type(stmt, 0) != SQLITE_NULL) {
        ultimoID = sqlite3_column_int(stmt, 0);
    } else {
        std::cerr << "Tabela está vazia, nenhum ID encontrado." << std::endl;
    }
  } else {
    std::cerr << "Erro ao executar consulta: " << sqlite3_errmsg(db) << std::endl;
  }

  sqlite3_finalize(stmt);

  return ultimoID;
}
