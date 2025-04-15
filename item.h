#ifndef ITEM_H
#define ITEM_H

#define MAX_TYPE 30


//STRUCT TO RAPPRESENT VEHICLE
typedef struct{
    char type[MAX_TYPE];
    char car_brand[30];
    int seats;
    float base_price;
    int id;
}item;

#define NULLITEM (item){"","",0,0.0,-1}

#endif

