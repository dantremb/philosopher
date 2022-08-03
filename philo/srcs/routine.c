/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:35:51 by dantremb          #+#    #+#             */
/*   Updated: 2022/07/27 23:16:51 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_drop_fork(t_philo *philo, int fork1, int fork2)
{
	pthread_mutex_unlock(&philo->fork[fork1]);
	pthread_mutex_unlock(&philo->fork[fork2]);
}

void	ft_take_a_fork(t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->fork[fork]);
	printf("%lums %d has taken a fork\n", ft_get_ms(philo), philo->name);
}

void	*ft_eating(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->name % 2 == 0)
		usleep(philo->table->time_to_die * 100);
	philo->last_meal = ft_get_time();
	while (1)
	{
		ft_take_a_fork(philo, philo->name - 1);
		ft_take_a_fork(philo, philo->name % philo->table->philo_count);
		philo->last_meal = ft_get_time();
		printf("%lums %d is eating!\n", ft_get_ms(philo), philo->name);
		ft_sleep(philo->last_meal + philo->table->time_to_eat);
		ft_drop_fork(philo, philo->name - 1,
			philo->name % philo->table->philo_count);
		printf("%lums %d is sleeping\n", ft_get_ms(philo), philo->name);
		philo->eated_meal += 1;
		if (philo->eated_meal == philo->table->meal_count)
			break ;
		ft_sleep(philo->last_meal + philo->table->time_to_sleep + philo->table->time_to_eat);
		printf("%lums %d is thinking\n", ft_get_ms(philo), philo->name);
		ft_sleep(((philo->last_meal + philo->table->time_to_die) / 100) * 90);
	}
	philo->table->finished++;
	return (NULL);
}

int	ft_death_watcher(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	usleep(table->time_to_die * 500);
	while (1)
	{
		if (table->finished == table->philo_count)
			return (1);
		if (ft_get_time() - philo[i].last_meal
			> table->time_to_die)
		{
			printf("%lums %d is dead\n", ft_get_ms(&philo[i]), philo[i].name);
			return (1);
		}
		i = (i + 1) % table->philo_count;
		usleep(50);
	}
}

int	ft_sit_at_table(t_table *table, t_philo *philo)
{
	int			i;

	i = -1;
	table->chair = malloc(sizeof(pthread_t) * table->philo_count);
	if (!table->chair)
		return (1);
	while (++i < table->philo_count)
		if (pthread_create(&table->chair[i], NULL, &ft_eating, &philo[i]) != 0)
			return (1);
	if (ft_death_watcher(table, philo) == 1)
		return (1);
	i = -1;
	while (++i < table->philo_count)
		if (pthread_join(table->chair[i], NULL) != 0)
			return (1);
	return (0);
}
