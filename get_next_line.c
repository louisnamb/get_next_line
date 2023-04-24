/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:49:10 by lnambaji          #+#    #+#             */
/*   Updated: 2023/04/24 16:15:02 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "leak_detector_c.h"

static int read_error = 0;
int fake_read(int fd, char *buffer, int size)
{
	if (read_error)
	{
		read_error = 0;
		return (-1);
	}
	return (read(fd, buffer, size));
}

char *get_currline(int fd, char *buffer, char **nbuff, char *rval)
{
    int	  	next;
    int	  	bytes_read;
    char	*prev_buff;
	int	character;

    bytes_read = 0;
	next = 0;
	character = 1;
	while (ft_strchr(*nbuff, '\n') == NULL)
	{
		bytes_read = next;
		next = fake_read(fd, buffer, BUFFER_SIZE); //0x30	
		if (next > 0)
		{
			prev_buff = *nbuff; // *nbuff = 0x60
			buffer[next] = '\0';
			*nbuff = ft_strjoin(prev_buff, buffer); //0x80
			free(prev_buff); // 0x60
		}
		else if (next <= -1)
		{
            return (NULL);
		}
        else
			break ;
	}
	// If we have a new line in the buffer:
	// set rval to evertthing before the newline, including the new line.
	if (ft_strchr(*nbuff, '\n'))
		rval = ft_substr(*nbuff, 0, ft_strchr(*nbuff, '\n') - *nbuff + 1); // rval 0xB0
	//else if (ft_strchr(*nbuff, '\0'))
//	{
	//	character = 0;
//		rval = ft_substr(*nbuff, 0, ft_strchr(*nbuff, '\0') - *nbuff + 1);
//	}
//	else if (next == -1)
//		return (NULL);
	else
	{
		if (bytes_read == 0)
		{
			rval = ft_strdup(*nbuff);
			return (rval);
		}
		else
			return (NULL);
	}
	prev_buff = *nbuff;
	*nbuff = ft_strchr(prev_buff, '\n') + 1;
	*nbuff = ft_strdup(*nbuff); // 0xE0
	free(prev_buff);
	prev_buff = NULL;
    return (rval);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	char		*rval = NULL;
	static char		*nbuff;
    size_t          j;

    j = 0;
	if (fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	while (j < BUFFER_SIZE + 1)
	{
		buffer[j] = 0;
		j++;
	}
	j = 0;
    if (nbuff == NULL)
    	nbuff = ft_strdup("");
    rval = get_currline(fd, buffer, &nbuff, rval);
    if (!rval)
	{
		free(nbuff);
		free(rval);
		rval = NULL;
		nbuff = NULL;
	    return (NULL);
	}
	free(buffer);
    buffer = NULL;
    return (rval);
}
#ifdef _MAIN_
int main()
{
	int fd;
	int	i;
	char *result;
	i = 1;
	fd = open("/Users/lnambaji/Documents/Cursus/get_next_line/example.txt", O_RDWR);
	if (fd == -1) {
		perror("Couldn't open the file. Try again.");
		return (0);
	}
	result = get_next_line(fd);
    printf("%d: %s\n", i, result);
	while (result)
    {
		result = get_next_line(fd); 
		printf("%d: %s\n", i, result);
		if (i == 1)
			read_error = 1;
		free (result);
	    i++;
    }
//	fd = open("/Users/lnambaji/Documents/Cursus/get_next_line/example.txt", O_RDWR);
    /*do
    {
	    result = get_next_line(fd);
		if (i == 1)
			read_error = 1;
		printf("%d: %s\n", i, result);
		free (result);
	    i++;
    } while (result);*/
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