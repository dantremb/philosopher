/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:48:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/07/19 15:17:01 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_error(char *error)
{
	perror(error);
	exit(1);
}

t_philo	*ft_init_philo(t_table *table)
{
	int	i;
	t_philo	*philo;
	
	printf("Init philo\n");
	philo = ft_calloc(sizeof(t_philo), table->philo_count + 1);
	i = -1;
	while(++i < table->philo_count)
	{
		philo[i].name = i + 1;
		philo[i].table = table;
		philo[i].nb_meal = table->meal_count;
		printf("init i = %d philo = %d meal count = %d\n", i, philo[i].name, philo[i].nb_meal);
	}
	return (philo);
}

t_philo	*ft_init_table(t_table *table, int argc, char **argv)
{
	(void) argc;
	printf("ft_init_room\n");
	
	table->philo_count = ft_atoi(argv[1]);
	if (argc == 3)
		table->meal_count = ft_atoi(argv[2]);
	table->threads = ft_calloc(sizeof(t_philo), table->philo_count + 1);

	return (ft_init_philo(table));
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int	i = 0;

	philo = arg;
	printf("Hi! im philo number %d\n", philo->name);
	while (++i <= 10)
	{
		printf("%d sec\n", i);
		usleep(1000000);
	}
	return(NULL);
}

int	ft_sit_at_table(t_table *t, t_philo *philo)
{
	int			i;
	
	i = 0;
	while (i < t->philo_count)
	{
		if (pthread_create(&t->threads[i], NULL,&routine, &philo[i]) != 0)
			return (2);	
		usleep(1);
		i++;
	}
	i = 0;
	while (i < t->philo_count)
	{
		if (pthread_join(t->threads[i],NULL) != 0)
			return (3);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	t;
	t_philo	*philo;
	
	if (argc == 2 || argc == 3)
	{
		philo = ft_init_table(&t, argc, argv);
		ft_sit_at_table(&t, philo);
	}
	else
		ft_error("Bad arguments");
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