#include <stdio.h>
#include <stdlib.h>

/**
 * Constants & enums
 */
#define PRIME 1
#define NOT_PRIME 0

enum character {
    _1_char = 35,
    prime_char = 43,
    not_prime_char = 45
};

enum direction { up, left, down, right, n_directions };
enum error { no_error, error_even, error_negative };

/**
 * Type declarations
 */
typedef struct ulam_spiral_t ulam_spiral;
typedef struct ulam_properties_t ulam_properties;

/**
 * Method headers
 */
/**
 * Function that uses primality test to check if the given argument is a prime number
 */
char is_prime(int number);

/**
 * Calculates an n x n ulam spiral, where n is the argument given. Returns the spiral
 */
ulam_spiral calculate_ulam_spiral(int length);

/**
 * Prints in screen the given ulam spiral
 */
void print_ulam_spiral(const ulam_spiral spiral);
static void change_direction(ulam_properties *properties);
static void move(ulam_properties *properties);
static void print_properties(const ulam_properties properties);

/**
 * Type definitions
 */
typedef struct ulam_spiral_t {
    char *grid;
    unsigned int length;
    unsigned char return_value;
} ulam_spiral;

typedef struct ulam_properties_t {
    int iteration;
    int hor_index;
    int ver_index;
    int current_step;
    int step_counter;
    int direction_trigger;
    int step_trigger;
    char direction;
} ulam_properties;