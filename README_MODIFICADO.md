Este proyecto es una simulación de una máquina expendedora escrita en C++.
La máquina expendedora permite a los usuarios seleccionar productos, ingresar dinero y recibir el producto seleccionado si tienen suficiente saldo.
Este código está diseñado para ser fácil de entender y modular, lo que facilita su mantenimiento y expansión.

El proyecto está dividido en varios archivos para organizar mejor el código:
main_vendingmachine.cpp:
Este es el archivo principal que ejecuta la máquina expendedora. 
Aquí se inicializa la máquina y se inicia la interacción con el usuario.
libreria_1.h:
Esta libreria contiene la definición de la clase VendingMachine.
Esa clase maneja la lógica de la máquina expendedora, incluyendo la visualización del menú y la gestión de productos.
Process_vendingmachine.cpp:
Este archivo implementa las funciones de la clase VendingMachine que es la clase para la máquina expendedora.
Se define cómo se comporta la máquina expendedora.
libreria_2.h:
Esta libreria define la clase Producto.
Representa un producto en la máquina expendedora al tener su nombre y precio.
Productos.cpp:
Este archivo implementa las funciones de la clase Producto.
Define cómo se accede a la información del producto en sí.

Para compilar el proyecto de código, se requiere tener instalado un compilador de C++, como g++.
Yo, personalmente utilicé Msys2 mingw64 que encontré en línea.
Abre una terminal como Msys2 de línea de comandos para ejecutar el código.
Navega al directorio donde se encuentran los archivos del proyecto con el comando "cd" si es el cmd.
Ejecuta el siguiente comando para compilar todos los archivos:
g++ main.cpp VendingMachine.cpp Product.cpp -o vending_machine
El comando va a crear un archivo ejecutable con el nombre de vending_machine.exe

Se puede ejecutar la máquina expendedora con el siguiente comando en la terminal:
./vending_machine
Al ejecutar el programa, se te dará la bienvenida a la máquina expendedora y se mostrará un menú con los productos disponibles.
Puedes ingresar la cantidad de dinero que deseas usar y seleccionar un producto ingresando el número correspondiente.
Si tienes suficiente saldo, el producto será dispensado. Caso contrario, no.

Para detallar la arquitectura de los objetos usados se utilizan objetos y clases basado en POO (Programación Orientada a Objetos).

Clase Producto
Atributos:
nombre: Almacena el nombre del producto.
precio: Almacena el precio del producto.
Métodos:
obtNombre(): Devuelve el nombre del producto.
obtPrecio(): Devuelve el precio del producto.

Clase VendingMachine:
Atributos:
productos: Un vector que almacena los productos disponibles en la máquina.
pago_en_efectivo: Almacena el saldo actual del usuario.
Métodos:
mostrarMenu(): Muestra el menú de productos disponibles.
iniciar(): Maneja la lógica de interacción con el usuario, permitiendo seleccionar productos y gestionar el saldo.
agregarProducto(): Agrega un nuevo producto a la máquina expendedora.

El proyecto se puede expandir con más características, como la gestión de inventario y la devolución de cambio.
Sin embargo me faltó profundizar en los temas para agregar esas características.
#############################################################################################################################################################################################################################################
Edit:
Este proyecto es una SIMULACIÓN de una máquina expendedora escrita en C++.
Es decir, el código realiza los pasos de un usuario y de la máquina expendedora.
Ha sido mejorado para cumplir con los requisitos de este proyecto final de programación superior con Estructuras de Datos, Gestión de Errores y Concurrencia.
La máquina expendedora permite a los usuarios seleccionar productos, ingresar dinero y recibir el producto seleccionado si tienen suficiente saldo.

El proyecto está dividido en varios archivos para organizar mejor el código y respetar la modularidad y abstracción:
main.cpp:
Código principal que ejecuta la aplicación de la máquina expendedora.
Incluye una simulación de concurrencia usando std::thread para demostrar el manejo de múltiples clientes interactuando con la máquina simultáneamente, y la protección de race conditions mediante std::mutex.
VendingMachine.h:
Contiene la definición de la clase VendingMachine.
Encapsula, nuevamente, la lógica central de la máquina expendedora, incluyendo la visualización del menú, la gestión de productos, el saldo y las operaciones de compra.
Utiliza excepciones para el manejo de posibles errores y un sistema de logging.
VendingMachine.cpp:
Implementa las funciones de la clase VendingMachine.
Define cómo se comporta la máquina expendedora, incluyendo la interacción con el usuario, la gestión de transacciones y el acceso sincronizado a recursos compartidos.
Product.h:
Define la clase Producto. 
Representa un producto individual en la máquina expendedora, con atributos para su nombre, precio y la cantidad de unidades disponibles.
Product.cpp:
Implementa las funciones de la clase Producto.
Define cómo se accede y se modifica la información del producto.
vending_machine.log:
Archivo de texto donde la máquina registra eventos importantes para el registro de actividad.

Utilización responsable de generación por IA.
La estructura inicial de las clases y la implementación de la concurrencia fueron asistidas por un modelo de lenguaje de IA.
Se utilizó IA para refactorizar la lógica de VendingMachine y añadir el log.
La IA también ayudó a mejorar la documentación y la estructura del código al recomendar pautas de uso y cambios drásticos en el diseño del algoritmo.
Los conocimientos del código son de la persona que lo escribió. Alexander Zhukov Durán De La Riva.

Para compilar el proyecto, se requiere un compilador de C++ que soporte C++11 o superior.
Se recomienda g++ (parte de MinGW-w64 en Windows o GCC en Linux/macOS).
Abre una terminal (por ejemplo, MSYS2 MinGW64).
Hay que estar en el directorio donde se encuentran los archivos del proyecto.
Se debe ejecutar el siguiente comando para compilar todos los archivos:
g++ main.cpp VendingMachine.cpp Product.cpp -o vending_machine -std=c++11 -pthread

Una vez compilado, se puede ejecutar la máquina expendedora con el siguiente comando en la terminal:
./vending_machine
