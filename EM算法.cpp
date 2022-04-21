//假设有A,B,C两种硬币，现在得到的数据中并没有硬币种类的信息和硬币正面朝上的信息
#include <iostream>
#include "math.h"
#include <cstdlib>
using namespace std;

//用于阶乘的函数
constexpr int f(int i) {
    return i < 2 ? 1 : i * f(i - 1);
}

int main() {
    srand((unsigned)time(NULL));
    //得到的硬币数据展示
    int samples[10][15] = {0};
   
    for (int a =0; a <= 9; a++)
    {
        if (a<5)         //A的数量为总量的十分之五
        {
            for (int b = 0; b <= 14; b++)
            {
           
                if (rand() % 4 == 0)
                {
                    samples[a][b] = 0;
                }
                else
                {
                    samples[a][b] = 1;    //A的朝上的概率四分之三
                }
            }
        }

         if ((a>4)&&(a<7))         //B的数量为总量的十分之二
        {
            for (int b = 0; b <= 14; b++)
            {

                if (rand() % 4 == 0)
                {
                    samples[a][b] = 0;
                }
                else
                {
                    samples[a][b] = 1;    //B的朝上的概率四分之三
                }

            }
        }

        if (a>6)         //C的数量为总量的十分之三
        {
            for (int b = 0; b <= 14; b++)
            {
                if (rand() % 3 == 0)
                {
                    samples[a][b] = 1;  //C的朝上的概率三分之一
                }
                else
                {
                    samples[a][b] = 0;
                }

            }
        }

    }



    for (int c = 0; c <= 9; c++)
    {
        for (int d = 0; d <= 14; d++)
        {
            cout  << samples[c][d] << " ";
        }
        cout<<endl ;
    }
    //初始化A,B,C三种硬币的朝上概率
    double prob_A = 0.9; double prob_B = 0.55; double prob_C = 0.2;
    double front[10];//front[i]表示对于第i组，硬币朝上的概率
    //根据得到的数据，算出front
    for (int j = 0; j <=9; j++) {
        front[j] = 0;
        for (int k = 0; k < 15; k++) {
            front[j] += samples[j][k];
        }
        front[j] = front[j] / 15;
    }
    //假设循环2000次后能够得到较为精确的解
    for (int i = 0; i < 500; i++) {
        //计算第i组硬币为A为B或者为C的概率
        double contribution_A = 0; double contribution_B = 0; double contribution_C = 0;
        double weight_A[10]; double weight_B[10]; double weight_C[10];
        double num_AH[10]; double num_BH[10]; double num_CH[10];
        double num_AT[10]; double num_BT[10]; double num_CT[10];
        for (int n = 0; n <=9; n++) {
            contribution_A = f(15) / (f(front[n] * 15) * f(15 - front[n] * 15)) * pow(prob_A, (front[n] * 15)) * pow((1 - prob_A), (15 - front[n] * 15));
            contribution_B = f(15) / (f(front[n] * 15) * f(15 - front[n] * 15)) * pow(prob_B, (front[n] * 15)) * pow((1 - prob_B), (15 - front[n] * 15));
            contribution_C = f(15) / (f(front[n] * 15) * f(15 - front[n] * 15)) * pow(prob_C, (front[n] * 15)) * pow((1 - prob_C), (15 - front[n] * 15));
            weight_A[n] = contribution_A / (contribution_A + contribution_B + contribution_C);
            weight_B[n] = contribution_B / (contribution_A + contribution_B + contribution_C);
            weight_C[n] = contribution_C / (contribution_A + contribution_B + contribution_C);
            num_AH[n] = weight_A[n] * front[n] * 15;
            num_BH[n] = weight_B[n] * front[n] * 15;
            num_CH[n] = weight_C[n] * front[n] * 15;
            num_AT[n] = weight_A[n] * (1 - front[n]) * 15;
            num_BT[n] = weight_B[n] * (1 - front[n]) * 15;
            num_CT[n] = weight_C[n] * (1 - front[n]) * 15;
        }
        double sum_AH = 0; double sum_BH = 0; double sum_CH = 0;
        double sum_AT = 0; double sum_BT = 0; double sum_CT = 0;
        for (int n = 0; n <=9; n++) {
            sum_AH += num_AH[n];
            sum_BH += num_BH[n];
            sum_CH += num_CH[n];
            sum_AT += num_AT[n];
            sum_BT += num_BT[n];
            sum_CT += num_CT[n];
        }
        prob_A = sum_AH / (sum_AH + sum_AT);
        prob_B = sum_BH / (sum_BH + sum_BT);
        prob_C = sum_CH / (sum_CH + sum_CT);
    }

    cout << "prob_A:" << prob_A << " ";
    cout << "prob_B:" << prob_B << " ";
    cout << "prob_C:" << prob_C << " ";
    cout << "\n";
}
