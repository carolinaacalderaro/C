#include <stdio.h>

int main() {
    int V1, V2, V3, D, D1, D2, caminho_direto, caminho_p2, energia;

    scanf("%d %d %d %d", &V1, &V2, &V3, &D);
    
    D1 = D/10;
    D2 = D%10;
    
    caminho_direto = V1 + V3;
    caminho_p2 = V1 + V2 + V3;
    
    if (D1 > D2) {
        caminho_direto += D1 - D2;
    }
    
    else if (D2 > D1) {
        caminho_p2 += D2 - D1;
    }
    
    else {
        caminho_direto += D1 + D2;
        caminho_p2 += D1 + D2;
    }
    
    if (caminho_direto > caminho_p2) {
        energia = caminho_direto;
    }
    
    else {
        energia = caminho_p2;
    }
    
    if (energia > 30) {
        if (caminho_direto > caminho_p2){
            printf("Caminho: direto. Xupenio aprova! Nível: ELITE.");
        }
        
        else {
            printf("Caminho: P2. Xupenio aprova! Nível: ELITE.");
        }
    }
    
    else if (energia >= 10 && energia <= 30) {
        if (caminho_direto > caminho_p2){
            printf("Caminho: direto. Boa caminhada! Nível: SÓLIDO.");
        }
        
        else {
            printf("Caminho: P2. Boa caminhada! Nível: SÓLIDO.");
        }
    }

    else if (energia >= 0 && energia <= 9) {
        if (caminho_direto > caminho_p2){
            printf("Caminho: direto. Passou por pouco. Nível: BÁSICO.");
        }
        
        else {
            printf("Caminho: P2. Passou por pouco. Nível: BÁSICO.");
        }
    }
    
    else {
        if (caminho_direto > caminho_p2){
            printf("Caminho: direto. Xupenio reprova. Nível: CRÍTICO.");
        }
        
        else {
            printf("Caminho: P2. Xupenio reprova. Nível: CRÍTICO.");
        }
    }
    return 0;
}