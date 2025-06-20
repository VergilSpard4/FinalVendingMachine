#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

class Producto{
    private:
        std::string nombre;                                  // Nombre del producto
        double precio;                                       // Precio del producto
    public:
        Producto(const std::string& nombre, double precio);  // Constructor
        std::string obtNombre() const;                       // Obtiene el nombre del producto
        double obtPrecio() const;};                          // Obtiene el precio del producto
#endif                                                       // PRODUCT_H