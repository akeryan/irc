/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:53:44 by akeryan           #+#    #+#             */
/*   Updated: 2024/06/25 14:33:15 by akeryan          ###   ########.fr       */
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
		// Create a socket
		int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (socket_fd == -1) {
			throw (std::runtime_error("Error: failed to create a socket"));
		}

		// Bind the socket to a IP/port
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(54000);
		if (inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr) == -1) {
			throw (std::runtime_error("Error: inet_pton() failed"));
		}
		if (bind(socket_fd, (sockaddr *)&hint, sizeof(hint)) == -1) {
			throw (std::runtime_error("Error: failed to bind to IP/port"));
		}

		// Mark the socket for listening
		if (listen(socket_fd, SOMAXCONN) == -1) {
			throw (std::runtime_error("Error: faled to establish listening: listen()"));
		}
		
		// Accept a call

	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}