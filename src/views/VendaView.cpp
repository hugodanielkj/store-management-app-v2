#include "VendaView.h"
#include "../models/Venda.h"
#include <iostream>
#include <limits>

void VendaView::exibirMensagem(const std::string& mensagem){
  std::cout << mensagem;
}

/*
void VendaView::exibirVenda(const Venda& venda){
  std::string produto =  venda.getProduto();
  int quantidade = venda.getQuantidade();
  std::string data = venda.getData();

  std::cout << "Nome da roupa: " << produto << std::endl;
  std::cout << "Quantidade de pecas: " << quantidade << std::endl;
  std::cout << "Tamanho da roupa: " << data << std::endl;
}
*/

bool VendaView::perguntarSimOuNao(){
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

Venda VendaView::obterDadosVenda(){
  std::string cliente, data;
  std::vector<std::string> produtos;
  std::vector<int> quantidades_de_produtos;

  while(true){
    try {
      exibirMensagem("Digite o nome do cliente: ");
      std::cin >> cliente;
      if(!verificacaoDaEntrada())
        throw std::invalid_argument("Erro: entrada invalida, insira o nome usando letras. Refaca a operacao a seguir.\n");

      exibirMensagem("Digite a data que a venda esta acontecendo\n");
      exibirMensagem("Formato exemplo(27/12/24): ");
      std::cin >> data;
      if(!verificacaoDaEntrada())
        throw std::invalid_argument("Erro: entrada invalida, insira o tamanho utilizando poucos caracteres. Refaca a operacao a seguir.\n");

      char opcao;
      while(opcao == 'y' || opcao == 'Y' || opcao == 's' || opcao == 'S'){
        exibirMensagem("Digite o nome do produto que o cliente comprou: ");
        std::string nome_do_produto;
        std::cin >> nome_do_produto;
        if(!verificacaoDaEntrada())
          throw std::invalid_argument("Erro: entrada invalida, insira o nome usando letras. Refaca a operacao a seguir.\n");
        
        produtos.push_back(nome_do_produto);

        exibirMensagem("Digite a quantidade que o cliente comprou desses produtos: ");
        int quantidade_do_produto;
        std::cin >> quantidade_do_produto;
        if(!verificacaoDaEntrada())
          throw std::invalid_argument("Erro: entrada invalida, insira um numero na quantidade de pecas. Refaca a operacao a seguir.\n");

        quantidades_de_produtos.push_back(quantidade_do_produto);

        exibirMensagem("Quer adicionar mais algum produto para o carrinho do cliente?(y/n) ");
        std::cin >> opcao;
      }
      break;
    } catch (std::invalid_argument &err) {
      exibirMensagem(err.what());
    }
  }

  Venda venda(cliente, produtos, quantidades_de_produtos, data);
  return venda;
}

bool VendaView::verificacaoDaEntrada(){
  if(std::cin.fail()){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }
  return true;
}