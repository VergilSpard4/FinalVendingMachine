#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <functional> // Necesario para std::ref
#include "VendingMachine.h"

// Función para simular un cliente interactuando con la máquina
void clienteSimulado(VendingMachine& vm, const std::string& productoDeseado, double dineroCliente) {
    std::cout << "[Cliente Thread] Cliente intentando comprar " << productoDeseado << " con Bs." << dineroCliente << std::endl;
    try {
        vm.procesarCompra(productoDeseado, dineroCliente);
        std::cout << "[Cliente Thread] Compra de " << productoDeseado << " exitosa." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Cliente Thread] Fallo la compra de " << productoDeseado << ": " << e.what() << std::endl;
    }
}

int main() {
    VendingMachine vendingMachine;

    // --- ELIGE UNA OPCIÓN ---
    // Opción 1: Interacción interactiva (descomenta la siguiente línea para activarla)
    // vendingMachine.iniciar();

    // Opción 2: Simulación de Concurrencia (comenta esta sección si usas el modo interactivo)
    std::cout << "\n--- Iniciando Simulación de Concurrencia ---" << std::endl;
    std::cout << "Observa el log (vending_machine.log) y los mensajes para entender los race conditions y su prevencion." << std::endl;

    std::vector<std::thread> clientes;

    clientes.emplace_back(clienteSimulado, std::ref(vendingMachine), "Coca-Cola 500ml", 7.00);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    clientes.emplace_back(clienteSimulado, std::ref(vendingMachine), "Coca-Cola 500ml", 6.50);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    clientes.emplace_back(clienteSimulado, std::ref(vendingMachine), "Papitas Lays", 2.00);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    clientes.emplace_back(clienteSimulado, std::ref(vendingMachine), "Agua 500ml", 10.00);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    clientes.emplace_back(clienteSimulado, std::ref(vendingMachine), "Coca-Cola 500ml", 10.00);

    for (auto& t : clientes) {
        if (t.joinable()) {
            t.join();
        }
    }
    std::cout << "--- Simulación de Concurrencia Finalizada ---" << std::endl;

    std::cout << "Programa finalizado." << std::endl;

    return 0;
}