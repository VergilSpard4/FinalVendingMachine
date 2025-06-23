#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <mutex>
#include <fstream>
#include <stdexcept> // Para std::runtime_error
#include "Product.h" // Incluimos la clase Producto

// Excepciones personalizadas
class DineroInsuficienteException : public std::runtime_error {
public:
    DineroInsuficienteException() : std::runtime_error("Dinero insuficiente.") {}
};

class ProductoNoDisponibleException : public std::runtime_error {
public:
    ProductoNoDisponibleException() : std::runtime_error("Producto no disponible o sin stock.") {}
};

class OpcionInvalidaException : public std::runtime_error {
public:
    OpcionInvalidaException() : std::runtime_error("Opción inválida. Intente de nuevo.") {}
};

class VendingMachine {
private:
    std::unordered_map<std::string, Producto> productos;
    double saldo_usuario;
    std::mutex mtx;
    std::ofstream logFile;

    void log(const std::string& message);

public:
    VendingMachine();
    ~VendingMachine();

    void agregarProducto(const Producto& producto);
    void mostrarMenu();
    void iniciar();
    void procesarCompra(const std::string& nombreProducto, double dineroIngresado);
    void devolverCambio();
};

#endif // VENDINGMACHINE_H