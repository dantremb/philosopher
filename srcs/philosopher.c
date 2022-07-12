/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:48:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/07/11 11:29:37 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <unistd.h>

pthread_mutex_t	mutex;
int add = 0;

void	ft_error(char *error)
{
	perror(error);
	exit(1);
}

void	ft_init_room(t_room *r, char **argv)
{
	r->philo_count = ft_atoi(argv[1]);
	r->time_to_die = ft_atoi(argv[2]) * 1000;
	r->time_to_eat = ft_atoi(argv[3]) * 1000;
	r->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5] != NULL)
		r->meal_count = ft_atoi(argv[5]);
}

void	*routine()
{
	int	i = 0;
	printf("Test from threads\n");
	while (i < 10)
	{
	pthread_mutex_lock(&mutex);
		add++;
		i++;
		printf("adding loop = %d\n", add);
	pthread_mutex_unlock(&mutex);
	usleep(1);
	}
	printf("Ending thread with add = %d\n", add);
	return(NULL);
}

int	main(int argc, char **argv)
{
	t_room		r;
	pthread_t	t1;
	pthread_t	t2;
	
	pthread_mutex_init(&mutex, NULL);
	if (argc == 5 || argc == 6)
	{
		ft_init_room(&r, argv);
		ft_printf("argc = %d\n", argc);
		ft_printf("philo_count = %d\n", r.philo_count);
		ft_printf("time_to_die = %d\n", r.time_to_die);
		ft_printf("time_to_eat = %d\n", r.time_to_eat);
		ft_printf("time_to_sleep = %d\n", r.time_to_sleep);
		if (argc == 6)
			ft_printf("meal_count = %d\n", r.meal_count);
		if (pthread_create(&t1, NULL,&routine, NULL) != 0)
			return (1);
		if (pthread_create(&t2, NULL,&routine, NULL) != 0)
			return (2);	
		if (pthread_join(t1,NULL) != 0)
			return (3);
		if (pthread_join(t2,NULL) != 0)
			return (4);
		pthread_mutex_destroy(&mutex);
	}
	else
		ft_error("Empty arguments");
}
