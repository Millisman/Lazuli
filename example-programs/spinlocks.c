/*
 * SPDX-License-Identifier: GPL-3.0-only
 * This file is part of Lazuli.
 */

/**
 * @file
 * @brief Spinlocks demonstration program.
 * @copyright 2019-2020, Remi Andruccioli <remi.andruccioli@gmail.com>
 *
 * Example program to demonstrate the use of spinlocks in Lazuli.
 */

#include <stdint.h>

#include <Lazuli/common.h>
#include <Lazuli/lazuli.h>
#include <Lazuli/serial.h>
#include <Lazuli/spinlock.h>

#include <Lazuli/sys/arch/AVR/interrupts.h>
#include <Lazuli/sys/arch/AVR/registers.h>
#include <Lazuli/sys/arch/AVR/usart.h>

DEPENDENCY_ON_MODULE(SPINLOCK);
DEPENDENCY_ON_MODULE(SERIAL);

static Lz_Spinlock lock = LZ_SPINLOCK_INIT;

void
Task(void)
{
  Lz_Spinlock_Lock(&lock);
  Usart_PrintRawString(Lz_Task_GetName());
  Lz_Spinlock_Unlock(&lock);
}

static void
EnableSerialTransmission(void) {
  Lz_SerialConfiguration serialConfiguration;

  Lz_Serial_GetConfiguration(&serialConfiguration);
  serialConfiguration.enableFlags = LZ_SERIAL_ENABLE_TRANSMIT;
    serialConfiguration.speed = LZ_SERIAL_SPEED_9600;
  Lz_Serial_SetConfiguration(&serialConfiguration);
}

int
main(void)
{
  Lz_TaskConfiguration taskConfiguration;

  EnableSerialTransmission();

  Lz_TaskConfiguration_Init(&taskConfiguration);
  taskConfiguration.name =
    "Task 1 says: "
    "\"An ounce of prevention is better than a pound of cure.\"\r\n";
  Lz_RegisterTask(Task, &taskConfiguration);

  Lz_TaskConfiguration_Init(&taskConfiguration);
  taskConfiguration.name =
    "Task 2 says: "
    "\"Don't count your chickens before they hatch.\"\r\n";
  Lz_RegisterTask(Task, &taskConfiguration);

  Lz_TaskConfiguration_Init(&taskConfiguration);
  taskConfiguration.name =
    "Task 3 says: "
    "\"Beauty is in the eye of the beholder.\"\r\n";
  Lz_RegisterTask(Task, &taskConfiguration);

  Lz_TaskConfiguration_Init(&taskConfiguration);
  taskConfiguration.name =
    "Task 4 says: "
    "\"Fire is a good servant but a bad master.\"\r\n";
  Lz_RegisterTask(Task, &taskConfiguration);

  Usart_PrintRawString("\r\n");

  Lz_Run();

  for (;;);
}
