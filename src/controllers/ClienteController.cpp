#include "ClienteController.h"
#include "../views/ClienteView.h"
#include "../dao/ClienteDAO.h"
#include <stdexcept>
#include <iostream>

ClienteController::ClienteController(sqlite3* _db): db(_db) {}

void ClienteController::adicionarCliente() {
  ClienteDAO dao(db);
  ClienteView view;
  Cliente cliente;

  while(true) {    // Verifica se as informacoes do cliente estao corretas
    try {
      cliente = view.obterDadosCliente();   // Pede ao usuario informacoes do cliente
      view.exibirCliente(cliente);
      view.exibirMensagem("As informacoes do cliente acima estao corretas?(y/n)");
      if(!view.perguntarSimOuNao())
        throw std::invalid_argument("Repita a operacao.\n");
      break;
    } catch (std::invalid_argument &err) {
      view.exibirMensagem(err.what());
    }
  }

  if(dao.salvar(cliente)) {   // Salva cliente e retorna seu id
    view.exibirMensagem("Sucesso ao adicionar Cliente.");
  } else {
    // Erro ao adicionar cliente
  }
}

void ClienteController::lerTodosClientes() {
  ClienteDAO dao(db);
  ClienteView view;

  int ultimo_id = dao.getUltimoId();
  view.exibirMensagem("-------------------------------------\n");
  view.exibirMensagem("Tabela de todos os clientes cadastrados:\n");
  view.exibirMensagem("-------------------------------------\n");
  view.exibirMensagem("Nome      | Telefone | Email\n");
  view.exibirMensagem("-------------------------------------\n");
  for(int i=1;i<=ultimo_id;i++){
    Cliente cliente = dao.capturar(i);
    view.exibirCliente(cliente);
    view.exibirMensagem("-------------------------------------\n");
  }
}
