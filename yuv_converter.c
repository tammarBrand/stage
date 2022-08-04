#include "yuv_converter.h"

void* yuv_converter(void* arg){
    char*rgb_matrix=(char*)arg;


        YUV * yuv=(YUV*)malloc(sizeof(YUV));

        convert_to_yuv(rgb_matrix,yuv);
        free_rgb_matrix(rgb_matrix);
        return yuv;


}
