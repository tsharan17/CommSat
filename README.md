# CommSat

CommSat refers to a satellite prototype consisting solar powered battery, temperature, pressure, humidity and acceleration sensors to mimick the action of satellite communication prototypes.



PIN CONNECTIONS

================================



ESP32 \& SENSOR/MODULE CONNECTIONS

---------------------------------



Sensor/Module:      Pressure Sensor

Sensor Name:        BMP280

Interface:          I2C

Connections:        

&nbsp;                   SDA -> GPIO21

&nbsp;                   SCL -> GPIO22



Sensor/Module:      Temperature \& Humidity

Sensor Name:        DHT11

Interface:          Digital

Connections:        

&nbsp;                   Data -> GPIO4



Sensor/Module:      Accelerometer

Sensor Name:        ADXL345

Interface:          I2C

Connections:        

&nbsp;                   SDA -> GPIO21

&nbsp;                   SCL -> GPIO22



Sensor/Module:      ESP-NOW Communication

Sensor Name:        ESP32 Wireless

Interface:          --

Connections:        No pins required



Sensor/Module:      Power Input to ESP32

Source:             From Boost Converter

Interface:          --

Connections:        

&nbsp;                   VIN -> 5V output

&nbsp;                   GND -> GND





POWER SYSTEM CONNECTIONS

------------------------



Component:      Solar Panel

Pin:            + (Vout)  ->  Connected To: TP4056 IN+

Pin:            - (GND)   ->  Connected To: TP4056 IN-



Component:      TP4056

Pin:            BAT+      ->  Connected To: Li-ion Battery + (positive terminal)

Pin:            BAT-      ->  Connected To: Li-ion Battery – (negative terminal)

Pin:            OUT+      ->  Connected To: MT3608 VIN+

Pin:            OUT-      ->  Connected To: MT3608 VIN-



Component:      MT3608

Pin:            VOUT+     ->  Connected To: ESP32 VIN (or 5V input pin)

Pin:            VOUT-     ->  Connected To: ESP32 GND



Component:      ESP32 Module

Pin:            VIN       ->  Connected To: MT3608 VOUT+

Pin:            GND       ->  Connected To: MT3608 VOUT-

