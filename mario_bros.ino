// -------------------------------------------------
// Copyright (c) 2022 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"   // Librería que define las constantes de notas musicales (NOTE_C4, NOTE_D4, etc.)

#define BUZZER_PIN 9   // Pin digital donde está conectado el buzzer

// 🎵 Arreglo con todas las notas de la melodía
// Cada constante corresponde a una frecuencia musical definida en pitches.h
// REST significa silencio (pausa sin sonido)
int melody[] = {
  NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5,
  NOTE_G5, REST, NOTE_G4, REST, 
  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5,NOTE_C5, NOTE_D5, NOTE_B4,
  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5,NOTE_C5, NOTE_D5, NOTE_B4,
  
  REST, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_E5,
  REST, NOTE_GS4, NOTE_A4, NOTE_C4, REST, NOTE_A4, NOTE_C5, NOTE_D5,
  REST, NOTE_DS5, REST, NOTE_D5,
  NOTE_C5, REST,
  
  // ... (continúa con toda la melodía)
  
  // 🎵 Sonido de "Game Over"
  NOTE_C5, NOTE_G4, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_AS4, NOTE_GS4,
  NOTE_G4, NOTE_D4, NOTE_E4
};

// ⏱️ Arreglo con las duraciones de cada nota
// Cada número indica la fracción de un segundo:
// 4 = negra (¼ segundo), 8 = corchea (⅛ segundo), 2 = blanca (½ segundo), 1 = redonda (1 segundo)
int durations[] = {
  8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4, 
  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4,8, 8, 4,
  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4,8, 8, 4,
  
  // ... (continúa con todas las duraciones)
  
  // ⏱️ Duraciones del sonido "Game Over"
  4, 4, 4,
  8, 8, 8, 8, 8, 8,
  8, 8, 2
};

void setup()
{
  pinMode(BUZZER_PIN, OUTPUT);  // Configura el pin del buzzer como salida
}

void loop()
{
  // Calcula cuántos elementos hay en el arreglo durations
  int size = sizeof(durations) / sizeof(int);

  // Recorre todas las notas de la melodía
  for (int note = 0; note < size; note++) {
    // Calcula la duración real de la nota en milisegundos
    // Ejemplo: si durations[note] = 4 → 1000/4 = 250 ms
    int duration = 1000 / durations[note];
    
    // Reproduce la nota en el buzzer con la duración calculada
    tone(BUZZER_PIN, melody[note], duration);

    // Pausa entre notas (30% más larga que la duración de la nota)
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    
    // Detiene el sonido antes de pasar a la siguiente nota
    noTone(BUZZER_PIN);
  }
}
