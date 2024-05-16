/**
 * @JohanMaldonado
 * @RamonBelandria
 */

#include <TestUtilities.hpp>

#include <gtk/gtk.h>
#include <iostream>
#include <string>
#include <vector>
#include "Solver.hpp"  // Asegúrate de incluir correctamente tus archivos de cabecera

// Función para mostrar un cuadro de diálogo con el resultado
void show_dialog(const std::string& message) {
    GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "%s", message.c_str());
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Función para ejecutar el código al hacer clic en el botón
void on_button_clicked(GtkWidget* button, gpointer user_data) {
    GtkEntry* entry = GTK_ENTRY(user_data);
    const char* equation = gtk_entry_get_text(entry);
    std::string expression(equation);

    Solver solver(expression);
    std::vector<double> solutions = solver.get_roots();

    if (solutions.empty()) {
        show_dialog("El polinomio no tiene raíces reales");
    } else if (solutions.size() == 1) {
        show_dialog("Solución: " + std::to_string(solutions[0]));
    } else {
        std::string result = "Soluciones: ";
        for (double solution : solutions) {
            result += std::to_string(solution) + " ";
        }
        show_dialog(result);
    }
}

void on_window_closed(GtkWidget* widget, GdkEvent* event, gpointer data) {
    gtk_main_quit(); // Finalizar la ejecución de la aplicación al cerrar la ventana
}

int main(int argc, char** argv) {
    gtk_init(&argc, &argv);

    // Cargar el archivo de diseño de la interfaz gráfica
    GtkBuilder* builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "design.ui", NULL);

    // Obtener los widgets necesarios
    GtkWidget* window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    GtkWidget* entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry"));
    GtkWidget* button = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
    GtkWidget* close_button = GTK_WIDGET(gtk_builder_get_object(builder, "close"));

    // Conectar la señal "clicked" del botón a la función on_button_clicked
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry);

    g_signal_connect(close_button, "clicked", G_CALLBACK(gtk_window_close), window);

    g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);


    // Mostrar la ventana principal
    gtk_widget_show_all(window);

    // Ejecutar el bucle principal de eventos
    gtk_main();

    return 0;
}
