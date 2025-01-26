#include "ItemDiversoController.h"
#include "../views/ItemDiversoView.h"
#include "../dao/ItemDiversoDAO.h"
#include <stdexcept>
#include <iostream>

ItemDiversoController::ItemDiversoController(sqlite3* _db): db(_db) {}

void ItemDiversoController::adicionarItemDiverso(){
  ItemDiversoDAO dao(db);
  ItemDiversoView view;
  ItemDiverso itemDiverso;

  while(true){    // Verifica se as informacoes da roupa estao corretas
    try {
      itemDiverso = view.obterDadoItemDiverso();   // Pede ao usuario informacoes da roupa
      view.exibirItemDiverso(itemDiverso);
      view.exibirMensagem("As informacoes da roupa acima estao corretas?(y/n)");
      if(!view.perguntarSimOuNao())
        throw std::invalid_argument("Repita a operacao.\n");
      break;
    } catch (std::invalid_argument &err) {
      view.exibirMensagem(err.what());
    }
  }

  if(dao.salvar(itemDiverso)){   // Salva roupa e retorna seu id
    view.exibirMensagem("Sucesso ao adicionar ItemDiverso.");
  } else {
    // Erro ao adicionar roupa
  }
}

/*
void RoupaController::lerRoupa(){
  RoupaDAO dao(db);
  RoupaView view;
  std::string nome = view.obterNomeRoupa();   // Obtem nome da roupa que se quer ler

  bool loop = true;
  while(loop){
    try {
      Roupa roupa = dao.capturar(nome);   // Constroi a roupa em questao
      // Verificar se roupa foi criada e lancar throw expcetion
      view.exibirRoupa(roupa);    // Exibe roupa para o usuario
      break;
    } catch (std::invalid_argument &err) {
      view.exibirMensagem("Erro: Nome invalido para a Roupa. Quer fazer a operacao novamente?\n");
      loop = view.perguntarSimOuNao();    // Usuario diz se quer refazer operacao ou nao
    }
  }
}
*/

void ItemDiversoController::lerTodosItemDiversos(){
  ItemDiversoDAO dao(db);
  ItemDiversoView view;

  int ultimo_id = dao.getUltimoId();
  std::cout << "TESTE TESTE " << ultimo_id << std::endl;
  view.exibirMensagem("-------------------------------------\n");
  view.exibirMensagem("Tabela de todas as ItemDiversos do estoque:\n");
  view.exibirMensagem("-------------------------------------\n");
  view.exibirMensagem("Nome      | Quantidade | Tipo\n");
  view.exibirMensagem("-------------------------------------\n");
  for(int i=1;i<=ultimo_id;i++){
    ItemDiverso itemDiverso = dao.capturar(i);
    view.exibirItemDiverso(itemDiverso);
    view.exibirMensagem("-------------------------------------\n");
  }
}

/*
void RoupaController::atualizarQuantidadeRoupa(){
  RoupaDAO dao(db);
  RoupaView view;
  std::string nome = view.obterNomeRoupa();

  bool loop = true;
  while(loop){
    try {
      if(!dao.existeEssaRoupa(nome))
        throw std::invalid_argument("Erro: Nome invalido para a Roupa. Quer fazer a operacao novamente?(y/n) ");
      Roupa roupa = dao.capturar(nome);   // Constroi a roupa em questao
      int quantidade = view.obterQuantidadeRoupa();   // Pede ao usuario quantidade da roupa
      roupa.setQuantidade(quantidade);    // Seta nova quantidade de roupas
      dao.atualizar(roupa);   // Atualiza quantidade de roupas no database
      view.exibirMensagem("Sucesso ao atualizar quantidade de roupas.\n");
      break;
    } catch (std::invalid_argument &err) {
      view.exibirMensagem(err.what());
      loop = view.perguntarSimOuNao();    // Usuario diz se quer refazer operacao ou nao
    }
  }
}

void RoupaController::removerRoupa(){
  RoupaDAO dao(db);
  RoupaView view;
  std::string nome = view.obterNomeRoupa();   // Pede para o usuario inserir nome de uma roupa

  bool loop = true;
  while(true){
    try{
      if(!dao.existeEssaRoupa(nome))    // Verifica se o nome da roupa existe
        throw std::invalid_argument("Erro: Nome invalido para a Roupa. Quer fazer a operacao novamente?(y/n) ");
      dao.deletar(nome);      // Deleta a roupa caso ela exista
    } catch (std::invalid_argument &err) {
      view.exibirMensagem(err.what());
      loop = view.perguntarSimOuNao();    // Usuario diz se quer refazer operacao ou nao
    }
  }
}
*/