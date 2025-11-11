# Welcome to My Printf
***

## Task
The task was to write a function that acts similar to the printf function.

## Description
The my_printf(char *restrict format, ...) function prints out a string and handles the following
conversion specifications that it finds within the string - %d for signed decimal, %o for unsigned octal,
%u for unsigned decimal, %x for unsigned hexadecimal, %s for string, %c for char and %p for pointer.
Apart from the string it takes a variadic argument list. The function uses a helper function numtostr
to convert numbers to different number systems when necessary, as well as convert them to strings.

## Installation
The project can be compiled with GCC. You can compile it together with your own .c file that contains
a main function, e.g. "gcc -Wall -Wextra -Werror my_printf.c your_main_file.c -o program"

## Usage
Parameters can be passed into the function the following way:
```
my_printf("The cat goes %s!\n", "meow");
my_printf("My cat is %d years old\n", 5);
my_printf("If I could, I would get %u cats instead of %u\n", 2, 1);
```

### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
