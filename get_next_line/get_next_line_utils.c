/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:02:25 by jolecomt          #+#    #+#             */
/*   Updated: 2024/03/09 23:57:10 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char	*str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	read_until_nl(t_data *datas, char **stock)
{
	datas->newline_index = get_newline_index(*stock);
	while (datas->newline_index == -1)
	{
		datas->buf_size = read(datas->fd, datas->buf, BUFFER_SIZE);
		if (datas->buf_size < 0)
		{
			free(datas->buf);
			free(*stock);
			*stock = NULL;
			return (0);
		}
		if (datas->buf_size == 0)
		{
			datas->tmp = *stock;
			*stock = NULL;
			free(datas->buf);
			return (1);
		}
		datas->buf[datas->buf_size] = '\0';
		*stock = concatenate_bufer(*stock, datas->buf);
		datas->newline_index = get_newline_index(*stock);
	}
	return (-1);
}
