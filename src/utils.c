/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:08:41 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/13 14:29:44 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char	*str)
{
	int	i;
	int	n;
	int	res;

	i = 0;
	while (str[i] == 32 || (str[i] >= 8 && str[i] <= 14))
		i++;
	n = 1;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (2147483648 / 10) && n == -1)
			return (0);
		if (res > (2147483647 / 10))
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * n);
}

int	error_message(t_err err, char *message)
{
	if (err == ERR)
		printf("Error: %s", message);
	return (ERR);
}
