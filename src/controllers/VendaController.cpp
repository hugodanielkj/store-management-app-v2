#include "VendaController.h"
#include "../views/VendaView.h"
#include "../dao/VendaDAO.h"
#include <stdexcept>

VendaController::VendaController(sqlite3* _db): db(_db) {}

void VendaController::comecarVenda(){
  VendaView view;
  VendaDAO dao(db);

  try {
    // Pede as informacoes de venda para o cliente
    Venda venda = view.obterDadosVenda();
    if(dao.salvar(venda)){
      view.exibirMensagem("Venda adicionada com sucesso!\n");
    }
  } catch (std::invalid_argument &err) {
    view.exibirMensagem(err.what());
  }

  // Salva a venda no banco de dados
}

void VendaController::exibirVenda(){

}