#ifndef ITEMDIVERSO_VIEW_H
#define ITEMDIVERSO_VIEW_H

#include "../models/ItemDiverso.h"
#include <string>

class ItemDiversoView{
  public:
    // Metodos de obter informacoes do usuario
    bool perguntarSimOuNao();
    ItemDiverso obterDadoItemDiverso();
    std::string obterNomeDoItemDiverso();
    std::string obterTipoDoItem();
    bool verificacaoDaEntrada();

    // Metodos de exibir informacoes ao usuario
    void exibirMensagem(const std::string& mensagem);
    void exibirItemDiverso(const ItemDiverso& itemDiverso);
};

#endif