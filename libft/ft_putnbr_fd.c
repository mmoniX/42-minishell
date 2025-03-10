/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:39:31 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/12 11:55:59 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
			write (fd, &"-2147483648", 11);
		else
		{
			n = -n;
			write (fd, "-", 1);
			ft_putnbr_fd (n, fd);
		}
	}
	else
	{
		if (n > 9)
			ft_putnbr_fd (n / 10, fd);
		write (fd, &"0123456789"[n % 10], 1);
	}
}

// int main()
// {
// 	int n = 2147483647;
// 	ft_putnbr_fd(n, 0);
// 	return (0);
// }