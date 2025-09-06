#include <stdio.h>

int main() {
    float valor_de_compra;
    float valor_liquido;
    float valor_de_frete;
    
    int qtd_pessoas;
    
    printf("\n Digite o valor total da compra: ");
    
    scanf("%f", &valor_de_compra);
    
    printf("\n Digite a quantidade de pessoas: ");
    
    scanf("%d", &qtd_pessoas);
    
    printf("\n Digite o valor do frete: ");
    
    scanf("%f", &valor_de_frete);
    
    valor_liquido = valor_de_compra + valor_de_frete;
    
    printf("\n Valor da conta com frete = %f", valor_liquido);
    
    printf("\n Valor a ser pago por pessoa = ");
    
    printf("%f", valor_liquido / qtd_pessoas);
    
    return 0;
}
