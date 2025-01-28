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

  sql = "CREATE TABLE IF NOT EXISTS "+ cliente.getNome() + R"(_tabela_venda (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      produto TEXT NOT NULL,
      quantidade INTEGER NOT NULL,
      data TEXT NOT NULL
    );
  )";

  mensagemErro = nullptr;
  exit = sqlite3_exec(db, sql.c_str(), 0, 0, &mensagemErro);
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
        sqlite3_finalize(stmt);
        throw std::runtime_error("Cliente não encontrado");
    }
    sqlite3_finalize(stmt);

    return cliente;
}


Cliente ClienteDAO::capturar(std::string nome){
    std::string sql = "SELECT * FROM clientes WHERE nome = ?;";

    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Erro ao capturar cliente por nome.");
    }

    if(sqlite3_bind_text(stmt, 1, nome.c_str(), -1, SQLITE_STATIC) != SQLITE_OK){
        std::cerr << "Erro ao vincular nome: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        throw std::runtime_error("Erro ao vincular nome do cliente.");
    }

    Cliente cliente;

    if(sqlite3_step(stmt) == SQLITE_ROW){
        cliente.setNome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        cliente.setTelefone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        cliente.setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    } else {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Cliente não encontrado");
    }
    sqlite3_finalize(stmt);

    return cliente;
}

bool ClienteDAO::atualizar(const Cliente& cliente) {
    std::cout << "\nQual informação você deseja atualizar?\n";
    std::cout << "1 - Telefone\n";
    std::cout << "2 - Email\n";
    std::cout << "Escolha uma opção: ";
    
    int opcao;
    std::cin >> opcao;

    std::string sql;
    std::string novo_valor;

    switch(opcao) {
        case 1:
            sql = "UPDATE clientes SET telefone = ? WHERE nome = ?;";
            std::cout << "Digite o novo telefone: ";
            std::cin >> novo_valor;
            break;
        case 2:
            sql = "UPDATE clientes SET email = ? WHERE nome = ?;";
            std::cout << "Digite o novo email: ";
            std::cin >> novo_valor;
            break;
        default:
            std::cout << "Opção inválida!\n";
            return false;
    }
    
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar atualização: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if(sqlite3_bind_text(stmt, 1, novo_valor.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
       sqlite3_bind_text(stmt, 2, cliente.getNome().c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Erro ao vincular valores: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    if(sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao atualizar cliente: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    std::cout << "Atualização realizada com sucesso!\n";
    return true;
}

bool ClienteDAO::deletar(std::string nome){
    std::string sql = "DELETE FROM clientes WHERE nome = ?;";
    
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
        std::cerr << "Erro ao preparar delete: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if(sqlite3_bind_text(stmt, 1, nome.c_str(), -1, SQLITE_STATIC) != SQLITE_OK){
        std::cerr << "Erro ao vincular nome: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    if(sqlite3_step(stmt) != SQLITE_DONE){
        std::cerr << "Erro ao deletar cliente: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
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

bool ClienteDAO::existeEsseCliente(std::string nome){
    std::string sql = "SELECT COUNT(*) FROM clientes WHERE nome = ?;";
    
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if(sqlite3_bind_text(stmt, 1, nome.c_str(), -1, SQLITE_STATIC) != SQLITE_OK){
        std::cerr << "Erro ao vincular nome: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    int count = 0;
    if(sqlite3_step(stmt) == SQLITE_ROW){
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return count > 0;
}
