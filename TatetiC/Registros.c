#include "Registros.h"
#include <curl/curl.h>

void POST_API(char*);

void CrearJSON(tLista* pJugadores){
/***
Recibe un puntero a una lista de jugadores
***/

    // Crear objeto raíz
    cJSON *raiz = cJSON_CreateObject();
    // Crear array "jugadores"
    cJSON *jugadores = cJSON_CreateArray();

    //Variables para obtener fecha y nombre
    char fecha[TAM_FECHA];
    char nombreArchivo[TAM_NOMBRE];


    // Agregar el nombre del grupo
    cJSON_AddStringToObject(raiz, "codigoGrupo", "direccion"); //Direccion debe ser leido desde un archivo
    // Recorre la lista y agrega a los jugadores al array
    AgregarJugadores(pJugadores, jugadores);
    // Cargo el array en la raiz
    cJSON_AddItemToObject(raiz, "jugadores", jugadores);

    // Genero el nombre del json
    ObtenerFecha(fecha, TAM_FECHA);
    strcpy(nombreArchivo, "informe_juego_");
    strcat(nombreArchivo, fecha);
    strcat(nombreArchivo, ".txt");


    // Convertir a string y guardar
    char *json = cJSON_Print(raiz); // Para formato legible
    FILE *archivo = fopen(nombreArchivo, "w"); //ACA FALTA VALIDAR SI SE ABRIO BIEN EL ARCHIVO
    if (archivo) {
        fputs(json, archivo);
        fclose(archivo);
    }

    POST_API(json);

    // Liberar memoria
    free(json);
    cJSON_Delete(raiz);


}

void AgregarJugadores(tLista *lJugadores, cJSON *aJugadores) {
    jugador aux;
    jugador *pAux;

    pAux = &aux;

    while(!ListaVacia(lJugadores)){
    SacarPrimeroLista(lJugadores, pAux);
    cJSON *jugador = cJSON_CreateObject();
    cJSON_AddStringToObject(jugador, "nombre", aux.nombre);
    cJSON_AddNumberToObject(jugador, "puntos", aux.puntos);

    cJSON_AddItemToArray(aJugadores, jugador);
    }
}

void ObtenerFecha(char *fecha, size_t tam){


    time_t t;
    struct tm *tm_info;

    t = time(NULL);
    tm_info = localtime(&t); // Obtiene la fecha y hora local

    strftime(fecha, tam, "%Y-%m-%d-%H-%M", tm_info);

    return;
}


//Struct para WriteCallBack
typedef struct {
    char *buffer;
    size_t size;
} ResponseData;

// Función que maneja la respuesta de la solicitud HTTP para el GET
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    ResponseData *resp = (ResponseData *)userp;

    char *new_buffer = realloc(resp->buffer, resp->size + realsize + 1);
    if (!new_buffer) return 0;

    resp->buffer = new_buffer;
    memcpy(&(resp->buffer[resp->size]), contents, realsize);
    resp->size += realsize;
    resp->buffer[resp->size] = '\0';

    return realsize;
}

char* GET_API(void)
{
    CURL *curl;
    CURLcode res;
    ResponseData response = {NULL, 0};

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://algoritmos-api.azurewebsites.net/api/TaCTi/direccion");

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "X-Secret: FADSFAS");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // solo test
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "Error en la solicitud: %s\n", curl_easy_strerror(res));
            free(response.buffer);
            response.buffer = NULL;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return response.buffer; // esto ahora es el JSON completo (o NULL si falla)
}


void CargarJugadoresDesdeAPI(tLista *lista)
{

    char *json_str = GET_API();
    if (!json_str)
        return;

    cJSON *root = cJSON_Parse(json_str);
    if (!root || !cJSON_IsArray(root))
    {
        free(json_str);
        return;
    }

    jugador jug;
    jugador *pJug = &jug;

    cJSON *item;
    cJSON_ArrayForEach(item, root)
    {
        cJSON *nombre = cJSON_GetObjectItem(item, "nombreJugador");
        cJSON *puntaje = cJSON_GetObjectItem(item, "puntaje");

        if (cJSON_IsString(nombre) && cJSON_IsNumber(puntaje))
        {
            strncpy(pJug->nombre, nombre->valuestring, sizeof(pJug->nombre));
            pJug->puntos = puntaje->valueint;
            PonerAlFinal(lista, pJug, sizeof(jugador));
        }
        //MostrarJugador(pJug);
    }

    cJSON_Delete(root);
    free(json_str);
}





void POST_API(char* pJSON)
{
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, "https://algoritmos-api.azurewebsites.net/api/TaCTi");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, pJSON);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); //Esta linea aca no se usa porque el POST no devuelve datos

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "Error en la solicitud: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return;
}






