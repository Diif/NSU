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

  unlink("myserver1");
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

// #define MAXBUF 256
// char buf[MAXBUF];
// int main() {
//   struct sockaddr serv_addr, clnt_addr;
//   int sockfd;
//   int saddrlen, caddrlen, max_caddrlen, n;

//   if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
//     printf("Невозможно создать сокетХп");
//     exit(1);
//   }

//   unlink("./echo.server");
//   // bzero(&serv_addr, sizeof(serv_addr));
//   serv_addr.sa_family = AF_UNIX;
//   strcpy(serv_addr.sa_data, "./echo.server");
//   saddrlen = sizeof(serv_addr.sa_family) + strlen(serv_addr.sa_data);
//   if (bind(sockfd, (struct sockaddr *)&serv_addr, saddrlen) < 0) {
//     printf("Ошибка связывания сокета c адресом\n");
//     exit(1);
//   }

//   max_caddrlen = sizeof(clnt_addr);
//   for (;;) {
//     caddrlen = max_caddrlen;
//     n = recvfrom(sockfd, buf, MAXBUF, 0, (struct sockaddr *)&clnt_addr,
//                  &caddrlen);
//     if (n < 0) {
//       printf("Ошибка приема\n");
//       exit(1);
//     }

//     if (sendto(sockfd, buf, n, 0, (struct sockaddr *)&clnt_addr, caddrlen) !=
//         n) {
//       printf("Ошибка передачи\n");
//       exit(1);
//     }
//   }
//   return 0;
// }
