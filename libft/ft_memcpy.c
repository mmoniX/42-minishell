/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:20:39 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/13 18:24:58 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*cdest;
	char	*csrc;

	i = 0;
	cdest = (char *)dst;
	csrc = (char *)src;
	if (dst == 0 && src == 0)
		return (dst);
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dst);
}

// int main(void)
// {
//     char src[] = "42 school";
//     char dest[8];
//     ft_memcpy(dest, src, 5);
//     printf("%s", dest);
//     return 0;
// }