/*****************************************************************************
 *
 * 
 *
 * Author:	SPINOZA

 *
 ****************************************************************************/
#include<stdio.h>
#include<stdlib.h>


///////////////////////////////////////////////////////////////////////////
//  DEFINITION OF CONSTANTS
///////////////////////////////////////////////////////////////////////////

#define NFLOOR 6  		// Number of floors in the hotel
#define NROOM 23   		// Number of rooms per floor
#define AVAILABLE -1	// Constant to mark the rooms available (free)

/////////////////////////////////////////////////////////////////////////////
//   Datatype used to store the client data when they make a reservation   //
/////////////////////////////////////////////////////////////////////////////
typedef struct
{
    int DNI;
    char name[50];
    char surname[50];
    int N_telephone[9];
    int credit[16];
    char arrival_date[20];
    char departure_date[20];


} Reservation;

/////////////////////////////////////////////////////////////////////////////
//
//  Datatype that represents the hotel:
// It is a matrix in which each row represents a floor and each column
// represents a room.
// The elements of the matrix are the data regarding each reservation (if it
// exists).
// If the room is not booked, the DNI field should have the value AVAILABLE
//
/////////////////////////////////////////////////////////////////////////////
typedef Reservation Hotel[NFLOOR][NROOM];





/////////////////////////////////////////////////////////////////////////////
//
//  Function:  EmptyHotel
//  Parameters:  Matrix representing the hotel
//  Returns: --
//  Task: Assigns the value AVAILABLE to the field DNI for all the rooms to
//        indicate that the hotel is empty
//
/////////////////////////////////////////////////////////////////////////////
void EmptyHotel (Hotel hotel)
{
    int f,r;
    for(f=0; f<NFLOOR; f++)
        for (r=0; r<NROOM; r++)
            hotel[f][r].DNI=AVAILABLE;
}

/////////////////////////////////////////////////////////////////////////////
//
//  Function:  ShowReservations
//  Parameters:  Matrix representing the hotel
//  Returns: --
//  Task: Shows on screen the matrix that represents the hotel
//                   Prints an F (free) if the room is available.
//                   Prints a R (reserved) if the room is reserved.
//
/////////////////////////////////////////////////////////////////////////////
void ShowReservations (Hotel hotel) {
    int f,r;
    for(f=0; f<NFLOOR; f++) {
        for (r=0; r<NROOM; r++) {
            if(hotel[f][r].DNI==-1)
                printf("F");
            else {
                printf("R");
            }
        }
        printf("\n");

    }
}

    /////////////////////////////////////////////////////////////////////////////
    //
    //  Function:  FindRoom
    //  Parameters:  Matrix representing the hotel
    //               Parameter passed by reference to return the floor in which the available room is found
    //               Parameter passed by reference to return the room number
    //  Returns:  The floor number and the room number of the room selected (by reference)
    //  Task: Finds an available room to be booked.
    //               Starts the search on the TOP floor and continues down
    //               If no available room is found, returns -1 as the floor number
    //
    /////////////////////////////////////////////////////////////////////////////
    void FindRoom(Hotel hotel, int *floor, int *room) {
        int f,r;
        for(f=NFLOOR-1; f>=0; f--){
            for (r=NROOM-1; r>=0; r--) {
                if(hotel[f][r].DNI==-1) {
                    *floor=f;
                    *room=r;
                    return;
                }
            }
        }
    *floor=-1;
    }



    /////////////////////////////////////////////////////////////////////////////
    //
    //  Function:  Ask4Data
    //  Parameters:  --
    //  Returns: Variable of type Reservation storing the data of the client
    //  Task: Asks the user for the reservation data (using printf and scanf)
    //
    /////////////////////////////////////////////////////////////////////////////
Reservation Ask4Data() {
    Reservation res;  // Declare a Reservation variable to store the client data

    printf("Please enter your DNI (only numbers):\n");
    scanf("%d", &res.DNI);

    printf("Please enter your name:\n");
    scanf("%s", res.name);

    printf("Please enter your surname:\n");
    scanf("%s", res.surname);

    printf("Please enter your telephone number:\n");

        scanf("%d", &res.N_telephone);

    printf("Please enter your credit/debit card number for payment:\n");

        scanf("%d", &res.credit);


    printf("Please enter your arrival date (dd/mm/yy):\n");
    scanf("%s", res.arrival_date);

    printf("Please enter your departure date (dd/mm/yy):\n");
    scanf("%s", res.departure_date);

    return res;
}


    /////////////////////////////////////////////////////////////////////////////
    //
    //  Function:  MakeReservation
    //  Parameters:  Matrix representing the hotel
    //  Returns: --
    //  Task: Makes the reservation of the room.
    //        Steps: Finds a free room (first) and then asks for the reservation data,
    //				 which is later stored at the corresponding position in the matrix.
    //
    /////////////////////////////////////////////////////////////////////////////
    void MakeReservation(Hotel hotel) {

    int floor, room;

    FindRoom(hotel, &floor, &room); // calling the function to find a free room

    if (floor != -1) { // making sure that there is a free room

        Reservation res = Ask4Data(); // getting reservation data and giving it in reservation res;

        hotel[floor][room] = res; // Store data in the hotel matrix

    } else {
        printf("No rooms available!\n");

    }

    }




    /////////////////////////////////////////////////////////////////////////////
    //
    //  Function:  CancelReservation
    //  Parameters:  Matrix representing the hotel
    //               Identifier of the reservation (floor number and room number)
    //  Returns: --
    //  Task: Sets the room as available by setting the DNI field to AVAILABLE,
    //        Visualises the reservation data before deleting it (name, surname
    //		  and date of arrival).
    //
    /////////////////////////////////////////////////////////////////////////////
    void CancelReservation(Hotel hotel, int floor, int room)
    {

    if (hotel[floor][room].DNI != AVAILABLE) {

        printf("Name: %s %s\n", hotel[floor][room].name, hotel[floor][room].surname);
        printf("Arrival Date: %s\n", hotel[floor][room].arrival_date);

        hotel[floor][room].DNI = AVAILABLE;
    } else {
        printf("No reservation found in this room.\n");
    }

    }

    /////////////////////////////////////////////////////////////////////////////
    //  DO NOT MODIFY
    /////////////////////////////////////////////////////////////////////////////
    //
    //  Function:  Main
    //  Parameters:  --
    //  Returns: --
    //  Task: Main program
    //
    /////////////////////////////////////////////////////////////////////////////
    void main()
    {
        Hotel hotel;
        int opt,floor,room;
        EmptyHotel(hotel);
        do
        {
            printf("1.- Make a reservation\n");
            printf("2.- Show the hotel status\n");
            printf("3.- Cancel a reservation\n");
            printf("4.- Exit\n");
            printf("Select an option:  ");
            scanf("%d",&opt);

            switch (opt)
            {
                case 1:
                    MakeReservation(hotel);
                break;
                case 2:
                    ShowReservations(hotel);
                break;
                case 3:
                    printf("Indicate the reservation to cancel\n");
                printf(" Floor (from 1 to %d):",NFLOOR);
                scanf("%d", &floor);
                floor--;
                printf(" Room (from 1 to %d:",NROOM);
                scanf("%d", &room);
                room--;
                CancelReservation(hotel, floor,room);
                break;
                case 4:
                    printf("SEE YOU!\n");
                break;
            }
        }
        while (opt!=4);
    }