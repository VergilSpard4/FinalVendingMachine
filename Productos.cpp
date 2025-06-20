#include "libreria_2.h"

Producto::Producto(const std::string& nombre,double precio):nombre(nombre),precio(precio){}   // Inicializa el producto con su nombre y precio

std::string Producto::obtNombre()const{
return nombre;}                                                                                  // Devuelve el nombre del producto

double Producto::obtPrecio()const{
return precio;}                                                                                  // Devuelve el precio del producto
