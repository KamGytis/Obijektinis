Copy

CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGET   = studentai
SRCS     = main.cpp utils.cpp generator.cpp \
           vector_funkc.cpp list_funkc.cpp \
           deque_funkc.cpp testavimas.cpp
 
.PHONY: all clean run
 
all: $(TARGET)
 
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Sukompiliuota: $(TARGET)"
 
run: $(TARGET)
	./$(TARGET)
 
clean:
	rm -f $(TARGET)
	@echo "Istrinta"
 