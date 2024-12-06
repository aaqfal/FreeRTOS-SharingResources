#  Sharing Resources
This project is an implementation of a system based on STM32 that demonstrate about sharing resource and the impact of performance in multitasking systems.

## Description
This project provides practical examples to understand the impact of sharing resources on the perrformance of multitasking systems. The exercise aims to demonstrate how task interactions can degrade system performance by observing the effects on LED flashing patterns when tasks compete for a shared resource. It also emphasizes the importance of managing shared resource access and the consequences of uncontrolled contention. That involves:
1. Task timing analysis, understanding he execution times of individual tasks in isolation and their collective behavior when running concurrently.
2. Resource contention, how shared resource access can lead to contention, resulting in degraded system responsiveness or potential failures.
3. Resource access control, the impact of applying mutual exclusion mechanisms, such as disabling interrupts, on system performance.

## Task Overflow
1. **Initialization**
   - Configure GPIO of LED
   - Create tasks, with orange LED task having highest priority
2. **Start Green Flashing Task**
   - Turn the Green LED ON
   - Accessing shared data function
   - Turn the Green LED OFF
   - Delay for 0.2 seconds
3. **Start Red Flashing Task**
   - Turn the Red LED ON
   - Accessing shared data function
   - Turn the Red LED OFF
   - Delay for 0.55 seconds
4. **Start Orange Flashing Task**
   - Toggle the Orange LED at 10Hz
5. **Access Shared Data**
   - Check StartFlag
   - If StartFlag up (1), put it down (0)
   - Else show an alert
   - Simulate read/write operation
   - Stop the alert
   - Set back StartFlag up
     
**Modified Accsess Shared Data**
- taskENTER_CRITICAL()
- Access Shared Data
- taskEXIT_CRITICAL()

## Hardware Used
- STM32 Microcontroller
- LED
- Resistor
