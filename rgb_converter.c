#include "rgb_converter.h"


void* rgb_converter(void* arg){
    int** matrix=(int**)arg;
    char *rgb_matrix=NULL;
    printf("rgb \n");
    rgb_matrix=(char *)calloc(sizeof(char)*(SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH*3),sizeof(char));

    covert_to_rgb(rgb_matrix,matrix);
    free_matrix(matrix);
    return rgb_matrix;

}




