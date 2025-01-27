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
      marca TEXT NOT NULL
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

  std::cout << "ALERTA! - Nao utilize 'espaço', ao inves disso utilize '-' ou '_' " << std::endl;

  std::cout << "Exemplo - Camisa_Polo ou Camisa-Polo" << std::endl;
  
  int opcao;
  while(opcao != 10){
    std::cout << "Menu de acoes\n";
    std::cout << "1 - Adicionar uma roupa.\n";
    std::cout << "2 - Mostrar roupas cadastradas.\n";
    std::cout << "3 - Atualizar roupas cadastrada\n";
    std::cout << "4 - Deletar roupas cadastradas\n";
    std::cout << "5 - Adicionar Item Diverso\n";
    std::cout << "6 - Mostrar itens diversos cadastrados.\n";
    std::cout << "7 - Atualizar a quantidade de um item cadastrado.\n";
    std::cout << "8 - Deletar um item salvo no estoque\n";
    std::cout << "9 - Ler Item Diverso\n";
    std::cout << "10 - Fechar sistema.\n";
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
      roupa_controller.atualizarQuantidadeRoupa();
      break;
    }
    case 4:{
      roupa_controller.removerRoupa();
      break;
    }
    case 5:{
      itemDiverso_controller.adicionarItemDiverso();
      break;
    }
    case 6:{
      itemDiverso_controller.lerTodosItemDiversos();
      break;
    }
    case 7:{
      itemDiverso_controller.atualizarQuantidadeItemDiverso();
      break;
    }
    case 8: {
      itemDiverso_controller.removerItemDiverso();
    }
    case 9: {
      itemDiverso_controller.lerItemDiverso();
    }
    default:
      break;
    }
  }
  return 0;
}