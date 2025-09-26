CXX = g++
CXXFLAGS = -std=c++11 -Wall

SOURCES = main.cpp Image.cpp GSCImage.cpp RGBImage.cpp Pixel.cpp GSCPixel.cpp RGBPixel.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = image_processing.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del $(OBJECTS) $(EXECUTABLE)
