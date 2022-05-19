#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX_LEN 256

char buf[MAX_LEN];

int main() {
  int client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
  if (client_socket < 0) {
    printf("Socket error\n");
    exit(EXIT_FAILURE);
  }

  int addr_len = sizeof(struct sockaddr);
  struct sockaddr server_addr;
  server_addr.sa_family = AF_UNIX;
  strcpy(server_addr.sa_data, "myserver1");
  if (connect(client_socket, &server_addr, addr_len) < 0) {
    printf("Connection error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    scanf("%255s", buf);
    int n = send(client_socket, buf, strlen(buf), 0);
    if (n < 0) {
      printf("Message error\n");
      exit(EXIT_FAILURE);
    }
  }
}
