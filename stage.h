#pragma once
#ifndef STAGE_H
#define STAGE_H
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "functions_tools.h"

typedef struct record_t{
    char* file_name;
    int codec;
    int width;
    int height;
    int fps;
}record_t;

typedef struct snapshot_t{
    char* file_name;  //full path ?
    int width;
    int height;
    char* type;  //GPEG,PNG,ppm
    char *data;
}snapshot_t;

struct handler;
typedef void* (*function)(void*, struct handler*);

typedef struct stage{
    function func;
    pthread_t thread;
    Queue* sourseQu;
    Queue* destQu;
    int status_bit;
    bool is_active;
    struct stage* next;
}stage;

typedef struct handler{
    stage * head;
    int* status_bits;
    void* dest_data;
}handler;

typedef struct stage_params{
    stage* stage;
    handler* handler;
}stage_params;






void* create_stage(Queue* sourse, Queue* dest, function func,stage* next);
void stop_stage(stage* head_stage);
void* main_stage_thread(void* arg);

#endif // STAGE_H
