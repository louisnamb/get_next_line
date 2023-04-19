/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:49:10 by lnambaji          #+#    #+#             */
/*   Updated: 2023/04/19 15:19:22 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*get_next_line(int fd)
{
	char			*buffer;
	char			*nbuff;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (nbuff == NULL)
		nbuff = ft_strdup("");
	line = currline(fd, buffer, nbuff);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (line);
	nbuff = gnl(nbuff)
	return (nbuff);
}

static char *currline(int fd, char *buffer)
{
	unsigned long	next;
	char		*rval = NULL;
	unsigned long	bytes_read;

	bytes_read = 0;
	while (ft_strchr(buffer, '\n') == NULL)
	{
		next = read(fd, buffer, BUFFER_SIZE);
		if (next == -1)
			return (NULL);
		else if (next == 0)
			break ;
		bytes_read = next;
		rval[bytes_read] = '\0';
		prev_buff = nbuff;
		nbuff = ft_strjoin(prev_buff, buffer);
		frree(prev_buff);
	}
	return (nbuff);
}

static char	*gnl(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[0] == '\0')
		return (NULL);

	if (next != 0)
	{
		rval = ft_substr(nbuff, 0, ft_strchr(nbuff, '\n') - nbuff + 1);
	//	prev_buff = nbuff;
		nbuff = ft_strchr(nbuff, '\n') + 1;
	//	nbuff = ft_strdup(nbuff + 1);
	//	frree(prev_buff);
	}
	else
	{

		rval = ft_substr(nbuff, 0, ft_strchr(nbuff, '\0') - nbuff);
		free(nbuff); 
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
- then we call the strjoin functoin to add buffer to the end of newbuff. frree
	buffer/
- this will loop while we havent found a newline character in newbuff. this is
	done using the strchr functoin from libft
- when we do encounter a newline in newbuff, return newbuff

notes:
- newbuff is a static char pointer. points to the s
- make a functoin that frrees whats left of the newline character, copies whats
	right of the newline character to the left.
*/
