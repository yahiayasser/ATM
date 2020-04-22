/*
 * ATM_Server.h
 *
 *  Created on: Apr 5, 2020
 *      Author: Yahia
 */

#ifndef SERVER_H_
#define SERVER_H_



#include "Platform_Types.h"
#include "common_macros.h"

/* Module Version 1.0.0 */
#define SERVER_SW_MAJOR_VERSION           (1U)
#define SERVER_SW_MINOR_VERSION           (0U)
#define SERVER_SW_PATCH_VERSION           (0U)

#include "Server_DataTypes.h"
/* Checking between Server and Server_DataTypes Modules */
#if ((SERVER_SW_MAJOR_VERSION != SERVER_DATATYPES_SW_MAJOR_VERSION)\
 ||  (SERVER_SW_MINOR_VERSION != SERVER_DATATYPES_SW_MINOR_VERSION)\
 ||  (SERVER_SW_PATCH_VERSION != SERVER_DATATYPES_SW_PATCH_VERSION))
  #error "The SW version of Server_DataTypes.h does not match the expected version"
#endif


#include "MCAL.h"

#include "Server_interface.h"
/* Checking between Server and Server_interface Modules */
#if ((SERVER_SW_MAJOR_VERSION != SERVER_INTERFACE_SW_MAJOR_VERSION)\
 ||  (SERVER_SW_MINOR_VERSION != SERVER_INTERFACE_SW_MINOR_VERSION)\
 ||  (SERVER_SW_PATCH_VERSION != SERVER_INTERFACE_SW_PATCH_VERSION))
  #error "The SW version of Server_interface.h does not match the expected version"
#endif

#include "Abstraction.h"


#endif /* SERVER_H_ */
