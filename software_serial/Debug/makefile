################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include software/src/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
fsociety_2.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
fsociety_2.list \

OBJCOPY_HEX += \
fsociety_2.hex \

OBJCOPY_BIN += \
fsociety_2.bin \


# All Target
all: fsociety_2.elf secondary-outputs

# Tool invocations
fsociety_2.elf: $(OBJS) $(USER_OBJS) D:\stm_workspace\fsociety_2\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "fsociety_2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\stm_workspace\fsociety_2\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="fsociety_2.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

fsociety_2.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "fsociety_2.list"
	@echo 'Finished building: $@'
	@echo ' '

fsociety_2.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "fsociety_2.hex"
	@echo 'Finished building: $@'
	@echo ' '

fsociety_2.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "fsociety_2.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
