#include <iostream>

#include "Classifier.h"

int main(int argc, char **argv)
{

    Classifier c;
    c.train(argv[1]);
    c.test(argv[2]);
    c.printToResultsFile(argv[4]);
    c.printToAccuracyFile(argv[3], argv[5]);

    return 0;
}