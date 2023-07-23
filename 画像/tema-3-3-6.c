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
  printf("start");
get_data();
printf("data\n");
rgb_to_ybr();
printf("rgb\n");
processing();
printf("pro\n");
ybr_to_rgb();
printf("ybr\n");
put_data();
printf("put\n");
return 0;
}

void get_data(){
 FILE *fp;
  
  char filename[MAXLENGTH]="books.bmp";
  int i, c, x, y;


  printf("ファイル名を入力して下さい:");
  //scanf("%s", filename);
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
void processing() {
    // 高斯滤波平滑图像
    int size = 5;
    float sigma = 1.4;
    const double pi = acos(-1.0);
    float kernel[5][5];
    int x, y;
    int m = size / 2;
    float sum = 0;
printf("gs\n");
    // 获取高斯核
    for (y = 0; y < size; y++) {
        for (x = 0; x < size; x++) {
            kernel[y][x] = (1 / (2 * pi * pow(sigma, 2))) * exp(-(pow((x - m), 2) + pow((y - m), 2)) / (2 / pow(sigma, 2))); // 高斯公式
            sum += kernel[y][x];
        }
    }
    printf("gsz\n");
    // 归一化
    for (y = 0; y < size; y++) {
        for (x = 0; x < size; x++) {
            kernel[y][x] /= sum;
        }
    }
  printf("gyh\n");
    // 执行平滑化
    for (y = m; y < height - m; y++) {
        for (x = m; x < width - m; x++) {
            sum = 0;
            for (int i = -m; i <= m; i++) {
                for (int j = -m; j <= m; j++) {
                    sum += imgin[0][y + i][x + j] * kernel[i + m][j + m];
                }
            }
            imgin[0][y][x] = (int)(sum + 0.5);
            imgout[0][y][x] = imgin[0][y][x];
        }
    }
  printf("phh\n");
    // 计算梯度强度
    int magnitude[512][512] = {};
    for (y = 1; y < height - 1; y++) {
        for (x = 1; x < width - 1; x++) {
            magnitude[y][x] = sqrt(pow((imgin[0][y][x + 1] - imgin[0][y][x - 1]), 2) + pow((imgin[0][y + 1][x] - imgin[0][y - 1][x]), 2));
        }
    }
  printf("tdqd\n");
    // 极大值处理
    for (y = 1; y < height - 1; y++) {
        for (x = 1; x < width - 1; x++) {
            double theta = atan2((imgin[0][y + 1][x] - imgin[0][y - 1][x]), (imgin[0][y][x + 1] - imgin[0][y][x - 1]));
            theta = theta * 180 / pi;
            if (theta < 0) {
                theta += 180;
            }

            double p = magnitude[y][x];
            double neighbor1 = 0.0, neighbor2 = 0.0;

            // 根据梯度的方向角度进行插值
            if (theta >= 0 && theta < 45) {
                neighbor1 = magnitude[y][x + 1] * (theta - 0) / 45 + magnitude[y - 1][x + 1] * (45 - theta) / 45;
                neighbor2 = magnitude[y][x - 1] * (theta - 0) / 45 + magnitude[y + 1][x - 1] * (45 - theta) / 45;
            } else if (theta >= 45 && theta < 90) {
                neighbor1 = magnitude[y + 1][x - 1] * (theta - 45) / 45 + magnitude[y + 1][x] * (90 - theta) / 45;
                neighbor2 = magnitude[y - 1][x + 1] * (theta - 45) / 45 + magnitude[y - 1][x] * (90 - theta) / 45;
            } else if (theta >= 90 && theta < 135) {
                neighbor1 = magnitude[y + 1][x] * (theta - 90) / 45 + magnitude[y + 1][x + 1] * (135 - theta) / 45;
                neighbor2 = magnitude[y - 1][x] * (theta - 90) / 45 + magnitude[y - 1][x - 1] * (135 - theta) / 45;
            } else {
                neighbor1 = magnitude[y - 1][x - 1] * (theta - 135) / 45 + magnitude[y][x - 1] * (180 - theta) / 45;
                neighbor2 = magnitude[y + 1][x + 1] * (theta - 135) / 45 + magnitude[y][x + 1] * (180 - theta) / 45;
            }

            // 进行非极大值抑制判断
            if (p >= neighbor1 && p >= neighbor2) {
                magnitude[y][x] = p;
            } else {
                magnitude[y][x] = 0;
            }
        }
    }
    printf("jdaz\n");
    // 双阈值检测 low50 high100
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (magnitude[i][j] >= 15) {
                imgin[0][i][j] = 0;  // 高阈值以上的像素点为强边缘
            } else if(magnitude[i][j]>=10 && magnitude[i][j] <15){
                imgin[0][i][j]=128;
            }else {
                imgin[0][i][j] = 255;  // 低阈值以下的像素点不是边缘
            }
        }
    }
  printf("syzjc\n");
    // 边缘连接
    for (y = 1; y < height - 1; y++) {
        for (x = 1; x < width - 1; x++) {
            if (imgin[0][y][x] == 128) {  // 弱边缘点
                // 检查8邻域内是否存在强边缘点
                if (imgin[0][y - 1][x - 1] == 0 || imgin[0][y - 1][x] == 0 || imgin[0][y - 1][x + 1] == 0 ||
                    imgin[0][y][x - 1] == 0 || imgin[0][y][x + 1] == 0 || imgin[0][y + 1][x - 1] == 0 ||
                    imgin[0][y + 1][x] == 0 || imgin[0][y + 1][x + 1] == 0) {
                    imgin[0][y][x] = 0;  // 连接为强边缘
                } else {
                    imgin[0][y][x] = 255;  // 连接为非边缘
                }
            }
        }
    }

 for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            if (imgout[0][y][x] == 0 && imgout[0][y+1][x+1] == 255) { // 找到第一个边缘
                for (int i = x + 1; i < width - 1; i++) {
                    if (imgout[0][y][i] == 255 && imgout[0][y+1][i +1] == 0) { // 找到第二个边缘
                        // 将两个边缘之间的像素设置为黑色
                        for (int j = x + 1; j < i; j++) {
                            imgout[0][y][j] = 0;
                        }
                        break; // 找到第二个边缘后退出内部循环
                    }
                }
            }
        }
    }


    printf("tc\n");
    // 将结果复制到输出图像
    for (int i = 0; i <= 2; i++) {
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                imgout[i][y][x] = imgin[i][y][x];
            }
        }
    }
    printf("put\n");
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
