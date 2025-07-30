import random
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import loadmat

plt.rcParams['font.sans-serif'] = ['SimHei']


class FCM:
    def __init__(self, data, clust_num, iter_num=30):
        self.data = data
        self.cnum = clust_num
        self.sample_num = data.shape[0]
        self.dim = data.shape[-1]
        J_list = []
        
        A = self.Initial_A(self.sample_num, self.cnum)
        for i in range(0, iter_num):
            B = self.Cen_Iter(self.data, A, self.cnum)
            A = self.A_Iter(A, B)
            print("The %d th iteration " %(i+1), end="")
            print("cluster center", B)
            J = self.J_calcu(self.data, A, B)
            J_list = np.append(J_list, J)
        
        self.label = np.argmax(A, axis=0)
        self.Clast = B
        self.J_list = J_list
    
    #Initialize the mmembership matrix
    def Initial_A(self, sample_num, cluster_n):
        A = np.random.rand(sample_num, cluster_n) #(sample_num, cluster_n)
        row_sum = np.sum(A, axis=1)
        row_sum = 1 / row_sum
        A = np.multiply(A.T, row_sum) #Make sure thoe column of A is 1
        return A
    
    #Compute the cluster center
    def Cen_Iter(self, data, A, cluster_n):
        m = 2
        c_new = np.empty(shape=[0, self.dim])
        for i in range(0, cluster_n):
            A_ij_m = A[i, :] ** m
            sum_a = np.sum(A_ij_m)
            a_temp = np.reshape(np.dot(A_ij_m, data),(1, self.dim))
            c_new = np.append(c_new, a_temp / sum_a, axis = 0) #(cluster_n, self.dim)
        return c_new
    
    #The iteration of membership matrix
    def A_Iter(self, A, B):
        m = 2
        for i in range(0, self.cnum):
            for j in range(0, self.sample_num):
                sum = 0
                for k in range(0, self.cnum):
                    temp = (np.linalg.norm(self.data[j, :] - B[i, :]) /
                            np.linalg.norm(self.data[j, :] - B[k, :])) ** (2 / (m - 1))
                    sum = temp + sum
                A[i, j] = 1 / sum
        return A
    
    #Calculate the target value
    def J_calcu(self, data, A, B):
        m = 2
        temp1 = np.zeros(A.shape)
        for i in range(0, A.shape[0]):
            for j in range(0, A.shape[1]):
                temp1[i, j] = (np.linalg.norm(data[j, :] - B[i, :])) ** 2 * A[i, j] ** m
        
        J = np.sum(np.sum(temp1))
        print("The target value is:%.2f" % J)
        return J
    
    #Print the cluster result graph
    def plot(self):
        mark = ['or', 'ob', 'og', 'om', 'oy', 'oc']
        color = ['c', 'b', 'g', 'r', 'm', 'y', 'k', 'w']
        if self.dim == 2:
            #第一张图
            plt.subplot(221)
            plt.plot(self.data[:, 0], self.data[:, 1], 'ob', markersize=2)
            plt.title("未聚类前散点图")

            #第二张图
            plt.subplot(2, 2, 2)
            j = 0
            for i in self.label:
                plt.plot(self.data[j:j+1, 0], self.data[j:j+1, 1], mark[i], markersize=2)
                j = j + 1
            plt.plot(self.Clast[:, 0], self.Clast[:, 1], 'k*', markersize=7)
            plt.title("聚类后的结果")

            #第三张图
            plt.subplot(2, 1, 2)
            plt.plot(self.J_list, 'g-')
            plt.title("目标函数变化图")
            plt.show()

        if self.dim==3:
            # 第一张图
            fig = plt.figure()
            ax1 = fig.add_subplot(221, projection='3d')
            ax1.scatter(self.data[:, 0], self.data[:, 1],self.data[:,2], "b")
            ax1.set_xlabel("X 轴")
            ax1.set_ylabel("Y 轴")
            ax1.set_zlabel("Z 轴")
            plt.title("未聚类前的图")

            # 第二张图
            ax2 = fig.add_subplot(222, projection='3d')
            j = 0
            for i in self.label:
                ax2.scatter(self.data[j:j+1, 0], self.data[j:j+1, 1],self.data[j:j+1,2], s=7, c=color[i])
                j += 1
            ax2.scatter(self.Clast[:, 0], self.Clast[:, 1], self.Clast[:, 2], 'k*', label='聚类中心', s=8)
            plt.legend()
            ax2.set_xlabel("X 轴")
            ax2.set_ylabel("Y 轴")
            ax2.set_zlabel("Z 轴")
            plt.title("聚类后结果")
            # # 第三张图
            plt.subplot(223)
            plt.plot(self.J_list, 'g-', )
            plt.title("目标函数变化图", )
            plt.show()

""" file = 'C:\\Users\\Yanfeng\\Downloads\\Bearing_Data\\105.mat'
data = loadmat(file, mat_dtype=True)
X105_BA_time = data['X105_BA_time']
X105_DE_time = data['X105_DE_time']
X105_FE_time = data['X105_FE_time']
X105RPM = data['X105RPM']
data = np.hstack((X105_BA_time, X105_DE_time, X105_FE_time))"""
data = np.loadtxt('C:\\Users\\Yanfeng\\Downloads\\Bearing_Data\\FCM_train_data.txt', skiprows=1, dtype=np.float32)
print(data.shape)

""" N = 1000
C = [[N/4, N/2], [N/2, N], [N/4, N/2], [N/2, N]]
data = []
for i in range(4):
    center = random.randint(20, 50)
    for j in range(center):
        change = random.randint(20, 100)
        x = random.randint(C[i][0] + change, C[i][1] - change)
        y = random.randint(C[i][0] + change + 1, C[i][1] - change + 1)
        data.append([x, y]) """

data = np.mat(data)
a = FCM(data, 4, 50)
a.plot()