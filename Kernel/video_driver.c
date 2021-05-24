#include "video_driver.h"

#define HEIGHT 25
#define WIDTH 80
#define MAX_DIGITS 15

static char *screen_start = (char *) 0xB8000;

void print_str(char *str, char color, int row, int column){
    int position = (WIDTH * row + column) * 2;
    int i = position;
    while (*str != '\0'){
        screen_start[i] = *str++;
        screen_start[i + 1] = color;
        i += 2;
    }
}

void print_char(char c, char color, int row, int column){
    print(&c, 1, color, row, column);
}

void print_number(int number, char color, int row, int column){
    unsigned int digits = count_digits(number);
    char str[MAX_DIGITS];
    int k = 0;
    if(number < 0){
        number *= -1;
        str[0] = '-';
        digits +=1;
        k = 1;
    }
    for(int i = digits - 1; i >= k; i--){
        str[i] = (number % 10) + '0';
        number /= 10;
    }
    print(str, digits, color, row, column);
}

void print(char *str, int length, char color, int row, int column){
    int position = (WIDTH * row + column) * 2;
    int len = length * 2;
    for(int i = position; i < len + position; i += 2){
        screen_start[i] = *str++;
        screen_start[i+1] = color;
    }
}

int str_len(char *str){
    int count;
    for(count = 0; str[count] != '\0'; count++){
        ;
    }
    return count;
}

unsigned int count_digits(int num){
    int digits = 1;
    if(num < 0)
        num *= -1;
    while((num/=10) > 0)
        digits++;
    return digits;
}

void clear(){
    print("\0", HEIGHT * WIDTH, 0x00, 0, 0);
}