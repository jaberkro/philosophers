/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 13:34:16 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/25 17:38:26 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned long	atoul(const char *input)
{
	unsigned long	number;
	unsigned long	i;

	number = 0;
	i = 0;
	while (input[i] >= '0' && input[i] <= '9')
	{
		number = number * 10 + input[i] - '0';
		i++;
	}
	return (number);
}

static int	check_if_digit(char *to_check)
{
	int	i;

	i = 0;
	if (!to_check)
	{
		printf("invalid input\n");
		return (0);
	}
	while (to_check[i])
	{
		if (to_check[i] < '0' || to_check[i] > '9')
		{
			printf("%s: not a whole number\n", to_check);
			return (0);
		}
		i++;
	}
	return (1);
}

t_data	parsing(int argc, char **argv)
{
	int				i;
	unsigned long	number;
	t_data			data;

	i = 1;
	data.error = 0;
	while (i < argc)
	{
		if (!check_if_digit(argv[i]))
			data.error = 1;
		number = atoul(argv[i]);
		data.inputs[i - 1] = number;
		i++;
	}
	if (argc == 5)
		data.inputs[4] = 0;
	return (data);
}
