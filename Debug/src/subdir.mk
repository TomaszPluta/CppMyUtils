################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MiscUtils.cpp \
../src/dirSize.cpp \
../src/logger.cpp \
../src/mvc.cpp \
../src/proc.cpp 

OBJS += \
./src/MiscUtils.o \
./src/dirSize.o \
./src/logger.o \
./src/mvc.o \
./src/proc.o 

CPP_DEPS += \
./src/MiscUtils.d \
./src/dirSize.d \
./src/logger.d \
./src/mvc.d \
./src/proc.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1z -O0 -g3 -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


