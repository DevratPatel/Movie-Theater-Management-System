#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_ROWS 9
#define MAX_COLS 9
#define TICKET_LIMIT 4

void FillMovieTheater(char MovieTheater[MAX_ROWS][MAX_COLS], int numRows, int numSeats, char infilename[MAX_COLS])
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numSeats; j++)
        {
            MovieTheater[i][j] = infilename[MAX_COLS];
        }
    }
}

void PrintSeatMap(char MovieTheater[MAX_ROWS][MAX_COLS], int numRows, int numSeats)
{
    printf("\n\n          ");
    for (int i = 1; i <= numSeats; i++)
    {
        printf("Seat ");
        printf("%-3d ", i);
    }

    printf("\n");

    for (int i = 0; i < numRows; i++)
    {
        printf("Row %c     ", 'A' + i);

        for (int j = 0; j < numSeats; j++)
        {
            printf("%-9c", MovieTheater[i][j]);
        }

        printf("\n");
    }
}

int IsSeatSold(char MovieTheater[MAX_ROWS][MAX_COLS], int row, int col)
{
    if (MovieTheater[row][col] == 'X')
    {
        return 1;
    }
    else
    {
        MovieTheater[row][col] = 'X';
        return 0;
    }

}

void WriteMovieTheater(char MovieTheater[MAX_ROWS][MAX_COLS], int numRows, int numSeats)
{
    char outfilename[50];
    FILE *outfile = NULL;

    printf("Enter the output filename: ");
    scanf("%s", outfilename);

    outfile = fopen(outfilename, "w+");

    if (outfile == NULL)
    {
        printf("Unable to open file for writing. Exiting program.\n");
        exit(0);
    }

    fprintf(outfile, "%d %d\n", numRows, numSeats);

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numSeats; j++)
        {
            fprintf(outfile, "%c", MovieTheater[i][j]);
        }
    }

    fclose(outfile);
}

int main(void)
{
    int numRows;
    int numSeats;
    int numTickets;
    int ticketsSold = 0;
    char Seat;
    int Col;
    int Array_Row;
    int Array_Col;
    
    FILE *infile = NULL;
    char MovieTheater[MAX_ROWS][MAX_COLS];
    char infilename[MAX_COLS];
    

    printf("Enter the name of your Movie Theater file ");
    scanf("%s", infilename);

    infile = fopen(infilename, "r");

    if (infile == NULL)
    {
        printf("Unable to open file for reading. Exiting program.\n");
        exit(0);
    }

    fscanf(infile, "%d %d", &numRows, &numSeats);
    fgets(infilename, sizeof(infilename), infile);

    for (int i = 0; i < numRows; i++)
    {
        fgets(MovieTheater[i], MAX_COLS + 1, infile);
    }

    fclose(infile);

    FillMovieTheater(MovieTheater, numRows, numSeats, infilename);

    printf("How many tickets would you like to purchase? (Limit %d): ", TICKET_LIMIT);
    scanf("%d", &numTickets);

    while (numTickets < 0 || numTickets > TICKET_LIMIT)
    {
        printf("This is a special showing - limit of %d tickets per purchase.\n", TICKET_LIMIT);
        printf("How many tickets would you like to purchase? (Limit %d): ", TICKET_LIMIT);
        scanf("%d", &numTickets);
    }

    if (numTickets == 0)
    {
        printf("No movie for you!");
    }
    else
    {
        while (numTickets > ticketsSold)
        {
            PrintSeatMap(MovieTheater, numRows, numSeats);

            printf("\n\nEnter seat choice by entering the row and seat\n");
            printf("Please pick a seat  ");
            scanf(" %c%d", &Seat, &Col);

            Seat = toupper(Seat);

            Array_Row = Seat - 'A';
            Array_Col = Col - 1;

            if (Array_Row < 0 || Array_Row >= numRows || Array_Col < 0 || Array_Col >= numSeats)
            {
                printf("\nThat seat is not in this theater!!\n");
            }
            else
            {
                if (IsSeatSold(MovieTheater, Array_Row, Array_Col))
                {
                    printf("\nSeat %c%d is already sold. Pick a different seat.\n\n", Seat, Col);
                }
                else
                {
                    MovieTheater[Array_Row][Array_Col] = 'X';
                    ticketsSold++;
                }
            }
        }

        printf("\n\nPlease find your way to your seats using this map...\n");
        PrintSeatMap(MovieTheater, numRows, numSeats);
        printf("\nEnjoy your movie!\n");

        WriteMovieTheater(MovieTheater, numRows, numSeats);
    }

    return 0;
}
