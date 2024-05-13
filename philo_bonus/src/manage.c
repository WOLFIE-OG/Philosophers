/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:39:26 by otodd             #+#    #+#             */
/*   Updated: 2024/05/08 15:04:04 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_init_philos(t_ctx *ctx)
{
	int		i;

	i = -1;
	ctx->philos = malloc(sizeof(t_philo) * ctx->nop);
	while (++i < ctx->nop)
	{
		ctx->philos[i].id = i;
		ctx->philos[i].meals_eaten = 0;
		ctx->philos[i].ctx = ctx;
		ctx->philos[i].max_ate = false;
		ctx->philos[i].last_ate = 0;
	}
}

void	ft_init_semaphores(t_ctx *ctx)
{
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_STOP);
	ctx->write_lock = sem_open(SEM_WRITE, O_CREAT, 0644, 1);
	ctx->forks = sem_open(SEM_FORKS, O_CREAT, 0644, ctx->nop);
	ctx->stop = sem_open(SEM_STOP, O_CREAT, 0644, 0);
}

void	ft_exit(t_ctx *ctx)
{
	int		i;

	i = -1;
	while (++i < ctx->nop)
		kill(ctx->philos[i].pid, SIGKILL);
}

void	ft_launch(t_ctx *ctx)
{
	int	i;

	ctx->start_time = ft_get_current_time();
	i = -1;
	while (++i < ctx->nop)
	{
		ctx->philos[i].pid = fork();
		if (ctx->philos[i].pid < 0)
			return ;
		if (ctx->philos[i].pid == 0)
			ft_routine(&ctx->philos[i]);
	}
}

long	ft_get_current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
