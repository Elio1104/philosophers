/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 01:48:32 by alondot           #+#    #+#             */
/*   Updated: 2023/01/30 01:48:57 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	int		error;
	t_rules	rules;

	if (argc != 5 && argc != 6)
		return (error_manager(ERROR));
	error = init_all(&rules, argv);
	if (error != GOOD)
		return (error_manager(error));
	if (ft_philo(&rules))
		return (write_error("PHILO ERROR"));
	return (0);
}
