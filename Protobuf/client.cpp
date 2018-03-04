#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "addressbook.pb.h"
#include "lib.h"

#define HOSTNAME "localhost"
#define PORT 8000
#define MAXDATASIZE 4096

using std::cout;
using std::endl;
using std::string;



int main(int argc, char** argv) {
   int fd;
   int numbytes;
   char buf[MAXDATASIZE];
   struct hostent *he;
   struct sockaddr_in server;

   if ((he = gethostbyname(HOSTNAME)) == NULL) {
       err("gethostbyname");
   }

   if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
       err("socket");
   }

   bzero(&server, sizeof(server));
   server.sin_family = AF_INET;
   server.sin_port = htons(PORT);
   server.sin_addr = *((struct in_addr *)he->h_addr);

   if (connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
       err("connect");
   }

   string msg;
   demo::People to;
   to.set_name("violet");
   to.set_email("violet@gmail.com");
   to.set_id(1002);
   to.SerializeToString(&msg);
   cout<< msg.c_str();
   send(fd, buf, sizeof(buf), 0);

   numbytes = recv(fd, buf, MAXDATASIZE, 0);
   buf[numbytes] = '\0';
   string data = buf;
   demo::People p;
   p.ParseFromString(data);
   cout << "People:\t"  << endl;
   cout << "Name:\t"    << p.name() << endl;
   cout << "ID:\t"      << p.id() << endl;
   cout << "Email:\t"   << p.email() << endl;

   close(fd);
   return 0;
}
