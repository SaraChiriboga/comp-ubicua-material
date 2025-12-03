import serial
import matplotlib.pyplot as plt
from IPython.display import display, clear_output

plt.ion()
fig, ax = plt.subplots()
humedad_data = []
temperatura_data = []

ser = serial.Serial('COM6', 9600)
print("Inicio de comunicacion serial: ")

line_count = 0  # contador para saber si toca humedad o temperatura

while True:
    line = ser.readline().decode('utf-8').strip()
    try:
        valor = float(line)
        if line_count % 2 == 0:  # pares -> humedad
            humedad_data.append(valor)
        else:  # impares -> temperatura
            temperatura_data.append(valor)

        line_count += 1

        ax.clear()
        ax.plot(humedad_data, label='Humedad (%)')
        ax.plot(temperatura_data, label='Temperatura (°C)')
        ax.set_title('Datos en tiempo real')
        ax.set_xlabel('Muestras')
        ax.set_ylabel('Valores')
        ax.legend()
        plt.pause(0.1)
        display(fig)
        clear_output(wait=True)
    except ValueError:
        print("Dato inválido recibido:", line)
