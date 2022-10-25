/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:41:38 by jerdos-s          #+#    #+#             */
/*   Created: 2022/10/25 14:41:38 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	waiting(unsigned long long time, t_philo *philo)
{
	unsigned long long	current_time;

	current_time = timestamp();
	while (!philo->dead)
	{
		usleep(50);
		if ((timestamp() - current_time) >= time)
			break;
	}
}

static void	eating_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_action(philo, take_fork);
	pthread_mutex_lock(&philo->next->fork);
	pthread_mutex_lock(&philo->data->check_eating);
	print_action(philo, take_fork);
	philo->last_eat = timestamp();
	print_action(philo, eating);
	(philo->eat)++;
	pthread_mutex_unlock(&philo->data->check_eating);
	waiting(philo->data->options.time_to_eat, philo);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	*routine_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2)
		usleep(1500);
	while (!philo->data->all_dead)
	{
		eating_philo(philo);
		printf("waiting for sleeping\n");
		print_action(philo, sleeping);
		waiting(philo->data->options.time_to_sleep, philo);
		print_action(philo, thinking);
	}
	printf("finish\n");
	return (NULL);
}