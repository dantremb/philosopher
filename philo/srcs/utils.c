/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:37:20 by dantremb          #+#    #+#             */
/*   Updated: 2023/01/15 20:46:16 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

long int	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long int	ft_get_ms(t_philo *p)
{
	return (ft_get_time() - p->t->time);
}

void	ft_sleep(long int time_to_stop)
{
	long int	delay;

	while (1)
	{
		delay = time_to_stop - ft_get_time();
		if (delay <= 0)
			break ;
		usleep(500);
	}
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
