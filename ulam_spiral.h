#include <stdio.h>
#include <stdlib.h>

/**
 * Constants
 */
#define _1_CHAR 35
#define PRIME 1
#define PRIME_CHAR 43
#define NOT_PRIME 0
#define NOT_PRIME_CHAR 45

#define N_DIRECTIONS 4
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

#define NO_ERRORS 0
#define ERROR_EVEN 1
#define ERROR_NEGATIVE 2

/**
 * Type declarations
 */
typedef struct ulam_spiral_t ulam_spiral;
typedef struct ulam_properties_t ulam_properties;

/**
 * Method headers
 */
char is_prime(int number);
ulam_spiral calculate_ulam_spiral(int length);
void print_ulam_spiral(const ulam_spiral spiral);
static void change_direction(ulam_properties *properties);
static void move(ulam_properties *properties);
static void print_properties(const ulam_properties properties);

/**
 * Type definitions
 */
typedef struct ulam_spiral_t
{
    char *grid;
    unsigned int length;
    unsigned char return_value;
} ulam_spiral;

typedef struct ulam_properties_t
{
    int iteration;
    int hor_index;
    int ver_index;
    int current_step;
    int step_counter;
    int direction_trigger;
    int step_trigger;
    char direction;
} ulam_properties;