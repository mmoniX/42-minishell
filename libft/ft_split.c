/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:53:24 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/13 18:50:21 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0' && str[i] != c)
		{
			count++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
	}
	return (count);
}

static int	word_len(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

static char	*word_mem(const char *str, char c)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	len = word_len(str, c);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (word == (void *)0)
		return (0);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	free_mem(char **str, int n)
{
	if (str == 0 || n < 0)
		return ;
	while (0 <= n)
	{
		free(str[n]);
		n--;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**result;

	i = 0;
	result = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (result == (void *)0)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			result[i] = word_mem(s, c);
			if (result[i] == (void *)0)
			{
				free_mem(result, i);
				return (0);
			}
			i++;
			s += word_len(s, c);
		}
	}
	result[i] = 0;
	return (result);
}

// int main(void)
// {
//     char *str = "   Hello   World 42 ";
//     char delimiter = ' ';
//     int count = word_count(str, delimiter);
//     char **res = ft_split(str, delimiter);
//     printf("Word count: %d\n", count);
//     for (int i = 0; res[i] != NULL; i++)
//     {
//         printf("Word %d: %s\n", i + 1, res[i]);
//     }
//     return 0;
// }