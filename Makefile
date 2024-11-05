# Nombre del compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system

# Nombre del ejecutable
TARGET = conway

# Archivos fuente
SRCS = main.cpp

# Regla para compilar el ejecutable
$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET) $(CXXFLAGS)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET)

