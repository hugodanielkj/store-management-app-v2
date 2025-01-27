#ifndef VENDA_VIEW_H
#define VENDA_VIEW_H

#include "../models/Venda.h"

class VendaView{
  public:
    // Metodos de obter informacoes do usuario
    bool perguntarSimOuNao();
    Venda obterDadosVenda();
    bool verificacaoDaEntrada();

    // Metodos de exibir informacoes ao usuario
    void exibirMensagem(const std::string& mensagem);
    void exibirVenda(const Venda& roupa);
};

#endif