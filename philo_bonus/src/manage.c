/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:39:26 by otodd             #+#    #+#             */
/*   Updated: 2024/04/23 17:23:20 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	}
}

void	ft_init_semaphores(t_ctx *ctx)
{
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DEAD);
	ctx->write_lock = sem_open(SEM_WRITE, O_CREAT, 0644, 1);
	ctx->forks = sem_open(SEM_FORKS, O_CREAT, 0644, ctx->nop);
	ctx->death = sem_open(SEM_DEAD, O_CREAT, 0644, 0);
}

void	ft_exit(t_ctx *ctx)
{
	int		i;

	i = -1;
	while (++i < ctx->nop)
		kill(ctx->philos[i].pid, SIGKILL);
	sem_close(ctx->death);
	sem_close(ctx->forks);
	sem_close(ctx->write_lock);
	free(ctx->philos);
}

void	ft_launch(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->nop)
	{
		ctx->philos[i].pid = fork();
		if (ctx->philos[i].pid < 0)
			return ;
		if (ctx->philos[i].pid == 0)
		{
			ft_routine(&ctx->philos[i]);
			exit(0);
		}
	}
}

unsigned long	ft_get_current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * (unsigned long)1000) + (t.tv_usec / 1000));
}
