/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:35:51 by dantremb          #+#    #+#             */
/*   Updated: 2023/01/15 19:30:06 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_print_msg(t_philo *philo, int msg)
{
	pthread_mutex_lock(&philo->table->dead);
	if (msg == FORK)
		printf("%lu %d has taken a fork\n", ft_get_ms(philo), philo->name);
	else if (msg == EAT)
		printf("%lu %d is eating!\n", ft_get_ms(philo), philo->name);
	else if (msg == SLEEP)
		printf("%lu %d is sleeping!\n", ft_get_ms(philo), philo->name);
	else if (msg == THINK)
		printf("%lu %d is thinking!\n", ft_get_ms(philo), philo->name);
	pthread_mutex_unlock(&philo->table->dead);
}

void	ft_take_a_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_one);
	ft_print_msg(philo, FORK);
	pthread_mutex_lock(philo->fork_two);
	philo->last_meal = ft_get_time();
	ft_print_msg(philo, FORK);
}

void	*ft_eating(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->name % 2 == 0)
		usleep(500);
	philo->last_meal = ft_get_time();
	while (1)
	{
		ft_take_a_fork(philo);
		ft_print_msg(philo, EAT);
		ft_sleep(philo->last_meal + philo->eat);
		pthread_mutex_unlock(&philo->fork_one);
		pthread_mutex_unlock(philo->fork_two);
		ft_print_msg(philo, SLEEP);
		philo->eated_meal += 1;
		if (philo->eated_meal == philo->meal_count)
			break ;
		ft_sleep(philo->last_meal + philo->sleep + philo->eat);
		ft_print_msg(philo, THINK);
	}
	philo->table->finished += 1;
	return (NULL);
}

bool	ft_death_watcher(t_table *table)
{
	int	i;

	i = 0;
	usleep(500);
	while (1)
	{
		if (table->finished == table->philo_count)
			return (false);
		if (ft_get_time() - table->philo[i].last_meal > table->die)
		{
			printf("%lu %d is dead\n", ft_get_ms(&table->philo[i]), table->philo[i].name);
			pthread_mutex_lock(&table->dead);
			return (true);
		}
		i = (i + 1) % table->philo_count;
		usleep(500);
	}
}

bool	ft_sit_at_table(t_table *table)
{
	int			i;

	i = -1;

	while (++i < table->philo_count)
		if (pthread_create(&table->philo[i].thread, NULL, &ft_eating, &table->philo[i]))
			return (false);
	if (ft_death_watcher(table) == 1)
		return (false);
	i = -1;
	while (++i < table->philo_count)
		pthread_join(table->philo[i].thread, NULL);
	return (true);
}
