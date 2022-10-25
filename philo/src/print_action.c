/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:25:47 by jerdos-s          #+#    #+#             */
/*   Created: 2022/10/24 15:25:47 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*get_message(enum e_action	action)
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

	msg = get_message(action);
	data = philo->data;
	current_time = timestamp() - data->start_time;
	printf("value start => %llu current => %llu\n", data->start_time, timestamp());
	printf("%llu\t\t%d %s\n", current_time, philo->id, msg);
}