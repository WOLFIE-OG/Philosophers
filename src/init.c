/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:06:41 by otodd             #+#    #+#             */
/*   Updated: 2024/03/18 18:14:51 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int arg_n, char **arg_a)
{
	t_earth	*earth;

	if (arg_n < 4)
		return (EXIT_FAILURE);
	earth = malloc(sizeof(t_earth));
	if (!earth)
		return (EXIT_FAILURE);
	earth->nop = ft_atoi(arg_a[1]);
	earth->ttd = ft_atoi(arg_a[2]);
	earth->tte = ft_atoi(arg_a[3]);
	earth->tts = ft_atoi(arg_a[4]);
	earth->notepme = ft_atoi(arg_a[5]);
	free(earth);
	return (EXIT_SUCCESS);
}
