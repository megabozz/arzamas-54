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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Arm
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/cgi.o \
	${OBJECTDIR}/src/datastrings.o \
	${OBJECTDIR}/src/json.o \
	${OBJECTDIR}/src/kkm.o \
	${OBJECTDIR}/src/kkm_functions.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=-Os

# CC Compiler Flags
CCFLAGS=-Os
CXXFLAGS=-Os

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk kkmservice.cgi

kkmservice.cgi: ${OBJECTFILES}
	${LINK.cc} -o kkmservice.cgi ${OBJECTFILES} ${LDLIBSOPTIONS} -luuid lib/armhf/libfptr.so -s

${OBJECTDIR}/src/cgi.o: src/cgi.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/cgi.o src/cgi.cpp

${OBJECTDIR}/src/datastrings.o: src/datastrings.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/datastrings.o src/datastrings.cpp

${OBJECTDIR}/src/json.o: src/json.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json.o src/json.cpp

${OBJECTDIR}/src/kkm.o: src/kkm.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/kkm.o src/kkm.cpp

${OBJECTDIR}/src/kkm_functions.o: src/kkm_functions.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/kkm_functions.o src/kkm_functions.cpp

${OBJECTDIR}/src/main.o: src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
