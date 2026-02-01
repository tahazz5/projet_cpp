# -------------------------------
# Makefile pour moteur d'échecs POO
# -------------------------------

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g

# Dossiers
SRC_DIR_CORE = core
SRC_DIR_ENGINE = engine

# Sources
SRCS_CORE = $(wildcard $(SRC_DIR_CORE)/*.cpp)
SRCS_ENGINE = $(wildcard $(SRC_DIR_ENGINE)/*.cpp)
SRCS = main.cpp $(SRCS_CORE) $(SRCS_ENGINE)

# Objets
OBJS = $(SRCS:.cpp=.o)

# Exécutable
TARGET = test_poo

# -------------------------------
# Règles
# -------------------------------

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compilation de chaque .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
