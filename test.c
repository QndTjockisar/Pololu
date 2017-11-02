#include <pololu/3pi.h>
#include "test.h"
#include <stdio.h>
#include <avr/pgmspace.h>

void run(){
        struct coord curr_pos;
	struct coord const * next_pos_p;
	unsigned int dest_idx, steps;


	curr_pos.x = start_pos.x;
	curr_pos.y = start_pos.y;
	curr_pos.d = start_pos.d;

	while(!reach_point(&curr_pos, &start_pos)){
		dest_idx = read_code();
		if(dest_idx >= NUM_EP){
			printf("Wrong next pos");
			continue;
		}

		next_pos_p = eps + dest_idx;

		while(!reach_point(&curr_pos, next_pos_p)){
			steps = set_direction(&curr_pos, next_pos_p);
			follow_line(steps);
		}
		turn_direction(&curr_pos, next_pos_p->d);
	}
}

void follow_line(unsigned int crosses){
	/* TODO follow line until n crosess passed */
}

int reach_point(const struct coord const * curr,
		const struct coord const * dest){
	if(curr->x == dest->x && curr->y == dest->y)
		return 1;
	else
		return 0;
}

int set_direction(struct coord* curr_p, struct coord const * dest_p){
	int diff = 0;

	if(curr_p->x == dest_p->x){
		diff = curr_p->y - dest_p->y;
		if(diff > 0){
			turn_direction(curr_p, S);
		} else {
			turn_direction(curr_p, N);
			diff *= -1;
		}
	} else if (curr_p->y == dest_p->y){
		diff = curr_p->x - dest_p->x;
		if(diff > 0){
			turn_direction(curr_p, W);
		} else {
			turn_direction(curr_p, E);
			diff *= -1;
		}
	} else if (W_EDGE_X == dest_p->x){
		diff = curr_p->x - dest_p->x;
		turn_direction(curr_p, W);
	} else if (E_EDGE_X == dest_p->x){
		diff = dest_p->x - curr_p->x;
		turn_direction(curr_p, E);
	} else	if (S_EDGE_Y == dest_p->y){
		diff = curr_p->y - dest_p->y;
		turn_direction(curr_p, S);
	} else if (N_EDGE_Y == dest_p->y){
		diff = dest_p->y - curr_p->y;
		turn_direction(curr_p, N);
	}

	return diff;
}

void turn_degree(unsigned int degree){
	/* TODO fix this */
}

void turn_direction(struct coord* curr_p, const enum direction to){
	unsigned int degree = ((int)to - (int)(curr_p->d) + CYCLE) % CYCLE;
	if(degree > 0)
        	turn_degree(degree);
	curr_p->d = to;
}

unsigned int read_code(){
	/* TODO fix this */
	return 10;
}

int main(){

	unsigned char btn = 0;
        while(1){
	  
		btn = wait_for_button(ANY_BUTTON);
		switch(btn){
		case BUTTON_A:
			run();
			break;
		case BUTTON_B:
			break;
		case BUTTON_C:
			break;
		default:
			break;
		}
	}
}
