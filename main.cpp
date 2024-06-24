/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:53:44 by akeryan           #+#    #+#             */
/*   Updated: 2024/06/24 19:42:34 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

int main ()
{
	try {
		int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (socket_fd == -1) {
			throw (std::runtime_error("Error: failed to create a socket"));
		}
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(54000);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}