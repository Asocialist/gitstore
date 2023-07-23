#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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
  width = value(21, 18);
  printf("---width : %3d\n",width);
  
  height = value(25, 22);
  printf("---height: %3d\n",height);
  
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


void processing( ) {
//Otsu法で２値化
int x,y,i;
int t;//しきい値
int histogram[256]={0};

for(y=0;y<height;y++){
  for(x=0;x<width;x++){
    histogram[imgin[0][x][y]]++;
  }
}//histogram 計算

/*int cal_histogram[256]={0};
cal_histogram[0]=histogram[0];
for(i=1;i<256;i++){
  cal_histogram[i]=histogram[i-1]+histogram[i];
}*/ //累積直方図

int total_pixel=width*height;
/*for(i=0;i<256;i++){
  total_pixel+=histogram[i];
}*/
//calculate total_pixel
double sum=0.0;
double u=0.0;
for(i=0;i<256;i++){
  sum+=i*histogram[i];
}
u= sum/ total_pixel;
//calculate average gray scale
double sum0=0.0;
double g=0.0;
double max_g=0.0;
double p1=0.0,
       p2=0.0,
       w1=0.0,
       w2=0.0;
for(i=0;i<256;i++){
  p1+=histogram[i];
  if(p1==0) continue;
  p2=total_pixel-p1;
  if(p2==0) break;
  sum0+=i*histogram[i];
w1=sum0/p1;
w2=(sum-sum0)/p2;
g=p1*p2*(w1-w2)*(w1-w2);//重み
if(g>max_g){
  max_g=g;
  t=i;
 }
}//しきい値計算
printf("閾値:%d",t);
for(y=0;y<height;y++){
    for(x=0;x<width;x++){
      for(i=2;i>=0;i--){
	if(i==0){
	  if(imgin[i][x][y]<t){
	    imgin[i][x][y]=0;
	  }else if(t<=imgin[i][x][y]&&imgin[i][x][y]<=255){
	  imgin[i][x][y]=255;
	  }
	}else {
	  imgin[i][x][y]=128;
      }
	imgout[i][x][y]=imgin[i][x][y];
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
      for(i = 2;i >= 0; i--){
        fputc(imgout[i][x][y], fp);
      }
    }
  }

  for(i = 0; i < bite; i++){
    fputc('\0', fp);
  }

  fclose(fp);

  printf("%sをクローズしました.\n", filename1); }
 

  

  


void rgb_to_ybr(){
  int i, x, y, j;

  
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
  
 
}

void ybr_to_rgb(){
  int i, x, y, j;
  
  

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
        }else{
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

  
}
