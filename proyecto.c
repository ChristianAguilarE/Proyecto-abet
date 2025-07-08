#include <stdio.h>
#include <string.h>

#define LIMITE_CO2   1000.0   // ppm
#define LIMITE_SO2     40.0   // µg/m³
#define LIMITE_NO2     25.0   // µg/m³
#define LIMITE_PM25    15.0   // µg/m³

struct Zona
{
    char nombre[50];
    char pais[30];
    char ubicacion[100];

    float co2;
    float so2;
    float no2;
    float pm25;

    float temperatura;
    float viento;
    float humedad;

    float historicoCO2[30], historicoSO2[30], historicoNO2[30], historicoPM25[30];
};

int menu();
int submenuIngresarDatos();
void InicializarZonas(struct Zona zona[], int *contador);
void guardarZonas(struct Zona zona[], int contador);
int cargarZonas(struct Zona zona[]);
void verZonas(struct Zona zona[], int contador);
void agregarZona(struct Zona zona[], int *contador);
void modificarZona(struct Zona zona[], int contador);


float predecir(float historico[30], int dias, float temperatura, float viento, float humedad);
void guardarPredicciones(struct Zona zona[], int contador); // <-- AGREGAR ESTA LÍNEA
void actualizarYVerPredicciones(struct Zona zona[], int contador) ;

void verPredicciones(struct Zona zona[], int contador);
void verDatosHistoricos(struct Zona zona[], int contador);
void verAlertas(struct Zona zona[], int contador);
void verRecomendaciones(struct Zona zona[], int contador);

int main()
{
    struct Zona zona[100];
    int seguir = 1;
    int opc;
    int opcSubmenuIngresarDatos;
    int seguirsubmenuIngresarDatos;
    // CAMBIO: El contador se sincroniza con el archivo al iniciar el programa
    int contador = cargarZonas(zona); // Cargar zonas existentes al iniciar

    while (seguir)
    {
        opc = menu();

        switch (opc)
        {
        case 0:
            InicializarZonas(zona, &contador);
            printf("Zonas inicializadas correctamente.\n");
            break;

        case 1:
            seguirsubmenuIngresarDatos = 1;
            while (seguirsubmenuIngresarDatos)
            {
                opcSubmenuIngresarDatos = submenuIngresarDatos();
                switch (opcSubmenuIngresarDatos)
                {
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
                    seguirsubmenuIngresarDatos = 0;
                    printf("Volviendo al menu principal...\n");
                    break;
                default:
                    printf("Opción no válida.\n");
                    break;
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
            printf("Función recomendaciones aún no implementada.\n");
            break;
        case 6:
            seguir = 0;
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opción no válida.\n");
            break;
        }
    }

    return 0;
}

int menu()
{
    int opcion;
    printf("\n===== MENU PRINCIPAL =====\n");
    printf("0) Inicializar Zonas\n");
    printf("1) Gestionar Zonas\n");
    printf("2) Ver predicciones\n");
    printf("3) Ver datos historicos\n");
    printf("4) Alertas\n");
    printf("5) Recomendaciones\n");
    printf("6) Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    return opcion;
}

int submenuIngresarDatos()
{
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

void InicializarZonas(struct Zona zona[], int *contador)
{
    strcpy(zona[0].nombre, "Quito");
    strcpy(zona[0].pais, "Ecuador");
    strcpy(zona[0].ubicacion, "Ubicacion 1");

    zona[0].co2 = 400.0;
    zona[0].so2 = 10.0;
    zona[0].no2 = 20.0;
    zona[0].pm25 = 15.0;

    zona[0].temperatura = 10.0;
    zona[0].viento = 5.0;
    zona[0].humedad = 60.0;

    strcpy(zona[1].nombre, "Cuenca");
    strcpy(zona[1].pais, "Ecuador");
    strcpy(zona[1].ubicacion, "Ubicacion 2");

    zona[1].co2 = 420.0;
    zona[1].so2 = 15.0;
    zona[1].no2 = 25.0;
    zona[1].pm25 = 15.0;

    zona[1].temperatura = 16.0;
    zona[1].viento = 15.0;
    zona[1].humedad = 60.0;

    strcpy(zona[2].nombre, "Guayaquil");
    strcpy(zona[2].pais, "Ecuador");
    strcpy(zona[2].ubicacion, "Ubicacion 3");

    zona[2].co2 = 430.0;
    zona[2].so2 = 20.0;
    zona[2].no2 = 25.0;
    zona[2].pm25 = 120.0;

    zona[2].temperatura = 25.0;
    zona[2].viento = 15.0;
    zona[2].humedad = 60.0;

    strcpy(zona[3].nombre, "Tulcan");
    strcpy(zona[3].pais, "Ecuador");
    strcpy(zona[3].ubicacion, "Ubicacion 4");

    zona[3].co2 = 430.0;
    zona[3].so2 = 20.0;
    zona[3].no2 = 25.0;
    zona[3].pm25 = 120.0;

    zona[3].temperatura = 25.0;
    zona[3].viento = 15.0;
    zona[3].humedad = 60.0;

    strcpy(zona[4].nombre, "Ibarra");
    strcpy(zona[4].pais, "Ecuador");
    strcpy(zona[4].ubicacion, "Ubicacion 4");

    zona[4].co2 = 430.0;
    zona[4].so2 = 20.0;
    zona[4].no2 = 25.0;
    zona[4].pm25 = 120.0;

    zona[4].temperatura = 25.0;
    zona[4].viento = 15.0;
    zona[4].humedad = 60.0;

    // Simulación de históricos para las 5 zonas iniciales
 for (int i = 0; i < 5; i++) {
    float a = 0.1f, b = 0.5f, c = 0.4f, d = 0.8f;  // coeficientes fijos

    for (int j = 0; j < 30; j++) {
        float variacion = 1.0f + 0.05f * ((j % 5) - 2); // Variación de -10% a +10%

        float co2  = zona[i].co2  * variacion;
        float so2  = zona[i].so2  * variacion;
        float no2  = zona[i].no2  * variacion;
        float pm25 = zona[i].pm25 * variacion;

        zona[i].historicoCO2[j]  = a * co2;
        zona[i].historicoSO2[j]  = b * so2;
        zona[i].historicoNO2[j]  = c * no2;
        zona[i].historicoPM25[j] = d * pm25;
    }
}


    *contador = 5;
    guardarZonas(zona, *contador);
}

void guardarZonas(struct Zona zona[], int contador)
{
    FILE *archivo = fopen("zonas.dat", "wb");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }
    fwrite(zona, sizeof(struct Zona), contador, archivo);
    fclose(archivo);
}

int cargarZonas(struct Zona zona[])
{
    FILE *archivo = fopen("zonas.dat", "rb");
    if (archivo == NULL)
        return 0;
    int contador = 0;
    while (fread(&zona[contador], sizeof(struct Zona), 1, archivo) == 1)
    {
        contador++;
        if (contador >= 100) break;
    }
    fclose(archivo);
    return contador;
}

void agregarZona(struct Zona zona[], int *contador)
{
    if (*contador >= 100)
    {
        printf("No se pueden agregar mas zonas.\n");
        return;
    }

    printf("Ingrese el nombre de la zona: ");
    scanf("%s", zona[*contador].nombre);
    printf("Ingrese el pais: ");
    scanf("%s", zona[*contador].pais);
    printf("Ingrese la ubicacion: ");
    scanf("%s", zona[*contador].ubicacion);

    printf("Ingrese los niveles de contaminantes:\n");
    printf("CO2 (ppm): ");
    scanf("%f", &zona[*contador].co2);
    printf("SO2 (ug/m3): ");
    scanf("%f", &zona[*contador].so2);
    printf("NO2 (ug/m3): ");
    scanf("%f", &zona[*contador].no2);
    printf("PM2.5 (ug/m3): ");
    scanf("%f", &zona[*contador].pm25);

    printf("Ingrese las condiciones climaticas:\n");
    printf("Temperatura (C): ");
    scanf("%f", &zona[*contador].temperatura);
    printf("Viento (km/h): ");
    scanf("%f", &zona[*contador].viento);
    printf("Humedad (porcentaje): ");
    scanf("%f", &zona[*contador].humedad);

  float a = 0.1f, b = 0.5f, c = 0.4f, d = 0.8f;  // Coeficientes fijos

for (int j = 0; j < 30; j++) {
    float variacion = 1.0f + 0.05f * ((j % 5) - 2); // Variación de -10% a +10%

    float co2  = zona[*contador].co2  * variacion;
    float so2  = zona[*contador].so2  * variacion;
    float no2  = zona[*contador].no2  * variacion;
    float pm25 = zona[*contador].pm25 * variacion;

    zona[*contador].historicoCO2[j]  = a * co2;
    zona[*contador].historicoSO2[j]  = b * so2;
    zona[*contador].historicoNO2[j]  = c * no2;
    zona[*contador].historicoPM25[j] = d * pm25;
}


    (*contador)++;
    guardarZonas(zona, *contador);
}

void verZonas(struct Zona zona[], int contador)
{
    printf("\n%-4s %-15s %-12s %-15s %-8s %-8s %-8s %-10s %-12s %-10s %-10s\n",
           "No.", "Nombre", "Pais", "Ubicacion", "CO2", "SO2", "NO2", "PM2.5", "Temp (C)", "Viento", "Humedad");
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < contador; i++)
    {
        printf("%-4d %-15s %-12s %-15s %-8.2f %-8.2f %-8.2f %-10.2f %-12.2f %-10.2f %-10.2f\n",
               i + 1,
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
    int i, opcion;
    if (contador == 0) {
        printf("No hay zonas para modificar.\n");
        return;
    }

    printf("\nZonas registradas:\n");
    for (i = 0; i < contador; i++) {
        printf("%d) %s, %s, %s\n", i + 1, zona[i].nombre, zona[i].pais, zona[i].ubicacion);
    }
    printf("Seleccione el numero de la zona a modificar (1-%d): ", contador);
    scanf("%d", &opcion);

    if (opcion < 1 || opcion > contador) {
        printf("Opcion invalida.\n");
        return;
    }
    i = opcion - 1;

    printf("Modificando zona: %s\n", zona[i].nombre);

    printf("Nuevo nombre (actual: %s): ", zona[i].nombre);
    scanf("%s", zona[i].nombre);
    printf("Nuevo pais (actual: %s): ", zona[i].pais);
    scanf("%s", zona[i].pais);
    printf("Nueva ubicaciin (actual: %s): ", zona[i].ubicacion);
    scanf("%s", zona[i].ubicacion);

    printf("Nuevos niveles de contaminantes:\n");
    printf("CO2 (ppm) (actual: %.2f): ", zona[i].co2);
    scanf("%f", &zona[i].co2);
    printf("SO2 (ug/m3) (actual: %.2f): ", zona[i].so2);
    scanf("%f", &zona[i].so2);
    printf("NO2 (ug/m3) (actual: %.2f): ", zona[i].no2);
    scanf("%f", &zona[i].no2);
    printf("PM2.5 (ug/m3) (actual: %.2f): ", zona[i].pm25);
    scanf("%f", &zona[i].pm25);

    printf("Nuevas condiciones climáticas:\n");
    printf("Temperatura (C) (actual: %.2f): ", zona[i].temperatura);
    scanf("%f", &zona[i].temperatura);
    printf("Viento (km/h) (actual: %.2f): ", zona[i].viento);
    scanf("%f", &zona[i].viento);
    printf("Humedad (porcentaje) (actual: %.2f): ", zona[i].humedad);
    scanf("%f", &zona[i].humedad);

    guardarZonas(zona, contador);
    printf("Zona modificada y guardada correctamente.\n");
}


/*void verPredicciones(struct Zona zona[], int contador) {
    char buscar[50];
    int encontrada = 0;



    printf("Ingrese el nombre de la zona para ver las predicciones: ");
    scanf("%s", buscar);

    for (int i = 0; i < contador; i++) {
        if (strcmp(zona[i].nombre, buscar) == 0) {
            printf("\nZONA: %s\n", zona[i].nombre);
            printf("Pais: %s\n", zona[i].pais);
            printf("Ubicacion: %s\n", zona[i].ubicacion);

            printf("\n--- Prediccion para 1 dia ---\n");
            printf("CO2: %.2f ppm\n", predecir(zona[i].historicoCO2, 1, zona[i].temperatura, zona[i].viento, zona[i].humedad));
            printf("SO2: %.2f ug/m3\n", predecir(zona[i].historicoSO2, 1, zona[i].temperatura, zona[i].viento, zona[i].humedad));
            printf("NO2: %.2f ug/m3\n", predecir(zona[i].historicoNO2, 1, zona[i].temperatura, zona[i].viento, zona[i].humedad));
            printf("PM2.5: %.2f ug/m3\n", predecir(zona[i].historicoPM25, 1, zona[i].temperatura, zona[i].viento, zona[i].humedad));

            printf("\n--- Prediccion para 1 semana ---\n");
            printf("CO2: %.2f ppm\n", predecir(zona[i].historicoCO2, 7, zona[i].temperatura, zona[i].viento, zona[i].humedad));
            printf("SO2: %.2f ug/m3\n", predecir(zona[i].historicoSO2, 7, zona[i].temperatura, zona[i].viento, zona[i].humedad));
            printf("NO2: %.2f ug/m3\n", predecir(zona[i].historicoNO2, 7, zona[i].temperatura, zona[i].viento, zona[i].humedad));
            printf("PM2.5: %.2f ug/m3\n", predecir(zona[i].historicoPM25, 7, zona[i].temperatura, zona[i].viento, zona[i].humedad));

            printf("\n--- Prediccion para 1 mes ---\n");
            printf("CO2: %.2f ppm\n", predecir(zona[i].historicoCO2, 30, zona[i].temperatura, zona[i].viento, zona[i].humedad));
            printf("SO2: %.2f ug/m3\n", predecir(zona[i].historicoSO2, 30, zona[i].temperatura, zona[i].viento, zona[i].humedad));
            printf("NO2: %.2f ug/m3\n", predecir(zona[i].historicoNO2, 30, zona[i].temperatura, zona[i].viento, zona[i].humedad));
            printf("PM2.5: %.2f ug/m3\n", predecir(zona[i].historicoPM25, 30, zona[i].temperatura, zona[i].viento, zona[i].humedad));

            encontrada = 1;
            break;
        }
    }
    if (!encontrada) {
        printf("Zona no encontrada.\n");
    }
}*/

float predecir(float historico[30], int dias, float temperatura, float viento, float humedad) {
    if (dias > 30) dias = 30;
    float suma = 0;
    for (int i = 30 - dias; i < 30; i++) suma += historico[i];
    float promedio = suma / dias;

    // Ajuste simple
    float ajuste = promedio;
    if (temperatura > 20) ajuste += promedio * 0.005f * (temperatura - 20);
    if (viento > 10) ajuste -= promedio * 0.01f * ((viento - 10) / 5.0f);
    if (humedad > 50) ajuste -= promedio * 0.002f * ((humedad - 50) / 5.0f);

    return ajuste;
}

void verDatosHistoricos(struct Zona zona[], int contador){

char buscar[50];
int encontrado=0;
printf("\n INGRESE EN EL NOMBRE DE LA ZONA PARA VER LOS DATOS HISTORICOS: ");
scanf("%s", buscar);

for (int i = 0; i < contador; i++)
{
    if (strcmp(zona[i].nombre, buscar) == 0)
    {
        encontrado = 1;
        printf("\nZONA: %s\n", zona[i].nombre);
        printf("Pais: %s\n", zona[i].pais);
        printf("Ubicacion: %s\n", zona[i].ubicacion);

        printf("\n--- Datos Historicos ---\n");
        printf("******CO2 (ppm)*******: ");
        for (int j = 0; j < 30; j++) {
            printf("\nDia %d) %.2f ",j,zona[i].historicoCO2[j]);
        }
        printf("\n");

        printf("*******SO2 (ug/m3)******: ");
        for (int j = 0; j < 30; j++) {
            printf("\nDia %d)%.2f ",j, zona[i].historicoSO2[j]);
        }
        printf("\n");

        printf("*******NO2 (ug/m3)******: ");
        for (int j = 0; j < 30; j++) {
            printf("\nDia %d)%.2f ",j, zona[i].historicoNO2[j]);
        }
        printf("\n");

        printf("********PM2.5 (ug/m3)******: ");
        for (int j = 0; j < 30; j++) {
            printf("\nDia %d)%.2f ",j, zona[i].historicoPM25[j]);
        }
        printf("\n");

        return;
    }
   
    if (!encontrado)
    {
        printf("Zona no encontrada.\n");
    }
    
    
}
}

void verAlertas(struct Zona zona[], int contador) {
    for (int i = 0; i < contador; i++) {
        printf("\nZona: %s\n", zona[i].nombre);

        int alerta = 0;

        if (zona[i].co2 > LIMITE_CO2) {
            printf("   Alerta: Nivel de CO2 peligroso (%.2f ppm)\n", zona[i].co2);
            alerta = 1;
        }

        if (zona[i].so2 > LIMITE_SO2) {
            printf("   Alerta: Nivel de SO2 peligroso (%.2f ug/m3)\n", zona[i].so2);
            alerta = 1;
        }

        if (zona[i].no2 > LIMITE_NO2) {
            printf("    Alerta: Nivel de NO2 peligroso (%.2f ug/m3)\n", zona[i].no2);
            alerta = 1;
        }

        if (zona[i].pm25 > LIMITE_PM25) {
            printf("    Alerta: Nivel de PM2.5 peligroso (%.2f ug/m3)\n", zona[i].pm25);
            alerta = 1;
        }

        if (!alerta) {
            printf("   Todos los niveles estan dentro de lo normal.\n");
        }
    }
} 



void guardarPredicciones(struct Zona zona[], int contador) {
    FILE *archivo = fopen("predicciones.dat", "wb"); // sobrescribe
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar predicciones.\n");
        return;
    }

    for (int i = 0; i < contador; i++) {
        // 1 día
        float predCO2_d1 = predecir(zona[i].historicoCO2, 1, zona[i].temperatura, zona[i].viento, zona[i].humedad);
        float predSO2_d1 = predecir(zona[i].historicoSO2, 1, zona[i].temperatura, zona[i].viento, zona[i].humedad);
        float predNO2_d1 = predecir(zona[i].historicoNO2, 1, zona[i].temperatura, zona[i].viento, zona[i].humedad);
        float predPM25_d1 = predecir(zona[i].historicoPM25, 1, zona[i].temperatura, zona[i].viento, zona[i].humedad);

        // 1 semana
        float predCO2_7 = predecir(zona[i].historicoCO2, 7, zona[i].temperatura, zona[i].viento, zona[i].humedad);
        float predSO2_7 = predecir(zona[i].historicoSO2, 7, zona[i].temperatura, zona[i].viento, zona[i].humedad);
        float predNO2_7 = predecir(zona[i].historicoNO2, 7, zona[i].temperatura, zona[i].viento, zona[i].humedad);
        float predPM25_7 = predecir(zona[i].historicoPM25, 7, zona[i].temperatura, zona[i].viento, zona[i].humedad);

        // 1 mes
        float predCO2_30 = predecir(zona[i].historicoCO2, 30, zona[i].temperatura, zona[i].viento, zona[i].humedad);
        float predSO2_30 = predecir(zona[i].historicoSO2, 30, zona[i].temperatura, zona[i].viento, zona[i].humedad);
        float predNO2_30 = predecir(zona[i].historicoNO2, 30, zona[i].temperatura, zona[i].viento, zona[i].humedad);
        float predPM25_30 = predecir(zona[i].historicoPM25, 30, zona[i].temperatura, zona[i].viento, zona[i].humedad);

        fwrite(zona[i].nombre, sizeof(char), 50, archivo);
        fwrite(&predCO2_d1, sizeof(float), 1, archivo);
        fwrite(&predSO2_d1, sizeof(float), 1, archivo);
        fwrite(&predNO2_d1, sizeof(float), 1, archivo);
        fwrite(&predPM25_d1, sizeof(float), 1, archivo);

        fwrite(&predCO2_7, sizeof(float), 1, archivo);
        fwrite(&predSO2_7, sizeof(float), 1, archivo);
        fwrite(&predNO2_7, sizeof(float), 1, archivo);
        fwrite(&predPM25_7, sizeof(float), 1, archivo);

        fwrite(&predCO2_30, sizeof(float), 1, archivo);
        fwrite(&predSO2_30, sizeof(float), 1, archivo);
        fwrite(&predNO2_30, sizeof(float), 1, archivo);
        fwrite(&predPM25_30, sizeof(float), 1, archivo);
    }

    fclose(archivo);
   
}




void actualizarYVerPredicciones(struct Zona zona[], int contador) {
    char buscar[50];
    int encontrada = 0;

    printf("Ingrese el nombre de la zona para ver las predicciones guardadas: ");
    scanf("%s", buscar);

    FILE *archivo = fopen("predicciones.dat", "rb");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de predicciones.\n");
        return;
    }

    char nombre[50];
    float pred[12];

    while (fread(nombre, sizeof(char), 50, archivo) == 50 &&
           fread(pred, sizeof(float), 12, archivo) == 12)
    {
        if (strcmp(nombre, buscar) == 0) {
            printf("\n--- PREDICCIONES PARA: %s ---\n", nombre);
            printf("%-10s %-10s %-10s %-10s %-10s\n", "Periodo", "CO2", "SO2", "NO2", "PM2.5");
            printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f\n", "1 dia", pred[0], pred[1], pred[2], pred[3]);
            printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f\n", "1 semana", pred[4], pred[5], pred[6], pred[7]);
            printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f\n", "1 mes", pred[8], pred[9], pred[10], pred[11]);
            encontrada = 1;
            break;
        }
    }

    if (!encontrada) {
        printf("Zona '%s' no encontrada en el archivo de predicciones.\n", buscar);
    }

    fclose(archivo);
}
