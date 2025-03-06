#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include "passenger.h"

int getCharField(FILE* file, char* field, int maxLength){
    char format[12];
    sprintf(format, "%%%d[A-Za-z]", maxLength);
    fscanf(file, "\n");
    int err = fscanf(file, format, field);
    if (err == 0){ return 1; }
    if (err == -1){ return -1; }
    return 0;
}

int getDateTimeField(FILE* file, char* field){
    int day, month, year, hours, minutes;
    fscanf(file, "\n");
    int err = fscanf(file, "%d.%d.%d %d:%d", &day, &month, &year, &hours, &minutes);
    if (err == -1){ return -1; }
    if (err != 5){ return 1; }
    sprintf(field, "%02d.%02d.%d %02d:%02d", day, month, year, hours, minutes);
    return 0;
}

int getInitials(FILE* file, char* field){
    char n, s;
    fscanf(file, "\n");
    int err = fscanf(file, "%c. %c.", &n, &s);
    if (err == -1){ return -1; }
    if (err != 2){ return 1; }
    sprintf(field, "%c. %c.", n, s);
    return 0;
}

int getIntegerField(FILE* file, int* field){
    int err = fscanf(file, "%d", field);
    if (err == -1){ return -1; }
    if (err == 0){ return 1; }
    return 0;
}

int main(int argc, char** argv){
    char choice, *outputFilename = NULL, *inputFilename = NULL;
    int count;
    while ((choice = getopt(argc, argv, "i:o:")) != -1){
        switch (choice){
            case 'i':
                free(inputFilename);
                inputFilename = (char*)malloc(sizeof(char)*(strlen(optarg) + 1));
                if (inputFilename == NULL){
                    free(outputFilename);
                    printf("memory error\n");
                    return 0;
                }
                strcpy(inputFilename, optarg);
                break;
            case 'o':
                free(outputFilename);
                outputFilename = (char*)malloc(sizeof(char)*(strlen(optarg) + 1));
                if (outputFilename == NULL){
                    free(inputFilename);
                    printf("memory error\n");
                    return 0;
                }
                strcpy(outputFilename, optarg);
                break;
        }
    }
    if (inputFilename == NULL){
        free(inputFilename);
        printf("Не введено название файла ввода\n");
        return 0;
    }
    if (outputFilename == NULL){
        free(outputFilename);
        printf("Не введено название файла вывода\n");
        return 0;
    }
    FILE* inputFile = fopen(inputFilename, "r");
    free(inputFilename);
    if (inputFile == NULL){
        free(outputFilename);
        printf("Не получилось открыть файл для чтения\n");
        return 0;
    }
    FILE* outputFile = fopen(outputFilename, "wb");
    free(outputFilename);
    if (outputFile == NULL){
        fclose(inputFile);
        printf("Не получилось открыть файл для записи\n");
        return 0;
    }
    Passenger passenger;
    memset(&passenger, '\0', sizeof(Passenger));
    int err = fscanf(inputFile, "%d", &count);
    if (err == -1){
        fclose(inputFile);
        fclose(outputFile);
        return 0;
    }
    if (err == 0){
        printf("Не введено количество пассажиров\n");
        fclose(inputFile);
        fclose(outputFile);
        return 0;
    }
    fwrite(&count, sizeof(int), 1, outputFile);
    for (int i = 0; i < count; i++){
        err = getCharField(inputFile, passenger.surname, SURNAMELENGTH);
        if (!err){ err = getInitials(inputFile, passenger.initials); }
        if (!err){ err = getIntegerField(inputFile, &(passenger.numberOfThings)); }
        if (!err){ err = getIntegerField(inputFile, &(passenger.weightOfThings)); }
        if (!err){ err = getCharField(inputFile, passenger.destination, DESTINATIONLENGTH); }
        if (!err){ err = getDateTimeField(inputFile, passenger.departureTime); }
        if (!err){ err = getIntegerField(inputFile, &(passenger.transfers)); }
        if (!err){ err = getIntegerField(inputFile, &(passenger.children)); }
        if (err == -1){
            fclose(inputFile);
            fclose(outputFile);
            return 0;
        }
        if (err == 1){
            printf("Некорректный ввод\n");
            fscanf(inputFile, "%*[^\n]");
            continue;
        }
        fwrite(&passenger, sizeof(Passenger), 1, outputFile);
    }
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
