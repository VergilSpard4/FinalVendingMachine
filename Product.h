#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Producto {
private:
    std::string nombre;
    double precio;
    int stock; // Cantidad de productos disponibles

public:
    Producto(const std::string& nombre, double precio, int stock);
    std::string obtNombre() const;
    double obtPrecio() const;
    int obtStock() const;
    void reducirStock(int cantidad = 1);
    void aumentarStock(int cantidad = 1);
};

#endif // PRODUCT_H