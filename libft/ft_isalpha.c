/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:49:27 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/09 20:37:51 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

// int main(void)
// {
//     char *str = "GSHAGE";
//     int n = ft_isalpha(str);
//     n = n + '0';
//     write (1, &n, 1);
//     write (1, "\n", 1);
//     return 0;
// }