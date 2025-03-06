#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "passenger.h"

int main(int argc, char** argv){
    char choice, *filename;
    int count;
    Passenger passenger;
    if ((choice = getopt(argc, argv, "f:")) != -1){
        filename = (char*)malloc(sizeof(char)*(strlen(optarg) + 1));
        if (filename == NULL){
            printf("memory error");
            return 0;
        }
        strcpy(filename, optarg);
    } else{
        printf("Название файла не введено\n");
        return 0;
    }
    FILE* file = fopen(filename, "rb");
    free(filename);
    if (file == NULL){
        printf("Не получилось открыть файл\n");
        return 0;
    }
    if (fread(&count, sizeof(int), 1, file) == 0){
        printf("Некорректное содержание файла\n");
        fclose(file);
        return 0;
    }
    printf("|     SURNAME     | INITIALS | NUMBER OF THINGS | WEIGHT OF THINGS |   DESTINATION   |   DEPARTURE TIME  | TRANSFERS | CHILDREN |\n");
    for (int i = 0; i < count; i++){
        if (fread(&passenger, sizeof(Passenger), 1, file) == 0){
            printf("Некорректное содержание файла\n");
            fclose(file);
            return 0;
        }
        printf("| %-15s | %-8s | %-16d | %-16d | %-15s | %-17s | %-9d | %-8d |\n", passenger.surname, passenger.initials, passenger.numberOfThings, passenger.weightOfThings, passenger.destination, passenger.departureTime, passenger.transfers, passenger.children);
    }
    fclose(file);
    return 0;
}
