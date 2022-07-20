/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:48:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/07/20 19:06:03 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_error(char *error)
{
	perror(error);
	exit(0);
}

long unsigned	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

unsigned long	ft_get_ms(t_philo *philo)
{
	return (ft_get_time() - philo->table->time);
}

/*
pthread_mutex_t	*ft_init_fork(t_philo *philo, t_table *table)
{
	pthread_mutex_t	*fork;
	int				i;

	i = -1;
	fork = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	while (++i < table->philo_count)
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			return (1);
}
*/
t_philo	*ft_init_philo(t_table *table)
{
	t_philo			*philo;
	//pthread_mutex_t	*fork;
	int				i;
	
	//fork = ft_init_fork(philo, table);
	philo = ft_calloc(sizeof(t_philo), table->philo_count + 1);
	i = -1;
	while(++i < table->philo_count)
	{
		philo[i].name = i + 1;
		philo[i].table = table;
		philo[i].eated_meal = 0;
		philo[i].last_meal = 0;
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
	return (ft_init_philo(table));
}

void	*ft_eating(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->name % 2 == 0)
		usleep(10);
	philo->last_meal = ft_get_time();
	while (1)
	{
		printf("%lums Philosopher(%d) eating!\n",ft_get_ms(philo), philo->name);
		usleep(philo->table->time_to_eat * 1000);
		printf("%lums Philosopher(%d) finished eating and now sleeping!\n",ft_get_ms(philo), philo->name);
		usleep(philo->table->time_to_sleep * 1000);
		philo->eated_meal += 1;
	}
	return(NULL);
}

void	ft_death_watcher(t_table *table, t_philo *philo)
{
	(void)philo;
	while (1)
	{
		if (table->meal_count == 0)
			exit(0);
		usleep(50);
	}
}

int	ft_sit_at_table(t_table *table, t_philo *philo)
{
	pthread_t	*chair;
	int			i;
	
	i = -1;
	chair = ft_calloc(sizeof(pthread_t), table->philo_count);
	while (++i < table->philo_count)
		if (pthread_create(&chair[i], NULL,&ft_eating, &philo[i]) != 0)
			return (1);	
	ft_death_watcher(table, philo);
	i = -1;
	while (++i < table->philo_count)
		if (pthread_join(chair[i],NULL) != 0)
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;
	
	if (argc < 5 || argc > 6)
		ft_error("Argument needed : [philo_count] [time_to_die] [time_to_eat] [time_to_sleep] [nb_meal]");
	philo = ft_init_table(&table, argc, argv);
	ft_sit_at_table(&table, philo);
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
