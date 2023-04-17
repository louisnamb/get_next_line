/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:49:10 by lnambaji          #+#    #+#             */
/*   Updated: 2023/04/17 12:28:41 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*ft_strchr(const char *s, int c)
{
	const char	*str;

	str = s;
	while (*str && str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

int get_next_line(int fd)
{
    char			buffer[1024];
    size_t			bytes_read;
	static int		i;
	char			*new_buff;
	static int		j;

    if (fd == -1) {
		perror("Couldn't open the file. Try again.");
		return (1);
    }
	i = 0;
	while (buffer[i] && i <= sizeof(buffer) && ft_strchr(buffer, '\n'))
	{
		++i;
		bytes_read = read(fd, buffer, sizeof(buffer));
		new_buff = malloc(sizeof(char) * (i + 1));
		//printf("\t\ti: %d - %c\n", i, buffer[i]);
		if (buffer[i] == '\n')
			break;
	}
    bytes_read = read(fd, new_buff, sizeof(new_buff));
	//new_buff[sizeof(buffer)] = '\0';
	printf("buffer: %s new_buff: %s\n", buffer, new_buff);
	/*while (buffer[i] != '\0' && i < sizeof(buffer))
	{
		new_buff[i] = buffer[i];
		i++;
	}*/
	j = 0;
	//printf("bytes allocated: %zu str:\n %s\n", sizeof(buffer), new_buff);
	printf("\n\n");
	free(new_buff);
	close(fd); // close file when done
    return 0;
}

int main()
{
	int fd;
	fd = open("/Users/lnambaji/Documents/Cursus/get_next_line/example.txt", O_RDONLY);
	get_next_line(fd);
	return (0);
}

/*
Get_next_line notes:
- use open and closefp function
- define BUFFER_SIZE in your header file
- copies buffer sized bytes but prints until the newline character and stops
- next time you run get_next_line, its going to start after the newline character
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