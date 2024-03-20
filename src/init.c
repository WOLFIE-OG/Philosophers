/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:06:41 by otodd             #+#    #+#             */
/*   Updated: 2024/03/20 14:42:16 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*test_thread(void *i)
{
	t_carbon	*tmp = (t_carbon *)i;
	t_earth		*tmp2 = (t_earth *)tmp->earth;
	
	pthread_mutex_lock(&tmp2->lock);
	tmp2->counter++;
	printf("Thread [%d]: %d\n", tmp->id, tmp2->counter);
	pthread_mutex_unlock(&tmp2->lock);
	return (0);
}

int	main(int arg_n, char **arg_a)
{
	t_earth	*earth;
	int		i;
	
	i = 0;
	earth = malloc(sizeof(t_earth));
	if (arg_n < 4)
		return (EXIT_FAILURE);
	if (!earth)
		return (EXIT_FAILURE);
	earth->nop = ft_atoi(arg_a[1]);
	earth->ttd = ft_atoi(arg_a[2]);
	earth->tte = ft_atoi(arg_a[3]);
	earth->tts = ft_atoi(arg_a[4]);
	earth->notepme = ft_atoi(arg_a[5]);
	earth->souls = malloc(sizeof(t_carbon *) * earth->nop);
	earth->counter = 0;
	pthread_mutex_init(&earth->lock, NULL);
	while (++i < earth->nop)
	{
		earth->souls[i] = malloc(sizeof(t_carbon));
		earth->souls[i]->thread = malloc(sizeof(pthread_t));
		earth->souls[i]->id = i;
		earth->souls[i]->state = DEAD;
		earth->souls[i]->earth = earth;
		pthread_create(earth->souls[i]->thread, NULL, test_thread, earth->souls[i]);
	}
	i = 0;
	while (++i < earth->nop)
		pthread_join(*earth->souls[i]->thread, NULL);
	free(earth);
	pthread_mutex_destroy(&earth->lock);
	return (EXIT_SUCCESS);
}
