// main.h
#include <gtk/gtk.h>
#include <cairo.h>
#ifndef UI_H
#define UI_H

#define WIDTH 800
#define HEIGHT 600

// create_pergunta.c
void tela_create_pergunta();

// edit_pergunta.c
void tela_edit_pergunta();
void last_players_played_by_date();
void got_to_last_patamar();
void got_all_jokers();

// user_UI.c
void start_user_UI();

void menu_admin();
void menu_left_admin();
void menu_admin_quests();
void ver_perguntas();
void tela_edit_user();
void tela_create_user();
void tela_delete_user();

// estatisticas_UI.c
void show_last_10_games();

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
GtkWidget *create_list();
void menu_admin_estatistica();
void add_array_of_elements_to_list_horizontal(GtkWidget *list, const gchar *text[], int len, guint padding, const gchar *css_ID, guint width, guint height);
typedef struct
{
    int current_pergunta;
    int current_dificuldade;
    int current_tema;
    int *already_shown;
    int already_shown_len;
    int ending;
    int joca_level;
    int jocas_number;
    int jocas_ganhos;
    int pontuacao;
    float multiplicador;
    int ff;
    int ff_certas;
    int player_id;
} JogoJoca;

extern JogoJoca save_jogos[2048];

int main_UI(int argc, char *argv[]);
void jogo_UI();
void menu_principal();
extern GtkWidget *window;
extern JogoJoca jogo;

extern char *pergunta_add;
extern char *resposta_1_add;
extern char *resposta_2_add;
extern char *resposta_3_add;
extern char *resposta_4_add;
extern unsigned long int current_resposta_certa;
extern unsigned long int dificuldade_add;
extern unsigned long int tema_add;
extern float tempo_add;
extern unsigned long int tipo;
extern unsigned long int ff;

extern GtkWidget *pergunta;
extern GtkWidget *resposta_1;
extern GtkWidget *resposta_2;
extern GtkWidget *resposta_3;
extern GtkWidget *resposta_4;
extern GtkWidget *tempo;

extern GtkWidget *array_dificuldade[3];
extern GtkWidget *array_resposta[4];
extern GtkWidget *array_tema[9];
extern GtkWidget *array_tipo[2];

extern char *niveis[];

void set_tipo(GtkWidget *widget, gpointer tipo, gpointer user_data);
void set_dificuldade(GtkWidget *widget, gpointer dificuldade, gpointer user_data);
void set_tema(GtkWidget *widget, gpointer tema, gpointer user_data);
void set_resposta(GtkWidget *widget, gpointer resposta);
void clear_all_camps();
void force_window_size();
void ssearch_user_ui(int clear);

#endif