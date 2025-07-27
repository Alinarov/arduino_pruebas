// Definir el pin analógico al que está conectado el sensor LM35
const int pinLM35 = A5; // Puedes usar A0, A1, A2, etc.

// Define un valor máximo de temperatura "esperado" o de referencia para la inversión.
// Este valor será el punto donde la temperatura real más baja se mapeará a la más alta invertida.
// Por ejemplo, si tu temperatura ambiente es 25C y quieres que esa sea el punto medio de inversion, ajusta esto.
// Puedes jugar con este valor para ajustar el rango de la inversión.


void setup() {
  // Inicializar la comunicación serial para mostrar los datos
  Serial.begin(9600);
  Serial.println("Iniciando lectura de temperatura LM35 con inversión...");
  // Opcional: Puedes usar analogReference(INTERNAL); si quieres usar la referencia de 1.1V
  // analogReference(INTERNAL);
}

void loop() {
  float TEMPERATURA_MAX_INVERTIDA = 50.0; // Puedes ajustar este valor, por ejemplo, 100.0, 50.0, etc.  
  // Leer el valor analógico del sensor
  int valorSensor = analogRead(pinLM35);

  // Convertir el valor analógico a voltaje
  // Si usaste analogReference(INTERNAL), cambia 5.0 a 1.1
  float voltaje = valorSensor * (5.0 / 1024.0);

  // Convertir el voltaje a temperatura en grados Celsius (temperatura "real" del LM35)
  float temperaturaCelsiusReal = voltaje * 100.0;

  // --- MODIFICACIÓN PARA INVERTIR LA TEMPERATURA ---
  // Restamos la temperatura real a un valor máximo predefinido.
  // Esto hará que, si temperaturaCelsiusReal sube, temperaturaInvertida baje.
  float temperaturaInvertida = TEMPERATURA_MAX_INVERTIDA - temperaturaCelsiusReal;

  float porcentaje_temp_max = TEMPERATURA_MAX_INVERTIDA * (temperaturaCelsiusReal / 100);
  if (porcentaje_temp_max < 1.50) {
    TEMPERATURA_MAX_INVERTIDA = TEMPERATURA_MAX_INVERTIDA + 10;
  } else if (porcentaje_temp_max > 98) {
    TEMPERATURA_MAX_INVERTIDA = TEMPERATURA_MAX_INVERTIDA - 10;
  }

  // Imprimir la temperatura en el Monitor Serie
  Serial.print("Valor del sensor (ADC): ");
  Serial.print(valorSensor);
  Serial.print(" | Voltaje: ");
  Serial.print(voltaje);
  Serial.print(" V | Temperatura REAL: ");
  Serial.print(temperaturaCelsiusReal);
  Serial.print(" °C | Temperatura INVERTIDA: ");
  Serial.print(temperaturaInvertida);
  Serial.println(" °C");

  // Esperar un poco antes de la próxima lectura
  delay(1000); // 1 segundo
}