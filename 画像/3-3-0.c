#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXLENGTH 100
unsigned char header[54];
unsigned char imgin[3][512][512];
unsigned char imgout[3][512][512];
unsigned char tmp1[3][512][512];
unsigned char tmp2[3][512][512];

double dtemp[3][512][512];
int itemp[3][512][512];

void convert(int n);
void get_data();
void rgb_to_ybr();
void processing();
void ybr_to_rgb();
void put_data();
int value(int a, int b);

int width, height, bite;
int localRegionSize = 20;

double rgb_con_ybr[3][3] = {
    {0.2990, 0.5870, 0.1140},
    {-0.1687, -0.3313, 0.5000},
    {0.5000, -0.4187, -0.0813},
};

double ybr_con_rgb[3][3] = {
    {1.0000, 0.0000, 1.4020},
    {1.0000, -0.3441, -0.7141},
    {1.0000, 1.7720, 0.0000},
};

int main()
{
    get_data();
    rgb_to_ybr();
    processing();
    ybr_to_rgb();
    put_data();
    return 0;
}

void get_data()
{
    FILE *fp;

    char filename[MAXLENGTH];
    int i, c, x, y;

    printf("ファイル名を入力して下さい:");
    scanf("%s", filename);

    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("ファイルをオープンできません.\n");
        exit(1);
    }

    printf("ファイルをオープンしました.\n");

    for (i = 0; i < 54; i++)
    {
        c = fgetc(fp);
        header[i] = (unsigned char)c;
    }
    width = value(21, 18);
    printf("---width : %3d\n", width);

    height = value(25, 22);
    printf("---height: %3d\n", height);

    for (y = height - 1; y >= 0; y--)
    {
        for (x = 0; x < width; x++)
        {
            for (i = 2; i >= 0; i--)
            {
                c = fgetc(fp);
                imgin[i][x][y] = (unsigned char)c;
            }
        }
    }

    fclose(fp);
    printf("\n%s をクローズしました.\n", filename);
}

void convert(int n)
{
    printf("%02x", n);
}

int value(int a, int b)
{
    int i;
    int value;
    value = header[a];
    for (i = a - 1; i >= b; i--)
    {
        value <<= 8;
        value += header[i];
    }
    return value;
}

void processing()
{
    // Moving Average-based Local Adaptive Thresholding
    int x, y, i, m, n;

    double temp[512][512] = {};
    int sum, count;

    // Calculate local adaptive threshold for each pixel
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            sum = 0;
            count = 0;
            for (m = -localRegionSize / 2; m <= localRegionSize / 2; m++)
            {
                for (n = -localRegionSize / 2; n <= localRegionSize / 2; n++)
                {
                    int tmpX = x + m;
                    int tmpY = y + n;
                    // Boundary handling: Use available image points to form average
                    if (tmpX >= 0 && tmpX < width && tmpY >= 0 && tmpY < height)
                    {
                        sum += imgin[0][tmpX][tmpY];
                        count++;
                    }
                }
            }
            temp[x][y] = 0.92*(sum / count);
        }
    }

    // Binarize the image based on the local adaptive threshold
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            for (i = 2; i >= 0; i--)
            {
                if (i == 0)
                {
                    if (imgin[i][x][y] < temp[x][y])
                    {
                        imgin[i][x][y] = 0;
                    }
                    else if (temp[x][y] <= imgin[i][x][y] && imgin[i][x][y] <= 255)
                    {
                        imgin[i][x][y] = 255;
                    }
                }
                else
                {
                    imgin[i][x][y] = 128;
                }
                imgout[i][x][y] = imgin[i][x][y];
            }
        }
    }
}

void put_data()
{
    FILE *fp;
    char filename1[MAXLENGTH];
    int i, x, y;

    printf("出力ファイル名を入力して下さい:");
    scanf("%s", filename1);

    fp = fopen(filename1, "wb");

    printf("%sをオープンしました.\n", filename1);

    for (i = 0; i < 54; i++)
    {
        fputc(header[i], fp);
    }

    for (y = height - 1; y >= 0; y--)
    {
        for (x = 0; x < width; x++)
        {
            for (i = 2; i >= 0; i--)
            {
                fputc(imgout[i][x][y], fp);
            }
        }
    }

    for (i = 0; i < bite; i++)
    {
        fputc('\0', fp);
    }

    fclose(fp);

    printf("%sをクローズしました.\n", filename1);
}

void rgb_to_ybr()
{
    int i, x, y, j;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            for (i = 0; i < 3; i++)
            {
                dtemp[i][x][y] = 0.0;
                for (j = 0; j < 3; j++)
                    dtemp[i][x][y] += rgb_con_ybr[i][j] * (double)imgin[j][x][y];
            }
        }
    }

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            for (i = 0; i < 3; i++)
            {

                if (dtemp[i][x][y] > 0.0)
                {
                    itemp[i][x][y] = (int)(dtemp[i][x][y] + 0.5);
                }
                else
                {
                    itemp[i][x][y] = (int)(dtemp[i][x][y] - 0.5);
                }

                if (i != 0)
                {
                    itemp[i][x][y] += 128;
                }

                if (itemp[i][x][y] > 255)
                {
                    itemp[i][x][y] = 255;
                }
                else if (itemp[i][x][y] < 0)
                {
                    itemp[i][x][y] = 0;
                }

                imgin[i][x][y] = (unsigned char)itemp[i][x][y];
            }
        }
    }
}

void ybr_to_rgb()
{
    int i, x, y, j;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            for (i = 0; i < 3; i++)
            {
                dtemp[i][x][y] = 0.0;
                for (j = 0; j < 3; j++)
                    if (j == 0)
                        dtemp[i][x][y] += ybr_con_rgb[i][j] * (double)imgout[j][x][y];
                    else
                        dtemp[i][x][y] += ybr_con_rgb[i][j] * (double)(imgout[j][x][y] - 128);
            }
        }
    }

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            for (i = 0; i < 3; i++)
            {

                if (dtemp[i][x][y] > 0.0)
                {
                    itemp[i][x][y] = (int)(dtemp[i][x][y] + 0.5);
                }
                else
                {
                    itemp[i][x][y] = (int)(dtemp[i][x][y] - 0.5);
                }

                if (itemp[i][x][y] > 255)
                {
                    itemp[i][x][y] = 255;
                }
                else if (itemp[i][x][y] < 0)
                {
                    itemp[i][x][y] = 0;
                }

                imgout[i][x][y] = (unsigned char)itemp[i][x][y];
            }
        }
    }
}
