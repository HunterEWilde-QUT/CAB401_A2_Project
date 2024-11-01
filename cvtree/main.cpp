#include <iostream>
#include "cvtree.h"

int main(int argc, char *argv[]) {
    time_t t1 = time(NULL);

    Init();
    ReadInputFile("list.txt");
    CompareAllBacteria();
    //CompareAllBacteria_parallel();

    time_t t2 = time(NULL);
    printf("time elapsed: %lld seconds\n", t2 - t1);
    return 0;
}
