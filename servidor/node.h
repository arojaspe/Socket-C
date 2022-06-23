//
// Created by diego on 14/04/22.
//

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H


struct Node{
    struct Node * next;
    unsigned short int source_id;
    unsigned short int dst_id;
    unsigned short int hour;
    float mean_travel;
};

struct bucket{
    struct Node * next;
    unsigned short int sourceId;
    unsigned short int amount;
};

struct nodeFile{
    unsigned short int source_id;
    unsigned short int dst_id;
    unsigned short int hour;
    float mean_travel;
};

struct bucketFile{
    unsigned short int sourceId;
    unsigned short int amount;
};

void insert(
        struct Node ** head_ref,
        unsigned short int new_source_id,
        unsigned short int new_dst_id,
        unsigned short int new_hour,
        float  new_mean_travel){

    struct Node * new_node = (struct Node*) malloc(sizeof (struct Node));
    new_node->source_id = new_source_id;
    new_node->dst_id = new_dst_id;
    new_node->hour = new_hour;
    new_node->mean_travel = new_mean_travel;

    new_node->next = (*head_ref);
    (*head_ref) = new_node;

}

void printList(struct Node ** head_ref){

    struct Node * last = * head_ref;
    unsigned  short int numberNode = 0;

    if (last == NULL){
        printf("List is empty\n  ");
    }

    while(last){
        numberNode++;
        printf("Node: %d\tSource: %d\tDst: %d\tHour: %d\tTime: %.2f\n",numberNode,last->source_id,last->dst_id,last->hour,last->mean_travel);
        last = last->next;
    }
}

float searchDstId(struct Node ** head_ref, int dst_id,int hour){

    struct Node * last = * head_ref;
    int i = 0;

    while (last){
        if(last->dst_id == dst_id && last->hour == hour){
            i = 1;
            break;
        }
        last = last->next;
    }
    if(i == 1){
        return last->mean_travel;
    }else{
        return -1;
    }
}

#endif //UNTITLED_NODE_H
