#include <iostream>
#include "controllers/RoupaController.h"
#include "controllers/ItemDiversoController.h"

// g++ main.cpp views/RoupaView.cpp views/ItemDiversoView.cpp models/Roupa.cpp models/Produto.cpp models/ItemDiverso.cpp dao/RoupaDAO.cpp dao/ItemDiversoDAO.cpp controllers/RoupaController.cpp controllers/ItemDiversoController.cpp -lsqlite3

int main(){
  // Abertura do banco de dados
  sqlite3* db;
  std::string DB_PATH = "database/database.db"; 
  if(sqlite3_open(DB_PATH.c_str(), &db) != SQLITE_OK){
    std::cerr << "Erro ao abrir database: " << sqlite3_errmsg(db);
    exit(1);
  } else {
    std::cout << "Sucesso ao conectar database! Inicializar sistema...\n";
  }

  
  // Criação da tabela de roupas
  std::string sql = R"(
    CREATE TABLE IF NOT EXISTS roupas (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      nome TEXT NOT NULL,
      quantidade INTEGER NOT NULL,
      tamanho TEXT NOT NULL
    );
  )";

  char* errMsg = nullptr;
  if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
    std::cerr << "Erro ao criar tabela de roupas: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  // Criação da tabela de clientes
  sql = R"(
    CREATE TABLE IF NOT EXISTS clientes (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      nome TEXT NOT NULL,
      telefone TEXT NOT NULL,
      email TEXT NOT NULL
    );
  )";

  if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
    std::cerr << "Erro ao criar tabela de clientes: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  // Criação da tabela de itens_diversos
  sql = R"(
    CREATE TABLE IF NOT EXISTS itens_diversos (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      nome TEXT NOT NULL,
      quantidade INTEGER NOT NULL,
      tipo TEXT NOT NULL
    );
  )";

  if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
    std::cerr << "Erro ao criar tabela de clientes: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  // Controllers para rodar programa
  RoupaController roupa_controller(db);
  // ItemDiversoController 
  ItemDiversoController itemDiverso_controller(db);
  
  std::cout << "-------- Sistema de gerenciamento de comercio. --------\n";
  
  int opcao;
  while(opcao != 7){
    std::cout << "Menu de acoes\n";
    std::cout << "1 - Adicionar uma roupa.\n";
    std::cout << "2 - Mostrar roupas cadastradas.\n";
    std::cout << "3 - Adicionar Item Diverso\n";
    std::cout << "4 - Mostrar itens diversos cadastrados.\n";
    std::cout << "5 - Atualizar a quantidade de um item cadastrado.\n";
    std::cout << "6 - Deletar um item salvo no estoque\n";
    std::cout << "7 - Fechar sistema.\n";
    std::cout << "Escolha uma opcao do menu de acoes: ";
    std::cin >> opcao;

    switch (opcao){
    case 1:{
      roupa_controller.adicionarRoupa();
      break;
    }
    case 2:{
      roupa_controller.lerTodasRoupas();
      break;
    }
    case 3:{
      itemDiverso_controller.adicionarItemDiverso();
      break;
    }
    case 4:{
      itemDiverso_controller.lerTodosItemDiversos();
      break;
    }
    case 5:{
      itemDiverso_controller.atualizarQuantidadeItemDiverso();
      break;
    }
    case 6:{
      itemDiverso_controller.removerItemDiverso();
      break;
    }
    case 7:{
      break;
    }
    default:
      break;
    }
  }
  return 0;
}