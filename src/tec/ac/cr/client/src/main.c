
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>
#include <gtk-3.0/gtk/gtk.h>
#include "socket/Socket.h"
#include "ui/AllegroWindow.h"

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
GtkWidget *label;

static char* serverIp = "127.0.0.1";
static int fpoints = 0;

/**
 * Metodo para conectarse al server como jugador
 * @param widget
 */
static void conectarseJugador (GtkWidget *widget){
    g_print("%s\n", gtk_entry_get_text(GTK_ENTRY(entry)));
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
    enviar(serverIp,8081, entry_text);
    sleep(1);
    enviar(serverIp,8081,"jjjjjjjjjjjjjjjjjjjjjj");
    char* recieved = escuchar(8081, serverIp);
    char * respuestaPositiva="si";
    int i = strcmp(recieved, respuestaPositiva);
    if (i == 0){
        char* hola;
        hola = escuchar(8081, serverIp);
        int a = (int) hola;
        printf("%d",a);
        if (a == 4287872){
            fpoints = mainAllegro(8082);
            printf("los puntos son %d",fpoints);
           // char* mensajePuntos=(char *)fpoints;
            //gtk_label_set_text(GTK_LABEL (label),  mensajePuntos);

        }else{
            fpoints = mainAllegro(8083);
            printf("los puntos son %d",fpoints);

           // char* mensajePuntos=(char *)fpoints;
            //gtk_label_set_text(GTK_LABEL (label),  mensajePuntos);
        }
    } else{
        printf("Me rechazaron");
    }
}

/**
 * Metodo para conectarse al servidor como observador
 * @param widget
 */
static void conectarseObservador (GtkWidget *widget){
    g_print("%s\n", gtk_entry_get_text(GTK_ENTRY(entry)));
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
    enviar(serverIp,8081, entry_text);
    sleep(1);
    enviar(serverIp,8081,"ooooooooooooooooooooooo");
    char* recieved = escuchar(8081, serverIp);
    char * respuestaPositiva="si";
    int i = strcmp(recieved, respuestaPositiva);
    if (i == 0){
        char* hola;
        hola = escuchar(8081, serverIp);
        int a = (int) hola;
        printf("%d",a);
        if (a == 4287872){
            fpoints = mainAllegro(8082);
        }else{
            fpoints = mainAllegro(8083);
        }
    } else{
        printf("Me rechazaron");
    }
}

int main( int argc, char *argv[]){
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
    label = gtk_label_new("");

    button = gtk_button_new_with_label ("Conectarse Como Jugador");
    button2 = gtk_button_new_with_label ("Conectarse Como Observador");
    entry= gtk_entry_new ();
    image = gtk_image_new_from_file("../src/imagenes/background.png");
    //Aqui asociamos un metodo con el boton cuando se realiza en el la accion de clicked
    g_signal_connect (button, "clicked", G_CALLBACK(conectarseJugador), NULL);
    g_signal_connect (button2, "clicked", G_CALLBACK(conectarseObservador), NULL);

    //Aqui lo que hacemos es  pegar todas las cosas en la ventana con sus respectivas cordenadas

    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

    gtk_entry_set_max_length (GTK_ENTRY (entry),0);
    gtk_layout_put(GTK_LAYOUT(layout), button2, 130, 445);
    gtk_layout_put(GTK_LAYOUT(layout), button, 140, 390);

    gtk_layout_put(GTK_LAYOUT(layout), entry, 475, 290);
    gtk_layout_put(GTK_LAYOUT(layout), label, 475, 320);

    gtk_widget_set_size_request(button, 80, 35);
    gtk_widget_set_size_request(button2, 80, 35);
    g_signal_connect_swapped(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
