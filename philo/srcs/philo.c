/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:48:30 by dantremb          #+#    #+#             */
/*   Updated: 2023/01/15 20:23:28 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

bool	ft_create_threads(t_table *t)
{
	int			i;

	i = -1;
	while (++i < t->philo_count)
		pthread_create(&t->p[i].th, NULL, &ft_routine, &t->p[i]);
	i = -1;
	ft_detect_death(t);
	while (++i < t->philo_count)
		pthread_join(t->p[i].th, NULL);
	return (true);
}

bool	ft_init_philo(t_table *t)
{
	int				i;

	i = -1;
	while (++i < t->philo_count)
	{
		t->p[i].name = i + 1;
		t->p[i].philo_count = t->philo_count;
		t->p[i].die = t->die;
		t->p[i].eat = t->eat;
		t->p[i].sleep = t->sleep;
		t->p[i].meal_count = t->meal_count;
		t->p[i].eated_meal = 0;
		t->p[i].last_meal = t->time;
		t->p[i].t = t;
		if (pthread_mutex_init(&t->p[i].fork_one, NULL) != 0)
			return (true);
		t->p[i].fork_two = &t->p[(i + 1) % t->philo_count].fork_one;
	}
	return (false);
}

bool	ft_init_table(t_table *t, int argc, char **argv)
{
	t->philo_count = ft_atoi(argv[1]);
	t->die = ft_atoi(argv[2]);
	t->eat = ft_atoi(argv[3]);
	t->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		t->meal_count = ft_atoi(argv[5]);
	else
		t->meal_count = -1;
	t->time = ft_get_time();
	t->finished = 0;
	t->dead = false;
	if (pthread_mutex_init(&t->lock, NULL) != 0)
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
		ft_create_threads(&table);
	return (0);
}
