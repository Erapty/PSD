#define cost_sedan 1;
#define cost_station_wagon 1;
#define cost_small_car 1;
#define cost_minivan 1;
#define cost_suv 1;
#define cost_cabrio 1;
#define cost_coupe 1;
#define cost_city_car 1;

struct vehicle{
    char *plate;
    float cost;
    int seats;
    char *type;
    char *fuel;
    char *brand;
    char *model;
    bool booked;
    int year;

    }

bool booked(vehicle a){
    return a.booked;
}
insert_plate(vehicle *a){
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
        if valid=false{
            a->plate[0]={0,0,0,0,0,0,0}
            printf("\n--invalid plate--");
        }
    }while(valid==false)   
}

define cost(vehicle *a){
    float base;
    
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

    
    
}