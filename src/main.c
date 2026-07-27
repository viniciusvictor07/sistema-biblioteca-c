#include <stdio.h>
#include <stdlib.h>

#include "arquivo.h"
#include "livros.h"

int main() {
    Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int proximoCodigo = 1;
    int opcao;

    carregarLivros(biblioteca, &totalLivros, &proximoCodigo);

    while (1) {
        limparTela();
        mostrarMenu();
        opcao = lerInteiro("", 0, 12);
        switch (opcao) {
            case 1:
                limparTela();
                cadastrarLivro(biblioteca, &totalLivros, &proximoCodigo);
                pausar();
                break;
            case 2:
                limparTela();
                exibirTodosLivros(biblioteca, totalLivros);
                pausar();
                break;
            case 3:
                limparTela();
                buscarLivroPorCodigo(biblioteca, totalLivros);
                pausar();
                break;
            case 4:
                limparTela();
                buscarLivroPorTitulo(biblioteca, totalLivros);
                pausar();
                break;
            case 5:
                limparTela();
                atualizarLivro(biblioteca, totalLivros);
                pausar();
                break;
            case 6:
                limparTela();
                excluirLivro(biblioteca, &totalLivros);
                pausar();
                break;
            case 7:
                limparTela();
                exibirLivrosDisponiveis(biblioteca, totalLivros);
                pausar();
                break;
            case 8:
                limparTela();
                salvarLivros(biblioteca, totalLivros);
                pausar();
                break;
            case 9:
                limparTela();
                alterarStatusEmprestimo(biblioteca, totalLivros);
                pausar();
                break;
            case 10:
                limparTela();
                exibirEstatisticas(biblioteca, totalLivros);
                pausar();
                break;
            case 11:
                limparTela();
                buscarLivrosPorCategoria(biblioteca, totalLivros);
                pausar();
                break;
            case 12:
                limparTela();
                buscarLivrosPorAutor(biblioteca, totalLivros);
                pausar();
                break;
            case 0:
                limparTela();
                salvarLivros(biblioteca, totalLivros);
                printf("\nDados salvos. Encerrando o sistema... Ate logo!\n");
                return 0;
            default:
                printf("\n[ERRO] Opcao inexistente. Tente novamente.\n");
        }
    }

    return 0;
}