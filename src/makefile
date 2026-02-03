# -------------------------------
# Makefile pour moteur d'échecs POO
# -------------------------------

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g
LDFLAGS =

# Dossiers
SRC_DIR_CORE = core
SRC_DIR_ENGINE = engine
SRC_DIR_GUI = gui
SRC_DIR_GUI_QT = gui/qt

# Sources
SRCS_CORE = $(wildcard $(SRC_DIR_CORE)/*.cpp)
SRCS_ENGINE = $(wildcard $(SRC_DIR_ENGINE)/*.cpp)
SRCS_GUI = $(wildcard $(SRC_DIR_GUI)/*.cpp)
SRCS = main.cpp $(SRCS_CORE) $(SRCS_ENGINE) $(SRCS_GUI)

ifeq ($(USE_QT_GUI),1)
SRCS_GUI_QT = $(wildcard $(SRC_DIR_GUI_QT)/*.cpp)
SRCS += $(SRCS_GUI_QT)
CXXFLAGS += $(QT_CXXFLAGS)
LDFLAGS += $(QT_LDFLAGS)
endif

# Objets
OBJS = $(SRCS:.cpp=.o)

# Exécutable
TARGET = test_poo

# -------------------------------
# Règles
# -------------------------------

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compilation de chaque .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
