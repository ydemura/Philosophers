//
//  small_tests.c
//  philo_codam
//
//  Created by Yuliia Demura on 1/24/22.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#include "small_tests.h"
#include "time.h"
#include "weave_threads.h"
#include <assert.h>
#include <unistd.h> //for usleep

int check_argc(t_input *inp, const char **argv)
{
	int argc = 5;
	assert(read_input(argc, argv, inp) == 0);
	argc = 6;
	if (argv[5] == NULL)
		assert(read_input(argc, argv, inp) == -1);
	else
		assert(read_input(argc, argv, inp) == 0);
	
	
	argc = -3;
	assert(read_input(argc, argv, inp) == -1);
	argc = 0;
	assert(read_input(argc, argv, inp) == -1);
	argc = 8;
	assert(read_input(argc, argv, inp) == -1);
	argc = 200;
	assert(read_input(argc, argv, inp) == -1);
	return 0;
}

int	arg_numbers(int argc, const char **argv, t_input *inp, int number_arg)
{
	argv[number_arg] = "1000";
	assert(read_input(argc, argv, inp) == 0);
	argv[number_arg] = "1";
	assert(read_input(argc, argv, inp) == 0);
	argv[number_arg] = "0";
	assert(read_input(argc, argv, inp) == 0);
	argv[number_arg] = "2147483647";
	assert(read_input(argc, argv, inp) == 0);
	
	
	argv[number_arg] = "-1000";
	assert(read_input(argc, argv, inp) == -1);
	argv[number_arg] = "\0";
	assert(read_input(argc, argv, inp) == -1);
	argv[number_arg] = NULL;
	assert(read_input(argc, argv, inp) == -1);
	argv[number_arg] = "2147483648";
	assert(read_input(argc, argv, inp) == -1);
	argv[number_arg] = "-2147483648";
	assert(read_input(argc, argv, inp) == -1);
	
	return 0;
}

int check_argv(int argc, const char **argv, t_input *inp)
{
	arg_numbers(argc, argv, inp, 1);
	argv[1] = "5";
	arg_numbers(argc, argv, inp, 2);
	argv[2] = "5";
	arg_numbers(argc, argv, inp, 3);
	argv[3] = "5";
	arg_numbers(argc, argv, inp, 4);
	argv[4] = "5";
	if (argc == 6)
	{
		arg_numbers(argc, argv, inp, 5);
		argv[1] = "5";
	}
	return 0;
}

int	test_input(int argc, const char **argv)
{
	t_input inp;
	
	check_argc(&inp, argv);
	check_argv(argc, argv, &inp);
	return 0;
}

//void	test_time_count(void)
//{
//	long int start_time;
//	long int timestamp;
//	t_philo philo;
//
//	start_time = get_start_time();
//	printf("time test: %li\n", start_time);
//	int i = 0;
//	while (i < 5)
//	{
//		usleep(4000); //1 s
//		//timestamp = timestamp_in_ms(&philo);
//
//
//		printf("time test: %li\n", timestamp);
//		i++;
//	}
//}

void	test_philo()
{
	int argc_correct1 = 4 + 1;
	int argc_correct2 = 5 + 1;
	const char *argv1[argc_correct1];
	const char *argv2[argc_correct2];
	
	argv1[0] = "philo";
	argv1[1] = "5";
	argv1[2] = "5";
	argv1[3] = "5";
	argv1[4] = "5";
	
	argv2[0] = "philo";
	argv2[1] = "6";
	argv2[2] = "6";
	argv2[3] = "6";
	argv2[4] = "6";
	argv2[5] = "6";
	
	//test_time_count();
	
	test_input(argc_correct1, argv1);
	test_input(argc_correct2, argv2);
}
