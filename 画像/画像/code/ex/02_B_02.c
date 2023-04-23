#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main(void){
  FILE *fp;
  char read_filename[MAX];
  char write_filename[MAX];
  int c, i;
  int ary[MAX];
  int x = 0;
  int y = 0;

  printf("コピー元ファイル名:");
  scanf("%s", read_filename);
  printf("コピー先ファイル名:");
  scanf("%s", write_filename);

  fp = fopen(read_filename, "rb");
  if(fp == NULL){
    printf("%sをオープンできません.\n", read_filename);
    exit(1);
  }
  printf("%sをオープンしました.\n", read_filename);

  c = fgetc(fp);
  while (c != EOF){
    ary[y] = c;
    c = fgetc(fp);
    x ++;
    y ++;
  }

  printf("%s から %d バイトデータを読み込み,配列に格納しました.\n", read_filename, x);
  fclose(fp);
  printf("%s をクローズしました.\n\n", read_filename);

  printf("配列の内容を表示します.\n");
  for(i = 0; i < y; i++){
    printf("ary[%d]=%d\n", i + 1, ary[i]);
  }

  fp = fopen(write_filename, "wb");
  if (fp == NULL){
    printf("ファイルをオープンできません.\n");
    exit(1);
  }
  printf("\n%s をオープンしました.\n", write_filename);

  x = 0;
  for(i = 0; i < y; i++){
    fputc(ary[i], fp);
    x ++;
  }

  printf("配列に格納された %d バイトのデータを %s に書き出しました.\n", x, write_filename);

  fclose(fp);
  printf("%s をクローズしました.\n", write_filename);

  return 0;

}