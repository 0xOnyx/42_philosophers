/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:33:12 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/10/26 15:33:13 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*get_message(enum e_action action)
{
	if (action == take_fork)
		return ("has taken a fork");
	if (action == eating)
		return ("is eating");
	if (action == sleeping)
		return ("is sleeping");
	if (action == thinking)
		return ("is thinking");
	if (action == died)
		return ("died");
	return (NULL);
}

void	print_action(t_philo *philo, enum e_action action)
{
	unsigned long long	current_time;
	t_data				*data;
	char				*msg;

	if (philo->dead || philo->data->all_dead)
		return ;
	pthread_mutex_lock(&philo->data->print_action);
	msg = get_message(action);
	data = philo->data;
	current_time = timestamp() - data->start_time;
	printf("%llu\t\t%d %s\n", current_time, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->data->print_action);
}
