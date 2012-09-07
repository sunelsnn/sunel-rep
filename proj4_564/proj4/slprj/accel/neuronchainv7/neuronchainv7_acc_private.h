/*
 * neuronchainv7_acc_private.h
 *
 * Real-Time Workshop code generation for Simulink model "neuronchainv7_acc.mdl".
 *
 * Model version              : 1.40
 * Real-Time Workshop version : 7.6  (R2010b)  03-Aug-2010
 * C source code generated on : Fri Dec  2 16:01:53 2011
 *
 * Target selection: accel.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_neuronchainv7_acc_private_h_
#define RTW_HEADER_neuronchainv7_acc_private_h_
#include "rtwtypes.h"
#ifndef RTW_COMMON_DEFINES_
# define RTW_COMMON_DEFINES_
#define rt_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
 ssSetErrorStatus(S, RT_MEMORY_ALLOCATION_ERROR);\
 }
#if !defined(_WIN32)
#define rt_FREE(ptr)                   if((ptr) != (NULL)) {\
 free((ptr));\
 (ptr) = (NULL);\
 }
#else

/* Visual and other windows compilers delcare free without const! */
#define rt_FREE(ptr)                   if((ptr) != (NULL)) {\
 free((void *)(ptr));\
 (ptr) = (NULL);\
 }
#endif
#endif                                 /* RTW_COMMON_DEFINES_ */

#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else

/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C08S16I32L64N64F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                 /* RTWTYPES_ID_C08S16I32L64N64F1 */
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

void neuronchainv7_fui(SimStruct *const S, real_T rtu_x, rtB_fui_neuronchainv7
  *localB, rtP_fui_neuronchainv7 *localP);
void neuronchainv7_Sigmoid2(SimStruct *const S, real_T rtu_x, real_T rtu_x_p,
  real_T rtu_x_m, real_T rtu_x_g, real_T rtu_x_f, real_T rtu_x_gk,
  rtB_Sigmoid2_neuronchainv7 *localB, rtP_Sigmoid2_neuronchainv7 *localP);
void neuronchainv7_Sigmoid1(SimStruct *const S, real_T rtu_x, real_T rtu_offset,
  rtB_Sigmoid1_neuronchainv7 *localB, rtP_Sigmoid1_neuronchainv7 *localP);
void neuronchainv7_Sigmoid2_i(SimStruct *const S, real_T rtu_x, real_T rtu_x_b,
  real_T rtu_x_m, real_T rtu_x_p, real_T rtu_x_m0, real_T rtu_offset,
  rtB_Sigmoid2_neuronchainv7_o *localB, rtP_Sigmoid2_neuronchainv7_n *localP);

#endif                                 /* RTW_HEADER_neuronchainv7_acc_private_h_ */
