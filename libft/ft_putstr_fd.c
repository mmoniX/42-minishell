/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:19:43 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/12 12:16:30 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	if (fd < 0)
		return ;
	write (fd, s, len);
}

// int main()
// {
// 	char str[] = "2147483647";
// 	ft_putstr_fd(str, 1);
// 	return (0);
// }