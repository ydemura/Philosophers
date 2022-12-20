//
//  input_in_structs.h
//  new_philo
//
//  Created by Julia Demura on 14/10/2022.
//

#ifndef input_in_structs_h
#define input_in_structs_h

typedef struct s_input
{
	int	num_philos;
	long int	die_time;
	long int	eat_time;
	long int	sleep_time;
	int	number_of_times_each_philosopher_must_eat;
}	t_input;

int	read_input(int argc, const char **argv, t_input *inp);

#endif /* input_in_structs_h */
