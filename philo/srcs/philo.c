/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:48:30 by dantremb          #+#    #+#             */
/*   Updated: 2023/01/14 21:42:36 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

bool	ft_init_philo(t_table *table)
{
	int				i;

	i = -1;
	while (++i < table->philo_count)
	{
		table->philo[i].name = i + 1;
		table->philo[i].philo_count = table->philo_count;
		table->philo[i].die = table->die;
		table->philo[i].eat = table->eat;
		table->philo[i].sleep = table->sleep;
		table->philo[i].meal_count = table->meal_count;
		table->philo[i].eated_meal = 0;
		table->philo[i].last_meal = table->time;
		table->philo[i].table = table;
		if (pthread_mutex_init(&table->philo[i].fork_one, NULL) != 0)
			return (true);
		table->philo[i].fork_two = &table->philo[(i + 1) % table->philo_count].fork_one;
	}
	return (false);
}

bool	ft_init_table(t_table *table, int argc, char **argv)
{
	table->philo_count = ft_atoi(argv[1]);
	table->die = ft_atoi(argv[2]);
	table->eat = ft_atoi(argv[3]);
	table->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->meal_count = ft_atoi(argv[5]);
	else
		table->meal_count = -1;
	table->time = ft_get_time();
	table->finished = 0;
	if (pthread_mutex_init(&table->dead, NULL) != 0)
		return (true);
	return (false);
}

bool	ft_check_argv(char **argv)
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
			if (argv[ip][is] < '0' || argv[ip][is] > '9')
				return (true);
		}
		if (ft_atoi(argv[ip]) < 0)
			return (true);
	}
	if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[1]) > 500)
		return (true);
	if (argv[5] && ft_atoi(argv[5]) == 0)
		return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		printf("[philo][die][eat][sleep][meal]\n");
	else if (ft_check_argv(argv) == 1)
		printf("Bad Arguments Combination\n");
	else if (ft_init_table(&table, argc, argv))
		printf("Error while initializing table\n");
	else if (ft_init_philo(&table))
		printf("Error while initializing philosophers\n");
	else
		ft_sit_at_table(&table);
	return (0);
}
