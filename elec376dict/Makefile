# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall

# Paths
CURL_INCLUDE = C:/msys64/ucrt64/include/curl
CURL_LIB = C:/msys64/ucrt64/lib

# Target executable
TARGET = elec376dict.exe

# Source files
SRC = elec376dict.cpp

# Build target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -I $(CURL_INCLUDE) -L $(CURL_LIB) -lcurl -o $(TARGET) $(SRC)

# Clean build files
clean:
	rm -f $(TARGET)
