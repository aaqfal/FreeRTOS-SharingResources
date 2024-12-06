#  Sharing Resources
This project is an implementation of a system based on STM32 that 

## Description
This project provides practical examples to understand the impact of sharing resources on the perrformance of multitasking systems. The exercise aims to demonstrate how task interactions can degrade system performance by observing the effects on LED flashing patterns when tasks compete for a shared resource. It also emphasizes the importance of managing shared resource access and the consequences of uncontrolled contention. With the main purpose to anal

## Task Overflow
1. **Initialization**
   - Configure GPIO of LED
   - Create tasks, with red LED task having highest priority
3. **Start Green Flashing Task**
   - Turn the Green LED ON
   - Accessing shared data function
   - Turn the Green LED OFF
   - Delay for 0.5 seconds
5. **Start Red Flashing Task**
   - Turn the Red LED ON
   - Accessing shared data function
   - Turn the Red LED OFF
   - Delay for 0.1 seconds
7. **Access Shared Data**
   - taskENTER_CRITICAL()
   - Check StartFlag
   - If StartFlag up (1), put it down (0)
   - Else show an alert
   - Simulate read/write operation
   - Set back StartFlag up
   - taskEXIT_CRITICAL()

## Hardware Used
- STM32 Microcontroller
- LED
- Resistor
