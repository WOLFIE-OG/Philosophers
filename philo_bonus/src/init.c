/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:06:41 by otodd             #+#    #+#             */
/*   Updated: 2024/04/22 18:41:04 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	parse_args(t_earth *earth, int arg_n, char **arg_a)
{
	if (arg_n == 1 || arg_n > 6)
		return (false);
	if (!ft_ischeck_str(arg_a[1], ft_isdigit))
		return (false);
	earth->nop = ft_atoi(arg_a[1]);
	if (!ft_ischeck_str(arg_a[2], ft_isdigit))
		return (false);
	earth->ttd = ft_atoi(arg_a[2]);
	if (!ft_ischeck_str(arg_a[3], ft_isdigit))
		return (false);
	earth->tte = ft_atoi(arg_a[3]);
	if (!ft_ischeck_str(arg_a[4], ft_isdigit))
		return (false);
	earth->tts = ft_atoi(arg_a[4]);
	if (arg_n == 6)
	{
		if (!ft_ischeck_str(arg_a[5], ft_isdigit))
			return (false);
		earth->notepme = ft_atoi(arg_a[5]);
	}
	else
		earth->notepme = -1;
	return (true);
}

static void	launch(t_earth *earth)
{
	int	i = -1;
	while (++i < earth->nop)
	{
		earth->souls[i]->pid = fork();
		if (earth->souls[i]->pid < 0)
			return ;
		if (earth->souls[i]->pid == 0)
			life(earth->souls[i]);
	}
}

static void	*death_trigger(void *i)
{
	t_earth	*earth;

	earth = (t_earth *)i;
	sem_wait(earth->death);
	sem_wait(earth->write_lock);
	earth->has_died = true;
	return (NULL);
}

int	main(int arg_n, char **arg_a)
{
	t_earth	*earth;

	earth = malloc(sizeof(t_earth));
	if (!parse_args(earth, arg_n, arg_a))
	{
		printf("Program usage: ");
		printf("./philo <number_of_philosophers> <time_to_die time_to_eat> ");
		printf("<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
		free(earth);
		return (EXIT_FAILURE);
	}
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_FORKS);
	earth->write_lock = sem_open(SEM_WRITE, O_CREAT, 0644, 1);
	earth->forks = sem_open(SEM_FORKS, O_CREAT, 0644, earth->nop);
	earth->death = sem_open(SEM_DEAD, O_CREAT, 0644, 0);
	earth->eaten = sem_open(SEM_FORKS, O_CREAT, 0644, earth->notepme * earth->nop);
	earth->is_parent = true;
	earth->has_died = false;
	earth->has_max_eat = false;
	invite_philos(earth);
	launch(earth);
	pthread_create(&earth->death_trigger, NULL, death_trigger, earth);
	while (!earth->has_died || !earth->has_max_eat)
		usleep(42);
	hell(earth);
	free(earth);
	return (EXIT_SUCCESS);
}
