/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:49:10 by lnambaji          #+#    #+#             */
/*   Updated: 2023/04/13 16:18:41 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


int main()
{
	char buffer[1024] = "When you invoke GCC, it normally does preprocessing, compilation, assembly and linking. The overall options allow you to stop this process at an intermediate stage. For example, the -c option says not to run the linker.Then the output consists of object files output by the assembler.";
	int fd = open("/Users/lnambaji/Documents/Cursus/get_next_line/example.txt", O_RDWR);
	write(1, &buffer, strlen(buffer));
	printf("fd: %d", fd);
	close(fd);
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
*/