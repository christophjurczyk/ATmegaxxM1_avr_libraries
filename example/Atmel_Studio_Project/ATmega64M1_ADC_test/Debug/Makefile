################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../adc.cpp \
../dac.cpp \
../main.cpp \
../uart.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
adc.o \
dac.o \
main.o \
uart.o

OBJS_AS_ARGS +=  \
adc.o \
dac.o \
main.o \
uart.o

C_DEPS +=  \
adc.d \
dac.d \
main.d \
uart.d

C_DEPS_AS_ARGS +=  \
adc.d \
dac.d \
main.d \
uart.d

OUTPUT_FILE_PATH +=ATmega64M1_ADC_test.elf

OUTPUT_FILE_PATH_AS_ARGS +=ATmega64M1_ADC_test.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./adc.o: .././adc.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.3.3
	$(QUOTE)D:\WinAVR-20100110\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.209\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega64m1  -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./dac.o: .././dac.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.3.3
	$(QUOTE)D:\WinAVR-20100110\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.209\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega64m1  -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./main.o: .././main.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.3.3
	$(QUOTE)D:\WinAVR-20100110\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.209\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega64m1  -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./uart.o: .././uart.c
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.3.3
	$(QUOTE)D:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.209\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega64m1  -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 4.3.3
	$(QUOTE)D:\WinAVR-20100110\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="ATmega64M1_ADC_test.map" -Wl,-u,vfprintf -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections  -mmcu=atmega64m1  -lprintf_flt  
	@echo Finished building target: $@
	"D:\WinAVR-20100110\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "ATmega64M1_ADC_test.elf" "ATmega64M1_ADC_test.hex"
	"D:\WinAVR-20100110\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "ATmega64M1_ADC_test.elf" "ATmega64M1_ADC_test.eep" || exit 0
	"D:\WinAVR-20100110\bin\avr-objdump.exe" -h -S "ATmega64M1_ADC_test.elf" > "ATmega64M1_ADC_test.lss"
	"D:\WinAVR-20100110\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "ATmega64M1_ADC_test.elf" "ATmega64M1_ADC_test.srec"
	"D:\WinAVR-20100110\bin\avr-size.exe" "ATmega64M1_ADC_test.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "ATmega64M1_ADC_test.elf" "ATmega64M1_ADC_test.a" "ATmega64M1_ADC_test.hex" "ATmega64M1_ADC_test.lss" "ATmega64M1_ADC_test.eep" "ATmega64M1_ADC_test.map" "ATmega64M1_ADC_test.srec" "ATmega64M1_ADC_test.usersignatures"
	