/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:48:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/07/21 11:23:42 by dantremb         ###   ########.fr       */
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


pthread_mutex_t	*ft_init_fork(t_table *table)
{
	pthread_mutex_t	*fork;
	int				i;

	i = -1;
	fork = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	while (++i < table->philo_count)
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			return (NULL);
	return (fork);
}

t_philo	*ft_init_philo(t_table *table)
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	int				i;
	
	fork = ft_init_fork(table);
	philo = ft_calloc(sizeof(t_philo), table->philo_count + 1);
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

void	ft_drop_fork(t_philo *philo, int fork1, int fork2)
{
	pthread_mutex_unlock(&philo->fork[fork1]);
	pthread_mutex_unlock(&philo->fork[fork2]);
}

void	ft_take_a_fork(t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->fork[fork]);
	printf("%lums %d has taken a fork\n",ft_get_ms(philo), philo->name);
}

void	*ft_eating(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->name % 2 == 0)
		usleep(100);
	philo->last_meal = ft_get_time();
	while (1)
	{
		ft_take_a_fork(philo, philo->name - 1);
		ft_take_a_fork(philo, philo->name % philo->table->philo_count);
		philo->last_meal = ft_get_time();
		printf("%lums %d is eating!\n",ft_get_ms(philo), philo->name);
		usleep(philo->table->time_to_eat * 1000);
		ft_drop_fork(philo, philo->name - 1, philo->name % philo->table->philo_count);
		printf("%lums %d is sleeping\n",ft_get_ms(philo), philo->name);
		philo->eated_meal += 1;
		if (philo->eated_meal == philo->table->meal_count)
		{
			philo->table->finished++;
			break ;
		}
		usleep(philo->table->time_to_sleep * 1000);
		printf("%lums %d is thinking\n",ft_get_ms(philo), philo->name);
	}
	return(NULL);
}

void	ft_death_watcher(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	usleep(200);
	while (1)
	{
		if (table->finished == table->philo_count)
			exit(0);
		if (ft_get_time() - philo[i].last_meal > (unsigned long)table->time_to_die)
		{
			printf("%lums %d is dead\n",ft_get_ms(&philo[i]), philo[i].name);
			exit(1);
		}
		i = (i + 1) % table->philo_count;
		usleep(5000);
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
		ft_error("Argument needed : nb_of_philo time_to_die time_to_eat time_to_sleep [nb of meals]");
	philo = ft_init_table(&table, argc, argv);
	ft_sit_at_table(&table, philo);
	return (0);
}
