/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_compare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:31:34 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/20 12:32:43 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	smart_compare(char *str1, char *str2)
{
	int		len;

	len = len_compare(str1, str2);
	return (ft_strncmp(str1, str2, len));
}
