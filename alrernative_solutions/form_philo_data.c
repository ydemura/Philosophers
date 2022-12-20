//
//  form_philo_data.c
//  new_philo
//
//  Created by Julia Demura on 14/10/2022.
//

#include "form_philo_data.h"
#include "utilities.h"
#include <stdlib.h>

int	init_mutexes(t_shared_data *data)
{
	data->print = malloc(sizeof(pthread_mutex_t));
	if (data->print == NULL || pthread_mutex_init(data->print, NULL) != 0)
		return (ERR);
	data->check = malloc(sizeof(pthread_mutex_t));
	if (data->check == NULL || pthread_mutex_init(data->check, NULL) != 0)
		return (ERR);
	return (0);
}

int	*init_arr_int(int number, int if_philo)
{
	int *arr;
	int	i;

	i = 0;
	if (if_philo == -1)
		arr = malloc(sizeof(long int) * number);
	else
		arr = malloc(sizeof(int) * number);
	if (arr == NULL)
		return (NULL);
	while (i < number)
	{
		if (if_philo == 1)
			arr[i] = ALIVE;
		else if (if_philo == -1)
			arr[i] = 0;
		else
			arr[i] = FREE;
		i++;
	}
	return (arr);
}

t_protected *init_protected_part(int number)
{
	t_protected *protctd;
	
	protctd = malloc(sizeof(t_protected));
	if (protctd == NULL)
		return (NULL);
	protctd->dead_philo = -1;
	protctd->arr_forks = init_arr_int(number, 0);
	if (protctd->arr_forks == NULL)
		return (NULL);
	protctd->arr_philo_states = init_arr_int(number, 1);
	if (protctd->arr_philo_states == NULL)
		return (NULL);
	protctd->last_meal_arr = (long int *)init_arr_int(number, -1);
	return (protctd);
}

t_shared_data *form_data(t_input *inp)
{
	t_shared_data *data;

	data = malloc(sizeof(t_shared_data));
	if (data == NULL)
		return (NULL);
	if (init_mutexes(data) == ERR)
		return (NULL);
	data->inp = inp;
	data->protectd = init_protected_part(inp->num_philos);
	if (data->protectd == NULL)
		return (NULL);
	data->start_time = get_start_time();
	return (data);
}
