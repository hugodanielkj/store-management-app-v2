#ifndef ROUPA_VIEW_H
#define ROUPA_VIEW_H

#include "Roupa.h"
#include <string>

class RoupaView{
  public:
    // Metodos de obter informacoes do usuario
    bool perguntarSimOuNao();
    Roupa obterDadosRoupa();
    std::string obterNomeRoupa();
    int obterQuantidadeRoupa();
    bool verificacaoDaEntrada();

    // Metodos de exibir informacoes ao usuario
    void exibirMensagem(const std::string& mensagem);
    void exibirRoupa(const Roupa& roupa);
};

#endif