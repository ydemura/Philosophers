//
//  main.c
//  new_philo
//
//  Created by Julia Demura on 14/10/2022.
//

#include <stdio.h>
#include "input_in_structs.h"
#include "utilities.h"
#include "main_thread.h"

int main(int argc, const char * argv[])
{
	t_input	inp;

	if (read_input(argc, argv, &inp) == ERR)
		return (error_message(ERR, "input"));
	launch_threads(&inp);
	return (0);
}
