/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:08:36 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/13 16:32:48 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include "utils.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

//gettimeofaday, real time in ms for further referenses
long int	get_start_time(void)
{
	struct timeval	tm;
	long int		start_time;

	if (gettimeofday(&tm, NULL) != 0)
		return (ERR);
	start_time = (tm.tv_sec * 1000) + (tm.tv_usec / 1000);
	return (start_time);
}

//how many ms passed from start time, comparing start time
//to current (gettimeofday)
long int	timestamp(long int start_time)
{
	struct timeval	tm;
	long int		time_now;
	long int		timestamp;

	if (gettimeofday(&tm, NULL) != 0)
		return (ERR);
	time_now = (tm.tv_sec * 1000) + (tm.tv_usec / 1000);
	timestamp = time_now - start_time;
	return (timestamp);
}
