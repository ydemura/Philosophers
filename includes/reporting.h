/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reporting.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:19:00 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/14 16:07:26 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPORTING_H
# define REPORTING_H

# include <pthread.h>
# include "launch_box_data.h"

int	print_philo_state(int jonh_n, const char *doing,
		t_data *data);
int	error_message(t_err err, char *message);
int	check_on_john(t_data *data, pthread_mutex_t *death, t_philo *john);
int	time_to_stop(t_data *data);
int	adjusted_usleep(long int sleep_time, t_data	*data);

#endif /* reporting_h */
