/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:44:45 by mmonika           #+#    #+#             */
/*   Updated: 2024/11/05 15:48:00 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = (char *)b;
	while (i < len)
	{
		temp[i] = c;
		i++;
	}
	return (b);
}

// int main() 
// { 
// 	char str[] = "42 school"; 
// 	memset(str, 'o', 8); 
// 	printf("%s", str); 
// 	return 0; 
// }