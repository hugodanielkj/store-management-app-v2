#include <iostream>
#include "controllers/RoupaController.h"
#include "controllers/ClienteController.h"
#include "controllers/ItemDiversoController.h"

//g++ main.cpp views/RoupaView.cpp views/ClienteView.cpp views/ItemDiversoView.cpp models/Roupa.cpp models/Produto.cpp models/ItemDiverso.cpp  models/Cliente.cpp dao/RoupaDAO.cpp dao/ClienteDAO.cpp dao/ItemDiversoDAO.cpp controllers/RoupaController.cpp controllers/ClienteController.cpp controllers/ItemDiversoController.cpp -lsqlite3

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
      telefone TEXT NOT NULL,
      email TEXT NOT NULL
    );
  )";

  if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
    std::cerr << "Erro ao criar tabela de clientes: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  // Controllers
  RoupaController roupa_controller(db);
  ClienteController cliente_controller(db);
  ItemDiversoController itemDiverso_controller(db);
  
  std::cout << "-------- Sistema de gerenciamento de comercio. --------\n";
  
  int opcao = 0;
  while(opcao != 9){
    std::cout << "\nMenu de acoes\n";
    std::cout << "--- Roupas ---\n";
    std::cout << "1 - Adicionar uma roupa\n";
    std::cout << "2 - Mostrar roupas cadastradas\n";
    std::cout << "3 - Atualizar quantidade de pecas de uma roupa\n";
    std::cout << "4 - Deletar uma roupa do cadastro\n";
    std::cout << "--- Clientes ---\n";
    std::cout << "5 - Adicionar um cliente\n";
    std::cout << "6 - Mostrar clientes cadastrados\n";
    std::cout << "7 - Atualizar dados de um cliente\n";
    std::cout << "8 - Deletar um cliente\n";
    std::cout << "9 - Fechar sistema\n";
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
      }
      case 4:{
        itemDiverso_controller.lerTodosItemDiversos();
      }
      case 5:{
        cliente_controller.adicionarCliente();
        break;
      }
      case 6:{
        cliente_controller.lerTodosClientes();
        break;
      }
      case 9:{
        break;
      }
      default:{
        std::cout << "Opcao invalida!\n";
        break;
      }
    }
  }

  sqlite3_close(db);
  return 0;
}
