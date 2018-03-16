/*01 - Photopobre;
// Aluno: Lucas Hiroshi Horinouchi
// Matricula: 160034591
// Sintese
//  Objetivo: Aplicar filtros ou operações sobre uma imagem 
//  Entrada : Imagem e parametros
//  Saida   : Imagem
*/

#include <stdio.h>

typedef struct _pixel 
{
    unsigned short int red;
    unsigned short int green;
    unsigned short int blue;
}Pixel;

typedef struct _image 
{
    // [largura] [altura][rgb]
    // 0 -> red
    // 1 -> green
    // 2 -> blue
    unsigned short int pixel[512][512][3];
    unsigned int largura;
    unsigned int altura;
}Image;

int max(int a, int blue);
int pixel_igual(Pixel p1, Pixel p2);

void imprime_imagem(Image img);
Image leia_imagem();

Image escala_de_cinza(Image img);
Image rotacionar90direita(Image img);
Image cortar_imagem(Image img);
Image filtro_sepia(Image img);
Image inverter_cores(Image img); 
Image blur(Image img);
Image espelhamento(Image img);


int main() 
{
    // Declarações    
    Image img;
    int n_opcoes;
    int aux;
    int opcao;

    // Instruções    
    img = leia_imagem();
    scanf("%d", &n_opcoes);

    for(int aux = 0; aux < n_opcoes; ++aux) 
    {
        scanf("%d", &opcao);
        switch(opcao) 
        {
            case 1: 
            { // Escala de Cinza
                img = escala_de_cinza(img);
                break;
            }
            case 2: 
            { // Filtro Sepia
                img = filtro_sepia(img);
                break;
            }
            case 3:
            { // Blur
                img = blur(img);
                break;
            }
            case 4: 
            { // Rotacao
                img = rotacionar90direita(img);
                break;
            }
            case 5: 
            { // Espelhamento
                img = espelhamento(img); 
                break;
            }
            case 6: 
            { // Inversao de Cores
                img = inverter_cores(img);
                break;
            }
            case 7: 
            { // Cortar Imagem
                img = cortar_imagem(img);
                break;
            }
        }
    }
    imprime_imagem(img);
    return 0;
}

// ============================= SUBPROGRAMAS =============================

int max(int a, int b) 
{
    if (a > b)
        return a;
    return b;
}

int pixel_igual(Pixel p1, Pixel p2) 
{
    if (p1.red == p2.red &&
        p1.green == p2.green &&
        p1.blue == p2.blue)
        return 1;
    return 0;
}


// -------------------------------- Ler e Imprimir --------------------------------

//Objetivo: Ler uma imagem
//Parametros: Imagem
//Retorno: Imagem
Image leia_imagem()
{
    Image img;
    unsigned int j;
    unsigned int i;
    char p3[4];
    int max_color;

    // lê o tipo da imagem
    scanf("%s", p3);

    // lê a altura e largura e a cor da imagem
    scanf("%u %u %d", &img.largura, &img.altura, &max_color);

    // lê todos os pixels da imagem
    for (i = 0; i < img.altura; ++i) {
        for (j = 0; j < img.largura; ++j) {
            scanf("%hu %hu %hu", &img.pixel[i][j][0],
                                &img.pixel[i][j][1],
                                &img.pixel[i][j][2]);

        }
    }
    return img;
}

//Objetivo: Imprimir uma imagem
//Parametros: Imagem
//Retorno: Sem retorno
void imprime_imagem(Image img)
{
    unsigned int aux_1, aux_2;

    // imprime o tipo da imagem
    printf("P3\n");
    // imprime largura altura e a cor da imagem 
    printf("%u %u\n255\n", img.largura, img.altura);

    // imprime os pixels da imagem
    for (aux_1 = 0; aux_1 < img.altura; ++aux_1) 
    {
        for (aux_2 = 0; aux_2 < img.largura; ++aux_2) 
        {
            printf("%hu %hu %hu ", img.pixel[aux_1][aux_2][0],
                                   img.pixel[aux_1][aux_2][1],
                                   img.pixel[aux_1][aux_2][2]);

        }
        printf("\n");
    }
}

// -------------------------------- Operações --------------------------------

//Objetivo: Aplicar uma escala de cinza em uma imagem
//Parametros: Imagem
//Retorno: Imagem
Image escala_de_cinza(Image img) 
{
    /*for (unsigned int i = 0; i < img.altura; ++i) {
        for (unsigned int j = 0; j < img.largura; ++j) {
            print("%u", img.pixel[i][j][0] + img.pixel[i][j][1] + img.pixel[i][j][2]);
        }
    }*/
    unsigned int aux_1, aux_2;

    for (unsigned int aux_1 = 0; aux_1 < img.altura; ++aux_1) 
    {
        for (unsigned int aux_2 = 0; aux_2 < img.largura; ++aux_2) 
        {
            int media = img.pixel[aux_1][aux_2][0] +
                        img.pixel[aux_1][aux_2][1] +
                        img.pixel[aux_1][aux_2][2];
            media /= 3;
            img.pixel[aux_1][aux_2][0] = media;
            img.pixel[aux_1][aux_2][1] = media;
            img.pixel[aux_1][aux_2][2] = media;
        }
    }

    return img;
}

//Objetivo: Aplicar o Blur em uma imagem
//Parametros: Imagem
//Retorno: Imagem
Image blur(Image img) 
{   
    int tamanho;
    unsigned int altura = img.altura;
    unsigned short int pixel[512][512][3] = img.pixel; 
    unsigned int largura = img.largura;
    
    scanf("%d", &tamanho);
    for (unsigned int i = 0; i < altura; ++i) {
        for (unsigned int j = 0; j < largura; ++j) {
            Pixel media = {0, 0, 0};

            int menor_h = (altura - 1 > i + tamanho/2) ? i + tamanho/2 : altura - 1;
            int min_w = (largura - 1 > j + tamanho/2) ? j + tamanho/2 : largura - 1;
            for(int x = (0 > i - tamanho/2 ? 0 : i - tamanho/2); x <= menor_h; ++x) {
                for(int y = (0 > j - tamanho/2 ? 0 : j - tamanho/2); y <= min_w; ++y) {
                    media.red += pixel[x][y][0];
                    media.green += pixel[x][y][1];
                    media.blue += pixel[x][y][2];
                }
            }

            // printf("%u", media.red)
            media.red /= tamanho * tamanho;
            media.green /= tamanho * tamanho;
            media.blue /= tamanho * tamanho;

            pixel[i][j][0] = media.red;
            pixel[i][j][1] = media.green;
            pixel[i][j][2] = media.blue;
        }
    }
    return img;
}

//Objetivo: Rotacionar uma imagem
//Parametros: Imagem
//Retorno: Imagem
Image rotacionar90direita(Image img) 
{
    int quantas_vezes;
    int quantas_vezes_contador;
    unsigned int i, j, x, y;
    
    Image rotacionada;
    scanf("%d", &quantas_vezes);
    quantas_vezes %= 4;
                
    rotacionada.largura = img.altura;
    rotacionada.altura = img.largura;
    for (quantas_vezes_contador = 0; quantas_vezes_contador < quantas_vezes; ++quantas_vezes_contador) 
    {        
        for (i = 0, y = 0; i < rotacionada.altura; ++i, ++y) 
        {
            for (j = rotacionada.largura - 1, x = 0; j >= 0; --j, ++x) 
            {
                rotacionada.pixel[i][j][0] = img.pixel[x][y][0];
                rotacionada.pixel[i][j][1] = img.pixel[x][y][1];
                rotacionada.pixel[i][j][2] = img.pixel[x][y][2];
            }
        }
    }
    return rotacionada;
}

//Objetivo: Inverter as cores de uma imagem
//Parametros: Imagem
//Retorno: Imagem
Image inverter_cores(Image img) 
{
    unsigned short int pixel[512][512][3] = img.pixel;
    unsigned int largura = img.largura;
    unsigned int altura = img.altura;
    unsigned int aux_1, aux_2;
    
    for(aux_1 = 0; aux_1 < altura; ++aux_1) 
    {
        for (aux_2 = 0; aux_2 < largura; ++aux_2) {
            pixel[aux_1][aux_2][0] = 255 - pixel[aux_1][aux_2][0];
            pixel[aux_1][aux_2][1] = 255 - pixel[aux_1][aux_2][1];
            pixel[aux_1][aux_2][2] = 255 - pixel[aux_1][aux_2][2];
        }
    }
    return img;
}

//Objetivo: Cortar uma imagem
//Parametros: Imagem
//Retorno: Imagem
Image cortar_imagem(Image img) 
{
    Image cortada;
    int largura_reduzida, altura_reduzida;
    int largura, altura;
    int aux_1, aux_2;

    scanf("%d %d", &largura_reduzida, &altura_reduzida);
    scanf("%d %d", &largura, &altura);

    cortada.largura = largura;
    cortada.altura = altura;

    for(aux_1 = 0; aux_1 < altura; ++aux_1) {
        for(aux_2 = 0; aux_2 < largura; ++aux_2) {
            cortada.pixel[aux_1][aux_2][0] = img.pixel[aux_1 + altura_reduzida][aux_2 + largura_reduzida][0];
            cortada.pixel[aux_1][aux_2][1] = img.pixel[aux_1 + altura_reduzida][aux_2 + largura_reduzida][1];
            cortada.pixel[aux_1][aux_2][2] = img.pixel[aux_1 + altura_reduzida][aux_2 + largura_reduzida][2];
        }
    }

    return cortada;
}

//Objetivo: Aplicar um filtro sepia em uma imagem
//Parametros: Imagem
//Retorno: Imagem
Image filtro_sepia(Image img)
{
    unsigned int aux_1;
    unsigned int aux_2;

    for (aux_1 = 0; aux_1 < img.altura; ++aux_1)
    {
        for (aux_2 = 0; aux_2 < img.largura; ++aux_2) 
        {
            unsigned short int pixel[3];
            pixel[0] = img.pixel[aux_1][aux_2][0];
            pixel[1] = img.pixel[aux_1][aux_2][1];
            pixel[2] = img.pixel[aux_1][aux_2][2];

            int p =  pixel[0] * .393 + pixel[1] * .769 + pixel[2] * .189;
            int menor_r = (255 >  p) ? p : 255;
            img.pixel[aux_1][aux_2][0] = menor_r;

            p =  pixel[0] * .349 + pixel[1] * .686 + pixel[2] * .168;
            menor_r = (255 >  p) ? p : 255;
            img.pixel[aux_1][aux_2][1] = menor_r;

            p =  pixel[0] * .272 + pixel[1] * .534 + pixel[2] * .131;
            menor_r = (255 >  p) ? p : 255;
            img.pixel[aux_1][aux_2][2] = menor_r;
        }
    }
    return img;
}

//Objetivo: Espelhar uma imagem
//Parametros: Imagem
//Retorno: Imagem
Image espelhamento(Image img)
{
    int horizontal = 0;
    scanf("%d", &horizontal);

    int largura = img.largura, altura = img.altura;

    if (horizontal == 1) largura /= 2;

    else altura /= 2;
    {
        for (int i2 = 0; i2 < altura; ++i2) 
        {
            for (int j = 0; j < largura; ++j) 
            {
                int x = i2, y = j;

                if (horizontal == 1) y = img.largura - 1 - j;
                else x = img.altura - 1 - i2;

                Pixel aux1;
                aux1.red = img.pixel[i2][j][0];
                aux1.green = img.pixel[i2][j][1];
                aux1.blue = img.pixel[i2][j][2];

                img.pixel[i2][j][0] = img.pixel[x][y][0];
                img.pixel[i2][j][1] = img.pixel[x][y][1];
                img.pixel[i2][j][2] = img.pixel[x][y][2];

                img.pixel[x][y][0] = aux1.red;
                img.pixel[x][y][1] = aux1.green;
                img.pixel[x][y][2] = aux1.blue;
            }
        }
    }
    return img;
}
