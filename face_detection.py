import cv2
import sys
import os
import serial
import time

# --- Configuración Serial ---
# Importante: Reemplaza 'COM3' o '/dev/ttyACM0' con el puerto serial de tu Arduino
# La velocidad (baud rate) debe coincidir con la configurada en el Arduino
SERIAL_PORT = 'COM7'  # Ejemplo en Windows: 'COM3' / Ejemplo en Linux: '/dev/ttyACM0'
BAUD_RATE = 9600

# Paso 1: Cargar el clasificador Haar Cascade
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

if face_cascade.empty():
    print("Error: No se pudo cargar el clasificador Haar Cascade XML.")
    sys.exit()

# Paso 2: Inicializar la comunicación serial y la cámara
try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.1)
    # Dar tiempo al Arduino para reiniciarse si está conectado
    time.sleep(2) 
    print(f"Conexión serial establecida en {SERIAL_PORT} a {BAUD_RATE} baudios.")
except serial.SerialException as e:
    print(f"Error al conectar con el puerto serial {SERIAL_PORT}: {e}")
    sys.exit()

# Inicializar la captura de video desde la cámara web
video_capture = cv2.VideoCapture(0)

if not video_capture.isOpened():
    print("Error: No se pudo abrir la cámara web.")
    ser.close()
    sys.exit()

print("Presiona 'q' para salir.")

# Bucle principal para el procesamiento de video en tiempo real
while True:
    ret, frame = video_capture.read() 
    
    if not ret:
        print("Error: No se pudo recibir el fotograma (fin de la transmisión o error).")
        break

    # Convertir el fotograma a escala de grises para la detección
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detectar rostros
    faces = face_cascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(30, 30)
    )
    
    # -----------------------------------------------
    # Lógica para enviar el carácter serial
    # -----------------------------------------------
    if len(faces) > 0:
        # Si se detecta al menos un rostro, enviar el carácter 'F'
        serial_output = 'F'
        ser.write(serial_output.encode('utf-8'))
        
        # Dibuja un rectángulo verde (indica detección)
        for (x, y, w, h) in faces:
            cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
            cv2.putText(frame, "ROSTRO DETECTADO (Serial: F)", (x, y-10), 
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
    else:
        # Si no se detectan rostros, envía otro carácter o ninguno (aquí enviamos 'N')
        serial_output = 'N'
        ser.write(serial_output.encode('utf-8'))
        
        # Opcional: Mostrar mensaje de no detección
        cv2.putText(frame, "No se detectaron rostros (Serial: N)", (10, 30), 
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
    
    # Mostrar el fotograma resultante
    cv2.imshow('Live Face Detection', frame)

    # Salir del bucle si se presiona la tecla 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Limpieza y cierre
video_capture.release()
cv2.destroyAllWindows()
ser.close()
print("Programa finalizado y conexión serial cerrada.")
