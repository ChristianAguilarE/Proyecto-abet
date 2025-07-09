#include <stdio.h>
#include <string.h>

#define LIMITE_CO2   1000.0f   // ppm
#define LIMITE_SO2     40.0f   // ug/m3
#define LIMITE_NO2     25.0f   // ug/m3
#define LIMITE_PM25    15.0f   // ug/m3

struct Zona {
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

    float historicoCO2[30];
    float historicoSO2[30];
    float historicoNO2[30];
    float historicoPM25[30];
};

int menu();
int submenuIngresarDatos();
void InicializarZonas(struct Zona zona[], int *contador);
void guardarZonas(struct Zona zona[], int contador);
int cargarZonas(struct Zona zona[]);
void verZonas(struct Zona zona[], int contador);
void agregarZona(struct Zona zona[], int *contador);
void modificarZona(struct Zona zona[], int contador);
int cargarHistoricoZona(struct Zona *z);

float predecir5(float historico[30], float hoy, float temperatura, float viento, float humedad, float coef);
void guardarPredicciones(struct Zona zona[], int contador);
void actualizarYVerPredicciones(struct Zona zona[], int contador);
void verDatosHistoricos(struct Zona zona[], int contador);
void verAlertas(struct Zona zona[], int contador);
void verRecomendaciones(struct Zona zona[], int contador);