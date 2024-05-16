#include "main.h"

/*
get_question
save_perguntas
load_perguntas
*/

char temas[5][20] = {"tema0", "tema1", "tema2", "tema3", "tema4"};

Pergunta_node *pergunta_head;

void init_perguntas(Pergunta *p)
{
    pergunta_head = malloc(sizeof(Pergunta_node));
    pergunta_head->next = NULL;
    pergunta_head->pergunta = p;
    okay("Perguntas initialized");
    return;
}

void free_pergunta(Pergunta *pergunta)
{
    for (int i = 0; i < 4; i++)
    {
        free(pergunta->respostas[i]);
    }
    free(pergunta->respostas);
    free(pergunta);
}

int get_number_of_perguntas()
{
    Pergunta_node *temp_node = pergunta_head;
    int NUMBER_OF_PERGUNTAS = 1;
    while (temp_node->next != NULL)
    {
        NUMBER_OF_PERGUNTAS++;
        temp_node = temp_node->next;
    }
    return NUMBER_OF_PERGUNTAS;
}

Pergunta *create_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int id, int tema, float tempo, int tipo)
{
    // criar pergunta
    Pergunta *p = (Pergunta *)malloc(sizeof(Pergunta));
    p->pergunta = pergunta;
    p->resposta_certa = resposta_certa;
    p->dificuldade = dificuldade;
    p->id = id;
    p->tema = tema;
    p->tempo = tempo;
    p->tipo = tipo;

    // malloc memory for respostas

    p->respostas = (char **)malloc(4 * sizeof(char *));

    p->respostas[0] = (char *)malloc(strlen(resposta_1) + 1);
    strcpy(p->respostas[0], resposta_1);
    p->respostas[1] = (char *)malloc(strlen(resposta_2) + 1);
    strcpy(p->respostas[1], resposta_2);

    p->respostas[2] = (char *)malloc(strlen(resposta_3) + 1);
    strcpy(p->respostas[2], resposta_3);
    p->respostas[3] = (char *)malloc(strlen(resposta_4) + 1);
    strcpy(p->respostas[3], resposta_4);

    return p;
}

void *add_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int id, int tema, float tempo, int tipo)
{
    Pergunta *p = create_pergunta(pergunta, resposta_1, resposta_2, resposta_3, resposta_4, resposta_certa, dificuldade, id, tema, tempo, tipo);

    Pergunta_node *temp_node = pergunta_head;

    while (temp_node->next != NULL)
    {
        temp_node = temp_node->next;
    }

    Pergunta_node *new = malloc(sizeof(Pergunta_node));
    new->pergunta = p;
    new->next = NULL;
    temp_node->next = new;
}

void add_pergunta_with_struct(Pergunta *p)
{
    add_pergunta(p->pergunta, p->respostas[0], p->respostas[1], p->respostas[2], p->respostas[3], p->resposta_certa, p->dificuldade, p->id, p->tema, p->tempo, p->tipo);
}

void *edit_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int id, int tema, float tempo, int tipo)
{
    Pergunta *p = create_pergunta(pergunta, resposta_1, resposta_2, resposta_3, resposta_4, resposta_certa, dificuldade, id, tema, tempo, tipo);

    Pergunta_node *temp_node = pergunta_head;

    while (temp_node->next != NULL)
    {
        if (temp_node->pergunta->id == id)
        {
            free_pergunta(temp_node->pergunta);
            temp_node->pergunta = p;
            return 0;
        }

        temp_node = temp_node->next;
    }

    if (temp_node->pergunta->id == id)
    {
        free_pergunta(temp_node->pergunta);
        temp_node->pergunta = p;
        return 0;
    }

    error("Pergunta.id not found edit_pergunta");
    return 0;
}

void delete_pergunta(int id) // FALTA DAR FREE
{
    Pergunta_node *temp_node = pergunta_head;
    Pergunta_node *depois;
    Pergunta_node *antes;

    while (temp_node->next != NULL)
    {
        if (temp_node->pergunta->id == id)
        {
            depois = temp_node->next;
            break;
        }
        antes = temp_node;
        temp_node = temp_node->next;
    }

    if (temp_node == pergunta_head && temp_node->next == NULL)
    {
        error("O programa deve ter pelo menos 1 pergunta (LL delete_pergunta)"); // da para fzr de outra maneira :D
        return;
    }

    if (temp_node == pergunta_head)
    {
        pergunta_head = depois;
    }
    else if (temp_node->next == NULL)
    {
        antes->next = NULL;
    }
    else
    {
        antes->next = depois;
    }
    free_pergunta(temp_node->pergunta); // free a pergunta
    free(temp_node);                    // free ao nodo da pergunta
}

Pergunta **get_all_perguntas()
{
    int NUMBER_OF_PERGUNTAS = get_number_of_perguntas();
    Pergunta **ret = malloc(sizeof(Pergunta *) * NUMBER_OF_PERGUNTAS);

    Pergunta_node *temp_node = pergunta_head;
    int i = 0;
    while (temp_node->next != NULL)
    {
        ret[i] = temp_node->pergunta;
        i++;
        temp_node = temp_node->next;
    }
    ret[i] = temp_node->pergunta;

    return ret;
}

void print_pergunta()
{
    Pergunta_node *temp_node = pergunta_head;

    while (temp_node->next != NULL)
    {
        printf("Pergunta: %s\n", temp_node->pergunta->pergunta);
        printf("Respostas: %s %s %s %s\n", temp_node->pergunta->respostas[0], temp_node->pergunta->respostas[1], temp_node->pergunta->respostas[2], temp_node->pergunta->respostas[3]);
        printf("Resposta certa: %d\n", temp_node->pergunta->resposta_certa);
        printf("Dificuldade: %d\n", temp_node->pergunta->dificuldade);
        printf("ID: %d\n", temp_node->pergunta->id);
        printf("Tema: %d\n", temp_node->pergunta->tema);
        printf("Tempo: %f\n", temp_node->pergunta->tempo);
        printf("Tipo: %d\n", temp_node->pergunta->tipo);
        printf("\n\n");
        temp_node = temp_node->next;
    }
    printf("Pergunta: %s\n", temp_node->pergunta->pergunta);
    printf("Respostas: %s %s %s %s\n", temp_node->pergunta->respostas[0], temp_node->pergunta->respostas[1], temp_node->pergunta->respostas[2], temp_node->pergunta->respostas[3]);
    printf("Resposta certa: %d\n", temp_node->pergunta->resposta_certa);
    printf("Dificuldade: %d\n", temp_node->pergunta->dificuldade);
    printf("ID: %d\n", temp_node->pergunta->id);
    printf("Tema: %d\n", temp_node->pergunta->tema);
    printf("Tempo: %f\n", temp_node->pergunta->tempo);
    printf("Tipo: %d\n", temp_node->pergunta->tipo);
    printf("\n\n");
}

void load_perguntas()
{
    okay("Loading perguntas\n");
    // abrir,verificar se existe,ler,guardar na lista
    FILE *f = fopen("perguntas.bin", "rb");

    if (f == NULL)
    {
        error("Error opening file");
        return;
    }

    okay("File opened\n");
    Pergunta *p = malloc(sizeof(Pergunta));

    if (p == NULL)
    {
        error("Error allocating memory");
        return;
    }

    int is_first_time = 0;
    while (fread(p, sizeof(Pergunta), 1, f))
    {
        RW_Pergunta rw_pergunta;
        fread(&rw_pergunta, sizeof(RW_Pergunta), 1, f);

        p->pergunta = malloc(rw_pergunta.pergunta_len);

        fread(p->pergunta, sizeof(char), rw_pergunta.pergunta_len, f);

        p->respostas = (char **)malloc(4 * sizeof(char *));

        for (int i = 0; i <= 3; i++)
        {
            p->respostas[i] = malloc(rw_pergunta.respostas_len[i]);
            fread(p->respostas[i], sizeof(char), rw_pergunta.respostas_len[i], f);
        }

        if (is_first_time == 0)
        {
            init_perguntas(create_pergunta(p->pergunta, p->respostas[0], p->respostas[1], p->respostas[2], p->respostas[3], p->resposta_certa, p->dificuldade, p->id, p->tema, p->tempo, p->tipo));
            is_first_time = 1;
        }
        else
        {
            add_pergunta_with_struct(create_pergunta(p->pergunta, p->respostas[0], p->respostas[1], p->respostas[2], p->respostas[3], p->resposta_certa, p->dificuldade, p->id, p->tema, p->tempo, p->tipo));
        }
    }

    free(p);
    fclose(f);
}

void write_to_file(FILE *f, Pergunta_node *temp_node, RW_Pergunta rw_pergunta)
{
    fwrite(temp_node->pergunta, sizeof(Pergunta), 1, f);

    rw_pergunta.pergunta_len = strlen(temp_node->pergunta->pergunta) + 1;

    for (int i = 0; i <= 3; i++)
    {
        rw_pergunta.respostas_len[i] = strlen(temp_node->pergunta->respostas[i]) + 1;
    }

    fwrite(&rw_pergunta, sizeof(RW_Pergunta), 1, f);

    fwrite(temp_node->pergunta->pergunta, sizeof(char), rw_pergunta.pergunta_len, f);
    for (int i = 0; i < 4; i++)
    {
        fwrite(temp_node->pergunta->respostas[i], sizeof(char), strlen(temp_node->pergunta->respostas[i]) + 1, f);
    }
}

void save_perguntas()
{
    FILE *f = fopen("perguntas.bin", "wb");

    if (f == NULL)
    {
        error("Error opening file");
        return;
    }

    Pergunta_node *temp_node = pergunta_head;
    RW_Pergunta rw_pergunta;
    while (temp_node->next != NULL)
    {
        write_to_file(f, temp_node, rw_pergunta);
        temp_node = temp_node->next;
    }

    write_to_file(f, temp_node, rw_pergunta);

    fclose(f);
}