/*****************************************************************************
 * Hotel Reservation System
 * Author: SPINOZA (Improved Version)
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

///////////////////////////////////////////////////////////////////////////
//  CONSTANTS
///////////////////////////////////////////////////////////////////////////
#define NFLOOR 6      // Number of floors
#define NROOM 23      // Number of rooms per floor
#define AVAILABLE -1  // Marks available rooms

///////////////////////////////////////////////////////////////////////////
//  RESERVATION STRUCTURE
///////////////////////////////////////////////////////////////////////////
typedef struct {
    int DNI;
    char name[50];
    char surname[50];
    char N_telephone[10];    // +34 123456789
    char credit[17];         // 16 digits + null terminator
    char arrival_date[11];   // DD/MM/YYYY
    char departure_date[11]; // DD/MM/YYYY
} Reservation;

typedef Reservation Hotel[NFLOOR][NROOM];

///////////////////////////////////////////////////////////////////////////
//  FUNCTION PROTOTYPES
///////////////////////////////////////////////////////////////////////////
void EmptyHotel(Hotel hotel);
void ShowReservations(Hotel hotel);
int FindRoom(Hotel hotel, int *floor, int *room);
Reservation Ask4Data(void);
void MakeReservation(Hotel hotel);
void CancelReservation(Hotel hotel, int floor, int room);
int validate_date(const char *date);
void clear_input_buffer(void);

///////////////////////////////////////////////////////////////////////////
//  MAIN FUNCTION
///////////////////////////////////////////////////////////////////////////
int main() {
    Hotel hotel;
    int opt, floor, room;
    EmptyHotel(hotel);
    
    do {
        printf("\nHotel Reservation System\n");
        printf("1. Make a reservation\n");
        printf("2. Show hotel status\n");
        printf("3. Cancel reservation\n");
        printf("4. Exit\n");
        printf("Select option: ");
        
        if (scanf("%d", &opt) != 1) {
            clear_input_buffer();
            printf("Invalid input! Please enter a number.\n");
            continue;
        }

        switch (opt) {
            case 1:
                MakeReservation(hotel);
                break;
            case 2:
                ShowReservations(hotel);
                break;
            case 3:
                printf("Enter floor (1-%d): ", NFLOOR);
                if (scanf("%d", &floor) != 1 || floor < 1 || floor > NFLOOR) {
                    printf("Invalid floor!\n");
                    clear_input_buffer();
                    break;
                }
                printf("Enter room (1-%d): ", NROOM);
                if (scanf("%d", &room) != 1 || room < 1 || room > NROOM) {
                    printf("Invalid room!\n");
                    clear_input_buffer();
                    break;
                }
                CancelReservation(hotel, floor-1, room-1);
                break;
            case 4:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option! Try again.\n");
        }
    } while (opt != 4);

    return 0;
}

///////////////////////////////////////////////////////////////////////////
//  FUNCTION IMPLEMENTATIONS
///////////////////////////////////////////////////////////////////////////

void EmptyHotel(Hotel hotel) {
    for (int f = 0; f < NFLOOR; f++)
        for (int r = 0; r < NROOM; r++)
            hotel[f][r].DNI = AVAILABLE;
}

void ShowReservations(Hotel hotel) {
    printf("\nHotel Status:\n");
    for (int f = 0; f < NFLOOR; f++) {
        printf("Floor %2d: ", f+1);
        for (int r = 0; r < NROOM; r++) {
            printf("%c ", hotel[f][r].DNI == AVAILABLE ? 'F' : 'R');
        }
        printf("\n");
    }
}

int FindRoom(Hotel hotel, int *floor, int *room) {
    for (int f = NFLOOR-1; f >= 0; f--) {
        for (int r = NROOM-1; r >= 0; r--) {
            if (hotel[f][r].DNI == AVAILABLE) {
                *floor = f;
                *room = r;
                return 1;
            }
        }
    }
    return 0;
}

Reservation Ask4Data(void) {
    Reservation res;
    clear_input_buffer();

    printf("\nEnter DNI (numbers only): ");
    while (scanf("%d", &res.DNI) != 1) {
        clear_input_buffer();
        printf("Invalid DNI! Try again: ");
    }

    clear_input_buffer();
    printf("Enter name: ");
    fgets(res.name, 50, stdin);
    res.name[strcspn(res.name, "\n")] = '\0';

    printf("Enter surname: ");
    fgets(res.surname, 50, stdin);
    res.surname[strcspn(res.surname, "\n")] = '\0';

    do {
        clear_input_buffer();
        printf("Enter phone (9 digits): ");
        fgets(res.N_telephone, 10, stdin);
        res.N_telephone[strcspn(res.N_telephone, "\n")] = '\0';
    } while (strlen(res.N_telephone) != 9 || !isdigit(res.N_telephone[0]));

    do {
        clear_input_buffer();
        printf("Enter credit card (16 digits): ");
        fgets(res.credit, 17, stdin);
        res.credit[strcspn(res.credit, "\n")] = '\0';
    } while (strlen(res.credit) != 16 || !isdigit(res.credit[0]));

    do {
        clear_input_buffer();
        printf("Enter arrival date (DD/MM/YYYY): ");
        fgets(res.arrival_date, 11, stdin);
        res.arrival_date[strcspn(res.arrival_date, "\n")] = '\0';
    } while (!validate_date(res.arrival_date));

    do {
        clear_input_buffer();
        printf("Enter departure date (DD/MM/YYYY): ");
        fgets(res.departure_date, 11, stdin);
        res.departure_date[strcspn(res.departure_date, "\n")] = '\0';
    } while (!validate_date(res.departure_date));

    return res;
}

void MakeReservation(Hotel hotel) {
    int floor, room;
    if (FindRoom(hotel, &floor, &room)) {
        hotel[floor][room] = Ask4Data();
        printf("\nReservation successful! Floor: %d, Room: %d\n", 
              floor+1, room+1);
    } else {
        printf("\nNo available rooms!\n");
    }
}

void CancelReservation(Hotel hotel, int floor, int room) {
    if (floor < 0 || floor >= NFLOOR || room < 0 || room >= NROOM) {
        printf("Invalid room location!\n");
        return;
    }

    if (hotel[floor][room].DNI != AVAILABLE) {
        printf("\nCanceling reservation for:\n");
        printf("Name: %s %s\n", hotel[floor][room].name, 
              hotel[floor][room].surname);
        printf("Arrival: %s\n", hotel[floor][room].arrival_date);
        hotel[floor][room].DNI = AVAILABLE;
        printf("Reservation canceled successfully.\n");
    } else {
        printf("Room is already available.\n");
    }
}

int validate_date(const char *date) {
    if (strlen(date) != 10) return 0;
    if (date[2] != '/' || date[5] != '/') return 0;
    return 1;
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
