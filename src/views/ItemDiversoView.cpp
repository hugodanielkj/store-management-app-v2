#include "ItemDiversoView.h"
#include "../models/ItemDiverso.h"
#include <iostream>
#include <limits>

void ItemDiversoView::exibirMensagem(const std::string& mensagem){
  std::cout << mensagem;
}

void ItemDiversoView::exibirItemDiverso(const ItemDiverso& itemDiverso){
  std::string nome =  itemDiverso.getNome();
  std::string tipo = itemDiverso.getTipo();
  int quantidade = itemDiverso.getQuantidade();

  std::cout << "Nome do item: " << nome << std::endl;
  std::cout << "Tipo do Item: " << tipo << std::endl;
  std::cout << "Quantidade de Itens " << quantidade << std::endl;
}

std::string ItemDiversoView::obterNomeDoItemDiverso(){
  exibirMensagem("Digite o nome do item exatamente como foi criado: ");
  std::string nome;
  std::cin >> nome;
  return nome;
}

bool ItemDiversoView::perguntarSimOuNao(){
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

ItemDiverso ItemDiversoView::obterDadoItemDiverso(){
  std::string nome, tamanho,tipo;
  int quantidade;

  while(true){
    try {
      exibirMensagem("Digite o nome do item: ");
      std::cin >> nome;
      if(!verificacaoDaEntrada())
        throw std::invalid_argument("Erro: entrada invalida, insira o nome usando letras. Refaca a operacao a seguir.\n");

      exibirMensagem("Digite a quantidade de itens: ");
      std::cin >> quantidade;
      if(!verificacaoDaEntrada())
        throw std::invalid_argument("Erro: entrada invalida, insira um numero na quantidade de pecas. Refaca a operacao a seguir.\n");

      exibirMensagem("Digite o tipo do item: ");
      std::cin >> tipo;
      if(!verificacaoDaEntrada())
        throw std::invalid_argument("Erro: entrada invalida, insira o tipo utilizando poucos caracteres. Refaca a operacao a seguir.\n");

      break;
    } catch (std::invalid_argument &err) {
      exibirMensagem(err.what());
    }
  }

  ItemDiverso itemDiverso(nome, quantidade, tipo);
  return itemDiverso;
}

bool ItemDiversoView::verificacaoDaEntrada(){
  if(std::cin.fail()){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }
  return true;
}

std::string ItemDiversoView::obterTipoDoItem(){
  exibirMensagem("Digite o tipo do item: ");
  
  while(true){
    try {
      std::string tipo;
      std::cin >> tipo;
      if(!verificacaoDaEntrada())
        throw std::invalid_argument("Erro: input invalido. Digite um tipo valido");
    } catch (std::invalid_argument &err) {
      exibirMensagem(err.what());
    }
  }
}