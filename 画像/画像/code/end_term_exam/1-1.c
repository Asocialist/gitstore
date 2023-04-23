
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAXLENGTH 100
unsigned char header[54];
unsigned char imgin[3][512][512];
unsigned char imgout[3][512][512];

double dtemp[3][512][512];
int itemp[3][512][512];

void convert(int n);
void get_data();
void rgb_to_ybr();
void processing();
void ybr_to_rgb();
void put_data();
int calculate(int a, int b);
int width, height, bite;

double rgb_con_ybr[3][3] = {
  { 0.2990, 0.5870, 0.1140},
  {-0.1687,-0.3313, 0.5000},
  { 0.5000,-0.4187,-0.0813}
};

double ybr_con_rgb[3][3] = {
  { 1.0000, 0.0000, 1.4020},
  { 1.0000,-0.3441,-0.7141},
  { 1.0000, 1.7720, 0.0000}
};

//char ybr_name[3][3] = { "Y", "Cb", "Cr"};

int main(){

  get_data();
  rgb_to_ybr();
  processing();
  ybr_to_rgb();
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
    header[i] = (unsigned char)c;
  }

  /*  //---------------------------------
  printf("\n<ファイルタイプ>\n");
  printf("header[0]=");
  convert(header[0]);

  printf(" header[1]=");
  convert(header[1]);
  printf("\n");
  */
  //---------------------------------
  printf("\n<ファイルサイズ>\n");
  /*printf("header[2]=");
  convert(header[2]);

  printf(" header[3]=");
  convert(header[3]);

  printf(" header[4]=");
  convert(header[4]);

  printf(" header[5]=");
  convert(header[5]);
  */
  filesize = calculate(5, 2);
  printf("\n%dバイト\n", filesize);
  /*//---------------------------------
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
  */
  //---------------------------------
  printf("\n<オフセット>\n");
  /*printf("header[10]=");
  convert(header[10]);

  printf(" header[11]=");
  convert(header[11]);

  printf(" header[12]=");
  convert(header[12]);

  printf(" header[13]=");
  convert(header[13]);*/

  offset = calculate(13, 10),
    printf("\n%dバイト\n", offset);
  /*//---------------------------------
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
  */
  //---------------------------------
  printf("\n<画像の幅>\n");
  /*printf("header[18]=");
  convert(header[18]);

  printf(" header[19]=");
  convert(header[19]);

  printf(" header[20]=");
  convert(header[20]);

  printf(" header[21]=");
  convert(header[21]);*/

  width = calculate(21, 18);
  printf("\n%d画素\n",width);
  //---------------------------------
  printf("\n<画像の高さ>\n");
  /*printf("header[22]=");
    convert(header[22]);

    printf(" header[23]=");
    convert(header[23]);

    printf(" header[24]=");
    convert(header[24]);

    printf(" header[25]=");
    convert(header[25]);*/

  height = calculate(25, 22);
  printf("\n%dライン\n",height);
  /*//---------------------------------
  printf("\n<色プレーン数>\n");
  printf("header[26]=");
  convert(header[26]);

  printf(" header[27]=");
  convert(header[27]);
  printf("\n");*/
  //---------------------------------
  printf("\n<1画素当たりのビット数>\n");
  /*printf("header[28]=");
  convert(header[28]);

  printf(" header[29]=");
  convert(header[29]);*/

  bite_pixel = calculate(29, 28);
  printf("\n%dビット\n",bite_pixel);
  /*//---------------------------------
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
  */
  //---------------------------------
  printf("\n<挿入ビット数>\n");
  bite = (offset + width * height * (bite_pixel / 8)) % 4;
  printf("%dバイト\n",bite);
  
  for(y = height - 1; y >= 0; y--){
    for(x = 0; x < width; x++){
      for(i = 2; i >= 0; i--){
        c = fgetc(fp);
        imgin[i][x][y] = (unsigned char)c;
      }
    }
  }
  fclose(fp);
  printf("\n%s をクローズしました.\n", filename);

}

void convert(int n){
  
  printf("%02x", n);

}

int calculate(int a, int b){
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
  int i,x,y;
  double n;
  double d_point[2];
  int i_point[2];
  double x_value[2];
  double y_value[2];
  double tmp[2];
  int value;
  //devide
  int block=2;
  int bx,by;
  bx=width/block;
  by=height/block;
  
  //A
  n=0.5;
  for(y=0;y<height;y++){
    for(x=0;x<width;x++){
        d_point[0]=(double)x*n;
         d_point[1]=(double)y*n;
      for(i=0;i<=1;i++){
        i_point[i]=(int)d_point[i];
}
  if(d_point[0]<width - 1 && d_point[1]<height - 1){
  x_value[0]=d_point[0]-i_point[0];
  x_value[1]=1-x_value[0];
  y_value[0]=d_point[1]-d_point[1];
  y_value[1]=1-y_value[0];
  for(i=0;i<=2;i++){
   
    tmp[0]=x_value[1]*(double)imgin[i][i_point[0]][i_point[1]]+x_value[0]*(double)imgin[i][i_point[0]+1][i_point[1]];
    tmp[1]=x_value[1]*(double)imgin[i][i_point[0]][i_point[1]+1]+x_value[0]*(double)imgin[i][i_point[0]+1][i_point[1]+1];
    value=(int)(y_value[1]*tmp[0]+y_value[0]*tmp[1]+0.5);
    imgout[i][x/2][y/2]=value;
    
  }
  }else {
    imgout[0][x][y]=0;
    imgout[1][x][y]=128;
    imgout[2][x][y]=128;
  }

    }
  }
//B
for(i=0;i<=2;i++){
for(y=0;y<by;y++){
  for(x=bx;x<width;x++){
    imgout[i][x][y]=imgin[i][x-128][y+128];
    }
  }
}
//C

double filter_change[3][3] = {  
            {0.0, 1.0, 0.0},
            {1.0,-4.0, 1.0},
            {0.0, 1.0, 0.0}};
int temp;
double sum;
for(y = by; y < height; y++){
    for(x = 0; x < bx; x++){
      if(x<=0 || x>=width || y<=0 || y>=height){
      imgout[0][x][y]=0;
      }else{
        sum=0.0;
        for(int m =-1;m<2;m++){
          for(int n=-1;n<2;n++){
            sum+=(double)(imgin[0][x+128+m][y-128+n]*filter_change[m+1][n+1]);
              }
            }
          if(sum >= 0.0){temp = (int)(sum + 0.5);
             }else{
        temp = (int)(sum - 0.5);
        }
        temp += 128;
        }
        if (temp>255){
          temp=255;
      }else if (temp<0){
        temp=0;
        }
      imgout[0][x][y] = (unsigned char)temp;
      imgout[1][x][y] = 128;
      imgout[2][x][y] = 128;
      
}
}

//D
 n=2;
  for(y=0;y<height;y++){
    for(x=0;x<width;x++){
        d_point[0]=(double)x*n;
         d_point[1]=(double)y*n;
      for(i=0;i<=1;i++){
        i_point[i]=(int)d_point[i];
}
  if(d_point[0]<width - 1 && d_point[1]<height - 1){
  x_value[0]=d_point[0]-i_point[0];
  x_value[1]=1-x_value[0];
  y_value[0]=d_point[1]-d_point[1];
  y_value[1]=1-y_value[0];
  for(i=0;i<=2;i++){
   
    tmp[0]=x_value[1]*(double)imgin[i][i_point[0]][i_point[1]]+x_value[0]*(double)imgin[i][i_point[0]+1][i_point[1]];
    tmp[1]=x_value[1]*(double)imgin[i][i_point[0]][i_point[1]+1]+x_value[0]*(double)imgin[i][i_point[0]+1][i_point[1]+1];
    value=(int)(y_value[1]*tmp[0]+y_value[0]*tmp[1]+0.5);
    imgout[i][x+256][y+256]=value;
    
  }
  }
  
    }
  }

  printf("入力画像データをコピーして出力画像データを作成しました.\n");
  }
  
 
  





 

void put_data(){
  FILE *fp;
  char filename1[MAXLENGTH];
  int i,x,y;

  printf("出力ファイル名を入力して下さい:");
  scanf("%s",filename1);

  fp = fopen(filename1,"w+");
  

  printf("%sをオープンしました.\n", filename1);

  for (i = 0; i < 54; i++){
    fputc(header[i], fp);
  }
  

  for(y = height - 1; y >= 0; y--){
    for(x = 0; x < width; x++){
      for(i = 2;i >= 0; i--){
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

void rgb_to_ybr(){
  int i, x, y, j;

  /*
  printf("\n<入力RGB信号(整数値)>\n");

  if(height <= 16 || width <= 16){
    
    printf("\n<R信号>\n");
    for(y = 0; y < height; y++){
      for(x = 0;x < width; x++){
        printf("%02x ", imgin[0][x][y]);
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
        printf("%02x ",imgin[2][x][y]);
      }
      printf("\n");
    }
  }else{
    printf("画像サイズが大きいため表示しません.\n");
  }
  */
  for(y = 0; y < height; y++){
    for(x = 0; x < width; x++){
      for(i = 0; i < 3; i++){
        dtemp[i][x][y] = 0.0;
        for (j = 0; j < 3; j++)
          dtemp[i][x][y] += rgb_con_ybr[i][j] * (double)imgin[j][x][y];
      }
    }
  }

  for(y = 0; y < height; y++){
    for(x = 0; x < width; x++){
      for(i = 0; i < 3; i++){
        
        if(dtemp[i][x][y] > 0.0){
          itemp[i][x][y] = (int)(dtemp[i][x][y] + 0.5);
        }else{
          itemp[i][x][y] = (int)(dtemp[i][x][y] - 0.5);
        }

        if (i != 0){
          itemp[i][x][y] += 128;
        }

        if (itemp[i][x][y] > 255){
          itemp[i][x][y] = 255;
	}else if (itemp[i][x][y] < 0){
          itemp[i][x][y] = 0;
        }
	
        imgin[i][x][y] = (unsigned char)itemp[i][x][y];
      }
    }
  }

  
  /*
  printf("\n<入力YCbCr信号(整数値)>\n");
  
  if(height <= 16 || width <= 16){
    
    printf("\n<Y信号>\n");
    for(y = 0; y < height; y++){
      for(x = 0; x < width; x++){
        printf("%02x ", imgin[0][x][y]);
      }
      printf("\n");
    }
    
    printf("\n<Cb信号>\n");
    for(y = 0; y < height; y++){
      for(x = 0; x < width; x++){
        printf("%02x ",imgin[1][x][y]);
      }
      printf("\n");
    }

    printf("\n<Cr信号>\n");
    for(y = 0; y < height; y++){
      for(x = 0; x < width; x++){
        printf("%02x ",imgin[2][x][y]);
      }
      printf("\n");
    }
  }else{
    printf("画像サイズが大きいため表示しません.\n");
  }
  */
}

void ybr_to_rgb(){
  int i, x, y, j;
  
  /*
  printf("\n<入力YCbCr信号(整数値)>\n");
  
  if(height <= 16 || width <= 16){

    printf("\n<Y信号>\n");
    for(y = 0; y < height; y++){
      for(x = 0;x < width; x++){
        printf("%02x ", imgin[0][x][y]);
      }
      printf("\n");
    }

    printf("\n<Cb信号>\n");
    for(y = 0; y < height; y++){
      for(x = 0; x < width; x++){
        printf("%02x ",imgin[1][x][y]);
      }
      printf("\n");
    }

    printf("\n<Cr信号>\n");
    for(y = 0; y < height; y++){
      for(x = 0; x < width; x++){
        printf("%02x ",imgin[2][x][y]);
      }
      printf("\n");
    }
  }else{
    printf("画像サイズが大きいため表示しません.\n");
  }
  */

  for(y = 0; y < height; y++){
    for(x = 0; x < width; x++){
      for(i = 0; i < 3; i++){
        dtemp[i][x][y] = 0.0;
        for (j = 0; j < 3; j++)
          if (j == 0)
            dtemp[i][x][y] += ybr_con_rgb[i][j] * (double)imgout[j][x][y];
          else
            dtemp[i][x][y] += ybr_con_rgb[i][j] * (double)(imgout[j][x][y] - 128);
      }
    }
  }
  

  for(y = 0; y < height; y++){
    for(x = 0; x < width; x++){
      for(i = 0; i < 3; i++){
        
        if(dtemp[i][x][y] > 0.0){
	  itemp[i][x][y] = (int)(dtemp[i][x][y] + 0.5);
          
        }else {
          itemp[i][x][y] = (int)(dtemp[i][x][y] - 0.5);
       
        }

        if (itemp[i][x][y] > 255){
          itemp[i][x][y] = 255;
        }else if (itemp[i][x][y] < 0){
          itemp[i][x][y] = 0;
        }

        imgout[i][x][y] = (unsigned char)itemp[i][x][y];
      }
    }
  }

  /*
  printf("\n<入力RGB信号(整数値)>\n");

  if(height <= 16 || width <= 16){
    
    printf("\n<R信号>\n");
    for(y = 0; y < height; y++){
      for(x = 0; x < width; x++){
        printf("%02x ", imgout[0][x][y]);
      }
      printf("\n");
    }

    printf("\n<G信号>\n");
    for(y = 0; y < height; y++){
      for(x = 0; x < width; x++){
        printf("%02x ",imgout[1][x][y]);
      }
      printf("\n");
    }

    printf("\n<B信号>\n");
    for(y = 0; y < height; y++){
      for(x = 0; x < width; x++){
        printf("%02x ",imgout[2][x][y]);
      }
      printf("\n");
    }
  }else{
    printf("画像サイズが大きいため表示しません.\n");
  }
  */
}
