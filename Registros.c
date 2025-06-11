#include "Registros.h"


void CrearJSON(grupo* pGrupo){
/***
Recibe un puntero a grupo ->Grupo ya almacena el nombre y la lista final
***/

    // Crear objeto raíz
    cJSON *raiz = cJSON_CreateObject();
    // Crear array "jugadores"
    cJSON *jugadores = cJSON_CreateArray();

    //Variables para obtener fecha y nombre
    char fecha[TAM_FECHA];
    char nombreArchivo[TAM_NOMBRE];


    // Agregar el nombre del grupo
    cJSON_AddStringToObject(raiz, "codigoGrupo", pGrupo->nombreGrupo);
    // Recorre la lista y agrega a los jugadores al array
    AgregarJugadores(pGrupo->jugadores, jugadores);
    // Cargo el array en la raiz
    cJSON_AddItemToObject(raiz, "jugadores", jugadores);

    // Genero el nombre del json
    ObtenerFecha(fecha, TAM_FECHA, 0);
    strcpy(nombreArchivo, "informe_juego_");
    strcat(nombreArchivo, fecha);
    strcat(nombreArchivo, ".json");


    // Convertir a string y guardar
    char *json = cJSON_Print(raiz); // Para formato legible
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo) {
        fputs(json, archivo);
        fclose(archivo);
    }

    // Liberar memoria
    free(json);
    cJSON_Delete(raiz);


}

void AgregarJugadores(tLista *lJugadores, cJSON *aJugadores) {

    char fecha[TAM_FECHA];
    jugador aux;
    jugador *pAux;

    pAux = &aux;
    ObtenerFecha(fecha, TAM_FECHA, 1);

    while(!ListaVacia(lJugadores)){
    SacarPrimeroLista(lJugadores, pAux);

    cJSON *jugador = cJSON_CreateObject();
    cJSON_AddStringToObject(jugador, "nombre", aux.nombre);
    cJSON_AddNumberToObject(jugador, "puntos", aux.puntos);
    cJSON_AddStringToObject(jugador, "fechaUltimaPartida", fecha);

    cJSON_AddItemToArray(aJugadores, jugador);
    }
}

void ObtenerFecha(char *fecha, int tam, int formato){
/**
**FORMATO == 0 --> para el nombre del archivo
**FORMATO == 1 --> para la hora de los jugadores
**/
    time_t t;
    struct tm *tm_info;

    t = time(NULL);
    tm_info = localtime(&t); // Obtiene la fecha y hora local

    if (formato == 0){
        strftime(fecha, sizeof(tam), "%Y-%m-%d-%H-%M", tm_info);
    }else if(formato == 1){
        strftime(fecha, sizeof(tam), "%d/%m/%Y %H:%M:%S", tm_info);
    }
}


void RecuperarDatos(grupo *pGrupo, const char *nombreArchivo){

    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return;
    }

    // Leer archivo completo en un buffer
    fseek(archivo, 0, SEEK_END);
    long tamanio = ftell(archivo);
    rewind(archivo);

    char *contenido = (char *)malloc(tamanio + 1);
    if (!contenido) {
        fclose(archivo);
        return;
    }

    fread(contenido, 1, tamanio, archivo);
    contenido[tamanio] = '\0';
    fclose(archivo);

    // Parsear JSON
    cJSON *raiz = cJSON_Parse(contenido);
    free(contenido);

    if (!raiz) return;

    // Inicializar estructura grupo
    pGrupo->jugadores = (tLista *)malloc(sizeof(tLista));
    CrearLista(pGrupo->jugadores);
    pGrupo->totalPuntos = 0;
    pGrupo->cantJugadores = 0;

    // Obtener nombre del grupo
    cJSON *codigoGrupo = cJSON_GetObjectItemCaseSensitive(raiz, "codigoGrupo");
    if (!cJSON_IsString(codigoGrupo)) {
        cJSON_Delete(raiz);
        return;
    }
    strncpy(pGrupo->nombreGrupo, codigoGrupo->valuestring, TAMTEXTO);

    // Obtener array de jugadores
    cJSON *jugadores = cJSON_GetObjectItemCaseSensitive(raiz, "jugadores");
    if (cJSON_IsArray(jugadores)) {
        cJSON *item;
        cJSON_ArrayForEach(item, jugadores) {
            jugador j;
            cJSON *nombre = cJSON_GetObjectItemCaseSensitive(item, "nombre");
            cJSON *puntos = cJSON_GetObjectItemCaseSensitive(item, "puntos");

            if (cJSON_IsString(nombre) && cJSON_IsNumber(puntos)) {
                strncpy(j.nombre, nombre->valuestring, TAMTEXTO);
                j.puntos = puntos->valueint;

                PonerAlFinal(pGrupo->jugadores, &j, sizeof(jugador));
                pGrupo->totalPuntos += j.puntos;
                pGrupo->cantJugadores++;
            }
        }
    }

    cJSON_Delete(raiz);
}

/***
Todavia falta la implementacion con la API
Verificar si el grupo ya existe y si es asi modificar los puntos para el jugador existe o crear al jugador en el grupo
Modificar la funcion que obtiene los datos ya que la API no devuelve un archivo.json sino directamente el string
***/


