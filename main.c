#include "ulam_spiral.c"

int main(int argc, const char *argv[])
{
	int length;
	fprintf(stderr, "Enter grid's length: ");
	scanf("%d", &length);

	ulam_spiral spiral = calculate_ulam_spiral(length);
	print_ulam_spiral(spiral);

	return 0;
}
