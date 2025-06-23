#include "Product.h"

Producto::Producto(const std::string& nombre, double precio, int stock)
    : nombre(nombre), precio(precio), stock(stock) {}

std::string Producto::obtNombre() const {
    return nombre;
}

double Producto::obtPrecio() const {
    return precio;
}

int Producto::obtStock() const {
    return stock;
}

void Producto::reducirStock(int cantidad) {
    if (stock >= cantidad) {
        stock -= cantidad;
    } else {
        // En un caso real, esto debería ser una excepción o un error crítico
        // ya que la verificación de stock debería ocurrir antes.
    }
}

void Producto::aumentarStock(int cantidad) {
    stock += cantidad;
}