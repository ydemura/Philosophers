/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:08:18 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/13 17:08:31 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "weave_threads.h"
#include "reporting.h"
#include "utils.h"
#include <stdio.h>

//wrong in input ./philo 3 310 100 100 30
// make re && ./philo 3 320 100 100 - issue not with meal number

int	main(int argc, const char	*argv[])
{
	t_input	inp;

	if (read_input(argc, argv, &inp) == ERR)
		return (error_message(ERR, "input"));
	if (weave_threads(&inp) == ERR)
		return (ERR);
	return (0);
}
