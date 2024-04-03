/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdragan <rdragan@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:11:54 by rdragan           #+#    #+#             */
/*   Updated: 2024/04/03 14:27:37 by rdragan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cstring>

int	convertPort(char* param)
{
	size_t	len = strlen(param);
	for (size_t i = 0; i < len; i++)
	{
		if (std::isdigit(param[i]) == false) return -1;
	}
	int port = std::atoi(param);
	if (port > 65535) return -1;
	return port;
}

int	main(int argc, char **argv)
{
	if (argc != 3) 
	{
		std::cerr << "[ERROR]: You must run ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	int	port = convertPort(argv[1]);
	if (port < 0) std::cerr << "[ERROR]: Invalid port" << std::endl;
	else std::cout << "> You want to run the server in port: " << argv[1] << std::endl;
	std::cout << "> The password for the server is: " << argv[2] << std::endl;
	return (0);
}