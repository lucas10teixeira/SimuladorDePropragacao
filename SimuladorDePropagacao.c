#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int evento_aleatorio() {
    int sorteio = rand() % 100 + 1;

    if (sorteio <= 5) {
        printf(" (Evento: Mutação mais contagiosa!)\n");
        return 50;
    } else if (sorteio <= 10) {
        printf(" (Evento: Mídia gera alerta!)\n");
        return -30;
    } else if (sorteio <= 20) {
        printf(" (Evento: Isolamento voluntário!)\n");
        return -20;
    } else if (sorteio <= 35) {
        printf(" (Evento: Aglomeração!)\n");
        return 25;
    }
    return 0;
}

int main() {
    srand(time(NULL));

    int pt, npi, tc, vacinados, ev, ns;
    char dw;

    do {
        printf("1 - Nova Simulação\n");
        printf("2 - Sair do Programa\n");
        scanf(" %c", &dw);
    } while (dw != '1' && dw != '2');

    if (dw == '2') {
        printf("Encerrando programa...\n");
        return 0;
    }

    printf("População total: ");
    scanf("%d", &pt);
    printf("Número de pessoas inicialmente infectadas: ");
    scanf("%d", &npi);
    printf("Taxa de contágio (%%): ");
    scanf("%d", &tc);
    printf("Número de pessoas vacinadas: ");
    scanf("%d", &vacinados); 
    printf("Efetividade da vacina (%%): ");
    scanf("%d", &ev);
    printf("Número de dias da simulação: ");
    scanf("%d", &ns);

    int saudaveis_vacinados = vacinados;
    int saudaveis_nao_vacinados = pt - vacinados - npi;
    int vacinados_infectados = 0;
    int infectados = npi;

    printf("\n--- Simulação Iniciada ---\n");
    for (int dia = 1; dia <= ns; dia++) {
        printf("Dia %d: %d infectados", dia, infectados);

        int impacto = evento_aleatorio();
        float taxa_dia = tc + impacto;
        if (taxa_dia < 0) taxa_dia = 0;

        int estimativa = (int)floor((taxa_dia / 100.0) * infectados);

        float suscetiveis = saudaveis_nao_vacinados + 
                            saudaveis_vacinados * (1 - ev / 100.0);

        if (suscetiveis <= 0) {
            printf(" — Todos os suscetíveis foram infectados.\n");
            break;
        }

        int novos = (int)fmin(estimativa, suscetiveis);
        printf(" (+%d)\n", novos);

        int infect_nv = (int)fmin(novos, saudaveis_nao_vacinados);
        int infect_v = novos - infect_nv;

        saudaveis_nao_vacinados -= infect_nv;
        saudaveis_vacinados -= infect_v;
        vacinados_infectados += infect_v;
        infectados += novos;
    }

    printf("\n--- Resultados Finais ---\n");
    printf("Total infectados: %d\n", infectados);
    printf("População vacinada: %d\n", vacinados);
    printf("Vacinados infectados: %d\n", vacinados_infectados);
    printf("População saudável: %d\n", saudaveis_nao_vacinados + saudaveis_vacinados);

    return 0;
}