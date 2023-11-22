| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- |

# _FreeRTOS Tasks Scheduling_

## Scheduling Algorithm Configuration in `freeRTOSconfig.h`

This README provides guidance on configuring and implementing various scheduling algorithms within our system. To employ different scheduling algorithms, adjust the following configurations within the `freeRTOSconfig.h` file as specified below:

### Prioritized Pre-emptive Scheduling with Time Slicing:

```cpp
#define configUSE_PREEMPTION 1
#define configUSE_TIME_SLICING 1
```

### Prioritized Pre-emptive Scheduling (without Time Slicing):

```cpp
#define configUSE_PREEMPTION 1
#define configUSE_TIME_SLICING 0
```

### Co-operative Scheduling:

```cpp
#define configUSE_PREEMPTION 0
#define configUSE_TIME_SLICING 0
```
