# TinyML_Fault_Diagnosis
A TinyML edge MCU fault diagnosis solution based on the CMSIS-DSP, CMSIS-NN, and TFLM frameworks



## IDE and Toolchain Environment

​		The selected MCU development board for the project is **Nordic NRF52840 DK**(**SDK Version：17.1.0**)

​		The IDE software used in this project is **Keil u5** and **SEGGER Embedded Studio V8.24**.



**Tensorflow Version：2.13.1**

**CMSIS CORE Version：5.6.0**

**CMSIS-DSP Version：1.14.4**

**CMSIS-NN Version：5.0.0**

**Device Startup Version：8.52.0**

**ARMCLANG v6.16（Keil）**

**GCC（SEGGER Embedded Studio）**



### Multi-Spectral Feature Extraction Layer（MSFE）

![Github_MSFE](C:\Users\Yanfeng\Downloads\Github_pictures\Github_MSFE.png)



### Classifer

​		Selected lightweight-CNN methods and classic ML methods (such as SVM， Gaussian Naive Bayes，Clustering，and so on)



### Dataset and experimental platform

#### CWRU Bearing Datasets

**Test bench**

![Github_CWRU_test_rig](C:\Users\Yanfeng\Downloads\Github_pictures\Github_CWRU_test_rig.png)

DE - drive end accelerometer data

FE - fan end accelerometer data

BA - base accelerometer data

time - time series data

RPM - rpm during testing

![Github_CWRU_Data](C:\Users\Yanfeng\Downloads\Github_pictures\Github_CWRU_Data.png)



**Result**

![Github_0HP_1797RPM_10C_ML_Methods_Metrics](C:\Users\Yanfeng\Downloads\Github_pictures\Github_0HP_1797RPM_10C_ML_Methods_Metrics.png)

![Github_1HP_1772RPM_10C_ML_Methods_Metrics](C:\Users\Yanfeng\Downloads\Github_pictures\Github_1HP_1772RPM_10C_ML_Methods_Metrics.png)

![Github_2HP_1750RPM_10C_ML_Methods_Metrics](C:\Users\Yanfeng\Downloads\Github_pictures\Github_2HP_1750RPM_10C_ML_Methods_Metrics.png)

![Github_FLASH_RAM_Inferring_Time_ML_Methods](C:\Users\Yanfeng\Downloads\Github_pictures\Github_FLASH_RAM_Inferring_Time_ML_Methods.png)

![Github_TFLM_VS_TFLM-CMSIS-NN_FLASH](C:\Users\Yanfeng\Downloads\Github_pictures\Github_TFLM_VS_TFLM-CMSIS-NN_FLASH.png)

![Github_TFLM_VS_TFLM-CMSIS-NN_RAM](C:\Users\Yanfeng\Downloads\Github_pictures\Github_TFLM_VS_TFLM-CMSIS-NN_RAM.png)

![Github_TFLM_VS_TFLM-CMSIS-NN_Inferring_Time](C:\Users\Yanfeng\Downloads\Github_pictures\Github_TFLM_VS_TFLM-CMSIS-NN_Inferring_Time.png)

**Still under improvement**

#### SKF Bearing Datasets

**Not yet completed**

#### XJTU-SY Bearing Datasets

**Not yet completed**

####  SKF Gearbox Datasets

**Not yet completed**



