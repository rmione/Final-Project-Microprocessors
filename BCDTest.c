#include <stdio.h>
#include <stdlib.h>

short to_binary(short k) {
    // Recursive function to change an integer into a binary representation. 
    if (k == 0) return 0;
    if (k == 1) return 1;   
    printf("\nrecursion"); // we need to go deeper
    return (k % 2) + 10 * to_binary(k / 2);
}
short *toBCD(short angle) {
    short ones = angle % 10; // extracts ones column of angle < 90
    short tens = angle / 10; // extracts tens column of angle < 90 
    static short arr[2]; // 2 element long array to hold BCD
    
    arr[0] = to_binary(ones);
    arr[1] = to_binary(tens); 
    printf("\nValue of ones %d", to_binary(ones));
    printf("\nValue of tens %d", to_binary(tens));

    return arr; // Return a pointer to our BCD array! 

}

void main(int argc, const char* argv[] ){
    short *result = toBCD(99);
    printf("\n"); 
    printf("%d", result[0]); 
    printf("\n"); 
    printf("%d", result[0]); 

}