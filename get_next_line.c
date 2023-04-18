/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:49:10 by lnambaji          #+#    #+#             */
/*   Updated: 2023/04/18 16:21:16 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	unsigned long			bytes_read;
	static char		*rval = NULL;
	static char		*nbuff;
	unsigned int	i;
	char			*prev_buff;
	unsigned long	next;

	if (rval)
	{
		free(rval);
		rval = NULL;
	}
	if (fd < 0)
		return (NULL);
	i = 0;
	bytes_read = 0;
	while (i < (BUFFER_SIZE + 1))
		buffer[i++] = 0;
	if (nbuff == NULL)
		nbuff = ft_strdup("");
	while (ft_strchr(buffer, '\n') == NULL)
	{

		next = read(fd, buffer, BUFFER_SIZE);
		
		if (next != 0)
		{
			bytes_read = next;
			prev_buff = nbuff;
			nbuff = ft_strjoin(nbuff, buffer);
			free(prev_buff);
		}
		else
			break ;

	}
	if (next != 0)
		rval = ft_substr(nbuff, 0, ft_strchr(nbuff, '\n') - nbuff + 1);
	else
		rval = ft_substr(nbuff, 0, ft_strchr(nbuff, '\0') - nbuff);

	if (next == 0)
	{
		free(nbuff);
	}
	else
	{
		prev_buff = nbuff;
		nbuff = ft_strchr(nbuff, '\n') + 1;
		nbuff = ft_strdup(nbuff + 1);
		free(prev_buff);
	}
	if (bytes_read == 0)
		return (NULL);

    return (rval);
}
#ifdef _MAIN_
int main()
{
	int fd;
	int	i;
	char *result;
	i = 0;
	fd = open("/Users/lnambaji/Documents/Cursus/get_next_line/example.txt", O_RDWR);
	if (fd == -1) {
		perror("Couldn't open the file. Try again.");
		return (0);
	}
	result = get_next_line(fd);
	while (result)
	{
		printf("%s", result);
		result = get_next_line(fd);
	}
	return (0);
}
#endif
/*
Get_next_line notes:
- use open and closefp function
- define BUFFER_SIZE in your header file
- copies buffer sized bytes but prints until the newline 
character and stops
- next time you run get_next_line, its going to start after 
the newline character
	hence the static variable
- for it to print the rest (until the newline character)

Steps: 
- everytime the gnl function is called, we read buffer_size bytes into buffer.
- then we call the strjoin functoin to add buffer to the end of newbuff. free
	buffer/
- this will loop while we havent found a newline character in newbuff. this is
	done using the strchr functoin from libft
- when we do encounter a newline in newbuff, return newbuff

notes:
- newbuff is a static char pointer. points to the s
- make a functoin that frees whats left of the newline character, copies whats
	right of the newline character to the left.
*/