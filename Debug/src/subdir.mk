################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/HttpSocket.cpp \
../src/StatusData.cpp \
../src/twiclipp.cpp 

OBJS += \
./src/HttpSocket.o \
./src/StatusData.o \
./src/twiclipp.o 

CPP_DEPS += \
./src/HttpSocket.d \
./src/StatusData.d \
./src/twiclipp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


