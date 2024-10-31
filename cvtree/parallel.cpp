//
// Created by Hunter on 30/10/2024.
//
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "cvtree.h"

double CompareBacteria_parallel(Bacteria *b1, Bacteria *b2) {
    double correlation = 0;
    double vector_len1 = 0;
    double vector_len2 = 0;
    long p1 = 0;
    long p2 = 0;
    while (p1 < b1->count && p2 < b2->count) {
        long n1 = b1->ti[p1];
        long n2 = b2->ti[p2];
        if (n1 < n2) {
            double t1 = b1->tv[p1];
            vector_len1 += (t1 * t1);
            p1++;
        } else if (n2 < n1) {
            double t2 = b2->tv[p2];
            p2++;
            vector_len2 += (t2 * t2);
        } else {
            double t1 = b1->tv[p1++];
            double t2 = b2->tv[p2++];
            vector_len1 += (t1 * t1);
            vector_len2 += (t2 * t2);
            correlation += t1 * t2;
        }
    }
    while (p1 < b1->count) {
        long n1 = b1->ti[p1];
        double t1 = b1->tv[p1++];
        vector_len1 += (t1 * t1);
    }
    while (p2 < b2->count) {
        long n2 = b2->ti[p2];
        double t2 = b2->tv[p2++];
        vector_len2 += (t2 * t2);
    }

    return correlation / (sqrt(vector_len1) * sqrt(vector_len2));
}

void CompareAllBacteria_parallel() {
    Bacteria **b = new Bacteria *[number_bacteria];

#pragma omp parallel for
    for (int i = 0; i < number_bacteria; i++) {
        printf("load %d of %d\n", i + 1, number_bacteria);
        b[i] = new Bacteria(bacteria_name[i]);
    }

#pragma omp parallel for collapse(2)
    for (int i = 0; i < number_bacteria - 1; i++)
        for (int j = i + 1; j < number_bacteria; j++) {
            printf("%2d %2d -> ", i, j);
            double correlation = CompareBacteria(b[i], b[j]);
            printf("%.20lf\n", correlation);
        }
}
