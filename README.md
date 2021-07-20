El código que resuelve el problema del enunciado está en el archivo main.cpp.
Para compilarlo se debe ejecutar los siguientes comandos 
en la consola.
	mkdir build
	cd build
	cmake ../
	cmake --build .

o ejecutar el comando sh build.sh en la terminal

Al ejecutarlo se le debe pasar un parámetro que indique cuál algoritmo se desea utilizar entre las siguientes opciones:

- VMC : vecino mas cercano
- AGM : arbol generador minimo
- I : insercion

- VMC-TS1 : vecino mas cercano - tabu search 1
- AGM-TS1 : arbol generador minimo - tabu search 1
- I-TS1 : insercion - tabu search 1

- VMC-TS2 : vecino mas cercano - tabu search 2
- AGM-TS2 : arbol generador minimo - tabu search 2
- I-TS2 : insercion - tabu search 2


Además se debe pasar la instancia por entrada estándar. Por ejemplo: 
	cat INST1.txt | ./main VMC
La salida del programa es doble. Por la salida estándar se devuelve lo pedido por el enunciado. Por la STDERR se devuelve el tiempo de ejecución del algoritmo.

La generación de instancias y corrida de experimentos está programada en Python utilizando Jupyter Lab (https://jupyter.org/). Para ver los notebooks se debe instalar Jupyter Labs siguiendo las instrucciones en su web. Se recomienda seguir los pasos de instalación utilizando pip3.