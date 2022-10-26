/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:35:06 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/10/26 15:35:11 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_all_eat(t_data *data)
{
	t_philo	*current;
	int		i;

	i = 0;
	current = data->first_philo;
	while (i < data->options.philo_len && current->eat >= data->options.max_eat
		   && data->options.max_eat > 0)
	{
		current = current->next;
		i++;
	}
	if (i == data->options.philo_len)
	{
		data->all_dead = 1;
		return (1);
	}
	return (0);
}

void	*routine_checker(void *raw)
{
	unsigned long long	current_time;
	t_philo				*current;
	t_data				*data;
	int					i;

	data = (t_data *)raw;
	current = data->first_philo;
	i = 0;
	while (!data->all_dead)
	{
		i = 0;
		while (i++ < data->options.philo_len)
		{
			current_time = timestamp();
			pthread_mutex_lock(&data->check_eating);
			if (current->dead || current_time - current->last_eat > data->options.time_to_die)
			{
				print_action(current, died);
				current->dead = 1;
			}
			pthread_mutex_unlock(&data->check_eating);
			if (current->dead)
				break ;
			current = current->next;
		}
		if (current->dead)
			break ;
		if (check_all_eat(data))
			break ;
	}
	data->all_dead = 1;
	return (NULL);
}
