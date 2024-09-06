# Define compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
DEBUG_FLAGS = -g
OPT_FLAGS = -O2

# Define target names
OLD_DEBUG_TARGET = q1_debug
OLD_OPT_TARGET = q1_opt
NEW_DEBUG_TARGET = q2_debug
NEW_OPT_TARGET = q2_opt

# Source files
OLD_SRC = InflationTax.cpp Q1.cpp
NEW_SRC = InflationTax.cpp InflationTax2024.cpp Q2.cpp

# Object files
OLD_OBJ = $(OLD_SRC:.cpp=.o)
NEW_OBJ = $(NEW_SRC:.cpp=.o)

# Build rules
all: $(OLD_DEBUG_TARGET) $(OLD_OPT_TARGET) $(NEW_DEBUG_TARGET) $(NEW_OPT_TARGET)

# Rule to build the debug version of old LTCG
$(OLD_DEBUG_TARGET): $(OLD_OBJ)
	$(CXX) $(DEBUG_FLAGS) $(CXXFLAGS) -o $(OLD_DEBUG_TARGET) $(OLD_OBJ)

# Rule to build the optimized version of old LTCG
$(OLD_OPT_TARGET): $(OLD_OBJ)
	$(CXX) $(OPT_FLAGS) $(CXXFLAGS) -o $(OLD_OPT_TARGET) $(OLD_OBJ)

# Rule to build the debug version of new LTCG
$(NEW_DEBUG_TARGET): $(NEW_OBJ)
	$(CXX) $(DEBUG_FLAGS) $(CXXFLAGS) -o $(NEW_DEBUG_TARGET) $(NEW_OBJ)

# Rule to build the optimized version of new LTCG
$(NEW_OPT_TARGET): $(NEW_OBJ)
	$(CXX) $(OPT_FLAGS) $(CXXFLAGS) -o $(NEW_OPT_TARGET) $(NEW_OBJ)

# Rule to compile old LTCG source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile new LTCG source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean object and binary files
clean:
	rm -f $(OLD_OBJ) $(NEW_OBJ) $(OLD_DEBUG_TARGET) $(OLD_OPT_TARGET) $(NEW_DEBUG_TARGET) $(NEW_OPT_TARGET)

# Rule to run the debug version of the old LTCG
run_old_debug: $(OLD_DEBUG_TARGET)
	./$(OLD_DEBUG_TARGET)

# Rule to run the optimized version of the old LTCG
run_old_opt: $(OLD_OPT_TARGET)
	./$(OLD_OPT_TARGET)

# Rule to run the debug version of the new LTCG
run_new_debug: $(NEW_DEBUG_TARGET)
	./$(NEW_DEBUG_TARGET)

# Rule to run the optimized version of the new LTCG
run_new_opt: $(NEW_OPT_TARGET)
	./$(NEW_OPT_TARGET)

.PHONY: all clean run_old_debug run_old_opt run_new_debug run_new_opt

