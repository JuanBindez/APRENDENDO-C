#include <stdio.h>

#define QT_MAXIMA_PESSOAS 30
#define VALOR_MINIMO_FRETE 3.50

int main() {
    float valor_de_compra;
    float valor_liquido;
    float valor_de_frete;
    
    int qtd_pessoas;
    
    printf("\n Digite o valor total da compra: ");
    scanf("%f", &valor_de_compra);
    
    printf("\n Digite a quantidade de pessoas: ");
    scanf("%d", &qtd_pessoas);

    if (qtd_pessoas > QT_MAXIMA_PESSOAS){
        printf("Erro: A quantidade maxima de pessoas por mesa foi atingida! \n");
        return 1;
    }
    
    printf("\n Digite o valor do frete: ");
    scanf("%f", &valor_de_frete);

    if (valor_de_frete < VALOR_MINIMO_FRETE){
        printf("Erro: O valor do frete deve ser maior que 3.50\n");
        return 1; // quando vc retorna 1 o programa é encerrado como erro
    }
    
    valor_liquido = valor_de_compra + valor_de_frete;
    
    printf("\n Valor da conta com frete = %f", valor_liquido);
    
    printf("\n Valor a ser pago por pessoa = \n");
    
    printf("%f", valor_liquido / qtd_pessoas);
    
    return 0;
}
