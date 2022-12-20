/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:08:05 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/14 17:16:05 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "activity.h"
#include "time.h"
#include "weave_threads.h"
#include "reporting.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void	actions_set(t_philo *john, t_data *data, t_actions action)
{
	check_on_john(data, data->mtx->death, john);
	if (time_to_stop(data) > 0)
		return ;
	if (action == EATING)
	{
		print_philo_state(john->number, "is eating", data);
		john->last_meal = timestamp(data->start_time);
		john->meal_number++;
		adjusted_usleep(data->inp->eat_time, data);
	}
	if (action == SLEEPING)
	{
		print_philo_state(john->number, "is sleeping", data);
		adjusted_usleep(data->inp->sleep_time, data);
		print_philo_state(john->number, "is thinking", data);
	}
}

int	take_neibors_fork(int john_number, int num_philos)
{
	int	neibors_fork;
	int	john_i;

	john_i = john_number - 1;
	neibors_fork = -1;
	if (john_i == 0)
		neibors_fork = num_philos - 1;
	if (num_philos % 2 == 0 && john_number == num_philos)
		neibors_fork = john_i - 1;
	else
	{
		if (john_number % 2 == 0)
			neibors_fork = john_i - 1;
		else
			neibors_fork = john_i + 1;
	}
	return (neibors_fork);
}

int	is_instruction_can_eat(int own_f, int other_f, t_philo *john, t_data *data)
{
	int	instruction;

	instruction = WAIT;
	while (instruction == WAIT)
	{
		pthread_mutex_lock(data->mtx->f_mutex);
		if (john->last_meal == 0 || (john->last_meal + data->inp->die_time)
			< (timestamp(data->start_time) + 10))
		{
			if (data->forks[own_f] == FREE && data->forks[other_f] == FREE)
			{
				instruction = CAN_EAT;
				data->forks[own_f] = TAKEN;
				data->forks[other_f] = TAKEN;
			}
		}
		pthread_mutex_unlock(data->mtx->f_mutex);
		if (instruction == WAIT)
			usleep(1000);
	}
	return (CAN_EAT);
}

void	taking_a_fork_eating(t_philo *john, t_data *data)
{
	int	own_f;
	int	other_f;

	own_f = john->number - 1;
	other_f = take_neibors_fork(john->number, data->inp->num_philos);
	if (time_to_stop(data) > 0)
		return ;
	is_instruction_can_eat(own_f, other_f, john, data);
	print_philo_state(john->number, "has taken a fork", data);
	print_philo_state(john->number, "has taken a fork", data);
	actions_set(john, data, EATING);
	pthread_mutex_lock(data->mtx->f_mutex);
	data->forks[own_f] = FREE;
	data->forks[other_f] = FREE;
	pthread_mutex_unlock(data->mtx->f_mutex);
}

void	*johns_actions_per_thread(void *one_boxed_john_number_i)
{
	t_data	*data;
	t_philo	*john;

	john = (t_philo *)one_boxed_john_number_i;
	data = john->data;
	if (john->number % 2 == 0 && john->number != 1)
		usleep(1000);
	while (john->jstatus == ALIVE && time_to_stop(data) == 0)
	{
		taking_a_fork_eating(john, data);
		if (john->meal_number == data->inp->meal_number)
			break ;
		actions_set(john, data, SLEEPING);
		check_on_john(data, data->mtx->death, john);
		if (john->jstatus == DEAD)
		{
			print_philo_state(john->number, "died", data);
			break ;
		}
		if (john->jstatus == FED)
			break ;
	}
	return (0);
}
