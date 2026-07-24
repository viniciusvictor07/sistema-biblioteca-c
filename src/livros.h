#ifndef LIVROS_H
#define LIVROS_H

#define MAX_LIVROS 100

typedef struct {
    int codigo;
    char titulo[50];
    char autor[50];
    int ano;
    int disponivel;
} Livro;

// Funções principais
void cadastrarLivro(Livro biblioteca[], int *totalLivros);
void exibirTodosLivros(Livro biblioteca[], int totalLivros);
void buscarLivroPorCodigo(Livro biblioteca[], int totalLivros);
void buscarLivroPorTitulo(Livro biblioteca[], int totalLivros);
void atualizarLivro(Livro biblioteca[], int totalLivros);
void excluirLivro(Livro biblioteca[], int *totalLivros);
void exibirLivrosDisponiveis(Livro biblioteca[], int totalLivros);

void salvarLivros(Livro biblioteca[], int totalLivros);
void carregarLivros(Livro biblioteca[], int *totalLivros);

// Funções extras
void alterarStatusEmprestimo(Livro biblioteca[], int totalLivros);
void exibirEstatisticas(Livro biblioteca[], int totalLivros);

// Funções auxiliares
int buscarIndicePorCodigo(Livro biblioteca[], int totalLivros, int codigoBuscado);
void limparBuffer();
int bibliotecaCheia(int totalLivros);
int bibliotecaVazia(int totalLivros);

#endif