# TinyML_Fault_Diagnosis
A TinyML edge MCU fault diagnosis solution based on the CMSIS-DSP, CMSIS-NN, and TFLM frameworks



## IDE and Toolchain Environment

​		The selected low-cost/low-performance MCU development board for the project is **Nordic NRF52840 DK**(**ARM Cortex-M4, 1MB Flash, 256KB RAM, SDK Version：17.1.0**)

​		The IDE software used in this project is **Keil u5** and **SEGGER Embedded Studio V8.24**.



**Tensorflow Version：2.13.1**

**CMSIS CORE Version：5.6.0**

**CMSIS-DSP Version：1.14.4**

**CMSIS-NN Version：5.0.0**

**Device Startup Version：8.52.0**

**ARMCLANG v6.16（Keil）**

**GCC（SEGGER Embedded Studio）**



### Multi-Spectral Feature Extraction Layer（MSFE）

![Github_MSFE](https://github.com/bluepikaqiu/TinyML_Fault_Diagnosis/tree/main/Screenshots/Github_MSFE.png?raw=true)



### Classifer

​		Selected lightweight-CNN methods and classic ML methods (such as SVM， Gaussian Naive Bayes，Clustering，and so on)



### Dataset and experimental platform

#### CWRU Bearing Datasets

**Test bench**

![Github_CWRU_test_rig](https://github.com/bluepikaqiu/TinyML_Fault_Diagnosis/tree/main/Screenshots/Github_CWRU_test_rig.png?raw=true)

DE - drive end accelerometer data

FE - fan end accelerometer data

BA - base accelerometer data

time - time series data

RPM - rpm during testing

![Github_CWRU_Data](https://github.com/bluepikaqiu/TinyML_Fault_Diagnosis/tree/main/Screenshots/Github_CWRU_Data.png?raw=true)



**Result**

![Github_0HP_1797RPM_10C_ML_Methods_Metrics](https://github.com/bluepikaqiu/TinyML_Fault_Diagnosis/tree/main/Screenshots/Github_0HP_1797RPM_10C_ML_Methods_Metrics.png?raw=true)

![Github_1HP_1772RPM_10C_ML_Methods_Metrics](https://github.com/bluepikaqiu/TinyML_Fault_Diagnosis/tree/main/Screenshots/Github_1HP_1772RPM_10C_ML_Methods_Metrics.png?raw=true)

![Github_2HP_1750RPM_10C_ML_Methods_Metrics](https://github.com/bluepikaqiu/TinyML_Fault_Diagnosis/tree/main/Screenshots/Github_2HP_1750RPM_10C_ML_Methods_Metrics.png?raw=true)

![Github_FLASH_RAM_Inferring_Time_ML_Methods](https://github.com/bluepikaqiu/TinyML_Fault_Diagnosis/tree/main/Screenshots/Github_FLASH_RAM_Inferring_Time_ML_Methods.png?raw=true)

![Github_TFLM_VS_TFLM-CMSIS-NN_FLASH](https://github.com/bluepikaqiu/TinyML_Fault_Diagnosis/tree/main/Screenshots/Github_TFLM_VS_TFLM-CMSIS-NN_FLASH.png?raw=true)

![Github_TFLM_VS_TFLM-CMSIS-NN_RAM](https://github.com/bluepikaqiu/TinyML_Fault_Diagnosis/tree/main/Screenshots/Github_TFLM_VS_TFLM-CMSIS-NN_RAM.png?raw=true)

![Github_TFLM_VS_TFLM-CMSIS-NN_Inferring_Time](https://github.com/bluepikaqiu/TinyML_Fault_Diagnosis/tree/main/Screenshots/Github_TFLM_VS_TFLM-CMSIS-NN_Inferring_Time.png?raw=true)

**Still under improvement**

#### SKF Bearing Datasets

**Not yet completed**

#### XJTU-SY Bearing Datasets

**Not yet completed**

####  SKF Gearbox Datasets

**Not yet completed**



