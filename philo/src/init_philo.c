/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:12:22 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/10/26 15:12:26 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philo(t_philo **current, int id, t_data *data)
{
	t_philo	*node;

	node = (t_philo *)malloc(sizeof(t_philo));
	if (!node)
		return (1);
	node->dead = 0;
	node->eat = 0;
	node->id = id;
	node->data = data;
	node->next = NULL;
	if (pthread_mutex_init(&node->fork, NULL) != 0)
		return (1);
	*current = node;
	return (0);
}

static void	add_front(t_philo **first_elem, t_philo *new)
{
	t_philo	*current;

	if (!*first_elem)
		*first_elem = new;
	else
	{
		current = *first_elem;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

int	init_philo(t_data *data)
{
	int		i;
	t_philo	*current_philo;

	i = 0;
	data->start_time = timestamp();
	while (i < data->options.philo_len)
	{
		if (create_philo(&current_philo, i, data))
			return (1);
		add_front(&data->first_philo, current_philo);
		i++;
	}
	current_philo->next = data->first_philo;
	current_philo = data->first_philo;
	i = 0;
	while (i++ < data->options.philo_len)
	{
		if (pthread_create(&current_philo->thread, NULL,
				&routine_philo, (void *)current_philo) != 0)
			return (1);
		current_philo = current_philo->next;
	}
	return (0);
}

int	init_checker(t_data *data)
{
	if (data->options.philo_len == 0)
	{
		data->all_dead = 1;
		return (0);
	}
	if (pthread_mutex_init(&data->print_action, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->check_eating, NULL) != 0)
		return (1);
	if (pthread_create(&data->thread_check, NULL,
			&routine_checker, (void *)data) != 0)
		return (1);
	return (0);
}
