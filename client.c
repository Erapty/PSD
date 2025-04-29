#include "list.h"
#include "vehicle.h"
#include <stdio.h>
//views all vehicle if vehicleList is not null and there is at least one car available.
void view_vehicle(vehicleList){
    if(vehicleList==NULL){
        printf("\nview_vehicle error : list not found.");
        exit(-1);
    }
    if(vehicleList->ItemCount==0){
        printf("\nno vehicle avaibles.");
        exit(0);
    }
    Node current=vehicleList->head;
    printf("\nvehicles list (%d availables):",&vehicleList->ItemCount);
    for(int i=0;i<vehicleList->ItemCount;i++;){
        view_vehicle(current->head->item);
        current=current->next;
    }
    printf("\n\nend of the list."):

}
//keeps the menu open until 0 is entred to exit.
void clientmenu(list vehicleList){
    int choice;
    bool error=false;
    do{
        printf("client menu:
            \n\twhat want you to do?
            \n\n\t0. exit the menu;
            \n\t1. view available cars;
            \n\t2.book a car;
            \n\n\t enter your choice :");
        scanf("%d",choice);
        switch(choice){
            case 0:
                printf("exit menu");
                exit(1);
            case 1:
                view_vehicle(vehicleList);
                error=false;
                break;
            case 2:
                make_reservation(vehicleList);
                error=false;
                break;
            default:
                printf("\ninvalid choice.")
                error=true;
                break;
        }
    }while(error=true);

}