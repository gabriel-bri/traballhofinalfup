#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

typedef struct professor{
    int matricula;
    char nome[50];
    // mestrado, doutorado, graduação
    char maior_titulacao[50];
    //engenharia de software, rede de computadores.
    char area_pesquisa[50];
}Prof;

typedef struct disciplina{
    int num_disc;
    char nome_disc[50];
    int semestre;
    int creditos;
}Disciplina;

typedef struct associado{
    int mat_prof;
    int num_disc;
}Associado;

/*void aloca(Associado **associacao){
        *associacao= (Associado *) realloc(*associacao, sizeof(Associado)*strlen(*associacao)+2);
        if(*associacao == NULL){
            puts("** Memoria insuficiente**");
            exit(0);
        }
    }*/

void inserir_professores(){
    FILE *p = fopen("professor.txt", "ab");
    int opc;
    Prof profe;
    do{
        printf("Digite a matricula, nome, maior titulação e area de pesquisa do professor\n");
        scanf(" %d", &profe.matricula);
        scanf(" %[^\n]", profe.nome);
        scanf(" %[^\n]", profe.maior_titulacao);
        scanf(" %[^\n]", profe.area_pesquisa);

        fwrite(&profe, sizeof(Prof), 1, p);

        printf("Deseja adicionar outro?\n 1- sim \n 0- nao");
        scanf("%d", &opc);
    }while(opc != 0);

    fclose(p);
}
void remover_professores(){
    FILE *pr = fopen("professor.txt","rb");
    int opc;
    int cont=0;
    int mat;
    Prof profe;
    Prof *profs = (Prof *) malloc(sizeof(Prof));
    
    printf("Digite a matricula do professor que deseja remover.\n");
    scanf(" %d", &mat);

        
    while(fread(&profe,sizeof(Prof), 1, pr)){
        if(profe.matricula != mat){
            *(profs+cont) = profe;
            cont++;
            profs = (Prof *) realloc(profs, (cont+1)*sizeof(Prof));
        }   
    }
    fclose(pr);

    FILE *pw = fopen("professor.txt", "wb");
    for(int i=0; i<cont; i++){
       fwrite(profs+i, sizeof(Prof), 1, pw); 
    }
    fclose(pw);
}
void inserir_disciplinas(){
    FILE *d = fopen("disciplina.txt", "ab");
    Disciplina disc; 
    int opc;

    printf("Digite o numero, nome, semestre e creditos da disciplina\n");
    scanf(" %d", &disc.num_disc);
    scanf(" %[^\n]", disc.nome_disc);
    scanf(" %d", &disc.semestre);
    scanf(" %d", &disc.creditos);
     fwrite(&disc, sizeof(Disciplina), 1, d);

    fclose(d);
}
void remover_disciplinas(){
    FILE *d = fopen("disciplina.txt", "rb");
    int cont = 0;
    int n;

    Disciplina disc;
    Disciplina *disciplinas =  malloc(sizeof(Disciplina));

    printf("Digite o numero da disciplina a ser removida.");
    scanf(" %d", &n);

    while(fread(&disc,sizeof(Disciplina), 1, d)){
        if(disc.num_disc != n){
            *(disciplinas+cont) = disc;
            cont++;
            disciplinas = (Disciplina *) realloc(disciplinas, (cont+1)*sizeof(Disciplina));
        }
    }
    fclose(d);

    FILE *dw = fopen("disciplina.txt", "wb");
    for(int i=0; i<cont; i++){
       fwrite(disciplinas+i, sizeof(Disciplina), 1, dw); 
    }
    fclose(dw);
}
void associar_diciplinas(){
    
    //criacao do arquivo de associacao do prof e da disc.
    FILE *p_m = fopen("associacao.txt", "ab");
    FILE *d = fopen("disciplina.txt", "rb");
    FILE *p = fopen("professor.txt", "rb");
    //estrutura que contém todos os dados de professor e disciplina reunidos.
    Associado associado;
    Prof profe;
    Disciplina disc;
    
    int mat_temp;
    int disc_temp;
    int cont1=0;
    int cont2=0;
    
    //while(cont1==0 || cont2==0)
        printf("\nDigite a matricula do professor e o numero da disciplina que quer associar.\n");
        scanf(" %d %d", &associado.mat_prof, &associado.num_disc);
/*
        //verificacao se existe o professor e a disciplina registrado.
        while(fread(&profe, sizeof(Prof), 1, p)){
            if(mat_temp==profe.matricula) cont1++;
        }
        if(cont1==0) printf("professor nao encontrado!\n");
        else printf("professor encontrado.");

        while(fread(&disc, sizeof(Disciplina), 1, d)){
            if(disc_temp==disc.num_disc) cont2++;
        }
        if(cont2==0) printf("disciplina nao encontrada!\n");
        else printf("disciplina encontrada.");
        }
 */   

    fwrite(&associado, sizeof(Associado), 1, p_m);
    
    fclose(p_m);
    fclose(p);
    fclose(d);

}
void imprimir_associacoes(){
    FILE *p_m = fopen("associacao.txt", "rb");

    Associado associado;

    while(fread(&associado, sizeof(Associado), 1, p_m) == 1){
            printf("Prof: %d -", associado.mat_prof);
            printf(" Disc: %d \n", associado.num_disc);
        }
    
    fclose(p_m);
}

void imprimir_professores(){
    FILE *p = fopen("professor.txt", "rb");

    Prof profe;

    while(fread(&profe, sizeof(Prof), 1, p) == 1){
            printf("Prof: %s -", profe.nome);
            printf(" mat: %d \n", profe.matricula);
        }
    
    fclose(p);
}
void imprimir_disciplinas(){
    FILE *d = fopen("disciplina.txt", "rb");

    Disciplina disc;

    while(fread(&disc, sizeof(Disciplina), 1, d) == 1){
            printf("nome: %s -", disc.nome_disc);
            printf("numero: %d \n", disc.num_disc);
        }
    
    fclose(d);
}
int main(){
    setlocale(LC_ALL,"Portuguese");
    int opc;
    do{
        printf("Selecione a opcao desejada:\n1- Inserir professor\n 2-Remover professor\n 3- Inserir disciplina\n 4- Remover disciplina\n 5-Associar professor a disciplina \n 6- Imprimir associacao \n 7- imprimir professor \n 8-imprimir disciplina \n 9- sair\n");
        scanf("%d", &opc);
        
        switch(opc){
            case 1:
                inserir_professores();
                break;
            case 2:
                remover_professores();
                break;
            case 3:
                inserir_disciplinas();
                break;
            case 4:
                remover_disciplinas();
                break;
            case 5:
                associar_diciplinas();
                break;
            case 6:
                imprimir_associacoes();
                break;
            case 7:
                imprimir_professores();
                break;
            case 8:
                imprimir_disciplinas();
                break;
            case 9:
                printf("Encerrando");
                break;
            default:
                printf("Opcao invalida!");
        }
        
    }while(opc!=9);
      
    return(0);
}
