EXENAME = final_project
#OBJS = main.o PNG.o HSLAPixel.o lodepng.o lab_intro.o Airport.o
#OBJS = main.o PNG.o HSLAPixel.o lodepng.o Airport.o Flight.o AirportGraph.o
OBJS = main.o PNG.o HSLAPixel.o lodepng.o Airport.o Flight.o AirportGraph.o
CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# Custom Clang version enforcement logic:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu") 
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
ifneq ($(strip $(SKIP_EWS_CHECK)),True)
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif
endif

.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

#main.o : main.cpp lab_intro.h cs225/PNG.h cs225/HSLAPixel.h
	#$(CXX) $(CXXFLAGS) main.cpp
main.o : main.cpp cs225/PNG.h cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) main.cpp

#lab_intro.o : lab_intro.cpp lab_intro.h
	#$(CXX) $(CXXFLAGS) lab_intro.cpp

PNG.o : cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp


test: output_msg catchmain.o tests-part1.o PNG.o HSLAPixel.o lodepng.o Airport.o AirportGraph.o Flight.o
	$(LD) catchmain.o tests-part1.o PNG.o HSLAPixel.o lodepng.o Airport.o AirportGraph.o Flight.o $(LDFLAGS) -o test

catchmain.o : cs225/catch/catchmain.cpp cs225/catch/catch.hpp
	$(CXX) $(CXXFLAGS) cs225/catch/catchmain.cpp

tests-part1.o : tests/tests-part1.cpp cs225/catch/catch.hpp Airport.cpp Airport.h AirportGraph.cpp AirportGraph.h Flight.cpp Flight.h
	$(CXX) $(CXXFLAGS) tests/tests-part1.cpp


clean :
	-rm -f *.o $(EXENAME) test
