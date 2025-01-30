#include "ItemDiversoView.h"
#include "../models/ItemDiverso.h"
#include <iostream>
#include <limits>
#include <vector>

void ItemDiversoView::exibirMensagem(const std::string& mensagem){
  std::cout << mensagem;
}

void ItemDiversoView::exibirItemDiverso(const ItemDiverso& itemDiverso){
  std::string nome =  itemDiverso.getNome();
  std::string marca = itemDiverso.getMarca();
  int quantidade = itemDiverso.getQuantidade();

  std::cout << "Nome do item: " << nome << std::endl;
  std::cout << "Marca do Item: " << marca << std::endl;
  std::cout << "Quantidade de Itens " << quantidade << std::endl;
}

std::string ItemDiversoView::obterNomeDoItemDiverso() {
  while (true) {
    try {
      exibirMensagem("Digite o nome do item: ");
      std::string nome;
      std::cin >> nome;

      if (!verificacaoDaEntrada(nome, "nome")) {
        throw std::invalid_argument("Erro: O nome deve conter apenas letras. Refaca a operacao.\n");
      }

      return nome; // Nome válido
    } catch (const std::invalid_argument& err) {
      exibirMensagem(err.what());
    }
  }
}

bool ItemDiversoView::perguntarSimOuNao() {
    std::string opcao_do_usuario;

    while (true) {
        try {
            // Removeu o "ignore()" desnecessário
            std::getline(std::cin, opcao_do_usuario);

            if (opcao_do_usuario.empty() || opcao_do_usuario.size() != 1) {
                throw std::invalid_argument("Erro 1: Digite apenas 'y' para SIM ou 'n' para NÃO: ");
            }

            char resposta = std::tolower(opcao_do_usuario[0]); // Simplifica a validação
            if (resposta == 'y') {
                return true;
            } else if (resposta == 'n') {
                return false;
            } else {
                throw std::invalid_argument("Erro 2: Caractere inválido. Use 'y' ou 'n': ");
            }
        } catch (const std::invalid_argument &err) {
            exibirMensagem(err.what());
        }
    }
}

ItemDiverso ItemDiversoView::obterDadoItemDiverso() {
  std::string nome, marca;
  int quantidade;

  while (true) {
    try {
      // Limpar o buffer do cin antes de usar getline
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      // Solicitar e validar o nome do item
      exibirMensagem("Digite o nome do item: ");
      getline(std::cin, nome);
      if (!verificacaoDaEntrada(nome, "nome")) {
        throw std::invalid_argument("Erro: entrada inválida. O nome deve conter apenas letras e sem espaço. Refaca a operação.\n");
      }

      // Solicitar e validar a quantidade do item
      exibirMensagem("Digite a quantidade de itens: ");
      std::string entradaQuantidade;
      std::cin >> entradaQuantidade;
      if (!verificacaoDaEntrada(entradaQuantidade, "quantidade")) {
        throw std::invalid_argument("Erro: entrada inválida. A quantidade deve ser um número inteiro positivo. Refaca a operação.\n");
      }
      quantidade = std::stoi(entradaQuantidade); // Conversão segura da quantidade


      // Solicitar e validar a marca do item
      exibirMensagem("Digite a marca do item: ");
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      getline(std::cin, marca);
      if (!verificacaoDaEntrada(marca, "marca")) {
        throw std::invalid_argument("Erro: entrada inválida. A marca deve conter apenas letras e sem espaço. Refaca a operação.\n");
      }

      // Quebra do loop ao concluir com entradas válidas
      break;

    } catch (const std::invalid_argument &err) {
      exibirMensagem(err.what()); // Exibir mensagem de erro e repetir o loop
    }
  }

  // Criação e retorno do objeto ItemDiverso com os dados válidos
  ItemDiverso itemDiverso(nome, quantidade, marca);
  return itemDiverso;
}

bool ItemDiversoView::verificacaoDaEntrada(const std::string& entrada, const std::string& tipo) {
  if (tipo == "nome" || tipo == "marca") {
    // Verificar se a entrada contém apenas letras
    for (char c : entrada) {
      if (!std::isalpha(c) && c != '_' && c != '-') { // Não é letra
        return false;
      }
    }
    return true;

  } else if (tipo == "quantidade") {
    // Verificar se a entrada é um número inteiro positivo
    try {
      int quantidade = std::stoi(entrada);
      if (quantidade < 0) {
        return false;
      }
      return true;
    } catch (...) {
      return false; // Caso não seja número
    }

  } else {
    return false; // Tipo desconhecido
  }
}

std::string ItemDiversoView::obterMarcaDoItem() {
  while (true) {
    try {
      exibirMensagem("Digite a marca do item: ");
      std::string marca;
      std::cin >> marca;

      // Validar a entrada: apenas letras são permitidas
      if (!verificacaoDaEntrada(marca, "marca")) {
        throw std::invalid_argument("Erro: entrada inválida. A marca deve conter apenas letras. Tente novamente.\n");
      }

      return marca; // Retorna a marca válida

    } catch (const std::invalid_argument &err) {
      exibirMensagem(err.what()); // Exibe mensagem de erro e repete o loop
    }
  }
}

int ItemDiversoView::obterQuantidadeItemDiverso() {
  while (true) {
    try {
      exibirMensagem("Digite a quantidade de itens a adicionar/remover: ");
      std::string entrada;
      std::cin >> entrada;

      if (!verificacaoDaEntrada(entrada, "quantidade")) {
        throw std::invalid_argument("Erro: Entrada inválida. A quantidade deve ser um número inteiro positivo.\n");
      }

      return std::stoi(entrada); // Retorna a quantidade válida
    } catch (const std::invalid_argument& err) {
      exibirMensagem(err.what());
    }
  }
}