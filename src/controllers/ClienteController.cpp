#include "ClienteController.h"
#include "../views/ClienteView.h"
#include "../dao/ClienteDAO.h"
#include <stdexcept>
#include <iostream>

// Inicializa o controller com a conexão do banco
ClienteController::ClienteController(sqlite3* _db): db(_db) {}

void ClienteController::adicionarCliente() {
    ClienteDAO dao(db);
    ClienteView view;
    Cliente cliente;

    // Loop pra confirmar se os dados estão corretos
    while(true) {
        try {
            cliente = view.obterDadosCliente();
            view.exibirCliente(cliente);
            view.exibirMensagem("As informacoes do cliente acima estao corretas?(y/n)");
            if(!view.perguntarSimOuNao())
                throw std::invalid_argument("Repita a operacao.\n");
            break;
        } catch (std::invalid_argument &err) {
            view.exibirMensagem(err.what());
        }
    }

    // Tenta salvar no banco
    if(dao.salvar(cliente)) {
        view.exibirMensagem("Sucesso ao adicionar Cliente.\n");
    } else {
        view.exibirMensagem("Erro ao adicionar Cliente.\n");
    }
}

void ClienteController::lerCliente() {
    ClienteDAO dao(db);
    ClienteView view;
    std::string nome = view.obterNomeCliente();

    // Loop de busca do cliente
    bool loop = true;
    while(loop) {
        try {
            if(!dao.existeEsseCliente(nome))
                throw std::runtime_error("Cliente não encontrado");
            Cliente cliente = dao.capturar(nome);
            view.exibirCliente(cliente);
            break;
        } catch (std::runtime_error &err) {
            view.exibirMensagem("Erro: Nome invalido para o Cliente. Quer fazer a operacao novamente?(y/n)\n");
            loop = view.perguntarSimOuNao();
            if (!loop) break;
            nome = view.obterNomeCliente();
        }
    }
}

void ClienteController::lerTodosClientes() {
    ClienteDAO dao(db);
    ClienteView view;

    // Mostra todos os clientes em formato tabela
    int ultimo_id = dao.getUltimoId();
    if(ultimo_id != -1){
        view.exibirMensagem("-------------------------------------\n");
        view.exibirMensagem("Tabela de todos os clientes cadastrados:\n");
        view.exibirMensagem("-------------------------------------\n");
        view.exibirMensagem("Nome      | Telefone | Email\n");
        view.exibirMensagem("-------------------------------------\n");
        for(int i=1;i<=ultimo_id;i++){
            try {
                Cliente cliente = dao.capturar(i);
                view.exibirCliente(cliente);
                view.exibirMensagem("-------------------------------------\n");
            } catch (std::runtime_error &err) {
                continue;
            }
        }
    }
}

void ClienteController::atualizarDadosCliente() {
    ClienteDAO dao(db);
    ClienteView view;
    std::string nome = view.obterNomeCliente();

    // Loop pra atualizar dados
    bool loop = true;
    while(loop) {
        try {
            if(!dao.existeEsseCliente(nome))
                throw std::runtime_error("Cliente não encontrado");
            
            Cliente cliente = dao.capturar(nome);
            if(dao.atualizar(cliente)) {
                view.exibirMensagem("Sucesso ao atualizar dados do cliente.\n");
            } else {
                view.exibirMensagem("Erro ao atualizar dados do cliente.\n");
            }
            break;
        } catch (std::runtime_error &err) {
            view.exibirMensagem("Erro: Nome invalido para o Cliente. Quer fazer a operacao novamente?(y/n)\n");
            loop = view.perguntarSimOuNao();
            if (!loop) break;
            nome = view.obterNomeCliente();
        }
    }
}

void ClienteController::removerCliente() {
    ClienteDAO dao(db);
    ClienteView view;
    std::string nome = view.obterNomeCliente();

    // Loop pra confirmar e remover cliente
    bool loop = true;
    while(loop) {
        try {
            if(!dao.existeEsseCliente(nome))
                throw std::runtime_error("Cliente não encontrado");
            
            view.exibirMensagem("Tem certeza que deseja remover este cliente?(y/n)\n");
            if(view.perguntarSimOuNao()) {
                if(dao.deletar(nome)) {
                    view.exibirMensagem("Cliente removido com sucesso.\n");
                } else {
                    view.exibirMensagem("Erro ao remover cliente.\n");
                }
            }
            break;
        } catch (std::runtime_error &err) {
            view.exibirMensagem("Erro: Nome invalido para o Cliente. Quer fazer a operacao novamente?(y/n)\n");
            loop = view.perguntarSimOuNao();
            if (!loop) break;
            nome = view.obterNomeCliente();
        }
    }
}
