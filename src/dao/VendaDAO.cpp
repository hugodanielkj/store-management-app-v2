#include "VendaDAO.h"
#include <iostream>

VendaDAO::VendaDAO(sqlite3* _db): db(_db) {}

bool VendaDAO::salvar(const Venda& venda){
  std::string sql = "INSERT INTO itens_diversos (nome, quantidade, tipo) VALUES('" + venda.getProduto() + "', " + std::to_string(venda.getQuantidade()) +", '" + venda.getData() + "');";

  char* mensagemErro = nullptr;
  int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &mensagemErro);
  if(exit != SQLITE_OK){
    std::cerr << "Erro para adicionar Venda: " << mensagemErro << std::endl;
    sqlite3_free(mensagemErro);
    return false;
  }

  std::cout << "Venda adicionada com sucesso!" << std::endl;
  return true;
}

/*
Venda VendaDAO::capturar(std::string cliente){
  std::string sql = "SELECT * FROM itens_diversos WHERE id = ?;";

  sqlite3_stmt* stmt;
  if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
    std::cerr << "Erro ao fazer insercao: " << sqlite3_errmsg(db) << std::endl;
    throw std::runtime_error("Erro ao capturar itens_diversos para mostrar ao usuario.");
  }

  if(sqlite3_bind_int(stmt, 1, id) != SQLITE_OK){
    std::cerr << "Erro ao dar bind_text: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    throw std::runtime_error("Erro ao capturar itens_diversos para mostrar ao usuario.");
  }

  Venda venda;

  if(sqlite3_step(stmt) == SQLITE_ROW){
    venda.setProduto(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    venda.setQuantidade(sqlite3_column_int(stmt, 2));
    venda.setData(reinterpret_cast<const char*>(sqlite3_column_text(stmt,3)));
  } else {
    std::cerr << "Erro: Nenhuma Venda encontrada com o ID fornecido." << std::endl;
    sqlite3_finalize(stmt);
    throw std::runtime_error("Venda não encontrada");
  }
  sqlite3_finalize(stmt);

  return venda;
}
*/

int VendaDAO::getUltimoId(){
  std::string sql = "SELECT MAX(id) FROM itens_diversos;";
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