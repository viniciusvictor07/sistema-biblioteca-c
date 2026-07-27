#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "livros.h"

#define CAMINHO_DADOS "livros.txt"

void salvarLivros(const Livro biblioteca[], int totalLivros);
void carregarLivros(Livro biblioteca[], int *totalLivros, int *proximoCodigo);

#endif