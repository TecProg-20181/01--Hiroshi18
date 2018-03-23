#include <stdio.h>

typedef struct _pixel {
    unsigned short int red;
    unsigned short int green;
    unsigned short int blue;
} Pixel;

typedef struct _image 
{
    Pixel pixel[512][512];
    unsigned int largura;
    unsigned int altura;
} Image;

int maior(int a, int b);
int menor(int a, int b);

Pixel media_pixel(Pixel pixel, int div);
Pixel soma_pixel(Pixel pixel);

Image leia_imagem();
Image imprime_imagem(Image img);

Image filtro_sepia(Image img);
Image escala_de_cinza(Image img);
Image blur(Image img);
Image rotacionar90direita(Image img);
Image inverter_cores(Image img);
Image cortar_imagem(Image img);
Image espelhamento(Image img);

int main() {
    Image img;
    img = leia_imagem();

    int n_opcoes;
    scanf("%d", &n_opcoes);

    for(int i = 0; i < n_opcoes; ++i) 
    {
        int opcao;
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


//----------------------------------------------------Imagens-----------------------------------------------------------------
Image leia_imagem()
{
    Image img;
    unsigned int j, i;
    char p3[4];
    int max_color;

    // lê o tipo da imagem
    scanf("%s", p3);

    // lê a altura e largura e a cor da imagem
    scanf("%u %u %d", &img.largura, &img.altura, &max_color);

    // lê todos os pixels da imagem
    for (i = 0; i < img.altura; ++i) {
        for (j = 0; j < img.largura; ++j) 
        {
            scanf("%hu %hu %hu", &img.pixel[i][j].red,
                                 &img.pixel[i][j].green,
                                 &img.pixel[i][j].blue);
        }
    }
    return img;
}

Image imprime_imagem(Image img)
{

    // imprime o tipo da imagem
    printf("P3\n");
    // imprime largura altura e a cor da imagem 
    printf("%u %u\n255\n", img.largura, img.altura);

    // imprime os pixels da imagem
    for (unsigned int i = 0; i < img.altura; ++i) 
    {
        for (unsigned int j = 0; j < img.largura; ++j) 
        {
            printf("%hu %hu %hu ", img.pixel[i][j].red,
                                   img.pixel[i][j].green,
                                   img.pixel[i][j].blue);

        }
        printf("\n");
    }
    return img;
}

//-------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------Operacoes------------------------------------------------------------

int menor(int a, int b) 
{
    if (a > b)
        return (b);
    return (a);
}

int maior(int a, int b) 
{
    if (a > b)
        return (a);
    return (b);
}

Pixel soma_pixel(Pixel pixel) 
{
    unsigned int soma;
    
    soma = pixel.red + pixel.green + pixel.blue;
    
    pixel.red = soma;
    pixel.green = soma;
    pixel.blue = soma;

    return pixel;
}

Pixel media_pixel(Pixel pixel, int div) 
{
    pixel.red /= div;
    pixel.green /= div;
    pixel.blue /= div;

    return pixel;
}

//-------------------------------------------------------------------------------------------------------------------------

Image espelhamento(Image img)
{
    int horizontal = 0;
    scanf("%d", &horizontal);

    int largura = img.largura, altura = img.altura;

    if (horizontal == 1) 
        largura /= 2;
    else 
        altura /= 2;

    for (int i2 = 0; i2 < altura; ++i2) 
    {
        for (int j = 0; j < largura; ++j) 
        {
            int x = i2, y = j;

            if (horizontal == 1) 
                y = img.largura - 1 - j;
            else 
                x = img.altura - 1 - i2;

            Pixel pixel_espelhado;
            pixel_espelhado = img.pixel[i2][j];

            img.pixel[i2][j] = img.pixel[x][y];
            img.pixel[x][y] = pixel_espelhado;
        }
    }
    return img;
}

Image escala_de_cinza(Image img) 
{
    for (unsigned int i = 0; i < img.altura; ++i) 
    {
        for (unsigned int j = 0; j < img.largura; ++j) 
        {
            img.pixel[i][j] = soma_pixel(img.pixel[i][j]);
            img.pixel[i][j] = media_pixel(img.pixel[i][j], 3);
        }
    }
    return img;
}

Image filtro_sepia(Image img) 
{
    unsigned int i, j;
    Pixel pixel;
    int menor_r, aux;

    for (i = 0; i < img.altura; ++i)
    {
        for (j = 0; j < img.largura; ++j) 
        {
            pixel= img.pixel[i][j];

            aux =  pixel.red * .393 + pixel.green * .769 + pixel.blue * .189;
            menor_r = menor(255,  aux);

            img.pixel[i][j].red = menor_r;

            aux =  pixel.red * .349 + pixel.green * .686 + pixel.blue * .168;
            menor_r = menor(255,  aux);

            img.pixel[i][j].green = menor_r;

            aux =  pixel.red * .272 + pixel.green * .534 + pixel.blue * .131;
            menor_r = menor(255,  aux);

            img.pixel[i][j].blue = menor_r;
        }
    }
    return img;
}

Image blur(Image img) 
{
    int tamanho = 0;
    scanf("%d", &tamanho);
                
    for (unsigned int i = 0; i < img.altura; ++i) 
    {
        for (unsigned int j = 0; j < img.largura; ++j) 
        {
            Pixel soma = {0, 0, 0};
            
            int menor_altura = menor(img.altura - 1, i + tamanho/2);
            int menor_largura = menor(img.largura - 1, j + tamanho/2);

            for(int x = (maior(0, i - tamanho/2)); x <= menor_altura; ++x) 
            {
                for(int y = (maior(0, j - tamanho/2)); y <= menor_largura; ++y) 
                {
                    soma.red += img.pixel[x][y].red;
                    soma.green += img.pixel[x][y].green;
                    soma.blue += img.pixel[x][y].blue;
                }
            }

            Pixel media; 
            media = media_pixel(soma, tamanho*tamanho);

            img.pixel[i][j] = media;
        }
    }
    return img;
}

Image rotacionar90direita(Image img) 
{
    int quantas_vezes;
    int quantas_vezes_contador;
    Image rotacionada;

    scanf("%d", &quantas_vezes);
    quantas_vezes %= 4;

    rotacionada.largura = img.altura;
    rotacionada.altura = img.largura;
    for(unsigned int k; k<quantas_vezes;k++)
    {
        for (unsigned int i = 0, y = 0; i < rotacionada.altura; ++i, ++y) 
        {
            for (int j = rotacionada.largura - 1, x = 0; j >= 0; --j, ++x) 
            {
                rotacionada.pixel[i][j] = img.pixel[x][y];
            }
        }
    }
    return rotacionada;
}

Image inverter_cores(Image img)
{
    for (unsigned int i = 0; i < img.altura; ++i) 
    {
        for (unsigned int j = 0; j < img.largura; ++j) 
        {
            img.pixel[i][j].red = 255 - img.pixel[i][j].red;
            img.pixel[i][j].green = 255 - img.pixel[i][j].green;
            img.pixel[i][j].blue = 255 - img.pixel[i][j].blue;
        }
    }
    return img;
}

Image cortar_imagem(Image img) 
{
    Image cortada;
    
    int x, y;
    scanf("%d %d", &x, &y);

    int largura, altura;
    scanf("%d %d", &largura, &altura);

    cortada.largura = largura;
    cortada.altura = altura;

    for(int i = 0; i < altura; ++i) {
        for(int j = 0; j < largura; ++j) {
            cortada.pixel[i][j].red = img.pixel[i + y][j + x].red;
            cortada.pixel[i][j].green = img.pixel[i + y][j + x].green;
            cortada.pixel[i][j].blue = img.pixel[i + y][j + x].blue;
        }
    }
    return cortada;
}
