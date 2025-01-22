#include <iostream>
#include "controllers/RoupaController.h"

// g++ main.cpp views/RoupaView.cpp models/Roupa.cpp models/Produto.cpp models/ItemDiverso.cpp dao/RoupaDAO.cpp controllers/RoupaController.cpp -lsqlite3

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

  // Criação da tabela, se não existir
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
    std::cerr << "Erro ao criar tabela: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  // Controllers para rodar programa
  RoupaController roupa_controller(db);
    // ItemDiversoController 
  
  std::cout << "-------- Sistema de gerenciamento de comercio. --------\n";
  
  int opcao;
  while(opcao != 5){
    std::cout << "Menu de acoes\n";
    std::cout << "1 - Adicionar uma roupa.\n";
    std::cout << "2 - Mostrar roupas cadastradas.\n";
    std::cout << "3 - Atualizar a quantidade de pecas de uma roupa.\n";
    std::cout << "4 - Deletar uma roupa do cadastro.\n";
    std::cout << "5 - Fechar sistema.\n";
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
    case 5:{
      break;
    }
    default:
      break;
    }
  }
  return 0;
}