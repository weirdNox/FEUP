#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#include "timer_tools.h"
#include "udp_remote.h"
#include "s_a_hacks.h"

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <conio.h>



////////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
  void GOTOXY(int XPos, int YPos) { COORD Coord; Coord.X = XPos; Coord.Y = YPos; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord); }
  #define CLEAR() system("cls")
#else
  #define CLEAR() printf("\033[H\033[J")
  #define GOTOXY(x,y) printf("\033[%d;%dH", (x), (y))
#endif


////////////////////////////////////////////////////////////////////////////////


#define ESQUERDA out.b0
#define BOMBA_V5 out.b1
#define MOTOR_PA out.b2
#define V1       out.b3
#define V2       out.b4
#define V3       out.b5
#define V4       out.b6
#define V7       out.b7

#define M_MAX    in.b0
#define M_MIN    in.b1
#define PRATO1   in.b2
#define PRATO2   in.b3
#define PARAGEM  in.b4
#define CICLO    in.b5


ms_timer timer1;  // Declare a timer (miliseconds)

int main()
{
    initialize_all();
   	start_timer(&timer1, 5000);  // initialize timer for first time (miliseconds)

	while (1)              // infinite control cycle
	{
		read_all_inputs(); // global variables "in.b0" up to "in.b7" are updated from <<buttons>>


        //Examples:
        //out.b7 = in.b7;
		//out.b3 = 1 - out.b3;
		// if (in.b0) {printf(".");}    // if button 1, then print
		// out.b1=(cur_time & 1);       // make led blick 1/10 sencod on, equal time off
		//                              // cur_time in tenths of sec, uses timer0
		//if (in.b2) out.b2=1-out.b2;  // if button2, then toggle out.b2

		V7 = (cur_time & 0x02) ? 1 : 0 ;
		V4 = (cur_time & 0x04) ? 1 : 0 ;
		V3 = (cur_time & 0x08) ? 1 : 0 ;
		V2 = (cur_time & 0x10) ? 1 : 0 ;
		V1 = (cur_time & 0x20) ? 1 : 0 ;

		//Timer Examples:
		//if (get_timer(&timer1)) {       // If timer expired
      	//    start_timer(&timer1, 1000); // Re-Start it
      	//    out.b7=1-out.b7;            // and toggle out.b7
        //}

		if (get_timer(&timer1)) {       // If timer expired
      	    start_timer(&timer1, 1000); // Re-Start it
      	    ESQUERDA=1-ESQUERDA;        // and toggle out.b2
        }

    	//CLEAR();

        GOTOXY(1,1);
        printf("%09.1f",cur_time/10.0);

		GOTOXY(1,3);
		printf("Entradas: M_MAX=%01d, M_MIN=%01d, PRATO1=%01d, PRATO2=%01d, PARAG=%01d, CICLO=%01d\n\r",
    		              M_MAX,      M_MIN  ,    PRATO1 ,     PRATO2,      PARAGEM, CICLO);

		GOTOXY(1,5);
		printf("Saidas: ESQ=%01d B_V5=%01d MOT_PA=%01d V1=%01d V2=%01d V3=%01d V4=%01d V7=%01d\n\r",
    		            ESQUERDA, BOMBA_V5, MOTOR_PA, V1, V2, V3, V4, V7);


		//////////////////// *** Escrever Código AQUI ***


		fflush(stdout);

		write_all_outputs(); // write global variables "out.b0" up to "out.b7" the <<leds>>

		if (kbhit()) {
			if (getch()==27) break;
		}
	}

	printf("\n\r\n\r      Acabei ;) \n\r\n\r");
    fflush(stdout);

	return 0;
}
