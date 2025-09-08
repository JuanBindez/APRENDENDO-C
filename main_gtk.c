#include <stdio.h>
#include <gtk/gtk.h>

#define QT_MAXIMA_PESSOAS 30
#define VALOR_MINIMO_FRETE 3.50

// Estrutura para armazenar os dados da aplicação
typedef struct {
    GtkWidget *valor_compra_entry;
    GtkWidget *qtd_pessoas_entry;
    GtkWidget *valor_frete_entry;
    GtkWidget *resultado_label;
} AppData;

// Função para validar se uma string é um número float válido
gboolean is_float(const gchar *str) {
    gchar *endptr;
    strtod(str, &endptr);
    return (*endptr == '\0');
}

// Função para validar se uma string é um número inteiro válido
gboolean is_integer(const gchar *str) {
    gchar *endptr;
    strtol(str, &endptr, 10);
    return (*endptr == '\0');
}

// Função chamada quando o botão de calcular é clicado
void calcular_divisao(GtkWidget *widget, gpointer data) {
    AppData *app_data = (AppData *)data;
    
    // Obter os valores dos campos de entrada
    const gchar *valor_compra_str = gtk_entry_get_text(GTK_ENTRY(app_data->valor_compra_entry));
    const gchar *qtd_pessoas_str = gtk_entry_get_text(GTK_ENTRY(app_data->qtd_pessoas_entry));
    const gchar *valor_frete_str = gtk_entry_get_text(GTK_ENTRY(app_data->valor_frete_entry));
    
    // Validar os campos
    if (strlen(valor_compra_str) == 0 || strlen(qtd_pessoas_str) == 0 || strlen(valor_frete_str) == 0) {
        gtk_label_set_text(GTK_LABEL(app_data->resultado_label), "Erro: Preencha todos os campos!");
        return;
    }
    
    if (!is_float(valor_compra_str) || !is_integer(qtd_pessoas_str) || !is_float(valor_frete_str)) {
        gtk_label_set_text(GTK_LABEL(app_data->resultado_label), "Erro: Valores inválidos!");
        return;
    }
    
    // Converter os valores
    float valor_de_compra = atof(valor_compra_str);
    int qtd_pessoas = atoi(qtd_pessoas_str);
    float valor_de_frete = atof(valor_frete_str);
    
    // Validar regras de negócio
    if (qtd_pessoas > QT_MAXIMA_PESSOAS) {
        gchar error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Erro: Máximo de %d pessoas por mesa!", QT_MAXIMA_PESSOAS);
        gtk_label_set_text(GTK_LABEL(app_data->resultado_label), error_msg);
        return;
    }
    
    if (valor_de_frete < VALOR_MINIMO_FRETE) {
        gchar error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Erro: Frete mínimo é R$ %.2f!", VALOR_MINIMO_FRETE);
        gtk_label_set_text(GTK_LABEL(app_data->resultado_label), error_msg);
        return;
    }
    
    // Calcular os valores
    float valor_liquido = valor_de_compra + valor_de_frete;
    float valor_por_pessoa = valor_liquido / qtd_pessoas;
    
    // Exibir os resultados
    gchar resultado[200];
    snprintf(resultado, sizeof(resultado), 
             "Valor total com frete: R$ %.2f\n"
             "Valor por pessoa: R$ %.2f\n"
             "Pessoas: %d | Frete: R$ %.2f",
             valor_liquido, valor_por_pessoa, qtd_pessoas, valor_de_frete);
    
    gtk_label_set_text(GTK_LABEL(app_data->resultado_label), resultado);
}

// Função para limpar os campos
void limpar_campos(GtkWidget *widget, gpointer data) {
    AppData *app_data = (AppData *)data;
    
    gtk_entry_set_text(GTK_ENTRY(app_data->valor_compra_entry), "");
    gtk_entry_set_text(GTK_ENTRY(app_data->qtd_pessoas_entry), "");
    gtk_entry_set_text(GTK_ENTRY(app_data->valor_frete_entry), "");
    gtk_label_set_text(GTK_LABEL(app_data->resultado_label), "Preencha os dados e clique em Calcular");
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    // Criar a janela principal
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Divisor de Conta");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 350);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    // Criar o container principal
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // Criar os widgets
    GtkWidget *titulo_label = gtk_label_new("Divisor de Conta de Restaurante");
    gtk_widget_set_halign(titulo_label, GTK_ALIGN_CENTER);
    
    GtkWidget *valor_compra_label = gtk_label_new("Valor total da compra (R$):");
    GtkWidget *valor_compra_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(valor_compra_entry), "Ex: 150.00");
    
    GtkWidget *qtd_pessoas_label = gtk_label_new("Quantidade de pessoas:");
    GtkWidget *qtd_pessoas_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(qtd_pessoas_entry), "Ex: 4");
    
    GtkWidget *valor_frete_label = gtk_label_new("Valor do frete (R$):");
    GtkWidget *valor_frete_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(valor_frete_entry), "Ex: 5.00");
    
    GtkWidget *calcular_button = gtk_button_new_with_label("Calcular");
    GtkWidget *limpar_button = gtk_button_new_with_label("Limpar");
    
    GtkWidget *resultado_label = gtk_label_new("Preencha os dados e clique em Calcular");
    gtk_label_set_line_wrap(GTK_LABEL(resultado_label), TRUE);
    gtk_widget_set_halign(resultado_label, GTK_ALIGN_CENTER);
    
    // Criar grid para os botões
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(button_box), calcular_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_box), limpar_button, TRUE, TRUE, 0);
    
    // Adicionar widgets ao container principal
    gtk_box_pack_start(GTK_BOX(vbox), titulo_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), valor_compra_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), valor_compra_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), qtd_pessoas_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), qtd_pessoas_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), valor_frete_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), valor_frete_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), resultado_label, FALSE, FALSE, 10);
    
    // Armazenar dados da aplicação
    AppData app_data = {
        .valor_compra_entry = valor_compra_entry,
        .qtd_pessoas_entry = qtd_pessoas_entry,
        .valor_frete_entry = valor_frete_entry,
        .resultado_label = resultado_label
    };
    
    // Conectar sinais
    g_signal_connect(calcular_button, "clicked", G_CALLBACK(calcular_divisao), &app_data);
    g_signal_connect(limpar_button, "clicked", G_CALLBACK(limpar_campos), &app_data);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Mostrar todos os widgets
    gtk_widget_show_all(window);
    
    // Executar o loop principal
    gtk_main();
    
    return 0;
}