# Laboratorio-2-Rob-tica

Integrantes:
-Alex Aravena
-Álvaro Catalán
-Samira Becerra
-Leandro Chamorro

Parte 1
1 • ¿ Qué es la percepción en robótica y por qué es fundamental en los sistemas autónomos? 

Percepción es la capacidad que tiene el robot de recolectar datos y transformarlo en información útil para navegar, interactuar. Es importante para tomar decisiones inteligentes y para construir una representación del mundo, esto se realiza mediante sensores. 

Existen tres tipos de percepción: 
Percepción sensorial básica: detectar obstáculos, colores, formas, luz, etc. 
Percepción espacial: Útil para entender dónde está el robot y que hay a su alrededor 
Percepción compleja: Reconocer objetos, emociones, personal, etc. 

2 • En el sensor ultrasónico HC-SR04 ¿ Qué parámetro se mide para calcular la distancia? 

El tiempo que se demora en que la onda ultrasónica viaje a un obstáculo, sumándole el tiempo de vuelta.


3 • ¿ Cómo influye el ruido en las mediciones del sensor ultrasónico y cómo
podría reducirse?

El ruido provoca que las mediciones del sensor ultrasónico no sean perfectas, disminuyendo la precisión y confiabilidad al medir distancias. Este ruido puede deberse a superficies irregulares, interferencias o al ángulo de rebote del sonido. Para reducir este error, se pueden procesar y filtrar los datos, eliminando así las fluctuaciones no deseadas y mejorando la calidad de las mediciones.


Parte 2

4 • Si el robot detecta el color rojo en el suelo ¿ Qué acción debe tomar?
¿ Por qué?



Si el robot detecta el color rojo en el suelo, debe girar a la izquierda, esto debido a que en el código, al detectar al color rojo, se ejecuta la función “girarIzquierda()”. Esto es para poder tomar decisiones rápidas respecto a qué hacer en ciertas situaciones, ya que, con el color azul gira a la derecha, entonces ya hay 2 situaciones en las que sabe que hacer en caso de detectar tales colores. Todo esto va con el apoyo del sensor ultrasónico para detectar obstáculos, por lo tanto no se necesita asignarle un color para detenerse ya que lo hará cuando detecte un obstáculo.



5 • Si el sensor ultrasónico detecta valores erráticos ¿ Que estrategias podrías aplicar para mejorar la precisión?

Algunas estrategias que se podrían aplicar para mejorar la precisión en caso de detectar valores erráticos incluyen el filtrado de las lecturas a través de la toma de varias muestras de forma consecutiva y el cálculo del promedio entre las mismas para reducir los picos o el ruido que se pueda generar. También se puede repetir el método anterior pero en vez de calcular el promedio se obtiene la mediana entre cierto número de lecturas. Otra estrategia puede incluir tomar solo los valores que se encuentren en un rango definido para evitar que lecturas atípicas sean leídas e interfieran en el resultado. Por último, otras medidas que se pueden aplicar están relacionadas con el ambiente en el cual se encuentra el robot como el control de las señales que hay a su alrededor para evitar que generen ruido o el uso de distintos materiales que ayuden a controlar el rebote del sonido para el sensor.

6 • Si tuvieras que integrar un nuevo sensor para mejorar la navegación
del robot ¿ Cuál elegirías y por qué?. 

Escogeríamos el sensor LIDAR, ya que actualmente no contamos con un sensor capaz de generar un mapa tridimensional del entorno, lo que permitiría una mejor planificación de rutas. Además, al utilizar pulsos de luz, el LIDAR ofrece una detección mucho más rápida que las ondas ultrasónicas del sensor HC-SR04, lo que se traduce en un mejor tiempo de respuesta ante obstáculos.

7 • ¿Cuál es el tiempo de respuesta del robot al detectar un cambio de color?		

El tiempo de respuesta que el robot tiene al momento de detectar un cambio de color es de entre 1102-3600 ms.


Reflexión sobre posibles mejoras en la detección

Para poder mejorar la detección podríamos realizar pruebas en un entorno más controlado, donde no haya ninguna señal que pueda interrumpir y exista un circuito más elaborado con obstáculos y colores bien definidos y una iluminación ideal para favorecer la detección de colores. Otra forma de mejorar la detección sería cambiar los sensores por otros de mayor calidad que puedan aumentar el tiempo de respuesta y mejorar la detección. Por último podríamos hacer un mayor uso de algoritmos de filtrado para evitar que datos atípicos influyan en la lectura.

Análisis de variaciones en las lecturas

Las lecturas iniciales no eran muy certeras, pero tampoco se alejaban tanto del valor real, presentando una variación de entre -0.67 y 0.54. Debido a esto decidimos ajustar el código para que se ajustara mejor a las mediciones, modificando el valor distancia a *=1,02. Tras realizar el ajuste debido las mediciones comenzaron a ser más precisas, presentando variaciones mínimas las cuales se pueden atribuir a una pequeña imprecisión de medición física.


