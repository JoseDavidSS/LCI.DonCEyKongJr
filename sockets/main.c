
  #include <stdio.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<stdio.h>
#include <gtk-3.0/gtk/gtk.h>

#define PORT 8080

#define PORTO 8082
/*
 * Estas variables son necesarias para la interfaz grafica entre las cuales se encuentran
 * los botones el entry y la ventana,etc
 * lo importante es que tenga un alcance global  para poder acceder a ellas desde cualquier metodo
 */
  GtkWidget *window;
  GtkWidget *layout;
  GtkWidget *image;
  GtkWidget *button;
  GtkWidget *button2;
  GtkWidget *entry;
/*
 * Este metodo lo que hace es abrir una conunicacion por sockets y
 * recibe la ip,el puerto y el mensaje a enviar una vez ya enviado el mensaje
 * se cierra el socket
 */
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
/*
 * Este  metodo lo que hace es abrir un socket escuchando el cual
 * tiene como parametros el puerto por el cual se abrira el socket
 */
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

/*
 * Este metodo lo que hace es recolectar el valor del entry y lo convierte en un char
 */
  static void recolectar_entrada (GtkWidget *widget)
  {
      g_print("%s\n", gtk_entry_get_text(GTK_ENTRY(entry)));
      const gchar *entry_text;
      entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
      printf ("Entry contents: %s\n", entry_text);
  }

  int main( int argc, char *argv[])
  {
      //Aqui lo que hacemos es cargar el motor grafico
      gtk_init(&argc, &argv);
      window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
      gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
      gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    //Aqui lo que sucede es crear un layout como container  para las cosas que se pondran en la ventana
      layout = gtk_layout_new(NULL, NULL);
      gtk_container_add(GTK_CONTAINER (window), layout);
      gtk_widget_show(layout);
      //Aqui lo que hacemos es crear los botones y el entry.Ademas de eso creamos  la imagen con el fondo  establecido
      button = gtk_button_new_with_label ("Conectarse Como Jugador");
      button2 = gtk_button_new_with_label ("Conectarse Como Observador");
      entry= gtk_entry_new ();
      image = gtk_image_new_from_file("../background2.png");
      //Aqui asociamos un metodo con el boton cuando se realiza en el la accion de clicked
      g_signal_connect (button, "clicked", G_CALLBACK (recolectar_entrada), NULL);
      //Aqui lo que hacemos es  pegar todas las cosas en la ventana con sus respectivas cordenadas
      gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);
      gtk_entry_set_max_length (GTK_ENTRY (entry),0);
      gtk_layout_put(GTK_LAYOUT(layout), button2, 130, 445);
      gtk_layout_put(GTK_LAYOUT(layout), button, 140, 390);
      gtk_layout_put(GTK_LAYOUT(layout), entry, 475, 290);
      gtk_widget_set_size_request(button, 80, 35);
      gtk_widget_set_size_request(button2, 80, 35);
/*
      gtk_layout_put(GTK_LAYOUT(layout), button2, 130, 445);
      gtk_layout_put(GTK_LAYOUT(layout), button, 140, 390);
      gtk_layout_put(GTK_LAYOUT(layout), entry, 475, 290);
      */

      g_signal_connect_swapped(G_OBJECT(window), "destroy",
                               G_CALLBACK(gtk_main_quit), NULL);

      gtk_widget_show_all(window);

      gtk_main();

      return 0;
  }