#ifndef CLIENTE_VIEW_H
#define CLIENTE_VIEW_H

#include "../models/Cliente.h"
#include <string>

class ClienteView {
  public:
    // Metodos de obter informacoes do usuario
    bool perguntarSimOuNao();
    Cliente obterDadosCliente();
    std::string obterNomeCliente();
    std::string obterTelefoneCliente();
    bool verificacaoDaEntrada();

    // Metodos de exibir informacoes ao usuario
    void exibirMensagem(const std::string& mensagem);
    void exibirCliente(const Cliente& cliente);
};

#endif
