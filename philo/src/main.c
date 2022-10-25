#include "philo.h"

static void	print_usage(char *name)
{
	printf("usage =>\n");
	printf("./%s number_of_philosophers time_to_die time_to_eat time_to_sleep\n"
		   "[number_of_times_each_philosopher_must_eat]", name);
}

static int	init_arg(int argc, char **argv, t_data *data)
{
	data->options.philo_len = ft_atoi(argv[1]);
	data->options.time_to_die = ft_atoi(argv[2]);
	data->options.time_to_eat = ft_atoi(argv[3]);
	data->options.time_to_sleep = ft_atoi(argv[4]);
	if (argc > 4)
		data->options.max_eat = ft_atoi(argv[5]);
	else
		data->options.max_eat = -1;
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){};
	data.options = (t_options){};
	if (argc < 4)
	{
		print_usage(argv[0]);
		return (1);
	}
	if (init_arg(argc, argv, &data)
		&& init_philo(&data))
		&& init_checker(&data))
	{
		print_error();
		free_all(data);
		return (1);
	}
	free_all(data);
	return (0);
}