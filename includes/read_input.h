/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:16:34 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/13 14:18:54 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_INPUT_H
# define READ_INPUT_H

# include <stdio.h>

typedef struct s_input
{
	int	num_philos;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	meal_number;
}	t_input;

int	read_input(int argc, const char **argv, t_input *inp);

#endif /* read_input_h */
