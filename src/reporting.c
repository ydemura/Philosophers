/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reporting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:08:30 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/14 17:14:39 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reporting.h"
#include "time.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

int	time_to_stop(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(data->mtx->death);
	if (data->first_dead_john > 0)
		res = 1;
	pthread_mutex_unlock(data->mtx->death);
	return (res);
}

int	adjusted_usleep(long int sleep_time, t_data *data)
{
	long int	ms_sleep;
	long int	start;
	long int	counter;

	counter = 0;
	ms_sleep = (long int) sleep_time;
	start = get_start_time();
	if (start == ERR)
		return (ERR);
	while (counter < ms_sleep)
	{
		if (time_to_stop(data) == 1)
			return (DEAD);
		if (usleep(1000) == -1)
			return (ERR);
		counter = timestamp(start);
		if (counter == ERR)
			return (ERR);
	}
	return (0);
}

int	print_philo_state(int jonh_n, const char *doing, t_data *data)
{
	long int	time;
	int			res;

	pthread_mutex_lock(data->mtx->print);
	res = time_to_stop(data);
	time = timestamp(data->start_time);
	if (res == 1 && data->first_dead_john != jonh_n)
	{
		pthread_mutex_unlock(data->mtx->print);
		return (1);
	}
	printf("%li %i %s\n", time, jonh_n, doing);
	pthread_mutex_unlock(data->mtx->print);
	return (0);
}

int	check_on_john(t_data *data, pthread_mutex_t *death, t_philo *john)
{
	long int	current_time;
	int			j_status;

	j_status = ALIVE;
	pthread_mutex_lock(death);
	current_time = timestamp(data->start_time);
	if (john->jstatus == DEAD)
		j_status = DEAD;
	else if (current_time - john->last_meal >= data->inp->die_time)
	{
		john->jstatus = DEAD;
		if (data->first_dead_john == -1)
			data->first_dead_john = john->number;
		j_status = DEAD;
	}
	else if (john->meal_number == data->inp->meal_number)
	{
		john->jstatus = FED;
		j_status = FED;
	}
	pthread_mutex_unlock(death);
	return (j_status);
}
