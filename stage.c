#include "stage.h"

void* create_handler(int* status, void* pipe_header, void* dest_data){

    handler* my_handler=(handler*)malloc(sizeof (handler));
    my_handler->status_bits=status;
    my_handler->head=(stage*)pipe_header;
    my_handler->dest_data=dest_data;

    return my_handler;
}

void* create_stage(Queue* sourse, Queue* dest, function func,stage* next){
    stage* my_stage=(stage*)malloc(sizeof(stage));
    my_stage->destQu=dest;
    my_stage->sourseQu=sourse;
    my_stage->func=func;
    my_stage->next=next;
    my_stage->is_active=0;
    return my_stage;
}
void stop_stage(stage* head_stage){

}
void* main_stage_thread(void* arg){
;
    handler* my_handler=((stage_params*)arg)->handler;
    stage* my_stage=((stage_params*)arg)->stage;


    Node *dest ,*n=(Node*)calloc(1,sizeof(Node));// last node to enter the pipeline
    void* data;

    /*
     * since all thread have 'do while' loop,
     * means the first thread will create at least 2 matrix,
     * the others won't be stucked in the dequeue setion.
     * */

    if(my_stage->sourseQu!=NULL){
        freeNode(n);
        n=dequeue(my_stage->sourseQu);
    }   


    /*
     * should save/write will be part of the stages.
     * yes-> they shouls know the definitions of the snap or record
     * no->  they will return value
     */



    do{
        data=my_stage->func(n->data, my_handler);
        if(my_stage->destQu!=NULL){            
            dest=createNode(data);
            enqueu(my_stage->destQu,dest);
        }
        else{
            my_handler->dest_data=data;
        }
        if(my_stage->sourseQu!=NULL){
            freeNode(n);
            n=dequeue(my_stage->sourseQu);
            my_stage->is_active=n->data!=NULL;
        }
        else{/*
              *for first thread
              *continue only if it's in the middle of a record
              */
           my_stage->is_active=((*(my_handler->status_bits))&PIPE_START)&&!((*(my_handler->status_bits))&PIPE_STOP);
        }
        sleep(2);
    }while(my_stage->is_active);


    if(my_stage->destQu!=NULL){
        enqueu(my_stage->destQu,n);
    }
    else{//last thread to pipeline only

        freeNode(n);
    }

}
