CXX = g++
CXXFLAGS = -lSDL2
DEPS = timers.h  keypad.h
OBJ = chip.o timers.o keypad.o

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

chipEmu: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)
clean:
	rm -f *.o
