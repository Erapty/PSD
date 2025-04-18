#include "storage.h"
#include "vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

List load_vehicles_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    List vehicleList = CreateList();
    char buffer[MAX_LINE];

    while (fgets(buffer, MAX_LINE, file)) {
        vehicle *v = malloc(sizeof(vehicle));
        v->plate = malloc(16);
        v->type = malloc(32);
        v->fuel = malloc(16);
        v->brand = malloc(32);
        v->model = malloc(32);

        sscanf(buffer, "%s %f %d %s %s %s %s %d %d",
               v->plate, &v->cost, &v->seats,
               v->type, v->fuel, v->brand, v->model,
               &v->booked, &v->year);

        InsertValue(vehicleList, v);
    }

    fclose(file);
    return vehicleList;
}

void save_vehicles_to_file(const char *filename, List list) {
    FILE *file = fopen(filename, "w");
    if (!file) return;

    for (int i = 0; i < GetSize(list); i++) {
        vehicle *v = (vehicle *)GetItem(list, i);
        fprintf(file, "%s %.2f %d %s %s %s %s %d %d\n",
                v->plate, v->cost, v->seats,
                v->type, v->fuel, v->brand, v->model,
                v->booked, v->year);
    }

    fclose(file);
}
