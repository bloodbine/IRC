#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int	main(int argc, char **argv)
{
	if (argc != 3) {
		std::cerr << "[*ERROR]: ./IRC <port> <password>" << std::endl;
		return 1;
	}
	int	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		std::cerr << "[*ERROR]: Failed to create the socket!" << std::endl;
		return 1;
	}
	struct sockaddr_in serverAddr;
	std::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(std::atoi(argv[1]));
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
		std::cerr << "[*ERROR]: Failed to Bind!" << std::endl;
		return 1;
	}
	if (listen(serverSocket, 5) == -1) {
		std::cerr << "[*ERROR]: Listen failed!" << std::endl;
		return 1;
	}
	std::cout << "[*INFO]: Listening in port " << argv[1] << std::endl;
	while (true)
	{
		struct sockaddr_in	clientAddr;
		socklen_t			clientAddrLen = sizeof(clientAddr);



		
		int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
		if (clientSocket == -1) {
			std::cerr << "[*ERROR]: Accept failed!" << std::endl;
			close(serverSocket);
			return 1;
		}
		char buffer[1024];
		int	bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (bytesRead == -1) {
			std::cerr << "[*ERROR]: Receive failed!" << std::endl;
			close(clientSocket);
			// continue ;
		}
		std::cout << "[*CLIENT]: " << buffer << std::endl;
		close(clientSocket);
	}
	close(serverSocket);
}
