/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_box_data.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:14:56 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/14 12:31:15 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCH_BOX_DATA_H
# define LAUNCH_BOX_DATA_H

# include "read_input.h"
# include "utils.h"
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/types.h>

typedef enum e_fork
{
	FREE = 0,
	TAKEN = 1
}	t_fork;

typedef enum e_jstatus
{
	ALIVE = 1,
	DEAD = -2,
	FED = -3
}		t_jstatus;

typedef struct s_mutexes
{
	pthread_mutex_t	*print;
	pthread_mutex_t	*f_mutex;
	pthread_mutex_t	*death;
}				t_mutexes;

typedef struct s_data
{
	t_input		*inp;
	t_mutexes	*mtx;
	int			first_dead_john;
	int			eaten_enough;
	long int	start_time;
	int			*forks;
}				t_data;

typedef struct s_philo
{
	t_data		*data;
	int			number;
	long int	last_meal;
	int			meal_number;
	t_err		err;
	t_jstatus	jstatus;
}				t_philo;

t_philo	*initiate_philo_data(t_input *inp);

#endif /* launch_box_data_h */
