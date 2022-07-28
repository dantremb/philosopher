/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:46:42 by dantremb          #+#    #+#             */
/*   Updated: 2022/07/27 22:16:43 by dantremb         ###   ########.fr       */
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
	long int	time;
	pthread_t		*chair;
}				t_table;

typedef struct s_philo
{
	t_table			*table;
	int				name;
	int				eated_meal;
	long int	last_meal;
	pthread_mutex_t	*fork;
}				t_philo;

int				ft_sit_at_table(t_table *table, t_philo *philo);
long int		ft_get_time(void);
long int		ft_get_ms(t_philo *philo);
void			ft_sleep(long int sleep);
int				ft_atoi(const char *str);

#endif
