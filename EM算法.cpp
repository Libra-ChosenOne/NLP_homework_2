//������A,B,C����Ӳ�ң����ڵõ��������в�û��Ӳ���������Ϣ��Ӳ�����泯�ϵ���Ϣ
#include <iostream>
#include "math.h"
#include <cstdlib>
using namespace std;

//���ڽ׳˵ĺ���
constexpr int f(int i) {
    return i < 2 ? 1 : i * f(i - 1);
}

int main() {
    srand((unsigned)time(NULL));
    //�õ���Ӳ������չʾ
    int samples[10][15] = {0};
   
    for (int a =0; a <= 9; a++)
    {
        if (a<5)         //A������Ϊ������ʮ��֮��
        {
            for (int b = 0; b <= 14; b++)
            {
           
                if (rand() % 4 == 0)
                {
                    samples[a][b] = 0;
                }
                else
                {
                    samples[a][b] = 1;    //A�ĳ��ϵĸ����ķ�֮��
                }
            }
        }

         if ((a>4)&&(a<7))         //B������Ϊ������ʮ��֮��
        {
            for (int b = 0; b <= 14; b++)
            {

                if (rand() % 4 == 0)
                {
                    samples[a][b] = 0;
                }
                else
                {
                    samples[a][b] = 1;    //B�ĳ��ϵĸ����ķ�֮��
                }

            }
        }

        if (a>6)         //C������Ϊ������ʮ��֮��
        {
            for (int b = 0; b <= 14; b++)
            {
                if (rand() % 3 == 0)
                {
                    samples[a][b] = 1;  //C�ĳ��ϵĸ�������֮һ
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
    //��ʼ��A,B,C����Ӳ�ҵĳ��ϸ���
    double prob_A = 0.9; double prob_B = 0.55; double prob_C = 0.2;
    double front[10];//front[i]��ʾ���ڵ�i�飬Ӳ�ҳ��ϵĸ���
    //���ݵõ������ݣ����front
    for (int j = 0; j <=9; j++) {
        front[j] = 0;
        for (int k = 0; k < 15; k++) {
            front[j] += samples[j][k];
        }
        front[j] = front[j] / 15;
    }
    //����ѭ��2000�κ��ܹ��õ���Ϊ��ȷ�Ľ�
    for (int i = 0; i < 500; i++) {
        //�����i��Ӳ��ΪAΪB����ΪC�ĸ���
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
