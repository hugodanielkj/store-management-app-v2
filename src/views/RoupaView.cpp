#include "RoupaView.h"
#include "../models/Roupa.h"
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

void RoupaView::exibirMensagem(const std::string& mensagem){
  std::cout << mensagem;
}

void RoupaView::exibirRoupa(const Roupa& roupa){
  std::string nome =  roupa.getNome();
  std::string tamanho = roupa.getTamanho();
  int quantidade = roupa.getQuantidade();

  std::cout << "Nome da Roupa: " << nome << std::endl;
  std::cout << "Tamanho da roupa: " << tamanho << std::endl;
  std::cout << "Quantidade de roupas " << quantidade << std::endl;
}

std::string RoupaView::obterNomeRoupa() {
  while (true) {
    try {
      exibirMensagem("Digite o nome do item: ");
      std::string nome;
      std::cin >> nome;


      // Verificar se o nome contém apenas letras
      if (!verificacaoDaEntrada(nome, "nome")) {
        throw std::invalid_argument("Erro: O nome deve conter apenas letras. Refaca a operacao.\n");
      }

      return nome; // Retornar o nome válido
    } catch (const std::invalid_argument& err) {
      exibirMensagem(err.what());
    }
  }
}

bool RoupaView::perguntarSimOuNao(){
  char opcao_do_usuario;
  std::cin >> opcao_do_usuario;

  while(true){
    try{
      if(opcao_do_usuario == 'y' || opcao_do_usuario == 'Y' || opcao_do_usuario == 's' || opcao_do_usuario == 'S')
        return true;
      else if(opcao_do_usuario == 'n' || opcao_do_usuario == 'N')
        return false;
      else
        throw std::invalid_argument("Erro: Digite 'y' se deseja realizar a operacao e 'n' se nao deseja realizar a operacao: ");
      break;
    } catch (std::invalid_argument &err) {
      exibirMensagem(err.what());
    }
  }

  return false;   // Apenas para nao gerar warning
}

Roupa RoupaView::obterDadosRoupa() {
  std::string nome, tamanho;
  int quantidade;

  while (true) {
    try {
      // Solicitar e validar o nome do item
      exibirMensagem("Digite o nome do item: ");
      std::cin >> nome;

       // Converter todas as letras para minúsculas
      std::transform(nome.begin(), nome.end(), nome.begin(), [](unsigned char c) {
        return std::tolower(c);
      });

      if (!verificacaoDaEntrada(nome, "nome")) {
        throw std::invalid_argument("Erro: entrada inválida. O nome deve conter apenas letras. Refaca a operação.\n");
      }

      // Solicitar e validar a quantidade do item
      exibirMensagem("Digite a quantidade de itens: ");
      std::string entradaQuantidade;
      std::cin >> entradaQuantidade;
      if (!verificacaoDaEntrada(entradaQuantidade, "quantidade")) {
        throw std::invalid_argument("Erro: entrada inválida. A quantidade deve ser um número inteiro positivo. Refaca a operação.\n");
      }
      quantidade = std::stoi(entradaQuantidade); // Conversão segura da quantidade

      // Solicitar e validar o tipo/tamanho do item
      exibirMensagem("Digite o tipo do item (P, M, G, XG, XGG): ");
      std::cin >> tamanho;
      if (!verificacaoDaEntrada(tamanho, "tamanho")) {
        throw std::invalid_argument("Erro: entrada inválida. O tipo deve ser P, M, G, XG ou XGG. Refaca a operação.\n");
      }

      // Quebra do loop ao concluir com entradas válidas
      break;

    } catch (const std::invalid_argument &err) {
      exibirMensagem(err.what()); // Exibir mensagem de erro e repetir o loop
    }
  }

  // Criação e retorno do objeto ItemDiverso com os dados válidos
  Roupa roupa(nome, quantidade, tamanho);
  return roupa;
}

bool RoupaView::verificacaoDaEntrada(const std::string& entrada, const std::string& tipo){
 if (tipo == "nome") {
    // Verificar se a entrada contém apenas letras
    for (char c : entrada) {
      if (!std::isalpha(c)) { // Não é letra
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

  } else if (tipo == "tamanho") {
    // Verificar se o tamanho é válido (P, M, G, XG, XGG)
    std::vector<std::string> tamanhosValidos = {"P", "M", "G", "XG", "XGG"};
    for (const auto& tamanho : tamanhosValidos) {
      if (entrada == tamanho) {
        return true;
      }
    }
    return false; 

  } else {
    return false; //Tipo desconhecido
  }
}

int RoupaView::obterQuantidadeRoupa() {
  while (true) {
    try {
      exibirMensagem("Digite a quantidade de roupas a adicionar/remover: ");
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