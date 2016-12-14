INC_DIR:= ./include
SRCS:=$(wildcard ./src/thread_pool/*.cc ./src/tcp/*.cc ./src/server/*.cc ./src/Query_module/*.cc ./src/CppJieba/*.cc ./src/Timer/*.cc ./src/Cache/*.cc ./src/Dictionary/*.cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
LIBS:= 

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 -lpthread -ljson $(addprefix -I, $(INC_DIR)) $(LIBS)

EXE:=./bin/main.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
