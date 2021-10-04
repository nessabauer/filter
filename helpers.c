#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Fazendo a média da nova cor em preto e branco
            float average = (image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0;
            int newColor = round(average);

            image[h][w].rgbtRed   = newColor;
            image[h][w].rgbtGreen = newColor;
            image[h][w].rgbtBlue  = newColor;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            int wi = width - (w + 1);

            //Salvando em uma temporaria
            int newPositionRed   =  image[h][w].rgbtRed;
            int newPositionGreen =  image[h][w].rgbtGreen;
            int newPositionBlue  =  image[h][w].rgbtBlue;

            //Trocando a primeira pela ultima posição
            image[h][w] = image[h][wi];

            //Trocando a última pela primeira posição
            image[h][wi].rgbtRed   = newPositionRed;
            image[h][wi].rgbtGreen = newPositionGreen;
            image[h][wi].rgbtBlue  = newPositionBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    //salvando um bkp para buscar as 9 posições semrpe originais, já que a variavel image estará mudando a cada loop
    RGBTRIPLE temp[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            temp[h][w] = image[h][w];
        }
    }

    //Loop para somar as 9 posições
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float somaRed = 0, somaGreen = 0, somaBlue = 0;
            int pixels = 0;

            if (h > 0)
            {
                if (w > 0)
                {
                    somaRed   += temp[h - 1][w - 1].rgbtRed;
                    somaGreen += temp[h - 1][w - 1].rgbtGreen;
                    somaBlue  += temp[h - 1][w - 1].rgbtBlue;
                    pixels ++;
                }

                somaRed   += temp[h - 1][w].rgbtRed;
                somaGreen += temp[h - 1][w].rgbtGreen;
                somaBlue  += temp[h - 1][w].rgbtBlue;
                pixels ++;

                if (w < width - 1)
                {
                    somaRed   += temp[h - 1][w + 1].rgbtRed;
                    somaGreen += temp[h - 1][w + 1].rgbtGreen;
                    somaBlue  += temp[h - 1][w + 1].rgbtBlue;
                    pixels ++;
                }
            }

            if (w > 0)
            {
                somaRed   += temp[h][w - 1].rgbtRed;
                somaGreen += temp[h][w - 1].rgbtGreen;
                somaBlue  += temp[h][w - 1].rgbtBlue;
                pixels ++;
            }

            somaRed   += temp[h][w].rgbtRed;
            somaGreen += temp[h][w].rgbtGreen;
            somaBlue  += temp[h][w].rgbtBlue;
            pixels ++;

            if (w < width - 1)
            {
                somaRed   += temp[h][w + 1].rgbtRed;
                somaGreen += temp[h][w + 1].rgbtGreen;
                somaBlue  += temp[h][w + 1].rgbtBlue;
                pixels ++;
            }

            if (h < height - 1)
            {
                if (w > 0)
                {
                    somaRed   += temp[h + 1][w - 1].rgbtRed;
                    somaGreen += temp[h + 1][w - 1].rgbtGreen;
                    somaBlue  += temp[h + 1][w - 1].rgbtBlue;
                    pixels ++;
                }

                somaRed   += temp[h + 1][w].rgbtRed;
                somaGreen += temp[h + 1][w].rgbtGreen;
                somaBlue  += temp[h + 1][w].rgbtBlue;
                pixels ++;

                if (w < width - 1)
                {
                    somaRed   += temp[h + 1][w + 1].rgbtRed;
                    somaGreen += temp[h + 1][w + 1].rgbtGreen;
                    somaBlue  += temp[h + 1][w + 1].rgbtBlue;
                    pixels ++;
                }
            }

            //Fazendo o calculo para um inteiro
            int newColorRed = round(somaRed / pixels);
            int newColorGreen = round(somaGreen / pixels);
            int newColorBlue = round(somaBlue / pixels);

            //Atualizando a variavel image!
            image[h][w].rgbtRed   = newColorRed;
            image[h][w].rgbtGreen = newColorGreen;
            image[h][w].rgbtBlue  = newColorBlue;

        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    //salvando um bkp para buscar as 9 posições semrpe originais, já que a variavel image estará mudando a cada loop
    RGBTRIPLE temp[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            temp[h][w] = image[h][w];
        }
    }

    //Loop para somar as 9 posições
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float somaRedx = 0, somaGreenx = 0, somaBluex = 0, somaRedy = 0, somaGreeny = 0, somaBluey = 0;

            if (h > 0)
            {
                if (w > 0)
                {
                    somaRedx   += temp[h - 1][w - 1].rgbtRed * -1;
                    somaGreenx += temp[h - 1][w - 1].rgbtGreen * -1;
                    somaBluex  += temp[h - 1][w - 1].rgbtBlue * -1;

                    somaRedy   += temp[h - 1][w - 1].rgbtRed * -1;
                    somaGreeny += temp[h - 1][w - 1].rgbtGreen * -1;
                    somaBluey  += temp[h - 1][w - 1].rgbtBlue * -1;
                }

                somaRedx   += temp[h - 1][w].rgbtRed * 0;
                somaGreenx += temp[h - 1][w].rgbtGreen * 0;
                somaBluex  += temp[h - 1][w].rgbtBlue * 0;

                somaRedy   += temp[h - 1][w].rgbtRed * -2;
                somaGreeny += temp[h - 1][w].rgbtGreen * -2;
                somaBluey  += temp[h - 1][w].rgbtBlue * -2;

                if (w < width - 1)
                {
                    somaRedx   += temp[h - 1][w + 1].rgbtRed * 1;
                    somaGreenx += temp[h - 1][w + 1].rgbtGreen * 1;
                    somaBluex  += temp[h - 1][w + 1].rgbtBlue * 1;

                    somaRedy   += temp[h - 1][w + 1].rgbtRed * -1;
                    somaGreeny += temp[h - 1][w + 1].rgbtGreen * -1;
                    somaBluey  += temp[h - 1][w + 1].rgbtBlue * -1;
                }
            }

            if (w > 0)
            {
                somaRedx   += temp[h][w - 1].rgbtRed * -2;
                somaGreenx += temp[h][w - 1].rgbtGreen * -2;
                somaBluex  += temp[h][w - 1].rgbtBlue * -2;

                somaRedy   += temp[h][w - 1].rgbtRed * 0;
                somaGreeny += temp[h][w - 1].rgbtGreen * 0;
                somaBluey  += temp[h][w - 1].rgbtBlue * 0;
            }

            somaRedx   += temp[h][w].rgbtRed * 0;
            somaGreenx += temp[h][w].rgbtGreen * 0;
            somaBluex  += temp[h][w].rgbtBlue * 0;

            somaRedy   += temp[h][w].rgbtRed * 0;
            somaGreeny += temp[h][w].rgbtGreen * 0;
            somaBluey  += temp[h][w].rgbtBlue * 0;

            if (w < width - 1)
            {
                somaRedx   += temp[h][w + 1].rgbtRed * 2;
                somaGreenx += temp[h][w + 1].rgbtGreen * 2;
                somaBluex  += temp[h][w + 1].rgbtBlue * 2;

                somaRedy   += temp[h][w + 1].rgbtRed * 0;
                somaGreeny += temp[h][w + 1].rgbtGreen * 0;
                somaBluey  += temp[h][w + 1].rgbtBlue * 0;
            }

            if (h < height - 1)
            {
                if (w > 0)
                {
                    somaRedx   += temp[h + 1][w - 1].rgbtRed * -1;
                    somaGreenx += temp[h + 1][w - 1].rgbtGreen * -1;
                    somaBluex  += temp[h + 1][w - 1].rgbtBlue * -1;

                    somaRedy   += temp[h + 1][w - 1].rgbtRed * 1;
                    somaGreeny += temp[h + 1][w - 1].rgbtGreen * 1;
                    somaBluey  += temp[h + 1][w - 1].rgbtBlue * 1;
                }

                somaRedx   += temp[h + 1][w].rgbtRed * 0;
                somaGreenx += temp[h + 1][w].rgbtGreen * 0;
                somaBluex  += temp[h + 1][w].rgbtBlue * 0;

                somaRedy   += temp[h + 1][w].rgbtRed * 2;
                somaGreeny += temp[h + 1][w].rgbtGreen * 2;
                somaBluey  += temp[h + 1][w].rgbtBlue * 2;

                if (w < width - 1)
                {
                    somaRedx   += temp[h + 1][w + 1].rgbtRed * 1;
                    somaGreenx += temp[h + 1][w + 1].rgbtGreen * 1;
                    somaBluex  += temp[h + 1][w + 1].rgbtBlue * 1;

                    somaRedy   += temp[h + 1][w + 1].rgbtRed * 1;
                    somaGreeny += temp[h + 1][w + 1].rgbtGreen * 1;
                    somaBluey  += temp[h + 1][w + 1].rgbtBlue * 1;
                }
            }

            //Fazendo o calculo
            int newColorRed  = round(sqrt(somaRedx * somaRedx + somaRedy * somaRedy));
            if (newColorRed > 255)
            {
                newColorRed = 255;
            }

            int newColorGreen  = round(sqrt(somaGreenx * somaGreenx + somaGreeny * somaGreeny));
            if (newColorGreen > 255)
            {
                newColorGreen = 255;
            }

            int newColorBlue  = round(sqrt(somaBluex * somaBluex + somaBluey * somaBluey));
            if (newColorBlue > 255)
            {
                newColorBlue = 255;
            }

            //Atualizando a variavel image!
            image[h][w].rgbtRed   = newColorRed;
            image[h][w].rgbtGreen = newColorGreen;
            image[h][w].rgbtBlue  = newColorBlue;
        }
    }

    return;
}
