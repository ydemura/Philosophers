//
//  utilities.c
//  new_philo
//
//  Created by Julia Demura on 14/10/2022.
//

#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int	error_message(t_err err, char *message)
{
	if (err == ERR)
		printf("Error: %s", message);
	return (ERR);
}

int	ft_atoi(const char	*str)
{
	int	i;
	int	n;
	int	res;

	i = 0;
	while (str[i] == 32 || (str[i] >= 8 && str[i] <= 14))
		i++;
	n = 1;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (2147483648 / 10) && n == -1)
			return (0);
		if (res > (2147483647 / 10))
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * n);
}

//gettimeofaday, real time in ms for further referenses
long int	get_start_time(void)
{
	struct timeval	tm;
	long int		start_time;

	if (gettimeofday(&tm, NULL) != 0)
		return (ERR);
	start_time = (tm.tv_sec * 1000000) + (tm.tv_usec);
	return (start_time);
}

//how many microseconds passed from start time, comparing start time
//to current (gettimeofday)
long int	timestamp(long int start_time)
{
	long int	time_now;

	time_now = get_start_time();
	return (time_now - start_time);
}

