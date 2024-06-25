/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:53:44 by akeryan           #+#    #+#             */
/*   Updated: 2024/06/25 18:26:33 by akeryan          ###   ########.fr       */
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

		// Bind the ip address and port to a socket
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(54000);
		if (inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr) == -1) {
			throw (std::runtime_error("Error: inet_pton() failed"));
		}
		if (bind(socket_fd, (sockaddr *)&hint, sizeof(hint)) == -1) {
			throw (std::runtime_error("Error: failed to bind to IP/port"));
		}

		// Specify that the socket is for listening
		if (listen(socket_fd, SOMAXCONN) == -1) {
			throw (std::runtime_error("Error: faled to establish listening: listen()"));
		}
		
		// Wait for a connection
		sockaddr_in client;
		socklen_t clientSize = sizeof(client);

		int clientSocket = accept(socket_fd, (sockaddr *)&client, &clientSize);
		if (clientSocket == -1) {
			throw (std::runtime_error("Error: Problem with client connecting :accept()"));
		}

		char host[NI_MAXHOST]; // Client's remote name
		memset(host, 0, NI_MAXHOST);

		char service[NI_MAXSERV]; // Service (i.e. port) the client is connect on
		memset(service, 0, NI_MAXSERV);

		if (getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
			std::cout << host << " connected on port " << service << std::endl;
		} else {
			inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
			std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
		}
		
		// Close the listening socket
		if (close(socket_fd) == -1) {
			throw (std::runtime_error("Error: socket_fd failed to close: close()"));
		}
		// While receiving - display message, echo message
		char buf[4096];
		while (true) {
			// Clear the buffer
			memset(buf, 0, 4096);
			// Wait for message
			int bytesRecv = recv(clientSocket, buf, 4096, 0);
			if (bytesRecv == -1) {
				std::cerr << "Error: connection issue: recv()" << std::endl;
				break ;
			}
			if (bytesRecv == 0) {
				std::cout << "The client disconnected" << std::endl;
				break ;
			}
			// Display message
			std::cout << std::string(buf, 0, bytesRecv) << std::endl;
			// Resend message
			send(clientSocket, buf, bytesRecv + 1, 0);
		}
		// Close socket
		close(clientSocket);
		return 0;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}