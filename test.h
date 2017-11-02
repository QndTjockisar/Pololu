#include <stdint.h>
#include <stdio.h>

#define CYCLE 360

enum direction {
	E=0,
	N=90,
	W=180,
	S=270
};

struct coord {
	unsigned int x;
	unsigned int y;
	enum direction d;
};

#define NUM_EP 13
#define W_EDGE_X 0
#define E_EDGE_X 4
#define N_EDGE_Y 3
#define S_EDGE_Y 0
const struct coord eps[] = {
	{0, 0, S},
	{1, 0, S},
	{2, 0, S},
	{3, 0, S},
	{4, 0, S},
	{4, 1, E},
	{4, 2, E},
	{4, 3, N},
	{3, 3, N},
	{2, 3, N},
	{1, 3, N},
	{0, 3, N},
	{0, 2, W},
	{0, 1, W}
};

const struct coord start_pos = {0, 0, S};

int reach_point(const struct coord const * curr,
		const struct coord const * dest);

void turn_degree(unsigned int degree);
void turn_direction(struct coord* curr_p,const enum direction to);

unsigned int read_code();

int set_direction(struct coord* curr_p, struct coord const * dest_p);

void follow_line(unsigned int crosses);
