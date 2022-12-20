//
//  loop_thread.c
//  new_philo
//
//  Created by Julia Demura on 14/10/2022.
//

#include "loop_thread.h"
#include "utilities.h"
#include <unistd.h>
#include <stdio.h>

int	dead_check_all_philos(int i, t_protected *protected, pthread_mutex_t *check)
{
	int status;
	pthread_mutex_lock(check);
	if (protected->dead_philo >= 0)
		status = DEAD;
	else
		status = ALIVE;
	pthread_mutex_unlock(check);
	return status;
}

int	unlocked_hunger_check_i_philo(int i, t_shared_data * data, long int time)
{
	int dead_philo;
	long int did_not_eat_for;
	did_not_eat_for = time - data->protectd->last_meal_arr[i];
	if (data->protectd->dead_philo < 0 && did_not_eat_for >= data->inp->die_time)
		data->protectd->dead_philo = i;
	dead_philo = data->protectd->dead_philo;
	return dead_philo;
}


int	hunger_check_i_philo(int i, t_shared_data * data)
{
	int dead_philo;
	pthread_mutex_lock(data->check);
	dead_philo = unlocked_hunger_check_i_philo(i, data, timestamp(data->start_time));
	pthread_mutex_unlock(data->check);
	return dead_philo;
}

int	print_philo_eating_state(int i, t_shared_data *data, long int time)
{
	if (dead_check_all_philos(i, data->protectd, data->check) == DEAD)
	{
		return (DEAD);
	}
	pthread_mutex_lock(data->print);
	printf("%li %i has taken a fork\n", time / 1000, i + 1);
	printf("%li %i has taken a fork\n", time / 1000, i + 1);
	printf("%li %i is eating\n", time / 1000, i + 1);
	pthread_mutex_unlock(data->print);
	return (0);
}


int	print_philo_state_with_time(const char *doing, long int time, int i, t_shared_data *data)
{
	if (dead_check_all_philos(i, data->protectd, data->check) == DEAD)
	{
		return (DEAD);
	}
	pthread_mutex_lock(data->print);
	printf("%li %i %s\n", time / 1000, i + 1, doing);
	pthread_mutex_unlock(data->print);
	return (0);
}

int	print_philo_state(const char *doing, int i, t_shared_data *data)
{
	return print_philo_state_with_time(doing, timestamp(data->start_time), i, data);
}

int	adjusted_usleep_with_start(long int sleep_time, long int start, int i, t_shared_data *data)
{
//	usleep((unsigned int)(sleep_time - timestamp(start)));
//	if (hunger_check_i_philo(i, data) >= 0)
//		return (DEAD);
//	else
//		return (0);
	long int	counter;

	while (1)
	{
		counter = timestamp(start);
		if (counter == ERR)
			return (ERR);
		if (counter >= sleep_time)
			return (0);
		if (hunger_check_i_philo(i, data) >= 0)
			return (DEAD);
		if (usleep(500) == -1)
			return (ERR);
	}
	return (0);
}

int	adjusted_usleep(long int sleep_time, int i, t_shared_data *data)
{
	long int start;
	start = get_start_time();
	if (start == ERR)
		return (ERR);
	return adjusted_usleep_with_start(sleep_time, start, i, data);
}

long int	take_fork_eat(t_shared_data *data, t_protected *protected, int i)
{
	int	own_fork;
	int other_fork;
	long int eating_started_time;
	long int sleeping_started_time;
	int status;

	own_fork = i;
	if (i == data->inp->num_philos - 1)
		other_fork = 0;
	else
		other_fork = i + 1;
	while (1)
	{
		pthread_mutex_lock(data->check);
		eating_started_time = timestamp(data->start_time);
		if (unlocked_hunger_check_i_philo(i, data, eating_started_time) >= 0)
		{
			status = -1;
		}
		else if (protected->arr_forks[own_fork] == FREE
				 && protected->arr_forks[other_fork] == FREE)
		{
			protected->arr_forks[own_fork] = TAKEN;
			protected->arr_forks[other_fork] = TAKEN;
			protected->last_meal_arr[i] = eating_started_time;
			status = 1;
		}
		else
		{
			status = 0;
		}
		pthread_mutex_unlock(data->check);
		if (status == -1)
			// someone is dead
			return -1;
		else if (status == 1)
			// took forks
			break;
		else
			// continue asking for forks
			usleep(500);
	}
	print_philo_eating_state(i, data, eating_started_time);
	
	if (adjusted_usleep_with_start(data->inp->eat_time, eating_started_time + data->start_time, i, data) == DEAD)
		return (-1);
	sleeping_started_time = timestamp(data->start_time);
	pthread_mutex_lock(data->check);
	protected->arr_forks[own_fork] = FREE;
	protected->arr_forks[other_fork] = FREE;
	pthread_mutex_unlock(data->check);
	print_philo_state_with_time("is sleeping", sleeping_started_time, i, data);
	return (data->start_time + sleeping_started_time);
}

int	last_words_of_first_dead(int i, t_shared_data *data)
{
	long int	time;
	int dead_philo;
	
	dead_philo = hunger_check_i_philo(i, data);

	if (dead_philo == i)
	{
		pthread_mutex_lock(data->print);
		time = timestamp(data->start_time);
		printf("%li %i died\n", time / 1000, i + 1);
		pthread_mutex_unlock(data->print);
	}
	return (DEAD);
}

int	philo_activity(int i, t_shared_data *data)
{
	long int sleeping_started_time;
	if (i % 2 == 0)
		adjusted_usleep(data->inp->eat_time / 2, i, data);
	while (1)
	{
		sleeping_started_time = take_fork_eat(data, data->protectd, i);
		if (sleeping_started_time < 0)
			return (last_words_of_first_dead(i, data));
		if (adjusted_usleep_with_start(data->inp->sleep_time, sleeping_started_time, i, data) == DEAD)
			return (last_words_of_first_dead(i, data));
		print_philo_state("is thinking", i, data);
	}
	return (0);
}
