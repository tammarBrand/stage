#include "capture.h"
#include "Queue.h"

void* capture(void* arg){

    int** matrix;
    matrix=(int**)malloc(sizeof(int *)*SNAPSHOT_HEIGHT);
    for(int i=0;i<SNAPSHOT_HEIGHT;i++)  {
        matrix[i]=NULL;
        matrix[i]=(int *)malloc(sizeof(int)*SNAPSHOT_WIDTH);
    }
    randMat(matrix);
    printf("capture %d\n",matrix[0][0]);
    return matrix;
}

