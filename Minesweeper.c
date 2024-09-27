#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FLUSH fflush(stdin)

void minefield_generator( void );
void print_minefield( void );
void guess( void );
void defeat( void );
void print_final_minefield( void );
void win( void );
void play_again( void );
void game_over( void );
void gotoxy(int x, int y);

COORD coord = {0, 0};
int const_x, const_y;
int ROWS = 20, COLUMNS = 20;
int total_mines = 10;
int minefield[30][30];                                      //This 2-D array contains all of the mines, numbers and blank spaces
int blank_minefield[30][30];                                //This contains the minefield full of '|-|' characters
int final_minefield[30][30];
int lives = 3;
int mine_locations[10][2];
int random_bomb = 0;
int guess_x[15]={1,4,9,11,19,3,15,13,0,1,17,9,6,13,17};
int guess_y[15]={10,16,4,2,10,11,9,13,9,7,3,16,17,5,6};
int guesscount = 0;

int main()
{
    minefield_generator();
    guess();
    return 0;
}

void gotoxy(int x, int y)
{
    coord.X = x - 1;
    coord.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void minefield_generator( void )                            //Function that generates the minefield
{
    int ctr_3 = 0, ctr_2 = 0;
    int mine_locations[10][2] = { {0, 10}, {1, 15}, {3, 4},{19,2},{19,10},{3,12},{6,9},{17,6},{3,9},{1,7} };
    while( ctr_2 < COLUMNS)                                          //Nested loop for making the blank minefield and final minefield
    {
        while( ctr_3 < ROWS)
        {
            minefield[ctr_3][ctr_2] = '-';
            blank_minefield[ctr_3][ctr_2] = minefield[ctr_3][ctr_2];
            final_minefield[ctr_3][ctr_2] = minefield[ctr_3][ctr_2];
            ctr_3++;
        }
        ctr_3 = 0;
        ctr_2++;
    }
    int mines = 0;
    while( mines < total_mines )                            //Randomly generates the mines into the minefield
    {
        ctr_3 = mine_locations[mines][0];
        ctr_2 = mine_locations[mines][1];
        if( minefield[ctr_3][ctr_2] != '*')                         //If statement that checks if there is a mine already there and doesn't place a mine if there is
        {
            minefield[ctr_3][ctr_2] = '*';
            final_minefield[ctr_3][ctr_2] = minefield[ctr_3][ctr_2];
            mines++;
        }
    }
    ctr_3 = 0;
    ctr_2 = 0;

    while( ctr_2 < COLUMNS )                                          //While loop that generates the numbers for any adjacent mines
    {
        while( ctr_3 < ROWS)
        {
            if( minefield[ctr_3][ctr_2] != '*')
            {
                minefield[ctr_3][ctr_2] = 0;
            }
            if((minefield[ctr_3-1][ctr_2-1] == '*') && (minefield[ctr_3][ctr_2] != '*'))
            {
                minefield[ctr_3][ctr_2]++;
            }
            if((minefield[ctr_3-1][ctr_2] == '*') && (minefield[ctr_3][ctr_2] != '*'))
            {
                minefield[ctr_3][ctr_2]++;
            }
            if((minefield[ctr_3][ctr_2-1] == '*') && (minefield[ctr_3][ctr_2] != '*'))
            {
                minefield[ctr_3][ctr_2]++;
            }
            if((minefield[ctr_3-1][ctr_2+1] == '*') && (minefield[ctr_3][ctr_2] != '*'))
            {
                minefield[ctr_3][ctr_2]++;
            }
            if((minefield[ctr_3+1][ctr_2-1] == '*') && (minefield[ctr_3][ctr_2] != '*'))
            {
                minefield[ctr_3][ctr_2]++;
            }
            if((minefield[ctr_3+1][ctr_2] == '*') && (minefield[ctr_3][ctr_2] != '*'))
            {
                minefield[ctr_3][ctr_2]++;
            }
            if((minefield[ctr_3][ctr_2+1] == '*') && (minefield[ctr_3][ctr_2] != '*'))
            {
                minefield[ctr_3][ctr_2]++;
            }
            if((minefield[ctr_3+1][ctr_2+1] == '*') && (minefield[ctr_3][ctr_2] != '*'))
            {
                minefield[ctr_3][ctr_2]++;
            }
            ctr_3++;
        }
        ctr_3 = 0;
        ctr_2++;
    }
    ctr_3 = 0;
    ctr_2 = 0;
}

void guess(void) {
    system("cls");
        printf("\n\t\t\t\t\033[1;35m#     # ### #     # #######  #####  #     # ####### ####### ######  ####### ######\033[0m");
        printf("\n\t\t\t\t\033[1;35m##   ##  #  ##    # #       #     # #  #  # #       #       #     # #       #     #\033[0m");
        printf("\n\t\t\t\t\033[1;35m# # # #  #  # #   # #       #       #  #  # #       #       #     # #       #     #\033[0m");
        printf("\n\t\t\t\t\033[1;35m#  #  #  #  #  #  # #####    #####  #  #  # #####   #####   ######  #####   ######\033[0m");
        printf("\n\t\t\t\t\033[1;35m#     #  #  #   # # #             # #  #  # #       #       #       #       #   #\033[0m");
        printf("\n\t\t\t\t\033[1;35m#     #  #  #    ## #       #     # #  #  # #       #       #       #       #    #\033[0m");
        printf("\n\t\t\t\t\033[1;35m#     # ### #     # #######  #####   ## ##  ####### ####### #       ####### #     #\033[0m");
    int ctr_3 = 0, ctr_2 = 0, match = 0;
    print_minefield();
    while (ctr_2 < COLUMNS) {  // While loop for testing whether or not the user has cleared the minefield
        while (ctr_3 < ROWS) {
            if (minefield[ctr_3][ctr_2] == blank_minefield[ctr_3][ctr_2]) {
                match++;
            }
            ctr_3++;
        }
        ctr_3 = 0;
        ctr_2++;
    }
    if (match >= 1) {  // If the user has cleared the minefield, the win() function is run
        win();
    }
    printf("\nPress any key to reveal a random cell...");
    getch();
    for (int k = guesscount; k < 15; k++) {
        const_x = guess_x[k];
        const_y = guess_y[k];
        printf("\nCell Revealed %i %i\n", const_x, const_y);
        getch();
        fflush(stdin);
        system("pause");

        if (minefield[const_x][const_y] == '*') {
            lives--;
            if (lives != 0){
            printf("\nYou hit a bomb!");
            printf("\n%d lives left\n", lives);
            system("pause");
            print_minefield();
            }
            else if (lives == 0) {
                printf("\nYou hit a bomb!");
                printf("\n%d lives left\n", lives);
                system("pause");
                defeat();
            }
        }
        if (blank_minefield[const_x][const_y] != '-') {
            printf("\nPlease enter a value that has not already been entered\n");
            system("pause");
            continue; // continue with the next iteration
        }
        else                                                // Checks if the adctr_2acent spaces are blank, then changes the values in the blank_minefield array. Because they are changed, they will now print out in the print_minefield function
        {
            blank_minefield[const_x][const_y] = minefield[const_x][const_y];
            if( minefield[const_x][const_y] == 0 )
            {
                if( minefield[const_x-1][const_y-1] == 0 )
                {
                    blank_minefield[const_x-1][const_y] = minefield[const_x-1][const_y];
                }
                if( minefield[const_x-1][const_y] == 0 )
                {
                    blank_minefield[const_x-1][const_y] = minefield[const_x-1][const_y];
                }
                if( minefield[const_x][const_y-1] == 0 )
                {
                    blank_minefield[const_x][const_y-1] = minefield[const_x][const_y-1];
                }
                if( minefield[const_x-1][const_y+1] == 0 )
                {
                    blank_minefield[const_x-1][const_y+1] = minefield[const_x-1][const_y+1];
                }
                if( minefield[const_x+1][const_y-1] == 0 )
                {
                    blank_minefield[const_x+1][const_y-1] = minefield[const_x+1][const_y-1];
                }
                if( minefield[const_x+1][const_y] == 0 )
                {
                    blank_minefield[const_x+1][const_y] = minefield[const_x+1][const_y];
                }
                if( minefield[const_x][const_y+1] == 0 )
                {
                    blank_minefield[const_x][const_y+1] = minefield[const_x][const_y+1];
                }
                if( minefield[const_x+1][const_y+1] == 0 )
                {
                    blank_minefield[const_x+1][const_y+1] = minefield[const_x+1][const_y+1];
                }
            }
            }
                guesscount++;
            guess();
        }

    defeat();

    }



void defeat( void )                                       // Runs the print_final_minefield function, then the play_again function
{
    printf("\n\t\tYou have no lives left. You lose!\n\n");
    print_final_minefield();
    play_again();
}

void print_minefield(void) {
    int ctr_3 = 0, ctr_2 = 0, ctr_1 = 0;
    while (ctr_1 < ROWS) {
        if (ctr_1 == 0) {
            gotoxy(6, 10);
        }
        printf("   \033[1;36m%2d\033[0m  ", ctr_1 );
        ctr_1++;
    }
    printf("\n\n");

    while (ctr_2 < COLUMNS) {

        printf("\033[1;36m> %2d\033[0m  ", ctr_2 );
        while (ctr_3 < ROWS) {
            if (blank_minefield[ctr_3][ctr_2] == '-') {
                printf("  \033[1;35m[%c]\033[0m  ", blank_minefield[ctr_3][ctr_2]);
            } else if (minefield[ctr_3][ctr_2] == 0) {
                blank_minefield[ctr_3][ctr_2] = '0';
                printf("  \033[1;34m[%c]\033[0m  ", blank_minefield[ctr_3][ctr_2]);
            }
            else if (blank_minefield[ctr_3][ctr_2] == '*')
            {
                blank_minefield[ctr_3][ctr_2] = 'X';
                printf("  \033[1;31m[%c]\033[0m  ", blank_minefield[ctr_3][ctr_2]);
            }
            else if (blank_minefield[ctr_3][ctr_2] == 'X')
            {
                printf("  \033[1;31m[%c]\033[0m  ", blank_minefield[ctr_3][ctr_2]);
            }
            else
            {
                printf("  \033[1;32m[%d]\033[0m  ", blank_minefield[ctr_3][ctr_2]);
            }
            ctr_3++;
        }
        printf("\n");
        ctr_3 = 0;
        ctr_2++;
    }
}

void print_final_minefield( void )                      // Prints the minefield, showing where all of the mines are placed
{
    system("cls");
    int ctr_3 = 0, ctr_2 = 0, ctr_1 = 0;
    while (ctr_1 < ROWS) {
        if (ctr_1 == 0) {
            gotoxy(6, 3);
        }
        printf("   \033[1;36m%2d\033[0m  ", ctr_1 );
        ctr_1++;
    }
    printf("\n\n");

    while (ctr_2 < COLUMNS) {

        printf("\033[1;36m> %2d\033[0m  ", ctr_2 );
         while(ctr_3 < ROWS)
        {
            printf("  \033[1;33m[%c]\033[0m  ", final_minefield[ctr_3][ctr_2]);
            ctr_3++;
        }
        printf("\n");
        ctr_3 = 0;
        ctr_2++;
    }
}
void win(void)
{
    int ctr_3, ctr_2;
    int hidden_Non_Mines = 0;           // counter for hidden non-mine cells

    for (ctr_3 = 0; ctr_3 < ROWS; ctr_3++)
    {
        for (ctr_2 = 0; ctr_2 < COLUMNS; ctr_2++)
        {
            if (minefield[ctr_3][ctr_2] != '*' && blank_minefield[ctr_3][ctr_2] == '-')
            {
                hidden_Non_Mines++;
            }
        }
    }

    if (hidden_Non_Mines == 0)
    {
        print_final_minefield();
        printf("\nCongratulations! You win!\n");
        play_again();
    }
}

void play_again( void )                                     // Gives the user the option to play again
{
    char option[2];
    printf("\n\tWould you like to play again(Y/N)?:");
    scanf("%c", &option[0]);
    FLUSH;
    if((option[0] == 'Y') || (option[0] == 'y'))             // Restarts the program from after the welcome message
    {
        lives=3;
        guesscount=0;
        main();
    }
    else if( (option[0] == 'N') || (option[0] == 'n'))
    {
        game_over();
    }
    else
    {
        printf("\n\tPlease enter either Y or N");
        play_again();
    }
}

void game_over( void )                                  // Ends the program
{
    printf("\n\n\t\tGame Over");
    exit(1);
}
