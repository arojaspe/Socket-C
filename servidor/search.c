#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main(int argc, char const* argv[]){

    //read bin file
    FILE * file = fopen("complete.bin", "rb+");
    struct bucketFile * readBucket = (struct bucketFile *) malloc(sizeof(struct bucketFile));

    int jump = 0;

    //input
    unsigned short int input = 951;
    unsigned short int hour = 12;
    unsigned  short int dst = 151;

    while (fread(readBucket, sizeof(struct bucketFile),1,file)){

        //printf("Source: %d\n",readBucket->sourceId);
        if(readBucket->sourceId == input){
            break;
        }
        jump = jump + sizeof(struct bucketFile)+readBucket->amount* sizeof(struct nodeFile);
        fseek(file,jump,SEEK_SET);
    }


    printf("Source: %d\tAmount: %d\n",readBucket->sourceId,readBucket->amount);

    //Read blues or nodes
    struct nodeFile * blue = (struct nodeFile * ) malloc(sizeof(struct nodeFile));
    jump = jump + sizeof(struct bucketFile);
    fseek(file,jump,SEEK_SET);
    int numberBlue = readBucket->amount;

    for(int i=0;i<= numberBlue ;i++){
        fread(blue, sizeof(struct nodeFile),1,file);
        //printf("I: %d\t",i);
        //printf("Source: %d\tDst: %d\tHour: %d\tMean: %.2f\n",blue->source_id,blue->dst_id,blue->hour,blue->mean_travel);
        if(blue->dst_id == dst && blue->hour == hour){
            break;
        }
        fseek(file,jump + sizeof(struct nodeFile)*i,SEEK_SET);
    }

    float final = blue->mean_travel;
    printf("Mean: %.2f",final);
    return 0;
}