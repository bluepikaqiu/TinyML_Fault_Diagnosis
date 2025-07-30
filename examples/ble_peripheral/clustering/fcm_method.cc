#include <iostream>
#include <cstdio>
#include <cstring>
#include <array>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <memory>
#include <vector>
#include "arm_math.h"
#include "nrf_delay.h"
#include "fcm_method.h"

using namespace std;

struct Mode
{
    int di = 0;
    int label;
    array<float32_t, 3> datas;
};

const int N = 2048;
const int dimension = 3;
const int clusternum = 4;
extern float32_t Mag_N[2048]; // magnitude N
extern float32_t Phase_N[2048]; // phase N 
extern float32_t f_integral_output[2048];
extern float32_t speed; // initial speed
array<array<Mode, N/2>, clusternum> ans;
//vector<vector<Mode>> ans;
array<array<float32_t, N>, clusternum> A;
array<array<float32_t, dimension>, clusternum> c_center = {{{1.01469471e+01, 1.38568052e+02, 1.98129630e-02},
									 {1.13365266e+01, 4.40655916e+01, 2.00618244e-02}, 
									 {1.11525853e+01, -5.24085909e+01, 2.01522509e-02}, 
									 {1.00686564e+01, -1.39919133e+02, 1.99355116e-02}}}; //初始化聚类中心
//const double eps = 1e-2;
//const double eps_dis = 1e-6;

void Membership_Matrix(Mode* test_data, int sample_num) {
    int i, j, k;
    float32_t m = 2.0;
    float32_t temp, sum;
	
    for (i = 0; i < clusternum; i++) 
    {
        for (j = 0; j < sample_num; j++) 
        {
            sum = 0.0;
            for (k = 0; k < clusternum; k++) 
            {
                temp = pow(
                    (sqrt(pow(test_data[j].datas[0] - c_center[i][0], 2) + pow(test_data[j].datas[1] - c_center[i][1], 2) + pow(test_data[j].datas[2] - c_center[i][2], 2)) /
                     sqrt(pow(test_data[j].datas[0] - c_center[k][0], 2) + pow(test_data[j].datas[1] - c_center[k][1], 2) + pow(test_data[j].datas[2] - c_center[k][2], 2))),
                     2 / (m - 1));
                sum += temp;
            }
            A[i][j] = 1.0 / sum;
        }
    }
}

void FCM(Mode* p, int sample_num)        //in: n,d,c       time:O(c*n*d) 时间复杂度=聚类数*点数*维数
{		
//		for (int i = 0; i < clusternum; i++)
//		{
//			vector<Mode> temp;
//			ans.push_back(temp);
//		}
    int i, j, k, s, sum = 0;
    int j0 = 0, j1 = 0, j2 = 0, j3 = 0; // static storage
    float32_t acc;
		
    for (int j = 0; j < sample_num; j++)
    {
        float32_t tp = 0;
        int index = 0;
        for (int i = 0; i < clusternum; i++)
        {
            if (A[i][j] >= tp)
            {
                  tp = A[i][j];
                  index = i;
            }
        }
    //				ans.at(index).push_back(Mode{dimension, {p[j].datas[0], p[j].datas[1], p[j].datas[2]}});
        if(index == 0) ans[index][j0++] = p[j];
        if(index == 1) ans[index][j1++] = p[j];
        if(index == 2) ans[index][j2++] = p[j];
        if(index == 3) ans[index][j3++] = p[j];
    //				ans[index].push_back(p[j]);
    //				printf("%d \n", ans[0].size());		
    //				nrf_delay_ms(50);
                
        //Compute the accuracy
        if(index == (p[j].label - 1)) sum++;
    }
        acc = static_cast<float32_t>(sum) / static_cast<float32_t>(sample_num);
        printf("The accuracy is : %f \n", acc);
        nrf_delay_ms(25);
		
        //Print the informatin about the final output
//		for (i = 0; i < clusternum; i++)
//    {
//				printf("The %d th class: \n", i + 1);
//				nrf_delay_ms(25);
//				if(i == 0) s = j0;
//				if(i == 1) s = j1;
//				if(i == 2) s = j2;
//				if(i == 3) s = j3;
//        for (j = 0; j < s; j++)
//        {
//            for (k = 0; k < dimension; k++)
//            {
//								printf("%f ", ans[i][j].datas[k]);		
//								nrf_delay_ms(25);
//            }
//						printf("\n");
//						nrf_delay_ms(25);
//        }
//    }
}

void FCM_Main(void)
{
    int i, j;				 
    int n = N;
    float32_t temp;  
    Mode p[N];

//    freopen("C:/Users/Yanfeng/Downloads/Bearing_Data/FCM_train_data.txt","r",stdin);
//    freopen("out.txt","w",stdout);
//    ifstream fin("C:/Users/Yanfeng/Downloads/Bearing_Data/FCM_train_data.txt");
//    fin >> n >> dimension >> clusternum;  //输入点的个数，维度，聚类数目
//		printf("n,dimension,clusternum:\n");
//		nrf_delay_ms(50);
//		cout << n << ' ' << dimension << ' ' << clusternum << endl;
//		nrf_delay_ms(50);

    for (i = 0; i < n; i++)
    {
        p[i].di = dimension;
        if(i / 512 == 0) p[i].label = 1; // label 1
        if(i / 512 == 1) p[i].label = 2; // label 1
        if(i / 512 == 2) p[i].label = 3; // label 1
        if(i / 512 == 3) p[i].label = 4; // label 1
				printf("label: %d\n", p[i].label);
        nrf_delay_ms(25);
        for (j = 0; j < p[i].di; j++)
        {
            if(j == 0) temp = Mag_N[i];
            if(j == 1) temp = Phase_N[i];
            if(j == 2) temp = f_integral_output[i] + speed;
            p[i].datas[j] = temp;
//						printf("%f ", p[i].datas[j]);
//						nrf_delay_ms(50);
        }
//				printf("example:%d \n", i);
//				nrf_delay_ms(50);
    }
    Membership_Matrix(p, n); //Get the membership matrix which already trained
    FCM(p, n);  //传入数组p，有n个点，维度为dimension，结果保存在ans
}
