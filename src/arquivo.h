#ifndef ARQUIVO_H
#define ARQUIVO_H

#define CAMINHO_DADOS "livros.txt"
#endif

#include "livros.h"

void salvarLivros(Livro biblioteca[], int totalLivros);
void carregarLivros(Livro biblioteca[], int *totalLivros);
