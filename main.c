#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_NUMEROS 10000

// =====================================
// Funções Protótipos
// =====================================
void exibirMenu(void);
void executarMenu(void);
void menuOrdenacao(void);
void criarArquivo(void);
int lerInteiro(const char* mensagem, int* valor);
int salvarNumeros(const int numeros[], int quantidade);
void visualizarDados(void);
int carregarDados(int numeros[], int* quantidade);
void executarOrdenacao(int algoritmo);
int salvarOrdenados(const int numeros[], int quantidade);
void compararAlgoritmos(void);
double obterTempo(void);
int salvarBenchmark(const char* nomes[], const double tempos[], int quantidade);
void alterarNumero(void);

// Métodos de Ordenação
void bubbleSort(int numeros[], int quantidade);
void insertionSort(int numeros[], int quantidade);
void selectionSort(int numeros[], int quantidade);
void mergeSort(int numeros[], int inicio, int fim);
void intercalar(int numeros[], int inicio, int meio, int fim);
void quickSort(int numeros[], int inicio, int fim);
int particionar(int numeros[], int inicio, int fim);

// =====================================
// MAIN
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
  printf("                ORDENA C\n");
  printf("========================================\n");
  printf("1 - Criar arquivo de numeros\n");
  printf("2 - Visualizar dados originais\n");
  printf("3 - Ordenar numeros\n");
  printf("4 - Comparar algoritmos\n");
  printf("5 - Alterar um numero\n");
  printf("0 - Sair\n");
  printf("========================================\n");
  printf("Escolha uma opcao: ");
}

// Exibe o submenu de ordenacao e executa o algoritmo escolhido

// =====================================
// MENU DE ORDENACAO
// =====================================
// Permite selecionar um dos cinco algoritmos
void menuOrdenacao(void) {
  int opcao;

  // Repete o submenu ate o usuario escolher voltar
  do {
    printf("\n========== ORDENAC - ORDENACAO ==========\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Insertion Sort\n");
    printf("3 - Selection Sort\n");
    printf("4 - Merge Sort\n");
    printf("5 - Quick Sort\n");
    printf("0 - Voltar\n");
    printf("========================================\n");

    // Le e valida a opcao escolhida
    if (!lerInteiro("Escolha uma opcao: ", &opcao)) {
      opcao = -1;
      continue;
    }

    // Executa o algoritmo selecionado
    switch (opcao) {
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        // Reaproveita a funcao geral de ordenacao
        executarOrdenacao(opcao);
        break;

      case 0:
        printf("\nVoltando ao menu principal...\n");
        break;

      default:
        printf("\nOpcao invalida!\n");
        break;
    }

  } while (opcao != 0);
}

// Repete o menu até o usuário escolher 0 e executa a opção selecionada.
// =====================================
// EXECUTAR MENU PRINCIPAL
// =====================================
// Exibe o menu e executa a opcao escolhida pelo usuario
void executarMenu(void) {
  // Armazena a opcao selecionada
  int opcao;

  // Repete o menu ate o usuario escolher sair
  do {
    // Exibe as opcoes do menu principal
    exibirMenu();

    // Le e valida a opcao digitada
    if (!lerInteiro("", &opcao)) {
      opcao = -1;
      continue;
    }

    // Executa a funcionalidade selecionada
    switch (opcao) {
      case 1:
        criarArquivo();
        break;

      case 2:
        visualizarDados();
        break;

      case 3:
        // Abre o submenu dos cinco algoritmos
        menuOrdenacao();
        break;

      case 4:
        // Executa a comparacao e registra o benchmark
        compararAlgoritmos();
        break;

      case 5:
        // Funcionalidade que implementaremos a seguir
        alterarNumero();
        break;

      case 0:
        printf("\nEncerrando OrdenaC...\n");
        break;

      default:
        printf("\nOpcao invalida!\n");
        break;
    }
  } while (opcao != 0);
}

// Le e valida um numero inteiro digitado pelo usuario
// Retorna 1 se for valido e 0 se for invalido

// =====================================
// LER INTEIRO
// =====================================
// Le e valida um numero inteiro digitado pelo usuario.
// Retorna 1 para entrada valida e 0 para entrada invalida.
int lerInteiro(const char* mensagem, int* valor) {
  // Armazena o texto digitado pelo usuario
  char entrada[32];
  char* fim;
  int caractere;

  // Exibe a mensagem solicitando a entrada
  printf("%s", mensagem);

  // Le uma linha do teclado
  if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
    return 0;
  }

  // Verifica se a entrada ultrapassou o tamanho permitido
  if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
    // Descarta os caracteres restantes da linha
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }

    printf("\nEntrada muito longa!\n");
    return 0;
  }

  // Reinicia o indicador de erro antes da conversao
  errno = 0;

  // Converte o texto para um numero inteiro do tipo long
  long numero = strtol(entrada, &fim, 10);

  // Verifica se nenhum numero foi encontrado
  if (entrada == fim) {
    printf("\nDigite um numero inteiro valido!\n");
    return 0;
  }

  // Ignora espacos e a quebra de linha apos o numero
  while (*fim == ' ' || *fim == '\t' || *fim == '\n' || *fim == '\r') {
    fim++;
  }

  // Verifica se houve erro, caracteres extras ou
  // se o numero ultrapassa os limites do tipo int
  if (errno == ERANGE || *fim != '\0' || numero < INT_MIN || numero > INT_MAX) {
    printf("\nDigite um numero inteiro valido!\n");
    return 0;
  }

  // Armazena o numero validado na variavel recebida
  *valor = (int)numero;

  // Informa que a leitura foi concluida
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
    printf("\nQuantidade invalida! Digite números entre 1 e 10000\n");
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

  // Preenche o vetor com números pseudoaleatórios entre 1 e 10000; podem
  // ocorrer repetições. Percorre todas as posições do vetor, de 0 até
  // quantidade - 1.
  for (int i = 0; i < quantidade; i++) {
    numeros[i] = (rand() % 10000) + 1;
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

// Exibe os numeros originais armazenados no arquivo
void visualizarDados(void) {
  // Reserva memoria para os numeros
  int* numeros = malloc(MAX_NUMEROS * sizeof(int));
  int quantidade = 0;

  // Verifica se a memoria foi alocada
  if (numeros == NULL) {
    printf("\nErro ao alocar memoria!\n");
    return;
  }

  // Carrega os numeros do arquivo
  if (!carregarDados(numeros, &quantidade)) {
    free(numeros);
    return;
  }

  // Exibe os numeros carregados
  printf("\n=== DADOS ORIGINAIS ===\n");
  printf("Total: %d numeros\n", quantidade);

  for (int i = 0; i < quantidade; i++) {
    printf("%d", numeros[i]);

    // Adiciona virgula entre os numeros
    if (i < quantidade - 1) {
      printf(", ");
    }
  }

  printf("\n");

  // Libera a memoria utilizada
  free(numeros);
}

// Carregar os numeros do arquivo para um vetor
// Retorna 1 para sucesso e 0 em caso de erro

// =====================================
// CARREGAR DADOS
// =====================================
// Le os numeros do arquivo data/dados.txt.
// Retorna 1 em caso de sucesso e 0 em caso de erro.
int carregarDados(int numeros[], int* quantidade) {
  // Abre o arquivo para leitura
  FILE* arquivo = fopen("data/dados.txt", "r");

  // Verifica se o arquivo existe e pode ser aberto
  if (arquivo == NULL) {
    printf("\nErro ao abrir o arquivo de dados!\n");
    return 0;
  }

  // Inicializa a quantidade de numeros carregados
  *quantidade = 0;

  int numero;
  int separador;
  int resultado;

  // Le os numeros do arquivo
  while (1) {
    // Tenta ler um numero inteiro
    resultado = fscanf(arquivo, "%d", &numero);

    // Verifica se chegou ao final do arquivo
    if (resultado == EOF) {
      break;
    }

    // Rejeita conteudo que nao seja um inteiro
    if (resultado != 1) {
      printf("\nErro: numero invalido no arquivo!\n");
      fclose(arquivo);
      return 0;
    }

    // Verifica se o numero esta no intervalo permitido
    if (numero < 1 || numero > MAX_NUMEROS) {
      printf("\nErro: numero fora do intervalo de 1 a 10000!\n");
      fclose(arquivo);
      return 0;
    }

    // Verifica o limite de elementos do vetor
    if (*quantidade >= MAX_NUMEROS) {
      printf("\nErro: limite de numeros excedido!\n");
      fclose(arquivo);
      return 0;
    }

    // Armazena o numero lido
    numeros[*quantidade] = numero;
    (*quantidade)++;

    // Le o caractere que aparece depois do numero
    separador = fgetc(arquivo);

    // Finaliza se encontrou o fim do arquivo
    if (separador == EOF) {
      break;
    }

    // Aceita quebra de linha somente no final
    if (separador == '\n') {
      if (fgetc(arquivo) != EOF) {
        printf("\nErro: conteudo inesperado apos a quebra de linha!\n");
        fclose(arquivo);
        return 0;
      }
      break;
    }

    // Verifica se o separador e uma virgula
    if (separador != ',') {
      printf("\nErro: separador invalido no arquivo!\n");
      fclose(arquivo);
      return 0;
    }

    // Verifica se existe outro numero apos a virgula
    separador = fgetc(arquivo);

    if (separador == EOF) {
      printf("\nErro: virgula sem numero no final do arquivo!\n");
      fclose(arquivo);
      return 0;
    }

    // Devolve o caractere para a proxima leitura
    ungetc(separador, arquivo);
  }

  // Fecha o arquivo e verifica se houve erro
  if (fclose(arquivo) == EOF) {
    printf("\nErro ao fechar o arquivo de dados!\n");
    return 0;
  }

  // Informa que a leitura foi concluida
  return 1;
}

// =====================================
// EXECUTAR ORDENACAO
// =====================================
// Carrega os dados, executa o algoritmo escolhido
// e salva os numeros ordenados em arquivo
void executarOrdenacao(int algoritmo) {
  // Aloca memoria para os numeros
  int* numeros = malloc(MAX_NUMEROS * sizeof(int));
  int quantidade = 0;

  // Verifica se a memoria foi alocada
  if (numeros == NULL) {
    printf("\nErro ao alocar memoria!\n");
    return;
  }

  // Carrega os numeros originais
  if (!carregarDados(numeros, &quantidade)) {
    free(numeros);
    return;
  }

  // Verifica se existem numeros para ordenar
  if (quantidade == 0) {
    printf("\nNenhum numero para ordenar!\n");
    free(numeros);
    return;
  }

  // Seleciona o algoritmo de ordenacao
  switch (algoritmo) {
    case 1:
      bubbleSort(numeros, quantidade);
      break;

    case 2:
      insertionSort(numeros, quantidade);
      break;

    case 3:
      selectionSort(numeros, quantidade);
      break;

    case 4:
      mergeSort(numeros, 0, quantidade - 1);
      break;

    case 5:
      quickSort(numeros, 0, quantidade - 1);
      break;

    default:
      printf("\nAlgoritmo ainda nao implementado!\n");
      free(numeros);
      return;
  }

  // Salva os numeros ordenados em arquivo
  if (salvarOrdenados(numeros, quantidade)) {
    printf("\nOrdenacao concluida! Arquivo salvo com sucesso.\n");
  }

  // Libera a memoria utilizada
  free(numeros);
}

// =====================================
// COMPARAR ALGORITMOS
// =====================================
// Executa os cinco algoritmos com os mesmos numeros,
// mede seus tempos e identifica o mais rapido ou empates.
void compararAlgoritmos(void) {
  // Aloca memoria para os numeros originais e sua copia
  int* originais = malloc(MAX_NUMEROS * sizeof(int));
  int* copia = malloc(MAX_NUMEROS * sizeof(int));

  // Armazena a quantidade de numeros carregados
  int quantidade = 0;

  // Armazena o tempo de execucao de cada algoritmo
  double tempos[5];

  // Nomes dos algoritmos
  const char* nomes[5] = {"Bubble Sort", "Insertion Sort", "Selection Sort",
                          "Merge Sort", "Quick Sort"};

  // Verifica se a memoria foi alocada corretamente
  if (originais == NULL || copia == NULL) {
    printf("\nErro ao alocar memoria!\n");
    free(originais);
    free(copia);
    return;
  }

  // Carrega os numeros originais do arquivo
  if (!carregarDados(originais, &quantidade)) {
    free(originais);
    free(copia);
    return;
  }

  // Verifica se existem numeros para comparar
  if (quantidade == 0) {
    printf("\nNenhum numero para comparar!\n");
    free(originais);
    free(copia);
    return;
  }

  // Executa os cinco algoritmos separadamente
  for (int algoritmo = 0; algoritmo < 5; algoritmo++) {
    // Restaura os dados originais antes de cada teste
    for (int i = 0; i < quantidade; i++) {
      copia[i] = originais[i];
    }

    // Registra o instante inicial da ordenacao
    double inicio = obterTempo();

    // Seleciona o algoritmo
    switch (algoritmo) {
      case 0:
        bubbleSort(copia, quantidade);
        break;

      case 1:
        insertionSort(copia, quantidade);
        break;

      case 2:
        selectionSort(copia, quantidade);
        break;

      case 3:
        mergeSort(copia, 0, quantidade - 1);
        break;

      case 4:
        quickSort(copia, 0, quantidade - 1);
        break;
    }

    // Registra o instante final da ordenacao
    double fim = obterTempo();

    // Calcula o tempo decorrido em milissegundos
    tempos[algoritmo] = fim - inicio;
  }

  // Apresenta o resultado da comparacao
  printf("\n========== COMPARACAO DE ALGORITMOS ==========\n");
  printf("Quantidade de numeros: %d\n\n", quantidade);

  printf("%-20s %15s\n", "Algoritmo", "Tempo (ms)");
  printf("--------------------------------------\n");

  // Localiza o algoritmo com o menor tempo medido
  int maisRapido = 0;

  for (int i = 0; i < 5; i++) {
    // Exibe o nome e o tempo do algoritmo
    printf("%-20s %15.6f\n", nomes[i], tempos[i]);

    // Atualiza o menor tempo encontrado
    if (tempos[i] < tempos[maisRapido]) {
      maisRapido = i;
    }
  }

  // Arredonda o menor tempo para seis casas decimais
  // usando unidades de 0,000001 milissegundo
  long long menorArredondado =
      (long long)(tempos[maisRapido] * 1000000.0 + 0.5);

  // Conta quantos algoritmos empataram no tempo exibido
  int empates = 0;

  for (int i = 0; i < 5; i++) {
    long long tempoArredondado = (long long)(tempos[i] * 1000000.0 + 0.5);

    if (tempoArredondado == menorArredondado) {
      empates++;
    }
  }

  // Exibe o vencedor ou os algoritmos empatados
  printf("--------------------------------------\n");

  if (empates == 1) {
    printf("Mais rapido neste teste: %s\n", nomes[maisRapido]);
  } else {
    printf("Empate entre os algoritmos:\n");

    for (int i = 0; i < 5; i++) {
      long long tempoArredondado = (long long)(tempos[i] * 1000000.0 + 0.5);

      if (tempoArredondado == menorArredondado) {
        printf("- %s\n", nomes[i]);
      }
    }
  }

  // Registra os resultados no historico CSV
  if (salvarBenchmark(nomes, tempos, quantidade)) {
    printf("\nBenchmark salvo em logs/benchmark.csv!\n");
  } else {
    printf("\nNao foi possivel salvar o benchmark.\n");
  }

  // Libera toda a memoria utilizada
  free(originais);
  free(copia);
}

// Retorna o tempo atual em milissegundos
// utilizando o contador de alta resolucao do Windows
double obterTempo(void) {
  LARGE_INTEGER frequencia;
  LARGE_INTEGER contador;

  // Obtem a frequencia do contador
  QueryPerformanceFrequency(&frequencia);

  // Obtem o valor atual do contador
  QueryPerformanceCounter(&contador);

  // Converte o resultado para milissegundos
  return ((double)contador.QuadPart / frequencia.QuadPart) * 1000.0;
}

// =====================================
// SALVAR BENCHMARK
// =====================================
// Acrescenta os resultados dos cinco algoritmos
// ao arquivo CSV, preservando os testes anteriores.
int salvarBenchmark(const char* nomes[], const double tempos[],
                    int quantidade) {
  // Abre o arquivo para leitura e acrescimo
  FILE* arquivo = fopen("logs/benchmark.csv", "a+");

  // Verifica se o arquivo foi aberto
  if (arquivo == NULL) {
    printf("\nErro ao abrir logs/benchmark.csv!\n");
    return 0;
  }

  // Verifica o tamanho atual do arquivo
  if (fseek(arquivo, 0, SEEK_END) != 0) {
    fclose(arquivo);
    return 0;
  }

  long tamanho = ftell(arquivo);

  if (tamanho < 0) {
    fclose(arquivo);
    return 0;
  }

  // Escreve o cabecalho somente em arquivos vazios
  if (tamanho == 0) {
    if (fprintf(arquivo, "Data,Hora,Quantidade,Algoritmo,Tempo_ms\n") < 0) {
      fclose(arquivo);
      return 0;
    }
  }

  // Obtem a data e hora da execucao
  time_t agora = time(NULL);
  struct tm* dataHora = localtime(&agora);

  // Verifica se a data e hora foram obtidas
  if (dataHora == NULL) {
    fclose(arquivo);
    return 0;
  }

  // Registra o resultado dos cinco algoritmos
  for (int i = 0; i < 5; i++) {
    if (fprintf(arquivo, "%04d-%02d-%02d,%02d:%02d:%02d,%d,%s,%.6f\n",
                dataHora->tm_year + 1900, dataHora->tm_mon + 1,
                dataHora->tm_mday, dataHora->tm_hour, dataHora->tm_min,
                dataHora->tm_sec, quantidade, nomes[i], tempos[i]) < 0) {
      printf("\nErro ao gravar benchmark!\n");
      fclose(arquivo);
      return 0;
    }
  }

  // Finaliza a gravacao do arquivo
  if (fclose(arquivo) == EOF) {
    printf("\nErro ao finalizar o benchmark!\n");
    return 0;
  }

  return 1;
}

// =====================================
// ALTERAR NUMERO
// =====================================
// Permite alterar um numero pela sua posicao
// e atualizar o arquivo de dados originais.
void alterarNumero(void) {
  // Reserva memoria para armazenar os numeros
  int* numeros = malloc(MAX_NUMEROS * sizeof(int));

  // Variaveis utilizadas na alteracao
  int quantidade = 0;
  int posicao;
  int novoValor;

  // Verifica se a memoria foi alocada corretamente
  if (numeros == NULL) {
    printf("\nErro ao alocar memoria!\n");
    return;
  }

  // Carrega os numeros do arquivo original
  if (!carregarDados(numeros, &quantidade)) {
    free(numeros);
    return;
  }

  // Verifica se existem numeros para alterar
  if (quantidade == 0) {
    printf("\nNenhum numero encontrado!\n");
    free(numeros);
    return;
  }

  // Apresenta as informacoes
  printf("\n========== ALTERAR NUMERO ==========\n");
  printf("Total de numeros: %d\n", quantidade);

  // Solicita a posicao que sera alterada
  if (!lerInteiro("\nDigite a posicao que deseja alterar: ", &posicao)) {
    free(numeros);
    return;
  }

  // Verifica se a posicao esta dentro do vetor
  if (posicao < 1 || posicao > quantidade) {
    printf("\nPosicao invalida! Escolha entre 1 e %d.\n", quantidade);
    free(numeros);
    return;
  }

  // Exibe o valor atual da posicao escolhida
  printf("Valor atual: %d\n", numeros[posicao - 1]);

  // Solicita o novo valor
  if (!lerInteiro("Digite o novo valor (1 a 10000): ", &novoValor)) {
    free(numeros);
    return;
  }

  // Verifica se o novo valor esta no intervalo permitido
  if (novoValor < 1 || novoValor > MAX_NUMEROS) {
    printf("\nValor invalido! Digite entre 1 e 10000.\n");
    free(numeros);
    return;
  }

  // Substitui o numero na posicao escolhida
  numeros[posicao - 1] = novoValor;

  // Salva o vetor atualizado no arquivo original
  if (salvarNumeros(numeros, quantidade)) {
    printf("\nNumero alterado com sucesso!\n");
    printf("Arquivo data/dados.txt atualizado.\n");
  }

  // Libera a memoria utilizada
  free(numeros);
}

// =====================================
// BUBBLE SORT
// =====================================
// Ordena um vetor de numeros inteiros em ordem crescente
// utilizando o algoritmo Bubble Sort otimizado
void bubbleSort(int numeros[], int quantidade) {
  // Controla a quantidade de passagens pelo vetor
  for (int i = 0; i < quantidade - 1; i++) {
    // Reinicia o controle de trocas a cada passagem
    int houveTroca = 0;

    // Percorre os elementos ainda não ordenados
    for (int j = 0; j < quantidade - i - 1; j++) {
      // Verifica se dois elementos vizinhos estao fora de ordem (aonde acontece
      // a troca, efeito bubble)
      if (numeros[j] > numeros[j + 1]) {
        // Armazena temporariamente o numero atual
        int temporario = numeros[j];

        // Move o menor numero para a esquerda
        numeros[j] = numeros[j + 1];

        // Move o maior numero para a direita
        numeros[j + 1] = temporario;

        // Registra que houve pelo menos uma troca
        houveTroca = 1;
      }
    }

    // Se nenhuma troca aconteceu, o vetor ja esta ordenado
    if (houveTroca == 0) {
      break;
    }
  }
}

// =====================================
// INSERTION SORT
// =====================================
// Ordena um vetor em ordem crescente por insercao
void insertionSort(int numeros[], int quantidade) {
  // Comeca no segundo elemento do vetor
  for (int i = 1; i < quantidade; i++) {
    // Guarda o numero que sera inserido na parte ordenada
    int atual = numeros[i];

    // Posicao anterior ao numero atual
    int j = i - 1;

    // Desloca os numeros maiores para a direita
    while (j >= 0 && numeros[j] > atual) {
      numeros[j + 1] = numeros[j];
      j--;
    }

    // Insere o numero na posicao correta
    numeros[j + 1] = atual;
  }
}

// =====================================
// SELECTION SORT
// =====================================
// Ordena os numeros em ordem crescente por selecao
void selectionSort(int numeros[], int quantidade) {
  // Percorre as posicoes que receberao os menores numeros
  for (int i = 0; i < quantidade - 1; i++) {
    // Considera inicialmente a posicao atual como a menor
    int indiceMenor = i;

    // Procura um numero menor na parte ainda nao ordenada
    for (int j = i + 1; j < quantidade; j++) {
      // Atualiza o indice caso encontre um numero menor
      if (numeros[j] < numeros[indiceMenor]) {
        indiceMenor = j;
      }
    }

    // Realiza a troca somente se encontrou um numero menor
    if (indiceMenor != i) {
      // Guarda temporariamente o numero atual
      int temporario = numeros[i];

      // Coloca o menor numero na posicao atual
      numeros[i] = numeros[indiceMenor];

      // Move o numero anterior para a posicao do menor
      numeros[indiceMenor] = temporario;
    }
  }
}

// =====================================
// MERGE SORT
// =====================================
// Divide recursivamente o vetor em partes menores
void mergeSort(int numeros[], int inicio, int fim) {
  // Continua dividindo enquanto houver mais de um elemento
  if (inicio < fim) {
    // Calcula a posicao central do trecho atual
    int meio = inicio + (fim - inicio) / 2;

    // Ordena a metade esquerda
    mergeSort(numeros, inicio, meio);

    // Ordena a metade direita
    mergeSort(numeros, meio + 1, fim);

    // Junta as duas metades em ordem crescente
    intercalar(numeros, inicio, meio, fim);
  }
}

// =====================================
// INTERCALAR
// =====================================
// Junta duas partes ordenadas em um unico trecho ordenado
void intercalar(int numeros[], int inicio, int meio, int fim) {
  // Calcula a quantidade de elementos do trecho
  int tamanho = fim - inicio + 1;

  // Reserva memoria temporaria para a intercalação
  int* auxiliar = malloc(tamanho * sizeof(int));

  // Verifica se a memoria foi alocada corretamente
  if (auxiliar == NULL) {
    printf("\nErro ao alocar memoria!\n");
    exit(EXIT_FAILURE);
  }

  // Indice inicial da metade esquerda
  int i = inicio;

  // Indice inicial da metade direita
  int j = meio + 1;

  // Indice do vetor auxiliar
  int k = 0;

  // Compara os elementos das duas metades
  while (i <= meio && j <= fim) {
    // Copia o menor elemento para o vetor auxiliar
    if (numeros[i] <= numeros[j]) {
      auxiliar[k++] = numeros[i++];
    } else {
      auxiliar[k++] = numeros[j++];
    }
  }

  // Copia os elementos restantes da metade esquerda
  while (i <= meio) {
    auxiliar[k++] = numeros[i++];
  }

  // Copia os elementos restantes da metade direita
  while (j <= fim) {
    auxiliar[k++] = numeros[j++];
  }

  // Devolve os numeros ordenados ao vetor original
  for (int n = 0; n < tamanho; n++) {
    numeros[inicio + n] = auxiliar[n];
  }

  // Libera a memoria temporaria
  free(auxiliar);
}

// =====================================
// PARTICIONAR
// =====================================
// Organiza os numeros em torno de um pivo
// e retorna a posicao definitiva desse pivo
int particionar(int numeros[], int inicio, int fim) {
  // Seleciona o ultimo numero como pivo
  int pivo = numeros[fim];

  // Controla a posicao dos numeros menores ou iguais ao pivo
  int i = inicio - 1;

  // Percorre os elementos anteriores ao pivo
  for (int j = inicio; j < fim; j++) {
    // Verifica se o numero atual e menor ou igual ao pivo
    if (numeros[j] <= pivo) {
      // Avanca a regiao dos numeros menores
      i++;

      // Troca o numero atual com o da posicao i
      int temporario = numeros[i];
      numeros[i] = numeros[j];
      numeros[j] = temporario;
    }
  }

  // Coloca o pivo entre os menores e os maiores
  int temporario = numeros[i + 1];
  numeros[i + 1] = numeros[fim];
  numeros[fim] = temporario;

  // Retorna a posicao definitiva do pivo
  return i + 1;
}

// =====================================
// QUICK SORT
// =====================================
// Ordena recursivamente o vetor utilizando Quick Sort
void quickSort(int numeros[], int inicio, int fim) {
  // Continua enquanto o trecho tiver mais de um elemento
  if (inicio < fim) {
    // Organiza os numeros e encontra a posicao do pivo
    int posicaoPivo = particionar(numeros, inicio, fim);

    // Ordena a parte esquerda do pivo
    quickSort(numeros, inicio, posicaoPivo - 1);

    // Ordena a parte direita do pivo
    quickSort(numeros, posicaoPivo + 1, fim);
  }
}

// Salvar arquivos ordenados
int salvarOrdenados(const int numeros[], int quantidade) {
  FILE* arquivo = fopen("output/ordenado.txt", "w");

  if (arquivo == NULL) {
    printf("\nErro ao criar o arquivo ordenado!\n");
    return 0;
  }

  for (int i = 0; i < quantidade; i++) {
    if (fprintf(arquivo, "%d", numeros[i]) < 0) {
      printf("\nErro ao gravar os numeros ordenados!\n");
      fclose(arquivo);
      return 0;
    }

    if (i < quantidade - 1) {
      if (fputc(',', arquivo) == EOF) {
        printf("\nErro ao gravar o separador!\n");
        fclose(arquivo);
        return 0;
      }
    }
  }

  // Fecha somente depois de gravar todos os numeros.
  if (fclose(arquivo) == EOF) {
    printf("\nErro ao finalizar o arquivo ordenado!\n");
    return 0;
  }

  return 1;
}