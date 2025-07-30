import numpy as np

with open('C:/Users/Yanfeng/Downloads/Bearing_Data/real_dataset_acc_source.txt','r') as f1, open('C:/Users/Yanfeng/Downloads/Bearing_Data/real_dataset_acc_source_process.txt','w+') as f2:
    line = f1.readlines()
    for line_list in line:
        line_new = line_list.replace(' ','')
        line_new = line_new.replace('\n',',') 
        f2.writelines(line_new + '\n')
        

