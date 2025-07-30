#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Mode
{
    int x = 0;
    int y = 0;
    int di = 0;
    vector<double> datas;
};
typedef vector<vector<Mode>> ModeVec;
const int N = 4096;
const double eps = 1e-2;
const double eps_dis = 1e-6;

double getDistance(Mode& m1, Mode& m2);
void FCM(Mode* p, int n, int di, int clusternum, vector<vector<Mode> >& ans);
void init_c(Mode* p, int n, int clusternum, Mode* c);
void comp_dis(Mode* p, Mode* c, int n, int clusternum, double dis[][4]); // 4 意味着最终聚类簇数
void comp_u(double dis[][4], int n, int clusternum, double u[][4]);
void update_c(Mode* p, double u[][4], int n, int clusternum, Mode* c);
double comp_obj_func(double u[][4], double dis[][4], int n, int clusternum, int di);

int main(void)
{
    int n, dimension, clusternum;
    Mode p[N];
    //freopen("C:/Users/Yanfeng/Downloads/Bearing_Data/FCM_train_data.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ifstream fin("C:/Users/Yanfeng/Downloads/Bearing_Data/FCM_train_data.txt");
    fin >> n >> dimension >> clusternum;  //输入点的个数，维度，聚类数目
    cout << n << ' ' << dimension << ' ' << clusternum << endl;
    for (int i = 0; i < n; i++)
    {
        p[i].di = dimension;
        for (int j = 0; j < dimension; j++)
        {
            double temp;
            fin >> temp;
            p[i].datas.push_back(temp);
        }
    }
    vector<vector<Mode>> ans;
    FCM(p, n, dimension, clusternum, ans);  //传入数组p，有n个点，维度为dimension，结果保存在ans
    for (int i = 0; i < clusternum; i++)
    {
        printf("The %d th class：\n", i + 1);
        for (int j = 0; j < ans[i].size(); j++)
        {
            printf("(");
            for (int k = 0; k < dimension; k++)
            {
                if (k == 0)
                {
                    printf("%f", ans[i][j].datas[k]);
                }
                else
                {
                    printf(",%f", ans[i][j].datas[k]);
                }
            }
            printf(")\n");
        }
    }
    return 0;
}

double getDistance(Mode& m1, Mode& m2)
{
    int di = m1.di;
    double ans = 0;
    for (int i = 0; i < di; i++)
        ans += (m1.datas[i] - m2.datas[i]) * (m1.datas[i] - m2.datas[i]);
    return ans;
}

void init_c(Mode* p, int n, int clusternum, Mode* c) //初始化聚类中心
{
    int di = p[0].di;
    srand(time(NULL));
    for (int i = 0; i < clusternum; i++)
    {
        c[i].di = di;
        c[i].datas.clear();
        for (int j = 0; j < di; j++)
            c[i].datas.push_back(0);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < di; j++)
            for (int k = 0; k < clusternum; k++)
                c[k].datas[j] += p[i].datas[j];
    for (int i = 0; i < clusternum; i++)
    {
        for (int j = 0; j < di; j++)
        {
            int tp = rand() % n + 1;
            c[i].datas[j] /= tp;
        }
    }
}

void comp_dis(Mode* p, Mode* c, int n, int clusternum, double dis[][4]) //初始化每个点和每个簇的距离
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < clusternum; j++)
            dis[i][j] = getDistance(p[i], c[j]);
}

void comp_u(double dis[][4], int n, int clusternum, double u[][4])  //计算隶属度矩阵
{
    for (int i = 0; i < n; i++)
    {
        double tp = 0;
        for (int j = 0; j < clusternum; j++)
        {
            if (dis[i][j] < eps_dis)  //如果这个点很接近一个簇类中心，那么这个隶属度设为1，其他为0
            {
                for (int k = 0; k < clusternum; k++)
                    u[i][k] = 0;
                u[i][j] = 1;
                return;
            }
            tp += 1 / dis[i][j];
        }
        tp = 1 / tp;
        for (int j = 0; j < clusternum; j++)
            u[i][j] = tp * (1 / dis[i][j]);
    }
}

void update_c(Mode* p, double u[][4], int n, int clusternum, Mode* c)
{
    int di = p[0].di;
    for (int j = 0; j < clusternum; j++)
    {
        c[j].di = di;
        c[j].datas.clear();
        for (int i = 0; i < di; i++)
            c[j].datas.push_back(0);
        double tp = 0;
        for (int i = 0; i < n; i++)
        {
            for (int k = 0; k < di; k++)
                c[j].datas[k] += u[i][j] * u[i][j] * p[i].datas[k];
            tp += u[i][j] * u[i][j];
        }
        for (int k = 0; k < di; k++)
            c[j].datas[k] /= tp;
    }
}

double comp_obj_func(double u[][4], double dis[][4], int n, int clusternum, int di)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < clusternum; j++)
            sum += u[i][j] * u[i][j] * dis[i][j];
    return sum;
}

void FCM(Mode* p, int n, int di, int clusternum, vector<vector<Mode>>& ans)        //in: n,d,c       time:O(c*n*d) 时间复杂度=聚类数*点数*维数
{
    int index = 0;
    double sum = 0, psum;
    Mode c[4]; //聚类中心
    double dis[N][4]; //距离
    double u[N][4];  //隶属度矩阵
    init_c(p, n, clusternum, c); // 初始化聚类中心  time: O(c)
    comp_dis(p, c, n, clusternum, dis); //更新距离矩阵dis
    while (1)
    {
        index++;
        //printf("第%d次循环----------------------------------------\n", index);
        comp_u(dis, n, clusternum, u);  //计算隶属度矩阵u  time:O(n*c);
        for (int i = 0; i < n; i++)
        {
            //printf("第%d个点的隶属值\n", i + 1);
            for (int j = 0; j < clusternum; j++)
            {
                //printf("%f ", u[i][j]);
            }
            //printf("\n");
        }
        update_c(p, u, n, clusternum, c);   //更新聚类中心 time:O(c*(2*d+(n*d))) = O(c*n*d)
        comp_dis(p, c, n, clusternum, dis); //重新计算距离矩阵
        psum = sum;
        sum = comp_obj_func(u, dis, n, clusternum, di);
        //printf("函数值=%f\n", sum);
        if (fabs(psum - sum) < eps)
            break;
    }
    for (int i = 0; i < clusternum; i++)
    {
        vector<Mode> m;
        ans.push_back(m);
    }
    for (int i = 0; i < n; i++)
    {
        double tp = -1;
        int index = 0;
        for (int j = 0; j < clusternum; j++)
        {
            if (u[i][j] > tp)
            {
                tp = u[i][j];
                index = j;
            }
        }
        ans[index].push_back(p[i]);
    }
}