#include <common.h>
#include <arpa/inet.h>
#include <UDP_handler.h>

int create_socket()
{
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_fd == -1)
	{
		perror("socket");
		_exit(2);
	}
	return sock_fd;
}

int bind_socket(int sock_fd, char *ip_addr, unsigned short port)
{
	struct sockaddr_in *addr = malloc(sizeof (struct sockaddr_in));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = inet_addr(ip_addr);
	addr->sin_port = htons(port);
	if (bind(sock_fd, (struct sockaddr *)addr, sizeof (struct sockaddr_in)))
	{
		perror("socket");
		_exit(2);
	}
	return 1;
}

int get_addr(struct sockaddr_in *addr, char **ip_addr, unsigned short *port)
{
	if (addr)
	{
		*ip_addr = inet_ntoa(addr->sin_addr);
		*port = ntohs(addr->sin_port);
		return 1;
	}
	return 0;
}

int set_addr(struct sockaddr_in *addr, char *ip_addr, unsigned short port)
{
	if (ip_addr && port)
	{
		((struct sockaddr_in *)addr)->sin_family = AF_INET;
		if ((((struct sockaddr_in *)addr)->sin_addr.s_addr = inet_addr(ip_addr)) == INADDR_NONE)
			return 0;
		((struct sockaddr_in *)addr)->sin_port = htons(port);
		return 1;
	}
	return 0;
}

int recv_packet(int sock_fd, void *buff, unsigned int bsize, struct sockaddr_in *addr)
{
	int tmp, size = sizeof (struct sockaddr_in);
	if ((tmp = recvfrom(sock_fd, buff, bsize, 0, (struct sockaddr *)addr, &size)) == -1)
		perror("recv");
	return tmp;
}

int send_packet(int sock_fd, void *buff, unsigned int bsize, struct sockaddr_in *addr)
{
	int tmp;
	if (tmp = sendto(sock_fd, buff, bsize, 0, (struct sockaddr *)addr, sizeof (struct sockaddr_in)) == -1)
		perror("send");
	return tmp;
}


