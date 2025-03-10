/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:05:23 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/13 18:23:41 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = (char *)s;
	while (i < n)
	{
		temp[i] = 0;
		i++;
	}
}

// int main(void)
// {
//     char str[] = "42 school";
//     ft_bzero(str+2, 4);
//     printf("%s", str);
//     return 0;
// }