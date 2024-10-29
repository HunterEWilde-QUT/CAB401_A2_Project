//
// Created by Hunter on 29/10/2024.
//

#ifndef CAB401_A2_PROJECT_CVTREE_H
#define CAB401_A2_PROJECT_CVTREE_H

int number_bacteria;
char** bacteria_name;
long M, M1, M2;
short code[27] = { 0, 2, 1, 2, 3, 4, 5, 6, 7, -1, 8, 9, 10, 11, -1, 12, 13, 14, 15, 16, 1, 17, 18, 5, 19, 3};
#define encode(ch)		code[ch-'A']
#define LEN				6
#define AA_NUMBER		20
#define	EPSILON			1e-010

void Init();

class Bacteria {
private:
    long *vector;
    long *second;
    long one_l[AA_NUMBER];
    long indexs;
    long total;
    long total_l;
    long complement;

    void InitVectors();

    void init_buffer(char *buffer);

    void cont_buffer(char ch);

public:
    long count;
    double *tv;
    long *ti;

    explicit Bacteria(char *filename);
};

void ReadInputFile(const char *input_name);

double CompareBacteria(Bacteria *b1, Bacteria *b2);

void CompareAllBacteria();

#endif //CAB401_A2_PROJECT_CVTREE_H
