/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:48:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/07/19 13:26:45 by dantremb         ###   ########.fr       */
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
		philo[i].name = i;
		philo[i].table = table;
		printf("init i = %d philo = %d\n", i, philo[i].name);
	}
	return (philo);
}

t_philo	*ft_init_room(t_table *table, int argc, char **argv)
{
	int		i;
	t_philo	*philo;
	(void) argc;
	
	table->philo_count = ft_atoi(argv[1]);
	
	printf("Malloc philo struct\n");
	
	table->th = ft_calloc(sizeof(t_philo), table->philo_count + 1);

	
	return (philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	printf("Hi! im philo number %d\n", philo->name);
	return(NULL);
}

int	ft_sit_at_table(t_table *t, t_philo *philo)
{
	int			i;
	
	i = 0;
	while (i < t->philo_count)
	{
		if (pthread_create(&t->th[i], NULL,&routine, &philo[i]) != 0)
			return (2);	
		usleep(1);
		i++;
	}
	i = 0;
	while (i < t->philo_count)
	{
		if (pthread_join(t->th[i],NULL) != 0)
			return (3);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	t;
	t_philo	*philo;
	
	if (argc == 2 || argc == 2)
	{
		philo = ft_init_room(&t, argc, argv);
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