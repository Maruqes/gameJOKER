// main.h
#include <gtk/gtk.h>
#include <cairo.h>
#ifndef MAIN_H
#define MAIN_H

// UI
extern GtkWidget *fixed;

void import_css();
void clear_all();
GtkWidget *create_button(const gchar *css_ID, const gchar *label, void *func);
GtkWidget *create_label(const gchar *css_ID, const gchar *label);
GtkWidget *create_password_entry(const gchar *css_ID);
GtkWidget *create_entry(const gchar *css_ID);
GtkWidget *create_placeholder_entry(const gchar *css_ID, const gchar *placeholder);
GtkWidget *create_password_entry_placeholder(const gchar *css_ID);

int main_UI(int argc, char *argv[]);

// MAIN
#define okay(msg, ...) printf("\033[1;32m[ + ]\033[0m " msg "\n", ##__VA_ARGS__)
#define error(msg, ...) printf("\033[1;31m[ - ]\033[0m " msg "\n", ##__VA_ARGS__)
#define info(msg, ...) printf("\033[1;34m[ i ]\033[0m " msg "\n", ##__VA_ARGS__)

#endif