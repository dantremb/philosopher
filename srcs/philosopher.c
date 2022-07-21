/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:48:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/07/21 15:45:57 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

pthread_mutex_t	*ft_init_fork(t_table *table)
{
	pthread_mutex_t	*fork;
	int				i;

	i = -1;
	fork = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!fork)
		return (NULL);
	while (++i < table->philo_count)
		if (pthread_mutex_init(&fork[i], NULL) != 0)
		{
			free (fork);
			return (NULL);
		}
	return (fork);
}

t_philo	*ft_init_philo(t_table *table)
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	int				i;
	
	fork = ft_init_fork(table);
	if (!fork)
		return (NULL);
	philo = malloc(sizeof(t_philo) * table->philo_count + 1);
	if (!philo)
	{
		free (fork);
		return (NULL);
	}
	i = -1;
	while(++i < table->philo_count)
	{
		philo[i].name = i + 1;
		philo[i].table = table;
		philo[i].eated_meal = 0;
		philo[i].last_meal = 0;
		philo[i].fork = fork;
	}
	return (philo);
}

t_philo	*ft_init_table(t_table *table, int argc, char **argv)
{
	table->philo_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->meal_count = ft_atoi(argv[5]);
	else
		table->meal_count = -1;
	table->time = ft_get_time();
	table->finished = 0;
	return (ft_init_philo(table));
}


int	ft_check_argv(char **argv)
{
	int	ip;
	int	is;

	ip = 0;
	is = 0;
	while (argv[++ip])
	{
		is = -1;
		while (argv[ip][++is])
		{
			if (argv[ip][is] == '-')
				is++;
			if (argv[ip][is] >= '0' && argv[ip][is] <= '9')
			{
				printf("Arguments need to be numbers\n");
				return (1);
			}
		}
		if (ft_atoi(argv[ip]) < 1)
		{
			printf("Arguments need to greater than 0\n");
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
	{
		printf("[philo][die][eat][sleep][meal]\n");
		return (1);
	}
	if (ft_check_argv(argv) == 1)
		return (1);
	philo = ft_init_table(&table, argc, argv);
	if (!philo)
		return(1);
	ft_sit_at_table(&table, philo);
	if (table.chair)
		free (table.chair);
	free(philo->fork);
	free(philo);
	return (0);
}
