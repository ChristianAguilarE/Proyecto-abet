#include <stdio.h>
#include <string.h>
#include "funciones.h"

#define LIMITE_CO2   1000.0f   // ppm
#define LIMITE_SO2     40.0f   // ug/m3
#define LIMITE_NO2     25.0f   // ug/m3
#define LIMITE_PM25    15.0f   // ug/m3


int menu() {
    int opcion;
    printf("\n===== MENU PRINCIPAL =====\n");
    printf("0) Inicializar Zonas\n");
    printf("1) Gestionar Zonas\n");
    printf("2) Ver predicciones\n");
    printf("3) Ver datos historicos\n");
    printf("4) Alertas\n");
    printf("5) Recomendaciones\n");
    printf("6) Ver REPORTES\n");
    printf("7) Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

int submenuIngresarDatos() {
    int opcion;
    printf("\n--- GESTION DE ZONAS ---\n");
    printf("1) Agregar una zona\n");
    printf("2) Ver zonas\n");
    printf("3) Modificar zona\n");
    printf("4) Volver al menu principal\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

void InicializarZonas(struct Zona zona[], int *contador) {
    // Zona 0: Quito
    strcpy(zona[0].nombre, "Quito");
    strcpy(zona[0].pais, "Ecuador");
    strcpy(zona[0].ubicacion, "Ubicacion 1");
    zona[0].co2 = 400.0f;
    zona[0].so2 = 10.0f;
    zona[0].no2 = 20.0f;
    zona[0].pm25 = 15.0f;
    zona[0].temperatura = 10.0f;
    zona[0].viento = 5.0f;
    zona[0].humedad = 60.0f;
    cargarHistoricoZona(&zona[0]);

    // Zona 1: Cuenca
    strcpy(zona[1].nombre, "Cuenca");
    strcpy(zona[1].pais, "Ecuador");
    strcpy(zona[1].ubicacion, "Ubicacion 2");
    zona[1].co2 = 420.0f;
    zona[1].so2 = 15.0f;
    zona[1].no2 = 25.0f;
    zona[1].pm25 = 15.0f;
    zona[1].temperatura = 16.0f;
    zona[1].viento = 15.0f;
    zona[1].humedad = 60.0f;
    cargarHistoricoZona(&zona[1]);

    *contador = 2;
    guardarZonas(zona, *contador);
}

void agregarZona(struct Zona zona[], int *contador) {
    if (*contador >= 100) {
        printf("No se pueden agregar mas zonas.\n");
        return;
    }

    // Datos de texto
    printf("Ingrese el nombre de la zona: ");
    scanf("%s", zona[*contador].nombre);
    while (getchar() != '\n');

    printf("Ingrese el pais: ");
    scanf("%s", zona[*contador].pais);
    while (getchar() != '\n');

    printf("Ingrese la ubicacion: ");
    scanf("%s", zona[*contador].ubicacion);
    while (getchar() != '\n');

    if (cargarHistoricoZona(&zona[*contador])) {
        printf("Historicos cargados de %s.txt\n", zona[*contador].nombre);
    }

    // Niveles de contaminantes
    printf("Ingrese niveles actuales de contaminantes:\n");

    printf("CO2 (ppm): ");
    while (scanf("%f", &zona[*contador].co2) != 1) {
        printf("Entrada invalida. Ingrese un numero valido para CO2 (ppm): ");
        while (getchar() != '\n');
    }

    printf("SO2 (ug/m3): ");
    while (scanf("%f", &zona[*contador].so2) != 1) {
        printf("Entrada invalida. Ingrese un numero valido para SO2 (ug/m3): ");
        while (getchar() != '\n');
    }

    printf("NO2 (ug/m3): ");
    while (scanf("%f", &zona[*contador].no2) != 1) {
        printf("Entrada invalida. Ingrese un numero valido para NO2 (ug/m3): ");
        while (getchar() != '\n');
    }

    printf("PM25 (ug/m3): ");
    while (scanf("%f", &zona[*contador].pm25) != 1) {
        printf("Entrada invalida. Ingrese un numero valido para PM25 (ug/m3): ");
        while (getchar() != '\n');
    }

    // Condiciones climaticas
    printf("Ingrese condiciones climaticas:\n");

    printf("Temperatura (C): ");
    while (scanf("%f", &zona[*contador].temperatura) != 1) {
        printf("Entrada invalida. Ingrese un numero valido para temperatura (C): ");
        while (getchar() != '\n');
    }

    printf("Viento (km/h): ");
    while (scanf("%f", &zona[*contador].viento) != 1) {
        printf("Entrada invalida. Ingrese un numero valido para viento (km/h): ");
        while (getchar() != '\n');
    }

    printf("Humedad (%%): ");
    while (scanf("%f", &zona[*contador].humedad) != 1) {
        printf("Entrada invalida. Ingrese un numero valido para humedad: ");
        while (getchar() != '\n');
    }

    (*contador)++;
    guardarZonas(zona, *contador);
    printf("Zona agregada correctamente.\n");
}


void verZonas(struct Zona zona[], int contador) {
    printf("\n%-4s %-15s %-12s %-15s %-8s %-8s %-8s %-10s %-12s %-10s %-10s\n",
           "No.", "Nombre", "Pais", "Ubicacion", "CO2", "SO2", "NO2", "PM25", "Temp C", "Viento", "Humedad");
    printf("----------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < contador; i++) {
        printf("%-4d %-15s %-12s %-15s %-8.2f %-8.2f %-8.2f %-10.2f %-12.2f %-10.2f %-10.2f\n",
               i+1,
               zona[i].nombre,
               zona[i].pais,
               zona[i].ubicacion,
               zona[i].co2,
               zona[i].so2,
               zona[i].no2,
               zona[i].pm25,
               zona[i].temperatura,
               zona[i].viento,
               zona[i].humedad);
    }
}

void modificarZona(struct Zona zona[], int contador) {
    int opcion;
    if (contador == 0) {
        printf("No hay zonas para modificar.\n");
        return;
    }
    printf("\nZonas registradas:\n");
    for (int i = 0; i < contador; i++) {
        printf("%d) %s, %s, %s\n", i+1, zona[i].nombre, zona[i].pais, zona[i].ubicacion);
    }
    printf("Seleccione el numero de zona (1-%d): ", contador);
    scanf("%d", &opcion);
    if (opcion < 1 || opcion > contador) {
        printf("Opcion invalida.\n");
        return;
    }
    int idx = opcion-1;
    printf("Modificando %s\n", zona[idx].nombre);
    printf("Nuevo nombre (actual %s): ", zona[idx].nombre);
    scanf("%s", zona[idx].nombre);
    printf("Nuevo pais (actual %s): ", zona[idx].pais);
    scanf("%s", zona[idx].pais);
    printf("Nueva ubicacion (actual %s): ", zona[idx].ubicacion);
    scanf("%s", zona[idx].ubicacion);
    guardarZonas(zona, contador);
    printf("Zona modificada.\n");
}

// Lee 30 valores de cada contaminante desde "<Nombre>.txt"
int cargarHistoricoZona(struct Zona *z) {
    char fileName[64];
    snprintf(fileName, sizeof(fileName), "%s.txt", z->nombre);
    FILE *f = fopen(fileName, "r");
    if (!f) {
        printf("Advertencia: no se encontro %s. Historicos a 0.\n", fileName);
        for (int j = 0; j < 30; j++) {
            z->historicoCO2[j] = 0.0f;
            z->historicoSO2[j] = 0.0f;
            z->historicoNO2[j] = 0.0f;
            z->historicoPM25[j] = 0.0f;
        }
        return 0;
    }
    char nombreArchivo[50];
    fscanf(f, "%49s", nombreArchivo);
    if (strcmp(nombreArchivo, z->nombre) != 0) {
        printf("Error: nombre en %s no coincide (%s).\n", fileName, nombreArchivo);
        fclose(f);
        return 0;
    }
    for (int j = 0; j < 30; j++) fscanf(f, "%f", &z->historicoCO2[j]);
    for (int j = 0; j < 30; j++) fscanf(f, "%f", &z->historicoSO2[j]);
    for (int j = 0; j < 30; j++) fscanf(f, "%f", &z->historicoNO2[j]);
    for (int j = 0; j < 30; j++) fscanf(f, "%f", &z->historicoPM25[j]);
    fclose(f);
    return 1;
}

float predecir5(float historico[30], float hoy, float temperatura, float viento, float humedad, float coef) {
    // Pesos fijos que suman 100%
    float pesos[7] = {0.35f, 0.25f, 0.15f, 0.10f, 0.07f, 0.05f, 0.03f};

    float pred = 0.0f;

    pred += hoy * pesos[0];                // Día actual
    pred += historico[29] * pesos[1];      // Día -1
    pred += historico[28] * pesos[2];      // Día -2
    pred += historico[27] * pesos[3];      // Día -3
    pred += historico[26] * pesos[4];      // Día -4
    pred += historico[25] * pesos[5];      // Día -5
    pred += historico[24] * pesos[6];      // Día -6

    // Ajuste climático
    if (temperatura > 20.0f) pred += pred * 0.005f * (temperatura - 20.0f);
    if (viento > 10.0f)     pred -= pred * 0.01f  * ((viento - 10.0f) / 5.0f);
    if (humedad > 50.0f)    pred -= pred * 0.002f * ((humedad - 50.0f) / 5.0f);

    return pred * coef;
}


void guardarPredicciones(struct Zona zona[], int contador) {
    FILE *archivo = fopen("predicciones.dat", "wb");
    if (!archivo) {
        printf("Error abriendo predicciones.dat\n");
        return;
    }
    float a=0.1f, b=0.5f, c=0.4f, d=0.8f;
    for (int i = 0; i < contador; i++) {
        float hoyCO2, hoySO2, hoyNO2, hoyPM25;
        printf("Ingrese niveles actuales para %s:\n", zona[i].nombre);
        printf("CO2 (ppm): ");    scanf("%f",&hoyCO2);
        printf("SO2 (ug/m3): "); scanf("%f",&hoySO2);
        printf("NO2 (ug/m3): "); scanf("%f",&hoyNO2);
        printf("PM25 (ug/m3): ");scanf("%f",&hoyPM25);
        float pred[8];
        pred[0]=predecir5(zona[i].historicoCO2, hoyCO2, zona[i].temperatura, zona[i].viento, zona[i].humedad, a);
        pred[1]=predecir5(zona[i].historicoSO2, hoySO2, zona[i].temperatura, zona[i].viento, zona[i].humedad, b);
        pred[2]=predecir5(zona[i].historicoNO2, hoyNO2, zona[i].temperatura, zona[i].viento, zona[i].humedad, c);
        pred[3]=predecir5(zona[i].historicoPM25,hoyPM25, zona[i].temperatura, zona[i].viento, zona[i].humedad, d);
        pred[4]=predecir5(zona[i].historicoCO2, hoyCO2, zona[i].temperatura, zona[i].viento, zona[i].humedad, a);
        pred[5]=predecir5(zona[i].historicoSO2, hoySO2, zona[i].temperatura, zona[i].viento, zona[i].humedad, b);
        pred[6]=predecir5(zona[i].historicoNO2, hoyNO2, zona[i].temperatura, zona[i].viento, zona[i].humedad, c);
        pred[7]=predecir5(zona[i].historicoPM25,hoyPM25, zona[i].temperatura, zona[i].viento, zona[i].humedad, d);
        fwrite(zona[i].nombre, sizeof(char), 50, archivo);
        fwrite(pred, sizeof(float), 8, archivo);
    }
    fclose(archivo);
}

void actualizarYVerPredicciones(struct Zona zona[], int contador) {
    char buscar[50];
    printf("Ingrese nombre de zona para ver prediccion: ");
    scanf("%s", buscar);
    FILE *archivo = fopen("predicciones.dat", "rb");
    if (!archivo) {
        printf("Error abriendo predicciones.dat\n");
        return;
    }
    char nombre[50];
    float pred[8];
    int encontrada=0;
    while (fread(nombre, sizeof(char), 50, archivo)==50 &&
           fread(pred, sizeof(float), 8, archivo)==8) {
        if (strcmp(nombre, buscar)==0) {
            printf("\n--- PREDICCION PARA %s ---\n", nombre);
            printf("%-10s %-10s %-10s %-10s %-10s\n","Periodo","CO2","SO2","NO2","PM25");
            printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f\n","1 dia",  pred[0],pred[1],pred[2],pred[3]);
            printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f\n","1 semana",pred[4],pred[5],pred[6],pred[7]);
            encontrada=1;
            break;
        }
    }
    if (!encontrada) {
        printf("Zona '%s' no encontrada.\n", buscar);
    }
    fclose(archivo);
}

void verDatosHistoricos(struct Zona zona[], int contador) {
    char buscar[50];
    int i, j;
    printf("Ingrese nombre de zona para ver historicos: ");
    scanf("%s", buscar);

    for (i = 0; i < contador; i++) {
        if (strcmp(zona[i].nombre, buscar) == 0) {
            // Cabecera de la tabla
            printf("\nDatos historicos de la zona: %s\n", zona[i].nombre);
            printf("%-5s %-10s %-10s %-10s %-10s\n",
                   "Dia", "CO2", "SO2", "NO2", "PM2.5");
            printf("------------------------------------------------------\n");
            // Filas de datos
            for (j = 0; j < 30; j++) {
                printf("%-5d %-10.2f %-10.2f %-10.2f %-10.2f\n",
                       j+1,
                       zona[i].historicoCO2[j],
                       zona[i].historicoSO2[j],
                       zona[i].historicoNO2[j],
                       zona[i].historicoPM25[j]);
            }
            return;
        }
    }

    // Si no encuentra la zona
    printf("Zona '%s' no encontrada\n", buscar);
}


void verAlertas(struct Zona zona[], int contador) {
    for (int i=0;i<contador;i++){
        printf("\nZona: %s\n", zona[i].nombre);
        int alerta=0;
        if(zona[i].co2> LIMITE_CO2)  { printf(" CO2 alto: %.2f\n", zona[i].co2);  alerta=1; }
        if(zona[i].so2> LIMITE_SO2)  { printf(" SO2 alto: %.2f\n", zona[i].so2);  alerta=1; }
        if(zona[i].no2> LIMITE_NO2)  { printf(" NO2 alto: %.2f\n", zona[i].no2);  alerta=1; }
        if(zona[i].pm25> LIMITE_PM25){ printf(" PM25 alto: %.2f\n", zona[i].pm25);alerta=1; }
        if(!alerta) printf(" Todos los niveles normales.\n");
    }
}

int cargarZonas(struct Zona zona[]) {
    FILE *archivo = fopen("zonas.dat","rb");
    if(!archivo) return 0;
    int contador=0;
    while(fread(&zona[contador], sizeof(struct Zona),1,archivo)==1){
        contador++;
        if(contador>=100) break;
    }
    fclose(archivo);
    return contador;
}

void guardarZonas(struct Zona zona[], int contador) {
    FILE *archivo = fopen("zonas.dat","wb");
    if(!archivo){
        printf("Error guardando zonas.dat\n");
        return;
    }
    fwrite(zona, sizeof(struct Zona), contador, archivo);
    fclose(archivo);
}


void verRecomendaciones(struct Zona zona[], int contador) {
    char buscar[50];
    int i;
    printf("Ingrese nombre de zona para ver recomendaciones: ");
    scanf("%s", buscar);
    for (i = 0; i < contador; i++) {
        if (strcmp(zona[i].nombre, buscar) == 0) {
            printf("\nRecomendaciones para zona: %s\n", zona[i].nombre);
            int anyAlerta = 0;
            if (zona[i].co2  > LIMITE_CO2) {
                printf("- CO2 alto: mejorar ventilacion interior y reducir actividad fisica\n");
                anyAlerta = 1;
            }
            if (zona[i].so2  > LIMITE_SO2) {
                printf("- SO2 alto: evitar areas industriales y trafico intenso\n");
                anyAlerta = 1;
            }
            if (zona[i].no2  > LIMITE_NO2) {
                printf("- NO2 alto: usar mascarilla al aire libre y limitar tiempo fuera\n");
                anyAlerta = 1;
            }
            if (zona[i].pm25 > LIMITE_PM25) {
                printf("- PM2.5 alto: usar purificador de aire o filtros HEPA\n");
                anyAlerta = 1;
            }
            if (!anyAlerta) {
                printf("Todos los niveles estan dentro de rangos recomendados\n");
            }
            return;
        }
    }
    printf("Zona '%s' no encontrada\n", buscar);
}



void generarReporteInteractivo(struct Zona zonas[], int contador) {
    int disponibles = 0;

    printf("\nZonas con datos actuales disponibles:\n");
    for (int i = 0; i < contador; i++) {
        if (zonas[i].co2 > 0 || zonas[i].so2 > 0 || zonas[i].no2 > 0 || zonas[i].pm25 > 0) {
            printf("- %s\n", zonas[i].nombre);
            disponibles++;
        }
    }

    if (disponibles == 0) {
        printf("No hay zonas con datos actuales para generar reporte.\n");
        return;
    }

    char nombre[50];
    printf("\nIngrese el nombre exacto de gla zona para generar el reporte: ");
    scanf("%s", nombre);

    for (int i = 0; i < contador; i++) {
        if (strcmp(zonas[i].nombre, nombre) == 0) {
            if (zonas[i].co2 == 0 && zonas[i].so2 == 0 && zonas[i].no2 == 0 && zonas[i].pm25 == 0) {
                printf("Esa zona no tiene datos actuales suficientes.\n");
                return;
            }
            generarReporteZonaTXT(&zonas[i]);

            return;
        }
    }

    printf("Zona no encontrada.\n");
}
void generarReporteZonaTXT(struct Zona *z) {
    char fileName[64];
    snprintf(fileName, sizeof(fileName), "reporte_%s.txt", z->nombre);

    FILE *f = fopen(fileName, "w");
    if (!f) {
        printf("Error al crear el archivo %s\n", fileName);
        return;
    }

    fprintf(f, "===== REPORTE DE ZONA =====\n");
    fprintf(f, "Nombre: %s\n", z->nombre);
    fprintf(f, "Pais: %s\n", z->pais);
    fprintf(f, "Ubicacion: %s\n\n", z->ubicacion);

    fprintf(f, "--- Niveles actuales de contaminantes ---\n");
    fprintf(f, "CO2: %.2f ppm\n", z->co2);
    fprintf(f, "SO2: %.2f ug/m3\n", z->so2);
    fprintf(f, "NO2: %.2f ug/m3\n", z->no2);
    fprintf(f, "PM2.5: %.2f ug/m3\n\n", z->pm25);

    fprintf(f, "--- Condiciones climaticas ---\n");
    fprintf(f, "Temperatura: %.2f C\n", z->temperatura);
    fprintf(f, "Viento: %.2f km/h\n", z->viento);
    fprintf(f, "Humedad: %.2f %%\n\n", z->humedad);

    fprintf(f, "--- Predicciones ---\n");

    float predDia[4], predSemana[4];
    predDia[0] = predecir5(z->historicoCO2, z->co2, z->temperatura, z->viento, z->humedad, 0.1f);
    predDia[1] = predecir5(z->historicoSO2, z->so2, z->temperatura, z->viento, z->humedad, 0.5f);
    predDia[2] = predecir5(z->historicoNO2, z->no2, z->temperatura, z->viento, z->humedad, 0.4f);
    predDia[3] = predecir5(z->historicoPM25, z->pm25, z->temperatura, z->viento, z->humedad, 0.8f);

    for (int i = 0; i < 4; i++) predSemana[i] = predDia[i];

    fprintf(f, "Prediccion a 1 dia:\n");
    fprintf(f, "CO2: %.2f ppm\n", predDia[0]);
    fprintf(f, "SO2: %.2f ug/m3\n", predDia[1]);
    fprintf(f, "NO2: %.2f ug/m3\n", predDia[2]);
    fprintf(f, "PM2.5: %.2f ug/m3\n\n", predDia[3]);

    fprintf(f, "Prediccion a 1 semana:\n");
    fprintf(f, "CO2: %.2f ppm\n", predSemana[0]);
    fprintf(f, "SO2: %.2f ug/m3\n", predSemana[1]);
    fprintf(f, "NO2: %.2f ug/m3\n", predSemana[2]);
    fprintf(f, "PM2.5: %.2f ug/m3\n\n", predSemana[3]);

    fprintf(f, "--- Alertas ---\n");
    if (z->co2 > LIMITE_CO2) fprintf(f, "- CO2 alto\n");
    if (z->so2 > LIMITE_SO2) fprintf(f, "- SO2 alto\n");
    if (z->no2 > LIMITE_NO2) fprintf(f, "- NO2 alto\n");
    if (z->pm25 > LIMITE_PM25) fprintf(f, "- PM2.5 alto\n");
    if (z->co2 <= LIMITE_CO2 && z->so2 <= LIMITE_SO2 && z->no2 <= LIMITE_NO2 && z->pm25 <= LIMITE_PM25)
        fprintf(f, "Todos los niveles estan dentro de limites normales.\n");

    fclose(f);
    printf("Reporte TXT generado: %s\n", fileName);
}
