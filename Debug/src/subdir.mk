################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LocalToSocket.cpp \
../src/MiscUtils.cpp \
../src/directoryUtils.cpp \
../src/logger.cpp \
../src/proc.cpp \
../src/timeUtils.cpp 

OBJS += \
./src/LocalToSocket.o \
./src/MiscUtils.o \
./src/directoryUtils.o \
./src/logger.o \
./src/proc.o \
./src/timeUtils.o 

CPP_DEPS += \
./src/LocalToSocket.d \
./src/MiscUtils.d \
./src/directoryUtils.d \
./src/logger.d \
./src/proc.d \
./src/timeUtils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1z -O0 -g3 -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


