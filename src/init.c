/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:06:41 by otodd             #+#    #+#             */
/*   Updated: 2024/03/21 19:04:26 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


static void	new_sleep(unsigned long duration)
{
	unsigned long	start;

	start = get_current_time();
	while (1)
	{
		if (get_current_time() - start >= duration)
			break ;
		usleep(100);
	}
}

static void	eating(t_carbon *carbon)
{
	t_earth *const	earth = (t_earth *)carbon->earth;

	pthread_mutex_lock(&carbon->left_fork);
	l_taken_fork(carbon);
	pthread_mutex_lock(&carbon->right_fork);
	l_taken_fork(carbon);
	l_is_eating(carbon);
	pthread_mutex_lock(&carbon->soul_lock);
	carbon->meals_eaten++;
	pthread_mutex_unlock(&carbon->soul_lock);
	new_sleep(earth->tte);
	pthread_mutex_unlock(&carbon->left_fork);
	pthread_mutex_unlock(&carbon->right_fork);
}

static void	sleeping(t_carbon *carbon)
{
	t_earth *const	earth = (t_earth *)carbon->earth;

	l_is_sleeping(carbon);
	new_sleep(earth->tts);
}

static void	*life(void *i)
{
	t_carbon *carbon;
	t_earth *earth;

	carbon = (t_carbon *)i;
	earth = (t_earth *)carbon->earth;
	while (1)
	{
		eating(carbon);
		sleeping(carbon);
		l_is_thinking(carbon);
		pthread_mutex_lock(&earth->done_lock);
		if (earth->done)
		{
			pthread_mutex_unlock(&earth->done_lock);
			break;
		}
		pthread_mutex_unlock(&earth->done_lock);
	}
	return (NULL);
}


static void	parse_args(t_earth *earth, int arg_n, char **arg_a)
{
	earth->nop = ft_atoi(arg_a[1]);
	earth->ttd = ft_atoi(arg_a[2]);
	earth->tte = ft_atoi(arg_a[3]);
	earth->tts = ft_atoi(arg_a[4]);
	if (arg_n == 5)
		earth->notepme = ft_atoi(arg_a[5]);
	else
		earth->notepme = -1;
}

static bool	set_table(t_earth *earth)
{
	int	i;

	i = -1;
	earth->forks = malloc(sizeof(pthread_mutex_t) * earth->nop);
	while (++i < earth->nop)
		if (pthread_mutex_init(&earth->forks[i], NULL))
			return (false);
	return (true);
}

// static size_t	left(t_carbon *carbon)
// {
// 	t_earth		*earth = (t_earth *)carbon->earth;
// 
// 	return (carbon->id - 1 + earth->nop) % earth->nop;
// }

static void	invite_philos(t_earth *earth)
{
	int		i;

	i = -1;
	earth->souls = malloc(sizeof(t_carbon) * earth->nop);
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

	earth->big_bang = get_current_time();
	i = -1;
	while (++i < earth->nop)
		pthread_create(&earth->souls[i].thread, 
			NULL, life, &earth->souls[i]);
}

static bool	create_locks(t_earth *earth)
{
	if(pthread_mutex_init(&earth->lock, NULL))
		return (false);
	if(pthread_mutex_init(&earth->done_lock, NULL))
		return (false);
	if(pthread_mutex_init(&earth->write_lock, NULL))
		return (false);
	if (!set_table(earth))
		return (false);
	return (true);
}

int	main(int arg_n, char **arg_a)
{
	t_earth	earth;
	int		i;
	
	if (arg_n < 4)
		return (EXIT_FAILURE);
	earth.counter = 0;
	earth.done = false;
	parse_args(&earth, arg_n, arg_a);
	if (!create_locks(&earth))
		return (EXIT_FAILURE);
	invite_philos(&earth);
	start_life(&earth);
	while (1)
	{
		pthread_mutex_lock(&earth.done_lock);
		if (earth.done)
		{
			pthread_mutex_unlock(&earth.done_lock);
			break;
		}
		pthread_mutex_unlock(&earth.done_lock);
	}
	i = -1;
	while (++i < earth.nop)
		pthread_join(earth.souls[i].thread, NULL);
	i = -1;
	free(earth.souls);
	free(earth.forks);
	// pthread_mutex_destroy(&earth->lock);
	return (EXIT_SUCCESS);
}
