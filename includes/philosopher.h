/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:46:42 by dantremb          #+#    #+#             */
/*   Updated: 2022/07/13 14:36:01 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "libft/includes/libft.h"
# include <stdio.h>
# include <pthread.h>

typedef struct s_philo
{
	t_table	*r;
	int		name;
}				t_philo;

typedef struct s_table
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	pthread_mutex_t	mutex;
	pthread_t		*th;
	t_philo			*philo;

}				t_table;

#endif
