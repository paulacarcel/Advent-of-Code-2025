#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

long long cont_inv = 0;

bool repeticiones(long long num) {

    char str[500]; // array de char (string) de tamaño 50 para guardar número convertido a texto

    // sprintf = printf pero escribe en string, no en pantalla

    sprintf(str, "%lld", num);  // convertir número a string, lo guarda en str

    int tamano = strlen(str); // si tamaño = num caracteres
    
    // Probar todos los tamaños de patrón posibles (de 1 hasta len/2)
    for (int tam_patron = 1; tam_patron <= (tamano / 2); tam_patron++) { // repeticiones de patrón
                                                                         // de 1 a la mitad del patrón,
                                                                         // solo se repite 2 veces, no
                                                                         // puede ocupar más de la mitad

        if (tamano % tam_patron == 0) { // si longitud es divisible por el tamaño del patrón, se puede repetir

            bool err_ID = true; // asumimos que hay repetición y es erróneo

            for (int i = 0; i < tamano; i++) { // comprobación de err_ID
                                                   // recorre caracteres patrón
                                                   // comprueba si cada caracter en pos i es igual a car en pos i en segunda mitad

                if (str[i] != str[i % tam_patron]) {

                    err_ID = false; // si hay algun caracter diferente NO ES ERRÓNEO EL ID
                    break;
                }
            }

            if (err_ID) {
                return true;
            }

        }
    }

    return false; // si se prueban todos y no hay es false
}

int busca_invalidos(long long ini, long long fin) {

    for (long long i = ini; i <= fin; i++) {
        
        if (repeticiones(i)) {
            cont_inv+=i;
        }
    }   

    return 0;    
}

int main(int argc, char *argv[]) {

    char linea[100000]; // buffer para leer linea
    
    FILE *archivo = fopen(argv[1], "r");
    
    if (archivo == NULL) {
        printf("Error: no se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }

    // fgets(char *str, int n, FILE *stream) -> puntero a buffer donde se guarda línea leída
    //                                          tamaño máximo de carateres a leer
    //                                          puntero al archivo desde donde leer
    // devuelve puntero a la cadena leída

    if (fgets(linea, sizeof(linea), archivo) == NULL) { // lee el archivo, 
        fclose(archivo); // en caso de error
        return 1;
    }
    
    // strtok separa cadena en función de un delimitador
    // strtok(char *str, const char *delim) -> cadena a dividir
    //                                         delimitador, en este caso ','
    // devuelve puntero a siguiente token (coma) o NULL si no hay más tokens

    char *token = strtok(linea, ",");

    while (token != NULL) { // mientras haya comas

        long long inicio;
        long long fin;
        
        // sscanf lee de una cadena de texto, no de teclado
        // int sscanf(const char *str, const char *format, ...) -> cadena a leer (hasta el token)
        //                                                         formato esperado (LL-LL)
        //                                                         variables donde se guardan los valores leídos
        // devuelve número de elementos leídos correctamente

        sscanf(token, "%lld-%lld", &inicio, &fin);
        busca_invalidos(inicio, fin); // con elemento ini y fin hasta el token

        token = strtok(NULL, ","); // token toma un nuevo valor, siguiente coma
    }
    
    printf("Contraseña: %lld\n", cont_inv);
    fclose(archivo);
    return 0;
}
