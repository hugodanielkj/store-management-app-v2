#include "VendaDAO.h"
#include <iostream>

VendaDAO::VendaDAO(sqlite3* _db): db(_db) {}


bool VendaDAO::salvar(const Venda& venda){
  for(int i=0;i<venda.getProdutos().size();i++){
    std::string sql = "INSERT INTO " + venda.getCliente() + "_tabela_venda (produto, quantidade, data) VALUES('" + venda.getProdutos()[i] + "', " + std::to_string(venda.getQuantidadesDeProdutos()[i]) +", '" + venda.getData() + "');";

    std::cout << sql << std::endl;

    char* mensagemErro = nullptr;
    int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &mensagemErro);
    if(exit != SQLITE_OK){
      std::cerr << "Erro para adicionar Venda: " << mensagemErro << std::endl;
      sqlite3_free(mensagemErro);
      return false;
    }
  }

  return true;
}

bool VendaDAO::produtosCorrespondemAosItensAdicionados(std::vector<std::string> produtos){
  return true;
}

int VendaDAO::getUltimoId(std::string cliente){
  std::string sql = "SELECT MAX(id) FROM "+ cliente +"_tabela_venda;";
  sqlite3_stmt* stmt;

  if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
    throw std::runtime_error("Erro ao preparar consulta para obter o último ID.");
  }

  // Executar a consulta e obter o resultado
  int ultimoID = 1;
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