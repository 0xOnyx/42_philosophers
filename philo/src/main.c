/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:11:14 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/10/26 15:11:41 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_usage(char *name)
{
	printf("usage =>\n");
	printf("%s number_of_philosophers time_to_die time_to_eat time_to_sleep\n"
		"[number_of_times_each_philosopher_must_eat]", name);
}

static int	init_arg(int argc, char **argv, t_data *data)
{
	data->options.philo_len = (int)ft_atoi(argv[1]);
	data->options.time_to_die = ft_atoi(argv[2]);
	data->options.time_to_eat = ft_atoi(argv[3]);
	data->options.time_to_sleep = ft_atoi(argv[4]);
	if (data->options.philo_len < 1
		|| data->options.philo_len > 2147483647
		|| data->options.time_to_die < 1
		|| data->options.time_to_die > 2147483647
		|| data->options.time_to_eat < 1
		|| data->options.time_to_eat > 2147483647
		|| data->options.time_to_sleep < 1
		|| data->options.time_to_sleep > 2147483647)
		return (1);
	if (argc > 5)
	{
		data->options.max_eat = (int)ft_atoi(argv[5]);
		if (data->options.max_eat <= 0)
			return (1);
	}
	else
		data->options.max_eat = -1;
	return (0);
}

static void	free_all(t_data data)
{
	int		i;
	t_philo	*current;
	t_philo	*swap;

	i = 0;
	current = data.first_philo;
	pthread_join(data.thread_check, NULL);
	while (current && i++ < data.options.philo_len)
	{
		pthread_join(current->thread, NULL);
		swap = current->next;
		pthread_mutex_destroy(&current->fork);
		free(current);
		current = swap;
	}
	pthread_join(data.thread_check, NULL);
	pthread_mutex_destroy(&data.check_eating);
}

void	print_error(char *str)
{
	printf("[ERROR]:\t%s\n", str);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){};
	data.options = (t_options){};
	if (argc < 4)
	{
		print_usage(argv[0]);
		return (1);
	}
	if (init_arg(argc, argv, &data)
		|| init_philo(&data)
		|| init_checker(&data))
	{
		print_error("init vars often due to bad args");
		free_all(data);
		return (1);
	}
	free_all(data);
	return (0);
}
