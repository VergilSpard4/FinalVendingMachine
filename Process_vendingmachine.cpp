#include <iostream>
#include "libreria_1.h"

VendingMachine::VendingMachine():pago_en_efectivo(0.0){
    // Prodcutos de la máquina expendedora
    agregarProducto(Producto("Coca-Cola 500ml",6.00));
    agregarProducto(Producto("Pepsi 500ml",4.50));
    agregarProducto(Producto("Agua 500ml",5.00));
    agregarProducto(Producto("Papitas Lays",4.00));
    agregarProducto(Producto("Gomitas 30g",3.00));
    agregarProducto(Producto("Coca-Cola peque 300ml",3.50));
    agregarProducto(Producto("Caja Sorpresa",99.99));
    agregarProducto(Producto("Galletas Oreo",4.00));
    }

void VendingMachine::displayMenu(){
    std::cout<<"¡Hola!, ¿qué te apetece comprar hoy? \n";
    std::cout<<"Contactar al numero de referencia en caso de falla"<<std::endl;
    std::cout<<"Los productos que tenemos disponibles son:"<<std::endl;
    for (size_t i=0; i<productos.size(); ++i) {
        std::cout<<i+1 <<". "<< productos[i].obtNombre() <<" - Bs. "<< productos[i].obtPrecio()<<std::endl;}}

void VendingMachine::iniciar(){
    short num_cliente;
    std::cout<<"Por favor, ingrese su dinero: ";
    std::cin>>pago_en_efectivo;
    while (true) {
        std::cout<<"Seleccione un producto (0 para salir): ";
        std::cin>>num_cliente;

        if (num_cliente==0) {
            std::cout<<"Gracias por usar la máquina expendedora, ¡Ten un gran día!"<<std::endl;
            break;}
            else if(num_cliente > 0 && num_cliente <= productos.size()){
            if(pago_en_efectivo>=productos[num_cliente-1].obtPrecio()){
               pago_en_efectivo-=productos[num_cliente-1].obtPrecio();
               std::cout<<"Dispensando "<<productos[num_cliente-1].obtNombre()<<std::endl;
               std::cout<<"Su saldo restante es: Bs."<<pago_en_efectivo<<std::endl;}
            else{
               std::cout<<"Saldo insuficiente para "<<productos[num_cliente-1].obtNombre()<<std::endl;}}
            else{
               std::cout<<"Opcion no valida. Intente de nuevo."<<std::endl;}}}

void VendingMachine::agregarProducto(const Producto& producto) {
    productos.push_back(producto);}