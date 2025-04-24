#include "vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//defining default coasts
#define cost_sedan 1;
#define cost_station_wagon 1;
#define cost_small_car 1;
#define cost_minivan 1;
#define cost_suv 1;
#define cost_cabrio 1;
#define cost_coupe 1;
#define cost_city_car 1;

typedef struct{
    char *plate;
    float cost;
    int seats;
    char *type;
    char *fuel;
    char *brand;
    char *model;
    bool booked;
    int year;

    }vehicle;
//it returns 1 if a is booked,else 0

bool booked(vehicle *a){
    if(!a)exit(-1);
    return (a->booked);
}
//it inserts a plate in a vehicle structure(a)
void insert_plate(vehicle *a){
    if(!a)exit(-1);
    char c;
    int i;
    bool valid=true;
    do{
        printf("\ninsert plate :");
        c=getchar();
        for(i=0;i<2;i++){
            if((c>='a' && c<='z')||(c>='A' && c<='z'))
                a->plate[i]=c;
            else
                valid=false;
        }
        for(;i<3;i++){
            if(c>='0' && c<='9')
                a->plate[i]=c;
            else
                valid=false;
        }
        for(i=0;i<2;i++){
            if((c>='a' && c<='z')||(c>='A' && c<='z'))
                a->plate[i]=c;
            else
                valid=false;
        }
        if (valid==false){
            a->plate[0]={0,0,0,0,0,0,0}
            printf("\n--invalid plate--");
        }
    }while(valid==false);   
}
//it define a coast to a structure vehicle
void define_cost(vehicle *a){
    if(!a)exit(-1);
    float base,cost;
    //cost variation based on vehicle type
    if(a->type=="sedan")
        base=cost_sedan;
    if(a->type=="small car")
        base=cost_small_car;
    if(a->type=="cabrio")
        base=cost_cabrio;
    if(a->type=="city car")
        base=cost_city_car;
    if(a->type=="coupe")
        base=cost_coupe;
    if(a->type=="minivan")
        base=cost_minivan;
    if(a->type=="suv")
        base=cost_suv;
    if(a->type=="station wagon")
        base=cost_station_wagon;
    //cost variation based on seats and year of registration
    cost=base*(seats/5)*((year-1950)/10);
    
}
//it inserts a number n in the field seats of the structure a
void instert_seats(vehicle *a,int n){
    if(!a) extit(-1);
    a->seats=n;
}
//it insert a string s in the field type of structure a
void insert_type(vehicle *a,char *s){
    if(!a)exit(-1);
    strcpy(a->type,s);
}
//it insert a string s in the field fuel of structure a
void insert_fuel(vehicle *a,char *s){
    if(!a)exit(-1);
    strcpy(a->fuel,s);
}
//it insert a string s in the field brand of structure a
void insert_brand(vehicle *a,char *s){
    if(!a)exit(-1);
    strcpy(a->brand,s);
}
//it insert a string s in the field model of structure a
void insert_model(vehicle *a,char *s){
    if(!a)exit(-1);
    strcpy(a->model,s);
}
//it inserts a number n in the field year of the structure a
void instert_year(vehicle *a,int n){
    if(!a) extit(-1);
    a->year=n;
}

List insert_vehicle(vehicle *v,char *plate, int seats,char *type, char *fuel, char *brand, char *model, int year){
    insert_model(v,model);
    insert_brand(v,brand);
    insert_plate(v,plate);
    insert_fuel(v,fuel);
    insert_type(v,type);
    instert_year(v,year);
    instert_seats(v,seats);
    define_cost(v);
    v->booked=false;
}