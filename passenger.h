#ifndef PASSENGER
#define PASSENGER
#define SURNAMELENGTH 16
#define INITIALSLENGTH 6
#define DESTINATIONLENGTH 16
#define DEPARTURETIMELENGTH 17

typedef struct Passenger{
    char surname[SURNAMELENGTH];
    char initials[INITIALSLENGTH];
    int numberOfThings;
    int weightOfThings;
    char destination[DESTINATIONLENGTH];
    char departureTime[DEPARTURETIMELENGTH];
    int transfers;
    int children;
}Passenger;
#endif
