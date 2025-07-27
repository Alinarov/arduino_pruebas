#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// Ajusta la dirección I2C si es necesario (ej. 0x27, 0x3F, 0x20)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Dirección, columnas, filas



// Definir pines y valores
// const int THERMISTOR_PIN = A0;
const int R1 = 330;  // Cambiado a 10k Ohmios para que funcione bien con termistor de 10k

// Parámetros del termistor NTC 10k (por ejemplo: 10D-7 de 10k)
const float NOMINAL_RESISTANCE = 10.0;    // 10 a 25 °C RESISTENCIA DEL TERMISTOR 
const float NOMINAL_TEMPERATURE = 25.0;      // En grados Celsius
const float B_VALUE = 3435.0;                // Valor beta típico


float calcular_celcius (int THERMISTOR_PIN) {
  int analogValue = analogRead(THERMISTOR_PIN);

  // --- PASO 1: Mostrar valor analógico ---
  // Serial.print("1. Valor Analogico (0-1023): ");
  // Serial.print(analogValue);

  // --- PASO 2: Calcular resistencia del termistor ---
  float resistance = R1 * ((1023.0 / analogValue) - 1);  // ✅ Fórmula corregida
  // Serial.print(" | 2. Resistencia Calculada (Ohms): ");
  // Serial.print(resistance);

  // --- PASO 3: Calcular temperatura usando la fórmula de Steinhart-Hart (simplificada) ---
  float steinhart;
  steinhart = resistance / NOMINAL_RESISTANCE;
  steinhart = log(steinhart);
  steinhart /= B_VALUE;
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15; // Convertir a grados Celsius

  // Serial.print(" | 3. Temperatura (°C): ");
  // Serial.println(steinhart);
  return steinhart;


}

void setup() {
  Serial.begin(9600); // Iniciar comunicación serie
  lcd.init();       // Inicializa el LCD
  lcd.backlight();  // Enciende la retroiluminación (si tiene)

}

void loop() {
  float t1 = calcular_celcius(A0);
  float t2 = calcular_celcius(A1);
  float t3 = calcular_celcius(A2);
  float t4 = calcular_celcius(A3);

  String t_s1 = String(t1);
  String t_s2 = String(t2);
  String t_s3 = String(t3);
  String t_s4 = String(t4);


  String resultados_f1 = "T1:" + t_s1 + " T2:" + t_s2;
  String resultados_f2 = "T3:" + t_s3 + " T4:" + t_s4;

  // Serial.println(resultados_f1); // Puedes cambiar esto por lcd.print si estás usando LCD
  // Serial.println(resultados_f2); // Puedes cambiar esto por lcd.print si estás usando LCD
  lcd.setCursor(0, 0);
  lcd.print(resultados_f1);
  lcd.setCursor(0, 1);
  lcd.print(resultados_f2);  

  

  delay(500);
}