#include <stdio.h>
#include <string.h>
#include <time.h>

int magnitude(int test) {
    int count = 0;

    while(test != 0)
    {
        test /= 10;
        count++;
    }

    return count;
}

char* lessThanTwenty(int value) {
    switch (value)
    {
        case 0:
            return "";
            break;
        case 1:
            return "One ";
            break;
        case 2:
            return "Two ";
            break;
        case 3:
            return "Three ";
            break;
        case 4:
            return "Four ";
            break;
        case 5:
            return "Five ";
            break;
        case 6:
            return "Six ";
            break;
        case 7:
            return "Seven ";
            break;
        case 8:
            return "Eight ";
            break;
        case 9:
            return "Nine ";
            break;
        case 10:
            return "Ten ";
            break;
        case 11:
            return "Eleven ";
            break;
        case 12:
            return "Twelve ";
            break;
        case 13:
            return "Thirteen ";
            break;
        case 14:
            return "Fourteen ";
            break;
        case 15:
            return "Fifteen ";
            break;
        case 16:
            return "Sixteen ";
            break;
        case 17:
            return "Seventeen ";
            break;
        case 18:
            return "Eighteen ";
            break;
        case 19:
            return "Nineteen ";
            break;
        default:
            return "huh?";
            break;
    }
}

char* lessThanHundred(int value) {
    int ones = value % 10;
    int tens = (value - ones) / 10;
    char dest [20];

    switch(tens)
    {
        case 0:
            return strcat(dest, lessThanTwenty(ones));
            break;
        case 1:
            return strcat(dest, lessThanTwenty(value));
            break;
        case 2:
            strcpy(dest, "Twenty ");
            return strcat(dest,lessThanTwenty(ones));
            break;
        case 3:
            strcpy(dest, "Thirty ");
            return strcat(dest,lessThanTwenty(ones));
            break;
        case 4:
            strcpy(dest, "Fourty ");
            return strcat(dest,lessThanTwenty(ones));
            break;
        case 5:
            strcpy(dest, "Fifty ");
            return strcat(dest,lessThanTwenty(ones));
            break;
        case 6:
            strcpy(dest, "Sixty ");
            return strcat(dest,lessThanTwenty(ones));
            break;
        case 7:
            strcpy(dest, "Seventy ");
            return strcat(dest,lessThanTwenty(ones));
            break;
        case 8:
            strcpy(dest, "Eighty ");
            return strcat(dest,lessThanTwenty(ones));
            break;
        case 9:
            strcpy(dest, "Ninety ");
            return strcat(dest,lessThanTwenty(ones));
            break;
    }
}

char* lessThanThousand(int value) {
    int remainder = value % 100;
    int hundreds = (value - remainder) / 100;
    char dest [40];

    if(hundreds == 0)
        return strcpy(dest,lessThanHundred(remainder));

    strcpy(dest, lessThanTwenty(hundreds));
    strcat(dest, "Hundred ");
    return strcat(dest,lessThanHundred(remainder));
}

char* lessThanMillion(int value) {
    int remainder = value % 1000;
    int thousands = (value - remainder) / 1000;
    char dest [80];

    strcpy(dest, lessThanThousand(thousands));
    strcat(dest, "Thousand ");
    if (remainder != 0)
        strcat(dest, lessThanThousand(remainder));
    return strcat(dest, "");
}

char* lessThanBillion(int value) {
    int remainder = value % 1000000;
    int millions = (value - remainder) / 1000000;
    char dest [120];

    strcpy(dest, lessThanThousand(millions));
    strcat(dest, "Million ");
    if (remainder != 0)
        strcat(dest, lessThanMillion(remainder));
    return strcat(dest, "");
}

void main() {
    clock_t start, end;
    double elapsed;
    int input, mag;
    char output [200];

    printf("Enter an Integer: ");
    scanf("%d", &input);

    ////////////////////////
    start = clock(); // Time Begins
    ////////////////////////

    if (input < 0)
    {
        input *= -1;
        strcat(output, "Negative ");
    }

    mag = magnitude(input);
    
    switch(mag) 
    {
        case 0:
            strcat(output,"Zero ");
            break;
        case 1:
        case 2:
            if (input < 20)
                strcat(output,lessThanTwenty(input));
            else
                strcat(output,lessThanHundred(input));
            break;
        case 3:
            strcat(output, lessThanThousand(input));
            break;
        case 4:
        case 5:
        case 6:
            strcat(output, lessThanMillion(input));
            break;
        case 7:
        case 8:
        case 9:
            strcat(output, lessThanBillion(input));
            break;
        default:
            strcat(output,"Number too large!"); 
    }

    ////////////////////
    end = clock();// Time Ends
    ////////////////////

    printf("%s\n", output);
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTime Elapsed : %f seconds\n", elapsed); 
}