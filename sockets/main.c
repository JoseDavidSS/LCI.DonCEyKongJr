
  #include <stdio.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
#define PORTO 8082
int enviar(char ip [] ,int puerto,char *mensaje){
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = mensaje;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(puerto);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
   // valread = read( sock , buffer, 1024);
   // printf("%s\n",buffer );
    close(sock);

}
int escuchar(int puerto){
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( puerto );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );



    //send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    close(new_socket);
    close(server_fd);
    return 0;
}
  int main() {
      int puerto =8000;


      enviar("192.168.1.100",8081,"MatrizOriginal");
      escuchar(8080);
//      sleep(1);
//      enviar("192.168.1.100",8080,"HOla sahid Guapo");
//      sleep(1);
//      enviar("192.168.1.100",8080,"HOla sahid Guapo");
//      sleep(1);
//      enviar("192.168.1.100",8080,"HOla sahid Guapo");
//      for (int i = 0; i <10000 ; i++) {
//          enviar("192.168.1.100",8080,"HOla sahid Guapo");
//          sleep(0.7);
//          puerto=puerto+1;
//
//          //
//
//      }




        //enviar("192.168.1.100",8080,"HOla sahid Guapo");
//      escuchar(8081);
//      escuchar(8081);
//      escuchar(8081);
//      escuchar(8081);
//      escuchar(8081);
//      escuchar(8081);
//      escuchar(8081);
//      escuchar(8081);
//      escuchar(8081);
      //enviar("192.168.1.100",8082,"HOla sahid Guapo");


      return 0;
}
