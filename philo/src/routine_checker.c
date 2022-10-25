/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:41:38 by jerdos-s          #+#    #+#             */
/*   Created: 2022/10/25 14:41:38 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_checker(void *raw)
{
	unsigned long long	current_time;
	t_philo				*current;
	t_data				*data;
	int					i;

	data = (t_data *)raw;
	current = data->first_philo;
	current_time = timestamp();
	while (!data->all_dead)
	{
		i = 0;
		while (i++ < data->options.philo_len)
		{
			pthread_mutex_lock(&data->check_eating);
			if (current_time - current->last_eat > data->options.time_to_die)
				current->dead = 1;
			if (current->eat >= data->options.max_eat)
				current->dead = 1;
			if (current->dead)
			{
				data->all_dead = 1;
				print_action(current, died);
			}
		}
	}
	return (NULL);
}