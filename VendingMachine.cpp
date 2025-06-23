#include "VendingMachine.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
#include <iomanip> // ¡NUEVO! Necesario para std::put_time

VendingMachine::VendingMachine() : saldo_usuario(0.0) {
    logFile.open("vending_machine.log", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de log." << std::endl;
    }
    log("Vending Machine inicializada.");

    productos.emplace("Coca-Cola 500ml", Producto("Coca-Cola 500ml", 6.00, 5));
    productos.emplace("Pepsi 500ml", Producto("Pepsi 500ml", 4.50, 3));
    productos.emplace("Agua 500ml", Producto("Agua 500ml", 5.00, 10));
    productos.emplace("Papitas Lays", Producto("Papitas Lays", 4.00, 7));
    productos.emplace("Gomitas 30g", Producto("Gomitas 30g", 3.00, 8));
    productos.emplace("Coca-Cola peque 300ml", Producto("Coca-Cola peque 300ml", 3.50, 4));
    productos.emplace("Caja Sorpresa", Producto("Caja Sorpresa", 99.99, 1));
    productos.emplace("Galletas Oreo", Producto("Galletas Oreo", 4.00, 6));

    log("Productos cargados.");
}

VendingMachine::~VendingMachine() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void VendingMachine::log(const std::string& message) {
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        logFile << "[LOG " << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "] " << message << std::endl;
    }
}

void VendingMachine::agregarProducto(const Producto& producto) {
    std::lock_guard<std::mutex> lock(mtx);
    productos.emplace(producto.obtNombre(), producto);
    log("Producto agregado: " + producto.obtNombre());
}

void VendingMachine::mostrarMenu() {
    std::cout << "\n¡Hola!, ¿qué te apetece comprar hoy? \n";
    std::cout << "Contactar al numero de referencia en caso de falla" << std::endl;
    std::cout << "Los productos que tenemos disponibles son:" << std::endl;
    int i = 1;
    for (const auto& pair : productos) {
        if (pair.second.obtStock() > 0) {
            std::cout << i++ << ". " << pair.second.obtNombre() << " - Bs. "
                      << pair.second.obtPrecio() << " (Stock: " << pair.second.obtStock() << ")" << std::endl;
        } else {
            std::cout << i++ << ". " << pair.second.obtNombre() << " - Bs. "
                      << pair.second.obtPrecio() << " (AGOTADO)" << std::endl;
        }
    }
    log("Menú mostrado.");
}

void VendingMachine::procesarCompra(const std::string& nombreProducto, double dineroIngresado) {
    std::lock_guard<std::mutex> lock(mtx);

    log("Intentando procesar compra de: " + nombreProducto + " con dinero: " + std::to_string(dineroIngresado));

    auto it = productos.find(nombreProducto);
    if (it == productos.end()) {
        log("Error: Producto '" + nombreProducto + "' no encontrado.");
        throw ProductoNoDisponibleException();
    }

    Producto& producto = it->second;

    if (producto.obtStock() <= 0) {
        log("Error: Producto '" + nombreProducto + "' agotado.");
        throw ProductoNoDisponibleException();
    }

    if (dineroIngresado < producto.obtPrecio()) {
        log("Error: Dinero insuficiente para '" + nombreProducto + "'. Necesita Bs." + std::to_string(producto.obtPrecio()));
        throw DineroInsuficienteException();
    }

    producto.reducirStock();
    double cambio = dineroIngresado - producto.obtPrecio();
    saldo_usuario += producto.obtPrecio();

    std::cout << "Dispensando " << producto.obtNombre() << std::endl;
    std::cout << "Su cambio es: Bs." << cambio << std::endl;
    log("Compra exitosa: " + producto.obtNombre() + ". Cambio: " + std::to_string(cambio));
}

void VendingMachine::devolverCambio() {
    std::lock_guard<std::mutex> lock(mtx);
    if (saldo_usuario > 0) {
        std::cout << "Devolviendo Bs." << saldo_usuario << " de saldo restante." << std::endl;
        log("Devolviendo saldo restante: " + std::to_string(saldo_usuario));
        saldo_usuario = 0;
    }
}

void VendingMachine::iniciar() {
    double dineroInicial;
    std::cout << "Por favor, ingrese su dinero inicial (Bs.): ";
    while (!(std::cin >> dineroInicial) || dineroInicial < 0) {
        std::cout << "Entrada inválida. Ingrese una cantidad de dinero válida: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer

    while (true) {
        mostrarMenu();
        std::string seleccionNombre;
        std::cout << "Seleccione un producto por nombre (o 'salir' para finalizar, 'cambio' para devolver dinero): ";
        std::getline(std::cin >> std::ws, seleccionNombre);

        if (seleccionNombre == "salir") {
            devolverCambio();
            std::cout << "Gracias por usar la máquina expendedora, ¡Ten un gran día!" << std::endl;
            log("Sesión finalizada por el usuario.");
            break;
        } else if (seleccionNombre == "cambio") {
            devolverCambio();
            continue;
        }

        double dineroParaEstaCompra;
        std::cout << "Ingrese dinero para " << seleccionNombre << ": ";
        while (!(std::cin >> dineroParaEstaCompra) || dineroParaEstaCompra < 0) {
            std::cout << "Entrada inválida. Ingrese una cantidad de dinero válida: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer

        try {
            procesarCompra(seleccionNombre, dineroParaEstaCompra);
        } catch (const DineroInsuficienteException& e) {
            std::cout << "Error: " << e.what() << std::endl;
            log("Error de compra: " + std::string(e.what()));
        } catch (const ProductoNoDisponibleException& e) {
            std::cout << "Error: " << e.what() << std::endl;
            log("Error de compra: " + std::string(e.what()));
        } catch (const OpcionInvalidaException& e) {
            std::cout << "Error: " << e.what() << std::endl;
            log("Error de compra: " + std::string(e.what()));
        } catch (const std::exception& e) {
            std::cout << "Ocurrió un error inesperado: " << e.what() << std::endl;
            log("Error inesperado: " + std::string(e.what()));
        }
        std::cout << "\nPresione Enter para continuar...";
        std::cin.get();
    }
}