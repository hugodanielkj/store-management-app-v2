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
      std::cin.ignore();
      getline(std::cin, nome);

      // Verificar se o nome contém apenas letras
      if (!verificacaoDaEntrada(nome, "nome")) {
        throw std::invalid_argument("Erro: O nome deve conter apenas letras e sem espaço.\n");
      }

      return nome; // Retornar o nome válido
    } catch (const std::invalid_argument& err) {
      exibirMensagem(err.what());
      //exibirMensagem("Quer fazer a operacao novamente?(y/n) ");
      throw std::runtime_error("Quer fazer a operacao novamente?(y/n) ");
    }
  }
}
bool RoupaView::perguntarSimOuNao() {
    std::string opcao_do_usuario;

    while (true) {
        try {
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

Roupa RoupaView::obterDadosRoupa() {
  std::string nome, tamanho;
  int quantidade;

  while (true) {
    try {
      // Limpar o buffer do cin antes de usar getline
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      // Solicitar e validar o nome do item
      exibirMensagem("Digite o nome do item: ");
      getline(std::cin, nome);

       // Converter todas as letras para minúsculas
      std::transform(nome.begin(), nome.end(), nome.begin(), [](unsigned char c) {
        return std::tolower(c);
      });

      if (!verificacaoDaEntrada(nome, "nome")) {
        throw std::invalid_argument("Erro: entrada inválida. O nome deve conter apenas letras e sem espaço.\n");
      }

      // Solicitar e validar a quantidade do item
      exibirMensagem("Digite a quantidade de itens: ");
      std::string entradaQuantidade;
      std::cin >> entradaQuantidade;
      if (!verificacaoDaEntrada(entradaQuantidade, "quantidade")) {
        throw std::invalid_argument("Erro: entrada inválida. A quantidade deve ser um número inteiro positivo.\n");
      }
      quantidade = std::stoi(entradaQuantidade); // Conversão segura da quantidade

      // Solicitar e validar o tipo/tamanho do item
      exibirMensagem("Digite o tamanho do item (NB, RN, PP, P, M, G, XG, XGG): ");
      std::cin >> tamanho;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (!verificacaoDaEntrada(tamanho, "tamanho")) {
        throw std::runtime_error("Erro: entrada inválida. O tamanho deve ser P, M, G, XG ou XGG.\n");
      }

      // Quebra do loop ao concluir com entradas válidas
      break;

    } catch (const std::invalid_argument &err) {
      exibirMensagem(err.what()); // Exibir mensagem de erro e repetir o loop
      throw std::invalid_argument("Deseja fazer a operação novamente?(y/n) ");
    } catch (const std::runtime_error &err) {
      exibirMensagem(err.what()); // Exibir mensagem de erro e repetir o loop
      throw std::invalid_argument("Deseja fazer a operação novamente?(y/n) ");
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

  } else if (tipo == "tamanho") {
    // Verificar se o tamanho é válido (P, M, G, XG, XGG)
    std::vector<std::string> tamanhosValidos = {"P", "M", "G", "XG", "XGG","p", "m", "g", "xg", "xgg","PP", "pp", "NB", "nb", "RN", "rn"};
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