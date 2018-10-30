#include "ulam_spiral.h"

char is_prime(int number)
{
	if (number == 2 || number == 3)
	{
		return PRIME;
	}

	if (number == 1 || !(number & 1) || (number % 3) == 0)
	{
		return NOT_PRIME;
	}

	int i = 5, w = 2;

	while ((i * i) <= number) 
	{
		if ((number % 1) == 0)
		{
			return NOT_PRIME;
		}

		i += w;
		w = 6 - w;
	}
	return PRIME;
}

ulam_spiral calculate_ulam_spiral(int length)
{
	int size = length * length;
	ulam_spiral spiral;
    spiral.length = (unsigned int)length;
    spiral.grid = (char*)calloc(sizeof(char), size);

	if ((length % 2) == 0)
	{
		printf("ERROR (code: %u): Length argument must be an odd number\n", ERROR_EVEN);
		spiral.return_value = ERROR_EVEN;
		return spiral;
	}
	else if (length <= 0)
	{
		printf("ERROR (code: %u): Length must be positive\n", ERROR_NEGATIVE);
		spiral.return_value = ERROR_NEGATIVE;
		return spiral;
	}

	int starting_position = length/2;

    ulam_properties properties;
    properties.iteration = 0;
    properties.hor_index = starting_position;
    properties.ver_index = starting_position;
    properties.current_step = 1;
    properties.step_counter = 0;
    properties.direction_trigger = 1;
    properties.step_trigger = 2;
    properties.direction = DOWN;

	while (properties.iteration < size)
	{
		print_properties(properties);

		// Paint respective cell
		int number = properties.iteration + 1;
		char number_is_prime = is_prime(number);

		int grid_pos = properties.hor_index + properties.ver_index * length;
		spiral.grid[grid_pos] = number_is_prime;

		printf("%d at position (%d, %d) is prime: %hhd\n", number, properties.hor_index, properties.ver_index, number_is_prime);

		// Change direction
		change_direction(&properties);

		// Move
		move(&properties);
		printf("Next position: (%d, %d)\n", properties.hor_index, properties.ver_index);

		// Update
		printf("Iteration and step counter increase\n");
		properties.iteration++;
		properties.step_counter++;
		printf("\n");
	}
	spiral.return_value = NO_ERRORS;
    return spiral;
}

void print_ulam_spiral(const ulam_spiral spiral)
{
	if (spiral.return_value != NO_ERRORS)
	{
		printf("There were errors when calculating the spiral. Error code: %hhu\n", spiral.return_value);
		return;
	}

	int _1_pos = spiral.length / 2;
	for (int column = 0; column != spiral.length; ++column)
	{
		for (int row = 0; row != spiral.length; ++row)
		{
			int grid_pos = row + column * spiral.length;
			char print_char = (spiral.grid[grid_pos] == PRIME) ? PRIME_CHAR : NOT_PRIME_CHAR;
			if (column == _1_pos && row == _1_pos)
			{
				print_char = _1_CHAR;
			}
			printf("%c", print_char);
		}
		printf("\n");
	}
}

static void change_direction(ulam_properties *properties)
{
	printf("Current direction: %hhd\n", properties->direction);
	if (properties->step_counter == properties->direction_trigger)
	{
		properties->direction = (properties->direction + 1)%N_DIRECTIONS;
		printf("Direction trigger. Changing direction. New direction: %hhd\n", properties->direction);
	}
	if (properties->step_counter == properties->step_trigger)
	{
		properties->direction = (properties->direction + 1) % N_DIRECTIONS;
		properties->current_step++;
		properties->step_counter = 0;
		properties->direction_trigger = properties->current_step;
		properties->step_trigger = 2 * properties->current_step;
		printf("Step trigger. Changing direction. New direction: %hhd\n", properties->direction);
		printf("Reseting step counter (%d), direction trigger (%d) and step_trigger(%d)\n",
			properties->step_counter, properties->direction_trigger, properties->step_trigger);
	}
}

static void move(ulam_properties *properties)
{
	switch (properties->direction)
	{
		case UP:
			properties->ver_index--;
			break;
		case LEFT:
			properties->hor_index--;
			break;
		case DOWN:
			properties->ver_index++;
			break;
		case RIGHT:
			properties->hor_index++;
			break;
		default:
			printf("Error advancing positions. DIRECTION: %hhd", properties->direction);
			exit(-1);
	}
}

static void print_properties(const ulam_properties properties)
{
	printf("[PROPERTIES]\n");
	printf("\tIteration %d\n", properties.iteration);
	printf("\tX index: %d\n", properties.hor_index);
	printf("\tY index: %d\n", properties.ver_index);
	printf("\tStep: %d\n", properties.current_step);
	printf("\tSteps taken this lap: %d\n", properties.step_counter);
	printf("\tDirection trigger: %d\n", properties.direction_trigger);
	printf("\tStep trigger: %d\n", properties.step_trigger);
	printf("\tDirection: %hhd\n", properties.direction);
}