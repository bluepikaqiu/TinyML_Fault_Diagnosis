#ifndef __CONFUSION_MATRIX_AND_METRICS_H__
#define __CONFUSION_MATRIX_AND_METRICS_H__

#include "arm_math.h"

#define NUM_CLASSES 10  // labels

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    int confusion_matrix[NUM_CLASSES][NUM_CLASSES];  //10x10 confusion matrix
    float32_t precision[NUM_CLASSES];                   //the precision rate of each category
    float32_t recall[NUM_CLASSES];                       //the recall rate of each category
    float32_t f1_score[NUM_CLASSES];                     //the recall rate of each label
    int support[NUM_CLASSES];                         //the number of supports for each label
    float32_t macro_avg[3];                              //macro averagePrecision/Recall/F1)
    float32_t weighted_avg[3];                           //weighted average/Recall/F1)
    float32_t accuracy;                                   //overall accuracy rate
} ClassificationReport;

void fill_confusion_matrix(uint8_t y_true[], uint8_t y_pred[], uint8_t n, ClassificationReport* report);
void calculate_metrics(ClassificationReport* report);

#ifdef __cplusplus
}
#endif

#endif
