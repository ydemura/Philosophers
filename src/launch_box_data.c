/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_box_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:08:13 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/14 17:12:06 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launch_box_data.h"
#include "time.h"
#include <stdlib.h>
#include <stdio.h>

int	*init_arr_int(int number)
{
	int	*arr;
	int	i;

	i = 0;
	arr = malloc(sizeof(int) * number);
	if (arr == NULL)
		return (NULL);
	while (i < number)
	{
		arr[i] = FREE;
		i++;
	}
	return (arr);
}

t_mutexes	*initiate_all_mutexes(void)
{
	t_mutexes	*mtx;

	mtx = malloc(sizeof(t_mutexes) * 1);
	if (mtx == NULL)
		return (NULL);
	mtx->print = malloc(sizeof(pthread_mutex_t));
	if (mtx->print == NULL || pthread_mutex_init(mtx->print, NULL) != 0)
		return (NULL);
	mtx->death = malloc(sizeof(pthread_mutex_t));
	if (mtx->death == NULL || pthread_mutex_init(mtx->death, NULL) != 0)
		return (NULL);
	mtx->f_mutex = malloc(sizeof(pthread_mutex_t));
	if (mtx->f_mutex == NULL || pthread_mutex_init(mtx->f_mutex, NULL) != 0)
		return (NULL);
	return (mtx);
}

t_philo	one_philo(int i, t_data *data)
{
	t_philo	philo;

	philo.data = data;
	philo.number = i + 1;
	philo.err = OK;
	philo.jstatus = ALIVE;
	philo.last_meal = 0;
	philo.meal_number = 0;
	return (philo);
}

t_data	*one_data(t_input *inp)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->inp = inp;
	if (inp->meal_number < 0)
		data->eaten_enough = -1;
	else
		data->eaten_enough = 0;
	data->first_dead_john = -1;
	data->start_time = 0;
	data->mtx = initiate_all_mutexes();
	if (data->mtx == NULL)
		return (NULL);
	data->forks = init_arr_int(inp->num_philos);
	return (data);
}

t_philo	*initiate_philo_data(t_input *inp)
{
	t_data	*data;
	t_philo	*johns;
	int		i;

	i = 0;
	johns = malloc(sizeof(t_philo) * inp->num_philos);
	if (johns == NULL)
		return (NULL);
	data = one_data(inp);
	if (data == NULL)
		return (NULL);
	while (i < inp->num_philos)
	{
		johns[i] = one_philo(i, data);
		if (johns[i].err == ERR)
			return (NULL);
		i++;
	}
	return (johns);
}
