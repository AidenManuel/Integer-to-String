#include <stdio.h>
#include <string.h>
#include <time.h>

int magnitude(int test) {
    int count;

    asm volatile(".intel_syntax noprefix ;"
                 "loop:                  ;"
                 "mov edx, 0              ;"
                 "div ecx                ;"
                 "inc rbx                ;"
                 "cmp edx, 0              ;"
                 "jne loop               ;"
                 ".att_syntax;"
                 :"=b"(count)
                 :"a"(test), "b"(0), "c"(10), "d"(0)
                 :"cc");

    return count - 1;
}

char* lessThanTwenty(int value) {
    if (value > 0) goto one;
    return "";
    one:
        if (value > 1) goto two;
        return "One ";
    two:
        if (value > 2) goto three;
        return "Two ";
    three:
        if (value > 3) goto four;
        return "Three ";
    four:
        if (value > 4) goto five;
        return "Four ";
    five:
        if (value > 5) goto six;
        return "Five ";
    six:
        if (value > 6) goto seven;
        return "Six ";
    seven:
        if (value > 7) goto eight;
        return "Seven ";
    eight:
        if (value > 8) goto nine;
        return "Eight ";
    nine:
        if (value > 9) goto ten;
        return "Nine ";
    ten:
        if (value > 10) goto eleven;
        return "Ten ";
    eleven:
        if (value > 11) goto twelve;
        return "Eleven ";
    twelve:
        if (value > 12) goto thirteen;
        return "Twelve ";
    thirteen:
        if (value > 13) goto fourteen;
        return "Thirteen ";
    fourteen:
        if (value > 14) goto fifteen;
        return "Fourteen ";
    fifteen:
        if (value > 15) goto sixteen;
        return "Fifteen ";
    sixteen:
        if (value > 16) goto seventeen;
        return "Sixteen ";
    seventeen:
        if (value > 17) goto eighteen;
        return "Seventeen ";
    eighteen:
        if (value > 18) goto nineteen;
        return "Eighteen ";
    nineteen:
        if (value > 19) goto whatintarnation;
        return "Nineteen ";
    whatintarnation:
        return "huh?";
}

char* lessThanHundred(int value) {
    int ones = value % 10;
    int tens = (value - ones) / 10;
    char dest [20];

    if (tens > 0) goto ten;
    return strcat(dest, lessThanTwenty(ones));
    ten:
        if (tens > 1) goto twenty;
        return strcat(dest, lessThanTwenty(value));
    twenty:
        if (tens > 2) goto thirty;
        strcpy(dest, "Twenty ");
        return strcat(dest,lessThanTwenty(ones));
    thirty:
        if (tens > 3) goto fourty;
        strcpy(dest, "Thirty ");
        return strcat(dest,lessThanTwenty(ones));
    fourty:
        if (tens > 4) goto fifty;
        strcpy(dest, "Fourty ");
        return strcat(dest,lessThanTwenty(ones));
    fifty:
        if (tens > 5) goto sixty;
        strcpy(dest, "Fifty ");
        return strcat(dest,lessThanTwenty(ones));
    sixty:
        if (tens > 6) goto seventy;
        strcpy(dest, "Sixty ");
        return strcat(dest,lessThanTwenty(ones));
    seventy:
        if (tens > 7) goto eighty;
        strcpy(dest, "Seventy ");
        return strcat(dest,lessThanTwenty(ones));
    eighty:
        if (tens > 8) goto ninety;
        strcpy(dest, "Eighty ");
        return strcat(dest,lessThanTwenty(ones));
    ninety:
        strcpy(dest, "Ninety ");
        return strcat(dest,lessThanTwenty(ones));
}

char* lessThanThousand(int value) {
    int remainder = value % 100;
    int hundreds = value / 100;
    char dest [40];

    if(hundreds == 0)
        return strcpy(dest,lessThanHundred(remainder));

    strcpy(dest, lessThanTwenty(hundreds));
    strcat(dest, "Hundred ");
    return strcat(dest,lessThanHundred(remainder));
}

char* lessThanMillion(int value) {
    int remainder = value % 1000;
    int thousands = value / 1000;
    char dest [80];

    strcpy(dest, lessThanThousand(thousands));
    strcat(dest, "Thousand ");
    if (remainder != 0)
        strcat(dest, lessThanThousand(remainder));
    return strcat(dest, "");
}

char* lessThanBillion(int value) {
    int remainder = value % 1000000;
    int millions = value / 1000000;
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
    
    if (mag == 0) goto zero;
    if (mag <= 2) goto two;
    if (mag <= 3) goto three;
    if (mag <= 6) goto fourtosix;
    if (mag <= 9) goto seventonine;
    goto bignum;
    
    zero:
        strcat(output,"Zero ");
        goto end;
    two:
        if (input < 20)
            strcat(output,lessThanTwenty(input));
        else
            strcat(output,lessThanHundred(input));
        goto end;
    three:
        strcat(output, lessThanThousand(input));
        goto end;
    fourtosix:
        strcat(output, lessThanMillion(input));
        goto end;
    seventonine:
        strcat(output, lessThanBillion(input));
        goto end;
    bignum:
        strcat(output,"Number too large!"); 

    end:

        ////////////////////
        end = clock();// Time Ends
        ////////////////////
    
        printf("%s\n", output);
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\nTime Elapsed : %f seconds\n", elapsed); 
}