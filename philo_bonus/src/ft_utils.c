/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:17:43 by otodd             #+#    #+#             */
/*   Updated: 2024/04/23 17:17:56 by otodd            ###   ########.fr       */
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
	while ((*c == ' ') || (*c == '\t')
		|| (*c == '\v') || (*c == '\r') || (*c == '\n') || (*c == '\f'))
		c++;
	if (*c == '+' || *c == '-')
	{
		if (*c == '-')
			operation *= -1;
		c++;
	}
	while (*c >= '0' && *c <= '9')
		value = (value * 10) + (*c++ - '0');
	return (value * operation);
}

int	ft_ischeck_str(char *str, int (*f)(int))
{
	while (*str)
		if (!f(*str++))
			return (0);
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	return (0);
}
