#include "RoupaController.h"
#include "RoupaView.h"
#include "RoupaDAO.h"
#include <stdexcept>

void RoupaController::adicionarRoupa(){
  RoupaDAO dao;
  RoupaView view;
  Roupa roupa = view.obterDadosRoupa();

  // Verificar se foi escrito os dados corretos para as roupas (utiliza-se view)

  if(dao.salvar(roupa)){   // Salva roupa e retorna seu id
    view.exibirMensagem("Sucesso ao adicionar Roupa.");
  } else {
    // Erro ao adicionar roupa
  }
}

void RoupaController::lerRoupa(){
  RoupaDAO dao;
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

void RoupaController::lerTodasRoupas(){
  RoupaDAO dao;
  RoupaView view;

  int ultimo_id = dao.getUltimoId();
  view.exibirMensagem("-------------------------------------\n");
  view.exibirMensagem("Tabela de todas as roupas do estoque:\n");
  view.exibirMensagem("-------------------------------------\n");
  view.exibirMensagem("Nome      | Quantidade | Tamanho\n");
  view.exibirMensagem("-------------------------------------\n");
  for(int i=0;i<ultimo_id;i++){
    Roupa roupa = dao.capturar(i);
    view.exibirRoupa(roupa);
    view.exibirMensagem("-------------------------------------\n");
  }
}

void RoupaController::atualizarQuantidadeRoupa(){
  RoupaDAO dao;
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
  RoupaDAO dao;
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