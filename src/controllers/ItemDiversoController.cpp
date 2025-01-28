#include "ItemDiversoController.h"
#include "../views/ItemDiversoView.h"
#include "../dao/ItemDiversoDAO.h"
#include <stdexcept>
#include <iostream>
#include <vector>

ItemDiversoController::ItemDiversoController(sqlite3* _db): db(_db) {}

void ItemDiversoController::adicionarItemDiverso(){
  ItemDiversoDAO dao(db);
  ItemDiversoView view;
  ItemDiverso itemDiverso;

  while(true){    // Verifica se as informacoes da roupa estao corretas
    try {
      itemDiverso = view.obterDadoItemDiverso();   // Pede ao usuario informacoes da roupa
      view.exibirItemDiverso(itemDiverso);
      view.exibirMensagem("As informacoes dos itens acima estao corretas?(y/n)");
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


void ItemDiversoController::lerItemDiverso(){
  ItemDiversoDAO dao(db);
  ItemDiversoView view;
  std::string nome = view.obterNomeDoItemDiverso();   // Obtem nome da roupa que se quer ler

  bool loop = true;
  while(loop){
    try {
      ItemDiverso itemDiverso = dao.capturarNome(nome);   // Constroi a roupa em questao
      // Verificar se roupa foi criada e lancar throw expcetion
      view.exibirItemDiverso(itemDiverso);    // Exibe roupa para o usuario
      break;
    } catch (std::invalid_argument &err) {
      view.exibirMensagem("Erro: Nome invalido para a Roupa. Quer fazer a operacao novamente?\n");
      loop = view.perguntarSimOuNao();    // Usuario diz se quer refazer operacao ou nao
    }
  }
}


void ItemDiversoController::lerTodosItemDiversos() {
    ItemDiversoDAO dao(db);
    ItemDiversoView view;

    // Obtém todos os IDs válidos (não se limita ao último ID)
    std::vector<int> idsValidos = dao.obterIdsValidos();  // Modifique para obter todos os IDs existentes

    if (idsValidos.empty()) {
        view.exibirMensagem("Não há itens no estoque.\n");
        return;
    }

    view.exibirMensagem("-------------------------------------\n");
    view.exibirMensagem("Tabela de todas as ItemDiversos do estoque:\n");
    view.exibirMensagem("-------------------------------------\n");
    view.exibirMensagem("Nome      | Quantidade | Tipo\n");
    view.exibirMensagem("-------------------------------------\n");

    // Itera sobre os IDs válidos
    for (int id : idsValidos) {
        ItemDiverso itemDiverso = dao.capturarId(id);  // Captura o item baseado no ID
        view.exibirItemDiverso(itemDiverso);
        view.exibirMensagem("-------------------------------------\n");
    }
}


void ItemDiversoController::atualizarQuantidadeItemDiverso() {
    ItemDiversoDAO dao(db);
    ItemDiversoView view;
    std::string nome = view.obterNomeDoItemDiverso();

    bool loop = true;
    while (loop) {
        try {
            // Verifica se o item existe no banco de dados
            if (!dao.existeEsseItemDiverso(nome)) {
                throw std::invalid_argument("Erro: O item informado não existe no banco de dados. Deseja tentar novamente? (y/n)");
            }

            // Captura o item com base no nome
            ItemDiverso itemDiverso = dao.capturarNome(nome);

            // Exibe a quantidade atual do item
            view.exibirMensagem("Quantidade atual do item '" + nome + "': " + std::to_string(itemDiverso.getQuantidade()) + "\n");

            // Pergunta ao usuário o valor que deseja adicionar ou subtrair à quantidade
            view.exibirMensagem("Deseja adicionar ou subtrair itens? (a para adicionar / s para subtrair)");
            char operacao;
            std::cin >> operacao;

            // Valida a operação escolhida
            if (operacao != 'a' && operacao != 's') {
                throw std::invalid_argument("Erro: Operação inválida. Digite 'a' para adicionar ou 's' para subtrair.");
            }

            // Pergunta ao usuário o valor a ser adicionado ou subtraído
            int quantidadeAlterar = view.obterQuantidadeItemDiverso();

            // Atualiza a quantidade com base na operação escolhida
            int novaQuantidade = itemDiverso.getQuantidade();
            if (operacao == 'a') {
                novaQuantidade += quantidadeAlterar; // Adiciona a quantidade
            } else if (operacao == 's') {
                if (quantidadeAlterar > novaQuantidade) {
                    throw std::invalid_argument("Erro: A subtração resultaria em uma quantidade negativa. Operação cancelada.");
                }
                novaQuantidade -= quantidadeAlterar; // Subtrai a quantidade
            }

            // Define a nova quantidade e atualiza o banco de dados
            itemDiverso.setQuantidade(novaQuantidade);
            dao.atualizar(itemDiverso);

            // Exibe mensagem de sucesso
            view.exibirMensagem("Sucesso ao atualizar a quantidade do item '" + nome + "'. Nova quantidade: " + std::to_string(novaQuantidade) + "\n");
            break; // Sai do loop após atualizar com sucesso
        } catch (const std::invalid_argument &err) {
            view.exibirMensagem(err.what());
            loop = view.perguntarSimOuNao(); // Pergunta se o usuário deseja tentar novamente
        } catch (const std::runtime_error &err) {
            // Erro quando não encontrar o item
            view.exibirMensagem(err.what());
            loop = view.perguntarSimOuNao(); // Pergunta se o usuário deseja tentar novamente
        }
    }
}

void ItemDiversoController::removerItemDiverso() {
    ItemDiversoDAO dao(db);
    ItemDiversoView view;
    std::string nome = view.obterNomeDoItemDiverso();

    bool loop = true;
    while (loop) {
        try {
            // Verifica se o item existe no banco de dados
            if (!dao.existeEsseItemDiverso(nome)) {
                throw std::invalid_argument("Erro: O item informado não existe no banco de dados. Deseja tentar novamente? (y/n)");
            }

            // Confirma a remoção com o usuário
            view.exibirMensagem("Tem certeza de que deseja remover o item '" + nome + "' do banco de dados? (y/n)");
            bool confirmacao = view.perguntarSimOuNao();

            if (confirmacao) {
                dao.deletar(nome); // Remove o item do banco de dados
                view.exibirMensagem("Item '" + nome + "' removido com sucesso.");
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