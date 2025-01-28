#include "ItemDiversoDAO.h"
#include <iostream>
#include <vector>

ItemDiversoDAO::ItemDiversoDAO(sqlite3* _db): db(_db) {}

bool ItemDiversoDAO::salvar(const ItemDiverso& ItemDiverso){
  std::string sql = "INSERT INTO itens_diversos (nome, quantidade, marca) VALUES('" + ItemDiverso.getNome() + "', " + std::to_string(ItemDiverso.getQuantidade()) +", '" + ItemDiverso.getMarca() + "');";

  char* mensagemErro = nullptr;
  int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &mensagemErro);
  if(exit != SQLITE_OK){
    std::cerr << "Erro para adicionar ItemDiverso: " << mensagemErro << std::endl;
    sqlite3_free(mensagemErro);
    return false;
  }

  std::cout << "ItemDiverso adicionada com sucesso!" << std::endl;
  return true;
}

ItemDiverso ItemDiversoDAO::capturarId(int id){
  std::string sql = "SELECT * FROM itens_diversos WHERE id = ?;";

  sqlite3_stmt* stmt;
  
  // Prepara a consulta
  if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
    std::cerr << "Erro ao preparar consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    throw std::runtime_error("Erro ao preparar consulta para capturar ItemDiverso por ID.");
  }

  // Faz o bind do ID na consulta
  if(sqlite3_bind_int(stmt, 1, id) != SQLITE_OK){
    sqlite3_finalize(stmt);
    std::cerr << "Erro ao fazer bind do ID: " << sqlite3_errmsg(db) << std::endl;
    throw std::runtime_error("Erro ao associar o ID na consulta SQL.");
  }

  ItemDiverso itemDiverso;

  // Executa a consulta e verifica o resultado
  if(sqlite3_step(stmt) == SQLITE_ROW){
    itemDiverso.setNome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    itemDiverso.setQuantidade(sqlite3_column_int(stmt, 2));
    itemDiverso.setMarca(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
  } else {
    sqlite3_finalize(stmt);
    std::cerr << "Erro: Nenhum ItemDiverso encontrado com o ID fornecido: " << id << std::endl;
    throw std::runtime_error("ItemDiverso não encontrado com o ID fornecido.");
  }

  sqlite3_finalize(stmt);
  return itemDiverso;
}


bool ItemDiversoDAO::existeEsseItemDiverso(std::string& nome) {
    std::string sql = "SELECT COUNT(1) FROM itens_diversos WHERE nome = ?;";
    sqlite3_stmt* stmt;

    // Preparar a consulta
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Fazer o bind do parâmetro 'nome'
    if (sqlite3_bind_text(stmt, 1, nome.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Erro ao fazer bind do parâmetro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Executar a consulta
    bool existe = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Verificar se o COUNT(1) é maior que 0
        int count = sqlite3_column_int(stmt, 0);
        existe = (count > 0);
    } else {
        std::cerr << "Erro ao executar consulta: " << sqlite3_errmsg(db) << std::endl;
    }

    // Finalizar a consulta
    sqlite3_finalize(stmt);
    return existe;
}

ItemDiverso ItemDiversoDAO::capturarNome(const std::string &nome) {
    std::string sql = "SELECT * FROM itens_diversos WHERE nome = ?;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Erro ao preparar consulta: " + std::string(sqlite3_errmsg(db)));
    }

    // Faz o bind do nome na consulta
    if (sqlite3_bind_text(stmt, 1, nome.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Erro ao fazer o bind do nome: " + std::string(sqlite3_errmsg(db)));
    }

    ItemDiverso itemDiverso;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        itemDiverso.setNome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        itemDiverso.setQuantidade(sqlite3_column_int(stmt, 2));
        itemDiverso.setMarca(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    } else {
        sqlite3_finalize(stmt);
        throw std::runtime_error("ItemDiverso não encontrado com o nome fornecido: " + nome);
    }

    sqlite3_finalize(stmt);  // Finaliza o statement
    return itemDiverso;
}

bool ItemDiversoDAO::atualizar(const ItemDiverso& itemDiverso) {
    std::string sql = "UPDATE itens_diversos SET quantidade = ? WHERE nome = ?;";

    sqlite3_stmt* stmt;
    // Preparar a consulta SQL
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Fazer o bind dos parâmetros (quantidade e nome)
    if (sqlite3_bind_int(stmt, 1, itemDiverso.getQuantidade()) != SQLITE_OK) {
        std::cerr << "Erro ao fazer bind do parâmetro 'quantidade': " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    if (sqlite3_bind_text(stmt, 2, itemDiverso.getNome().c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Erro ao fazer bind do parâmetro 'nome': " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Executar a consulta
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao executar a consulta de atualização: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Finalizar a consulta
    sqlite3_finalize(stmt);
    std::cout << "ItemDiverso atualizado com sucesso!" << std::endl;

    return true;
}

bool ItemDiversoDAO::deletar(const std::string &nome) {
    std::string sql = "DELETE FROM itens_diversos WHERE nome = ?;";

    sqlite3_stmt *stmt;
    // Prepara o comando SQL
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar a consulta para deletar o item: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Faz o bind do nome no comando SQL
    if (sqlite3_bind_text(stmt, 1, nome.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Erro ao fazer o bind do nome: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Executa o comando DELETE
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao deletar o item: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt); // Finaliza o statement
    return true; // Retorna sucesso
}

std::vector<int> ItemDiversoDAO::obterIdsValidos() {
    std::string sql = "SELECT id FROM itens_diversos;";
    sqlite3_stmt* stmt;
    std::vector<int> idsValidos;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return idsValidos;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);  // Recupera o ID
        idsValidos.push_back(id);
    }

    sqlite3_finalize(stmt);
    return idsValidos;
}
