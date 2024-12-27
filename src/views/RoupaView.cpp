#include "RoupaView.h"
#include "../models/Roupa.h"
#include <iostream>
#include <limits>

void RoupaView::exibirMensagem(const std::string& mensagem){
  std::cout << mensagem;
}

void RoupaView::exibirRoupa(const Roupa& roupa){
  std::string nome =  roupa.getNome();
  int quantidade = roupa.getQuantidade();
  std::string tamanho = roupa.getTamanho();

  std::cout << "Nome da roupa: " << nome << std::endl;
  std::cout << "Quantidade de pecas: " << quantidade << std::endl;
  std::cout << "Tamanho da roupa: " << tamanho << std::endl;
}

std::string RoupaView::obterNomeRoupa(){
  exibirMensagem("Digite o nome da roupa exatamente como foi criado: ");
  std::string nome;
  std::cin >> nome;
  return nome;
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

Roupa RoupaView::obterDadosRoupa(){
  std::string nome, tamanho;
  int quantidade;

  while(true){
    try {
      exibirMensagem("Digite o nome da roupa: ");
      std::cin >> nome;
      if(!verificacaoDaEntrada())
        throw std::invalid_argument("Erro: entrada invalida, insira o nome usando letras. Refaca a operacao a seguir.\n");

      exibirMensagem("Digite a quantidade de pecas dessa roupa: ");
      std::cin >> quantidade;
      if(!verificacaoDaEntrada())
        throw std::invalid_argument("Erro: entrada invalida, insira um numero na quantidade de pecas. Refaca a operacao a seguir.\n");

      exibirMensagem("Digite o tamanho da roupa: ");
      std::cin >> tamanho;
      if(!verificacaoDaEntrada())
        throw std::invalid_argument("Erro: entrada invalida, insira o tamanho utilizando poucos caracteres. Refaca a operacao a seguir.\n");

      break;
    } catch (std::invalid_argument &err) {
      exibirMensagem(err.what());
    }
  }

  Roupa roupa(nome, quantidade, tamanho);
  return roupa;
}

bool RoupaView::verificacaoDaEntrada(){
  if(std::cin.fail()){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }
}

int RoupaView::obterQuantidadeRoupa(){
  exibirMensagem("Digite a quantidade de pecas da roupa: ");
  
  while(true){
    try {
      int quantidade;
      std::cin >> quantidade;
      if(!verificacaoDaEntrada())
        throw std::invalid_argument("Erro: input invalido. Digite em numeros a quantia de pecas.");
    } catch (std::invalid_argument &err) {
      exibirMensagem(err.what());
    }
  }
}