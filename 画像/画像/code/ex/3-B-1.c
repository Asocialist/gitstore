

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 100
unsigned char header[54];
void get_data();
int main() {
    get_data();
    return 0;
}

int calculate(int a, int b);//バイト数計算
void get_data() {
    FILE* fp;

    char filename[MAX];
    int c;
    int filesize, offset, width, height, bite_px, bits;//画像の属性


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
    printf("\n\n<ファイルタイプ>\n");
    for (int i = 0; i < 2; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\nファイルサイズ>\n");
    filesize = calculate(5,2);
    for (int i = 2; i < 6; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n%dバイト",filesize);
    printf("\n\n<予約領域>\n");
    for (int i = 6; i < 10; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<オフセット>\n");
    for (int i = 10; i < 14; i++) {
        printf("header[%d]=%2x ", i, header[i]);

    }
    offset = calculate(13, 10);
    printf("\n\n%dバイト", offset);
    printf("\n\n<情報へッダサイズ>\n");
    for (int i = 14; i < 18; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<画像の幅>\n");
    width = calculate(21, 18);
    for (int i = 18; i < 22; i++) {
        printf("header[%d]=%2x ", i, header[i]);
        
    }
    printf("\n%d画素\n",width);
    printf("\n\n<画像の高さ>");
    height = calculate(25, 22);
    for (int i = 22; i < 26; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }

    printf("\n%dライン\n", height);
    printf("\n\n<色プレーン数>\n");
    for (int i = 26; i < 28; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<1画素にあたりのビット数>\n");
    bite_px = value(29, 28);
    for (int i = 28; i < 30; i++) {
        printf("header[%d]=%2x ", i, header[i]);

    }
    printf("\n%dビット", bite_px);
    printf("\n\n<圧縮方式>\n");
    for (int i = 30; i < 34; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<画像データサイズ>\n");
    for (int i = 34; i < 38; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<水平解像度>\n");
    for (int i = 39; i < 42; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<垂直解像度>\n");
    for (int i = 42; i < 46; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<色数>\n");
    for (int i = 46; i < 50; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<重要な色数>\n");
    for (int i = 50; i < 54; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<挿入ビット数>\n");
    bits = (offset + width * height * (bite_px / 8)) % 4;
    printf("%dバイト\n", bits);
    fclose(fp);
    printf("\n%sをクローズしました.", filename);

}




int calculate(int a, int b) {
    int value;
    value = header[a];
    for (int i = a - 1; i >= b; i--) {
        value <<= 8;
        value += header[i];
    }

    
}


