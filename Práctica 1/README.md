# Sistemas Distribuidos
## Práctica 1

---

### Organización de ficheros
- Las carpetas que terminan en `Distr` son los 5 primeros puntos del ejercicio, donde se pide distribuir el código proporcionado en la actividad original.
- Las carpetas que terminan en `Main` son las que contienen el código de la parte "Extra", donde se pide que se mejore el código main con algunas cosas. En mi defensa he de decir que no he tenido tiempo de probar `MultMatrixMain` más allá de ver si compilaba correctamente o no, así que puede que funcione o puede... que no ¯\\\_(ツ)_/¯
- La carpeta que termina en `Local` contiene la parte de 1 punto de Multiplicación de Matrices con datos locales.

### Sobre la implementación
En los primeros intentos que hice estuve utilizando el código que escribimos en su día en clase, con el fichero `Utils`, etc..., pero no hacía más que desesperarme porque -bajo mi punto de vista- no era intuitivo en absoluto lo de tener que hacer *casteo* de valores en todas partes o recibir todo como `char` y luego convertirlo en cada uno de los puntos donde se utilizaban estos métodos. Es por ello que decidí reimplementarlo "a la manera C++" utilizando clases, objetos y herencia de clases.

*A grosso modo*, todas las clases que hacen uso de un *socket* heredan antes o después de la clase `MyConnection`. Esta clase implementa métodos como `send` o `receive`, además de encargarse de cerrar la conexión de manera limpia cuando se destruyen los objetos que la implementan. Ambos métodos pueden aceptar distintos tipos de parámetros dependiendo del ejercicio (`char *`, `int`, `matrix_t`) y se encargan del envío/recepción de éstos de manera completamente transparente para las partes de más alto nivel del código.

En el caso del servidor, decidí implementarlo en una nueva clase `Server` de manera que el `main` quedase limpio. Esta clase `Server` controla todo lo que sucede con el servidor en sí. Se encarga de crear y cerrar el socket en el que el servidor escucha, y cuando un cliente se conecta crea su propio `ClientConnection` y lo mueve a un thread aparte. Además se encarga de "supervisar" todos los *threads* que haya abierto y los cierra cuando es oportuno. Como se puede ver simplemente mirando al fichero `Server.h` es una clase bastante grande, pero esto se debe en gran parte al uso de *threads* y, por consiguiente, al uso de *locks*/*mutex* para evitar el acceso simultáneo de lectura/escritura a variables.

### Otros Comentarios
Sé que los programas no son perfectos ni de lejos. Se crashean cuando reciben un dato inesperado, y falta mucho control de errores en general; además de que al final he terminado escribiendo ficheros gigantes en lugar de dividirlo en varios más pequeños. Dicho esto, estoy bastante "contento" teniendo en cuenta lo muy apretado de tiempo que ha sido esta práctica.