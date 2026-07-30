#include <stdlib.h>

#ifndef LIVROS_H
#define LIVROS_H

#define MAX_LIVROS 100
#define ANO_ATUAL 2026

typedef struct {
    int codigo;
    char titulo[50];
    char autor[50];
    char categoria[30];
    int ano;
    int disponivel;
} Livro;

// --- Funções Principais ---

void cadastrarLivro(Livro biblioteca[], int *totalLivros, int *proximoCodigo);
void exibirTodosLivros(const Livro biblioteca[], int totalLivros);
void buscarLivroPorCodigo(const Livro biblioteca[], int totalLivros);
void buscarLivroPorTitulo(const Livro biblioteca[], int totalLivros);
void atualizarLivro(Livro biblioteca[], int totalLivros);
void excluirLivro(Livro biblioteca[], int *totalLivros);
void exibirLivrosDisponiveis(const Livro biblioteca[], int totalLivros);

// --- Funções Extras ---

void alterarStatusEmprestimo(Livro biblioteca[], int totalLivros);
void exibirEstatisticas(const Livro biblioteca[], int totalLivros);
void buscarLivrosPorCategoria(const Livro biblioteca[], int totalLivros);
void buscarLivrosPorAutor(const Livro biblioteca[], int totalLivros);

// --- Funções Auxiliares ---

// Validação e busca interna
int buscarIndicePorCodigo(const Livro biblioteca[], int totalLivros, int codigoBuscado);
int pedirEBuscarIndice(const Livro biblioteca[], int totalLivros);
int bibliotecaCheia(int totalLivros);
int bibliotecaVazia(int totalLivros);

// Entrada e saída de dados
int lerInteiro(const char *mensagem, int min, int max);
void lerString(char *buffer, int tamanho);
const char* escolherCategoria();
void exibirLivro(Livro livro);

// Controle do terminal e fluxo
void limparBuffer();
void mostrarMenu();
void limparTela();
void pausar();

#endif