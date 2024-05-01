/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:25:00 by otodd             #+#    #+#             */
/*   Updated: 2024/05/01 11:47:22 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_get_total_eaten_meals(t_ctx *ctx)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < ctx->nop)
		count += ctx->philos[i]->meals_eaten;
	return (count);
}

int	ft_get_total_philo_ready_count(t_ctx *ctx)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < ctx->nop)
		if (ctx->philos[i]->is_ready)
			count++;
	return (count);
}

bool	ft_are_philos_finished(t_ctx *ctx)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < ctx->nop)
		if (ctx->philos[i]->is_finished)
			count++;
	if (count == ctx->nop)
		return (true);
	else
		return (false);
}
