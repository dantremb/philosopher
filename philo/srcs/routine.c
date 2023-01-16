/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:35:51 by dantremb          #+#    #+#             */
/*   Updated: 2023/01/15 20:27:33 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_detect_death(t_table *t)
{
	int	i;

	i = 0;
	usleep(500);
	while (1)
	{
		if (t->finished == t->philo_count)
			return ;
		if (ft_get_time() - t->p[i].last_meal > t->die)
		{
			printf("%lu %d is dead\n", ft_get_ms(&t->p[i]), t->p[i].name);
			t->dead = true;
			return ;
		}
		i = (i + 1) % t->philo_count;
		usleep(500);
	}
}


bool	ft_eating(t_philo *p)
{
	pthread_mutex_lock(&p->fork_one);
	if (ft_print_msg(p, FORK))
	{
		pthread_mutex_unlock(&p->fork_one);
		return (true);
	}
	pthread_mutex_lock(p->fork_two);
	p->last_meal = ft_get_time();
	if (ft_print_msg(p, FORK))
	{
		pthread_mutex_unlock(&p->fork_one);
		pthread_mutex_unlock(p->fork_two);
		return (true);
	}
	return (false);
}

bool	ft_sleeping(t_philo *p)
{
	if (ft_print_msg(p, EAT))
		ft_sleep(p->last_meal + p->eat);
	pthread_mutex_unlock(&p->fork_one);
	pthread_mutex_unlock(p->fork_two);
	p->eated_meal += 1;
	if (ft_print_msg(p, SLEEP))
		return (true);
	return (false);
}

void	*ft_routine(void *arg)
{
	t_philo	*p;

	p = arg;
	if (p->name % 2 == 0)
		usleep(500);
	p->last_meal = p->t->time;
	while (1)
	{
		if (ft_eating(p))
			break ;
		if (ft_sleeping(p))
			break ;
		if (p->eated_meal == p->meal_count)
			break ;
		ft_sleep(p->last_meal + p->sleep + p->eat);
		if (ft_print_msg(p, THINK))
			break ;
	}
	p->t->finished += 1;
	return (NULL);
}
