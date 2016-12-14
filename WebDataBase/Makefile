INC_DIR:= ./include
SRCS:=$(wildcard ./src/CppJieba/*.cc ./src/rss/*.cc ./src/Dictionary/*.cc ./src/PageLib/*.cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
LIBS:= -ljson -lboost_regex

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS)

EXE:=./bin/main.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
