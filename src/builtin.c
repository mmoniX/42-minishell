/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:58:45 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/14 13:20:45 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 1;
	
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		n = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (n)
		printf("\n");
	return (0);
}

