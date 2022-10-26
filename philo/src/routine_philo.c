/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:35:52 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/10/26 15:35:54 by jerdos-s         ###   ########.fr       */
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
			break ;
	}
}

static void	eating_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_action(philo, take_fork);
	if (philo->next == philo)
		return ;
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
	philo->last_eat = timestamp();
	if (philo->id % 2)
		usleep(1500);
	while (!philo->dead)
	{
		eating_philo(philo);
		if (philo->data->all_dead || philo->next == philo)
			break ;
		print_action(philo, sleeping);
		waiting(philo->data->options.time_to_sleep, philo);
		print_action(philo, thinking);
	}
	return (NULL);
}
