/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weave_threads.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:24:21 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/13 16:31:52 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAVE_THREADS_H
# define WEAVE_THREADS_H

# include "launch_box_data.h"
# include <stdio.h>

int	weave_threads(t_input *inp);
int	new_eat_per_thread(t_philo *john, t_philo *philo, int index);

#endif /* weave_threads_h */
