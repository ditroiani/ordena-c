<div align="center">

# 🔢 OrdenaC

### Algoritmos de ordenação em linguagem C

**Uma aplicação de terminal para explorar, executar e comparar cinco métodos de ordenação.**

![Linguagem C](https://img.shields.io/badge/Linguagem-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Algoritmos](https://img.shields.io/badge/Algoritmos-5-2962FF?style=for-the-badge)
![Interface](https://img.shields.io/badge/Interface-Terminal-333333?style=for-the-badge)
![Plataforma](https://img.shields.io/badge/Plataforma-Windows-0078D4?style=for-the-badge&logo=windows&logoColor=white)

</div>

---

## 🎯 Sobre o projeto

O **OrdenaC** é um projeto acadêmico desenvolvido em **linguagem C** para estudar, na prática, diferentes algoritmos de ordenação e comparar seus desempenhos.

Por meio de um menu no terminal, o programa gera **de 1 a 10.000 números inteiros aleatórios**, permite visualizar e alterar os valores originais, ordena os dados pelo método escolhido e registra os resultados em arquivos **TXT**. Também mede o tempo de execução dos cinco algoritmos e mantém um histórico das comparações em **CSV**.

## ⚙️ Funcionalidades

- 🎲 **Gerar números:** cria um arquivo com até 10.000 números inteiros aleatórios, com valores de 1 a 10.000.
- 📄 **Visualizar e alterar dados:** consulta o arquivo original e permite substituir um número pela sua posição.
- 🔀 **Ordenar:** aplica um dos cinco algoritmos e salva o resultado em ordem crescente.
- ⏱️ **Comparar desempenho:** mede os tempos dos cinco métodos utilizando os mesmos dados de entrada.
- 📊 **Registrar benchmarks:** armazena data, hora, quantidade de números, algoritmo e tempo em um arquivo CSV.

## 🧠 Métodos de ordenação

| Algoritmo | Como funciona | Complexidade média |
|:--|:--|:--:|
| **Bubble Sort** | Compara números vizinhos e troca os que estiverem fora de ordem, levando os maiores para o final. | `O(n²)` |
| **Insertion Sort** | Insere cada novo número na posição correta da parte do vetor que já está ordenada. | `O(n²)` |
| **Selection Sort** | Procura o menor valor da parte não ordenada e o coloca na próxima posição. | `O(n²)` |
| **Merge Sort** | Divide o vetor em partes menores e depois intercala essas partes em ordem. | `O(n log n)` |
| **Quick Sort** | Escolhe um pivô, separa os valores menores e maiores e ordena recursivamente cada lado. | `O(n log n)` |

> **Comparação:** Bubble, Insertion e Selection costumam exigir mais operações em conjuntos grandes. Merge e Quick tendem a ser mais eficientes nesses casos. O Quick Sort, porém, pode atingir `O(n²)` no pior caso. Os tempos medidos variam conforme os dados e o computador utilizado.

## 📁 Arquivos gerados

```text
OrdenaC/
├── main.c                 # Codigo-fonte do programa
├── data/
│   └── dados.txt          # Numeros originais
├── output/
│   └── ordenado.txt       # Resultado da ultima ordenacao
└── logs/
    └── benchmark.csv      # Historico das comparacoes
```

Os números originais são preservados durante a ordenação. Ao **alterar um valor**, é necessário executar novamente um algoritmo para atualizar `output/ordenado.txt`.

## 💻 Execução

**Requisitos:** Windows e compilador GCC (por exemplo, MinGW-w64). O benchmark utiliza `QueryPerformanceCounter`, da API do Windows.

No terminal **PowerShell**, dentro da pasta do projeto, crie as pastas necessárias, compile e execute:

```powershell
New-Item -ItemType Directory -Force -Path data, output, logs | Out-Null
gcc main.c -o ordenac.exe
.\ordenac.exe
```

## 👨‍💻 Autor

Desenvolvido como projeto acadêmico de estudo de **algoritmos, vetores, arquivos e linguagem C**.

**[Diego Troiani](https://github.com/ditroiani)** · [Repositório OrdenaC](https://github.com/ditroiani/ordena-c)

---

<div align="center">
  <sub>OrdenaC • Aprendendo algoritmos na prática</sub>
</div>
