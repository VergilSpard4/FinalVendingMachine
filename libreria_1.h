#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H
#include <vector>
#include "libreria_2.h"

class VendingMachine{
private:
    std::vector<Producto> productos;                     // Lista de productos en la máquina.
    double pago_en_efectivo;                             // Balance actual del usuario.
public:
    VendingMachine();                                    // Llamada al constructor de la clase.
    void displayMenu();                                  // Muestra el menú de productos disponibles a comprar.
    void iniciar();                                      // Ejecuta toda la lógica detrás de la máquina para que empiece a funcionar.
    void agregarProducto(const Producto& producto);};    // Agrega el producto que se desee a la máquina.
#endif                                                   // VENDINGMACHINE_H