/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:46:42 by dantremb          #+#    #+#             */
/*   Updated: 2023/01/15 20:27:26 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				name;
	int				philo_count;
	int				die;
	int				eat;
	int				sleep;
	int				eated_meal;
	int				meal_count;
	long int		last_meal;
	t_table			*t;
	pthread_t		th;
	pthread_mutex_t	fork_one;
	pthread_mutex_t	*fork_two;
}				t_philo;

typedef struct s_table
{
	int				philo_count;
	int				die;
	int				eat;
	int				sleep;
	int				meal_count;
	int				finished;
	long int		time;
	bool			dead;
	t_philo			p[500];
	pthread_mutex_t	lock;
}				t_table;

void			*ft_routine(void *arg);
void			ft_detect_death(t_table *t);
long int		ft_get_time(void);
long int		ft_get_ms(t_philo *philo);
void			ft_sleep(long int time_to_stop);
bool			ft_print_msg(t_philo *philo, int msg);
int				ft_atoi(const char *str);

#endif
