import serial                       # Librería para comunicación serial (Arduino ↔ PC)
import matplotlib.pyplot as plt     # Librería para graficar datos
from IPython.display import display, clear_output  # Para mostrar y actualizar gráficos en notebooks

# Activa el modo interactivo de matplotlib (permite actualizar gráficos en tiempo real)
plt.ion()
fig, ax = plt.subplots()            # Crea una figura y un eje para graficar

# Arreglos (listas) donde se almacenarán los datos recibidos
humedad_data = []                   # Lista para guardar valores de humedad
temperatura_data = []               # Lista para guardar valores de temperatura

# Configura el puerto serial (ajusta 'COM6' según tu PC y velocidad de transmisión)
ser = serial.Serial('COM6', 9600)
print("Inicio de comunicacion serial: ")

line_count = 0  # Contador para alternar entre humedad y temperatura

# Bucle infinito: lee datos continuamente desde el puerto serial
while True:
    line = ser.readline().decode('utf-8').strip()  # Lee una línea, decodifica y elimina espacios
    try:
        valor = float(line)  # Convierte el dato recibido a número decimal

        # Alterna entre humedad y temperatura usando el contador
        if line_count % 2 == 0:       # Si el contador es par → dato de humedad
            humedad_data.append(valor)
        else:                         # Si el contador es impar → dato de temperatura
            temperatura_data.append(valor)

        line_count += 1               # Incrementa el contador para la próxima lectura

        # Actualiza el gráfico en tiempo real
        ax.clear()                    # Limpia el gráfico anterior
        ax.plot(humedad_data, label='Humedad (%)')        # Grafica los valores de humedad
        ax.plot(temperatura_data, label='Temperatura (°C)') # Grafica los valores de temperatura
        ax.set_title('Datos en tiempo real')              # Título del gráfico
        ax.set_xlabel('Muestras')                         # Etiqueta del eje X
        ax.set_ylabel('Valores')                          # Etiqueta del eje Y
        ax.legend()                                       # Muestra la leyenda
        plt.pause(0.1)                                    # Pausa breve para refrescar el gráfico
        display(fig)                                      # Muestra la figura actualizada
        clear_output(wait=True)                           # Limpia la salida anterior en notebook

    except ValueError:
        # Si el dato recibido no es numérico, muestra un mensaje de error
        print("Dato inválido recibido:", line)
