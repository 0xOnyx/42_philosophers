/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:25:47 by jerdos-s          #+#    #+#             */
/*   Created: 2022/10/24 15:25:47 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	ft_atoi(char *str)
{
	unsigned long long	current;

	current = 0;
	while(*str >= '0' && *str <= '9')
	{
		current *= 10;
		current += *str - '0';
		str++;
	}
	return ((int)current);
}

unsigned long long	timestamp(void)
{
	struct timeval		tv;
	unsigned long long	res;

	gettimeofday(&tv, NULL);
	res = tv.tv_sec * 1000;
	res += tv.tv_usec / 1000;
	return (res);
}