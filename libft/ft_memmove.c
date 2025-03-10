/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:52:44 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/13 18:27:29 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*cdest;
	char	*csrc;

	i = 0;
	cdest = (char *)dst;
	csrc = (char *)src;
	if (dst == 0 && src == 0)
		return (dst);
	if (csrc < cdest && cdest < csrc + len)
		while (len-- > 0)
			cdest[len] = csrc[len];
	else
	{
		while (i < len)
		{
			cdest[i] = csrc[i];
			i++;
		}
	}
	return (dst);
}

// int main()
// {
//     char csrc[100] = "1234567890";
//     ft_memmove(csrc + 1, csrc, 10);    
//     printf("%s\n", csrc + 1);
//     return 0;
// }