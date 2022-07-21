/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:46:42 by dantremb          #+#    #+#             */
/*   Updated: 2022/07/21 15:53:40 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_table
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	int				finished;
	long unsigned	time;
	pthread_t		*chair;
}				t_table;

typedef struct s_philo
{
	t_table 		*table;
	int				name;
	int				eated_meal;
	long unsigned	last_meal;
	pthread_mutex_t	*fork;
}				t_philo;
#endif

int				ft_sit_at_table(t_table *table, t_philo *philo);
long unsigned	ft_get_time(void);
unsigned long	ft_get_ms(t_philo *philo);
int				ft_atoi(const char *str);