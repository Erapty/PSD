#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "storage.h"

#define MAX_NAME 50
#define ADMIN_PASS "1234"
#define VEHICLE_FILE "vehicles.txt"

void adminMenu(List *vehicles);
void clientMenu(List vehicles);


int main(){
    List vehicleList = newList();
    vehicleList=load_vehicles_from_file(&VEHICLE_FILE);

    printf("Welcome to Car Sharing Service\n");
    printf("Are you an Admin or a CLient?  (a/c): ");
    char role;
    scanf(" %c",&role);

    if(role=='a'){
        char pass[20];
        printf("Enter admin password: ");
        scanf("%s",pass);
        if(strcmp(pass,ADMIN_PASS)==0){
            adminMenu(&vehicleList);
        }
        else{
            printf("Incorrect password.\n");
            return 0;
        }
    }else{
        clientMenu(vehicleList);
    }
    
    freeList(vehicleList);
    return 0;
}