/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:48:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/07/12 21:52:12 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_error(char *error)
{
	perror(error);
	exit(1);
}

t_philo	*ft_init_room(t_room *r, int argc, char **argv)
{
	t_philo	*p;
	int		i;
	(void) argc;
	
	r->philo_count = ft_atoi(argv[1]);
	r->add = 0;
	printf("Malloc philo struct\n");
	p = malloc(sizeof(t_philo) * (ft_atoi(argv[1]) + 1));
	if (!p)
		return (NULL);
	i = -1;
	while(++i <= r->philo_count)
	{
		p[i].r = r;
		printf("init room = %p pointer = %p\n", r, p[i].r);
		p[i].philo = i;
		printf("init i = %d philo = %d\n", i, p[i].philo);
	}
	return (p);
}

void	*routine(void *arg)
{
	t_room	*r;

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

int	main(int argc, char **argv)
{
	t_philo	*p;
	t_room	r;
	
	pthread_mutex_init(&r.mutex, NULL);
	if (argc == 5 || argc == 6)
	{
		p = ft_init_room(&r, argc, argv);
		ft_create_thread()
		p->r->time_to_die = 1;
		/*if (pthread_create(&t1, NULL,&routine, &r) != 0)
			return (1);
		usleep(1);
		if (pthread_create(&t2, NULL,&routine, &r) != 0)
			return (2);	
		if (pthread_join(t1,NULL) != 0)
			return (3);
		if (pthread_join(t2,NULL) != 0)
			return (4);*/
		pthread_mutex_destroy(&r.mutex);
	}
	else
		ft_error("Empty arguments");
}
