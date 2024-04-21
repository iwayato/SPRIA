**Date**: 06/04/2024

**Issue**: Describe the architectural design issue you’re addressing, leaving no questions about why you’re addressing this issue now. Following a minimalist approach, address and document only the issues that need addressing at various points in the life cycle.

**Issue**: Se busca implementar en la arquitectura del sistema una Base de Datos que pueda realizar VSS o metodos de busquedas vectoriales alternativas dado un vector de entrada. El objetivo es no tener que realizar reconocimiento facial "manualmente", si no que una base de datos especializada lo realice de forma más eficiente y rápida en contraste a una implementación propia.

**Decision**: Se ha decidido por implementar la Base de Datos Vectorial Weaviate.

**Assumptions**: La implementación del sistema en C++ limitó las posibles opciones a implementar en cuanto a Base de Datos Vectoriales. Weaviate ofrece commo una alternativa agnostica del lenguaje el uso de REST API o GraphQL API para la comunicación.
Se contempla la opción de implementar en el futuro los modelos de embedding en la Base de Datos para agilizar el proceso de Image Encoding.

**Constraints**: Posiblemente pase mucho tiempo antes de que exista una libreria para C++ con la cual se pueda conectar a la Base de Datos directamente, sin embargo este caso es el mismo que para el resto de las Bases de Datos vectoriales más populares.
Existe un nivel de dificultad asociado a implementar bases de datos vectoriales ya que es algo todavia novedoso.
Hasta el momento, se tienen unicamente 3 alternativas para conectar con la Base de Datos en C++: GraphQL API, REST API, y gRPC API.