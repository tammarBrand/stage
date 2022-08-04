#include <stdio.h>
#include <pthread.h>

#include "stage.h"
#include "rgb_converter.h"


#include "yuv_converter.h"
#include "encode.h"
#include "write_record.h"
#include "capture.h"
//#include "functions_tools.h"

void main(int argc, char *argv[])
{
    pthread_t p1,p2,p3,p4,p5;
    Queue* q1=createQueue(10);
    Queue* q2=createQueue(10);
    Queue* q3=createQueue(10);
    Queue* q4=createQueue(10);

    stage* st5=create_stage(q4,NULL,write_record,NULL);
    stage* st4=create_stage(q3,q4,encode,st5);
    stage* st3=create_stage(q2,q3,yuv_converter,st4);
    stage* st2=create_stage(q1,q2,rgb_converter,st3);
    stage* st1=create_stage(NULL,q1,capture,st2);
    init_rgb_matrix();

    pthread_create(&p1,NULL,main_stage_thread, st1);
    pthread_create(&p2,NULL,main_stage_thread, st2);
    pthread_create(&p3,NULL,main_stage_thread, st3);
    pthread_create(&p4,NULL,main_stage_thread, st4);
    pthread_create(&p5,NULL,main_stage_thread, st5);

    sleep(3);
    stop_stage(st1);

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(p3,NULL);
    pthread_join(p4,NULL);
    pthread_join(p5,NULL);
    free(st1);free(st2);free(st3);free(st4);free(st5);
    freeQueue(q1); freeQueue(q2); freeQueue(q3); freeQueue(q4);



}
