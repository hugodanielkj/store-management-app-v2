#include "ClienteView.h"
#include "../models/Cliente.h"
#include <iostream>
#include <limits>

void ClienteView::exibirMensagem(const std::string& mensagem) {
  std::cout << mensagem;
}

void ClienteView::exibirCliente(const Cliente& cliente) {
  std::string nome = cliente.getNome();
  std::string telefone = cliente.getTelefone();
  std::string email = cliente.getEmail();

  std::cout << "Nome do cliente: " << nome << std::endl;
  std::cout << "Telefone: " << telefone << std::endl;
  std::cout << "Email: " << email << std::endl;
}

std::string ClienteView::obterNomeCliente() {
  exibirMensagem("Digite o nome do cliente exatamente como foi cadastrado: ");
  std::string nome;
  std::cin >> nome;
  return nome;
}

bool ClienteView::perguntarSimOuNao() {
  char opcao_do_usuario;
  std::cin >> opcao_do_usuario;

  while(true) {
    try {
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

  return false;
}

Cliente ClienteView::obterDadosCliente() {
  std::string nome, telefone, email;

  while(true) {
    try {
      exibirMensagem("Digite o nome do cliente: ");
      std::cin >> nome;
      if(!verificacaoDaEntrada())
        throw std::invalid_argument("Erro: entrada invalida, insira o nome usando letras. Refaca a operacao a seguir.\n");

      exibirMensagem("Digite o telefone do cliente: ");
      std::cin >> telefone;
      if(!verificacaoDaEntrada())
        throw std::invalid_argument("Erro: entrada invalida, insira um telefone valido. Refaca a operacao a seguir.\n");

      exibirMensagem("Digite o email do cliente: ");
      std::cin >> email;
      if(!verificacaoDaEntrada())
        throw std::invalid_argument("Erro: entrada invalida, insira um email valido. Refaca a operacao a seguir.\n");

      break;
    } catch (std::invalid_argument &err) {
      exibirMensagem(err.what());
    }
  }

  Cliente cliente(nome, telefone, email);
  return cliente;
}

bool ClienteView::verificacaoDaEntrada() {
  if(std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }
  return true;
}

std::string ClienteView::obterTelefoneCliente() {
  exibirMensagem("Digite o telefone do cliente: ");
  std::string telefone;
  std::cin >> telefone;
  return telefone;
}
