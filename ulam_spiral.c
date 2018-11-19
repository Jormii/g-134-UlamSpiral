#include "ulam_spiral.h"

char is_prime(int number) {
	if (number == 2 || number == 3)
	{
		return PRIME;
	}

	if (number == 1 || !(number & 1) || (number % 3) == 0)
	{
		return NOT_PRIME;
	}

	int i = 5;

	while ((i * i) <= number) 
	{
		if ((number % i) == 0 || (number % (i + 2) == 0))
		{
			return NOT_PRIME;
		}

		i += 6;
	}
	return PRIME;
}

ulam_spiral calculate_ulam_spiral(int length) {
	int size = length * length;
	ulam_spiral spiral;
    spiral.length = (unsigned int)length;
    spiral.grid = (char*)calloc(sizeof(char), size);

	if ((length % 2) == 0)
	{
		printf("ERROR (code: %u): Length argument must be an odd number\n", error_even);
		spiral.return_value = error_even;
		return spiral;
	}
	else if (length <= 0)
	{
		printf("ERROR (code: %u): Length must be positive\n", error_negative);
		spiral.return_value = error_negative;
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
    properties.direction = down;

	while (properties.iteration < size)
	{
		#ifdef DEBUG
		print_properties(properties);
		#endif

		// Paint respective cell
		int number = properties.iteration + 1;
		char number_is_prime = is_prime(number);

		int grid_pos = properties.hor_index + properties.ver_index * length;
		spiral.grid[grid_pos] = number_is_prime;

		#ifdef DEBUG
		printf("%d at position (%d, %d) is prime: %hhd\n", number, properties.hor_index, properties.ver_index, number_is_prime);
		#endif

		// Change direction
		change_direction(&properties);

		// Move
		move(&properties);
		
		// Update
		#ifdef DEBUG
		printf("Iteration and step counter increase\n");
		#endif
		properties.iteration++;
		properties.step_counter++;
		#ifdef DEBUG
		printf("\n");
		#endif
	}
	spiral.return_value = no_error;
    return spiral;
}

void print_ulam_spiral(const ulam_spiral spiral) {
	if (spiral.return_value != no_error)
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
			char print_char = (spiral.grid[grid_pos] == PRIME) ? prime_char : not_prime_char;
			if (column == _1_pos && row == _1_pos)
			{
				print_char = _1_char;
			}
			printf("%c", print_char);
		}
		printf("\n");
	}
}

static void change_direction(ulam_properties *properties) {
	#ifdef DEBUG
	printf("Current direction: %hhd\n", properties->direction);
	#endif
	if (properties->step_counter == properties->direction_trigger)
	{
		properties->direction = (properties->direction + 1) % n_directions;
		#ifdef DEBUG
		printf("Direction trigger. Changing direction. New direction: %hhd\n", properties->direction);
		#endif
	}
	if (properties->step_counter == properties->step_trigger)
	{
		properties->direction = (properties->direction + 1) % n_directions;
		properties->current_step++;
		properties->step_counter = 0;
		properties->direction_trigger = properties->current_step;
		properties->step_trigger = 2 * properties->current_step;
		#ifdef DEBUG
		printf("Step trigger. Changing direction. New direction: %hhd\n", properties->direction);
		printf("Reseting step counter (%d), direction trigger (%d) and step_trigger(%d)\n",
			properties->step_counter, properties->direction_trigger, properties->step_trigger);
		#endif
	}
}

static void move(ulam_properties *properties) {
	switch (properties->direction)
	{
		case up:
			properties->ver_index--;
			break;
		case left:
			properties->hor_index--;
			break;
		case down:
			properties->ver_index++;
			break;
		case right:
			properties->hor_index++;
			break;
		default:
			printf("Error advancing positions. DIRECTION: %hhd", properties->direction);
			exit(-1);
	}
	#ifdef DEBUG
	printf("Next position: (%d, %d)\n", properties->hor_index, properties->ver_index);
	#endif
}

static void print_properties(const ulam_properties properties) {
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
