/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weave_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:08:46 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/14 17:22:33 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "weave_threads.h"
#include "time.h"
#include "activity.h"
#include "reporting.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int	free_all_mutexes(t_mutexes *mtx)
{
	if (pthread_mutex_destroy(mtx->f_mutex) != 0)
		return (ERR);
	if (pthread_mutex_destroy(mtx->print) != 0)
		return (ERR);
	if (pthread_mutex_destroy(mtx->death) != 0)
		return (ERR);
	free(mtx->death);
	free(mtx->print);
	free(mtx->f_mutex);
	free(mtx);
	return (0);
}

int	free_structs(int err, t_data *data, t_philo *johns, pthread_t	*threads)
{
	if (err == ERR)
	{
		if (free_all_mutexes(data->mtx) == ERR)
			return (ERR);
	}
	free(data->forks);
	free(data);
	free(johns);
	free(threads);
	if (err == ERR)
		return (ERR);
	return (OK);
}

int	check_jonhs_constantly(int meals, t_data *data, t_philo *philo,
	pthread_mutex_t *death)
{
	int	i;
	int	j_status;
	int	enough_meals;

	i = 0;
	enough_meals = 0;
	while (1)
	{
		if (i == data->inp->num_philos)
			i = 0;
		j_status = check_on_john(data, death, &philo[i]);
		if (j_status == DEAD)
			return (philo[i].number);
		else if (meals >= 0 && j_status == FED)
		{
			enough_meals++;
			data->eaten_enough++;
		}
		if (meals >= 0 && enough_meals == meals)
			return (enough_meals);
		adjusted_usleep(1000, data);
		i++;
	}
	return (0);
}

int	tread_control(int n, int meals, pthread_t *threads, t_philo *philo)
{
	int				i;
	pthread_mutex_t	*death;

	i = 0;
	death = philo[0].data->mtx->death;
	check_jonhs_constantly(meals, philo[0].data, philo, death);
	while (i < n)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (free_structs(ERR, philo[0].data, philo, threads));
		i++;
	}
	return (0);
}

int	weave_threads(t_input *inp)
{
	pthread_t	*threads;
	t_philo		*philo;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * inp->num_philos);
	if (threads == NULL)
		return (ERR);
	philo = initiate_philo_data(inp);
	if (philo == 0)
		return (free_structs(ERR, philo[0].data, philo, threads));
	philo[0].data->start_time = get_start_time();
	while (i < inp->num_philos)
	{
		if (pthread_create(&threads[i], NULL, johns_actions_per_thread,
				(void *)&philo[i]) != 0)
		{
			return (free_structs(ERR, philo[0].data, philo, threads));
		}
		i++;
	}
	tread_control(inp->num_philos, inp->meal_number, threads, philo);
	if (free_all_mutexes(philo[0].data->mtx) == ERR)
		return (free_structs(ERR, philo[0].data, philo, threads));
	return (free_structs(OK, philo[0].data, philo, threads));
}
