/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:37:20 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/08 12:19:59 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

long int	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long int	ft_get_ms(t_philo *philo)
{
	return (ft_get_time() - philo->table->time);
}

void	ft_sleep(long int time_to_stop)
{
	long int	delay;

	while (1)
	{
		delay = time_to_stop - ft_get_time();
		if (delay <= 0)
			break ;
		usleep(50);
	}
}

int	ft_check_minimum_value(char **argv)
{
	if (ft_atoi(argv[1]) == 0)
	{
		printf("You need at least 1 philosopher\n");
		return (1);
	}
	if (argv[5] && ft_atoi(argv[5]) == 0)
	{
		printf("You need at least 1 meal to eat\n");
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				ret;
	int				sign;

	i = 0;
	sign = 1;
	ret = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		ret = (str[i++] - '0') + (ret * 10);
	if (sign == 1)
		return (ret);
	return (ret * sign);
}
