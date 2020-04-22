/*
 * main.h
 *
 *  Created on: 17 Apr 2020
 *      Author: Yahia
 */

#ifndef ATM_H_
#define ATM_H_

#include "Platform_Types.h"
#include "common_macros.h"

/* Module Version 1.0.0 */
#define ATM_SW_MAJOR_VERSION           (1U)
#define ATM_SW_MINOR_VERSION           (0U)
#define ATM_SW_PATCH_VERSION           (0U)
#include "ATM_DataTypes.h"

#include "ATM_Dependencies.h"
/* Checking between ATM and ATM_dependencies Modules */
#if ((ATM_SW_MAJOR_VERSION != ATM_DEPENDENCIES_SW_MAJOR_VERSION)\
 ||  (ATM_SW_MINOR_VERSION != ATM_DEPENDENCIES_SW_MINOR_VERSION)\
 ||  (ATM_SW_PATCH_VERSION != ATM_DEPENDENCIES_SW_PATCH_VERSION))
  #error "The SW version of ATM_dependencies.h does not match the expected version"
#endif

#include "Abstraction.h"

#include "ATM_interface.h"
/* Checking between ATM and ATM_interface Modules */
#if ((ATM_SW_MAJOR_VERSION != ATM_INTERFACE_SW_MAJOR_VERSION)\
 ||  (ATM_SW_MINOR_VERSION != ATM_INTERFACE_SW_MINOR_VERSION)\
 ||  (ATM_SW_PATCH_VERSION != ATM_INTERFACE_SW_PATCH_VERSION))
  #error "The SW version of ATM_interface.h does not match the expected version"
#endif

#include "ATM_CFG.h"
/* Checking between ATM and ATM_CONFIG Modules */
#if ((ATM_SW_MAJOR_VERSION != ATM_CFG_SW_MAJOR_VERSION)\
 ||  (ATM_SW_MINOR_VERSION != ATM_CFG_SW_MINOR_VERSION)\
 ||  (ATM_SW_PATCH_VERSION != ATM_CFG_SW_PATCH_VERSION))
  #error "The SW version of ATM_config.h does not match the expected version"
#endif

#include "Scheduler.h"
/* Checking between ATM and Scheduler Modules */
#if ((ATM_SW_MAJOR_VERSION != SCHEDULER_SW_MAJOR_VERSION)\
 ||  (ATM_SW_MINOR_VERSION != SCHEDULER_SW_MINOR_VERSION)\
 ||  (ATM_SW_PATCH_VERSION != SCHEDULER_SW_PATCH_VERSION))
  #error "The SW version of Scheduler.h does not match the expected version"
#endif

#include "ATM_Scheduler.h"

#endif /* ATM_H_ */
