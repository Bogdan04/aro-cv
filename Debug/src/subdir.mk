################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bogdan.cpp \
../src/Bogdan2.cpp \
../src/Bogdan3_circles.cpp \
../src/StereoCalib.cpp \
../src/main.cpp \
../src/myapp.cpp 

OBJS += \
./src/Bogdan.o \
./src/Bogdan2.o \
./src/Bogdan3_circles.o \
./src/StereoCalib.o \
./src/main.o \
./src/myapp.o 

CPP_DEPS += \
./src/Bogdan.d \
./src/Bogdan2.d \
./src/Bogdan3_circles.d \
./src/StereoCalib.d \
./src/main.d \
./src/myapp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


