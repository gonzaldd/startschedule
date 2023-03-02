# StartSchedule

Creado para ESP32, permite setear horarios para encender un relay conectado a la placa.

## Instalación

1. Agregar el nombre y la password del WIFI en config.h
2. Cambiar en config.h -> PIN_TO_ENGINE al pin donde está conectado el relay (De lo contrario se usa el pin del led integrado)
3. Setear los horarios en los que se enciende el relay en schedule.h -> IGNITION_SCHEDULE (Solo se aceptan 3 por el momento).

## Roadmap

- Modificar el Wifi a traves del bluetooth

- Modificar los horarios a traves de API/Bluetooth/otra idea
