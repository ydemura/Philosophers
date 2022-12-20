//
//  input_in_structs.c
//  new_philo
//
//  Created by Julia Demura on 14/10/2022.
//

#include "input_in_structs.h"
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int	check_integer(int n)
{
	if (n < 0 || n > 2147483647)
		return (1);
	return (0);
}

int	check_int_put_into_struct(const char *src, int *dst)
{
	int	n;

	if (src == NULL || src[0] == '\0')
		return (ERR);
	if (src[0] == '0' && src[1] != '\0')
		return (ERR);
	n = 0;
	n = ft_atoi(src);
	if (check_integer(n) == 0)
		*dst = n;
	else
		return (ERR);
	return (0);
}

int	collect_philo_input(const char **argv, t_input *inp)
{
	int value;
	if (check_int_put_into_struct(argv[1], &inp->num_philos) == ERR)
		return (ERR);
	if (check_int_put_into_struct(argv[2], &value) == ERR)
		return (ERR);
	inp->die_time = ((long int)value) * 1000;
	if (check_int_put_into_struct(argv[3], &value) == ERR)
		return (ERR);
	inp->eat_time = ((long int)value) * 1000;
	if (check_int_put_into_struct(argv[4], &value) == ERR)
		return (ERR);
	inp->sleep_time = ((long int)value) * 1000;
	return (0);
}

int	read_input(int argc, const char **argv, t_input *inp)
{
	if (argc < 5 || argc > 6)
		return (ERR);
	if (collect_philo_input(argv, inp) == ERR)
		return (ERR);
	if (argc == 6)
	{
		if (check_int_put_into_struct(argv[5],
				&inp->number_of_times_each_philosopher_must_eat) == ERR)
			return (ERR);
	}
	else
		inp->number_of_times_each_philosopher_must_eat = -1;
	return (0);
}
