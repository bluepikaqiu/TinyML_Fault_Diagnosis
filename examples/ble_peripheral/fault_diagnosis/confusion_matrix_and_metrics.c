#include <stdio.h>
#include "arm_math.h"
#include "fault_diagnosis/confusion_matrix_and_metrics.h"

void fill_confusion_matrix(uint8_t y_true[], uint8_t y_pred[], uint8_t n, ClassificationReport* report) {
    //Initialize the confusion matrix to 0
    for (int i = 0; i < NUM_CLASSES; i++) {
        for (int j = 0; j < NUM_CLASSES; j++) {
            report->confusion_matrix[i][j] = 0;
        }
    }
    //Filling matrix
    for (int k = 0; k < n; k++) {
        int true_class = y_true[k];
        int pred_class = y_pred[k];
        report->confusion_matrix[true_class][pred_class]++;
    }
}

void calculate_metrics(ClassificationReport* report) {
    int total_samples = 0;
    //Calculate the number of supports and the total sample size
    for (int i = 0; i < NUM_CLASSES; i++) {
        report->support[i] = 0;
        for (int j = 0; j < NUM_CLASSES; j++) {
            report->support[i] += report->confusion_matrix[i][j];
        }
        total_samples += report->support[i];
    }

    //Calculate the Precision, Recall and F1 of each category
    for (int i = 0; i < NUM_CLASSES; i++) {
        int tp = report->confusion_matrix[i][i];
        int fp = 0, fn = 0;

        //Calculate FP (the sum of non-diagonal elements in the i-th column)
        for (int j = 0; j < NUM_CLASSES; j++) {
            if (j != i) fp += report->confusion_matrix[j][i];
        }

        //Calculate FN (the sum of non-diagonal elements in the i-th row)
        for (int j = 0; j < NUM_CLASSES; j++) {
            if (j != i) fn += report->confusion_matrix[i][j];
        }

        //Avoid division by zero errors
        report->precision[i] = (tp + fp == 0) ? 0 : (float32_t)tp / (tp + fp);
        report->recall[i] = (tp + fn == 0) ? 0 : (float32_t)tp / (tp + fn);
        report->f1_score[i] = (report->precision[i] + report->recall[i] == 0) ? 0 :
            2 * (report->precision[i] * report->recall[i]) / (report->precision[i] + report->recall[i]);
    }

    //Calculate the macro average and the weighted average
    float32_t sum_precision = 0, sum_recall = 0, sum_f1 = 0;
    float32_t weighted_precision = 0, weighted_recall = 0, weighted_f1 = 0;
    for (int i = 0; i < NUM_CLASSES; i++) {
        sum_precision += report->precision[i];
        sum_recall += report->recall[i];
        sum_f1 += report->f1_score[i];

        weighted_precision += report->precision[i] * report->support[i];
        weighted_recall += report->recall[i] * report->support[i];
        weighted_f1 += report->f1_score[i] * report->support[i];
    }

    //Macro average
    report->macro_avg[0] = sum_precision / NUM_CLASSES;
    report->macro_avg[1] = sum_recall / NUM_CLASSES;
    report->macro_avg[2] = sum_f1 / NUM_CLASSES;

    //Weighted average
    report->weighted_avg[0] = weighted_precision / total_samples;
    report->weighted_avg[1] = weighted_recall / total_samples;
    report->weighted_avg[2] = weighted_f1 / total_samples;

    //Calculate the accuracy rate
    int correct = 0;
    for (int i = 0; i < NUM_CLASSES; i++) {
        correct += report->confusion_matrix[i][i];
    }
    report->accuracy = (float32_t)correct / total_samples;
}