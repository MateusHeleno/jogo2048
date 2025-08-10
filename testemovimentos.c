#include "jogo2048.h"

int main(){
    int mat[4][4];
    int n = 4;

    for(int i = 0;i<n;i++){
        for (int j = 0;j<n;j++){
            mat[i][j] = 0;
        }
    }

    mat[0][0] = 8;mat[0][1] = 0;mat[0][2] = 2;mat[0][3] = 2;
    mat[1][1] = 4; 
    mat[2][2] = 8;
    mat[3][3] = 16; 
    //andar para esquerda
    mapa(n,mat);
    for (int i = 0; i < n; i++) {
        int k = 0; // vai indicar minhas casas
    
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                mat[i][k] = mat[i][j];  
                k++;
            }
        }
    // colocar 0 onde vai ta vazia, para ficar vago
        while (k < n) {
            mat[i][k] = 0;
            k++;
        }
    }  
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
    
            if (mat[i][j] != 0 && mat[i][j] == mat[i][j+1]) {
                    mat[i][j] = mat[i][j] * 2;      // Dobra o valor do primeiro bloco
                    mat[i][j+1] = 0;     // Zera o segundo bloco

            }
        }
    }

    // andar para esquerda
    for (int i = 0; i < n; i++) {
        int k = 0; // vai indicar minhas casas
    
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                mat[i][k] = mat[i][j];  
                k++;
            }
        }
        // colocar 0 onde vai ta vazia, para ficar vago
        while (k < n) {
            mat[i][k] = 0;
            k++;
        }
    } 
    mapa(n,mat);
}
