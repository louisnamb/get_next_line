/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:49:10 by lnambaji          #+#    #+#             */
/*   Updated: 2023/04/17 11:05:40 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
	bytes_read = read(fd, buffer, 39);
	while (buffer[i] && i <= sizeof(buffer))
	{
		++i;
		//printf("\t\ti: %d - %c\n", i, buffer[i]);
		if (buffer[i] == '\n')
			break;
	}
	new_buff = malloc(sizeof(char) * (i + 1));
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

Research areas:
- research fgets() function

Steps:
- Open the file and create a pointer to the first character of the file
- store buffer sized characters in the buffer variable, including the 
  newline character. 
- print up to newline characters. free whats left of the newline character
  and keep whats right of it
*/