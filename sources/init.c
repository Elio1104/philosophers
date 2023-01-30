/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 01:47:40 by alondot           #+#    #+#             */
/*   Updated: 2023/01/30 01:47:51 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_philosophers(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philo[i].id = i;
		rules->philo[i].nb_meal = 0;
		rules->philo[i].last_meal = 0;
		rules->philo[i].left_fork = i;
		rules->philo[i].right_fork = (i + 1) % rules->nb_philo;
		rules->philo[i].rules = rules;
		i++;
	}
}

int	init_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (ERROR);
		i++;
	}
	if (pthread_mutex_init(&(rules->writing), NULL))
		return (ERROR);
	if (pthread_mutex_init(&(rules->eating), NULL))
		return (ERROR);
	return (GOOD);
}

int	init_all(t_rules *rules, char **argv)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	rules->status = ALIVE;
	rules->all_ate = NO;
	if (rules->nb_philo < 2 || rules->time_death < 0 || rules->time_eat < 0
		|| rules->time_sleep < 0)
		return (ERROR);
	if (argv[5])
	{
		rules->nb_eat = ft_atoi(argv[5]);
		if (rules->nb_eat <= 0)
			return (ERROR);
	}
	else
		rules->nb_eat = -1;
	init_philosophers(rules);
	if (init_mutex(rules) == ERROR)
		return (ERROR_MUTEX);
	return (GOOD);
}
