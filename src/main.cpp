#include <iostream>
#include "controllers/RoupaController.h"
#include "controllers/ClienteController.h"
#include "controllers/ItemDiversoController.h"
#include "controllers/VendaController.h"

//g++ main.cpp views/RoupaView.cpp views/ClienteView.cpp views/ItemDiversoView.cpp views/VendaView.cpp models/Roupa.cpp models/Produto.cpp models/ItemDiverso.cpp  models/Cliente.cpp models/Venda.cpp dao/RoupaDAO.cpp dao/ClienteDAO.cpp dao/ItemDiversoDAO.cpp dao/VendaDAO.cpp controllers/RoupaController.cpp controllers/ClienteController.cpp controllers/ItemDiversoController.cpp controllers/VendaController.cpp -lsqlite3

int main(){
  // Abertura do banco de dados
  sqlite3* db;
  std::string DB_PATH = "database/database.db"; 
  if(sqlite3_open(DB_PATH.c_str(), &db) != SQLITE_OK){
    std::cerr << "Erro ao abrir database: " << sqlite3_errmsg(db);
    exit(1);
  } else {
    std::cout << "Sucesso ao conectar database! Inicializar sistema...\n\n";
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

  // Controllers
  RoupaController roupa_controller(db);
  ClienteController cliente_controller(db);
  ItemDiversoController itemDiverso_controller(db);
  VendaController venda_controller(db);
  
  std::cout << "-------- Sistema de gerenciamento de comercio. --------\n";

  std::cout << "ALERTA! - Nao utilize 'espaço', ao inves disso utilize '-' ou '_'\n";

  std::cout << "Exemplo - Camisa_Polo ou Camisa-Polo\n\n";
  
  int opcao = 0;
  while(opcao != 15){
    std::cout << "\nMenu de acoes\n\n";
    std::cout << "--- Roupas ---\n";
    std::cout << "1 - Adicionar uma roupa\n";
    std::cout << "2 - Mostrar roupas cadastradas\n";
    std::cout << "3 - Atualizar quantidade de pecas de uma roupa\n";
    std::cout << "4 - Deletar uma roupa do cadastro\n\n";
    std::cout << "--- Clientes ---\n";
    std::cout << "10 - Adicionar um cliente\n";
    std::cout << "11 - Mostrar clientes cadastrados\n";
    std::cout << "12 - Atualizar dados de um cliente\n";
    std::cout << "13 - Deletar um cliente\n";
    std::cout << "14 - Gerar uma venda\n";
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
      case 8:{
        itemDiverso_controller.removerItemDiverso();
        break;
      }
      case 9:{
        itemDiverso_controller.lerItemDiverso();
        break;
      }
      case 10:{
        cliente_controller.adicionarCliente();
        break;
      }
      case 11:{
        cliente_controller.lerTodosClientes();
        break;
      }
      case 12:{
        //cliente_controller.atualizarDadosCliente();
      }
      case 13:{
        //cliente_controller.removerCliente();
      }
      case 14:{
        venda_controller.comecarVenda();
        break;
      }
      default:
        break;
    }
  }

  sqlite3_close(db);
  return 0;
}
