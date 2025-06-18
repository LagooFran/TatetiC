
# Tateti C : Grupo Puntero

Juego del Tateti implementado en lenguaje C.


![tateti](https://media1.giphy.com/media/v1.Y2lkPTc5MGI3NjExbTdkNnJod3hpZTg4ZzAxaGZsZ3U0dTU2YXUzajFnZWFzeTVuaTRjZCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/mFbaZGgiuHW9FiX2AU/giphy.gif)

## Funciones

- Jugar al tateti en grupos con uno o mas jugadores.
- Ranking online.
- Generacion de resumenes de partida.
- Opciones y API para rankings configurable.


## Requisitos e instalacion

Este programa solamente funciona en sistemas de tipo Windows debido a limitaciones en el funcionamiento de los comandos utilizados para manejar la interfaz por consola. El programa deberia funcionar en sistemas Linux si se borran estas lineas o se cambian por equivalentes para estos sistemas pero no podemos garantizar el funcionamiento correcto de la conexion con la API utilizando curl.


Ademas de windows es necesario instalar las siguientes dependencias:

- Curl https://curl.se/windows/ (El dll de curl viene dentro de la carpeta del programa pero curl debe instalarse y configurarse por separado)

Una vez instalado Curl: 

Abrir el archivo de proyecto .cbp utilizando codeblocks https://www.codeblocks.org/ configurar curl en el entorno de trabajo y compilar el programa desde la interfaz del mismo. 

Durante el desarrollo del programa se utilizo la libreria cJSON https://github.com/DaveGamble/cJSON que ya viene incluida en los archivos.

Verificar que el abrir el archivo de proyecto todos los archivos del programa esten incluidos en el proyecto antes de compilar.

Una vez completados los pasos abrir el programa compilado y a Jugar! Recordar que el archivo config debe estar en el mismo lugar que el ejecutable compilado.




    
## Configuracion

Dentro de la carpeta del programa se encuentra un archivo llamado config.TXT este archivo respeta el siguiente formato:

```
<url de la API>|<codigo de acceso api>
<cantidad de partidas por jugador>
```

Configuracion por defecto:

```
https://algoritmos-api.azurewebsites.net/api/TaCTi|direccion
2
```

