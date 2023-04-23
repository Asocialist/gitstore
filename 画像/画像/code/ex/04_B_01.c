#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAXLENGTH 100
unsigned char header[54];
unsigned char imgin[3][512][512];
unsigned char imgout[3][512][512];
void convert(int n);
void get_data();
void processing();
void put_data();
int value(int a, int b);
int width, height, bite;

int main(){

  get_data();
  processing();
  put_data();

  return 0;
}

void get_data(){
  FILE *fp;
  
  char filename[MAXLENGTH];
  int i, c, x, y;
  int filesize, offset, bite_pixel;

  printf("ファイル名を入力して下さい:");
  scanf("%s", filename);

  fp = fopen(filename, "rb");

  if(fp == NULL){
    printf("ファイルをオーブンできません.\n");
    exit(1);
  }

  printf("ファイルをオーブンしました.\n");

  for(i = 0; i < 54; i ++){
    c = fgetc(fp);
    header[i] = c;
  }



  //---------------------------------
  printf("\n<ファイルタイプ>\n");
  printf("header[0]=");
  convert(header[0]);

  printf(" header[1]=");
  convert(header[1]);
  printf("\n");
  //---------------------------------
  printf("\n<ファイルサイズ>\n");
  printf("header[2]=");
  convert(header[2]);

  printf(" header[3]=");
  convert(header[3]);

  printf(" header[4]=");
  convert(header[4]);

  printf(" header[5]=");
  convert(header[5]);

  filesize = value(5, 2);
  printf("\n%dバイト\n", filesize);
  //---------------------------------
  printf("\n<予約領域>\n");
  printf("header[6]=");
  convert(header[6]);

  printf(" header[7]=");
  convert(header[7]);

  printf(" header[8]=");
  convert(header[8]);

  printf(" header[9]=");
  convert(header[9]);
  printf("\n");
  //---------------------------------
  printf("\n<オフセット>\n");
  printf("header[10]=");
  convert(header[10]);

  printf(" header[11]=");
  convert(header[11]);

  printf(" header[12]=");
  convert(header[12]);

  printf(" header[13]=");
  convert(header[13]);

  offset = value(13, 10),
  printf("\n%dバイト\n", offset);
  //---------------------------------
  printf("\n<情報ベッダサイズ>\n");
  printf("header[14]=");
  convert(header[14]);

  printf(" header[15]=");
  convert(header[15]);

  printf(" header[16]=");
  convert(header[16]);

  printf(" header[17]=");
  convert(header[17]);
  printf("\n");
  //---------------------------------
  printf("\n<画像の幅>\n");
  printf("header[18]=");
  convert(header[18]);

  printf(" header[19]=");
  convert(header[19]);

  printf(" header[20]=");
  convert(header[20]);

  printf(" header[21]=");
  convert(header[21]);

  width = value(21, 18);
  printf("\n%d画素\n",width);
  //---------------------------------
  printf("\n<画像の高さ>\n");
  printf("header[22]=");
  convert(header[22]);

  printf(" header[23]=");
  convert(header[23]);

  printf(" header[24]=");
  convert(header[24]);

  printf(" header[25]=");
  convert(header[25]);

  height = value(25, 22);
  printf("\n%dライン\n",height);
  //---------------------------------
  printf("\n<色プレーン数>\n");
  printf("header[26]=");
  convert(header[26]);

  printf(" header[27]=");
  convert(header[27]);
  printf("\n");
  //---------------------------------
  printf("\n<1画素当たりのビット数>\n");
  printf("header[28]=");
  convert(header[28]);

  printf(" header[29]=");
  convert(header[29]);

  bite_pixel = value(29, 28);
  printf("\n%dビット\n",bite_pixel);
  //---------------------------------
  printf("\n<圧縮方式>\n");
  printf("header[30]=");
  convert(header[30]);

  printf(" header[31]=");
  convert(header[31]);

  printf(" header[32]=");
  convert(header[32]);

  printf(" header[33]=");
  convert(header[33]);
  printf("\n");
  //---------------------------------
  printf("\n<画像データサイズ>\n");
  printf("header[34]=");
  convert(header[34]);

  printf(" header[35]=");
  convert(header[35]);

  printf(" header[36]=");
  convert(header[36]);

  printf(" header[37]=");
  convert(header[37]);
  printf("\n");
  //---------------------------------
  printf("\n<水平解像度>\n");
  printf("header[38]=");
  convert(header[38]);

  printf(" header[39]=");
  convert(header[39]);

  printf(" header[40]=");
  convert(header[40]);

  printf(" header[41]=");
  convert(header[41]);
  printf("\n");
  //---------------------------------
  printf("\n<垂直解像度>\n");
  printf("header[42]=");
  convert(header[42]);

  printf(" header[43]=");
  convert(header[43]);

  printf(" header[44]=");
  convert(header[44]);

  printf(" header[45]=");
  convert(header[45]);
  printf("\n");
  //---------------------------------
  printf("\n<色数>\n");
  printf("header[46]=");
  convert(header[46]);

  printf(" header[47]=");
  convert(header[47]);

  printf(" header[48]=");
  convert(header[48]);

  printf(" header[49]=");
  convert(header[49]);
  printf("\n");
  //---------------------------------
  printf("\n<重要な色数>\n");
  printf("header[50]=");
  convert(header[50]);

  printf(" header[51]=");
  convert(header[51]);

  printf(" header[52]=");
  convert(header[52]);

  printf(" header[53]=");
  convert(header[53]);
  printf("\n");
  //---------------------------------
  printf("\n<挿入ビット数>\n");
  bite = (offset + width * height * (bite_pixel / 8)) % 4;
  printf("%dバイト\n",bite);
  
  for(y = height - 1; y >= 0; y--){
    for(x = 0; x < width; x++){
      for(i = 0; i < 3; i++){
        c = fgetc(fp);
        imgin[i][x][y] = c;
      }
    }
  }
  fclose(fp);
  printf("\n%s をクローズしました.\n", filename);

}

void convert(int n){
  
  printf("%02x", n);

}

int value(int a, int b){
  int i;
  int value;
  value = header[a];
  for(i = a-1; i >= b; i--){
    value <<= 8;
    value += header[i];
  }
  return value;
}

void processing(){
  int i, x, y;
  if(height <= 16 || width <= 16){
    printf("入力画像データを表示します.\n");
  
    printf("\n<R信号>\n");
    for(y = 0; y < height; y++){
      for(x = 0;x < width; x++){
        printf("%02x ", imgin[2][x][y]);
      }
      printf("\n");
    }

    printf("\n<G信号>\n");
    for(y = 0; y < height; y++){
      for(x = 0; x < width; x++){
        printf("%02x ",imgin[1][x][y]);
      }
      printf("\n");
    }

    printf("\n<B信号>\n");
    for(y = 0; y < height; y++){
      for(x = 0; x < width; x++){
        printf("%02x ",imgin[0][x][y]);
      }
      printf("\n");
    }
  }else{
    printf("画像サイズが大きいため表示しません.\n");
  }

  for(y = 0; y < height; y++){
    for(x = 0; x < width; x++){
      for(i = 0; i < 3; i++){
        imgout[i][x][y] = imgin[i][x][y];
      }
    }
  }

}

void put_data(){
  FILE *fp;
  char filename1[MAXLENGTH];
  int i,x,y;

  printf("出力ファイル名を入力して下さい:");
  scanf("%s",filename1);

  fp = fopen(filename1,"wp");

  printf("%sをオープンしました.\n", filename1);

  for (i = 0; i < 54; i++){
    fputc(header[i], fp);
  }
  

  for(y = height - 1; y >= 0; y--){
    for(x = 0; x < width; x++){
      for(i = 0;i < 3; i++){
        fputc(imgout[i][x][y], fp);
      }
    }
  }

  for(i = 0; i < bite; i++){
    fputc('\0', fp);
  }

  fclose(fp);

  printf("%sをクローズしました.\n", filename1);

}
