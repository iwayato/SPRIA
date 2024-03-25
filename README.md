# Sistema-Preventivo-Robos-Hormiga
Sistema que utiliza reconocimiento facial para detectar el ingreso de "mecheros" hacia los locales y prevenir posibles "robos hormiga".
La idea principal es implementar 3 módulos: detección facial, extracción de las características faciales y reconocimiento facial.

## Módulo de detección facial
Dlib implementa 2 modelos para este objetivo:
1. Histograma de Gradientes Orientados (HOG):
    - Para la implementación en particular de Dlib, es necesario utilizar imágenes que contengan rostros con unas dimensiones mínimas de 80 x 80 píxeles.
    - HOG es más rápido que la implementación DNN, dado que ésta última tiene buenos desempeños utilizando una GPU de alto rendimiento.
2. Deep Neural Network (DNN)