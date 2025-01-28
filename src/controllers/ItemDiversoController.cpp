#include "ItemDiversoController.h"
#include "../views/ItemDiversoView.h"
#include "../dao/ItemDiversoDAO.h"
#include <stdexcept>
#include <iostream>
#include <vector>

// Construtor que recebe conexão com banco de dados
ItemDiversoController::ItemDiversoController(sqlite3* _db): db(_db) {}

void ItemDiversoController::adicionarItemDiverso(){
  ItemDiversoDAO dao(db);
  ItemDiversoView view;
  ItemDiverso itemDiverso;

  // Loop de validação dos dados do item
  while(true){
    try {
      itemDiverso = view.obterDadoItemDiverso();
      view.exibirItemDiverso(itemDiverso);
      view.exibirMensagem("As informacoes dos itens acima estao corretas?(y/n)");
      if(!view.perguntarSimOuNao())
        throw std::invalid_argument("Repita a operacao.\n");
      break;
    } catch (std::invalid_argument &err) {
      view.exibirMensagem(err.what());
    }
  }

  // Tenta salvar no banco
  if(dao.salvar(itemDiverso)){
    view.exibirMensagem("Sucesso ao adicionar ItemDiverso.\n");
  }
}

void ItemDiversoController::lerItemDiverso(){
  ItemDiversoDAO dao(db);
  ItemDiversoView view;
  std::string nome = view.obterNomeDoItemDiverso();

  // Loop de busca do item
  bool loop = true;
  while(loop){
    try {
      ItemDiverso itemDiverso = dao.capturarNome(nome);
      view.exibirItemDiverso(itemDiverso);
      break;
    } catch (std::invalid_argument &err) {
      view.exibirMensagem("Erro: Nome invalido para a Roupa. Quer fazer a operacao novamente?\n");
      loop = view.perguntarSimOuNao();
    }
  }
}

void ItemDiversoController::lerTodosItemDiversos() {
    ItemDiversoDAO dao(db);
    ItemDiversoView view;

    // Busca todos os IDs válidos no banco
    std::vector<int> idsValidos = dao.obterIdsValidos();

    if (idsValidos.empty()) {
        view.exibirMensagem("Não há itens no estoque.\n");
        return;
    }

    // Exibe cabeçalho da tabela
    view.exibirMensagem("-------------------------------------\n");
    view.exibirMensagem("Tabela de todas as ItemDiversos do estoque:\n");
    view.exibirMensagem("-------------------------------------\n");
    view.exibirMensagem("Nome      | Quantidade | Tipo\n");
    view.exibirMensagem("-------------------------------------\n");

    // Lista todos os itens
    for (int id : idsValidos) {
        ItemDiverso itemDiverso = dao.capturarId(id);
        view.exibirItemDiverso(itemDiverso);
        view.exibirMensagem("-------------------------------------\n");
    }
}

void ItemDiversoController::atualizarQuantidadeItemDiverso() {
    ItemDiversoDAO dao(db);
    ItemDiversoView view;
    std::string nome = view.obterNomeDoItemDiverso();

    // Loop de atualização de quantidade
    bool loop = true;
    while (loop) {
        try {
            if (!dao.existeEsseItemDiverso(nome)) {
                throw std::invalid_argument("Erro: O item informado não existe no banco de dados. Deseja tentar novamente? (y/n)");
            }

            ItemDiverso itemDiverso = dao.capturarNome(nome);
            view.exibirMensagem("Quantidade atual do item '" + nome + "': " + std::to_string(itemDiverso.getQuantidade()) + "\n");

            // Processa operação de adição/subtração
            view.exibirMensagem("Deseja adicionar ou subtrair itens? (a para adicionar / s para subtrair)");
            char operacao;
            std::cin >> operacao;

            if (operacao != 'a' && operacao != 's') {
                throw std::invalid_argument("Erro: Operação inválida. Digite 'a' para adicionar ou 's' para subtrair.");
            }

            int quantidadeAlterar = view.obterQuantidadeItemDiverso();
            int novaQuantidade = itemDiverso.getQuantidade();
            
            // Calcula nova quantidade
            if (operacao == 'a') {
                novaQuantidade += quantidadeAlterar;
            } else if (operacao == 's') {
                if (quantidadeAlterar > novaQuantidade) {
                    throw std::invalid_argument("Erro: A subtração resultaria em uma quantidade negativa. Operação cancelada.");
                }
                novaQuantidade -= quantidadeAlterar;
            }

            itemDiverso.setQuantidade(novaQuantidade);
            dao.atualizar(itemDiverso);

            view.exibirMensagem("Sucesso ao atualizar a quantidade do item '" + nome + "'. Nova quantidade: " + std::to_string(novaQuantidade) + "\n");
            break;
        } catch (const std::invalid_argument &err) {
            view.exibirMensagem(err.what());
            loop = view.perguntarSimOuNao();
        } catch (const std::runtime_error &err) {
            view.exibirMensagem(err.what());
            loop = view.perguntarSimOuNao();
        }
    }
}

void ItemDiversoController::removerItemDiverso() {
    ItemDiversoDAO dao(db);
    ItemDiversoView view;
    std::string nome = view.obterNomeDoItemDiverso();

    // Loop de remoção com confirmação
    bool loop = true;
    while (loop) {
        try {
            if (!dao.existeEsseItemDiverso(nome)) {
                throw std::invalid_argument("Erro: O item informado não existe no banco de dados. Deseja tentar novamente? (y/n)");
            }

            view.exibirMensagem("Tem certeza de que deseja remover o item '" + nome + "' do banco de dados? (y/n)");
            if(view.perguntarSimOuNao()) {
                dao.deletar(nome);
                view.exibirMensagem("Item '" + nome + "' removido com sucesso.");
            } else {
                view.exibirMensagem("Remoção cancelada pelo usuário.");
            }
            break;
        } catch (const std::invalid_argument &err) {
            view.exibirMensagem(err.what());
            loop = view.perguntarSimOuNao();
        }
    }
}
