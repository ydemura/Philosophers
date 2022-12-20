//
//  loop_thread.h
//  new_philo
//
//  Created by Julia Demura on 14/10/2022.
//

#ifndef loop_thread_h
#define loop_thread_h

#include "form_philo_data.h"

int	philo_activity(int i, t_shared_data *data);
int	dead_check_all_philos(int i, t_protected *protected, pthread_mutex_t *check);

#endif /* loop_thread_h */
