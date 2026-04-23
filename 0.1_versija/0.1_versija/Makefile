CXX: = g++
CXXFLAGS : = -std = c++17 - O2 - Wall - Wextra - Iinclude
TARGET : = studentai
SRCS : = src / main.cpp src / utils.cpp src / generator.cpp \
src / vector_funkc.cpp src / list_funkc.cpp \
src / deque_funkc.cpp src / testavimas.cpp

.PHONY: all clean run generate test

all : $(TARGET)

$(TARGET) : $(SRCS)
$(CXX) $(CXXFLAGS) - o $@ $ ^
@echo "Sukompiliuota: $(TARGET)"

run: $(TARGET)
. / $(TARGET)

clean :
	rm - f $(TARGET)
	@echo "Istrinta"
