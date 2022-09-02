#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_LEN 256
#define MAX_CONNECTIONS 1020

int kServSocket;
char buf[MAX_LEN];

void processConnection(struct pollfd* fd_array, nfds_t* arr_size) {
  if (*arr_size == MAX_CONNECTIONS) {
    (*arr_size)--;
    close(fd_array[*arr_size].fd);
  }
  int new_client = accept(fd_array[0].fd, NULL, NULL);
  if (new_client < 0) {
    fprintf(stderr, "Can't connect client.");
    exit(EXIT_FAILURE);
  }
  fd_array[*arr_size].fd = new_client;
  fd_array[*arr_size].events = POLLIN;
  (*arr_size)++;
}

void processReading(int socket) {
  int n = recv(socket, buf, MAX_LEN, 0);
  if (n < 0) {
    printf("Message error\n");
    perror(NULL);
    exit(EXIT_FAILURE);
  }
  if (n == 0) {
    return;
  }
  printf("%s\n", buf);
  bzero(buf, MAX_LEN);
}

void processDisconnection(struct pollfd* fd_array, nfds_t* arr_size,
                          int index) {
  close(fd_array[index].fd);
  printf("Socket %d disconection\n", fd_array[index].fd);
  fd_array[index].fd = -1;
}

void processInputEvent(struct pollfd* fd_array, nfds_t* arr_size, int socket) {
  if (socket == kServSocket) {
    processConnection(fd_array, arr_size);
  } else {
    processReading(socket);
  }
}

void checkForEvents(struct pollfd* fd_array, nfds_t* arr_size, int num_events) {
  int cur_socket_index = 0;
  while (num_events) {
    int revents = fd_array[cur_socket_index].revents;
    if (revents == 0) {
      cur_socket_index++;
      continue;
    }
    if (((revents & POLLHUP) == POLLHUP) || ((revents & POLLERR) == POLLERR) ||
        ((revents & POLLNVAL) == POLLNVAL)) {
      processDisconnection(fd_array, arr_size, cur_socket_index);
      cur_socket_index++;
      num_events--;
      continue;
    }
    if (((revents & POLLIN) == POLLIN)) {
      processInputEvent(fd_array, arr_size, fd_array[cur_socket_index].fd);
      cur_socket_index++;
      num_events--;
      continue;
    }
    fprintf(stderr, "Unexpected event");
    exit(EXIT_FAILURE);
  }
}

void serverJob() {
  struct pollfd* fd_array =
      (struct pollfd*)malloc(sizeof(struct pollfd) * MAX_CONNECTIONS);
  nfds_t arr_size = 1;
  fd_array[0].fd = kServSocket;
  fd_array[0].events = POLLIN;
  while (1) {
    int num_events = poll(fd_array, arr_size, -1);
    if (num_events <= 0) {
      fprintf(stderr, "Poll error\n");
      exit(EXIT_SUCCESS);
    }
    checkForEvents(fd_array, &arr_size, num_events);
  }
}

int main() {
  kServSocket = socket(AF_UNIX, SOCK_STREAM, 0);
  if (kServSocket < 0) {
    printf("Socket error\n");
    exit(EXIT_FAILURE);
  }

  struct sockaddr server_addr;
  server_addr.sa_family = AF_UNIX;
  strcpy(server_addr.sa_data, "myserver1");
  unsigned int addr_len =
      sizeof(server_addr.sa_family) + strlen(server_addr.sa_data) + 1;

  unlink("myserver1");
  if (bind(kServSocket, &server_addr, addr_len) < 0) {
    printf("Binding error\n");
    exit(EXIT_FAILURE);
  }

  if (listen(kServSocket, 1) < 0) {
    printf("Can't listen...\n");
    exit(EXIT_FAILURE);
  }

  serverJob();

  close(kServSocket);
  unlink("myserver1");
  return 0;
}