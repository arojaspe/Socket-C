#ifndef UNTITLED_SEARCH_H
#define UNTITLED_SEARCH_H

float searchMean(int input,int dst,int hour){

    //read bin file
    FILE * file = fopen("complete.bin", "rb+");
    struct bucketFile * readBucket = (struct bucketFile *) malloc(sizeof(struct bucketFile));

    int jump = 0;

    while (fread(readBucket, sizeof(struct bucketFile),1,file)){

        //printf("Source: %d\n",readBucket->sourceId);
        if(readBucket->sourceId == input){
            break;
        }
        jump = jump + sizeof(struct bucketFile)+readBucket->amount* sizeof(struct nodeFile);
        fseek(file,jump,SEEK_SET);
    }


    //printf("Source: %d\tAmount: %d\n",readBucket->sourceId,readBucket->amount);

    //Read blues or nodes
    struct nodeFile * blue = (struct nodeFile * ) malloc(sizeof(struct nodeFile));
    jump = jump + sizeof(struct bucketFile);
    fseek(file,jump,SEEK_SET);
    int numberBlue = readBucket->amount;

    for(int i=0;i<= numberBlue ;i++){
        fread(blue, sizeof(struct nodeFile),1,file);
        if(blue->dst_id == dst && blue->hour == hour){
            break;
        }
        fseek(file,jump + sizeof(struct nodeFile)*i,SEEK_SET);
    }

    float final = blue->mean_travel;
    printf("Mean: %.2f",final);
    return final;
}

#endif

