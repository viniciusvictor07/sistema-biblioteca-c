#include "livros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cadastrarLivro(Livro biblioteca[], int *totalLivros, int *proximoCodigo) {
    if (bibliotecaCheia(*totalLivros)) return;

    Livro novoLivro;
    novoLivro.codigo = *proximoCodigo;
    (*proximoCodigo)++;

    printf("\n--- CADASTRO DE NOVO LIVRO ---\n");
    printf("Codigo: %d\n", novoLivro.codigo);

    printf("Digite o titulo: ");
    fgets(novoLivro.titulo, sizeof(novoLivro.titulo), stdin);
    novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = '\0';

    printf("Digite o autor: ");
    fgets(novoLivro.autor, sizeof(novoLivro.autor), stdin);
    novoLivro.autor[strcspn(novoLivro.autor, "\n")] = '\0';

    printf("Digite o ano de publicacao: ");
    scanf("%d", &novoLivro.ano);

    printf("O livro esta disponivel? (1- Sim / 0- Nao): ");
    scanf("%d", &novoLivro.disponivel);
    limparBuffer();

    biblioteca[*totalLivros] = novoLivro;
    (*totalLivros)++;

    printf("\nLivro cadastrado com sucesso!\n");
}

void exibirTodosLivros(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    printf("\n=== LISTA DE LIVROS CADASTRADOS ===\n");
    for (int i = 0; i < totalLivros; i++) {
        printf("Codigo: %d | Titulo: %s | Autor: %s | Ano: %d | Status: %s\n",
               biblioteca[i].codigo,  //
               biblioteca[i].titulo,  //
               biblioteca[i].autor,   //
               biblioteca[i].ano,     //
               biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
    }
}

void buscarLivroPorCodigo(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    int codigoBuscado;
    printf("\n--- BUSCAR LIVRO ---\n");
    printf("Digite o codigo do livro que deseja buscar: ");
    scanf("%d", &codigoBuscado);
    limparBuffer();

    int indice = buscarIndicePorCodigo(biblioteca, totalLivros, codigoBuscado);

    if (indice == -1) {
        printf("\n[ERRO] Livro com o codigo %d nao foi encontrado.\n", codigoBuscado);
        return;
    }

    exibirLivro(biblioteca[indice]);
}

void buscarLivroPorTitulo(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    char tituloBuscado[50];
    printf("\n--- BUSCAR LIVRO POR TITULO ---\n");
    printf("Digite o titulo do livro: ");
    fgets(tituloBuscado, sizeof(tituloBuscado), stdin);
    tituloBuscado[strcspn(tituloBuscado, "\n")] = '\0';

    int encontrados = 0;
    for (int i = 0; i < totalLivros; i++) {
        if (strstr(biblioteca[i].titulo, tituloBuscado) != NULL) {
            exibirLivro(biblioteca[i]);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\n[ERRO] Nenhum livro com o titulo \"%s\" foi encontrado.\n", tituloBuscado);
    }
}

void atualizarLivro(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;
    int codigoBuscado;

    printf("\n--- ATUALIZAR LIVRO ---\n");
    exibirTodosLivros(biblioteca, totalLivros);
    
    printf("Digite o codigo do livro que deseja atualizar: ");
    scanf("%d", &codigoBuscado);
    limparBuffer();

    int indice = buscarIndicePorCodigo(biblioteca, totalLivros, codigoBuscado);

    if (indice == -1) {
        printf("\n[ERRO] Livro com o codigo %d nao foi encontrado.\n", codigoBuscado);
        return;
    }

    printf("\nDigite o novo titulo: ");
    fgets(biblioteca[indice].titulo, sizeof(biblioteca[indice].titulo), stdin);
    biblioteca[indice].titulo[strcspn(biblioteca[indice].titulo, "\n")] = '\0';

    printf("Digite o novo autor: ");
    fgets(biblioteca[indice].autor, sizeof(biblioteca[indice].autor), stdin);
    biblioteca[indice].autor[strcspn(biblioteca[indice].autor, "\n")] = '\0';

    printf("Digite o novo ano de publicacao: ");
    scanf("%d", &biblioteca[indice].ano);

    printf("O livro esta disponivel? (1-Sim / 0-Nao): ");
    scanf("%d", &biblioteca[indice].disponivel);
    limparBuffer();

    printf("\n[SUCESSO] Informacoes do livro atualizadas com sucesso!\n");
}

void excluirLivro(Livro biblioteca[], int *totalLivros) {
    if (bibliotecaVazia(*totalLivros)) return;
    int codigoBuscado;

    printf("\n--- REMOVER LIVRO ---\n");
    exibirTodosLivros(biblioteca, *totalLivros);
    
    printf("\nDigite o codigo do livro que deseja remover: ");
    scanf("%d", &codigoBuscado);
    limparBuffer();

    int indice = buscarIndicePorCodigo(biblioteca, *totalLivros, codigoBuscado);

    if (indice == -1) {
        printf("\n[ERRO] Livro com o codigo %d nao foi encontrado.\n", codigoBuscado);
        return;
    }

    for (int i = indice; i < *totalLivros - 1; i++) {
        biblioteca[i] = biblioteca[i + 1];
    }

    (*totalLivros)--;

    printf("\nLivro removido com sucesso!\n");
}

void exibirLivrosDisponiveis(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    printf("\n=== LIVROS DISPONIVEIS ===\n");

    int encontrados = 0;
    for (int i = 0; i < totalLivros; i++) {
        if (biblioteca[i].disponivel) {
            printf("\nCodigo: %d | Titulo: %s | Autor: %s | Ano: %d\n",
                   biblioteca[i].codigo,  //
                   biblioteca[i].titulo,  //
                   biblioteca[i].autor,   //
                   biblioteca[i].ano);    //

            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum livro disponivel no momento.\n");
    }
    printf("===========================\n");
}

void alterarStatusEmprestimo(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    int codigoBuscado;
    printf("\n--- ALTERAR STATUS DE EMPRESTIMO ---\n");
    printf("Digite o codigo do livro: ");
    scanf("%d", &codigoBuscado);
    limparBuffer();

    int indice = buscarIndicePorCodigo(biblioteca, totalLivros, codigoBuscado);

    if (indice == -1) {
        printf("\n[ERRO] Livro com o codigo %d nao foi encontrado.\n", codigoBuscado);
        return;
    }

    biblioteca[indice].disponivel = !biblioteca[indice].disponivel;
    printf("\n[SUCESSO] Status alterado para: %s\n", biblioteca[indice].disponivel ? "Disponivel" : "Emprestado");
}

void exibirEstatisticas(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    int disponiveis = 0;
    int emprestados = 0;

    for (int i = 0; i < totalLivros; i++) {
        if (biblioteca[i].disponivel) {
            disponiveis++;
        } else {
            emprestados++;
        }
    }

    printf("\n=== ESTATISTICAS DA BIBLIOTECA ===\n");
    printf("Total de livros cadastrados: %d\n", totalLivros);
    printf("Livros disponiveis: %d\n", disponiveis);
    printf("Livros emprestados: %d\n", emprestados);
    printf("==================================\n");
}

// Funções auxiliares
int buscarIndicePorCodigo(Livro biblioteca[], int totalLivros, int codigoBuscado) {
    for (int i = 0; i < totalLivros; i++) {
        if (biblioteca[i].codigo == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

int bibliotecaCheia(int totalLivros) {
    if (totalLivros >= MAX_LIVROS) {
        printf("\n[AVISO] A biblioteca esta cheia! Nao e possivel cadastrar mais livros.\n");
        return 1;
    }
    return 0;
}

int bibliotecaVazia(int totalLivros) {
    if (totalLivros == 0) {
        printf("\n[AVISO] Nenhum livro cadastrado na biblioteca.\n");
        return 1;
    }
    return 0;
}

void exibirLivro(Livro livro) {
    printf("\n=== LIVRO ENCONTRADO ===\n");
    printf("Codigo: %d\n", livro.codigo);
    printf("Titulo: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Ano: %d\n", livro.ano);
    printf("Status: %s\n", livro.disponivel ? "Disponivel" : "Emprestado");
    printf("=========================\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}