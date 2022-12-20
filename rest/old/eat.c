//
//  eat.c
//  philo_codam
//
//  Created by Yuliia Demura on 2/14/22.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#include "eat.h"
#include "time.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>



int	is_john_dead(t_philo *john, t_data *data)
{
	long int time_passed_from_start;
	long int from_start_time;

	time_passed_from_start = timestamp_in_ms(data);
	from_start_time = data->start_time + time_passed_from_start;

	if (john->time_eaten == 0 && from_start_time < data->inp.time_to_die) ///can do time to die - time to eat, not sure if prediction is nessesary as he is alive still
	{
		john->jstatus = ALIVE;
		return (0);
	}
	if (time_passed_from_start - john->last_meal < data->inp.time_to_die)
	{
		john->jstatus = ALIVE;
		return (0);
	}
	john->jstatus = DEAD;
	return (200);
}

int	new_eat_per_thread(t_philo *john, t_data *data, int index) ///	do I need index int in john struct or it will be better separate completely?
{
	int r_fork;
	int l_fork;
	pthread_mutex_t *r_fork_mutex;
	pthread_mutex_t *l_fork_mutex;

	r_fork = data->forks[index];
	r_fork_mutex = &data->mutex[index];
	if (index == 0)
	{
		l_fork = data->forks[data->inp.number_of_philosophers - 1];
		l_fork_mutex = &data->mutex[data->inp.number_of_philosophers - 1];
	}
	else
	{
		l_fork = data->forks[index - 1];
		l_fork_mutex = &data->mutex[index - 1];
	}
	while (john->jstatus == ALIVE && john->number_of_forks_hold < 2)
	{
		if (is_john_dead(john, data) == 200)
		{
			printf("john died hungry");
			return (DEAD); //DEAD
		}
		pthread_mutex_lock(r_fork_mutex);
		if (r_fork == FREE)
		{
			john->number_of_forks_hold++;
			r_fork = TAKEN_RIGHT;
		}
		pthread_mutex_lock(l_fork_mutex);
		if (l_fork == FREE)
		{
			john->number_of_forks_hold++;
			l_fork = TAKEN_LEFT;
		}
		if (john->number_of_forks_hold == 2 && is_john_dead(john, data) == 0)
		{
			adjusted_usleep(data->inp.time_to_eat);
			r_fork = FREE;
			l_fork = FREE;
			pthread_mutex_unlock(r_fork_mutex);
			pthread_mutex_unlock(l_fork_mutex);
			john->time_eaten++;
			john->last_meal = timestamp_in_ms(data);
			if (is_john_dead(john, data) == 0)
			{
				data->timestamp = timestamp_in_ms(data);
				printf("john number %i survived at %li\n", index + 1, data->timestamp);
				break ;
			}

		}

	}
	john->number_of_forks_hold = 0;
	return (john->jstatus);
}







// prev old lol


//void	eat(t_data *data) OLD
//{
//	int left_fork_index;
//	int right_fork_index;
//
//	left_fork_index = data->index;
//	if (data->index == 1) ///	first john can take 1__fork and number_of_philo__fork (last)
//		right_fork_index = data->inp.number_of_philosophers;
//	else
//		right_fork_index = data->index - 1;
//
//	while (data->johns[data->index].number_of_forks_hold < 2 || data->johns[data->index].jstatus == ALIVE) //&& or ||
//	{
//		if (data->johns[data->index].last_meal + data->johns[data->index].current_time > data->inp.time_to_die)
//		{
//			data->johns[data->index].jstatus = DEAD;
//			return ;
//			//need to stop waiting and return DEAD
//		}
//		if (data->johns[left_fork_index].fork_left == FREE)
//		{
//			//grab it with mutex
//			data->johns[left_fork_index].fork_left = TAKEN;
//		}
//		else
//		{
//			//wait for it?
//		}
//		if (data->johns[right_fork_index].fork_right == FREE)
//		{
//			//grab it with mutex
//			data->johns[right_fork_index].fork_right = TAKEN;
//		}
//		else
//		{
//			//wait for it?
//		}
//	}
//	//EAT time for eating
//	//DROP:
//	//free mutex left fork
//	//free mutex right fork
//	data->johns[left_fork_index].fork_left = FREE;
//	data->johns[right_fork_index].fork_right = FREE;
//}
