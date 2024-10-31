//
// Created by Hunter on 30/10/2024.
//
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "cvtree.h"

Bacteria_parallel::Bacteria_parallel(char *filename) : Bacteria(filename) {
    FILE *bacteria_file;
    errno_t OK = fopen_s(&bacteria_file, filename, "r");

    if (OK != 0) {
        fprintf(stderr, "Error: failed to open file %s\n", filename);
        exit(1);
    }

    InitVectors();

    char ch;
    while ((ch = fgetc(bacteria_file)) != EOF) {
        if (ch == '>') {
            while (fgetc(bacteria_file) != '\n'); // skip rest of line

            char buffer[LEN - 1];
            fread(buffer, sizeof(char), LEN - 1, bacteria_file);
            init_buffer(buffer);
        } else if (ch != '\n') cont_buffer(ch);
    }

    long total_plus_complement = total + complement;
    double total_div_2 = total * 0.5;
    int i_mod_aa_number = 0;
    int i_div_aa_number = 0;
    long i_mod_M1 = 0;
    long i_div_M1 = 0;

    double one_l_div_total[AA_NUMBER];
    for (int i = 0; i < AA_NUMBER; i++) one_l_div_total[i] = (double) one_l[i] / total_l;

    double *second_div_total = new double[M1];
    for (int i = 0; i < M1; i++) second_div_total[i] = (double) second[i] / total_plus_complement;

    count = 0;
    double *t = new double[M];

    for (long i = 0; i < M; i++) {
        double p1 = second_div_total[i_div_aa_number];
        double p2 = one_l_div_total[i_mod_aa_number];
        double p3 = second_div_total[i_mod_M1];
        double p4 = one_l_div_total[i_div_M1];
        double stochastic = (p1 * p2 + p3 * p4) * total_div_2;

        if (i_mod_aa_number == AA_NUMBER - 1) {
            i_mod_aa_number = 0;
            i_div_aa_number++;
        } else i_mod_aa_number++;

        if (i_mod_M1 == M1 - 1) {
            i_mod_M1 = 0;
            i_div_M1++;
        } else i_mod_M1++;

        if (stochastic > EPSILON) {
            t[i] = (vector[i] - stochastic) / stochastic;
            count++;
        } else t[i] = 0;
    }

    delete second_div_total;
    delete vector;
    delete second;

    tv = new double[count];
    ti = new long[count];

    int pos = 0;
    for (long i = 0; i < M; i++) {
        if (t[i] != 0) {
            tv[pos] = t[i];
            ti[pos] = i;
            pos++;
        }
    }
    delete t;

    fclose(bacteria_file);
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
