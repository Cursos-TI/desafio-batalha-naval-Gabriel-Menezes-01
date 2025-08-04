#include <stdio.h>
#include <stdbool.h>

/*
 * BATALHA NAVAL - NÍVEL INTERMEDIÁRIO
 *
 * Este programa implementa um tabuleiro de Batalha Naval 10x10 com:
 * - 4 navios de tamanho 3 cada
 * - 2 navios posicionados horizontalmente/verticalmente
 * - 2 navios posicionados na diagonal
 * - Representação visual do tabuleiro
 * - Validação de posicionamento dos navios
 *
 * Representação no tabuleiro:
 * 0 = Água
 * 3 = Parte do navio
 */

// Constantes do jogo
#define TAMANHO_TABULEIRO 10 // Tabuleiro fixo 10x10
#define TAMANHO_NAVIO 3      // Navios de tamanho fixo 3
#define AGUA 0               // Valor para representar água
#define NAVIO 3              // Valor para representar parte do navio

// Função para inicializar o tabuleiro com água (valor 0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO])
{
    printf("Inicializando tabuleiro 10x10...\n");

    // Loop aninhado para percorrer todas as posições da matriz
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++)
    {
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++)
        {
            tabuleiro[linha][coluna] = AGUA; // Inicializa com água (valor 0)
        }
    }

    printf("Tabuleiro inicializado com sucesso!\n");
}

// Função para verificar se as coordenadas estão dentro dos limites do tabuleiro
bool coordenadasValidas(int linha, int coluna, int orientacao)
{
    // Verifica limites básicos da posição inicial
    if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO)
    {
        return false;
    }

    // Verifica se o navio cabe no tabuleiro considerando sua orientação
    if (orientacao == 0)
    { // Horizontal - verifica se cabe na horizontal
        return (coluna + TAMANHO_NAVIO - 1) < TAMANHO_TABULEIRO;
    }
    else if (orientacao == 1)
    { // Vertical - verifica se cabe na vertical
        return (linha + TAMANHO_NAVIO - 1) < TAMANHO_TABULEIRO;
    }
    else if (orientacao == 2)
    { // Diagonal descendente (\) - verifica se cabe na diagonal
        return (linha + TAMANHO_NAVIO - 1) < TAMANHO_TABULEIRO && 
               (coluna + TAMANHO_NAVIO - 1) < TAMANHO_TABULEIRO;
    }
    else if (orientacao == 3)
    { // Diagonal ascendente (/) - verifica se cabe na diagonal
        return (linha + TAMANHO_NAVIO - 1) < TAMANHO_TABULEIRO && 
               (coluna - TAMANHO_NAVIO + 1) >= 0;
    }
    
    return false; // Orientação inválida
}

// Função para verificar se há sobreposição com navios já posicionados
bool verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                           int linha, int coluna, int orientacao)
{

    // Verifica cada posição que o navio ocupará
    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        int linha_verificar, coluna_verificar;

        if (orientacao == 0)
        { // Horizontal
            linha_verificar = linha;
            coluna_verificar = coluna + i;
        }
        else if (orientacao == 1)
        { // Vertical
            linha_verificar = linha + i;
            coluna_verificar = coluna;
        }
        else if (orientacao == 2)
        { // Diagonal descendente (\)
            linha_verificar = linha + i;
            coluna_verificar = coluna + i;
        }
        else if (orientacao == 3)
        { // Diagonal ascendente (/)
            linha_verificar = linha + i;
            coluna_verificar = coluna - i;
        }
        else
        {
            return true; // Orientação inválida = considera sobreposição
        }

        // Se já há um navio nesta posição, há sobreposição
        if (tabuleiro[linha_verificar][coluna_verificar] == NAVIO)
        {
            return true; // Sobreposição detectada
        }
    }

    return false; // Sem sobreposição
}

// Função para posicionar um navio no tabuleiro
bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int navio[TAMANHO_NAVIO], int linha_inicial, int coluna_inicial,
                     int orientacao, int numero_navio)
{

    printf("Tentando posicionar navio %d na posição (%d, %d) - ",
           numero_navio, linha_inicial, coluna_inicial);

    if (orientacao == 0)
    {
        printf("Orientação: Horizontal\n");
    }
    else if (orientacao == 1)
    {
        printf("Orientação: Vertical\n");
    }
    else if (orientacao == 2)
    {
        printf("Orientação: Diagonal descendente (\\)\n");
    }
    else if (orientacao == 3)
    {
        printf("Orientação: Diagonal ascendente (/)\n");
    }

    // Validar coordenadas
    if (!coordenadasValidas(linha_inicial, coluna_inicial, orientacao))
    {
        printf("ERRO: Coordenadas inválidas ou navio não cabe no tabuleiro!\n");
        return false;
    }

    // Verificar sobreposição
    if (verificarSobreposicao(tabuleiro, linha_inicial, coluna_inicial, orientacao))
    {
        printf("ERRO: Há sobreposição com outro navio!\n");
        return false;
    }

    // Inicializar o vetor do navio com o valor 3
    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        navio[i] = NAVIO;
    }

    // Posicionar o navio no tabuleiro copiando os valores do vetor
    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        if (orientacao == 0)
        { // Horizontal
            tabuleiro[linha_inicial][coluna_inicial + i] = navio[i];
        }
        else if (orientacao == 1)
        { // Vertical
            tabuleiro[linha_inicial + i][coluna_inicial] = navio[i];
        }
        else if (orientacao == 2)
        { // Diagonal descendente (\)
            tabuleiro[linha_inicial + i][coluna_inicial + i] = navio[i];
        }
        else if (orientacao == 3)
        { // Diagonal ascendente (/)
            tabuleiro[linha_inicial + i][coluna_inicial - i] = navio[i];
        }
    }

    printf("Navio %d posicionado com sucesso!\n", numero_navio);
    return true;
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO])
{
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n");

    // Cabeçalho com números das colunas para facilitar visualização
    printf("   ");
    for (int col = 0; col < TAMANHO_TABULEIRO; col++)
    {
        printf("%2d ", col);
    }
    printf("\n");

    // Linha separadora para organização visual
    printf("   ");
    for (int col = 0; col < TAMANHO_TABULEIRO; col++)
    {
        printf("---");
    }
    printf("\n");

    // Exibir cada linha do tabuleiro com loops aninhados
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++)
    {
        printf("%2d|", linha); // Número da linha para referência

        // Loop interno para exibir cada coluna da linha atual
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++)
        {
            printf("%2d ", tabuleiro[linha][coluna]); // Espaço separador entre elementos
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = Água, 3 = Navio\n");
}

// Função para exibir estatísticas do tabuleiro
void exibirEstatisticas(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO])
{
    int posicoes_agua = 0;  // Contador de posições com água
    int posicoes_navio = 0; // Contador de posições com navios

    // Contar posições de água e navio usando loops aninhados
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++)
    {
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++)
        {
            if (tabuleiro[linha][coluna] == AGUA)
            {
                posicoes_agua++;
            }
            else if (tabuleiro[linha][coluna] == NAVIO)
            {
                posicoes_navio++;
            }
        }
    }

    printf("\n=== ESTATÍSTICAS ===\n");
    printf("Total de posições: %d\n", TAMANHO_TABULEIRO * TAMANHO_TABULEIRO);
    printf("Posições com água: %d\n", posicoes_agua);
    printf("Posições com navios: %d\n", posicoes_navio);
    printf("Navios posicionados: %d\n", posicoes_navio / TAMANHO_NAVIO);
}

// Função principal
int main()
{
    // Declaração da matriz do tabuleiro 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Declaração dos vetores para representar os quatro navios
    int navio1[TAMANHO_NAVIO]; // Primeiro navio (horizontal)
    int navio2[TAMANHO_NAVIO]; // Segundo navio (vertical)
    int navio3[TAMANHO_NAVIO]; // Terceiro navio (diagonal descendente)
    int navio4[TAMANHO_NAVIO]; // Quarto navio (diagonal ascendente)

    printf("=== PROGRAMA BATALHA NAVAL - NÍVEL INTERMEDIÁRIO ===\n\n");

    // Passo 1: Inicializar o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Passo 2: Definir coordenadas dos quatro navios (definidas diretamente no código)
    
    // Coordenadas do primeiro navio (horizontal)
    int linha1 = 1;      // Linha inicial do navio 1
    int coluna1 = 2;     // Coluna inicial do navio 1
    int orientacao1 = 0; // 0 = Horizontal

    // Coordenadas do segundo navio (vertical)
    int linha2 = 4;      // Linha inicial do navio 2
    int coluna2 = 7;     // Coluna inicial do navio 2
    int orientacao2 = 1; // 1 = Vertical

    // Coordenadas do terceiro navio (diagonal descendente \)
    int linha3 = 0;      // Linha inicial do navio 3
    int coluna3 = 0;     // Coluna inicial do navio 3
    int orientacao3 = 2; // 2 = Diagonal descendente

    // Coordenadas do quarto navio (diagonal ascendente /)
    int linha4 = 6;      // Linha inicial do navio 4
    int coluna4 = 9;     // Coluna inicial do navio 4
    int orientacao4 = 3; // 3 = Diagonal ascendente

    printf("\nCoordenadas definidas para os 4 navios:\n");
    printf("Navio 1: Posição (%d, %d) - Horizontal\n", linha1, coluna1);
    printf("Navio 2: Posição (%d, %d) - Vertical\n", linha2, coluna2);
    printf("Navio 3: Posição (%d, %d) - Diagonal descendente (\\)\n", linha3, coluna3);
    printf("Navio 4: Posição (%d, %d) - Diagonal ascendente (/)\n\n", linha4, coluna4);

    // Passo 3: Posicionar os quatro navios no tabuleiro
    bool navio1_posicionado = posicionarNavio(tabuleiro, navio1, linha1, coluna1,
                                              orientacao1, 1);

    bool navio2_posicionado = posicionarNavio(tabuleiro, navio2, linha2, coluna2,
                                              orientacao2, 2);

    bool navio3_posicionado = posicionarNavio(tabuleiro, navio3, linha3, coluna3,
                                              orientacao3, 3);

    bool navio4_posicionado = posicionarNavio(tabuleiro, navio4, linha4, coluna4,
                                              orientacao4, 4);

    // Verificar se todos os navios foram posicionados com sucesso
    if (navio1_posicionado && navio2_posicionado && navio3_posicionado && navio4_posicionado)
    {
        printf("\nTodos os 4 navios foram posicionados com sucesso!\n");
    }
    else
    {
        printf("\nERRO: Nem todos os navios puderam ser posicionados!\n");
        printf("Status dos navios:\n");
        printf("Navio 1 (Horizontal): %s\n", navio1_posicionado ? "✓ Sucesso" : "✗ Falhou");
        printf("Navio 2 (Vertical): %s\n", navio2_posicionado ? "✓ Sucesso" : "✗ Falhou");
        printf("Navio 3 (Diagonal \\): %s\n", navio3_posicionado ? "✓ Sucesso" : "✗ Falhou");
        printf("Navio 4 (Diagonal /): %s\n", navio4_posicionado ? "✓ Sucesso" : "✗ Falhou");
        return 1; // Encerrar programa com código de erro
    }

    // Passo 4: Exibir o tabuleiro completo
    exibirTabuleiro(tabuleiro);

    // Passo 5: Exibir estatísticas do jogo
    exibirEstatisticas(tabuleiro);

    printf("\nPrograma executado com sucesso!\n");
    printf("Total de navios posicionados: 4\n");
    printf("Orientações utilizadas: Horizontal, Vertical, Diagonal descendente, Diagonal ascendente\n");
    return 0; // Retorno de sucesso
}
