#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include "passenger.h"

void getCharField(char* field, int maxlength, int minlength){
    int count = minlength + (rand() % (maxlength - minlength));
    for (int i = 0; i < count; i++){ *(field + i) = 'a' + (rand() % ('z' - 'a' + 1)); }
    field[0] -= 32;
    field[count] = '\0';
}

void getDateTimeField(char* field){
    int day = 1 + rand()%28;
    int month = 1 + rand()%12;
    int year = 5 + rand()%5;
    int hours = rand()%24;
    int minutes = rand()%60;
    sprintf(field, "%02d.%02d.202%d %02d:%02d", day, month, year, hours, minutes);
}

void getInitials(char* field){
    sprintf(field, "%c. %c.", 'A' + rand()%('Z' - 'A' + 1), 'A' + rand()%('Z' - 'A' + 1));
}

int main(int argc, char** argv){
    char choice, *filename = NULL;
    int count = 20;
    while ((choice = getopt(argc, argv, "c:f:")) != -1){
        switch (choice){
            case 'c':
                count = 0;
                for (char* number = optarg; (*number) != '\0'; number++){
                    if ((*number) < '0' || (*number) > '9'){
                        count = -1;
                        break;
                    }
                    count *= 10;
                    count += (*number) - '0';
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
    if (count == -1){
        printf("Введено некорректное значение\n");
        return 0;
    } else if (count < 20){
        printf("число пассажиров должно быть не менее 20\n");
        return 0;
    }
    FILE* file = fopen(filename, "wb");
    free(filename);
    if (file == NULL){
        printf("Не получилось открыть файл для записи\n");
        return 0;
    }
    Passenger passenger;
    fwrite(&count, sizeof(int), 1, file);
    for (int i = 0; i < count; i++){
        getCharField(passenger.surname, SURNAMELENGTH, 4);
        getInitials(passenger.initials);
        passenger.numberOfThings = 1 + rand()%500;
        passenger.weightOfThings = 1 + rand()%1000;
        getCharField(passenger.destination, DESTINATIONLENGTH, 4);
        getDateTimeField(passenger.departureTime);
        passenger.transfers = rand()%10;
        passenger.children = rand()%5;
        fwrite(&passenger, sizeof(passenger), 1, file);
    }
    fclose(file);
    return 0;
}
