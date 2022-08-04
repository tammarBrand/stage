#include "write_record.h"

void* write_record(void* arg){

    printf("write\n");

    YUV* yuv=(YUV*)arg;
    return yuv;


}
