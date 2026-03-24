## 🏭 Sistema de Automatización para Máquinas de Flexografía
📌 Descripción del Proyecto

Este proyecto consiste en el diseño y desarrollo de un sistema de automatización industrial aplicado a máquinas de impresión flexográfica.

Se implementó una arquitectura distribuida basada en microcontroladores, donde un nodo maestro coordina múltiples nodos esclavos a través de comunicación I2C, permitiendo el control independiente de cada cuerpo de impresión.

El sistema está orientado a mejorar la precisión de registro, facilitar la operación manual y garantizar la persistencia de configuraciones críticas del proceso.

## 🎯 Objetivos
Automatizar el control de múltiples cuerpos de impresión.
Mejorar la precisión en el registro de impresión.
Implementar una arquitectura escalable y robusta.
Garantizar almacenamiento persistente de parámetros operativos.
Facilitar la operación mediante interfaz manual con feedback visual.
⚙️ Arquitectura del Sistema

## El sistema se basa en un modelo Maestro–Esclavo:

Maestro (Arduino Mega 2560)
Control central del sistema
Gestión de comunicación I2C
Coordinación de los cuerpos de impresión
Esclavos (nodos independientes)
Control individual de cada cuerpo de impresión
Recepción de comandos del maestro
Ejecución de ajustes de registro
Comunicación
Protocolo: I2C (Wire Library)
Topología multi-dispositivo

## 🧠 Funcionalidades Principales
🔹 Control de Cuerpos de Impresión
Manejo independiente de hasta 6 cuerpos de impresión
Ajustes precisos en tiempo real
🔹 Control de Registro
Registro circunferencial
Registro lateral
Mejora de alineación en impresión
🔹 Persistencia de Datos
Uso de EEPROM para almacenamiento de:
Configuraciones
Parámetros de calibración
🔹 Interfaz de Usuario
Operación manual
Feedback visual para el operador
Control directo sin necesidad de sistemas externos
🔹 Hardware Personalizado

## Diseño de PCB propio
Circuitos de multiplexación optimizados

## 🧪 Tecnologías Utilizadas
Arduino Mega 2560
Comunicación I2C (Wire Library)
EEPROM
Diseño de PCB
Sistemas Embebidos
Automatización Industrial

## 🏗️ Estructura del Proyecto
/src
  ├── master/
  │     ├── main.ino
  │     └── i2c_manager.h
  │
  ├── slave/
  │     ├── slave_controller.ino
  │     └── register_control.h
  │
  ├── drivers/
  │     ├── eeprom_manager.h
  │     └── io_control.h
  │
  └── ui/
        └── manual_interface.h

/hardware
  ├── pcb_design/
  └── schematics/

/docs
  ├── architecture.md
  └── wiring_diagram.png
