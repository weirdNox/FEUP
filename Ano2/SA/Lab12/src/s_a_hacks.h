#ifndef S_A_HACKS_H_
#define S_A_HACKS_H_


////////////////////////////////////////////////////////////////////////////////

// Declarar Globais timer0 e cur_time
extern ms_timer timer0;
extern unsigned long cur_time;


////////////////////////////////////////////////////////////////////////////////


void initialize_all(void)
{
    start_timer(&timer0, 100);   // Arrancar o timer com um tempo de 100 milisegundos
    
//	UDP_verbose = 1;
    UDP_remote_init();
}



void read_all_inputs()
{
	UDP_remote_read_timeout(1000); // timeout in us
	
    if (get_timer(&timer0)) {       // Se o timer já expirou
      	start_timer(&timer0, 100);  // Então rearma-o
      	cur_time++;                 // incrementa tempo global
    }

}

void write_all_outputs(void)
{
    fflush(stdout);	    
	UDP_remote_write();
    Sleep(1);  // miliseconds
}

#endif /* S_A_HACKS_H_ */
