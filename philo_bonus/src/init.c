/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:06:41 by otodd             #+#    #+#             */
/*   Updated: 2024/04/26 17:27:17 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static bool	ft_parse_args(t_ctx *ctx, int arg_n, char **arg_a)
{
	if (arg_n == 1 || arg_n > 6)
		return (false);
	if (!ft_ischeck_str(arg_a[1], ft_isdigit))
		return (false);
	ctx->nop = ft_atoi(arg_a[1]);
	if (!ft_ischeck_str(arg_a[2], ft_isdigit))
		return (false);
	ctx->ttd = ft_atoi(arg_a[2]);
	if (!ft_ischeck_str(arg_a[3], ft_isdigit))
		return (false);
	ctx->tte = ft_atoi(arg_a[3]);
	if (!ft_ischeck_str(arg_a[4], ft_isdigit))
		return (false);
	ctx->tts = ft_atoi(arg_a[4]);
	if (arg_n == 6)
	{
		if (!ft_ischeck_str(arg_a[5], ft_isdigit))
			return (false);
		ctx->notepme = ft_atoi(arg_a[5]);
	}
	else
		ctx->notepme = -1;
	return (true);
}

void	ft_wait_process(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->nop)
	{
		waitpid(ctx->philos[i].pid, NULL, 0);
		i++;
	}
}

void	*ft_death_trigger(void *c)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)c;
	sem_wait(ctx->stop);
	ft_exit(ctx);
	ctx->death = true;
	return (NULL);
}

int	main(int arg_n, char **arg_a)
{
	t_ctx	ctx;

	if (!ft_parse_args(&ctx, arg_n, arg_a))
	{
		printf("Program usage: ");
		printf("./philo <number_of_philosophers> <time_to_die time_to_eat> ");
		printf("<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	ctx.death = false;
	ft_init_semaphores(&ctx);
	ft_init_philos(&ctx);
	ft_launch(&ctx);
	ft_wait_process(&ctx);
	if (!ctx.death)
		ft_exit(&ctx);
	pthread_join(ctx.death_trigger, NULL);
	free(ctx.philos);
	return (EXIT_SUCCESS);
}
