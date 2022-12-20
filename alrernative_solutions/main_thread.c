//
//  main_thread.c
//  new_philo
//
//  Created by Julia Demura on 14/10/2022.
//

#include "main_thread.h"
#include "form_philo_data.h"
#include "utilities.h"
#include "loop_thread.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void	*thread(void	*arg_void)
{
	t_shared_data *data;
	int i;

	i = ((t_jdata *)arg_void)->i;
	data = ((t_jdata *)arg_void)->data;
	free(arg_void);
	philo_activity(i, data);
	return (0);
}

int	tread_finishing(pthread_t *threads, t_shared_data *data)
{
	int i;

	i = 0;
	
	while (i < data->inp->num_philos)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (ERR);
		i++;
	}
	
	return 0;
}

int	tread_moniroting(t_shared_data *data)
{
	int i;

	i = 0;
	while (1)
	{
		if (i == data->inp->num_philos - 1)
			i = 0;
		if (dead_check_all_philos(i, data->protectd, data->check) == DEAD)
		{
			return (i);
		}
		usleep(1000);
	}
	return 0;
}

int	launch_threads(t_input *inp)
{
	t_shared_data *data;
	t_jdata *arg;
	pthread_t *threads;
	int i;

	i = 0;
	data = form_data(inp);
	if (data == NULL)
		return ERR;
	threads = malloc(sizeof(pthread_t) * inp->num_philos);
	if (threads == NULL)
		return ERR;
	while (i < inp->num_philos)
	{
		arg = malloc(sizeof(t_jdata));
		if (arg == NULL)
			return ERR;
		arg->data = data;
		arg->i = i;
		if (pthread_create(&threads[i], NULL, thread, (void *)arg) != 0)
			return ERR;
		i++;
	}
	tread_moniroting(data);
	tread_finishing(threads, data);
	return 0;
}
