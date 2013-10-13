################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../Connection.o \
../ConnectionInfo.o \
../Server.o \
../client.o \
../connectionInfo.o \
../server.o 

CPP_SRCS += \
../ConnectionInfo.cpp \
../client.cpp \
../server.cpp 

OBJS += \
./ConnectionInfo.o \
./client.o \
./server.o 

CPP_DEPS += \
./ConnectionInfo.d \
./client.d \
./server.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


