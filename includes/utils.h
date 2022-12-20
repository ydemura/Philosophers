/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemura <ydemura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:23:37 by ydemura           #+#    #+#             */
/*   Updated: 2022/10/13 14:24:16 by ydemura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>

typedef enum e_err
{
	OK = 0,
	ERR = -1
}	t_err;

int	ft_atoi(const char *str);
int	error_message(t_err err, char *message);

#endif /* utils_h */
