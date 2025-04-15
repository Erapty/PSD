#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

#define MAX_NAME 50
#define ADMIN_PASS "1234"
#define VEHICLE_FILE "vehicles.txt"

void adminMenu(list *vehicles);
void clientMenu(List vehicles);
void loadVehicle(List *vehicles);
void saveVehicle(List vehicles);

int main(){
    List vehicleList = newList();
    loadVehicles(&vehicleList);

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
        }
    }else{
        clientMenu(vehicleList);
    }
    saveVehicles(vehicleList);
    freeList(vehicleList);
    return 0;
}