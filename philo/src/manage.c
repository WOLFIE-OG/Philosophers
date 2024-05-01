/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:43:45 by otodd             #+#    #+#             */
/*   Updated: 2024/05/01 13:10:40 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_init_philos(t_ctx *ctx)
{
	int		i;

	ctx->philos = malloc(sizeof(t_philo) * ctx->nop);
	i = -1;
	while (++i < ctx->nop)
	{
		ctx->philos[i] = malloc(sizeof(t_philo));
		ctx->philos[i]->id = i;
		ctx->philos[i]->meals_eaten = 0;
		ctx->philos[i]->last_ate = 0;
		ctx->philos[i]->ctx = ctx;
		ctx->philos[i]->is_dead = false;
		ctx->philos[i]->is_finished = false;
		ctx->philos[i]->left_fork = &ctx->forks[i];
		ctx->philos[i]->right_fork = &ctx->forks[(i + 1) % ctx->nop];
	}
}

void	ft_init_mutexes(t_ctx *ctx)
{
	int	i;

	i = -1;
	pthread_mutex_init(&ctx->write_lock, NULL);
	ctx->forks = malloc(sizeof(pthread_mutex_t) * ctx->nop);
	while (++i < ctx->nop)
		pthread_mutex_init(&ctx->forks[i], NULL);
}

void	ft_exit(t_ctx *ctx)
{
	int	i;

	while (!ft_are_philos_finished(ctx))
		usleep(100);
	i = -1;
	while (++i < ctx->nop)
		pthread_join(ctx->philos[i]->thread, NULL);
	pthread_mutex_destroy(&ctx->write_lock);
	i = -1;
	while (++i < ctx->nop)
	{
		pthread_mutex_destroy(&ctx->forks[i]);
		free(ctx->philos[i]);
	}
	free(ctx->philos);
	free(ctx->forks);
}

void	ft_create_threads(t_ctx *ctx)
{
	int	i;

	ctx->start_time = ft_get_current_time();
	i = -1;
	while (++i < ctx->nop)
	{
		pthread_create(&ctx->philos[i]->thread,
			NULL, ft_routine, ctx->philos[i]);
		ctx->philos[i]->last_ate = ft_get_current_time();
	}
}
