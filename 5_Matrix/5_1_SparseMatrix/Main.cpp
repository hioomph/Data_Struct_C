#include"SparseMatrix.h"

int main()
{
    SparseMatrix sm, sm1, sm2, mt;
    memset(&sm, 0, sizeof(sm));
    memset(&sm1, 0, sizeof(sm1));
    memset(&sm2, 0, sizeof(sm2));
    memset(&mt, 0, sizeof(mt));

    CreateMatrix(&sm, "Matrix.txt");
    CreateMatrix(&sm1, "Matrix1.txt");
    CreateMatrix(&sm2, "Matrix2.txt");
    // PrintMatrix(&sm);

    // CopyMatrix(&sm, &sm1);
    // PrintMatrix(&sm1);

    // AddMatrix(&sm, &sm1, &mt);
    // PrintMatrix(&mt);

    // SubMatrix(&sm, &sm1, &mt);
    // PrintMatrix(&mt);


    // MulMatrix(&sm1, &sm2, &mt);
    // PrintMatrix(&mt);

    PrintMatrix(&sm1);
    // TransposeMatrix(&sm1, &mt);
    FastTransposeMatrix(&sm1, &mt);
    PrintMatrix(&mt);


    printf("ok");
}