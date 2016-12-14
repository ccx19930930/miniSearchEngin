INC_DIR:= ./
SRCS:=$(wildcard ./*.cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
LIBS:= 

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 -ljson $(addprefix -I, $(INC_DIR)) $(LIBS)

EXE:=./main.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
