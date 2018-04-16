//
// Created by 陈国威 on 2018/4/14.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>


#define IP	"127.0.0.1"
#define PORT 8888
#define WORKER 4

int worker(int listenfd, int i)
{
  while (1)
    {
      printf ("I am woker %d, begin to accept connection.\n", i);
      struct sockaddr_in  clientaddr;
      socklen_t client_addrLen = sizeof (clientaddr);
      int connfd = accept (listenfd, (struct sockaddr*)&clientaddr, &client_addrLen);
      if (connfd != -1)
        {
          printf ("worker %d accept a connection success. \t", i);
          printf ("ip: %s \t", inet_ntoa (clientaddr.sin_addr));
          printf ("port: %d\t", clientaddr.sin_port);
        }
      else
        {
          printf ("worker %d accept a connection failed , error :%s\n", i, strerror (errno));
          close (listenfd);
        }
    }
}


int main(void)
{
  int i = 0;
  struct sockaddr_in address;
  bzero (&address, sizeof (address));
  address.sin_family = AF_INET;
//  inet_pton (AF_INET, IP, &address.sin_addr);
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons (PORT);
  int listenfd = socket (AF_INET, SOCK_STREAM, 0);
  assert (listenfd >= 0);

  int ret = bind (listenfd, (struct sockaddr*)&address, sizeof (address));
  assert ( ret != -1);

  ret = listen (listenfd, 5);
  assert ( ret != -1);

  for (i = 0; i < WORKER; ++i)
    {
      printf (" Create worker %d \n", i);
      pid_t pid = fork ();
      if (pid == 0)
        {
          worker (listenfd, i);
        }

      if (pid < 0)
        {
          printf ("fork error\n");
        }
    }

  /// wait child process
  int status;
  wait (&status);

  return 0;
}