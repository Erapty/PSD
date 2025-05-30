#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vehicle.h"
#include "booking.h"
#include "user.h"
#include "hash.h"
#include "list.h"
#include "storage.h"
#include "timeutils.h"


#define MAX_LINE 256

/*
 * Reads a line from a file and removes the newline character.
 *
 * f: file pointer
 * buffer: destination buffer
 */
void readLine(FILE* f, char* buffer) {
    if (fgets(buffer, MAX_LINE, f)) {
        buffer[strcspn(buffer, "\n")] = 0;
    }
}

/*
 * Compares two files line by line.
 *
 * file1: first file to compare
 * file2: second file to compare
 *
 * Returns 1 if files match exactly, 0 otherwise
 */
int compareFiles(const char* file1, const char* file2) {
    FILE* f1 = fopen(file1, "r");
    FILE* f2 = fopen(file2, "r");
    if (!f1 || !f2) return 0;

    char line1[256], line2[256];
    int result = 1;

    while (fgets(line1, sizeof(line1), f1) && fgets(line2, sizeof(line2), f2)) {
        // Rimuove newline finali (compatibile con \r\n e \n)
        line1[strcspn(line1, "\r\n")] = 0;
        line2[strcspn(line2, "\r\n")] = 0;

        if (strcmp(line1, line2) != 0) {
            result = 0;
            break;
        }
    }

    // Se uno dei file ha righe in più
    if ((fgets(line1, sizeof(line1), f1) != NULL) || (fgets(line2, sizeof(line2), f2) != NULL)) {
        result = 0;
    }

    fclose(f1);
    fclose(f2);
    return result;
}


/*
 * Executes a test case that attempts to create a booking from an input file.
 * If the vehicle is available, the booking is added to the list and a message is printed.
 * Otherwise, an error message is written to output.
 */
void test_create_booking(HashTable* vehicleTable, HashTable* userTable, List bookingList, const char* caseName) {
    char inputFile[64], outputFile[64];
    sprintf(inputFile, "%s_input.txt", caseName);
    sprintf(outputFile, "%s_output.txt", caseName);

    FILE* in = fopen(inputFile, "r");
    if (!in) {
        printf("Error: could not open %s\n", inputFile);
        return;
    }

    FILE* out = fopen(outputFile, "w");
    if (!out) {
        printf("Error: could not create %s\n", outputFile);
        fclose(in);
        return;
    }

    char username[50], plate[20], datetime[32];
    int duration = 0;

    if (!fgets(username, sizeof(username), in) ||
        !fgets(plate, sizeof(plate), in) ||
        !fgets(datetime, sizeof(datetime), in) ||
        fscanf(in, "%d", &duration) != 1) {
        fprintf(out, "INPUT ERROR\n");
        fclose(in);
        fclose(out);
        return;
    }

    username[strcspn(username, "\n")] = 0;
    plate[strcspn(plate, "\n")] = 0;
    datetime[strcspn(datetime, "\n")] = 0;

    fclose(in);

    long start = convertToTimestamp(datetime);
    long end = start + duration * 3600;

    if (!isVehicleAvailable(bookingList, plate, start, end)) {
        fprintf(out, "This vehicle is not available in the selected period. Try another.\n");
    } else {
        Vehicle* v = findVehicle(vehicleTable, plate);
        if (!v) {
            fprintf(out, "Vehicle not found.\n");
        } else {
            Booking* b = createBooking(username, v, start, duration);
            insertList(bookingList, b);
            fprintf(out, "Booking created successfully.\n");
        }
    }

    fclose(out);
}

/*
 * Executes a test case that prints all bookings of a user to outputFile.
 * Then compares outputFile with oracleFile to check correctness.
 */
void test_user_history_from_file(List bookingList, const char* username,
                                 const char* outputFile, const char* oracleFile, FILE* resultFile) {
    FILE* out = fopen(outputFile, "w");
    if (!out) return;

    for (int i = 0; i < getSize(bookingList); i++) {
        Booking* b = (Booking*)getItem(bookingList, i);
        if (strcmp(getBookingUsername(b), username) == 0) {
            fprintf(out, "%s\n", getBookingPlate(b));
        }
    }
    fclose(out);

    int pass = compareFiles(outputFile, oracleFile);
    fprintf(resultFile, "TestCase3: %s\n", pass ? "PASS" : "FAIL");
    printf("TestCase3: %s\n", pass ? "PASS" : "FAIL");
}

/*
 * Main function to run the automated test suite.
 * Reads test cases from test_suite.txt and runs them sequentially.
 * Results are printed to result.txt and also shown on the terminal.
 */
int main() {
    HashTable* vehicleTable = createHashTable();
    HashTable* userTable = createHashTable();
    List bookingList = createList();

    // Load default data (for TestCase1 and TestCase2)
    LoadVehiclesFromFile(vehicleTable, "vehicles.txt");
    LoadUsersFromFile(userTable, "users.txt");
    LoadBookingsFromFile(bookingList, "bookings.txt", vehicleTable, userTable);

    FILE* suite = fopen("test_suite.txt", "r");
    if (!suite) {
        printf("Error: cannot open test_suite.txt\n");
        return 1;
    }

    FILE* result = fopen("result.txt", "w");
    if (!result) {
        fclose(suite);
        return 1;
    }

    char caseName[64];
    int expected;

    while (fscanf(suite, "%s %d", caseName, &expected) == 2) {
        char oracleFile[64], outputFile[64];
        sprintf(oracleFile, "%s_oracle.txt", caseName);
        sprintf(outputFile, "%s_output.txt", caseName);

        if (strcmp(caseName, "TestCase3") == 0) {

            freeList(bookingList);
            bookingList = createList();
            LoadBookingsFromFile(bookingList, "TestCase3_input.txt", vehicleTable, userTable);

            test_user_history_from_file(bookingList, "mario_rossi", outputFile, oracleFile, result);
        } else {
            test_create_booking(vehicleTable, userTable, bookingList, caseName);
            int pass = compareFiles(outputFile, oracleFile);
            fprintf(result, "%s: %s\n", caseName, pass ? "PASS" : "FAIL");
            printf("%s: %s\n", caseName, pass ? "PASS" : "FAIL");
        }
    }

    fclose(suite);
    fclose(result);
    freeHashTable(vehicleTable);
    freeHashTable(userTable);
    freeList(bookingList);

    return 0;
}

