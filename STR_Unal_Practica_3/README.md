# Practica 3: Introducción a los sistemas en tiempo real con Arduino

La guía de trabajo de esta practica, puede visualizarse [aqui](/media/guia.pdf).

## Desarrollo de la guía ##
Una vez instalado y ejecutado los códigos de ejemplo requeridos para comprender la guía de desarrollo, se procede a dar respuesta a las preguntas realizadas para la elaboración de este trabajo, que empieza a partir de la sección **4.1.1** de la guía.

### 4.1.1: Hilos para abordar tareas. ###
**¿Con cuál método se le hizo más fácil programar las secuencias? ¿Por qué?**

- Es mucho mas simple desarrollar las tareas teniendo presente alguna metodología que permita declararla como ejecuciones independientes, ya que solo estamos interesados en cada una de ellas por separado. Así, para el caso de los leds, es mas facil definir el cómo será la ejecución de cada uno sin preocuparnos como el tiempo afectará a cada uno. Cuando se hace el desarrollo como una sola tarea, es necesario pensar en como vamos a distribuir los tiempos para que se cumpla las tareas programadas, lo que reduce la capacidad de desacoplarlas, pues al momento de realizar un cambio, afectaremos el resto de tareas que dependen de unos tiempos especificados a partir del proceso en el que nos encontramos.
- Un problema generico que se presenta al tratar de hacer varias ejecuciones con un programa secuencial, se encuentra en el momento de querer agregar otras instrucciones adicionales, lo cual no siempre será eficiente, y mucho menos escalable. Cuando existe la posibilidad de crear hilos, estamos delegando estos problemas a un sistema que se encarga de hacer estas distribuciones de tiempos por nosotros. El problema es que estos cambios pueden afectar la sincronía. Con los leds se observa que el desarrollo secuencial garantiza una sincronia entre los encendidos y apagados, pues notamos que hay un punto en las secuencias donde los 3 leds encienden y se apagan, de manera casi uniforme sin perder esta caracteristica. Al hacer el desarrollo por hilos, observamos que esto no ocurre, pues se desfasan los encendidos y apagados que en secuencial, son uniformes. Este resulta ser el precio de trabajar con sistemas con hilos pues, estariamos perdiendo precision en los tiempos por comodidad en la creacion de tareas.

**¿El cambio en la prioridad de los hilos afecta en algo a las tareas programadas?**

- Cuando se hace un cambio en las prioridades, si esta es mayor que las anteriores, las otras no se ejecutarán a menos que el hilo al que hacemos referencia, deje de funcionar. Para probarlo, basta con darle un numero mayor a cualquiera de las tareas, sin importar el periodo de encendido y apagado, y dejar el resto con valores menores. Se observa que la tarea que mas valor tiene, es la unica que se puede observar en el encendido y apagado.

### 4.1.2: Usted si, usted no. ###
La implementación para este punto, se puede encontrar en el archivo [02_you_do_you_dont.ino](/src/project/02_you_do_you_dont/challenge/02_you_do_you_dont.ino) en la ruta `/src/project/02_you_do_you_dont/challenge/02_you_do_you_dont.ino`. El desarrollo de este programa fue a su vez basado en el desarrollo del uso de hilos en posix [1].

**¿Qué pasa con los mensajes cuando no se utilizan semáforos?**

- Para ese caso particular, lo que sucede es que dentro de las instrucciones que se están realizando con el puerto serie enviando datos, envia un fragmento de lo que es la tarea A y lo que envíe la otra tarea B, dando como resultado cualquier cosa, que no puede ser interpretada por el usuario. Para evitar esto, se hace uso de los semáforos. Su funcionamiento resulta ser parecido a un semáforo de tráfico. La tarea que vaya a usar un recurso, lo notifica al semáforo. 

**¿Qué pasa con los mensajes si el semáforo les permite utilizar el recurso “al mismo tiempo”?**
- Tomando como base la respuesta anterior, el problema de usar el recurso al mismo tiempo se pueden dar los siguientes casos:
  - Usar el mismo recurso con semaforo sin soltar el semaforo: En este caso, se llenará el contador interno rápidamente y no podrá ser usado por los otros hilos.
  - Usar el mismo recurso soltando el semaforo: Dos hilos al intentar acceder al semáforo, se tomara un orden de prioridad que podrá ser incluso determinado por el orden de creación. Esto lo podemos ver, en la secuencia de dos hilos diferentes, en el cual se observa el mismo orden, si se maneja el mismo tiempo de retardo y las mismas iteraciones.

**¿Cómo afecta la prioridad a la ejecución de los hilos?**
Al ejecutarse con la misma prioridad, los eventos se pueden alternar entre si el uso del semaforo, aumentando el contador interno cuando esta en uso, y reduciendo el contador cuando no lo está. Si se hace un cambio de prioridades, se ejecuta la tarea que tenga el valor de prioridad mas alto. Se observa que si las tareas tienen un valor de prioridad cercano entre si, no mayor a una unidad, pueden ejecutarse de manera simultanea, pero si el valor de prioridad es muy distante, la tarea solo será ejecutada por aquella que tenga el valor más alto.

**Cambie el comando xSemaphoreCreateCounting(2,1) por xSemaphoreCreateMutex().**
Revisando en la documentacion de FreeRTOS para la función [CreateMutex](https://www.freertos.org/CreateMutex.html) [2], se observa que este llamado permite crear un semaforo con una memoria dinámica, asignándo el tamaño de la misma desde el heap de FreeRTOS.

Un mutex es un objeto de exclusión mutua, similar a un semáforo pero que solo permite un casillero a la vez y cuyas restricciones de propiedad pueden ser más estrictas que un semáforo [3].

En la implementación de esta función, no se encuentra mayor diferencia respecto al uso de semaforos con contadores, exceptuando que en algunos casos se presenta un riesgo de solape entre mensajes tal como se muestra en un ejemplo capturado, usando la misma prioridad entre las tareas:

```
print something.print other...
task 3...
. other...
task 3...
int something.p.
print other...
task 3...
```

La ejecución esperada deberia ser la siguiente:

```
print something...
print other...
task 3...
```

### 4.2: RETO. ###

El archivo asociado, se encuentra puede apreciar en el archivo [03_challenge.ino](/src/project/03_challenge/03_challenge.ino) en la ruta ```/src/project/03_challenge/challenge/challenge.ino```.

## Referencias ##

[1] [Uso de semaforos POSIX](https://www.youtube.com/watch?v=YC61729PThw)
[2] CreateMutex: https://www.freertos.org/CreateMutex.html
[3] When should we use mutex and when should we use semaphore: https://stackoverrun.com/es/q/943334