#include <stdio.h>
#include <string.h>
#include "funciones.h"

#define LIMITE_CO2   1000.0f   // ppm
#define LIMITE_SO2     40.0f   // ug/m3
#define LIMITE_NO2     25.0f   // ug/m3
#define LIMITE_PM25    15.0f   // ug/m3

void generarReporteInteractivo(struct Zona zona[], int contador); 


int main() {
    struct Zona zona[100];
    int seguir = 1;
    int opc;
    int opcSub;
    int seguirSub;
    int contador = cargarZonas(zona);

    while (seguir) {
        opc = menu();
        switch (opc) {
            case 0:
                InicializarZonas(zona, &contador);
                printf("Zonas inicializadas correctamente.\n");
                break;
            case 1:
                seguirSub = 1;
                while (seguirSub) {
                    opcSub = submenuIngresarDatos();
                    switch (opcSub) {
                        case 1:
                            agregarZona(zona, &contador);
                            printf("Zona agregada correctamente.\n");
                            break;
                        case 2:
                            verZonas(zona, contador);
                            break;
                        case 3:
                            modificarZona(zona, contador);
                            break;
                        case 4:
                            seguirSub = 0;
                            printf("Volviendo al menu principal...\n");
                            break;
                        default:
                            printf("Opcion no valida.\n");
                    }
                }
                break;
            case 2:
                guardarPredicciones(zona, contador);
                actualizarYVerPredicciones(zona, contador);
                break;
            case 3:
                verDatosHistoricos(zona, contador);
                break;
            case 4:
                verAlertas(zona, contador);
                break;
            case 5:
                    verRecomendaciones(zona, contador);

                break;

            case 6:
               
generarReporteInteractivo(zona, contador);

                break;
            case 7:
                printf("Saliendo del programa...\n");
                seguir = 0;
                break;
            default:
                printf("Opcion no valida.\n");
        }
    }

    return 0;
}

