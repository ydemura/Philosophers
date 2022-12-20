//
//  utilities.h
//  new_philo
//
//  Created by Julia Demura on 14/10/2022.
//

#ifndef utilities_h
#define utilities_h

typedef enum e_err
{
	OK = 0,
	ERR = -1
}	t_err;

int			error_message(t_err err, char *message);
int			ft_atoi(const char	*str);
long int	get_start_time(void);
long int	timestamp(long int start_time);

#endif /* utilities_h */
