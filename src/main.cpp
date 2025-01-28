#include <iostream>
#include "controllers/RoupaController.h"
#include "controllers/ClienteController.h"
#include "controllers/ItemDiversoController.h"
#include "controllers/VendaController.h"

// g++ main.cpp views/RoupaView.cpp views/ItemDiversoView.cpp views/ClienteView.cpp views/VendaView.cpp models/Roupa.cpp models/Produto.cpp models/ItemDiverso.cpp models/Cliente.cpp models/Venda.cpp dao/RoupaDAO.cpp dao/ItemDiversoDAO.cpp dao/ClienteDAO.cpp dao/VendaDAO.cpp controllers/RoupaController.cpp controllers/ItemDiversoController.cpp controllers/ClienteController.cpp controllers/VendaController.cpp -lsqlite3

int main(){

  // Abertura do banco de dados
  sqlite3* db;
  std::string DB_PATH = "database/database.db"; 
  if(sqlite3_open(DB_PATH.c_str(), &db) != SQLITE_OK){
    std::cerr << "Erro ao abrir database: " << sqlite3_errmsg(db);
    exit(1);
  } else {
    std::cout << "Sucesso ao conectar database! Inicializando sistema...\n\n";
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
  ItemDiversoController itemDiverso_controller(db);
  ClienteController cliente_controller(db);
  VendaController venda_controller(db);
  
  std::cout << "-------- Sistema de gerenciamento de comercio. --------\n";
  std::cout << "ALERTA! - Nao utilize 'espaço', ao inves disso utilize '-' ou '_'\n";
  std::cout << "Exemplo - Camisa_Polo ou Camisa-Polo\n\n";

  
  int opcao = 0;
  while(opcao != 20){
    std::cout << "Menu de ações:\n";
    std::cout << "1 - Adicionar uma roupa\n";
    std::cout << "2 - Exibir todas as roupas cadastradas\n";
    std::cout << "3 - Exibir apenas uma roupa cadastrada\n";
    std::cout << "4 - Atualizar a quantidade de peças de uma roupa\n";
    std::cout << "5 - Deletar uma roupa do cadastro\n";
    std::cout << "6 - Adicionar um item\n";
    std::cout << "7 - Exibir todos os itens cadastrados\n";
    std::cout << "8 - Exibir apenas um item cadastrado\n";
    std::cout << "9 - Atualizar a quantidade de itens\n";
    std::cout << "10 - Deletar um item do cadastro\n";
    std::cout << "11 - Adicionar um cliente\n";
    std::cout << "12 - Exibir todos os clientes cadastrados\n";
    std::cout << "13 - Exibir apenas um cliente cadastrado\n";
    std::cout << "14 - Atualizar dados de um cliente\n";
    std::cout << "15 - Deletar um cliente\n";
    std::cout << "16 - Gerar uma nova venda\n";
    std::cout << "20 - Fechar sistema\n";
    std::cout << "Escolha uma opção do menu de ações: ";
    std::cin >> opcao;

    switch (opcao){
      case 1:{
        roupa_controller.adicionarRoupa();
        std::cout << std::endl;
        break;
      }
      case 2:{
        roupa_controller.lerTodasRoupas();
        std::cout << std::endl;
        break;
      }
      case 3:{
        roupa_controller.lerRoupa();
        std::cout << std::endl;
        break;
      }
      case 4:{
        roupa_controller.atualizarQuantidadeRoupa();
        std::cout << std::endl;
        break;
      }
      case 5:{
        roupa_controller.removerRoupa();
        std::cout << std::endl;
        break;
      }
      case 6:{
        itemDiverso_controller.adicionarItemDiverso();
        std::cout << std::endl;
        break;
      }
      case 7:{
        itemDiverso_controller.lerTodosItemDiversos();
        std::cout << std::endl;
        break;
      }
      case 8:{
        itemDiverso_controller.lerItemDiverso();
        std::cout << std::endl;
        break;
      }
      case 9:{
        itemDiverso_controller.atualizarQuantidadeItemDiverso();
        std::cout << std::endl;
        break;
      }
      case 10:{
        itemDiverso_controller.removerItemDiverso();
        std::cout << std::endl;
        break;
      }
      case 11:{
        cliente_controller.adicionarCliente();
        std::cout << std::endl;
        break;
      }
      case 12:{
        cliente_controller.lerTodosClientes();
        std::cout << std::endl;
        break;
      }
      case 13:{
        cliente_controller.lerCliente();
        std::cout << std::endl;
        break;
      }
      case 14:{
        cliente_controller.atualizarDadosCliente();
        std::cout << std::endl;
        break;
      }
      case 15:{
        cliente_controller.removerCliente();
        std::cout << std::endl;
        break;
      }
      case 16:{
        venda_controller.comecarVenda();
        std::cout << std::endl;
        break;
      }
      case 20:{
        break;
      }
      default:
        std::cout << "Opcao invalida!\n";
        break;
    }
  }

  sqlite3_close(db);
  return 0;
}