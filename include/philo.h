/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:05:37 by otodd             #+#    #+#             */
/*   Updated: 2024/03/18 18:23:53 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "colour_codes.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_carbon
{
	int		id;
	int		meals_eaten;
	bool	is_dead;
	int		nop;
	int		ttd;
	int		tte;
	int		tts;
}	t_carbon;

typedef struct s_earth
{
	t_carbon	**souls;
	int			nop;
	int			ttd;
	int			tte;
	int			tts;
	int			notepme;
}	t_earth;

unsigned long	get_current_time(void);
void			l_taken_fork(char *tmp);
void			l_is_eating(char *tmp);
void			l_is_sleeping(char *tmp);
void			l_is_thinking(char *tmp);
void			l_has_died(char *tmp);
int				ft_atoi(const char *nptr);
#endif