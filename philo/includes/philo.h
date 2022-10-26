/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:11:58 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/10/26 15:11:59 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;

enum	e_action
{
	take_fork,
	eating,
	sleeping,
	thinking,
	died,
};

typedef struct s_option
{
	int					philo_len;
	int					max_eat;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
}	t_options;

typedef struct s_philo
{
	int					dead;
	unsigned long long	last_eat;
	int					eat;
	int					id;
	pthread_t			thread;
	pthread_mutex_t		fork;
	t_data				*data;
	struct s_philo		*next;
}	t_philo;

struct	s_data
{
	int					all_dead;
	unsigned long long	start_time;
	t_philo				*first_philo;
	pthread_t			thread_check;
	pthread_mutex_t		check_eating;
	pthread_mutex_t		print_action;
	t_options			options;
};

int					init_philo(t_data *data);
int					init_checker(t_data *data);

void				*routine_philo(void *data);
void				*routine_checker(void *raw);

void				print_error(char *str);
void				print_action(t_philo *philo, enum e_action action);

unsigned long long	timestamp(void);
unsigned long long	ft_atoi(char *str);

#endif
