

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

int calculate(int a, int b);//�o�C�g���v�Z
void get_data() {
    FILE* fp;

    char filename[MAX];
    int c;
    int filesize, offset, width, height, bite_px, bits;//�摜�̑���


    printf("�t�@�C��������͂��ĉ�����:");
    scanf("%s", filename);
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("%s���I�[�u���ł��܂���\n", filename);
        exit(1);
    }
    printf("%s���I�[�u�����܂���.\n", filename);
    for (int i = 0; i < 54; i++) {
        c = fgetc(fp);
        header[i] = c;
    }
    printf("\n\n<�t�@�C���^�C�v>\n");
    for (int i = 0; i < 2; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n�t�@�C���T�C�Y>\n");
    filesize = calculate(5,2);
    for (int i = 2; i < 6; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n%d�o�C�g",filesize);
    printf("\n\n<�\��̈�>\n");
    for (int i = 6; i < 10; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<�I�t�Z�b�g>\n");
    for (int i = 10; i < 14; i++) {
        printf("header[%d]=%2x ", i, header[i]);

    }
    offset = calculate(13, 10);
    printf("\n\n%d�o�C�g", offset);
    printf("\n\n<���փb�_�T�C�Y>\n");
    for (int i = 14; i < 18; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<�摜�̕�>\n");
    width = calculate(21, 18);
    for (int i = 18; i < 22; i++) {
        printf("header[%d]=%2x ", i, header[i]);
        
    }
    printf("\n%d��f\n",width);
    printf("\n\n<�摜�̍���>");
    height = calculate(25, 22);
    for (int i = 22; i < 26; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }

    printf("\n%d���C��\n", height);
    printf("\n\n<�F�v���[����>\n");
    for (int i = 26; i < 28; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<1��f�ɂ�����̃r�b�g��>\n");
    bite_px = value(29, 28);
    for (int i = 28; i < 30; i++) {
        printf("header[%d]=%2x ", i, header[i]);

    }
    printf("\n%d�r�b�g", bite_px);
    printf("\n\n<���k����>\n");
    for (int i = 30; i < 34; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<�摜�f�[�^�T�C�Y>\n");
    for (int i = 34; i < 38; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<�����𑜓x>\n");
    for (int i = 39; i < 42; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<�����𑜓x>\n");
    for (int i = 42; i < 46; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<�F��>\n");
    for (int i = 46; i < 50; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<�d�v�ȐF��>\n");
    for (int i = 50; i < 54; i++) {
        printf("header[%d]=%2x ", i, header[i]);
    }
    printf("\n\n<�}���r�b�g��>\n");
    bits = (offset + width * height * (bite_px / 8)) % 4;
    printf("%d�o�C�g\n", bits);
    fclose(fp);
    printf("\n%s���N���[�Y���܂���.", filename);

}




int calculate(int a, int b) {
    int value;
    value = header[a];
    for (int i = a - 1; i >= b; i--) {
        value <<= 8;
        value += header[i];
    }

    
}


