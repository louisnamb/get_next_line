/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:49:10 by lnambaji          #+#    #+#             */
/*   Updated: 2023/04/27 14:19:30 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *unique(char **data, char	*new)
{
	free(*data);
	*data = NULL;
	return (new);
}

char *get_currline(int fd, char *buffer, char **nbuff, char *rval)
{
    int	  	next;
	int	character;

	next = 69;
	character = 1;
	while (next != 0)
	{
		next = read(fd, buffer, BUFFER_SIZE); //0x30	
		if (next <= -1 || (next == 0 && *nbuff[0] == '\0'))
		    return (unique(nbuff, NULL));
		else if (next == 0)
			break ;
		buffer[next] = '\0';
		*nbuff = unique(nbuff, ft_strjoin(*nbuff, buffer)); //0x80
        if (ft_strchr(*nbuff, '\n'))
			break ;
	}
	if (ft_strchr(*nbuff, '\n'))
		rval = ft_substr(*nbuff, 0, ft_strchr(*nbuff, '\n') - *nbuff + 1); // rval 0xB0
	else if (ft_strchr(*nbuff, '\0'))//byte s_read == 0 && sizeof(*nbuff) > 4 && !ft_strchr(*nbuff, '\n'))
	{
		rval = ft_strdup(*nbuff);
		character = 0;
	}
	else
		return (NULL);
	if (character) // moves nbuff on if we're not on the last line
		*nbuff = unique(nbuff, ft_strdup(ft_strchr(*nbuff, '\n') + 1)); // 0xE0
	else
		*nbuff = unique(nbuff, ft_strdup(ft_strchr(*nbuff, '\0'))); // 0xE0
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
		return (unique(&nbuff, NULL));
	buffer = (char *)malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	while (j < BUFFER_SIZE + 1)
		buffer[j++] = 0;
    if (nbuff == NULL)
    	nbuff = ft_strdup("");
    rval = get_currline(fd, buffer, &nbuff, rval);
	free(buffer);
    buffer = NULL;
    if (!rval)
	{
		unique(&nbuff, NULL);
		unique(&rval, NULL);
	    return (NULL);
	}
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