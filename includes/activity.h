/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:14:05 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/13 16:32:02 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIVITY_H
# define ACTIVITY_H

# include "launch_box_data.h"
# include <stdio.h>

typedef enum e_instructions
{
	WAIT = 0,
	CAN_EAT = 1
}				t_instructions;

typedef enum e_actions
{
	THINKING = 0,
	SLEEPING = 1,
	EATING = 2,
}				t_actions;

int		pick_activity_for_john(t_philo *john, t_data *data);
void	*johns_actions_per_thread(void *one_boxed_john_number_i);

#endif /* activity_h */
