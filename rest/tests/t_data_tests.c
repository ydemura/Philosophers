//
//  t_philo_tests.c
//  philo_codam
//
//  Created by Yuliia Demura on 10/11/22.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#include "t_data_tests.h"
#include "time.h"
#include "weave_threads.h"
#include "launch_box_data.h"
#include <stdlib.h>

void	test_philo(t_input inp)
{
//	void *test_res;
//
//	test_res = initiate_philos(inp);
//
//	t_philo *philo_test;
//	philo_test = (t_philo *)test_res;
//
	
}

void	test_time(void)
{
	long int time;
	long int time_upd;
	int i = 0;
	
	time = get_start_time();
	while (i < 100)
	{
		time_upd = timestamp(time);
		adjusted_usleep(200);
		printf("timestamp: %li\n", time_upd);
		i++;
	}
	exit(0);
}
