//
//  form_philo_data.h
//  new_philo
//
//  Created by Julia Demura on 14/10/2022.
//

#ifndef form_philo_data_h
#define form_philo_data_h

#include "input_in_structs.h"
#include <pthread.h>

typedef enum e_instruction
{
	WAIT = -1,
	CAN_EAT = -2
	
}	t_instruction;

typedef enum e_philo
{
	ALIVE = -3,
	SLEEP = -4,
	EAT = -5,
	DEAD = -6
}	t_philo;

typedef enum e_fork
{
	FREE = 0,
	TAKEN = 1
}	t_fork;

typedef struct s_protected
{
	int dead_philo;
	int *arr_forks;
	int *arr_philo_states;
	long int *last_meal_arr;
} t_protected;

typedef struct s_shared_data
{
	t_input *inp;
	t_protected *protectd;
	long int start_time;
	pthread_mutex_t *print;
	pthread_mutex_t *check;
} t_shared_data;

typedef struct s_jdata
{
	int i;
	t_shared_data *data;
}				t_jdata;

t_shared_data *form_data(t_input *inp);

#endif /* form_philo_data_h */
