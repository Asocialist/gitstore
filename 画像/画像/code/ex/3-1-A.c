#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 100
void get_data();
int main(){
  get_data();
  return 0;
}
int calculate(int a,int b,int c, int d);
void get_data(){
  FILE *fp;
  unsigned char header[54];
  char filename[MAX];
  int c,b;//bはバイト数
  //int filesize,offset,width,height,bits//画像の属性

  
  printf("ファイル名を入力して下さい:");
  scanf("%s",filename);
  fp= fopen(filename,"rb");
  if(fp==NULL){
    printf("%sをオーブンできません\n",filename);
    exit(1);
  }
  printf("%sをオーブンしました.\n",filename);
  for(int i=0;i<54;i++){
    c=fgetc(fp);
    header[i]=c;
  }
  printf("\n<ファイルタイプ>\n");
  for(int i=0;i<2;i++){
    printf("header[%d]=%2x ",i,header[i]);
  }
  printf("\nファイルサイズ>\n");
  b=calculate(header[2],header[3],header[4],header[5]);
  for(int i=2;i<6;i++){
    printf("header[%d]=%2x ",i,header[i]);
  }
  printf("\n%dバイト",b);
}
int calculate(int a,int b,int c ,int d){
  return d*16908288+c*65536+b*256+a;
}

      
