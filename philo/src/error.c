/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 11:12:41 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/12 16:14:24 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static int	ft_is_digit(char c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

static int	check_is_valid(char *to_check)
{
	int	i;

	i = 0;
	while (to_check[i])
	{
		if ((!ft_is_digit(to_check[i]) && (i != 0 || to_check[i] != '+')) || \
		atoul(to_check) == 0)
		{
			printf("Error: %s: invalid input\n", to_check);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_argument_count(int argc)
{
	if (argc < 5)
		return (print_return("Error: too few arguments", 0));
	if (argc > 6)
		return (print_return("Error: too many arguments", 0));
	return (1);
}

int	error_check(int argc, char **argv)
{
	int	i;

	i = 1;
	if (!check_argument_count(argc))
		return (0);
	while (i < argc)
	{
		if (!argv[i][0])
			return (print_return("Error: empty argument", 0));
		if (!check_is_valid(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
