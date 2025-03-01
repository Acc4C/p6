#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include "passenger.h"

int main(int argc, char** argv){
    char choice, *filename = NULL;
    int weight = -2, count;
    while ((choice = getopt(argc, argv, "p:f:")) != -1){
        switch (choice){
            case 'p':
                weight = 0;
                for (char* number = optarg; (*number) != '\0'; number++){
                    if ((*number) < '0' || (*number) > '9'){
                        weight = -1;
                        break;
                    }
                    weight *= 10;
                    weight += (*number) - '0';
                }
                break;
            case 'f':
                free(filename);
                filename = (char*)malloc(sizeof(char)*(strlen(optarg) + 1));
                if (filename == NULL){
                    printf("memory error\n");
                    return 0;
                }
                strcpy(filename, optarg);
                break;
        }
    }
    if (filename == NULL){
        printf("Не введено название файла\n");
        return 0;
    }
    if (weight == -1){
        printf("Введено некорректное значение параметра\n");
        return 0;
    }
    if (weight == -1){
        printf("Не введено значение параметра\n");
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
    Passenger* passengers = (Passenger*)malloc(sizeof(Passenger)*count);
    if (fread(passengers, sizeof(Passenger), count, file) != count){
        printf("Некорректное содержание файла\n");
        free(passengers);
        fclose(file);
        return 0;
    }
    fclose(file);
    Passenger passenger;
    time_t stamp1, stamp2;
    stamp1 = clock();
    for (int i = 1; i < count; i++){
        passenger = passengers[i];
        for (int j = 0; j < i; j++){
            if (passengers[j].numberOfThings == passenger.numberOfThings){
                if ((passengers[j].weightOfThings - passenger.weightOfThings) <= weight && (passengers[j].weightOfThings - passenger.weightOfThings) >= -weight){
                    stamp2 = clock();
                    printf("|     SURNAME     | INITIALS | NUMBER OF THINGS | WEIGHT OF THINGS |   DESTINATION   |   DEPARTURE TIME  | TRANSFERS | CHILDREN |\n");
                    printf("| %-15s | %-8s | %-16d | %-16d | %-15s | %-17s | %-9d | %-8d |\n", passengers[j].surname, passengers[j].initials, passengers[j].numberOfThings, passengers[j].weightOfThings, passengers[j].destination, passengers[j].departureTime, passengers[j].transfers, passengers[j].children);
                    printf("| %-15s | %-8s | %-16d | %-16d | %-15s | %-17s | %-9d | %-8d |\n", passenger.surname, passenger.initials, passenger.numberOfThings, passenger.weightOfThings, passenger.destination, passenger.departureTime, passenger.transfers, passenger.children);
                    printf("time: %.3lfms\n", ((double)(stamp2 - stamp1))*1000/((double) CLOCKS_PER_SEC));
                    free(passengers);
                    return 0;
                }
            }
        }
    }
    stamp2 = clock();
    printf("Подходящих элементов не найдено\n");
    printf("time: %.3lfms\n", ((double)(stamp2 - stamp1))*1000/((double) CLOCKS_PER_SEC));
    free(passengers);
    return 0;
}
