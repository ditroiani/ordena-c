#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMEROS 10000

// =====================================
// Declarações das funções utilizadas pelo programa
// =====================================
void exibirMenu(void);
void executarMenu(void);
void criarArquivo(void);
int lerInteiro(const char* mensagem, int* valor);
int salvarNumeros(const int numeros[], int quantidade);
void visualizarDados(void);
int carregarDados(int numeros[], int* quantidade);

// =====================================
// Início da execução do programa
// =====================================
int main(void) {
  // Usa o horário atual como semente de rand(), inicializando o gerador uma
  // vez. A conversão para unsigned int adapta o valor ao tipo esperado por
  // srand(). Execuções no mesmo segundo podem produzir a mesma sequência.
  srand((unsigned int)time(NULL));

  executarMenu();
  return 0;
}

// =====================================
// EXIBIR MENU
// =====================================
// Exibe as opções disponíveis e solicita a escolha do usuário.
void exibirMenu(void) {
  printf("\n");
  printf("========================================\n");
  printf("              ORDENAÇAO\n");
  printf("========================================\n");
  printf("1 - Criar arquivo de números\n");
  printf("2 - Importar arquivo TXT\n");
  printf("3 - Visualizar dados originais\n");
  printf("4 - Ordenar numeros\n");
  printf("5 - Comparar algoritmos\n");
  printf("6 - Visualizar dados ordenados\n");
  printf("7 - Alterar um numero\n");
  printf("8 - Visualizar relatorios\n");
  printf("0 - Sair\n");
  printf("========================================\n");
  printf("Escolha uma opcao: ");
}

// Repete o menu até o usuário escolher 0 e executa a opção selecionada.
void executarMenu(void) {
  int opcao;
  int caractere;

  do {
    exibirMenu();

    // scanf retorna 1 quando consegue ler e armazenar um inteiro em opcao.
    if (scanf("%d", &opcao) != 1) {
      printf("\nEntrada invalida!\n");

      // Descarta a entrada inválida até o fim da linha ou da entrada (EOF).
      while ((caractere = getchar()) != '\n' && caractere != EOF) {
      }

      // Evita encerrar o menu e inicia uma nova tentativa de leitura.
      opcao = -1;
      continue;
    }

    // Descarta os caracteres restantes da linha após a leitura da opção.
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }

    switch (opcao) {
      case 1:
        criarArquivo();
        break;

      case 2:
        printf("\nImportar arquivo TXT.\n");
        break;

      case 3:
        visualizarDados();
        break;

      case 4:
        printf("\nOrdenar numeros.\n");
        break;

      case 5:
        printf("\nComparar algoritmos.\n");
        break;

      case 6:
        printf("\nVisualizar dados ordenados.\n");
        break;

      case 7:
        printf("\nAlterar um numero.\n");
        break;

      case 8:
        printf("\nVisualizar relatorios.\n");
        break;

      case 0:
        printf("\nEncerrando Algoritmo...\n");
        break;

      default:
        printf("\nOpcao invalida!\n");
    }
  } while (opcao != 0);
}

// =====================================
// Leitura, geração e gravação dos números
// =====================================
// Lê um inteiro e o armazena no endereço recebido em valor. Retorna 1 em caso
// de sucesso ou 0 em caso de falha.
int lerInteiro(const char* mensagem, int* valor) {
  int resultado;

  // Exibe a mensagem recebida para orientar a entrada do usuário.
  printf("%s", mensagem);

  // valor aponta para a variável que receberá o inteiro digitado.
  // resultado recebe a quantidade de valores lidos e armazenados pelo scanf.
  resultado = scanf("%d", valor);

  // Se scanf não armazenou um inteiro, informa o erro e retorna 0.
  if (resultado != 1) {
    printf("Erro: digite um numero inteiro valido!\n");

    // Descarta a entrada inválida até a quebra de linha ou o fim da entrada
    // (EOF).
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }

    return 0;
  }

  return 1;
}

// Solicita a quantidade, gera os números e tenta salvá-los em arquivo.
void criarArquivo(void) {
  int quantidade;
  int* numeros;

  printf("\n========== GERAR DADOS ==========\n");

  // Passa o endereço de quantidade para receber o inteiro; interrompe se a
  // leitura falhar.
  if (!lerInteiro("Quantidade de numeros (1 a 10000): ", &quantidade)) {
    return;
  }

  // Aceita somente quantidades entre 1 e MAX_NUMEROS, inclusive.
  if (quantidade < 1 || quantidade > MAX_NUMEROS) {
    printf("\nQuantidade invalida!\n");
    return;
  }

  // Reserva espaço para quantidade inteiros; sizeof(int) fornece o tamanho de
  // cada um.
  numeros = malloc(quantidade * sizeof(int));

  // malloc retorna NULL se não conseguir reservar a memória solicitada.
  if (numeros == NULL) {
    printf("\nErro ao alocar memoria!\n");
    return;
  }

  // Preenche o vetor com números pseudoaleatórios de 0 a 9999; podem ocorrer
  // repetições. Percorre todas as posições do vetor, de 0 até quantidade - 1.
  for (int i = 0; i < quantidade; i++) {
    numeros[i] = rand() % 10000;
  }

  // Exibe a confirmação somente se a gravação e o fechamento do arquivo tiverem
  // sucesso.
  if (salvarNumeros(numeros, quantidade)) {
    printf("\nArquivo criado com sucesso!\n");
    printf("Total: %d numeros\n", quantidade);
  }

  // Libera a memória do vetor após a tentativa de salvar, mesmo se a gravação
  // falhar.
  free(numeros);
}

// Grava os números separados por vírgulas. Retorna 1 em caso de sucesso ou 0 em
// caso de erro.
int salvarNumeros(const int numeros[], int quantidade) {
  // O modo w cria o arquivo ou apaga seu conteúdo anterior se ele já existir.
  FILE* arquivo = fopen("data/dados.txt", "w");

  // NULL indica que não foi possível abrir o arquivo.
  if (arquivo == NULL) {
    printf("Erro ao criar o arquivo!\n");
    return 0;
  }

  // Percorre todas as posições do vetor, de 0 até quantidade - 1.
  for (int i = 0; i < quantidade; i++) {
    // Escreve o número atual e verifica se houve erro.
    if (fprintf(arquivo, "%d", numeros[i]) < 0) {
      printf("Erro ao gravar os dados!\n");
      fclose(arquivo);
      return 0;
    }

    // Só coloca uma vírgula se o número atual não for o último.
    if (i < quantidade - 1) {
      // Escreve a vírgula e verifica se houve erro.
      if (fputc(',', arquivo) == EOF) {
        printf("Erro ao gravar os dados!\n");
        fclose(arquivo);
        return 0;
      }
    }
  }

  // Fecha o arquivo e verifica se houve erro ao concluir a gravação.
  if (fclose(arquivo) == EOF) {
    printf("Erro ao finalizar o arquivo!\n");
    return 0;
  }

  return 1;
}

// Ler o arquivo
void visualizarDados(void) {
  // Abre o arquivo original em modo leitura
  FILE* arquivo = fopen("data/dados.txt", "r");

  // Verifica se foi possivel abrir o arquivo
  if (arquivo == NULL) {
    printf("\nErro ao abrir o arquivo!\n");
    return;
  }

  // Variaveis utilizadas durante a leitura
  int numero;
  int separador;
  int quantidade = 0;

  // Aloca memoria para armazenar ate MAX_NUMEROS inteiros
  int* numeros = malloc(MAX_NUMEROS * sizeof(int));

  // Verifica se a memoria foi alocada corretamente
  if (numeros == NULL) {
    printf("\nErro ao alocar memoria!\n");
    fclose(arquivo);
    return;
  }

  // Le os numeros do arquivo enquanto houver inteiros validos
  while (fscanf(arquivo, "%d", &numero) == 1) {
    // Impede ultrapassar a capacidade do vetor
    if (quantidade >= MAX_NUMEROS) {
      printf("\nErro: limite de numeros excedido!\n");
      free(numeros);
      fclose(arquivo);
      return;
    }

    // Armazena o numero lido na proxima posicao do vetor
    numeros[quantidade] = numero;

    // Atualiza a quantidade de numeros armazenados
    quantidade++;

    // Consome o separador que aparece depois do numero
    separador = fgetc(arquivo);

    // Verifica se chegamos ao fim do arquivo ou da linha
    if (separador == EOF || separador == '\n') {
      break;
    }

    // Verifica se o separador encontrado e uma virgula
    if (separador != ',') {
      printf("\nErro: separador invalido!\n");
      free(numeros);
      fclose(arquivo);
      return;
    }
  }

  // Mostra primeiro número da sequência
  printf("\nTotal de numeros lidos: %d\n", quantidade);

  // Libera a memoria utilizada pelo vetor
  free(numeros);

  // Fecha arquivo
  fclose(arquivo);
}