#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Cameras.o \
	${OBJECTDIR}/src/Graph.o \
	${OBJECTDIR}/src/Lightning.o \
	${OBJECTDIR}/src/Node.o \
	${OBJECTDIR}/src/Primitive.o \
	${OBJECTDIR}/src/Scene.o \
	${OBJECTDIR}/src/YafParser.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lglut -lCGF -ltinyxml `pkg-config --libs gl` `pkg-config --libs glew` `pkg-config --libs glu` `pkg-config --libs glui`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/laig-2013-2014

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/laig-2013-2014: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/laig-2013-2014 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/Cameras.o: src/Cameras.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags glu` `pkg-config --cflags glui`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Cameras.o src/Cameras.cpp

${OBJECTDIR}/src/Graph.o: src/Graph.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags glu` `pkg-config --cflags glui`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Graph.o src/Graph.cpp

${OBJECTDIR}/src/Lightning.o: src/Lightning.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags glu` `pkg-config --cflags glui`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Lightning.o src/Lightning.cpp

${OBJECTDIR}/src/Node.o: src/Node.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags glu` `pkg-config --cflags glui`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Node.o src/Node.cpp

${OBJECTDIR}/src/Primitive.o: src/Primitive.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags glu` `pkg-config --cflags glui`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Primitive.o src/Primitive.cpp

${OBJECTDIR}/src/Scene.o: src/Scene.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags glu` `pkg-config --cflags glui`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Scene.o src/Scene.cpp

${OBJECTDIR}/src/YafParser.o: src/YafParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags glu` `pkg-config --cflags glui`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/YafParser.o src/YafParser.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags glu` `pkg-config --cflags glui`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/laig-2013-2014

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
