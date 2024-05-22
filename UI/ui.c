#include <gtk/gtk.h>
#include "../main.h"
#include "ui.h"
#include "../perguntas/perguntas.h"
#include "../user/user.h"

GtkWidget *window;
GtkWidget *login;
GtkWidget *password;
GtkWidget *fixed;

#define WIDTH 800
#define HEIGHT 600

void login_func()
{
    const gchar *login_text = gtk_entry_get_text(GTK_ENTRY(login));
    const gchar *password_text = gtk_entry_get_text(GTK_ENTRY(password));

    if (strcmp(login_text, "admin") == 0 && strcmp(password_text, "admin") == 0)
    {
        menu_admin();
    }
    else if (login_user((char *)login_text, (char *)password_text) == 1)
    {
        printf("Login efetuado com sucesso\n");
        jogo_UI();
    }

    else
    {
        // create new window with error message
        GtkWidget *error_window;
        GtkWidget *error_label;
        error_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(error_window), 200, 100);
        gtk_window_set_title(GTK_WINDOW(error_window), "Error");
        error_label = gtk_label_new("Login ou senha incorretos");
        gtk_container_add(GTK_CONTAINER(error_window), error_label);
        gtk_widget_show_all(error_window);
        printf("Login ou senha incorretos\n");
    }
}

void register_button()
{
    const gchar *login_text = gtk_entry_get_text(GTK_ENTRY(login));
    const gchar *password_text = gtk_entry_get_text(GTK_ENTRY(password));

    register_user((char *)login_text, (char *)password_text);
}

gboolean barra_left(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    // Set the color and size of the shape

    cairo_set_source_rgb(cr, 0.122, 0.267, 0.573); // to git 0-1, 0-1, 0-1 colors
    cairo_set_line_width(cr, 150);

    // Draw a rectangle shape
    cairo_rectangle(cr, 0, 0, 150, HEIGHT);
    cairo_stroke(cr);

    return FALSE;
}

// Criar tela admin -> users
void menu_admin_users()
{
    clear_all();
    menu_left_admin();

    // create_button("users_ver_users", "Ver Usuarios", tela_get_user);
    // create_button("users_create_users", "Criar Usuario", tela_create_user);
    // create_button("users_delete_users", "Apagar Usuario", tela_delete_user);

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}

// Screen user
void tela_create_user()
{
    clear_all();

    create_button("user_create_button", "Criar Usuario", NULL);

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}

void tela_get_user()
{
    clear_all();

    create_button("user_edit_button", "Editar Usuario", NULL);

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}

void tela_delete_user()
{
    clear_all();

    create_button("user_delete_button", "Apagar Usuario", NULL);

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}

int current_pergunta = 0;

void go_left_pergunta()
{
    current_pergunta--;
    if (current_pergunta < 0)
    {
        current_pergunta = get_number_of_perguntas() - 1;
    }
    ver_perguntas();
}

void go_right_pergunta()
{
    current_pergunta++;
    if (current_pergunta >= get_number_of_perguntas())
    {
        current_pergunta = 0;
    }
    ver_perguntas();
}

void ver_perguntas()
{
    clear_all();

    Pergunta **perguntas_get = get_all_perguntas();
    int number_perguntas = get_number_of_perguntas();
    int ff = 0;
    GtkWidget *label = create_label("pergunta_ver", perguntas_get[current_pergunta]->pergunta);
    GtkWidget *label1 = create_label("resposta1_ver", perguntas_get[current_pergunta]->respostas[0]);
    GtkWidget *label2 = create_label("resposta2_ver", perguntas_get[current_pergunta]->respostas[1]);
    GtkWidget *label3;
    GtkWidget *label4;
    if (strcmp(perguntas_get[current_pergunta]->respostas[2], "NULL") != 0)
    {
        label3 = create_label("resposta3_ver", perguntas_get[current_pergunta]->respostas[2]);
    }
    else
    {
        ff = 1;
    }
    if (strcmp(perguntas_get[current_pergunta]->respostas[3], "NULL") != 0)
    {
        label4 = create_label("resposta4_ver", perguntas_get[current_pergunta]->respostas[3]);
    }
    else
    {
        ff = 1;
    }
    GtkWidget *label8 = create_label("dificuldade_ver", dificuldades[perguntas_get[current_pergunta]->dificuldade]);
    GtkWidget *label10 = create_label("tema_ver", temas[perguntas_get[current_pergunta]->tema]);

    char id_str[10];
    sprintf(id_str, "%d", perguntas_get[current_pergunta]->id);
    GtkWidget *label12 = create_label("id_ver", id_str);

    GtkWidget *arr_respostas[4] = {label1, label2, label3, label4};
    GdkRGBA color;
    gdk_rgba_parse(&color, "#00FF00"); // Change the color code to the desired color
    if (ff == 1 && perguntas_get[current_pergunta]->resposta_certa > 1)
    {
        error("Resposta certa não pode ser maior que 2");
        return;
    }
    gtk_widget_override_color(arr_respostas[perguntas_get[current_pergunta]->resposta_certa], GTK_STATE_FLAG_NORMAL, &color);

    create_button("go_left_pergunta", "<", go_left_pergunta);
    create_button("go_right_pergunta", ">", go_right_pergunta);
    create_button("leave_creation_button", "<", menu_admin_quests);

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}

void menu_admin_quests()
{
    clear_all();
    menu_left_admin();

    create_button("ver_perguntas", "Ver Perguntas", ver_perguntas);
    create_button("quests_create_quest", "Criar Pergunta", tela_create_pergunta);
    create_button("quests_edit_quest", "Editar Pergunta", NULL);
    create_button("quests_delete_quest", "Apagar Pergunta", NULL);

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}

// Criar tela admin -> stats

void menu_admin_stats()
{
    clear_all();
    menu_left_admin();

    okay("Stats admin loaded successfully");

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}

void menu_principal()
{
    login_user_global = NULL;
    jogo.joca_level = 0;
    jogo.jocas_number = 3;
    jogo.current_pergunta = 0;
    jogo.current_dificuldade = 0;
    jogo.current_tema = 0;
    jogo.already_shown = NULL;
    jogo.already_shown_len = 0;
    jogo.ending = 0;

    clear_all();

    create_label("jocaTITLE", "JOCA");

    login = create_placeholder_entry("login_input", "Login");

    password = create_password_entry_placeholder("password_input");

    create_button("login_button", "Entrar", login_func);

    create_button("register_button", "Registrar", register_button);

    gtk_widget_show_all(window);
    okay("UI menu loaded successfully");
    gtk_main();
}

void menu_left_admin()
{
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 200, HEIGHT);
    gtk_fixed_put(GTK_FIXED(fixed), drawing_area, 0, 0);

    create_label("say_JOKER_admin", "Admin");
    create_button("users_see_admin", "Usuários", menu_admin_users);
    create_button("perguntas_admin", "Questões", menu_admin_quests);
    create_button("estatisticas_admin", "Estatisticas", menu_admin_stats);

    create_button("logout_game", "Logout", menu_principal);

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(barra_left), NULL);
}

void menu_admin()
{
    clear_all();

    menu_left_admin();

    gtk_widget_show_all(window);
    okay("UI admin loaded successfully");
    gtk_main();
}

int main_UI(int argc, char *argv[])
{

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);
    gtk_window_set_title(GTK_WINDOW(window), "Joca");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_set_name(window, "window");

    import_css();

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    menu_principal();

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}