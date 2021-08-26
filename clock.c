/*
CO222 - Clock

Project 1
Github - https://github.com/ishanfdo18098/CO222_Project1_Clock.git
Will be made public after the deadline

References,
https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

Author : Fernando K.A. Ishan - E/18/098
*/
#include <stdio.h>
#include <string.h> // to strcmp
#include <time.h>   // to get time
#include <stdlib.h> // to exit()
#include <unistd.h> // to usleep()
#include <signal.h> // to catch CTRL+C
#include <getopt.h> // to argument parse
#include <ctype.h>  // tolower()
#include <stdlib.h> // to system() - runs commands in terminal

void getTime();                                  // get time as a string in format HH:MM:SS
void printUsage();                               // print help usage
void printSupportedColors();                     // print help usage last line
void printDate();                                // print the date in the middle
void closeProgram(int dummy);                    // catch CTRL+C
void setTextColor(int color);                    // set text color before printDate()
void resetTextColor();                           // reset text color to white
void setBackgroundColor(int color);              // set backgound color for printing the big numbers
void moveToNextLineOfNumber();                   // move cursor to the next line of the current number
void moveCursorToDigit(int number);              // move cursor to the correct position for printing
void printNumber(int selectedColor, int number); // print a big number in selectedColor
void printColon(int selectedColor);              // print a colon : in selected color
void helpText();                                 // print the -h text
void resetBackgroundColor();                     // reset background color
void stringToLowercase(char array[]);            // convert string to lowercase
int parseColorOption(char color[]);              // check for valid input colors

// numbers are assigned to colors for better readability
enum colors
{
    colorBlack = 1,
    colorRed = 2,
    colorGreen = 3,
    colorYellow = 4,
    colorBlue = 5,
    colorMagenta = 6,
    colorCyan = 7,
    colorWhite = 8
};

int main(int argc, char *argv[])
{
    // for catching CTRL+C and closing the program the correct way
    signal(SIGINT, closeProgram);

    // set default color to white
    int selectedColor = colorWhite;

    // argument parsing
    char optionEntered;
    // stop "./a.out: invalid option -- 'arg'" from printing
    opterr = 0;
    while ((optionEntered = getopt(argc, argv, "c:h")) != -1) // while there are arguments left
    {
        switch (optionEntered)
        {
        case 'h': // if -h is entered
            helpText();
            exit(0);
        case 'c': //if -c is entered
            // convert optarg string to lowercase
            stringToLowercase(optarg);
            // parse the color
            selectedColor = parseColorOption(optarg);
            // if color is not valid
            if (selectedColor == -1)
            {
                printf("%s :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n", optarg);
                exit(0);
            }
            break;
        default:
            printf("Invalid use of arguments.\n");
            printUsage();
            exit(0);
        }
    }

    // enable alternative buffer, this will look like a new window (have to close this when the program exits)
    printf("\e[?1049h");
    // hide cursor (needs to be made visible when program ends) - https://stackoverflow.com/questions/30126490/how-to-hide-console-cursor-in-c
    printf("\e[?25l");
    // disable echo in terminal - to make the input from user invisible
    // https://stackoverflow.com/questions/4316730/hiding-user-input-on-terminal-in-linux-script
    // https://stackoverflow.com/questions/19209141/how-do-i-execute-a-shell-built-in-command-with-a-c-function
    system("stty -echo");

    // keep changing the text in a loop
    while (1)
    {
        // reset all the colors before doing anything
        resetTextColor();
        resetBackgroundColor();

        // get the time as a string
        char timeString[50];
        getTime(timeString);

        // print the first digit
        // subtracted 0 from ascii table to get the correct int
        // https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html
        int firstDigit = (int)timeString[0] - '0';
        moveCursorToDigit(0);
        printNumber(selectedColor, firstDigit);

        // second digit
        int secondDigit = (int)timeString[1] - '0';
        moveCursorToDigit(1);
        printNumber(selectedColor, secondDigit);

        // colon
        moveCursorToDigit(2);
        printColon(selectedColor);

        // third digit
        int thirdDigit = (int)timeString[3] - '0';
        moveCursorToDigit(3);
        printNumber(selectedColor, thirdDigit);

        // fourth digit
        int fourthDigit = (int)timeString[4] - '0';
        moveCursorToDigit(4);
        printNumber(selectedColor, fourthDigit);

        // colon
        moveCursorToDigit(5);
        printColon(selectedColor);

        // fifth digit
        int fifthDigit = (int)timeString[6] - '0';
        moveCursorToDigit(6);
        printNumber(selectedColor, fifthDigit);

        // sixth digit
        int sixthDigit = (int)timeString[7] - '0';
        moveCursorToDigit(7);
        printNumber(selectedColor, sixthDigit);

        // print date at correct location
        printf("\e[H");              // go to top left corner
        printf("\e[7B");             // go down 7 lines
        printf("\e[22C");            // go right 22 cols
        setTextColor(selectedColor); // set the color
        printDate();                 // print the date

        // sleep for some time
        usleep(1000 * 300); // sleep in micro seconds
    }
    return 0;
}

void getTime(char timeString[])
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // assign the time to timeString[] in correct format
    sprintf(timeString, "%02d:%02d:%02d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

void helpText()
{
    // print the help text when -h is given
    printUsage();
    printSupportedColors();
}

void printUsage()
{
    // print the strings when -h is given
    printf("usage : clock -h 		quick help on cmd \n");
    printf("usage : clock -c <color> 	print clock with a color \n");
}

void printSupportedColors()
{
    // print the color values
    printf("<color-black|red|green|yellow|blue|magenta|cyan|white> 	supported colors\n");
}

// check validity of input color name
int parseColorOption(char color[])
{
    // default to error and then change if valid
    int colorNeeded = -1;

    // assign the correct color to be returned
    if (strcmp(color, "black") == 0)
    {
        colorNeeded = colorBlack;
    }
    else if (strcmp(color, "red") == 0)
    {
        colorNeeded = colorRed;
    }
    else if (strcmp(color, "green") == 0)
    {
        colorNeeded = colorGreen;
    }
    else if (strcmp(color, "yellow") == 0)
    {
        colorNeeded = colorYellow;
    }
    else if (strcmp(color, "blue") == 0)
    {
        colorNeeded = colorBlue;
    }
    else if (strcmp(color, "magenta") == 0)
    {
        colorNeeded = colorMagenta;
    }
    else if (strcmp(color, "cyan") == 0)
    {
        colorNeeded = colorCyan;
    }
    else if (strcmp(color, "white") == 0)
    {
        colorNeeded = colorWhite;
    }

    return colorNeeded;
}

void printDate()
{
    // print the date in correct format in the current cursor position

    // https://www.techiedelight.com/print-current-date-and-time-in-c/

    // variables to store the date and time components
    int day, month, year;

    // `time_t` is an arithmetic time type
    time_t now;

    // Obtain current time
    // `time()` returns the current time of the system as a `time_t` value
    time(&now);

    // localtime converts a `time_t` value to calendar time and
    // returns a pointer to a `tm` structure with its members
    // filled with the corresponding values
    struct tm *local = localtime(&now);

    day = local->tm_mday;         // get day of month (1 to 31)
    month = local->tm_mon + 1;    // get month of year (0 to 11)
    year = local->tm_year + 1900; // get year since 1900

    // print the current date
    // printf("Date is: %02d/%02d/%d\n", day, month, year);
    printf("%d-%02d-%02d\n", year, month, day);
}

// catch CTRL+C
// Then close alternative buffer
// Make cursor visible
void closeProgram(int dummy)
{
    printf("\e[?1049l"); // disable alternative buffer
    printf("\e[?25h");   // make cursor visible
    system("stty echo"); // enable echo in terminal
    resetBackgroundColor();
    resetTextColor();
    exit(0);
}

void setTextColor(int color)
{
    // set text color for printing the date

    // this is called foreground color officially
    char BLACK[] = "\e[30m";
    char RED[] = "\e[31m";
    char GREEN[] = "\e[32m";
    char YELLOW[] = "\e[33m";
    char BLUE[] = "\e[34m";
    char MAGENTA[] = "\e[35m";
    char CYAN[] = "\e[36m";
    char WHITE[] = "\e[37m";

    switch (color)
    {
    case colorBlack:
        printf("%s", BLACK);
        break;
    case colorRed:
        printf("%s", RED);
        break;
    case colorGreen:
        printf("%s", GREEN);
        break;
    case colorYellow:
        printf("%s", YELLOW);
        break;
    case colorBlue:
        printf("%s", BLUE);
        break;
    case colorMagenta:
        printf("%s", MAGENTA);
        break;
    case colorCyan:
        printf("%s", CYAN);
        break;
    case colorWhite:
        printf("%s", WHITE);
        break;
    }
}

void setBackgroundColor(int color)
{
    // set background color for printing spaces

    char BLACK[] = "\e[40m";
    char RED[] = "\e[41m";
    char GREEN[] = "\e[42m";
    char YELLOW[] = "\e[43m";
    char BLUE[] = "\e[44m";
    char MAGENTA[] = "\e[45m";
    char CYAN[] = "\e[46m";
    char WHITE[] = "\e[47m";

    switch (color)
    {
    case colorBlack:
        printf("%s", BLACK);
        break;
    case colorRed:
        printf("%s", RED);
        break;
    case colorGreen:
        printf("%s", GREEN);
        break;
    case colorYellow:
        printf("%s", YELLOW);
        break;
    case colorBlue:
        printf("%s", BLUE);
        break;
    case colorMagenta:
        printf("%s", MAGENTA);
        break;
    case colorCyan:
        printf("%s", CYAN);
        break;
    case colorWhite:
        printf("%s", WHITE);
        break;
    }
}

void resetTextColor()
{
    // reset color to white as thats used in the original program
    char WHITE[] = "\e[37m";
    printf("%s", WHITE);
}

void resetBackgroundColor()
{
    // reset color
    char RESET[] = "\e[0m";
    printf("%s", RESET);
}

void printColon(int selectedColor)
{
    // print a colon using printNumber() function
    printNumber(selectedColor, 10);
}

void printNumber(int selectedColor, int number)
{
    // create the numbers as matrix
    // numbers[number][row_of_each_number][column_of_each_number]
    int numbers[11][5][6] = {
        {{1, 1, 1, 1, 1, 1}, // number 0
         {1, 1, 0, 0, 1, 1},
         {1, 1, 0, 0, 1, 1},
         {1, 1, 0, 0, 1, 1},
         {1, 1, 1, 1, 1, 1}},

        {{0, 0, 0, 0, 1, 1}, // number 1
         {0, 0, 0, 0, 1, 1},
         {0, 0, 0, 0, 1, 1},
         {0, 0, 0, 0, 1, 1},
         {0, 0, 0, 0, 1, 1}},

        {{1, 1, 1, 1, 1, 1}, // number 2
         {0, 0, 0, 0, 1, 1},
         {1, 1, 1, 1, 1, 1},
         {1, 1, 0, 0, 0, 0},
         {1, 1, 1, 1, 1, 1}},

        {{1, 1, 1, 1, 1, 1}, // number 3
         {0, 0, 0, 0, 1, 1},
         {1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 1, 1},
         {1, 1, 1, 1, 1, 1}},

        {{1, 1, 0, 0, 1, 1}, // number 4
         {1, 1, 0, 0, 1, 1},
         {1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 1, 1},
         {0, 0, 0, 0, 1, 1}},

        {{1, 1, 1, 1, 1, 1}, // number 5
         {1, 1, 0, 0, 0, 0},
         {1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 1, 1},
         {1, 1, 1, 1, 1, 1}},

        {{1, 1, 1, 1, 1, 1}, // number 6
         {1, 1, 0, 0, 0, 0},
         {1, 1, 1, 1, 1, 1},
         {1, 1, 0, 0, 1, 1},
         {1, 1, 1, 1, 1, 1}},

        {{1, 1, 1, 1, 1, 1}, // number 7
         {0, 0, 0, 0, 1, 1},
         {0, 0, 0, 0, 1, 1},
         {0, 0, 0, 0, 1, 1},
         {0, 0, 0, 0, 1, 1}},

        {{1, 1, 1, 1, 1, 1}, // number 8
         {1, 1, 0, 0, 1, 1},
         {1, 1, 1, 1, 1, 1},
         {1, 1, 0, 0, 1, 1},
         {1, 1, 1, 1, 1, 1}},

        {{1, 1, 1, 1, 1, 1}, // number 9
         {1, 1, 0, 0, 1, 1},
         {1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 1, 1},
         {1, 1, 1, 1, 1, 1}},

        {{0, 0, 0, 0, 0, 0}, // colon sign
         {0, 0, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0},
         {0, 0, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0}}};

    // select the correct number from the 3D matrix and then start printing
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 6; col++)
        {
            // reset colors
            resetBackgroundColor();
            // if its a zero, then print space without colors
            if (numbers[number][row][col] == 0)
            {
                printf(" ");
            }
            // if its 1, print space with selectedColor
            else if (numbers[number][row][col] == 1)
            {
                setBackgroundColor(selectedColor); // set the color
                printf(" ");
                resetBackgroundColor(); // reset the color
            }
        }
        // when chaning rows, have to change the line in termianl
        moveToNextLineOfNumber();
    }
}

void moveToNextLineOfNumber()
{
    // move one line down
    // then move 6 cols to the left
    printf("\e[1B"); // 1 down
    printf("\e[6D"); // 6 left
}

void moveCursorToDigit(int number)
{
    // move the cursor to correct position before printing the big number
    printf("\e[H");  // move cursor to 0,0
    printf("\e[1B"); // go to line 1
    printf("\e[");   // go to correct col

    // numbers dont have much of a pattern because of the colon only having 6 spaces for it
    // all the other numbers have 7 spaces
    switch (number)
    {
    case 0:
        printf("1C");
        break;
    case 1:
        printf("8C");
        break;
    case 2:
        printf("14C");
        break;
    case 3:
        printf("20C");
        break;
    case 4:
        printf("27C");
        break;
    case 5:
        printf("33C");
        break;
    case 6:
        printf("39C");
        break;
    case 7:
        printf("46C");
        break;
    }
}

// convert string to lowercase
void stringToLowercase(char array[])
{
    for (int i = 0; array[i]; i++)
    {
        array[i] = tolower(array[i]);
    }
}