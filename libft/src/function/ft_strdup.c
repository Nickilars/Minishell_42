/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:21:49 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/17 13:18:10 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strdup(const char *s1, t_dlist **trash)
{
	int		i;
	int		len;
	char	*s_cpy;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	s_cpy = my_malloc(len + 1, sizeof(char), trash);
	if (!s_cpy)
		return (0);
	while (i <= len && s1[i])
	{
		s_cpy[i] = s1[i];
		i++;
	}
	s_cpy[i] = 0;
	return (s_cpy);
}
