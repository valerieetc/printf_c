#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int numtostr(unsigned long num, int base, char c);

int my_printf(char *restrict format, ...) {
    va_list args;
    va_start(args, format);
    int counter = 0;

    //loop that prints fom the string until it hits '%'. after it hits '%', it goes to specific cases
    int i = 0;
    while (format[i] != '\0') {
        if (format[i] != '%') {
            write(1, &format[i], 1);
            counter++;
        } else if (format[i] == '%') {
            if (format[i + 1] == 'd') {
                //retrieves int
                int number = va_arg(args, int); 

                //if number is negative, prints out '-', then turns to positive
                if (number < 0) {
                    write(1, "-", 1);
                    counter++;
                    number = number * (-1);
                }

                //turns already positive int into unsigned int to pass into function
                unsigned int num = number;
                counter = counter + numtostr(num, 10, 'd');
            } else if (format[i + 1] == 'u') {
                //retrieves unsigned int, passes it into function to print
                unsigned int num = va_arg(args, unsigned int);
                counter = counter + numtostr(num, 10, 'u');
            } else if (format[i + 1] == 'x') {
                //retrieves unsigned int, passes it into function to convert and print
                unsigned int num = va_arg(args, unsigned int);
                counter = counter + numtostr(num, 16, 'x');
            } else if (format[i + 1] == 'o') {
                //retrieves unsigned int, passes it into function to convert and print
                unsigned int num = va_arg(args, unsigned int);
                counter = counter + numtostr(num, 8, 'o');
            } else if (format[i + 1] == 'p') {
                //retrieves pointer, casts it to unsigned long
                void *ptr = va_arg(args, void *);
                unsigned long pointer = (unsigned long)ptr;
                //writes "0x" before the rest of the hexadecimal number
                write(1, "0x", 2);
                //passes pointer into function to convert and print
                counter = counter + 2 + numtostr(pointer, 16, 'p'); 
            } else if (format[i + 1] == 's') {
                //retrieves string, checks if string is valid, if yes prints its contents
                char *str = va_arg(args, char *);
                if (str == NULL) {
                    write(1, "(null)", 6);
                    counter = counter + 6;
                } else {
                    int j = 0;
                    while (str[j] != '\0') {
                        write(1, &str[j], 1);
                        j++;
                        counter++;
                    } 
                }
            } else if (format[i + 1] == 'c') {
                //retrieves and prints char
                char c = va_arg(args, int);
                write(1, &c, 1);
                counter++;
            }
            i++;
        }
        i++;
    }
    va_end(args);
    return counter;
}

//converts numbers to a specific system, turns them to strings and prints, returns number of chars printed
//int base corresponds to the number system, char c parameter distinguishes between uppercase for %x and lowercase for %p
int numtostr(unsigned long num, int base, char c) {
    int counter = 0;

    //checks if number is 0
    if (num == 0) {
        write(1, "0", 1);
        counter++;
    } else {
        unsigned long numcopy = num;

        //counts number of digits
        int numlength = 0;
        while (num != 0) {
            num = num / base;
            numlength++;
        }
        
        //declares string and fills it with digits converted to chars
        char *numstr = malloc(numlength + 1);
        int j = numlength;
        int remainder = 0;
        numstr[j] = '\0';             
        while (numcopy != 0) {
            remainder = numcopy % base;
            //if remainder is >= 10 in case of hex conversion, converts remainder to letters
            if (remainder >= 10 && c == 'x') {
                numstr[j - 1] = remainder + 55;
            } else if (remainder >= 10 && c == 'p') {
                numstr[j - 1] = remainder + 87;
            } else {
                numstr[j - 1] = remainder + 48;
            }
            numcopy = numcopy / base;
            j--;
        }

        //prints out the string
        write(1, numstr, numlength);
        free(numstr);
        counter = counter + numlength;
        }    
    return counter;
}
