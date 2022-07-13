/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:48:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/07/13 14:41:08 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_error(char *error)
{
	perror(error);
	exit(1);
}

int	ft_init_room(t_table *table, int argc, char **argv)
{
	int		i;
	(void) argc;
	
	table->philo_count = ft_atoi(argv[1]);
	
	printf("Malloc philo struct\n");
	table->philo = ft_calloc(sizeof(t_philo), table->philo_count);
	if (!table->philo)
		return (NULL);
	i = -1;
	while(++i <= table->philo_count)
	{
		table->philo[i].r = table;
		printf("init room = %p pointer = %p\n", table, p[i].r);
		table->philo[i].philo = i;
		printf("init i = %d philo = %d\n", i, philo[i].philo);
	}
	return (p);
}

/*
void	*routine(void *arg)
{
	t_philo	*r;

	r = arg;
	int	i = 0;
	printf("Test from threads no\n");
	while (i < 10)
	{
	pthread_mutex_lock(&r->mutex);
		r->add++;
		i++;
		printf("adding loop = %d\n", r->add);
	pthread_mutex_unlock(&r->mutex);
	usleep(1);
	}
	printf("Ending thread with add = %d\n", r->add);
	return(NULL);
}
int	ft_sit_at_table(t_philo	**p)
{
	if (pthread_create(r.t1, NULL,&routine, &r) != 0)
			return (1);
		usleep(1);
		if (pthread_create(r.t2, NULL,&routine, &r) != 0)
			return (2);	
		if (pthread_join(*r.t1,NULL) != 0)
			return (3);
		if (pthread_join(*r.t2,NULL) != 0)
			return (4);
		pthread_mutex_destroy(&r.mutex);
}
*/
int	main(int argc, char **argv)
{
	t_table	table;
	
	if (argc == 5 || argc == 6)
	{
		ft_init_room(&table, argc, argv);
	}
	else
		ft_error("Bad arguments");
}
