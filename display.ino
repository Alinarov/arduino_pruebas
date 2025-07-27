#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Ajusta la dirección I2C si es necesario (ej. 0x27, 0x3F, 0x20)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Dirección, columnas, filas

void setup() {
  lcd.init();       // Inicializa el LCD
  lcd.backlight();  // Enciende la retroiluminación (si tiene)
  lcd.setCursor(0, 0);
  lcd.print("Hola, Chbote!");
}

void loop() {
  // Tu código de loop
  lcd.display();
}