/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:48:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/07/19 23:33:24 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_error(char *error)
{
	perror(error);
	exit(1);
}

t_philo	*ft_init_philo(t_table *table)
{
	int	i;
	t_philo	*philo;
	
	printf("Init philo\n");
	philo = ft_calloc(sizeof(t_philo), table->philo_count + 1);
	i = -1;
	while(++i < table->philo_count)
	{
		philo[i].name = i + 1;
		philo[i].table = table;
		philo[i].nb_meal = table->meal_count;
		printf("init i = %d philo = %d meal count = %d\n", i, philo[i].name, philo[i].nb_meal);
	}
	//ft_init_fork(philo);
	return (philo);
}

t_philo	*ft_init_table(t_table *table, int argc, char **argv)
{
	(void) argc;
	printf("ft_init_room\n");
	table->philo_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->meal_count = ft_atoi(argv[5]);
	return (ft_init_philo(table));
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int	i = 0;

	philo = arg;
	printf("Hi! im philo number %d\n", philo->name);
	while (++i <= 10)
	{
		printf("%d sec\n", i);
		usleep(1000000);
	}
	return(NULL);
}

int	ft_sit_at_table(t_table *table, t_philo *philo)
{
	pthread_t	*chair;
	int			i;
	
	i = -1;
	chair = ft_calloc(sizeof(pthread_t) * table->philo_count);
	while (++i < table->philo_count)
		if (pthread_create(&chair[i], NULL,&routine, &philo[i]) != 0)
			return (1);	
	i = -1;
	while (++i < table->philo_count)
		if (pthread_join(&chair[i],NULL) != 0)
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	t;
	t_philo	*philo;
	
	if (argc < 5 || argc > 6)
		ft_error("Bad arguments");
	philo = ft_init_table(&t, argc, argv);
	ft_sit_at_table(&t, philo);
	return (0);
}

//	printf("Test from threads no\n");
//	while (i < 10)
//	{
//	pthread_mutex_lock(&r->mutex);
//		r->add++;
//		i++;
//		printf("adding loop = %d\n", r->add);
//	pthread_mutex_unlock(&r->mutex);
//	usleep(1);
//	}
//	printf("Ending thread with add = %d\n", r->add);