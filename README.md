# ESP32

This repository contains a wide variety of projects for the ESP32 using Xtensa's integrated development framework, or ESP-IDF.

### Multiprocessing on ESP32:

The ESP-IDF uses a [modified version of FreeRTOS that implements symmetric multiprocessing](https://docs.espressif.com/projects/esp-idf/en/stable/api-guides/freertos-smp.html) across the ESP's two cores and is pretty much why this platform is so awesome.

In short, each core has it's own scheduler which will release ready tasks. In addition, each core has it's own interrupt controller. This means that the vanilla FreeRTOS critical section where the scheduler and interrupts are disabled only affect the core calling for the critical section, i.e. it only makes sure that the critical section is not preempted.

However, as the cores share memory, mutual exclusion still has to be ensured, which the [IDF provides an API for](https://docs.espressif.com/projects/esp-idf/en/stable/api-guides/freertos-smp.html#critical-sections).