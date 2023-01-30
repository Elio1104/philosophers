/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 01:51:23 by alondot           #+#    #+#             */
/*   Updated: 2023/01/30 01:51:33 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long t0, long long t1)
{
	return (t1 - t0);
}

void	sleep_time(long long sleeping_time, t_rules *rules)
{
	long long	i;

	i = timestamp();
	while (rules->status == ALIVE && rules->all_ate == NO)
	{
		if (time_diff(i, timestamp()) >= sleeping_time)
			break ;
		usleep(50);
	}
}

void	action(t_rules *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->writing));
	if (rules->status == ALIVE && rules->all_ate == NO)
	{
		printf("%lli ", timestamp() - rules->t0);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(rules->writing));
	return ;
}
