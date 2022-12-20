/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:08:25 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/13 14:27:19 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int	check_integer(int n)
{
	if (n < 0 || n > 2147483647)
		return (1);
	return (0);
}

int	check_int_put_into_struct(const char *src, int *dst)
{
	int	n;

	if (src == NULL || src[0] == '\0')
		return (ERR);
	if (src[0] == '0' && src[1] != '\0')
		return (ERR);
	n = 0;
	n = ft_atoi(src);
	if (check_integer(n) == 0)
		*dst = n;
	else
		return (ERR);
	return (0);
}

int	collect_philo_input(const char **argv, t_input *inp)
{
	if (check_int_put_into_struct(argv[1], &inp->num_philos) == ERR)
		return (ERR);
	if (check_int_put_into_struct(argv[2], &inp->die_time) == ERR)
		return (ERR);
	if (check_int_put_into_struct(argv[3], &inp->eat_time) == ERR)
		return (ERR);
	if (check_int_put_into_struct(argv[4], &inp->sleep_time) == ERR)
		return (ERR);
	return (0);
}

int	read_input(int argc, const char **argv, t_input *inp)
{
	if (argc < 5 || argc > 6)
		return (ERR);
	if (collect_philo_input(argv, inp) == ERR)
		return (ERR);
	if (argc == 6)
	{
		if (check_int_put_into_struct(argv[5],
				&inp->meal_number) == ERR)
			return (ERR);
	}
	else
		inp->meal_number = -1;
	return (0);
}
