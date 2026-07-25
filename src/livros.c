#include "livros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funções principais
void cadastrarLivro(Livro biblioteca[], int *totalLivros, int *proximoCodigo) {
    if (bibliotecaCheia(*totalLivros)) return;

    Livro novoLivro;
    novoLivro.codigo = *proximoCodigo;

    printf("\n--- CADASTRO DE NOVO LIVRO ---\n");
    printf("Codigo: %d\n", novoLivro.codigo);

    printf("Digite o titulo: ");
    lerString(novoLivro.titulo, sizeof(novoLivro.titulo));

    printf("Digite o autor: ");
    lerString(novoLivro.autor, sizeof(novoLivro.autor));

    novoLivro.ano = lerInteiro("Digite o ano de publicacao: ", 1, ANO_ATUAL);
    novoLivro.disponivel = lerInteiro("O livro esta disponivel? (1 - Sim / 0 - Nao): ", 0, 1);

    biblioteca[*totalLivros] = novoLivro;
    (*totalLivros)++;
    (*proximoCodigo)++;

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

    printf("\n--- BUSCAR LIVRO ---\n");
    int indice = pedirEBuscarIndice(biblioteca, totalLivros);
    if (indice != -1) {
        exibirLivro(biblioteca[indice]);
    }
}

void buscarLivroPorTitulo(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    char tituloBuscado[50];
    printf("\n--- BUSCAR LIVRO POR TITULO ---\n");
    printf("Digite o titulo do livro: ");
    lerString(tituloBuscado, sizeof(tituloBuscado));

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

    printf("\n--- ATUALIZAR LIVRO ---\n");
    exibirTodosLivros(biblioteca, totalLivros);

    int indice = pedirEBuscarIndice(biblioteca, totalLivros);
    if (indice == -1) return;

    printf("\nDigite o novo titulo: ");
    lerString(biblioteca[indice].titulo, sizeof(biblioteca[indice].titulo));

    printf("Digite o novo autor: ");
    lerString(biblioteca[indice].autor, sizeof(biblioteca[indice].autor));

    biblioteca[indice].ano = lerInteiro("Digite o novo ano de publicacao: ", 1, ANO_ATUAL);
    biblioteca[indice].disponivel = lerInteiro("O livro esta disponivel? (1 - Sim / 0 - Nao): ", 0, 1);

    printf("\n[SUCESSO] Informacoes do livro atualizadas com sucesso!\n");
}

void excluirLivro(Livro biblioteca[], int *totalLivros) {
    if (bibliotecaVazia(*totalLivros)) return;

    printf("\n--- REMOVER LIVRO ---\n");
    exibirTodosLivros(biblioteca, *totalLivros);

    int indice = pedirEBuscarIndice(biblioteca, *totalLivros);
    if (indice == -1) return;

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
            exibirLivro(biblioteca[i]);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum livro disponivel no momento.\n");
    }
    printf("===========================\n");
}

// Funções extras
void alterarStatusEmprestimo(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    printf("\n--- ALTERAR STATUS DE EMPRESTIMO ---\n");
    exibirTodosLivros(biblioteca, totalLivros);

    int indice = pedirEBuscarIndice(biblioteca, totalLivros);
    if (indice == -1) return;

    biblioteca[indice].disponivel = !biblioteca[indice].disponivel;
    printf("\n[SUCESSO] Status do livro '%s' alterado para: %s\n",
           biblioteca[indice].titulo,  //
           biblioteca[indice].disponivel ? "Disponivel" : "Emprestado");
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
int pedirEBuscarIndice(Livro biblioteca[], int totalLivros) {
    int codigo = lerInteiro("Digite o codigo do livro: ", 1, 999999);
    int indice = buscarIndicePorCodigo(biblioteca, totalLivros, codigo);

    if (indice == -1) {
        printf("\n[ERRO] Livro com o codigo %d nao foi encontrado.\n", codigo);
    }

    return indice;
}

int buscarIndicePorCodigo(Livro biblioteca[], int totalLivros, int codigoBuscado) {
    for (int i = 0; i < totalLivros; i++) {
        if (biblioteca[i].codigo == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

int lerInteiro(const char *mensagem, int min, int max) {
    int valor;
    int resultado;

    while (1) {
        printf("%s", mensagem);
        resultado = scanf("%d", &valor);
        limparBuffer();

        if (resultado == 1 && valor >= min && valor <= max) {
            return valor;
        }

        printf("[ERRO] Entrada invalida. Digite um numero entre %d e %d.\n", min, max);
    }
}

void lerString(char *buffer, int tamanho) {
    do {
        fgets(buffer, tamanho, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[0] == '\0') {
            printf("O campo nao pode ficar em branco. Digite novamente: ");
        }
    } while (buffer[0] == '\0');
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