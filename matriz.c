#include "matriz.h"

void criar(MatrizEsparsa *M){
    M->cabecalho = (no *)malloc(sizeof(no));
    M->cabecalho->id = -1;
    M->cabecalho->proxcoluna = M->cabecalho;
    M->cabecalho->proxlinha = M->cabecalho;
    M->cabecalho->tipo = 'c';
}

void inserir_no(MatrizEsparsa *M, int *iden){
    no *inserir1;
    no *inserir2;
    inserir1 = (no*) malloc(sizeof(no));
    inserir2 = (no*) malloc(sizeof(no));

    //aux nodes
    	//nó para colunas
    no *p1;
    p1 = M->cabecalho;

    	//nó para linhas
    no *p2;
    p2 = M->cabecalho;

    //achando o último nó inserido menor que o atual
    while (p1->proxcoluna != M->cabecalho && p1->proxcoluna->id < *iden)
        p1 = p1->proxcoluna;

    while (p2->proxlinha != M->cabecalho && p1->proxlinha->id < *iden)
        p2 = p2->proxlinha;


    if (p1->proxcoluna->id > *iden){
        inserir1->proxcoluna = p1->proxcoluna;
        p1->proxcoluna = inserir1;
    }
    else{
        p1->proxcoluna = inserir1;
        inserir1->proxcoluna = M->cabecalho;
    }

    if (p2->proxlinha->id > *iden){
        inserir2->proxlinha = p2->proxlinha;
        p2->proxlinha = inserir2;
    }
    else{
        p2->proxlinha = inserir2;
        inserir2->proxlinha = M->cabecalho;
    }

    inserir1->proxlinha = inserir1;
    inserir2->proxcoluna = inserir2;

    inserir1->id = *iden;
    inserir1->tipo = 'v';

    inserir2->id = *iden;
    inserir2->tipo = 'v';
}

int checar_aresta (no *aresta, int escolha){
    no *aux;
    aux = aresta;
    if (escolha == 1){
        while (aux->tipo != 'v')
            aux = aux->proxcoluna;
    }
    else{
        while (aux->tipo != 'v')
            aux = aux->proxlinha;
    }

    return aux->id;
}

void inserir_aresta (MatrizEsparsa *M, int *id1, int *id2){
    /*-----------Parte 1: colocar aresta para p1 coluna e p2 linha-----------*/
    no *inserir; //nova aresta a ser colocada
    inserir = (no*) malloc(sizeof(no)); //alocar memoria para nova aresta

    no *p1, *p2; //auxiliares que andarao por colunas e linhas, respectivamente
    p1 = M->cabecalho; //ambos começam no cabeçalho
    p2 = M->cabecalho;

    //achando o nó da coluna e da linha
    while (p1->id != *id1) //enquanto o id do auxiliar p1 nao eh o id do nó 1 que queremos
        p1 = p1->proxcoluna; //anda uma coluna pra frente

    while (p2->id != *id2) //enquanto o id do auxiliar p2 nao eh o id do nó 2 que queremos
        p2 = p2->proxlinha; //anda uma linha pra baixo
    //printf("\nencontrou certo os vertices\n");


    if (p1->proxlinha != p1 && checar_aresta(p1->proxlinha, 1) < *id2) { //se p1 ja possui uma aresta (ou seja, nao aponta pra ele mesmo)
                                                                         //e essa aresta ta numa posicao antes da aresta que queremos colocar
        //printf("colocara depois de um existente\n");
        no *aux; //nó auxiliar
        aux = p1; //começa no nó que saira a nova aresta

        while (aux->proxlinha != p1 && checar_aresta(aux->proxlinha, 1) < *id2){ //enquanto o auxiliar nao chega de volta em p1
                                                                                 //e ta antes do local a ser colocado a aresta
            aux = aux->proxlinha; //anda uma linha pra baixo
        }
        //printf ("colocou depois de um existente\n");
        inserir->proxlinha = aux->proxlinha; //a aresta a ser inserida aponta pro proximo do auxiliar (que ta logo antes da posicao da aresta)
        aux->proxlinha = inserir; //o proximo do auxiliar (que ta logo antes da posicao da aresta) eh a aresta inserida
    }
    else{ //se p1 ja possui uma aresta (ou seja, nao aponta pra ele mesmo) e essa aresta ta numa posicao DEPOIS da arsta que queremos colocar
          //OU p1 nao possui alguma aresta
        //printf("colocou antes de um existente\n");
        inserir->proxlinha = p1->proxlinha; //a aresta a ser inserida vai ser logo dps do vertice, entao o proximo da nova aresta
                                            //eh a proxima antiga aresta ou o vertice
        p1->proxlinha = inserir; //e o proximo de p1 vai ser a nova aresta
    }


    if (p2->proxcoluna != p2 && checar_aresta(p2->proxcoluna, 2) < *id1) { //se p2 ja possui uma aresta (ou seja, nao aponta pra ele mesmo)
                                                                           //e essa aresta ta numa posicao antes da aresta que queremos colocar
        //printf("colocara depois de um existente\n");
        no *aux; //nó auxiliar
        aux = p2; //começa no nó que saira a nova aresta

        while (aux->proxcoluna != p2 && checar_aresta(aux->proxcoluna, 2) < *id1){ //enquanto o auxiliar nao chega de volta em p2
                                                                                   //e ta antes do local a ser colocado a aresta
            aux = aux->proxcoluna; //anda uma coluna pra direita
        }
        //printf("colocou depois de um existente\n");
        inserir->proxcoluna = aux->proxcoluna; //a aresta a ser inserida aponta pro proximo do auxiliar (que ta logo antes da posicao da aresta)
        aux->proxcoluna = inserir; //o proximo do auxiliar (que ta logo antes da posicao da aresta) eh a aresta inserida
    }

    else{ //se p2 ja possui uma aresta (ou seja, nao aponta pra ele mesmo) e essa aresta ta numa posicao DEPOIS da aresta que queremos colocar
          //OU p2 nao possui alguma aresta
        //printf("colocou antes de um existente\n");
        inserir->proxcoluna = p2->proxcoluna; //a aresta a ser inserida vai ser logo dps do vertice, entao o proximo da nova aresta
                                              //eh a proxima antiga aresta ou o vertice
        p2->proxcoluna = inserir; //e o proximo de p2 vai ser a nova aresta
    }

    inserir->id = 0;
    inserir->tipo = 'a';

    //printf("deu bom\n");

    /*-------------Parte 2: colocar aresta para p1 coluna e p2 linha------------*/
    no *inserir2;
    inserir2 = (no*) malloc(sizeof(no));

    p1 = M->cabecalho;
    p2 = M->cabecalho;

    while (p1->id != *id1)
        p1 = p1->proxlinha;

    while (p2->id != *id2)
        p2 = p2->proxcoluna;

    //printf("\nencontrou certo os vertices\n");

    if (p1->proxcoluna != p1 && checar_aresta(p1->proxcoluna, 2) < *id2) { //se p1 ja possui uma aresta (ou seja, nao aponta pra ele mesmo)
                                                                           //e essa aresta ta numa posicao antes da aresta que queremos colocar
        //printf("colocara depois de um existente\n");
        no *aux; //nó auxiliar
        aux = p1; //começa no nó que saira a nova aresta

        while (aux->proxcoluna != p1 && checar_aresta(aux->proxcoluna, 2) < *id2){ //enquanto o auxiliar nao chega de volta em p1
                                                                                   //e ta antes do local a ser colocado a aresta
            aux = aux->proxcoluna; //anda uma coluna pra direita
        }
        //printf("colocou depois de um existente\n");
        inserir2->proxcoluna = aux->proxcoluna; //a aresta a ser inserida aponta pro proximo do auxiliar (que ta logo antes da posicao da aresta)
        aux->proxcoluna = inserir2; //o proximo do auxiliar (que ta logo antes da posicao da aresta) eh a aresta inserida
    }

    else{//se p1 ja possui uma aresta (ou seja, nao aponta pra ele mesmo) e essa aresta ta numa posicao DEPOIS da aresta que queremos colocar
         //OU p1 nao possui alguma aresta
        //printf("colocou antes de um existente\n");
        inserir2->proxcoluna = p1->proxcoluna; //a aresta a ser inserida vai ser logo dps do vertice, entao o proximo da nova aresta
                                               //eh a proxima antiga aresta ou o vertice
        p1->proxcoluna = inserir2; //e o proximo de p1 vai ser a nova aresta
    }


    if (p2->proxlinha != p2 && checar_aresta(p2->proxlinha, 1) < *id1) { //se p2 ja possui uma aresta (ou seja, nao aponta pra ele mesmo)
                                                                         //e essa aresta ta numa posicao antes da aresta que queremos colocar
        //printf("colocara depois de um existente\n");
        no *aux; //nó auxiliar
        aux = p2; //começa no nó que saira a nova aresta

        while (aux->proxlinha != p2 && checar_aresta(aux->proxlinha, 1) < *id1){ //enquanto o auxiliar nao chega de volta em p2
                                                                                 //e ta antes do local a ser colocado a aresta
            aux = aux->proxlinha; //anda uma linha pra baixo
        }
        //printf("colocou depois de um existente\n");
        inserir2->proxlinha = aux->proxlinha; //a aresta a ser inserida aponta pro proximo do auxiliar (que ta logo antes da posicao da aresta)
        aux->proxlinha = inserir2; //o proximo do auxiliar (que ta logo antes da posicao da aresta) eh a aresta inserida
    }

    else { //se p2 ja possui uma aresta (ou seja, nao aponta pra ele mesmo) e essa aresta ta numa posicao DEPOIS da aresta que queremos colocar
           //OU p2 nao possui alguma aresta
        //printf("colocou antes de um existente\n");
        inserir2->proxlinha = p2->proxlinha; //a aresta a ser inserida vai ser logo dps do vertice, entao o proximo da nova aresta
                                            //eh a proxima antiga aresta ou o vertice
        p2->proxlinha = inserir2; //e o proximo de p2 vai ser a nova aresta
    }

    inserir2->id = 0;
    inserir2->tipo = 'a';
    //printf("deu bom 2\n");
}

int analisarGrau(MatrizEsparsa *M, int *ide){
    no *p, *aux;
    p = M->cabecalho;
    int grau = 0;
    while(p->proxcoluna != M->cabecalho && p->proxcoluna->id != *ide){
        p = p->proxcoluna;
    }
    if(p->proxcoluna == M->cabecalho){
        return -1;
    }
    else{
        p = p->proxcoluna;
        aux = p;
    }
    while(p->proxlinha != aux){
        grau++;
        p = p->proxlinha;
    }
    return grau;
}

void grauVizinhos(MatrizEsparsa *M, int *ide){
    int grauPrincipal = analisarGrau(M, ide);
    float resultado = 0;
    int i;
    no *p;
    p = M->cabecalho;
    while(p->id != *ide){
        p = p->proxcoluna;
    }
    no *aux;
    aux = p;
    for(i = 0; i < grauPrincipal; i++){
        aux = aux->proxlinha;
        no *aux2 = aux;
        while(aux2->tipo == 'a')
            aux2 = aux2->proxcoluna;

        resultado += analisarGrau(M, &aux2->id);
    }
    resultado /= grauPrincipal;
    printf("\n%.2f", resultado);
}

int eVizinho(MatrizEsparsa *M, int ide, int ide2){
    no *p, *l;
    p = l = M->cabecalho;
    while(p->id != ide)
        p = p->proxcoluna;
    while(l->id != ide2)
        l = l->proxlinha;
    p = p->proxlinha;
    l = l->proxcoluna;
    for(;l->tipo == 'a'; l = l->proxcoluna){
        if(p->tipo != 'a')
            p = p->proxlinha;
        for(;p->tipo == 'a'; p = p->proxlinha){
            if(p == l)
                return 1;
        }
    }
    return 0;
}

void coeficiente(MatrizEsparsa *M, int *ide){
    int grauPrincipal = analisarGrau(M, ide);
    float resultado1, resultado2;
    int ex = 0, i, j, vetor[grauPrincipal];
    no *p = M->cabecalho;
    p = p->proxcoluna;
    while(p->id != *ide)
        p = p->proxcoluna;
    for(i = 0; i < grauPrincipal; i++){
        p = p->proxlinha;
        no *aux = p;
        while(aux->tipo == 'a')
            aux = aux->proxcoluna;
        vetor[i] = aux->id;
    }
    for(j = 0; j < grauPrincipal; j++){
        for(i = 0; i < grauPrincipal; i++){
            if(eVizinho(M, vetor[i], vetor[j]) == 1)
                ex++;
        }
    }
    ex = ex/2;

    resultado1 = (2*ex);
    resultado2 = (pow(grauPrincipal, 2) - grauPrincipal);
    float resultado = resultado1/resultado2;
    if(resultado1 == 0 || resultado2 == 0)
        printf("\n0.00\n");
    else
        printf("\n%.2f\n", resultado);
}

int setardist(MatrizEsparsa *M, no *aux, int distatual){
    no *p;
    p = aux;

    while(p->tipo == 'a'){
        p = p->proxcoluna;
    }

    if(p->dist > distatual){ //se for a distatual for menor
        p->dist = distatual;
        return p->id; //sucesso
    }else
    return -1; //não setou

}

void grau_hierarquico_rec(MatrizEsparsa *M, int ide, int distatual){
    if (distatual > 2) //implementação para h = 2, caso deseje genérica é só criar o parâmetro h.
        return;
    //printf("\nChamou para id = %d\n", ide);
    no *p;
    p = M->cabecalho;

    while(p->id != ide){
        p = p->proxcoluna;
    }

    no *aux;
    aux = p;
    int setou;

    do {
        aux = aux->proxlinha;
        setou = setardist(M, aux, distatual);
        //printf("Setou = %d, dist = %d\n", setou, distatual);

        if (setou != -1)
            grau_hierarquico_rec(M, setou, distatual+1);

    } while(aux->tipo == 'a');


    return;
}


void grau_hierarquico(MatrizEsparsa *M, int ide){
    no *p;

    p = M->cabecalho;
    p = p->proxlinha;

    while(p->tipo != 'c'){
        p->dist = INF; //setando distância como "infinito"
        if(p->id == ide)
            p->dist = 0;
        p = p->proxlinha;
    }

    grau_hierarquico_rec(M, ide, 1);

    p = M->cabecalho;
    p = p->proxlinha;

    int hierarquico = 0;

    while(p->tipo != 'c'){
        if(p->dist == 2 && p->id != ide){
        	//printf("Somou hierarquico para id = %d\n", p->id);
            hierarquico++;
        }

        p = p->proxlinha;
    }

    printf("%d\n", hierarquico);
}
