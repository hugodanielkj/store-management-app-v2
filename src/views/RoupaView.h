#ifndef ROUPA_VIEW_H
#define ROUPA_VIEW_H

#include "../models/Roupa.h"
#include <string>

class RoupaView{
  public:
    // Metodos de obter informacoes do usuario
    bool perguntarSimOuNao();
    Roupa obterDadosRoupa();
    std::string obterNomeRoupa();
    int obterQuantidadeRoupa();
    bool verificacaoDaEntrada(const std::string& entrada, const std::string& marca);

    // Metodos de exibir informacoes ao usuario
    void exibirMensagem(const std::string& mensagem);
    void exibirRoupa(const Roupa& roupa);
};

#endif