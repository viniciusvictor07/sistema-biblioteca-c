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
        printf("\n==========================================\n");
        printf("  SISTEMA DE GERENCIAMENTO DE BIBLIOTECA \n");
        printf("==========================================\n");
        printf("1.  Cadastrar novo livro\n");
        printf("2.  Exibir todos os livros\n");
        printf("3.  Buscar livro por codigo\n");
        printf("4.  Buscar livro por titulo\n");
        printf("5.  Atualizar dados de um livro\n");
        printf("6.  Excluir livro\n");
        printf("7.  Exibir livros disponiveis\n");
        printf("8.  Emprestar/Devolver livro (Extra)\n");
        printf("9.  Exibir estatisticas da biblioteca (Extra)\n");
        printf("10. Salvar dados no arquivo\n");
        printf("0.  Sair\n");
        printf("------------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }

        limparBuffer();
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
                alterarStatusEmprestimo(biblioteca, totalLivros);
                pausar();
                break;
            case 9:
                limparTela();
                exibirEstatisticas(biblioteca, totalLivros);
                pausar();
                break;
            case 10:
                limparTela();
                salvarLivros(biblioteca, totalLivros);
                pausar();
                break;
            case 0:
                limparTela();
                salvarLivros(biblioteca, totalLivros);
                printf("\nEncerrando o sistema... Ate logo!\n");
                return 0;
            default:
                printf("\n[ERRO] Opcao inexistente. Tente novamente.\n");
        }
    }

    return 0;
}