/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 01:45:57 by alondot           #+#    #+#             */
/*   Updated: 2023/01/30 01:45:59 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	if (rules->all_ate == NO)
	{
		pthread_mutex_lock(&(rules->forks[philo->left_fork]));
		action(rules, philo->id, "has taken a fork");
		pthread_mutex_lock(&(rules->forks[philo->right_fork]));
		action(rules, philo->id, "has taken a fork");
		pthread_mutex_lock(&(rules->eating));
		action(rules, philo->id, "is eating");
		philo->last_meal = timestamp();
		pthread_mutex_unlock(&(rules->eating));
		sleep_time(rules->time_eat, rules);
		(philo->nb_meal)++;
		pthread_mutex_unlock(&(rules->forks[philo->left_fork]));
		pthread_mutex_unlock(&(rules->forks[philo->right_fork]));
	}
}

void	*philo_thread(void *philosopher)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(100);
	while (rules->status == ALIVE)
	{
		eating(philo);
		if (rules->all_ate == YES)
			break ;
		action(rules, philo->id, "is sleeping");
		sleep_time(rules->time_sleep, rules);
		if (rules->all_ate == YES)
			break ;
		action(rules, philo->id, "is thinking");
	}
	return (NULL);
}

void	loop(t_rules *rules, t_philo *philo)
{
	int	i;

	while (rules->all_ate == NO)
	{
		i = -1;
		while (++i < rules->nb_philo && rules->status == ALIVE)
		{
			pthread_mutex_lock(&(rules->eating));
			if (time_diff(philo[i].last_meal, timestamp()) > rules->time_death)
			{
				action(rules, i, "died");
				rules->status = DEAD;
			}
			pthread_mutex_unlock(&(rules->eating));
			usleep(100);
		}
		if (rules->status == DEAD)
			break ;
		i = 0;
		while (rules->nb_eat != -1 && i < rules->nb_philo
			&& philo[i].nb_meal >= rules->nb_eat)
			i++;
		if (i == rules->nb_philo)
			rules->all_ate = YES;
	}
}

void	exit_philo(t_rules *rules, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
	pthread_mutex_destroy(&(rules->eating));
}

int	ft_philo(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = rules->philo;
	rules->t0 = timestamp();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id),
				NULL, philo_thread, &(philo[i])))
			return (ERROR);
		philo[i].last_meal = timestamp();
		i++;
	}
	loop(rules, rules->philo);
	exit_philo(rules, philo);
	return (GOOD);
}
