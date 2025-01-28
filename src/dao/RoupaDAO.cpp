#include "RoupaDAO.h"
#include <iostream>

RoupaDAO::RoupaDAO(sqlite3* _db): db(_db) {}

bool RoupaDAO::salvar(const Roupa& roupa){
  std::string sql = "INSERT INTO roupas (nome, quantidade, tamanho) VALUES('" + roupa.getNome() + "', " + std::to_string(roupa.getQuantidade()) +", '" + roupa.getTamanho() + "');";

  char* mensagemErro = nullptr;
  int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &mensagemErro);
  if(exit != SQLITE_OK){
    std::cerr << "Erro para adicionar roupa: " << mensagemErro << std::endl;
    sqlite3_free(mensagemErro);
    return false;
  }

  std::cout << "Roupa adicionada com sucesso!" << std::endl;
  return true;
}

Roupa RoupaDAO::capturarId(int id){
  std::string sql = "SELECT * FROM roupas WHERE id = ?;";

  sqlite3_stmt* stmt;
  if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
    std::cerr << "Erro ao fazer insercao: " << sqlite3_errmsg(db) << std::endl;
    throw std::runtime_error("Erro ao capturar roupas para mostrar ao usuario.");
  }

  if(sqlite3_bind_int(stmt, 1, id) != SQLITE_OK){
    std::cerr << "Erro ao dar bind_text: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    throw std::runtime_error("Erro ao capturar roupas para mostrar ao usuario.");
  }

  Roupa roupa;

  if(sqlite3_step(stmt) == SQLITE_ROW){
    roupa.setNome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    roupa.setQuantidade(sqlite3_column_int(stmt, 2));
    roupa.setTamanho(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
  } else {
    std::cerr << "Erro: Nenhuma roupa encontrada com o ID fornecido." << std::endl;
    sqlite3_finalize(stmt);
    throw std::runtime_error("Roupa não encontrada");
  }
  sqlite3_finalize(stmt);

  return roupa;
}

bool RoupaDAO::existeEssaRoupa(std::string& nome) {
    std::string sql = "SELECT COUNT(1) FROM roupas WHERE nome = ?;";
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

Roupa RoupaDAO::capturarNome(const std::string &nome) {
    std::string sql = "SELECT * FROM roupas WHERE nome = ?;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Erro ao preparar consulta: " + std::string(sqlite3_errmsg(db)));
    }

    // Faz o bind do nome na consulta
    if (sqlite3_bind_text(stmt, 1, nome.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Erro ao fazer o bind do nome: " + std::string(sqlite3_errmsg(db)));
    }

    Roupa roupa;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        roupa.setNome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        roupa.setQuantidade(sqlite3_column_int(stmt, 2));
        roupa.setTamanho(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    } else {
        sqlite3_finalize(stmt);
        throw std::runtime_error("roupa não encontrada com o nome fornecido: " + nome);
    }

    sqlite3_finalize(stmt);  // Finaliza o statement
    return roupa;
}



std::vector<int> RoupaDAO::obterIdsValidos() {
    std::string sql = "SELECT id FROM roupas;";
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

bool RoupaDAO::atualizar(const Roupa& roupa) {
    std::string sql = "UPDATE roupas SET quantidade = ? WHERE nome = ?;";

    sqlite3_stmt* stmt;
    // Preparar a consulta SQL
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Fazer o bind dos parâmetros (quantidade e nome)
    if (sqlite3_bind_int(stmt, 1, roupa.getQuantidade()) != SQLITE_OK) {
        std::cerr << "Erro ao fazer bind do parâmetro 'quantidade': " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    if (sqlite3_bind_text(stmt, 2, roupa.getNome().c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
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
    std::cout << "Roupa atualizado com sucesso!" << std::endl;

    return true;
}

bool RoupaDAO::deletar(const std::string& nome) {
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
