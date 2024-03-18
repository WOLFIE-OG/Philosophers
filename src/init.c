/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:06:41 by otodd             #+#    #+#             */
/*   Updated: 2024/03/18 17:34:29 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int arg_n, char **arg_a)
{
	(void)arg_n;
	(void)arg_a;
	l_taken_fork("test");
	l_is_eating("test");
	l_is_sleeping("test");
	l_is_thinking("test");
	l_has_died("test");
	return (0);
}
