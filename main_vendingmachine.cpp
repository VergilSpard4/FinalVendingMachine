#include <iostream>
#include "libreria_1.h"

int main() {
    VendingMachine vendingMachine;          //Crear una instancia de la máquina expendedora.
    vendingMachine.displayMenu();           //Mostrar el menú de la máquina expendedora.
    vendingMachine.iniciar();               //Ejecutar la máquina expendedora.
    return 0;}