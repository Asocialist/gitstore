#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 100
#define CH 3
#define Ych 0
#define ROW 3
#define COL 3

unsigned char header[54];
unsigned char imgin[3][512][512];//入力画像
unsigned char imgout[3][512][512];//
double dtemp[3][512][512];
int itemp[3][512][512];

void processing();
void get_data();
void put_data();
void rgb_to_ybr();
void ybr_to_rgb();

int width, height;//画像の幅と高さ
int bits;//画像のビット数

double rgb_con_ybr[ROW][COL] = {
  { 0.2990, 0.5870, 0.1140},
   {-0.1687,-0.3313, 0.5000},
   { 0.5000,-0.4187,-0.0813}
};
double ybr_con_rgb[ROW][COL] = {
  { 1.0000, 0.0000, 1.4020},
  { 1.0000,-0.3441,-0.7141},
  { 1.0000, 1.7720, 0.0000}
};
char ybr_name[3][3] = { "Y","Cb","Cr" };

int main() {
    get_data();
    rgb_to_ybr();
    processing();
    ybr_to_rgb();
    put_data();
    return 0;
}

int calculate(int a, int b);//バイト数計算
void get_data() {
    FILE* fp;

    char filename[MAX];
    int c;
    int filesize, offset, bite_px;//画像の属性


    printf("ファイル名を入力して下さい:");
    scanf("%s", filename);
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("%sをオーブンできません\n", filename);
        exit(1);
    }
    printf("%sをオーブンしました.\n", filename);
    for (int i = 0; i < 54; i++) {
        c = fgetc(fp);
        header[i] = c;
    }
    /* printf("\n\n<ファイルタイプ>\n");
    for (int i = 0; i < 2; i++) {
      printf("header[%d]=%02x ", i, header[i]);
      } */
    printf("\n\nファイルサイズ>\n");
    filesize = calculate(5, 2);
    /*  for (int i = 2; i < 6; i++) {
          printf("header[%d]=%02x ", i, header[i]);
      }*/
    printf("\n\n%dバイト", filesize);
    /* printf("\n\n<予約領域>\n");
    for (int i = 6; i < 10; i++) {
      printf("header[%d]=%02x ", i, header[i]);
      } */
    printf("\n\n<オフセット>\n");
    /*for (int i = 10; i < 14; i++) {
        printf("header[%d]=%02x ", i, header[i]);

    }*/
    offset = calculate(13, 10);
    printf("\n\n%dバイト", offset);
    /*  printf("\n\n<情報へッダサイズ>\n");
    for (int i = 14; i < 18; i++) {
      printf("header[%d]=%02x ", i, header[i]);
      } */
    printf("\n\n<画像の幅>\n");
    width = calculate(21, 18);
    /*for (int i = 18; i < 22; i++) {
        printf("header[%d]=%02x ", i, header[i]);

    }*/
    printf("\n%d画素\n", width);
    printf("\n\n<画像の高さ>");
    height = calculate(25, 22);
    /*for (int i = 22; i < 26; i++) {
        printf("header[%d]=%02x ", i, header[i]);
    }*/

    printf("\n%dライン\n", height);
    /*  printf("\n\n<色プレーン数>\n");
    for (int i = 26; i < 28; i++) {
      printf("header[%d]=%02x ", i, header[i]);
      } */
    printf("\n\n<1画素にあたりのビット数>\n");
    bite_px = calculate(29, 28);
    /*  for (int i = 28; i < 30; i++) {
          printf("header[%d]=%02x ", i, header[i]);

      }*/
    printf("\n%dビット", bite_px);
    /* printf("\n\n<圧縮方式>\n");
    for (int i = 30; i < 34; i++) {
      printf("header[%d]=%02x ", i, header[i]);
    }
    printf("\n\n<画像データサイズ>\n");
    for (int i = 34; i < 38; i++) {
      printf("header[%d]=%02x ", i, header[i]);
    }
    printf("\n\n<水平解像度>\n");
    for (int i = 39; i < 42; i++) {
      printf("header[%d]=%02x ", i, header[i]);
    }
    printf("\n\n<垂直解像度>\n");
    for (int i = 42; i < 46; i++) {
      printf("header[%d]=%02x ", i, header[i]);
    }
    printf("\n\n<色数>\n");
    for (int i = 46; i < 50; i++) {
      printf("header[%d]=%02x ", i, header[i]);
    }
    printf("\n\n<重要な色数>\n");
    for (int i = 50; i < 54; i++) {
      printf("header[%d]=%02x ", i, header[i]);
      } */
    printf("\n\n<挿入ビット数>\n");
    bits = (offset + width * height * (bite_px / 8)) % 4;
    printf("%dバイト\n", bits);
    //imgin[][][]の初期化
    for (int h = height - 1; h >= 0; h--) {
        for (int w = 0; w < width; w++) {
            for (int i = 2; i >= 0; i--) {
                imgin[i][w][h] = (unsigned char)fgetc(fp);
            }
        }
    }

    fclose(fp);
    printf("\n%sをクローズしました.\n", filename);

}
int calculate(int a, int b) {
    int value;
    value = header[a];
    for (int i = a - 1; i >= b; i--) {
        value <<= 8;
        value += header[i];
    }
    return value;

}

void processing() {

    /* for (int y=height-1;y>=0;y--){
   for(int x=0;x<width;x++){
     for(int i=3;i>0;i--){
       imgout[i][x][y]=imgin[i][width-1-x][y];
     }
   }
 }*/

    int i, x, y;
    int copy[3];

    printf("\n コピーモードを入力して下さい.\n");
    printf("(コピーする場合 : 1, 固定値に置き換える場合 : 0)\n");
    for (i = 0; i < 3; i++) {
        printf("%-2s : ", ybr_name[i]);
        scanf("%d", &copy[i]);
    }

    for (i = 0; i < 3; i++) {
        if (copy[i] == 1) {
            for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++) {
                    imgout[i][x][y] = imgin[i][x][y];
                }
            }
        }
        else {
            for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++) {
                    imgout[i][x][y] = 128;
                }
            }
        }
    }


    printf("出力画像データを作成しました.\n");
}
void put_data() {
    FILE* fp;
    char filename1[MAX];
    int i, x, y;

    printf("出力ファイル名を入力して下さい:");
    scanf("%s", filename1);

    fp = fopen(filename1, "wp");

    printf("%sをオープンしました.\n", filename1);

    for (i = 0; i < 54; i++) {
        fputc(header[i], fp);
    }


    for (y = height - 1; y >= 0; y--) {
        for (x = 0; x < width; x++) {
            for (i = 2; i >= 0; i--) {
                fputc(imgout[i][x][y], fp);
            }
        }
    }

    for (i = 0; i < bite; i++) {
        fputc('\0', fp);
    }

    fclose(fp);

    printf("%sをクローズしました.\n", filename1);

}
void rgb_to_ybr() {
    int i, x, y;
    /*if (height <= 16 || width <= 16) {

        printf("\n<R信号>\n");
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                printf("%02x ", imgin[0][x][y]);
            }
            printf("\n");
        }

        printf("\n<G信号>\n");
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                printf("%02x ", imgin[1][x][y]);
            }
            printf("\n");
        }

        printf("\n<B信号>\n");
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                printf("%02x ", imgin[2][x][y]);
            }
            printf("\n");
        }
    }
    else {
        printf("画像サイズが大きいため表示しません.\n");
    }*/

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {

            for (i = 0; i < 3; i++) {
                dtemp[i][x][y] = 0.0;
                for (int j = 0; j < 3; j++)
                    dtemp[i][x][y] += rgb_con_ybr[i][j] * (double)imgin[j][x][y];
            }
        }
    }

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            for (i = 0; i < 3; i++) {

                if (dtemp[i][x][y] > 0.0) {
                    itemp[i][x][y] = (int)(dtemp[i][x][y] + 0.5);
                }
                else {
                    itemp[i][x][y] = (int)(dtemp[i][x][y] - 0.5);
                }

                if (i != 0) {
                    itemp[i][x][y] += 128;
                }

                if (itemp[i][x][y] > 255) {
                    itemp[i][x][y] = 255;
                }
                else if (itemp[i][x][y] < 0) {
                    itemp[i][x][y] = 0;
                }

                imgin[i][x][y] = (unsigned char)itemp[i][x][y];
            }
        }
    }

    /*printf("\n<入力YCbCr信号(整数値)>\n");

    if (height <= 16 || width <= 16) {

        printf("\n<Y信号>\n");
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                printf("%02x ", imgin[0][x][y]);
            }
            printf("\n");
        }

        printf("\n<Cb信号>\n");
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                printf("%02x ", imgin[1][x][y]);
            }
            printf("\n");
        }

        printf("\n<Cr信号>\n");
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                printf("%02x ", imgin[2][x][y]);
            }
            printf("\n");
        }
    }
    else {
        printf("画像サイズが大きいため表示しません.\n");
    }*/

}

void ybr_to_rgb() {
    int i, x, y, j;

   /* printf("\n<入力YCbCr信号(整数値)>\n");

    if (height <= 16 || width <= 16) {

        printf("\n<Y信号>\n");
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                printf("%02x ", imgin[0][x][y]);
            }
            printf("\n");
        }

        printf("\n<Cb信号>\n");
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                printf("%02x ", imgin[1][x][y]);
            }
            printf("\n");
        }

        printf("\n<Cr信号>\n");
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                printf("%02x ", imgin[2][x][y]);
            }
            printf("\n");
        }
    }
    else {
        printf("画像サイズが大きいため表示しません.\n");
    }*/

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            for (i = 0; i < 3; i++) {
                dtemp[i][x][y] = 0.0;
                for (j = 0; j < 3; j++)
                    if (j == 0)
                        dtemp[i][x][y] += ybr_con_rgb[i][j] * (double)imgin[j][x][y];
                    else
                        dtemp[i][x][y] += ybr_con_rgb[i][j] * (double)(imgin[j][x][y] - 128);
            }
        }
    }


    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            for (i = 0; i < 3; i++) {

                if (dtemp[i][x][y] > 0.0) {
                    itemp[i][x][y] = (int)(dtemp[i][x][y] + 0.5);
                }
                else {
                    itemp[i][x][y] = (int)(dtemp[i][x][y] - 0.5);
                }

                if (itemp[i][x][y] > 255) {
                    itemp[i][x][y] = 255;
                }
                else if (itemp[i][x][y] < 0) {
                    itemp[i][x][y] = 0;
                }

                imgout[i][x][y] = (unsigned char)itemp[i][x][y];
            }
        }
    }

    /*printf("\n<入力RGB信号(整数値)>\n");

    if (height <= 16 || width <= 16) {

        printf("\n<R信号>\n");
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                printf("%02x ", imgout[0][x][y]);
            }
            printf("\n");
        }

        printf("\n<G信号>\n");
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                printf("%02x ", imgout[1][x][y]);
            }
            printf("\n");
        }

        printf("\n<B信号>\n");
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                printf("%02x ", imgout[2][x][y]);
            }
            printf("\n");
        }
    }
    else {
        printf("画像サイズが大きいため表示しません.\n");
    }*/

}
