import pandas as pd
import matplotlib.pyplot as plt
import re

# 1. Procesar los datos del archivo de texto
# Asumimos que el archivo se llama 'capture.txt' y está en la misma carpeta
t_data = []
h_data = []

# Expresión regular para encontrar los valores decimales después de 't =' y 'h ='
# Esto ayuda a ignorar errores de formato o etiquetas extrañas
patron = re.compile(r"t\s*=\s*([\d\.]+),\s*h\s*=\s*([\d\.]+)")

try:
    with open('capture.txt', 'r') as f:
        contenido = f.read()
        # Buscamos todas las coincidencias en el texto
        coincidencias = patron.findall(contenido)
        
        for t_val, h_val in coincidencias:
            t_data.append(float(t_val))
            h_data.append(float(h_val))

    # 2. Crear DataFrame
    df_sensor = pd.DataFrame({
        'Temperatura': t_data,
        'Humedad': h_data
    })

    # 3. Configurar y mostrar los gráficos
    fig = plt.figure(figsize=(20, 12)) # Ajusté la altura para dos gráficos

    # Gráfico 1: Temperatura
    plt.subplot(211)
    plt.title('Datos del Sensor - Temperatura', fontsize=24)
    plt.ylabel('Temperatura (°C)', fontsize=20)
    # plt.xlabel('Muestras', fontsize=20) # Opcional si quieres eje X en ambos
    plt.plot(df_sensor['Temperatura'], 'r', linewidth=2) # 'r' para rojo
    plt.grid(True)
    plt.xticks(fontsize=14)
    plt.yticks(fontsize=14)

    # Gráfico 2: Humedad
    plt.subplot(212)
    plt.title('Datos del Sensor - Humedad', fontsize=24)
    plt.xlabel('Muestras', fontsize=24)
    plt.ylabel('Humedad (%)', fontsize=20)
    plt.plot(df_sensor['Humedad'], 'b', linewidth=2) # 'b' para azul
    plt.grid(True)
    plt.xticks(fontsize=14)
    plt.yticks(fontsize=14)

    plt.tight_layout() # Ajusta el espaciado para que no se superpongan
    plt.show()

except FileNotFoundError:
    print("Error: No se encontró el archivo 'capture.txt'. Asegúrate de guardarlo en la misma carpeta.")
except Exception as e:
    print(f"Ocurrió un error procesando los datos: {e}")