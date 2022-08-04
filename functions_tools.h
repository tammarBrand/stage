#pragma once
#ifndef FUNCTIONS_TOOLS_H
#define FUNCTIONS_TOOLS_H
#define SNAPSHOT_HEIGHT 240
#define SNAPSHOT_WIDTH 360
#define MAX_TEMP 30
#include <stdio.h>
#include <stdlib.h>

enum status_bits{
    INIT=1,
    PIPE_START=2,
    PIPE_STOP=4,
    SNAPSHOT=8,
   /* CAPTURE=16,
    RGB_CONVERTER=32,
    YUV_CONVERTER=64,
    ENCODE=128,
    WRITE_RECORD=256
    */
};



static char  rgb_per_temp[MAX_TEMP*3];

typedef struct yuv{
    char y[SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH];
    char u[SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH/4];
    char v[SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH/4];
}YUV;

typedef struct ppm_image{
    int width;
    int height;
    char *data;
    size_t size;
    char * name;
} ppm_image;
void init_rgb_matrix();
void randMat(int** matrix_temp);
void covert_to_rgb(char rgb_matrix[],int** matrix);
void convert_to_yuv(char rgb_matrix[],  YUV* yuv);
void free_matrix(int** m);
void free_rgb_matrix(char * m);

#endif // FUNCTIONS_TOOLS_H
