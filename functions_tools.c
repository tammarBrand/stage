#include "functions_tools.h"

void init_rgb_matrix(){
    int j=0;
    char z=(char)255,x=0;
    //mat_rgb[0]=(char)255
    //mat_rgb[1]=(char)0
    //mat_rgb[2]=(char)0
    while(j!=MAX_TEMP*3)
    {
        //rand numbers
        rgb_per_temp[j++]=z;
        rgb_per_temp[j++]=x;
        rgb_per_temp[j++]=x;
    }
    rgb_per_temp[9]=x;
    rgb_per_temp[10]=x;
    rgb_per_temp[11]=z;
    rgb_per_temp[81]=x;
    rgb_per_temp[82]=z;
    rgb_per_temp[83]=x;
}

void randMat(int** matrix_temp){
    int i,j,new_temp,height_pos,width_pos,num_iterations=0.1*SNAPSHOT_WIDTH*SNAPSHOT_HEIGHT;
    for(i=0;i<SNAPSHOT_HEIGHT;i++){
        for(j=0;j<SNAPSHOT_WIDTH;j++){
            matrix_temp[i][j]=27;
        }
    }
    for(i=0;i<num_iterations;i++)
    {
        height_pos=rand() % SNAPSHOT_HEIGHT;
        width_pos=rand() % SNAPSHOT_WIDTH;
        new_temp=rand()%(MAX_TEMP+1);
        matrix_temp[
                height_pos][width_pos]=new_temp;
    }
}
void covert_to_rgb(char rgb_matrix[],int** matrix){
    if(matrix==NULL)
    {
        *rgb_matrix=NULL;
        return;
    }
    int k=0;
    for(int i=0;i<SNAPSHOT_HEIGHT;i++)
        for(int j=0;j<SNAPSHOT_WIDTH;j++)
        {
            int t=matrix[i][j]*3;
            rgb_matrix[k++]=rgb_per_temp[t];
            rgb_matrix[k++]=rgb_per_temp[t+1];
            rgb_matrix[k++]=rgb_per_temp[t+2];
           // printf("%d rr %s\n",matrix[i][j],rgb_arr[matrix[i][j]]);
            //strcat(rgb_matrix,rgb_arr[matrix[i][j]]);
        }
}
void convert_to_yuv(char rgb_matrix[],  YUV* yuv){
    if(rgb_matrix==NULL){
        //*yuv=NULL;
        return;
    }
    char R,G,B;
    for(int i=0;i<SNAPSHOT_HEIGHT;i++)
            {
                for(int j=0;j<SNAPSHOT_WIDTH;j++)
                {
                    R=*(rgb_matrix+i*SNAPSHOT_WIDTH*3+j*3);
                    G=*(rgb_matrix+i*SNAPSHOT_WIDTH*3+j*3+1);
                    B=*(rgb_matrix+i*SNAPSHOT_WIDTH*3+j*3+2);
                    yuv->y[SNAPSHOT_WIDTH*i+j]= (0.257 * R) + (0.504 * G) + (0.098 * B) + 16+'0';
                    if(i%2==0&&j%2==0)
                    {
                        yuv->u[(SNAPSHOT_WIDTH*i+j)/4]= (0.439 * R) - (0.368 * G) - (0.071 * B) + 128+'0';
                        yuv->v[(SNAPSHOT_WIDTH*i+j)/4]= -(0.148 * R) - (0.291 * G) + (0.439 * B) + 128+'0';
                    }

                }
            }
}


void free_matrix(int** m){
    for(int i=0;i<SNAPSHOT_HEIGHT;i++){
        free(m[i]);
        m[i]=NULL;
    }
    m=NULL;
}
void free_rgb_matrix(char * m){
  if(m!=NULL)
    free(m);

}
size_t ppm_save(ppm_image *img) {
    printf("save ppm\n %d",img->width);
    FILE *   fp=fopen("img123.bmp","wb+");
    size_t n = 0;
    n +=fprintf(fp, "P6\n# THIS IS A COMMENT\n%d %d\n%d\n",
                img->width, img->height, 0xFF);
    n += fwrite(img->data, 1, img->width * img->height * 3, fp);
    fclose(fp);
    return n;
}
void save_snapshot(char* rgb_matrix){
    ppm_image p;
    p.height=SNAPSHOT_HEIGHT;
    p.width=SNAPSHOT_WIDTH;
    p.name="image.ppm";
    p.size=230400;
    p.data=rgb_matrix;
    ppm_save(&p);
}
