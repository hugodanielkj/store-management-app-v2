#include "RoupaController.h"
#include "../views/RoupaView.h"
#include "../dao/RoupaDAO.h"
#include <stdexcept>
#include <iostream>
#include <vector>

RoupaController::RoupaController(sqlite3* _db): db(_db) {}

void RoupaController::adicionarRoupa(){
  RoupaDAO dao(db);
  RoupaView view;
  Roupa roupa;

  while(true){    // Verifica se as informacoes da roupa estao corretas
    try {
      roupa = view.obterDadosRoupa();   // Pede ao usuario informacoes da roupa
      view.exibirRoupa(roupa);
      view.exibirMensagem("As informacoes dos roupas acima estao corretas?(y/n)");
      if(!view.perguntarSimOuNao())
        throw std::invalid_argument("Repita a operacao.\n");
      break;
    } catch (std::invalid_argument &err) {
      view.exibirMensagem(err.what());
    }
  }

  if(dao.salvar(roupa)){   // Salva roupa e retorna seu id
    view.exibirMensagem("Sucesso ao adicionar Roupa.");
  } else {
    // Erro ao adicionar roupa
  }
}

void RoupaController::lerRoupa(){
  RoupaDAO dao(db);
  RoupaView view;
  std::string nome = view.obterNomeRoupa();   // Obtem nome da roupa que se quer ler

  bool loop = true;
  while(loop){
    try {
      Roupa roupa = dao.capturarNome(nome);   // Constroi a roupa em questao
      // Verificar se roupa foi criada e lancar throw expcetion
      view.exibirRoupa(roupa);    // Exibe roupa para o usuario
      break;
    } catch (std::invalid_argument &err) {
      view.exibirMensagem("Erro: Nome invalido para a Roupa. Quer fazer a operacao novamente?\n");
      loop = view.perguntarSimOuNao();    // Usuario diz se quer refazer operacao ou nao
    }
  }
}


void RoupaController::lerTodasRoupas() {
    RoupaDAO dao(db);
    RoupaView view;

    // Obtém todos os IDs válidos (não se limita ao último ID)
    std::vector<int> idsValidos = dao.obterIdsValidos();  // Modifique para obter todos os IDs existentes

    if (idsValidos.empty()) {
        view.exibirMensagem("Não há roupas no estoque.\n");
        return;
    }

    view.exibirMensagem("-------------------------------------\n");
    view.exibirMensagem("Tabela de todas as Roupas do estoque:\n");
    view.exibirMensagem("-------------------------------------\n");
    view.exibirMensagem("Nome      | Quantidade | Tamanho\n");
    view.exibirMensagem("-------------------------------------\n");

    // Itera sobre os IDs válidos
    for (int id : idsValidos) {
        Roupa roupa = dao.capturarId(id);  // Captura a roupa baseado no ID
        view.exibirRoupa(roupa);
        view.exibirMensagem("-------------------------------------\n");
    }
}


void RoupaController::atualizarQuantidadeRoupa() {
    RoupaDAO dao(db);
    RoupaView view;
    std::string nome = view.obterNomeRoupa();

    bool loop = true;
    while (loop) {
        try {
            // Verifica se a Roupa existe no banco de dados
            if (!dao.existeEssaRoupa(nome)) {
                throw std::invalid_argument("Erro: A roupa informado não existe no banco de dados. Deseja tentar novamente? (y/n)");
            }

            // Captura a Roupa com base no nome
            Roupa roupa = dao.capturarNome(nome);

            // Exibe a quantidade atual da Roupa
            view.exibirMensagem("Quantidade atual da roupa '" + nome + "': " + std::to_string(roupa.getQuantidade()) + "\n");

            // Pergunta ao usuário o valor que deseja adicionar ou subtrair à quantidade
            view.exibirMensagem("Deseja adicionar ou subtrair roupas? (a para adicionar / s para subtrair)");
            char operacao;
            std::cin >> operacao;

            // Valida a operação escolhida
            if (operacao != 'a' && operacao != 's') {
                throw std::invalid_argument("Erro: Operação inválida. Digite 'a' para adicionar ou 's' para subtrair.");
            }

            // Pergunta ao usuário o valor a ser adicionado ou subtraído
            int quantidadeAlterar = view.obterQuantidadeRoupa();

            // Atualiza a quantidade com base na operação escolhida
            int novaQuantidade = roupa.getQuantidade();
            if (operacao == 'a') {
                novaQuantidade += quantidadeAlterar; // Adiciona a quantidade
            } else if (operacao == 's') {
                if (quantidadeAlterar > novaQuantidade) {
                    throw std::invalid_argument("Erro: A subtração resultaria em uma quantidade negativa. Operação cancelada.");
                }
                novaQuantidade -= quantidadeAlterar; // Subtrai a quantidade
            }

            // Define a nova quantidade e atualiza o banco de dados
            roupa.setQuantidade(novaQuantidade);
            dao.atualizar(roupa);

            // Exibe mensagem de sucesso
            view.exibirMensagem("Sucesso ao atualizar a quantidade de roupa '" + nome + "'. Nova quantidade: " + std::to_string(novaQuantidade) + "\n");
            break; // Sai do loop após atualizar com sucesso
        } catch (const std::invalid_argument &err) {
            view.exibirMensagem(err.what());
            loop = view.perguntarSimOuNao(); // Pergunta se o usuário deseja tentar novamente
        } catch (const std::runtime_error &err) {
            // Erro quando não encontrar o roupa
            view.exibirMensagem(err.what());
            loop = view.perguntarSimOuNao(); // Pergunta se o usuário deseja tentar novamente
        }
    }
}

void RoupaController::removerRoupa() {
    RoupaDAO dao(db);
    RoupaView view;
    std::string nome = view.obterNomeRoupa();

    bool loop = true;
    while (loop) {
        try {
            // Verifica se a roupa existe no banco de dados
            if (!dao.existeEssaRoupa(nome)) {
                throw std::invalid_argument("Erro: A roupa informada não existe no banco de dados. Deseja tentar novamente? (y/n)");
            }

            // Confirma a remoção com o usuário
            view.exibirMensagem("Tem certeza de que deseja remover a roupa '" + nome + "' do banco de dados? (y/n)");
            bool confirmacao = view.perguntarSimOuNao();

            if (confirmacao) {
                dao.deletar(nome); // Remove a roupa do banco de dados
                view.exibirMensagem("Roupa '" + nome + "' removido com sucesso.");
            } else {
                view.exibirMensagem("Remoção cancelada pelo usuário.");
            }
            break; // Sai do loop após a remoção ou cancelamento
        } catch (const std::invalid_argument &err) {
            view.exibirMensagem(err.what());
            loop = view.perguntarSimOuNao(); // Pergunta se o usuário deseja tentar novamente
        }
    }
}