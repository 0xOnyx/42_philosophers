/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:36:17 by jerdos-s          #+#    #+#             */
/*   Created: 2022/10/24 15:36:17 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philo(t_philo **current, int id, t_data *data)
{
	t_philo	*node;

	node = (t_philo *)malloc(sizeof(t_philo));
	node->deat = 0;
	node->eat = 0;
	node->id = id;
	node->data = data;
	node->next = NULL;
	if (pthread_mutex_init(&node->fork, NULL) != 0)
		return (1);
	if (pthread_create(&node->thread, NULL, &routine_philo, (void *)node) != 0)
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
		while(current->next)
			current = current->next;
		current->next = new;
	}
}

int	init_philo(t_data *data)
{
	int		i;
	t_philo	*current_philo;

	i = 0;
	while (i < data->options.philo_len)
	{
		if (create_philo(&current_philo, i, (void *)current_philo))
			return (1);
		add_front(&data->first_philo, current_philo);
	}
	current_philo->next = data->first_philo;
	data->start_time = timestamp();
	return (0);
}

int	init_checker(t_data *data)
{
	if (pthread_mutex_init(&data->check_eating, NULL) != 0)
		return (1);
	if (pthread_create(&data->thread_check, NULL, &routine_checker, (void *)data) != 0)
		return (1);
	return (0);
}