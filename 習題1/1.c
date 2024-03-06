#include <stdio.h>
#include <stdlib.h>

// 结构体表示矩阵
typedef struct {
    int rows;
    int cols;
    double **data; // 二维数组用于存储矩阵数据
} Matrix;

// 创建一个新的矩阵
Matrix *createMatrix(int rows, int cols) {
    Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;

    // 分配内存以存储矩阵数据
    mat->data = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        mat->data[i] = (double *)malloc(cols * sizeof(double));
    }

    return mat;
}

// 释放矩阵占用的内存
void freeMatrix(Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

// 转置矩阵
Matrix *transposeMatrix(Matrix *mat) {
    Matrix *transposed = createMatrix(mat->cols, mat->rows);

    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            transposed->data[j][i] = mat->data[i][j];
        }
    }

    return transposed;
}

// 矩阵相加
Matrix *addMatrix(Matrix *mat1, Matrix *mat2) {
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        printf("Error: Matrices dimensions do not match for addition.\n");
        return NULL;
    }
    Matrix *result = createMatrix(mat1->rows, mat1->cols);
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            result->data[i][j] = mat1->data[i][j] + mat2->data[i][j];
            // printf("%d %d:%.2f\n", i, j, result->data[i][j]);
        }
    }

    return result;
}

// 矩阵相乘
Matrix *multiplyMatrix(Matrix *mat1, Matrix *mat2) {
    if (mat1->cols != mat2->rows) {
        printf("Error: Matrices dimensions do not match for multiplication.\n");
        return NULL;
    }

    Matrix *result = createMatrix(mat1->rows, mat2->cols);

    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat2->cols; j++) {
            double sum = 0;
            for (int k = 0; k < mat1->cols; k++) {
                sum += mat1->data[i][k] * mat2->data[k][j];
            }
            result->data[i][j] = sum;
        }
    }

    return result;
}

// 打印矩阵
void printMatrix(Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%.2f\t", mat->data[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Matrix *mat1 = createMatrix(2, 3);
    Matrix *mat2 = createMatrix(3, 2);

    // 初始化矩阵数据
    mat1->data[0][0] = 1; mat1->data[0][1] = 2; mat1->data[0][2] = 3;
    mat1->data[1][0] = 4; mat1->data[1][1] = 5; mat1->data[1][2] = 6;

    mat2->data[0][0] = 7; mat2->data[0][1] = 8;
    mat2->data[1][0] = 9; mat2->data[1][1] = 10;
    mat2->data[2][0] = 11; mat2->data[2][1] = 12;

    printf("Matrix 1:\n");
    printMatrix(mat1);
    printf("\nMatrix 2:\n");
    printMatrix(mat2);

    Matrix *transposed1 = transposeMatrix(mat1);
    printf("\nTransposed Matrix 1:\n");
    printMatrix(transposed1);

    Matrix *transposed2 = transposeMatrix(mat2);
    printf("\nTransposed Matrix 2:\n");
    printMatrix(transposed2);

    Matrix *sum = addMatrix(mat1, transposed2);
    printf("\nMatrix Sum:\n");
    printMatrix(sum);

    Matrix *product = multiplyMatrix(mat1, mat2);
    printf("\nMatrix Product:\n");
    printMatrix(product);

    // 释放内存
    freeMatrix(mat1);
    freeMatrix(mat2);
    freeMatrix(transposed1);
    freeMatrix(transposed2);
    freeMatrix(sum);
    freeMatrix(product);

    return 0;
}
