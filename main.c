#include <stdio.h>
#include <stdlib.h>

/**
 * Constants
 */
#define ARGUMENTS_NEEDED 2

#define _1_CHAR 35
#define PRIME 1
#define PRIME_CHAR 43
#define NOT_PRIME 0
#define NOT_PRIME_CHAR 45//32

#define N_DIRECTIONS 4
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

#define ERROR_ARGC 0
#define ERROR_EVEN 1
#define ERROR_NEGATIVE 2

/**
 * Type declarations
 */
typedef struct ulam_spiral_t ulam_spiral;

/**
 * Method headers
 */
int main(int argc, const char *argv[]);
static char is_prime(int number);
static void print_grid(const char grid[], int length);
static void draw_ulam_spiral(int length);
static void change_direction(ulam_spiral *data);
static void move(ulam_spiral *data);
static void print_data(const ulam_spiral data);

/**
 * Type definitions
 */
typedef struct ulam_spiral_t
{
	int length;
	int iteration;
	int hor_offset;
	int ver_offset;
	int current_step;
	int step_counter;
	int direction_trigger;
	int step_trigger;
	char direction;
} ulam_spiral;

/**
 * Method implementations
 */
static char is_prime(int number)
{
	int limit = number/2;
	int n_divisors = 0;

	printf("Checking if %d is prime\n", number);
	for (int n = 1; n <= limit; n++)
	{
		if ((number % n) == 0)
		{
			printf("\t%d is divisor of %d\n", n, number);
			n_divisors++;
		}
	}
	return n_divisors == PRIME;
}

static void print_grid(const char grid[], int length)
{
	int _1_pos = length / 2;
	for (int column = 0; column != length; ++column)
	{
		for (int row = 0; row != length; ++row)
		{
			int array_pos = row + column * length;
			char print_char = (grid[array_pos] == PRIME) ? PRIME_CHAR : NOT_PRIME_CHAR;
			if (column == _1_pos && row == _1_pos)
			{
				print_char = _1_CHAR;
			}
			printf("%c", print_char);
		}
		printf("\n");
	}
}

static void draw_ulam_spiral(int length)
{
	int starting_position = length/2;

	ulam_spiral data;
	data.length = length;
	data.hor_offset = starting_position;
	data.ver_offset = starting_position;
	data.iteration = 0;
	data.current_step = 1;
	data.step_counter = 0;
	data.direction_trigger = data.current_step;
	data.step_trigger = 2 * data.current_step;
	data.direction = DOWN;

	int size = length * length;
	char ulam_grid[size];

	while (data.iteration < size)
	{
		print_data(data);

		// Paint respective cell
		int number = data.iteration + 1;
		char number_is_prime = is_prime(number);

		int grid_pos = data.hor_offset + data.ver_offset * length;
		ulam_grid[grid_pos] = number_is_prime;

		printf("%d at position (%d, %d) is prime: %hhd\n", number, data.hor_offset, data.ver_offset, number_is_prime);

		// Change direction
		change_direction(&data);

		// Move
		move(&data);
		printf("Next position: (%d, %d)\n", data.hor_offset, data.ver_offset);

		// Update
		printf("Iteration and step counter increase\n");
		data.iteration++;
		data.step_counter++;
		printf("\n");
	}
	print_grid(ulam_grid, length);
}

static void change_direction(ulam_spiral *data)
{
	printf("Current direction: %hhd\n", data->direction);
	if (data->step_counter == data->direction_trigger)
	{
		data->direction = (data->direction + 1)%N_DIRECTIONS;
		printf("Direction trigger. Changing direction. New direction: %hhd\n", data->direction);
	}
	if (data->step_counter == data->step_trigger)
	{
		data->direction = (data->direction + 1) % N_DIRECTIONS;
		data->current_step++;
		data->step_counter = 0;
		data->direction_trigger = data->current_step;
		data->step_trigger = 2 * data->current_step;
		printf("Step trigger. Changing direction. New direction: %hhd\n", data->direction);
		printf("Reseting step counter (%d), direction trigger (%d) and step_trigger(%d)\n",
			data->step_counter, data->direction_trigger, data->step_trigger);
	}
}

static void move(ulam_spiral *data)
{
	switch (data->direction)
	{
		case UP:
			data->ver_offset--;
			break;
		case LEFT:
			data->hor_offset--;
			break;
		case DOWN:
			data->ver_offset++;
			break;
		case RIGHT:
			data->hor_offset++;
			break;
		default:
			printf("Error advancing positions. DIRECTION: %hhd", data->direction);
			exit(-1);
	}
}

static void print_data(const ulam_spiral data)
{
	printf("[DATA]\n");
	printf("\tIteration %d\n", data.iteration);
	printf("\tX index: %d\n", data.hor_offset);
	printf("\tY index: %d\n", data.ver_offset);
	printf("\tStep: %d\n", data.current_step);
	printf("\tSteps taken this lap: %d\n", data.step_counter);
	printf("\tDirection trigger: %d\n", data.direction_trigger);
	printf("\tStep trigger: %d\n", data.step_trigger);
	printf("\tDirection: %hhd\n", data.direction);
}

int main(int argc, const char *argv[])
{
	// Argument checking
	if (argc != ARGUMENTS_NEEDED)
	{
		printf("ERROR. Error code: %u\n", ERROR_ARGC);
		return ERROR_ARGC;
	}

	int length = atoi(argv[1]);
	if ((length % 2) == 0)
	{
		printf("ERROR. Error code: %u\n", ERROR_EVEN);
		return ERROR_EVEN;
	}

	if (length <= 0)
	{
		printf("ERROR. Error code: %u\n", ERROR_NEGATIVE);
		return ERROR_NEGATIVE;
	}
	// End argument checking

	int size = length * length * sizeof(char);
	printf("Length: %d\n", length);
	printf("Grid size: %d\n\n", size);

	draw_ulam_spiral(length);

	return 0;
}
