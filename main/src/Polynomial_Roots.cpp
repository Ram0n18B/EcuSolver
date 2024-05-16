/**
 * @JohanMaldonado
 * @RamonBelandria
 */

#include <TestUtilities.hpp>

#include <gtk/gtk.h>
#include <iostream>
#include <iomanip>  
#include <sstream>     
#include <string>
#include <vector>
#include "Solver.hpp"  


void show_dialog(const std::string& message) {
    GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "%s", message.c_str());
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void on_button_clicked(GtkWidget* button, gpointer user_data) {
    GtkEntry* entry = GTK_ENTRY(user_data);
    const char* equation = gtk_entry_get_text(entry);
    std::string expression(equation);

    Solver solver(expression);
    std::vector<double> solutions = solver.get_roots();

    if (solutions.empty()) {
        show_dialog("El polinomio no tiene raíces reales");
    } else if (solutions.size() == 1) {
        
        std::stringstream stream;
        stream << "Solución: " << std::fixed << std::setprecision(2) << solutions[0];
        show_dialog(stream.str());
    } else {
        std::string result = "Soluciones: ";
        for (double solution : solutions) {
            
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << solution << ",";
            result += stream.str();
        }
        show_dialog(result);
    }
}

void on_window_closed(GtkWidget* widget, GdkEvent* event, gpointer data) {
    gtk_main_quit(); 
}

int main(int argc, char** argv) {
    gtk_init(&argc, &argv);

    
    GtkBuilder* builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "design.ui", NULL);

    GtkWidget* window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    GtkWidget* entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry"));
    GtkWidget* button = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
    GtkWidget* close_button = GTK_WIDGET(gtk_builder_get_object(builder, "close"));

    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry);

    g_signal_connect(close_button, "clicked", G_CALLBACK(gtk_window_close), window);

    g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);


    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
