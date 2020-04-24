#
# @ Win32 Dialog base mingw32 example
# 
CXX = g++
TARGET = ./bin/GwentDrawSim.exe

# =============================================
# CFLAGE

CFLAG = -O2 -g -w -I./

# =============================================
# LD_FLAG

LD_FLAG = -lcomctl32 -luser32 -lkernel32 -lcomdlg32

LD_FLAG += -Wl,--subsystem,windows
# For debug
#LD_FLAG += -Wl,--subsystem,console

# =============================================
# BUILD

OBJS = main.o resource.o LibGwentDrawSim.o

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LD_FLAG)

MAIN_HEADER = resource.h LibGwentDrawSim.h
main.o: main.cpp $(MAIN_HEADER)
	gcc -c $< $(CFLAG)

LibGwentDrawSim.o : LibGwentDrawSim.cpp LibGwentDrawSim.h
	gcc -c $< $(CFLAG)

resource.o: resource.rc
	windres -i $< -o $@

clean:
	rm -f *.o
	rm -f *.exe