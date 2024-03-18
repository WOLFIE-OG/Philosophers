/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minift.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:39:56 by otodd             #+#    #+#             */
/*   Updated: 2024/03/18 17:41:34 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int		value;
	int		operation;
	char	*c;

	c = (char *)nptr;
	operation = 1;
	value = 0;
	while ((c == ' ') || (c == '\t')
		|| (c == '\v') || (c == '\r') || (c == '\n') || (c == '\f'))
		c++;
	if (*c == '+' || *c == '-')
	{
		if (*c == '-')
			operation *= -1;
		c++;
	}
	while (c >= 48 && c <= 57)
		value = (value * 10) + (*c++ - '0');
	return (value * operation);
}
