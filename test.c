#include <pololu/3pi.h>
#include "test.h"
#include <stdio.h>
#include <avr/pgmspace.h>
// 10 levels of bar graph characters
const char bar_graph_characters[10] = {' ',0,0,1,2,3,3,4,5,255};
const char beep[] PROGMEM = "!c32";
void dosth(){
		int	speed = 30;
        //encoders_get_counts_and_reset_m1();
        //encoders_get_counts_and_reset_m2();
		
		while(speed >= -30){
			set_motors(speed,speed);
			delay_ms(500);
			speed -= 5;
			printf("%d,%d,%d!", speed, encoders_get_counts_m1(), encoders_get_counts_m2());
		}
		set_motors(0, 0);
		printf("Done");
}

void printsensors(unsigned char readMode){
	unsigned int sensors[5];
	read_line_sensors(sensors,readMode);
	for(int i = 0; i < 5; i++){
		print_character(bar_graph_characters[sensors[i]/201]);
	}
}
     
void readcode(unsigned char readMode){
  //	set_motors(25,25);
	//	delay_ms(500);
	
	for(int i = 0; i < 40; i++){
		set_motors(20,20);
		delay_ms(100);
		set_motors(0, 0);
		play_from_program_space(beep);
		clear();
		printsensors(readMode);
		delay_ms(2000);
	}
}

char readvalue(unsigned char readMode){
	char rslt = 0;
	unsigned int sensors[5];
	read_line_sensors(sensors,readMode);
	for(int i = 0; i < 5; i++){
		if (sensors[i] > 1700){
			rslt = rslt | (1 << i);
		}
	}
	return rslt;
}

void count_dots(unsigned char readMode){
	char reading_0 = 0;
	char reading_1 = 0;
	char in_range = 0;
        char value;
	char total = 0;

	set_motors(20, 20);
	clear();
	
	while(!in_range){
		delay_ms(100);
		value = readvalue(readMode);
		if ((value & 14) == 14){
			in_range = 1;
			printf("S");
		}
	}

	while(in_range && total<5){
		delay_ms(100);
		value = readvalue(readMode);
		
		if ((value & 14) == 14){
			if(in_range < 2){
				continue;
			} else {
				break;
			}
		}

		in_range = 2;		
		
		if ((value & 16) == 0){
			if (reading_1){
				reading_1 = 0;
			}
		} else {
			if(!reading_1){
			        reading_1 = 1;
				printf("1");
				total++;
			}
		}
		
		if ((value & 1) == 0){
			if (reading_0){
				reading_0 = 0;
			}
		} else {
			if(!reading_0){
			        reading_0 = 1;
				printf("0");
				total++;
			}
		}
	}

	printf("E");

	set_motors(0,0);
}



int main()
{
	//encoders_init(PD5, PD6, PD3, PB3);
        pololu_3pi_init(2000);
	lcd_init_printf();
	
	printf("%s", "Started.");

	unsigned char btn = 0;
        while(1){
	  
		btn=wait_for_button(ANY_BUTTON);
		switch(btn){
		case BUTTON_A:
			count_dots(IR_EMITTERS_ON);
			break;
		case BUTTON_B:
			readcode(IR_EMITTERS_ON);
			break;
		case BUTTON_C:
			readcode(IR_EMITTERS_OFF);
			break;
		default:
			break;
		}
	}
}
