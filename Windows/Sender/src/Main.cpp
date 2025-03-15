#include "../include/Raw_Socket.h"


int main()
{
	std::string data = "Hello!";
	Raw_Socket rsocket(8, inet_addr("127.0.0.1"), data);
	rsocket.start();

	return 0;
}