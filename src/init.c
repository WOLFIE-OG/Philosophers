/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:06:41 by otodd             #+#    #+#             */
/*   Updated: 2024/03/25 19:26:09 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	slumber(unsigned long time, t_earth *earth)
{
	unsigned long	then;

	then = get_current_time();
	while (!earth->solar_flare)
	{
		if ((get_current_time() - then) >= time)
			break ;
		usleep(50);
	}
}

static void	eating(t_carbon *carbon)
{
	t_earth *const	earth = (t_earth *)carbon->earth;

	pthread_mutex_lock(&carbon->left_fork);
	carbon->state = GOT_FIRST_FORK;
	l_taken_fork(carbon);
	pthread_mutex_lock(&carbon->right_fork);
	carbon->state = GOT_SECOND_FORK;
	l_taken_fork(carbon);
	l_is_eating(carbon);
	carbon->state = EATING;
	carbon->meals_eaten++;
	carbon->last_ate = get_current_time();
	slumber(earth->tte, earth);
	pthread_mutex_unlock(&carbon->left_fork);
	pthread_mutex_unlock(&carbon->right_fork);
}

static void	*life(void *i)
{
	t_carbon *carbon;
	t_earth *earth;

	carbon = (t_carbon *)i;
	earth = (t_earth *)carbon->earth;
	while (!earth->solar_flare)
	{
		eating(carbon);
		l_is_sleeping(carbon);
		carbon->state = SLEEPING;
		slumber(earth->tts, earth);
		l_is_thinking(carbon);
		carbon->state = THINKING;
	}
	return (NULL);
}


static void	parse_args(t_earth *earth, int arg_n, char **arg_a)
{
	earth->nop = ft_atoi(arg_a[1]);
	earth->ttd = ft_atoi(arg_a[2]);
	earth->tte = ft_atoi(arg_a[3]);
	earth->tts = ft_atoi(arg_a[4]);
	if (arg_n == 6)
		earth->notepme = ft_atoi(arg_a[5]);
	else
		earth->notepme = -1;
}

static bool	set_table(t_earth *earth)
{
	int	i;

	i = -1;
	while (++i < earth->nop)
		if (pthread_mutex_init(&earth->forks[i], NULL))
			return (false);
	return (true);
}

static void	invite_philos(t_earth *earth)
{
	int		i;

	i = -1;
	while (++i < earth->nop)
	{
		earth->souls[i].id = i;
		earth->souls[i].meals_eaten = 0;
		earth->souls[i].state = NONE;
		earth->souls[i].earth = earth;
		earth->souls[i].left_fork = earth->forks[i];
		earth->souls[i].right_fork = earth->forks[(i + 1) % earth->nop];
	}
}

static void	start_life(t_earth *earth)
{
	int	i;

	i = -1;
	while (++i < earth->nop)
	{
		earth->souls[i].last_ate = get_current_time();
		pthread_create(&earth->souls[i].thread, 
			NULL, life, &earth->souls[i]);
	}
	
}

static bool	create_locks(t_earth *earth)
{
	if(pthread_mutex_init(&earth->write_lock, NULL))
		return (false);
	if (!set_table(earth))
		return (false);
	return (true);
}

static int	get_current_total_eaten_meals(t_earth *earth)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < earth->nop)
		count += earth->souls[i].meals_eaten;
	return (count);
}

static void	hell(t_earth *earth)
{
	int	i;

	i = -1;
	if (earth->nop >= 1)
		while (++i < earth->nop)
			pthread_join(earth->souls[i].thread, NULL);
	else
		pthread_detach(earth->souls[0].thread);
	pthread_mutex_destroy(&earth->write_lock);
}

int	main(int arg_n, char **arg_a)
{
	t_earth	earth;
	int		i;
	
	i = 0;
	if (arg_n < 4)
		return (EXIT_FAILURE);
	earth.solar_flare = false;
	parse_args(&earth, arg_n, arg_a);
	if (!create_locks(&earth))
		return (EXIT_FAILURE);
	invite_philos(&earth);
	start_life(&earth);
	while (!earth.solar_flare)
	{
		if (get_current_total_eaten_meals(&earth) == earth.notepme)
			earth.solar_flare = true;
		if ((int)(get_current_time() - earth.souls[i].last_ate) >= earth.ttd)
		{
			earth.solar_flare = true;
			l_has_died(&earth.souls[i]);
			earth.souls[i].state = DEAD;
		}
		i = (i + 1) % earth.nop;
		usleep(100);
	}
	hell(&earth);
	return (EXIT_SUCCESS);
}
