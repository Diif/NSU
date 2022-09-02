#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX_LEN 256
char buf[MAX_LEN];

int main() {
  int server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
  if (server_socket < 0) {
    printf("Socket error\n");
    exit(EXIT_FAILURE);
  }

  struct sockaddr server_addr;
  server_addr.sa_family = AF_UNIX;
  strcpy(server_addr.sa_data, "myserver1");
  unsigned int addr_len =
      sizeof(server_addr.sa_family) + strlen(server_addr.sa_data) + 1;

  if (unlink("myserver1") < 0) {
    printf("Unlink error\n");
    exit(EXIT_FAILURE);
  }
  if (bind(server_socket, &server_addr, addr_len) < 0) {
    printf("Binding error\n");
    exit(EXIT_FAILURE);
  }

  if (listen(server_socket, 1) < 0) {
    printf("Can't listen...\n");
    exit(EXIT_FAILURE);
  }
  int client_socket = accept(server_socket, NULL, NULL);

  while (1) {
    int n = recv(client_socket, buf, MAX_LEN, 0);
    if (n < 0) {
      printf("Message error\n");
      perror(NULL);
      exit(EXIT_FAILURE);
    }
    if (n == 0) {
      printf("%s", "Closing...\n");
      break;
    }
    printf("%s\n", buf);
    bzero(buf, MAX_LEN);
  }
  close(server_socket);
  unlink("myserver1");
  return 0;
}
