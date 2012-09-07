#if 0

This file is not available for use in any application other than as a
  MATLAB(R) MEX file for use with the Simulink(R) product.
  If you do not have the Real-Time Workshop licensed, this file contains
  encrypted block names, etc. If you purchase the Real-Time Workshop,
  this file will contain full block descriptions and improved variable
  names.
#endif

/*
 * neuronchainv7_acc.c
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
#include <math.h>
#include "neuronchainv7_acc.h"
#include "neuronchainv7_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat                     S-Function
#define AccDefine1                     Accelerator_S-Function

/*
 * Output and update for atomic system:
 *    '<S14>/f(ui)'
 *    '<S14>/f(uj)'
 *    '<S14>/h(ui)'
 *    '<S15>/f(ui)'
 *    '<S15>/f(uj)'
 *    '<S15>/h(ui)'
 *    '<S16>/f(ui)'
 *    '<S16>/f(uj)'
 *    '<S16>/h(ui)'
 *    '<S17>/f(ui)'
 * ...
 */
void neuronchainv7_fui(SimStruct *const S, real_T rtu_x, rtB_fui_neuronchainv7
  *localB, rtP_fui_neuronchainv7 *localP)
{
  if (ssIsSampleHit(S, 1, 0)) {
    localB->B_0_0_0 = localP->P_0;
    localB->B_0_1_0 = localP->P_1;
    localB->B_0_2_0 = localP->P_2;
  }

  localB->B_0_8_0 = 1.0 / (muDoubleScalarExp((rtu_x - localB->B_0_0_0) *
    localB->B_0_1_0 * localP->P_3) + localB->B_0_2_0);
}

/*
 * Output and update for atomic system:
 *    '<S1124>/Sigmoid2'
 *    '<S1128>/Sigmoid2'
 *    '<S1129>/Sigmoid2'
 *    '<S1132>/Sigmoid2'
 *    '<S1133>/Sigmoid2'
 *    '<S1174>/Sigmoid2'
 *    '<S1178>/Sigmoid2'
 *    '<S1179>/Sigmoid2'
 *    '<S1182>/Sigmoid2'
 *    '<S1183>/Sigmoid2'
 * ...
 */
void neuronchainv7_Sigmoid2(SimStruct *const S, real_T rtu_x, real_T rtu_x_p,
  real_T rtu_x_m, real_T rtu_x_g, real_T rtu_x_f, real_T rtu_x_gk,
  rtB_Sigmoid2_neuronchainv7 *localB, rtP_Sigmoid2_neuronchainv7 *localP)
{
  real_T B_481_5_0[10];
  int32_T i;
  if (ssIsSampleHit(S, 1, 0)) {
    localB->B_481_0_0 = localP->P_0;
    localB->B_481_1_0 = localP->P_1;
    localB->B_481_2_0 = localP->P_2;
  }

  B_481_5_0[0] = (rtu_x - localB->B_481_0_0) * localB->B_481_1_0 * localP->P_3;
  B_481_5_0[1] = (rtu_x_p - localB->B_481_0_0) * localB->B_481_1_0 * localP->P_3;
  B_481_5_0[2] = (rtu_x_m - localB->B_481_0_0) * localB->B_481_1_0 * localP->P_3;
  B_481_5_0[3] = (rtu_x_g - localB->B_481_0_0) * localB->B_481_1_0 * localP->P_3;
  B_481_5_0[4] = (rtu_x_f - localB->B_481_0_0) * localB->B_481_1_0 * localP->P_3;
  B_481_5_0[5] = (rtu_x_gk - localB->B_481_0_0) * localB->B_481_1_0 *
    localP->P_3;
  B_481_5_0[6] = (rtu_x_gk - localB->B_481_0_0) * localB->B_481_1_0 *
    localP->P_3;
  B_481_5_0[7] = (rtu_x_gk - localB->B_481_0_0) * localB->B_481_1_0 *
    localP->P_3;
  B_481_5_0[8] = (rtu_x_gk - localB->B_481_0_0) * localB->B_481_1_0 *
    localP->P_3;
  B_481_5_0[9] = (rtu_x_gk - localB->B_481_0_0) * localB->B_481_1_0 *
    localP->P_3;
  for (i = 0; i < 10; i++) {
    localB->B_481_8_0[i] = 1.0 / (muDoubleScalarExp(B_481_5_0[i]) +
      localB->B_481_2_0);
  }
}

/*
 * Output and update for atomic system:
 *    '<S1125>/Sigmoid1'
 *    '<S1126>/Sigmoid1'
 *    '<S1127>/Sigmoid1'
 *    '<S1130>/Sigmoid1'
 *    '<S1131>/Sigmoid1'
 *    '<S1175>/Sigmoid1'
 *    '<S1176>/Sigmoid1'
 *    '<S1177>/Sigmoid1'
 *    '<S1180>/Sigmoid1'
 *    '<S1181>/Sigmoid1'
 * ...
 */
void neuronchainv7_Sigmoid1(SimStruct *const S, real_T rtu_x, real_T rtu_offset,
  rtB_Sigmoid1_neuronchainv7 *localB, rtP_Sigmoid1_neuronchainv7 *localP)
{
  real_T B_482_4_0;
  if (ssIsSampleHit(S, 1, 0)) {
    localB->B_482_0_0 = localP->P_0;
    localB->B_482_1_0 = localP->P_1;
  }

  B_482_4_0 = (rtu_x - rtu_offset) * localB->B_482_0_0 * localP->P_2;
  localB->B_482_7_0 = 1.0 / (muDoubleScalarExp(B_482_4_0) + localB->B_482_1_0);
}

/*
 * Output and update for atomic system:
 *    '<S1125>/Sigmoid2'
 *    '<S1126>/Sigmoid2'
 *    '<S1127>/Sigmoid2'
 *    '<S1130>/Sigmoid2'
 *    '<S1131>/Sigmoid2'
 *    '<S1175>/Sigmoid2'
 *    '<S1176>/Sigmoid2'
 *    '<S1177>/Sigmoid2'
 *    '<S1180>/Sigmoid2'
 *    '<S1181>/Sigmoid2'
 * ...
 */
void neuronchainv7_Sigmoid2_i(SimStruct *const S, real_T rtu_x, real_T rtu_x_b,
  real_T rtu_x_m, real_T rtu_x_p, real_T rtu_x_m0, real_T rtu_offset,
  rtB_Sigmoid2_neuronchainv7_o *localB, rtP_Sigmoid2_neuronchainv7_n *localP)
{
  real_T B_483_4_0[10];
  int32_T i;
  if (ssIsSampleHit(S, 1, 0)) {
    localB->B_483_0_0 = localP->P_0;
    localB->B_483_1_0 = localP->P_1;
  }

  B_483_4_0[0] = (rtu_x - rtu_offset) * localB->B_483_0_0 * localP->P_2;
  B_483_4_0[1] = (rtu_x_b - rtu_offset) * localB->B_483_0_0 * localP->P_2;
  B_483_4_0[2] = (rtu_x_m - rtu_offset) * localB->B_483_0_0 * localP->P_2;
  B_483_4_0[3] = (rtu_x_p - rtu_offset) * localB->B_483_0_0 * localP->P_2;
  B_483_4_0[4] = (rtu_x_m0 - rtu_offset) * localB->B_483_0_0 * localP->P_2;
  B_483_4_0[5] = (rtu_x_m0 - rtu_offset) * localB->B_483_0_0 * localP->P_2;
  B_483_4_0[6] = (rtu_x_m0 - rtu_offset) * localB->B_483_0_0 * localP->P_2;
  B_483_4_0[7] = (rtu_x_m0 - rtu_offset) * localB->B_483_0_0 * localP->P_2;
  B_483_4_0[8] = (rtu_x_m0 - rtu_offset) * localB->B_483_0_0 * localP->P_2;
  B_483_4_0[9] = (rtu_x_m0 - rtu_offset) * localB->B_483_0_0 * localP->P_2;
  for (i = 0; i < 10; i++) {
    localB->B_483_7_0[i] = 1.0 / (muDoubleScalarExp(B_483_4_0[i]) +
      localB->B_483_1_0);
  }
}

/* Outputs for root system: '<Root>' */
static void mdlOutputs(SimStruct *S, int_T tid)
{
  /* local block i/o variables */
  real_T B_540_2537_0;
  real_T B_540_2562_0;
  real_T B_540_2573_0;
  real_T B_540_2602_0;
  real_T B_540_2613_0;
  real_T B_540_2648_0;
  real_T B_540_2673_0;
  real_T B_540_2684_0;
  real_T B_540_2713_0;
  real_T B_540_2724_0;
  real_T B_540_2759_0;
  real_T B_540_2784_0;
  real_T B_540_2795_0;
  real_T B_540_2824_0;
  real_T B_540_2835_0;
  real_T B_540_610_0;
  real_T B_540_616_0;
  real_T B_540_622_0;
  real_T B_540_641_0;
  real_T B_540_647_0;
  real_T B_540_653_0;
  real_T B_540_659_0;
  real_T B_540_665_0;
  real_T B_540_683_0;
  real_T B_540_689_0;
  real_T B_540_695_0;
  real_T B_540_701_0;
  real_T B_540_707_0;
  real_T B_540_726_0;
  real_T B_540_732_0;
  real_T B_540_738_0;
  real_T B_540_744_0;
  real_T B_540_750_0;
  real_T B_540_905_0;
  real_T B_540_911_0;
  real_T B_540_917_0;
  real_T B_540_923_0;
  real_T B_540_929_0;
  real_T B_540_936_0;
  real_T B_540_942_0;
  real_T B_540_948_0;
  real_T B_540_954_0;
  real_T B_540_960_0;
  real_T B_540_967_0;
  real_T B_540_973_0;
  real_T B_540_979_0;
  real_T B_540_985_0;
  real_T B_540_991_0;
  real_T B_540_998_0;
  real_T B_540_1004_0;
  real_T B_540_1010_0;
  real_T B_540_1016_0;
  real_T B_540_1022_0;
  real_T B_540_897_0;
  real_T B_540_891_0;
  real_T B_540_883_0;
  real_T B_540_876_0;
  real_T B_540_870_0;
  real_T B_540_604_0;
  real_T B_540_598_0;
  real_T B_540_584_0;
  real_T B_540_586_0;
  real_T B_540_588_0;
  real_T B_540_590_0;
  real_T B_540_831_0;
  real_T B_540_833_0;
  real_T B_540_835_0;
  real_T B_540_837_0;
  real_T B_540_839_0;
  real_T B_540_841_0;
  real_T B_540_842_0;
  real_T B_540_843_0;
  real_T B_540_844_0;
  real_T B_540_845_0;
  real_T B_540_847_0;
  real_T B_540_848_0;
  real_T B_540_849_0;
  real_T B_540_850_0;
  real_T B_540_851_0;
  real_T B_540_853_0;
  real_T B_540_854_0;
  real_T B_540_855_0;
  real_T B_540_856_0;
  real_T B_540_857_0;
  real_T B_540_859_0;
  real_T B_540_860_0;
  real_T B_540_861_0;
  real_T B_540_862_0;
  real_T B_540_863_0;
  real_T B_540_871_0;
  real_T B_540_878_0;
  real_T B_540_885_0;
  real_T B_540_892_0;
  real_T B_540_899_0;
  real_T B_540_906_0;
  real_T B_540_912_0;
  real_T B_540_918_0;
  real_T B_540_924_0;
  real_T B_540_930_0;
  real_T B_540_937_0;
  real_T B_540_943_0;
  real_T B_540_949_0;
  real_T B_540_955_0;
  real_T B_540_961_0;
  real_T B_540_968_0;
  real_T B_540_974_0;
  real_T B_540_980_0;
  real_T B_540_986_0;
  real_T B_540_992_0;
  real_T B_540_2541_0[10];
  int32_T i;
  real_T B[5];
  real_T tmp[5];
  real_T tmp_0[5];
  real_T B_0[5];
  int64_T tmp_1;
  if (ssIsSampleHit(S, 1, 0)) {
    /* Scope: '<Root>/Scope8' */
    /* Call into Simulink for Scope */
    ssCallAccelRunBlock(S, 540, 0, SS_CALL_MDL_OUTPUTS);

    /* Scope: '<Root>/Scope9' */

    /* Call into Simulink for Scope */
    ssCallAccelRunBlock(S, 540, 1, SS_CALL_MDL_OUTPUTS);
  }

  /* Integrator: '<S211>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE;

  /* Clock: '<S211>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_4_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_5_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_4_0;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_2;
  }

  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode = (((BlockIO *) _ssGetBlockIO(S))
      ->B_540_5_0 > ((Parameters *) ssGetDefaultParam(S))->P_3);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_7_0 = ((BlockIO *) _ssGetBlockIO(S))
      ->B_540_2_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_7_0 = ((BlockIO *) _ssGetBlockIO(S))
      ->B_540_6_0;
  }

  /* Integrator: '<S203>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_8_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_g;

  /* Clock: '<S203>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_10_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_5;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_11_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_10_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_n = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_11_0 > ((Parameters *) ssGetDefaultParam(S))->P_6);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_n) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_12_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_8_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_12_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S208>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_13_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_a;

  /* Clock: '<S208>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_15_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_8;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_16_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_15_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_d = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_16_0 > ((Parameters *) ssGetDefaultParam(S))->P_9);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_d) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_17_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_13_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_17_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S214>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_18_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_e;

  /* Clock: '<S214>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_20_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_11;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_21_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_20_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_c = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_21_0 > ((Parameters *) ssGetDefaultParam(S))->P_12);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_c) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_22_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_18_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_22_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S220>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_23_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_h;

  /* Clock: '<S220>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_25_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_14;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_26_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_25_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_p = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_26_0 > ((Parameters *) ssGetDefaultParam(S))->P_15);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_p) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_27_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_23_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_27_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S221>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_28_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_b;

  /* Clock: '<S221>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_30_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_17;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_31_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_30_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_k = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_31_0 > ((Parameters *) ssGetDefaultParam(S))->P_18);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_k) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_32_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_28_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_32_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S215>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_33_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_m;

  /* Clock: '<S215>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_35_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_20;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_36_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_35_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_dd = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_36_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_21);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_dd) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_37_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_33_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_37_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S209>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_38_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_o;

  /* Clock: '<S209>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_40_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_23;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_41_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_40_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_a = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_41_0 > ((Parameters *) ssGetDefaultParam(S))->P_24);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_a) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_42_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_38_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_42_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S204>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_43_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_l;

  /* Clock: '<S204>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_45_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_26;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_46_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_45_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ao = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_46_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_27);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ao) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_47_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_43_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_47_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S217>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_48_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_j;

  /* Clock: '<S217>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_50_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_29;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_51_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_50_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_l = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_51_0 > ((Parameters *) ssGetDefaultParam(S))->P_30);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_l) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_52_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_48_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_52_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S218>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_53_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_j0;

  /* Clock: '<S218>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_55_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_32;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_56_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_55_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_b = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_56_0 > ((Parameters *) ssGetDefaultParam(S))->P_33);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_b) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_57_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_53_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_57_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S212>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_58_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_bd;

  /* Clock: '<S212>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_60_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_35;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_61_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_60_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ah = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_61_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_36);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ah) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_62_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_58_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_62_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S206>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_63_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_n;

  /* Clock: '<S206>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_65_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_38;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_66_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_65_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_m = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_66_0 > ((Parameters *) ssGetDefaultParam(S))->P_39);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_m) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_67_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_63_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_67_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S201>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_68_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_h1;

  /* Clock: '<S201>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_70_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_41;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_71_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_70_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_dc = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_71_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_42);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_dc) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_72_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_68_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_72_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S199>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_73_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_no;

  /* Clock: '<S199>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_75_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_44;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_76_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_75_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_kz = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_76_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_45);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_kz) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_77_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_73_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_77_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S223>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_78_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_k;

  /* Clock: '<S223>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_80_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_47;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_81_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_80_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_f = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_81_0 > ((Parameters *) ssGetDefaultParam(S))->P_48);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_f) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_82_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_78_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_82_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S205>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_83_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_c;

  /* Clock: '<S205>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_85_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_50;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_86_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_85_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pt = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_86_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_51);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pt) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_87_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_83_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_87_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S210>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_88_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_b0;

  /* Clock: '<S210>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_90_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_53;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_91_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_90_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_cl = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_91_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_54);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_cl) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_92_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_88_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_92_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S216>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_93_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_k4;

  /* Clock: '<S216>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_95_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_56;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_96_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_95_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_o = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_96_0 > ((Parameters *) ssGetDefaultParam(S))->P_57);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_o) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_97_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_93_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_97_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S222>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_98_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_gk;

  /* Clock: '<S222>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_100_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_59;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_101_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_100_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ci = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_101_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_60);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ci) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_102_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_98_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_102_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S219>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_103_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_p;

  /* Clock: '<S219>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_105_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_62;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_106_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_105_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_om = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_106_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_63);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_om) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_107_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_103_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_107_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S213>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_108_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_d;

  /* Clock: '<S213>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_110_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_65;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_111_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_110_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_fz = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_111_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_66);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_fz) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_112_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_108_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_112_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S207>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_113_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_cw;

  /* Clock: '<S207>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_115_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_68;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_116_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_115_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_my = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_116_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_69);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_my) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_117_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_113_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_117_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S202>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_118_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_aa;

  /* Clock: '<S202>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_120_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_71;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_121_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_120_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_by = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_121_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_72);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_by) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_122_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_118_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_122_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S200>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_123_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_oh;

  /* Clock: '<S200>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_125_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_74;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_126_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_125_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bm = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_126_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_75);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bm) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_127_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_123_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_127_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Scope: '<Root>/H1TO014352' */

  /* Call into Simulink for Scope */
  ssCallAccelRunBlock(S, 540, 128, SS_CALL_MDL_OUTPUTS);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_129_0 = ((D_Work *) ssGetRootDWork(S)
      )->TappedDelay3_X;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_130_0 = ((D_Work *) ssGetRootDWork(S)
      )->TappedDelay6_X;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_131_0 = ((D_Work *) ssGetRootDWork(S)
      )->TappedDelay3_X_m;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_132_0 = ((D_Work *) ssGetRootDWork(S)
      )->TappedDelay6_X_c;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_133_0 = ((D_Work *) ssGetRootDWork(S)
      )->TappedDelay6_X_f;
  }

  B_540_584_0 = ((Parameters *) ssGetDefaultParam(S))->P_82 * ssGetT(S);
  if (B_540_584_0 - muDoubleScalarFloor(B_540_584_0) >= 0.5) {
    B_540_604_0 = ((Parameters *) ssGetDefaultParam(S))->P_81;
  } else {
    B_540_604_0 = -((Parameters *) ssGetDefaultParam(S))->P_81;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_135_0[0] = ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_129_0 * B_540_604_0;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_135_0[1] = ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_130_0 * B_540_604_0;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_135_0[2] = ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_131_0 * B_540_604_0;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_135_0[3] = ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_132_0 * B_540_604_0;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_135_0[4] = ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_133_0 * B_540_604_0;
  if (ssIsMajorTimeStep(S)) {
    for (i = 0; i < 5; i++) {
      ((D_Work *) ssGetRootDWork(S))->Saturation_MODE[i] = ((BlockIO *)
        _ssGetBlockIO(S))->B_540_135_0[i] >= ((Parameters *) ssGetDefaultParam(S))
        ->P_83 ? 1 : ((BlockIO *) _ssGetBlockIO(S))->B_540_135_0[i] >
        ((Parameters *) ssGetDefaultParam(S))->P_84 ? 0 : -1;
    }
  }

  for (i = 0; i < 5; i++) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_829_0[i] = (((D_Work *) ssGetRootDWork
      (S))->Saturation_MODE[i] == 1 ? ((Parameters *) ssGetDefaultParam(S))
      ->P_83 : ((D_Work *) ssGetRootDWork(S))->Saturation_MODE[i] == -1 ?
      ((Parameters *) ssGetDefaultParam(S))->P_84 : ((BlockIO *) _ssGetBlockIO(S))
      ->B_540_135_0[i]) * ((Parameters *) ssGetDefaultParam(S))->P_85;
  }

  B_540_584_0 = ((Parameters *) ssGetDefaultParam(S))->P_87 * ssGetT(S);
  if (B_540_584_0 - muDoubleScalarFloor(B_540_584_0) >= 0.5) {
    B_540_604_0 = ((Parameters *) ssGetDefaultParam(S))->P_86;
  } else {
    B_540_604_0 = -((Parameters *) ssGetDefaultParam(S))->P_86;
  }

  B_540_584_0 = ((Parameters *) ssGetDefaultParam(S))->P_89 * ssGetT(S);
  if (B_540_584_0 - muDoubleScalarFloor(B_540_584_0) >= 0.5) {
    B_540_598_0 = ((Parameters *) ssGetDefaultParam(S))->P_88;
  } else {
    B_540_598_0 = -((Parameters *) ssGetDefaultParam(S))->P_88;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_140_0 = B_540_604_0 - B_540_598_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Saturation_MODE_e = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_140_0 >= ((Parameters *) ssGetDefaultParam(S))
      ->P_90 ? 1 : ((BlockIO *) _ssGetBlockIO(S))->B_540_140_0 > ((Parameters *)
      ssGetDefaultParam(S))->P_91 ? 0 : -1;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_141_0 = ((D_Work *) ssGetRootDWork(S))
    ->Saturation_MODE_e == 1 ? ((Parameters *) ssGetDefaultParam(S))->P_90 :
    ((D_Work *) ssGetRootDWork(S))->Saturation_MODE_e == -1 ? ((Parameters *)
    ssGetDefaultParam(S))->P_91 : ((BlockIO *) _ssGetBlockIO(S))->B_540_140_0;
  B_540_584_0 = ((Parameters *) ssGetDefaultParam(S))->P_93 * ssGetT(S);
  if (B_540_584_0 - muDoubleScalarFloor(B_540_584_0) >= 0.5) {
    B_540_598_0 = ((Parameters *) ssGetDefaultParam(S))->P_92;
  } else {
    B_540_598_0 = -((Parameters *) ssGetDefaultParam(S))->P_92;
  }

  B_540_584_0 = ((Parameters *) ssGetDefaultParam(S))->P_95 * ssGetT(S);
  if (B_540_584_0 - muDoubleScalarFloor(B_540_584_0) >= 0.5) {
    B_540_604_0 = ((Parameters *) ssGetDefaultParam(S))->P_94;
  } else {
    B_540_604_0 = -((Parameters *) ssGetDefaultParam(S))->P_94;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_144_0 = B_540_598_0 - B_540_604_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Saturation1_MODE = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_144_0 >= ((Parameters *) ssGetDefaultParam(S))
      ->P_96 ? 1 : ((BlockIO *) _ssGetBlockIO(S))->B_540_144_0 > ((Parameters *)
      ssGetDefaultParam(S))->P_97 ? 0 : -1;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_145_0 = ((D_Work *) ssGetRootDWork(S))
    ->Saturation1_MODE == 1 ? ((Parameters *) ssGetDefaultParam(S))->P_96 :
    ((D_Work *) ssGetRootDWork(S))->Saturation1_MODE == -1 ? ((Parameters *)
    ssGetDefaultParam(S))->P_97 : ((BlockIO *) _ssGetBlockIO(S))->B_540_144_0;
  B_540_584_0 = ((Parameters *) ssGetDefaultParam(S))->P_99 * ssGetT(S);
  if (B_540_584_0 - muDoubleScalarFloor(B_540_584_0) >= 0.5) {
    B_540_598_0 = ((Parameters *) ssGetDefaultParam(S))->P_98;
  } else {
    B_540_598_0 = -((Parameters *) ssGetDefaultParam(S))->P_98;
  }

  B_540_584_0 = ((Parameters *) ssGetDefaultParam(S))->P_101 * ssGetT(S);
  if (B_540_584_0 - muDoubleScalarFloor(B_540_584_0) >= 0.5) {
    B_540_604_0 = ((Parameters *) ssGetDefaultParam(S))->P_100;
  } else {
    B_540_604_0 = -((Parameters *) ssGetDefaultParam(S))->P_100;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_148_0 = B_540_598_0 - B_540_604_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Saturation_MODE_h = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_148_0 >= ((Parameters *) ssGetDefaultParam(S))
      ->P_102 ? 1 : ((BlockIO *) _ssGetBlockIO(S))->B_540_148_0 > ((Parameters *)
      ssGetDefaultParam(S))->P_103 ? 0 : -1;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_149_0 = ((D_Work *) ssGetRootDWork(S))
    ->Saturation_MODE_h == 1 ? ((Parameters *) ssGetDefaultParam(S))->P_102 :
    ((D_Work *) ssGetRootDWork(S))->Saturation_MODE_h == -1 ? ((Parameters *)
    ssGetDefaultParam(S))->P_103 : ((BlockIO *) _ssGetBlockIO(S))->B_540_148_0;
  B_540_584_0 = ((Parameters *) ssGetDefaultParam(S))->P_105 * ssGetT(S);
  if (B_540_584_0 - muDoubleScalarFloor(B_540_584_0) >= 0.5) {
    B_540_598_0 = ((Parameters *) ssGetDefaultParam(S))->P_104;
  } else {
    B_540_598_0 = -((Parameters *) ssGetDefaultParam(S))->P_104;
  }

  B_540_584_0 = ((Parameters *) ssGetDefaultParam(S))->P_107 * ssGetT(S);
  if (B_540_584_0 - muDoubleScalarFloor(B_540_584_0) >= 0.5) {
    B_540_604_0 = ((Parameters *) ssGetDefaultParam(S))->P_106;
  } else {
    B_540_604_0 = -((Parameters *) ssGetDefaultParam(S))->P_106;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_152_0 = B_540_598_0 - B_540_604_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Saturation1_MODE_m = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_152_0 >= ((Parameters *) ssGetDefaultParam(S))
      ->P_108 ? 1 : ((BlockIO *) _ssGetBlockIO(S))->B_540_152_0 > ((Parameters *)
      ssGetDefaultParam(S))->P_109 ? 0 : -1;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_153_0 = ((D_Work *) ssGetRootDWork(S))
    ->Saturation1_MODE_m == 1 ? ((Parameters *) ssGetDefaultParam(S))->P_108 :
    ((D_Work *) ssGetRootDWork(S))->Saturation1_MODE_m == -1 ? ((Parameters *)
    ssGetDefaultParam(S))->P_109 : ((BlockIO *) _ssGetBlockIO(S))->B_540_152_0;
  B_540_584_0 = ((Parameters *) ssGetDefaultParam(S))->P_111 * ssGetT(S);
  if (B_540_584_0 - muDoubleScalarFloor(B_540_584_0) >= 0.5) {
    B_540_598_0 = ((Parameters *) ssGetDefaultParam(S))->P_110;
  } else {
    B_540_598_0 = -((Parameters *) ssGetDefaultParam(S))->P_110;
  }

  B_540_584_0 = ((Parameters *) ssGetDefaultParam(S))->P_113 * ssGetT(S);
  if (B_540_584_0 - muDoubleScalarFloor(B_540_584_0) >= 0.5) {
    B_540_604_0 = ((Parameters *) ssGetDefaultParam(S))->P_112;
  } else {
    B_540_604_0 = -((Parameters *) ssGetDefaultParam(S))->P_112;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_156_0 = B_540_598_0 - B_540_604_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Saturation1_MODE_b = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_156_0 >= ((Parameters *) ssGetDefaultParam(S))
      ->P_114 ? 1 : ((BlockIO *) _ssGetBlockIO(S))->B_540_156_0 > ((Parameters *)
      ssGetDefaultParam(S))->P_115 ? 0 : -1;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_157_0 = ((D_Work *) ssGetRootDWork(S))
    ->Saturation1_MODE_b == 1 ? ((Parameters *) ssGetDefaultParam(S))->P_114 :
    ((D_Work *) ssGetRootDWork(S))->Saturation1_MODE_b == -1 ? ((Parameters *)
    ssGetDefaultParam(S))->P_115 : ((BlockIO *) _ssGetBlockIO(S))->B_540_156_0;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_828_0[0] = ((Parameters *)
    ssGetDefaultParam(S))->P_116 * ((BlockIO *) _ssGetBlockIO(S))->B_540_141_0;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_828_0[1] = ((Parameters *)
    ssGetDefaultParam(S))->P_116 * ((BlockIO *) _ssGetBlockIO(S))->B_540_145_0;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_828_0[2] = ((Parameters *)
    ssGetDefaultParam(S))->P_116 * ((BlockIO *) _ssGetBlockIO(S))->B_540_149_0;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_828_0[3] = ((Parameters *)
    ssGetDefaultParam(S))->P_116 * ((BlockIO *) _ssGetBlockIO(S))->B_540_153_0;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_828_0[4] = ((Parameters *)
    ssGetDefaultParam(S))->P_116 * ((BlockIO *) _ssGetBlockIO(S))->B_540_157_0;

  /* Integrator: '<S1125>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_l5;

  /* Integrator: '<S1126>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_bt;

  /* Integrator: '<S1127>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_mj;

  /* Integrator: '<S1130>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ks;

  /* Integrator: '<S1131>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_j4;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_1025_0[0] = (((BlockIO *) _ssGetBlockIO
    (S))->B_540_129_0 - ((BlockIO *) _ssGetBlockIO(S))->B_540_135_0[0]) *
    ((Parameters *) ssGetDefaultParam(S))->P_122;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_1025_0[1] = (((BlockIO *) _ssGetBlockIO
    (S))->B_540_130_0 - ((BlockIO *) _ssGetBlockIO(S))->B_540_135_0[1]) *
    ((Parameters *) ssGetDefaultParam(S))->P_122;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_1025_0[2] = (((BlockIO *) _ssGetBlockIO
    (S))->B_540_131_0 - ((BlockIO *) _ssGetBlockIO(S))->B_540_135_0[2]) *
    ((Parameters *) ssGetDefaultParam(S))->P_122;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_1025_0[3] = (((BlockIO *) _ssGetBlockIO
    (S))->B_540_132_0 - ((BlockIO *) _ssGetBlockIO(S))->B_540_135_0[3]) *
    ((Parameters *) ssGetDefaultParam(S))->P_122;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_1025_0[4] = (((BlockIO *) _ssGetBlockIO
    (S))->B_540_133_0 - ((BlockIO *) _ssGetBlockIO(S))->B_540_135_0[4]) *
    ((Parameters *) ssGetDefaultParam(S))->P_122;

  /* Scope: '<Root>/Scope' */

  /* Call into Simulink for Scope */
  ssCallAccelRunBlock(S, 540, 166, SS_CALL_MDL_OUTPUTS);

  /* Integrator: '<S1175>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_gi;

  /* Integrator: '<S1176>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_mr;

  /* Integrator: '<S1177>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_gz;

  /* Integrator: '<S1180>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_cs;

  /* Integrator: '<S1181>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ch;

  /* Scope: '<Root>/Scope1' */

  /* Call into Simulink for Scope */
  ssCallAccelRunBlock(S, 540, 172, SS_CALL_MDL_OUTPUTS);

  /* Integrator: '<S403>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_173_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ow;

  /* Clock: '<S403>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_175_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_129;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_176_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_175_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ag = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_176_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_130);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ag) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_177_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_173_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_177_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S397>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_178_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_nz;

  /* Clock: '<S397>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_180_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_132;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_181_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_180_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_181_0 > ((Parameters *) ssGetDefaultParam(S))->P_133);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_182_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_178_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_182_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S391>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_183_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_nr;

  /* Clock: '<S391>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_185_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_135;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_186_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_185_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ps = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_186_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_136);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ps) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_187_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_183_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_187_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S386>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_188_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_i;

  /* Clock: '<S386>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_190_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_138;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_191_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_190_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_k2 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_191_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_139);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_k2) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_192_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_188_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_192_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S384>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_193_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ix;

  /* Clock: '<S384>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_195_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_141;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_196_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_195_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j4 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_196_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_142);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j4) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_197_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_193_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_197_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S406>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_198_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ns;

  /* Clock: '<S406>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_200_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_144;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_201_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_200_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_g = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_201_0 > ((Parameters *) ssGetDefaultParam(S))->P_145);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_g) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_202_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_198_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_202_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S400>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_203_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_gw;

  /* Clock: '<S400>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_205_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_147;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_206_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_205_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_e = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_206_0 > ((Parameters *) ssGetDefaultParam(S))->P_148);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_e) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_207_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_203_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_207_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S394>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_208_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_g5;

  /* Clock: '<S394>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_210_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_150;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_211_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_210_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_dw = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_211_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_151);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_dw) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_212_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_208_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_212_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S389>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_213_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_dm;

  /* Clock: '<S389>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_215_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_153;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_216_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_215_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_h = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_216_0 > ((Parameters *) ssGetDefaultParam(S))->P_154);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_h) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_217_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_213_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_217_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S402>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_218_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_nb;

  /* Clock: '<S402>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_220_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_156;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_221_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_220_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_b3 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_221_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_157);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_b3) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_222_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_218_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_222_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S396>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_223_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_f;

  /* Clock: '<S396>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_225_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_159;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_226_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_225_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_gt = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_226_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_160);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_gt) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_227_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_223_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_227_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S388>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_228_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_h4;

  /* Clock: '<S388>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_230_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_162;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_231_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_230_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_et = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_231_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_163);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_et) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_232_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_228_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_232_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S393>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_233_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_dx;

  /* Clock: '<S393>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_235_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_165;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_236_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_235_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_o3 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_236_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_166);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_o3) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_237_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_233_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_237_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S399>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_238_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_g3;

  /* Clock: '<S399>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_240_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_168;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_241_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_240_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_m1 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_241_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_169);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_m1) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_242_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_238_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_242_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S405>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_243_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_km;

  /* Clock: '<S405>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_245_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_171;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_246_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_245_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ka = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_246_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_172);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ka) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_247_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_243_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_247_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S408>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_248_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_nc;

  /* Clock: '<S408>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_250_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_174;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_251_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_250_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_mg = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_251_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_175);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_mg) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_252_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_248_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_252_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S390>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_253_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_bk;

  /* Clock: '<S390>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_255_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_177;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_256_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_255_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_lx = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_256_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_178);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_lx) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_257_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_253_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_257_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S395>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_258_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_hg;

  /* Clock: '<S395>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_260_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_180;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_261_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_260_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j3 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_261_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_181);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j3) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_262_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_258_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_262_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S401>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_263_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_fz;

  /* Clock: '<S401>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_265_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_183;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_266_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_265_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pw = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_266_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_184);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pw) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_267_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_263_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_267_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S407>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_268_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ms;

  /* Clock: '<S407>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_270_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_186;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_271_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_270_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_aob = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_271_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_187);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_aob) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_272_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_268_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_272_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S404>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_273_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_gzl;

  /* Clock: '<S404>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_275_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_189;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_276_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_275_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_h2 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_276_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_190);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_h2) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_277_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_273_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_277_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S398>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_278_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_f3;

  /* Clock: '<S398>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_280_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_192;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_281_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_280_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_hr = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_281_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_193);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_hr) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_282_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_278_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_282_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S392>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_283_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_k1;

  /* Clock: '<S392>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_285_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_195;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_286_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_285_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ao5 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_286_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_196);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ao5) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_287_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_283_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_287_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S387>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_288_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_lk;

  /* Clock: '<S387>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_290_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_198;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_291_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_290_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_fw = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_291_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_199);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_fw) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_292_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_288_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_292_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S385>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_293_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_bn;

  /* Clock: '<S385>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_295_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_201;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_296_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_295_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bj = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_296_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_202);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bj) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_297_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_293_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_297_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Scope: '<Root>/Scope10' */

  /* Call into Simulink for Scope */
  ssCallAccelRunBlock(S, 540, 298, SS_CALL_MDL_OUTPUTS);

  /* Integrator: '<S588>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_299_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_jk;

  /* Clock: '<S588>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_301_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_204;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_302_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_301_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_he = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_302_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_205);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_he) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_303_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_299_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_303_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S582>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_304_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_dc;

  /* Clock: '<S582>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_306_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_207;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_307_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_306_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pi = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_307_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_208);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pi) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_308_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_304_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_308_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S576>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_309_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_pf;

  /* Clock: '<S576>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_311_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_210;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_312_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_311_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_l0 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_312_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_211);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_l0) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_313_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_309_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_313_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S571>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_314_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_hq;

  /* Clock: '<S571>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_316_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_213;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_317_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_316_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_mp = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_317_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_214);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_mp) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_318_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_314_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_318_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S569>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_319_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_mp;

  /* Clock: '<S569>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_321_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_216;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_322_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_321_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_fm = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_322_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_217);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_fm) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_323_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_319_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_323_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S591>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_324_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_fb;

  /* Clock: '<S591>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_326_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_219;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_327_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_326_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_dy = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_327_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_220);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_dy) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_328_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_324_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_328_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S585>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_329_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_gf;

  /* Clock: '<S585>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_331_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_222;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_332_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_331_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ko = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_332_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_223);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ko) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_333_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_329_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_333_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S579>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_334_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_an;

  /* Clock: '<S579>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_336_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_225;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_337_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_336_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_oo = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_337_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_226);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_oo) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_338_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_334_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_338_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S574>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_339_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ex;

  /* Clock: '<S574>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_341_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_228;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_342_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_341_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_oi = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_342_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_229);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_oi) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_343_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_339_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_343_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S587>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_344_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_if;

  /* Clock: '<S587>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_346_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_231;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_347_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_346_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j0 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_347_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_232);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j0) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_348_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_344_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_348_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S581>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_349_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_hb;

  /* Clock: '<S581>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_351_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_234;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_352_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_351_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_lo = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_352_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_235);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_lo) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_353_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_349_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_353_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S573>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_354_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_fa;

  /* Clock: '<S573>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_356_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_237;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_357_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_356_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_jo = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_357_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_238);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_jo) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_358_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_354_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_358_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S578>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_359_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_i4;

  /* Clock: '<S578>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_361_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_240;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_362_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_361_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_i = (((BlockIO *) _ssGetBlockIO
      (S))->B_540_362_0 > ((Parameters *) ssGetDefaultParam(S))->P_241);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_i) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_363_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_359_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_363_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S584>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_364_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_il;

  /* Clock: '<S584>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_366_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_243;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_367_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_366_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bz = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_367_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_244);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bz) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_368_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_364_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_368_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S590>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_369_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_nw;

  /* Clock: '<S590>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_371_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_246;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_372_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_371_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ib = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_372_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_247);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ib) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_373_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_369_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_373_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Scope: '<Root>/Scope12' */

  /* Call into Simulink for Scope */
  ssCallAccelRunBlock(S, 540, 374, SS_CALL_MDL_OUTPUTS);

  /* Integrator: '<S958>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_375_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_k3;

  /* Clock: '<S958>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_377_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_249;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_378_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_377_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pj = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_378_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_250);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pj) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_379_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_375_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_379_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S952>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_380_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_jy;

  /* Clock: '<S952>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_382_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_252;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_383_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_382_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pa = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_383_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_253);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pa) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_384_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_380_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_384_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S946>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_385_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ng;

  /* Clock: '<S946>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_387_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_255;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_388_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_387_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_g1 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_388_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_256);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_g1) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_389_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_385_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_389_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S941>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_390_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_pr;

  /* Clock: '<S941>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_392_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_258;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_393_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_392_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ea = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_393_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_259);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ea) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_394_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_390_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_394_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S939>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_395_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_hl;

  /* Clock: '<S939>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_397_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_261;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_398_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_397_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_if = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_398_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_262);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_if) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_399_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_395_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_399_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S961>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_400_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ep;

  /* Clock: '<S961>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_402_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_264;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_403_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_402_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ex = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_403_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_265);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ex) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_404_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_400_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_404_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S955>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_405_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_hq4;

  /* Clock: '<S955>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_407_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_267;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_408_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_407_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ig = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_408_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_268);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ig) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_409_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_405_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_409_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S949>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_410_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_e1;

  /* Clock: '<S949>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_412_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_270;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_413_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_412_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_n2 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_413_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_271);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_n2) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_414_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_410_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_414_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S944>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_415_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_cv;

  /* Clock: '<S944>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_417_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_273;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_418_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_417_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bl = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_418_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_274);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bl) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_419_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_415_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_419_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S957>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_420_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ne;

  /* Clock: '<S957>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_422_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_276;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_423_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_422_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ar = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_423_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_277);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ar) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_424_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_420_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_424_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S951>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_425_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_kd;

  /* Clock: '<S951>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_427_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_279;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_428_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_427_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_kx = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_428_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_280);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_kx) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_429_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_425_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_429_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S943>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_430_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_jq;

  /* Clock: '<S943>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_432_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_282;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_433_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_432_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pb = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_433_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_283);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pb) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_434_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_430_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_434_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S948>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_435_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ov;

  /* Clock: '<S948>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_437_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_285;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_438_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_437_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_k1 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_438_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_286);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_k1) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_439_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_435_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_439_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S954>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_440_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ck;

  /* Clock: '<S954>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_442_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_288;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_443_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_442_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_m2 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_443_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_289);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_m2) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_444_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_440_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_444_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S960>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_445_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_hc;

  /* Clock: '<S960>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_447_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_291;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_448_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_447_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_fq = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_448_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_292);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_fq) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_449_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_445_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_449_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Scope: '<Root>/Scope13' */

  /* Call into Simulink for Scope */
  ssCallAccelRunBlock(S, 540, 450, SS_CALL_MDL_OUTPUTS);

  /* Integrator: '<S33>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_451_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_bw;

  /* Clock: '<S33>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_453_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_294;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_454_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_453_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ib0 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_454_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_295);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ib0) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_455_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_451_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_455_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S27>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_456_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_kx;

  /* Clock: '<S27>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_458_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_297;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_459_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_458_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pr = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_459_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_298);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pr) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_460_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_456_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_460_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S21>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_461_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_nn;

  /* Clock: '<S21>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_463_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_300;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_464_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_463_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_az = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_464_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_301);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_az) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_465_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_461_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_465_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S16>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_466_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_di;

  /* Clock: '<S16>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_468_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_303;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_469_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_468_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pz = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_469_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_304);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pz) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_470_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_466_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_470_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S14>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_471_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_bc;

  /* Clock: '<S14>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_473_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_306;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_474_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_473_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_kd = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_474_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_307);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_kd) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_475_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_471_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_475_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S36>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_476_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_lf;

  /* Clock: '<S36>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_478_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_309;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_479_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_478_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pd = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_479_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_310);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pd) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_480_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_476_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_480_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S30>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_481_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_dt;

  /* Clock: '<S30>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_483_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_312;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_484_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_483_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ok = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_484_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_313);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ok) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_485_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_481_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_485_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S24>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_486_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_kso;

  /* Clock: '<S24>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_488_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_315;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_489_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_488_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pu = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_489_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_316);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pu) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_490_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_486_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_490_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S19>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_491_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ht;

  /* Clock: '<S19>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_493_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_318;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_494_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_493_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_kf = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_494_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_319);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_kf) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_495_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_491_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_495_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S32>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_496_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ls;

  /* Clock: '<S32>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_498_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_321;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_499_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_498_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_hb = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_499_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_322);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_hb) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_500_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_496_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_500_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S26>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_501_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_g5k;

  /* Clock: '<S26>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_503_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_324;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_504_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_503_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_n0 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_504_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_325);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_n0) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_505_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_501_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_505_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S18>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_506_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_lq;

  /* Clock: '<S18>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_508_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_327;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_509_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_508_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_da = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_509_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_328);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_da) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_510_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_506_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_510_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S23>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_511_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_af;

  /* Clock: '<S23>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_513_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_330;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_514_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_513_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_p2 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_514_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_331);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_p2) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_515_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_511_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_515_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S29>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_516_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ir;

  /* Clock: '<S29>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_518_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_333;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_519_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_518_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_g2 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_519_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_334);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_g2) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_520_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_516_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_520_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S35>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_521_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_m3;

  /* Clock: '<S35>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_523_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_336;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_524_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_523_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j1 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_524_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_337);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j1) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_525_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_521_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_525_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S38>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_526_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_jt;

  /* Clock: '<S38>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_528_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_339;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_529_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_528_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_lb = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_529_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_340);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_lb) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_530_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_526_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_530_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S20>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_531_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ah;

  /* Clock: '<S20>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_533_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_342;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_534_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_533_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ek = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_534_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_343);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ek) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_535_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_531_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_535_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S25>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_536_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_lp;

  /* Clock: '<S25>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_538_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_345;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_539_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_538_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_gf = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_539_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_346);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_gf) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_540_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_536_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_540_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S31>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_541_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_j2;

  /* Clock: '<S31>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_543_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_348;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_544_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_543_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_n3 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_544_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_349);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_n3) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_545_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_541_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_545_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S37>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_546_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_cc;

  /* Clock: '<S37>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_548_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_351;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_549_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_548_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_jg = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_549_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_352);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_jg) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_550_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_546_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_550_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S34>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_551_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_mq;

  /* Clock: '<S34>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_553_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_354;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_554_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_553_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_aj = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_554_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_355);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_aj) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_555_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_551_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_555_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S28>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_556_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ahl;

  /* Clock: '<S28>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_558_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_357;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_559_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_558_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_mx = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_559_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_358);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_mx) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_560_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_556_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_560_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S22>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_561_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ap;

  /* Clock: '<S22>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_563_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_360;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_564_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_563_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_i0 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_564_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_361);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_i0) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_565_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_561_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_565_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S17>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_566_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_al;

  /* Clock: '<S17>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_568_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_363;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_569_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_568_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_hw = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_569_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_364);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_hw) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_570_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_566_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_570_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Integrator: '<S15>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_571_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_fu;

  /* Clock: '<S15>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_573_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_366;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_574_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_573_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_cd = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_574_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_367);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_cd) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_575_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_571_0;
  } else {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_575_0 = ((BlockIO *) _ssGetBlockIO(S)
      )->B_540_6_0;
  }

  /* Scope: '<Root>/Scope14' */

  /* Call into Simulink for Scope */
  ssCallAccelRunBlock(S, 540, 576, SS_CALL_MDL_OUTPUTS);

  /* Integrator: '<S1225>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_kh;

  /* Integrator: '<S1226>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_n3;

  /* Integrator: '<S1227>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_by;

  /* Integrator: '<S1230>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ia;

  /* Integrator: '<S1231>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_jh;

  /* Scope: '<Root>/Scope2' */

  /* Call into Simulink for Scope */
  ssCallAccelRunBlock(S, 540, 582, SS_CALL_MDL_OUTPUTS);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj5);
  B_540_584_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj5.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_303_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj4);
  B_540_586_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_308_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj4.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj2, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj2);
  B_540_588_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_313_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj2.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj1, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj1);
  B_540_590_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj1.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_318_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj3, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj3);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_593_0 = (((B_540_584_0 + B_540_586_0) +
    B_540_588_0) + B_540_590_0) + ((BlockIO *) _ssGetBlockIO(S))->B_540_323_0 *
    ((BlockIO *) _ssGetBlockIO(S))->fuj3.B_0_8_0;

  /* Integrator: '<S589>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_594_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_j3;

  /* Clock: '<S589>/Clock' */
  B_540_598_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_596_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_374;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_597_0 = B_540_598_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_596_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_du = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_597_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_375);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_du) {
    B_540_598_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_594_0;
  } else {
    B_540_598_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_584_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj5.B_0_8_0 * B_540_598_0;

  /* Integrator: '<S583>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_600_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_d4;

  /* Clock: '<S583>/Clock' */
  B_540_604_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_602_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_377;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_603_0 = B_540_604_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_602_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j0p = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_603_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_378);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j0p) {
    B_540_604_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_600_0;
  } else {
    B_540_604_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_586_0 = B_540_604_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj4.B_0_8_0;

  /* Integrator: '<S577>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_606_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_d2;

  /* Clock: '<S577>/Clock' */
  B_540_610_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_608_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_380;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_609_0 = B_540_610_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_608_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_e2 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_609_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_381);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_e2) {
    B_540_610_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_606_0;
  } else {
    B_540_610_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_588_0 = B_540_610_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj2.B_0_8_0;

  /* Integrator: '<S572>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_612_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ckt;

  /* Clock: '<S572>/Clock' */
  B_540_616_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_614_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_383;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_615_0 = B_540_616_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_614_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_av = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_615_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_384);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_av) {
    B_540_616_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_612_0;
  } else {
    B_540_616_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_590_0 = B_540_616_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj1.B_0_8_0;

  /* Integrator: '<S570>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_618_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_go;

  /* Clock: '<S570>/Clock' */
  B_540_622_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_620_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_386;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_621_0 = B_540_622_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_620_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ao5w = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_621_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_387);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ao5w) {
    B_540_622_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_618_0;
  } else {
    B_540_622_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_624_0 = (((B_540_584_0 + B_540_586_0) +
    B_540_588_0) + B_540_590_0) + B_540_622_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->fuj3.B_0_8_0;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_630_0 = (((((BlockIO *) _ssGetBlockIO(S))
    ->fuj5.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->B_540_373_0 + ((BlockIO *)
    _ssGetBlockIO(S))->fuj4.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_368_0) + ((BlockIO *) _ssGetBlockIO(S))->fuj2.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_363_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->fuj1.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->B_540_358_0) + ((BlockIO *)
    _ssGetBlockIO(S))->fuj3.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_353_0;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_636_0 = (((((BlockIO *) _ssGetBlockIO(S))
    ->B_540_328_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj5.B_0_8_0 + ((BlockIO *)
    _ssGetBlockIO(S))->B_540_333_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->fuj4.B_0_8_0) + ((BlockIO *) _ssGetBlockIO(S))->B_540_338_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj2.B_0_8_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_343_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj1.B_0_8_0) + ((BlockIO *)
    _ssGetBlockIO(S))->B_540_348_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->fuj3.B_0_8_0;

  /* Integrator: '<S592>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_637_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_oa;

  /* Clock: '<S592>/Clock' */
  B_540_641_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_639_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_389;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_640_0 = B_540_641_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_639_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_fi = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_640_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_390);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_fi) {
    B_540_641_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_637_0;
  } else {
    B_540_641_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_584_0 = B_540_641_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj5.B_0_8_0;

  /* Integrator: '<S586>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_643_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ows;

  /* Clock: '<S586>/Clock' */
  B_540_647_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_645_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_392;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_646_0 = B_540_647_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_645_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_od = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_646_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_393);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_od) {
    B_540_647_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_643_0;
  } else {
    B_540_647_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_586_0 = B_540_647_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj4.B_0_8_0;

  /* Integrator: '<S580>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_649_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ej;

  /* Clock: '<S580>/Clock' */
  B_540_653_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_651_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_395;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_652_0 = B_540_653_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_651_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_jy = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_652_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_396);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_jy) {
    B_540_653_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_649_0;
  } else {
    B_540_653_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_588_0 = B_540_653_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj2.B_0_8_0;

  /* Integrator: '<S575>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_655_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_p0;

  /* Clock: '<S575>/Clock' */
  B_540_659_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_657_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_398;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_658_0 = B_540_659_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_657_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_hy = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_658_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_399);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_hy) {
    B_540_659_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_655_0;
  } else {
    B_540_659_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_590_0 = B_540_659_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj1.B_0_8_0;

  /* Integrator: '<S593>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_661_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_da;

  /* Clock: '<S593>/Clock' */
  B_540_665_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_663_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_401;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_664_0 = B_540_665_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_663_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ht = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_664_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_402);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ht) {
    B_540_665_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_661_0;
  } else {
    B_540_665_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_667_0 = (((B_540_584_0 + B_540_586_0) +
    B_540_588_0) + B_540_590_0) + B_540_665_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->fuj3.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj5_l, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj5_l);
  B_540_584_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj5_l.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_379_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj4_a, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj4_a);
  B_540_586_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_384_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj4_a.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj2_a, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj2_a);
  B_540_588_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_389_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj2_a.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj1_g, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj1_g);
  B_540_590_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj1_g.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_394_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj3_h, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj3_h);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_678_0 = (((B_540_584_0 + B_540_586_0) +
    B_540_588_0) + B_540_590_0) + ((BlockIO *) _ssGetBlockIO(S))->B_540_399_0 *
    ((BlockIO *) _ssGetBlockIO(S))->fuj3_h.B_0_8_0;

  /* Integrator: '<S959>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_679_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_oi;

  /* Clock: '<S959>/Clock' */
  B_540_683_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_681_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_404;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_682_0 = B_540_683_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_681_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_b0 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_682_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_405);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_b0) {
    B_540_683_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_679_0;
  } else {
    B_540_683_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_584_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj5_l.B_0_8_0 * B_540_683_0;

  /* Integrator: '<S953>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_685_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_do;

  /* Clock: '<S953>/Clock' */
  B_540_689_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_687_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_407;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_688_0 = B_540_689_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_687_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_fg = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_688_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_408);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_fg) {
    B_540_689_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_685_0;
  } else {
    B_540_689_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_586_0 = B_540_689_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj4_a.B_0_8_0;

  /* Integrator: '<S947>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_691_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_f0;

  /* Clock: '<S947>/Clock' */
  B_540_695_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_693_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_410;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_694_0 = B_540_695_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_693_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_mq = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_694_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_411);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_mq) {
    B_540_695_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_691_0;
  } else {
    B_540_695_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_588_0 = B_540_695_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj2_a.B_0_8_0;

  /* Integrator: '<S942>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_697_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_gfn;

  /* Clock: '<S942>/Clock' */
  B_540_701_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_699_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_413;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_700_0 = B_540_701_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_699_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j4u = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_700_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_414);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_j4u) {
    B_540_701_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_697_0;
  } else {
    B_540_701_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_590_0 = B_540_701_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj1_g.B_0_8_0;

  /* Integrator: '<S940>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_703_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_iv;

  /* Clock: '<S940>/Clock' */
  B_540_707_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_705_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_416;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_706_0 = B_540_707_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_705_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_i5 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_706_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_417);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_i5) {
    B_540_707_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_703_0;
  } else {
    B_540_707_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_709_0 = (((B_540_584_0 + B_540_586_0) +
    B_540_588_0) + B_540_590_0) + B_540_707_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->fuj3_h.B_0_8_0;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_715_0 = (((((BlockIO *) _ssGetBlockIO(S))
    ->fuj5_l.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->B_540_449_0 + ((BlockIO *)
    _ssGetBlockIO(S))->fuj4_a.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_444_0) + ((BlockIO *) _ssGetBlockIO(S))->fuj2_a.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_439_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->fuj1_g.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->B_540_434_0) + ((BlockIO *)
    _ssGetBlockIO(S))->fuj3_h.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_429_0;
  ((BlockIO *) _ssGetBlockIO(S))->B_540_721_0 = (((((BlockIO *) _ssGetBlockIO(S))
    ->B_540_404_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj5_l.B_0_8_0 + ((BlockIO *)
    _ssGetBlockIO(S))->B_540_409_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->fuj4_a.B_0_8_0) + ((BlockIO *) _ssGetBlockIO(S))->B_540_414_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj2_a.B_0_8_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_419_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj1_g.B_0_8_0) + ((BlockIO *)
    _ssGetBlockIO(S))->B_540_424_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->fuj3_h.B_0_8_0;

  /* Integrator: '<S962>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_722_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_mjo;

  /* Clock: '<S962>/Clock' */
  B_540_726_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_724_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_419;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_725_0 = B_540_726_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_724_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_l0b = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_725_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_420);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_l0b) {
    B_540_726_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_722_0;
  } else {
    B_540_726_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_584_0 = B_540_726_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj5_l.B_0_8_0;

  /* Integrator: '<S956>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_728_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_c5;

  /* Clock: '<S956>/Clock' */
  B_540_732_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_730_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_422;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_731_0 = B_540_732_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_730_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_og = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_731_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_423);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_og) {
    B_540_732_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_728_0;
  } else {
    B_540_732_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_586_0 = B_540_732_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj4_a.B_0_8_0;

  /* Integrator: '<S950>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_734_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_kf;

  /* Clock: '<S950>/Clock' */
  B_540_738_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_736_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_425;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_737_0 = B_540_738_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_736_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_gr = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_737_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_426);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_gr) {
    B_540_738_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_734_0;
  } else {
    B_540_738_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_588_0 = B_540_738_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj2_a.B_0_8_0;

  /* Integrator: '<S945>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_740_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_gkg;

  /* Clock: '<S945>/Clock' */
  B_540_744_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_742_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_428;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_743_0 = B_540_744_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_742_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_kp = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_743_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_429);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_kp) {
    B_540_744_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_740_0;
  } else {
    B_540_744_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_590_0 = B_540_744_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj1_g.B_0_8_0;

  /* Integrator: '<S963>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_746_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_mt;

  /* Clock: '<S963>/Clock' */
  B_540_750_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_748_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_431;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_749_0 = B_540_750_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_748_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_me = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_749_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_432);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_me) {
    B_540_750_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_746_0;
  } else {
    B_540_750_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_752_0 = (((B_540_584_0 + B_540_586_0) +
    B_540_588_0) + B_540_590_0) + B_540_750_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->fuj3_h.B_0_8_0;

  /* Scope: '<Root>/Scope3' */

  /* Call into Simulink for Scope */
  ssCallAccelRunBlock(S, 540, 753, SS_CALL_MDL_OUTPUTS);

  /* Scope: '<Root>/Scope4' */

  /* Call into Simulink for Scope */
  ssCallAccelRunBlock(S, 540, 754, SS_CALL_MDL_OUTPUTS);

  /* Scope: '<Root>/Scope5' */

  /* Call into Simulink for Scope */
  ssCallAccelRunBlock(S, 540, 755, SS_CALL_MDL_OUTPUTS);

  /* Scope: '<Root>/Scope6' */

  /* Call into Simulink for Scope */
  ssCallAccelRunBlock(S, 540, 756, SS_CALL_MDL_OUTPUTS);

  /* Scope: '<Root>/Scope7' */

  /* Call into Simulink for Scope */
  ssCallAccelRunBlock(S, 540, 757, SS_CALL_MDL_OUTPUTS);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj5_b, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj5_b);
  B_540_584_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj5_b.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_57_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj4_a5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj4_a5);
  B_540_586_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_62_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj4_a5.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj2_k, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj2_k);
  B_540_588_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_67_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj2_k.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj1_b, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj1_b);
  B_540_590_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj1_b.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_72_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj3_g, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj3_g);
  B_540_897_0 = (((B_540_584_0 + B_540_586_0) + B_540_588_0) + B_540_590_0) +
    ((BlockIO *) _ssGetBlockIO(S))->B_540_77_0 * ((BlockIO *) _ssGetBlockIO(S)
    )->fuj3_g.B_0_8_0;
  B_540_891_0 = (((((BlockIO *) _ssGetBlockIO(S))->fuj5_b.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_107_0 + ((BlockIO *) _ssGetBlockIO(S))->B_540_112_0
                   * ((BlockIO *) _ssGetBlockIO(S))->fuj4_a5.B_0_8_0) +
                  ((BlockIO *) _ssGetBlockIO(S))->B_540_117_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj2_k.B_0_8_0) + ((BlockIO *) _ssGetBlockIO(S))
                 ->B_540_122_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj1_b.B_0_8_0)
    + ((BlockIO *) _ssGetBlockIO(S))->B_540_127_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->fuj3_g.B_0_8_0;
  B_540_883_0 = (((((BlockIO *) _ssGetBlockIO(S))->fuj5_b.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_27_0 + ((BlockIO *) _ssGetBlockIO(S))
                   ->fuj4_a5.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))
                   ->B_540_22_0) + ((BlockIO *) _ssGetBlockIO(S))
                  ->fuj2_k.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->B_540_17_0)
                 + ((BlockIO *) _ssGetBlockIO(S))->fuj1_b.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_12_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->fuj3_g.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->B_540_7_0;
  B_540_876_0 = (((((BlockIO *) _ssGetBlockIO(S))->B_540_32_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj5_b.B_0_8_0 + ((BlockIO *) _ssGetBlockIO(S))
                   ->B_540_37_0 * ((BlockIO *) _ssGetBlockIO(S))
                   ->fuj4_a5.B_0_8_0) + ((BlockIO *) _ssGetBlockIO(S))
                  ->B_540_42_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj2_k.B_0_8_0)
                 + ((BlockIO *) _ssGetBlockIO(S))->B_540_47_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj1_b.B_0_8_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_52_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj3_g.B_0_8_0;
  B_540_870_0 = (((((BlockIO *) _ssGetBlockIO(S))->B_540_102_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj5_b.B_0_8_0 + ((BlockIO *) _ssGetBlockIO(S))
                   ->B_540_97_0 * ((BlockIO *) _ssGetBlockIO(S))
                   ->fuj4_a5.B_0_8_0) + ((BlockIO *) _ssGetBlockIO(S))
                  ->B_540_92_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj2_k.B_0_8_0)
                 + ((BlockIO *) _ssGetBlockIO(S))->B_540_87_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj1_b.B_0_8_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_82_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj3_g.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj5_m, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj5_m);
  B_540_584_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj5_m.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_177_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj4_m, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj4_m);
  B_540_586_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_182_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj4_m.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj2_i, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj2_i);
  B_540_588_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_187_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj2_i.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj1_n, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj1_n);
  B_540_590_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj1_n.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_192_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj3_i, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj3_i);
  B_0[0] = B_540_897_0;
  B_0[1] = B_540_891_0;
  B_0[2] = B_540_883_0;
  B_0[3] = B_540_876_0;
  B_0[4] = B_540_870_0;
  B[0] = (((B_540_584_0 + B_540_586_0) + B_540_588_0) + B_540_590_0) + ((BlockIO
    *) _ssGetBlockIO(S))->B_540_197_0 * ((BlockIO *) _ssGetBlockIO(S))
    ->fuj3_i.B_0_8_0;
  B[1] = (((((BlockIO *) _ssGetBlockIO(S))->fuj5_m.B_0_8_0 * ((BlockIO *)
             _ssGetBlockIO(S))->B_540_277_0 + ((BlockIO *) _ssGetBlockIO(S))
            ->B_540_282_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj4_m.B_0_8_0) +
           ((BlockIO *) _ssGetBlockIO(S))->B_540_287_0 * ((BlockIO *)
            _ssGetBlockIO(S))->fuj2_i.B_0_8_0) + ((BlockIO *) _ssGetBlockIO(S)
          )->B_540_292_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj1_n.B_0_8_0) +
    ((BlockIO *) _ssGetBlockIO(S))->B_540_297_0 * ((BlockIO *) _ssGetBlockIO(S)
    )->fuj3_i.B_0_8_0;
  B[2] = (((((BlockIO *) _ssGetBlockIO(S))->fuj5_m.B_0_8_0 * ((BlockIO *)
             _ssGetBlockIO(S))->B_540_247_0 + ((BlockIO *) _ssGetBlockIO(S))
            ->fuj4_m.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->B_540_242_0) +
           ((BlockIO *) _ssGetBlockIO(S))->fuj2_i.B_0_8_0 * ((BlockIO *)
            _ssGetBlockIO(S))->B_540_237_0) + ((BlockIO *) _ssGetBlockIO(S))
          ->fuj1_n.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->B_540_232_0) +
    ((BlockIO *) _ssGetBlockIO(S))->fuj3_i.B_0_8_0 * ((BlockIO *) _ssGetBlockIO
    (S))->B_540_227_0;
  B[3] = (((((BlockIO *) _ssGetBlockIO(S))->B_540_202_0 * ((BlockIO *)
             _ssGetBlockIO(S))->fuj5_m.B_0_8_0 + ((BlockIO *) _ssGetBlockIO(S)
            )->B_540_207_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj4_m.B_0_8_0) +
           ((BlockIO *) _ssGetBlockIO(S))->B_540_212_0 * ((BlockIO *)
            _ssGetBlockIO(S))->fuj2_i.B_0_8_0) + ((BlockIO *) _ssGetBlockIO(S)
          )->B_540_217_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj1_n.B_0_8_0) +
    ((BlockIO *) _ssGetBlockIO(S))->B_540_222_0 * ((BlockIO *) _ssGetBlockIO(S)
    )->fuj3_i.B_0_8_0;
  B[4] = (((((BlockIO *) _ssGetBlockIO(S))->B_540_272_0 * ((BlockIO *)
             _ssGetBlockIO(S))->fuj5_m.B_0_8_0 + ((BlockIO *) _ssGetBlockIO(S)
            )->B_540_267_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj4_m.B_0_8_0) +
           ((BlockIO *) _ssGetBlockIO(S))->B_540_262_0 * ((BlockIO *)
            _ssGetBlockIO(S))->fuj2_i.B_0_8_0) + ((BlockIO *) _ssGetBlockIO(S)
          )->B_540_257_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj1_n.B_0_8_0) +
    ((BlockIO *) _ssGetBlockIO(S))->B_540_252_0 * ((BlockIO *) _ssGetBlockIO(S)
    )->fuj3_i.B_0_8_0;
  tmp[0] = ((BlockIO *) _ssGetBlockIO(S))->B_540_593_0;
  tmp[1] = ((BlockIO *) _ssGetBlockIO(S))->B_540_624_0;
  tmp[2] = ((BlockIO *) _ssGetBlockIO(S))->B_540_630_0;
  tmp[3] = ((BlockIO *) _ssGetBlockIO(S))->B_540_636_0;
  tmp[4] = ((BlockIO *) _ssGetBlockIO(S))->B_540_667_0;
  tmp_0[0] = ((BlockIO *) _ssGetBlockIO(S))->B_540_678_0;
  tmp_0[1] = ((BlockIO *) _ssGetBlockIO(S))->B_540_709_0;
  tmp_0[2] = ((BlockIO *) _ssGetBlockIO(S))->B_540_715_0;
  tmp_0[3] = ((BlockIO *) _ssGetBlockIO(S))->B_540_721_0;
  tmp_0[4] = ((BlockIO *) _ssGetBlockIO(S))->B_540_752_0;
  for (i = 0; i < 5; i++) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_828_0[i] = (B_0[i] + B[i]) + ((BlockIO
      *) _ssGetBlockIO(S))->B_540_828_0[i];
    ((BlockIO *) _ssGetBlockIO(S))->B_540_829_0[i] = (tmp[i] + tmp_0[i]) +
      ((BlockIO *) _ssGetBlockIO(S))->B_540_829_0[i];
  }

  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj5_k, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj5_k);
  B_540_831_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj5_k.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_455_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj4_ma, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj4_ma);
  B_540_833_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_460_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj4_ma.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj2_d, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj2_d);
  B_540_835_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_465_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj2_d.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj1_bh, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj1_bh);
  B_540_837_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj1_bh.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_470_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj3_g2, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj3_g2);
  B_540_839_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_475_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj3_g2.B_0_8_0;
  B_540_841_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj5_k.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_555_0;
  B_540_842_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_560_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj4_ma.B_0_8_0;
  B_540_843_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_565_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj2_d.B_0_8_0;
  B_540_844_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_570_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj1_bh.B_0_8_0;
  B_540_845_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_575_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj3_g2.B_0_8_0;
  B_540_847_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj5_k.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_525_0;
  B_540_848_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj4_ma.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_520_0;
  B_540_849_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj2_d.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_515_0;
  B_540_850_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj1_bh.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_510_0;
  B_540_851_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj3_g2.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_505_0;
  B_540_853_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_480_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj5_k.B_0_8_0;
  B_540_854_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_485_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj4_ma.B_0_8_0;
  B_540_855_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_490_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj2_d.B_0_8_0;
  B_540_856_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_495_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj1_bh.B_0_8_0;
  B_540_857_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_500_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj3_g2.B_0_8_0;
  B_540_859_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_550_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj5_k.B_0_8_0;
  B_540_860_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_545_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj4_ma.B_0_8_0;
  B_540_861_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_540_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj2_d.B_0_8_0;
  B_540_862_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_535_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj1_bh.B_0_8_0;
  B_540_863_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_530_0 * ((BlockIO *)
    _ssGetBlockIO(S))->fuj3_g2.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj5_c, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj5_c);

  /* Integrator: '<S773>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_866_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ki;

  /* Clock: '<S773>/Clock' */
  B_540_870_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_868_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_434;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_869_0 = B_540_870_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_868_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_kc = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_869_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_435);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_kc) {
    B_540_870_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_866_0;
  } else {
    B_540_870_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_871_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj5_c.B_0_8_0 * B_540_870_0;

  /* Integrator: '<S767>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_872_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_px;

  /* Clock: '<S767>/Clock' */
  B_540_876_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_874_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_437;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_875_0 = B_540_876_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_874_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bk = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_875_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_438);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bk) {
    B_540_876_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_872_0;
  } else {
    B_540_876_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj4_k, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj4_k);
  B_540_878_0 = B_540_876_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj4_k.B_0_8_0;

  /* Integrator: '<S761>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_879_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ml;

  /* Clock: '<S761>/Clock' */
  B_540_883_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_881_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_440;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_882_0 = B_540_883_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_881_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_cf = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_882_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_441);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_cf) {
    B_540_883_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_879_0;
  } else {
    B_540_883_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj2_ab, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj2_ab);
  B_540_885_0 = B_540_883_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj2_ab.B_0_8_0;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj1_e, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj1_e);

  /* Integrator: '<S756>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_887_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_mi;

  /* Clock: '<S756>/Clock' */
  B_540_891_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_889_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_443;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_890_0 = B_540_891_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_889_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_dd1 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_890_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_444);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_dd1) {
    B_540_891_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_887_0;
  } else {
    B_540_891_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_892_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj1_e.B_0_8_0 * B_540_891_0;

  /* Integrator: '<S754>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_893_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_fn;

  /* Clock: '<S754>/Clock' */
  B_540_897_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_895_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_446;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_896_0 = B_540_897_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_895_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ic = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_896_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_447);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ic) {
    B_540_897_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_893_0;
  } else {
    B_540_897_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj3_k, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj3_k);
  B_540_899_0 = B_540_897_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj3_k.B_0_8_0;

  /* Integrator: '<S774>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_901_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_mpg;

  /* Clock: '<S774>/Clock' */
  B_540_905_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_903_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_449;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_904_0 = B_540_905_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_903_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ck = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_904_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_450);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ck) {
    B_540_905_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_901_0;
  } else {
    B_540_905_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_906_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj5_c.B_0_8_0 * B_540_905_0;

  /* Integrator: '<S768>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_907_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_i1;

  /* Clock: '<S768>/Clock' */
  B_540_911_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_909_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_452;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_910_0 = B_540_911_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_909_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_iz = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_910_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_453);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_iz) {
    B_540_911_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_907_0;
  } else {
    B_540_911_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_912_0 = B_540_911_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj4_k.B_0_8_0;

  /* Integrator: '<S762>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_913_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_hd;

  /* Clock: '<S762>/Clock' */
  B_540_917_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_915_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_455;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_916_0 = B_540_917_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_915_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_na = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_916_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_456);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_na) {
    B_540_917_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_913_0;
  } else {
    B_540_917_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_918_0 = B_540_917_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj2_ab.B_0_8_0;

  /* Integrator: '<S757>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_919_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_nd;

  /* Clock: '<S757>/Clock' */
  B_540_923_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_921_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_458;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_922_0 = B_540_923_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_921_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pjo = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_922_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_459);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pjo) {
    B_540_923_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_919_0;
  } else {
    B_540_923_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_924_0 = B_540_923_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj1_e.B_0_8_0;

  /* Integrator: '<S755>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_925_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_nek;

  /* Clock: '<S755>/Clock' */
  B_540_929_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_927_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_461;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_928_0 = B_540_929_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_927_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_hs = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_928_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_462);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_hs) {
    B_540_929_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_925_0;
  } else {
    B_540_929_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_930_0 = B_540_929_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj3_k.B_0_8_0;

  /* Integrator: '<S775>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_932_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_j0t;

  /* Clock: '<S775>/Clock' */
  B_540_936_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_934_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_464;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_935_0 = B_540_936_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_934_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_df = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_935_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_465);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_df) {
    B_540_936_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_932_0;
  } else {
    B_540_936_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_937_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj5_c.B_0_8_0 * B_540_936_0;

  /* Integrator: '<S769>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_938_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_jf;

  /* Clock: '<S769>/Clock' */
  B_540_942_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_940_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_467;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_941_0 = B_540_942_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_940_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_de = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_941_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_468);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_de) {
    B_540_942_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_938_0;
  } else {
    B_540_942_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_943_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj4_k.B_0_8_0 * B_540_942_0;

  /* Integrator: '<S763>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_944_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_et;

  /* Clock: '<S763>/Clock' */
  B_540_948_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_946_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_470;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_947_0 = B_540_948_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_946_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ju = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_947_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_471);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ju) {
    B_540_948_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_944_0;
  } else {
    B_540_948_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_949_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj2_ab.B_0_8_0 * B_540_948_0;

  /* Integrator: '<S758>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_950_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_du;

  /* Clock: '<S758>/Clock' */
  B_540_954_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_952_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_473;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_953_0 = B_540_954_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_952_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pq = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_953_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_474);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pq) {
    B_540_954_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_950_0;
  } else {
    B_540_954_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_955_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj1_e.B_0_8_0 * B_540_954_0;

  /* Integrator: '<S766>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_956_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_o2;

  /* Clock: '<S766>/Clock' */
  B_540_960_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_958_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_476;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_959_0 = B_540_960_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_958_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_np = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_959_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_477);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_np) {
    B_540_960_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_956_0;
  } else {
    B_540_960_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_961_0 = ((BlockIO *) _ssGetBlockIO(S))->fuj3_k.B_0_8_0 * B_540_960_0;

  /* Integrator: '<S776>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_963_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_gfb;

  /* Clock: '<S776>/Clock' */
  B_540_967_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_965_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_479;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_966_0 = B_540_967_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_965_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_naw = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_966_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_480);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_naw) {
    B_540_967_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_963_0;
  } else {
    B_540_967_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_968_0 = B_540_967_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj5_c.B_0_8_0;

  /* Integrator: '<S770>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_969_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_fq;

  /* Clock: '<S770>/Clock' */
  B_540_973_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_971_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_482;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_972_0 = B_540_973_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_971_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pr5 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_972_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_483);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pr5) {
    B_540_973_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_969_0;
  } else {
    B_540_973_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_974_0 = B_540_973_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj4_k.B_0_8_0;

  /* Integrator: '<S764>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_975_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_od;

  /* Clock: '<S764>/Clock' */
  B_540_979_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_977_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_485;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_978_0 = B_540_979_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_977_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_mc = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_978_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_486);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_mc) {
    B_540_979_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_975_0;
  } else {
    B_540_979_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_980_0 = B_540_979_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj2_ab.B_0_8_0;

  /* Integrator: '<S759>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_981_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_jw;

  /* Clock: '<S759>/Clock' */
  B_540_985_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_983_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_488;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_984_0 = B_540_985_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_983_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_k4 = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_984_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_489);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_k4) {
    B_540_985_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_981_0;
  } else {
    B_540_985_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_986_0 = B_540_985_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj1_e.B_0_8_0;

  /* Integrator: '<S772>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_987_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_iz;

  /* Clock: '<S772>/Clock' */
  B_540_991_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_989_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_491;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_990_0 = B_540_991_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_989_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ev = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_990_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_492);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_ev) {
    B_540_991_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_987_0;
  } else {
    B_540_991_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_992_0 = B_540_991_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj3_k.B_0_8_0;

  /* Integrator: '<S777>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_994_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_hv;

  /* Clock: '<S777>/Clock' */
  B_540_998_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_996_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_494;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_997_0 = B_540_998_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_996_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_oj = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_997_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_495);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_oj) {
    B_540_998_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_994_0;
  } else {
    B_540_998_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_584_0 = B_540_998_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj5_c.B_0_8_0;

  /* Integrator: '<S771>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_1000_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ph;

  /* Clock: '<S771>/Clock' */
  B_540_1004_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1002_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_497;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1003_0 = B_540_1004_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1002_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bn = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_1003_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_498);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bn) {
    B_540_1004_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_1000_0;
  } else {
    B_540_1004_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_586_0 = B_540_1004_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj4_k.B_0_8_0;

  /* Integrator: '<S765>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_1006_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ec;

  /* Clock: '<S765>/Clock' */
  B_540_1010_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1008_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_500;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1009_0 = B_540_1010_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1008_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pc = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_1009_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_501);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_pc) {
    B_540_1010_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_1006_0;
  } else {
    B_540_1010_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_588_0 = B_540_1010_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj2_ab.B_0_8_0;

  /* Integrator: '<S760>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_1012_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_ie;

  /* Clock: '<S760>/Clock' */
  B_540_1016_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1014_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_503;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1015_0 = B_540_1016_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1014_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_py = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_1015_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_504);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_py) {
    B_540_1016_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_1012_0;
  } else {
    B_540_1016_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_590_0 = B_540_1016_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj1_e.B_0_8_0;

  /* Integrator: '<S778>/Integrator' */
  ((BlockIO *) _ssGetBlockIO(S))->B_540_1018_0 = ((ContinuousStates *)
    ssGetContStates(S))->Integrator_CSTATE_co;

  /* Clock: '<S778>/Clock' */
  B_540_1022_0 = ssGetT(S);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1020_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_506;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1021_0 = B_540_1022_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1020_0;
  if (ssIsMajorTimeStep(S)) {
    ((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bc = (((BlockIO *)
      _ssGetBlockIO(S))->B_540_1021_0 > ((Parameters *) ssGetDefaultParam(S))
      ->P_507);
  }

  if (((D_Work *) ssGetRootDWork(S))->Switch1_Mode_bc) {
    B_540_1022_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_1018_0;
  } else {
    B_540_1022_0 = ((BlockIO *) _ssGetBlockIO(S))->B_540_6_0;
  }

  B_540_584_0 = (((B_540_584_0 + B_540_586_0) + B_540_588_0) + B_540_590_0) +
    B_540_1022_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj3_k.B_0_8_0;
  B_0[0] = (((B_540_831_0 + B_540_833_0) + B_540_835_0) + B_540_837_0) +
    B_540_839_0;
  B_0[1] = (((B_540_841_0 + B_540_842_0) + B_540_843_0) + B_540_844_0) +
    B_540_845_0;
  B_0[2] = (((B_540_847_0 + B_540_848_0) + B_540_849_0) + B_540_850_0) +
    B_540_851_0;
  B_0[3] = (((B_540_853_0 + B_540_854_0) + B_540_855_0) + B_540_856_0) +
    B_540_857_0;
  B_0[4] = (((B_540_859_0 + B_540_860_0) + B_540_861_0) + B_540_862_0) +
    B_540_863_0;
  B[0] = (((B_540_871_0 + B_540_878_0) + B_540_885_0) + B_540_892_0) +
    B_540_899_0;
  B[1] = (((B_540_906_0 + B_540_912_0) + B_540_918_0) + B_540_924_0) +
    B_540_930_0;
  B[2] = (((B_540_937_0 + B_540_943_0) + B_540_949_0) + B_540_955_0) +
    B_540_961_0;
  B[3] = (((B_540_968_0 + B_540_974_0) + B_540_980_0) + B_540_986_0) +
    B_540_992_0;
  B[4] = B_540_584_0;
  for (i = 0; i < 5; i++) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1025_0[i] = (B_0[i] + B[i]) +
      ((BlockIO *) _ssGetBlockIO(S))->B_540_1025_0[i];
  }

  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1029_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_508;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1035_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1029_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_471_0) * ((BlockIO *) _ssGetBlockIO(S))->hui.B_0_8_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_509 * ((BlockIO *) _ssGetBlockIO(S))->B_540_475_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_510;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_c, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_c);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_j, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_j);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_h, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_h);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1039_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_511;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1045_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_j.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_h.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1039_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_571_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_c.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_512 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_575_0) * ((Parameters *) ssGetDefaultParam(S))->P_513;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_l, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_l);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_d, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_d);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_l, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_l);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1049_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_514;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1055_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_d.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_l.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1049_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_466_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_l.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_515 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_470_0) * ((Parameters *) ssGetDefaultParam(S))->P_516;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_f, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_f);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_k, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_k);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_p, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_p);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1059_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_517;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1065_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_k.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_p.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1059_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_566_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_f.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_518 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_570_0) * ((Parameters *) ssGetDefaultParam(S))->P_519;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_o, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_o);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_m, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_m);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_b, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_b);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1069_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_520;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1075_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_m.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_b.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1069_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_506_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_o.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_521 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_510_0) * ((Parameters *) ssGetDefaultParam(S))->P_522;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_g, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_g);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_c, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_c);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_d, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_d);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1079_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_523;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1085_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_c.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_d.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1079_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_491_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_g.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_524 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_495_0) * ((Parameters *) ssGetDefaultParam(S))->P_525;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_b, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_b);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_kw, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_kw);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_de, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_de);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1089_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_526;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1095_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_kw.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_de.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1089_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_531_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_b.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_527 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_535_0) * ((Parameters *) ssGetDefaultParam(S))->P_528;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_oj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_oj);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_g, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_g);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_l5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_l5);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1099_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_529;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1105_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_g.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_l5.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1099_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_461_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_oj.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_530 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_465_0) * ((Parameters *) ssGetDefaultParam(S))->P_531;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_o2, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_o2);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_mz, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_mz);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_j, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_j);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1109_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_532;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1115_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_mz.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_j.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1109_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_561_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_o2.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_533 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_565_0) * ((Parameters *) ssGetDefaultParam(S))->P_534;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_gh, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_gh);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_b, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_b);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_h1, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_h1);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1119_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_535;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1125_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_b.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_h1.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1119_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_511_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_gh.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_536 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_515_0) * ((Parameters *) ssGetDefaultParam(S))->P_537;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_i, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_i);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_n, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_n);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_b4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_b4);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1129_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_538;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1135_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_n.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_b4.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1129_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_486_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_i.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_539 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_490_0) * ((Parameters *) ssGetDefaultParam(S))->P_540;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_a, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_a);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_gr, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_gr);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_l0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_l0);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1139_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_541;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1145_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_gr.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_l0.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1139_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_536_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_a.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_542 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_540_0) * ((Parameters *) ssGetDefaultParam(S))->P_543;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_e, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_e);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_o, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_o);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_a, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_a);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1149_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_544;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1155_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_o.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_a.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1149_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_501_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_e.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_545 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_505_0) * ((Parameters *) ssGetDefaultParam(S))->P_546;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_on, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_on);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_i, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_i);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_n, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_n);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1159_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_547;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1165_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_i.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_n.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1159_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_456_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_on.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_548 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_460_0) * ((Parameters *) ssGetDefaultParam(S))->P_549;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_el, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_el);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_mi, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_mi);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_e, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_e);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1169_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_550;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1175_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_mi.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_e.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1169_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_556_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_el.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_551 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_560_0) * ((Parameters *) ssGetDefaultParam(S))->P_552;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_p, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_p);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_a, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_a);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ld, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ld);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1179_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_553;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1185_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_a.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ld.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1179_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_516_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_p.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_554 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_520_0) * ((Parameters *) ssGetDefaultParam(S))->P_555;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_m, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_m);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_l, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_l);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_c, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_c);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1189_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_556;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1195_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_l.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_c.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1189_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_481_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_m.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_557 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_485_0) * ((Parameters *) ssGetDefaultParam(S))->P_558;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_co, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_co);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_o0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_o0);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ct, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ct);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1199_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_559;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1205_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_o0.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ct.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1199_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_541_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_co.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_560 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_545_0) * ((Parameters *) ssGetDefaultParam(S))->P_561;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ev, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ev);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_e, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_e);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_m, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_m);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1209_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_562;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1215_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_e.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_m.B_0_8_0 * ((BlockIO *)
    _ssGetBlockIO(S))->B_540_1209_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_496_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ev.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_563 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_500_0) * ((Parameters *) ssGetDefaultParam(S))->P_564;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_gp, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_gp);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_h, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_h);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_lv, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_lv);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1219_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_565;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1225_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_h.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_lv.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1219_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_451_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_gp.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_566 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_455_0) * ((Parameters *) ssGetDefaultParam(S))->P_567;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ei, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ei);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_cp, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_cp);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_i, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_i);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1229_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_568;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1235_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_cp.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_i.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1229_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_551_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ei.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_569 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_555_0) * ((Parameters *) ssGetDefaultParam(S))->P_570;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ele, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ele);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_hc, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_hc);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_i1, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_i1);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1239_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_571;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1245_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_hc.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_i1.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1239_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_521_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ele.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_572 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_525_0) * ((Parameters *) ssGetDefaultParam(S))->P_573;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_j, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_j);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_eh, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_eh);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_mz, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_mz);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1249_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_574;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1255_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_eh.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_mz.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1249_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_476_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_j.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_575 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_480_0) * ((Parameters *) ssGetDefaultParam(S))->P_576;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_am, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_am);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_on, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_on);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_lw, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_lw);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1259_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_577;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1265_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_on.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_lw.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1259_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_546_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_am.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_578 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_550_0) * ((Parameters *) ssGetDefaultParam(S))->P_579;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_n, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_n);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_hco, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_hco);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_p0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_p0);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1269_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_580;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1275_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_hco.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_p0.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1269_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_526_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_n.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_581 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_530_0) * ((Parameters *) ssGetDefaultParam(S))->P_582;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_h, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_h);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ki, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ki);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_k, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_k);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1279_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_583;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1285_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ki.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_k.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1279_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_73_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_h.B_0_8_0 - ((Parameters
    *) ssGetDefaultParam(S))->P_584 * ((BlockIO *) _ssGetBlockIO(S))->B_540_77_0)
    * ((Parameters *) ssGetDefaultParam(S))->P_585;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_bz, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_bz);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_p, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_p);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_lc, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_lc);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1289_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_586;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1295_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_p.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_lc.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1289_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_123_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_bz.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_587 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_127_0) * ((Parameters *) ssGetDefaultParam(S))->P_588;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_mx, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_mx);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ns, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ns);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_nq, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_nq);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1299_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_589;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1305_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ns.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_nq.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1299_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_68_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_mx.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_590 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_72_0) * ((Parameters *) ssGetDefaultParam(S))->P_591;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_of, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_of);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_f, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_f);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ef, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ef);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1309_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_592;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1315_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_f.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ef.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1309_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_118_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_of.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_593 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_122_0) * ((Parameters *) ssGetDefaultParam(S))->P_594;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_bc, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_bc);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ev, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ev);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_hw, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_hw);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1319_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_595;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1325_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ev.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_hw.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1319_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_8_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_bc.B_0_8_0 - ((Parameters
    *) ssGetDefaultParam(S))->P_596 * ((BlockIO *) _ssGetBlockIO(S))->B_540_12_0)
    * ((Parameters *) ssGetDefaultParam(S))->P_597;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_cd, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_cd);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_o1, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_o1);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_lp, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_lp);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1329_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_598;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1335_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_o1.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_lp.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1329_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_43_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_cd.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_599 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_47_0) * ((Parameters *) ssGetDefaultParam(S))->P_600;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_p4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_p4);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_f3, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_f3);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_d5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_d5);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1339_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_601;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1345_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_f3.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_d5.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1339_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_83_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_p4.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_602 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_87_0) * ((Parameters *) ssGetDefaultParam(S))->P_603;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_o5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_o5);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_fm, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_fm);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_jt, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_jt);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1349_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_604;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1355_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_fm.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_jt.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1349_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_63_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_o5.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_605 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_67_0) * ((Parameters *) ssGetDefaultParam(S))->P_606;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_fz, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_fz);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ih, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ih);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_l4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_l4);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1359_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_607;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1365_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ih.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_l4.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1359_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_113_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_fz.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_608 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_117_0) * ((Parameters *) ssGetDefaultParam(S))->P_609;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_a2, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_a2);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_cz, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_cz);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_f, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_f);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1369_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_610;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1375_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_cz.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_f.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1369_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_13_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_a2.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_611 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_17_0) * ((Parameters *) ssGetDefaultParam(S))->P_612;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_bu, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_bu);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_f1, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_f1);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ds, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ds);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1379_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_613;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1385_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_f1.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ds.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1379_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_38_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_bu.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_614 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_42_0) * ((Parameters *) ssGetDefaultParam(S))->P_615;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_d, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_d);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_kq, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_kq);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_kx, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_kx);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1389_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_616;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1395_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_kq.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_kx.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1389_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_88_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_d.B_0_8_0 - ((Parameters
    *) ssGetDefaultParam(S))->P_617 * ((BlockIO *) _ssGetBlockIO(S))->B_540_92_0)
    * ((Parameters *) ssGetDefaultParam(S))->P_618;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_m2, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_m2);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_nh, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_nh);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ma, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ma);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1399_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_619;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1405_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_nh.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ma.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1399_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_2_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_m2.B_0_8_0 - ((Parameters
    *) ssGetDefaultParam(S))->P_620 * ((BlockIO *) _ssGetBlockIO(S))->B_540_7_0)
    * ((Parameters *) ssGetDefaultParam(S))->P_621;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_k, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_k);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_jr, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_jr);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_at, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_at);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1409_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_622;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1415_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_jr.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_at.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1409_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_58_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_k.B_0_8_0 - ((Parameters
    *) ssGetDefaultParam(S))->P_623 * ((BlockIO *) _ssGetBlockIO(S))->B_540_62_0)
    * ((Parameters *) ssGetDefaultParam(S))->P_624;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ch, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ch);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ce, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ce);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_g, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_g);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1419_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_625;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1425_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ce.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_g.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1419_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_108_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ch.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_626 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_112_0) * ((Parameters *) ssGetDefaultParam(S))->P_627;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ko, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ko);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_a2, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_a2);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_no, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_no);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1429_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_628;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1435_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_a2.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_no.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1429_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_18_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ko.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_629 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_22_0) * ((Parameters *) ssGetDefaultParam(S))->P_630;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ib, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ib);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ig, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ig);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_gz, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_gz);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1439_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_631;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1445_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ig.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_gz.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1439_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_33_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ib.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_632 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_37_0) * ((Parameters *) ssGetDefaultParam(S))->P_633;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_dd, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_dd);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_al, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_al);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ms, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ms);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1449_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_634;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1455_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_al.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ms.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1449_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_93_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_dd.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_635 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_97_0) * ((Parameters *) ssGetDefaultParam(S))->P_636;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ki, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ki);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_pw, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_pw);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_kq, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_kq);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1459_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_637;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1465_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_pw.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_kq.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1459_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_48_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ki.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_638 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_52_0) * ((Parameters *) ssGetDefaultParam(S))->P_639;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_eh, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_eh);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_m2, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_m2);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_g4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_g4);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1469_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_640;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1475_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_m2.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_g4.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1469_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_53_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_eh.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_641 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_57_0) * ((Parameters *) ssGetDefaultParam(S))->P_642;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_i0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_i0);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_k5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_k5);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_nz, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_nz);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1479_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_643;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1485_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_k5.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_nz.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1479_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_103_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_i0.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_644 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_107_0) * ((Parameters *) ssGetDefaultParam(S))->P_645;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_fv, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_fv);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ff, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ff);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ez, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ez);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1489_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_646;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1495_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ff.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ez.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1489_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_23_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_fv.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_647 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_27_0) * ((Parameters *) ssGetDefaultParam(S))->P_648;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_m3, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_m3);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_jb, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_jb);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_bj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_bj);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1499_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_649;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1505_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_jb.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_bj.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1499_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_28_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_m3.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_650 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_32_0) * ((Parameters *) ssGetDefaultParam(S))->P_651;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_jt, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_jt);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ma, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ma);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_e5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_e5);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1509_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_652;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1515_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ma.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_e5.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1509_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_98_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_jt.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_653 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_102_0) * ((Parameters *) ssGetDefaultParam(S))->P_654;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_eo, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_eo);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_bg, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_bg);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_pz, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_pz);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1519_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_655;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1525_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_bg.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_pz.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1519_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_78_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_eo.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_656 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_82_0) * ((Parameters *) ssGetDefaultParam(S))->P_657;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ir, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ir);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_i3, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_i3);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_f5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_f5);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1529_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_658;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1535_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_i3.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_f5.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1529_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_193_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ir.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_659 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_197_0) * ((Parameters *) ssGetDefaultParam(S))->P_660;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ci, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ci);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_fe, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_fe);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_df, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_df);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1539_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_661;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1545_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_fe.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_df.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1539_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_293_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ci.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_662 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_297_0) * ((Parameters *) ssGetDefaultParam(S))->P_663;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_d1, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_d1);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ou, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ou);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_aj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_aj);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1549_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_664;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1555_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ou.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_aj.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1549_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_188_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_d1.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_665 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_192_0) * ((Parameters *) ssGetDefaultParam(S))->P_666;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_dt, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_dt);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_a0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_a0);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_cm, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_cm);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1559_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_667;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1565_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_a0.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_cm.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1559_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_288_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_dt.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_668 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_292_0) * ((Parameters *) ssGetDefaultParam(S))->P_669;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_a0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_a0);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_lp, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_lp);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_la, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_la);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1569_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_670;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1575_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_lp.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_la.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1569_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_228_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_a0.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_671 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_232_0) * ((Parameters *) ssGetDefaultParam(S))->P_672;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ka, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ka);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_a5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_a5);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_e1, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_e1);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1579_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_673;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1585_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_a5.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_e1.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1579_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_213_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ka.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_674 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_217_0) * ((Parameters *) ssGetDefaultParam(S))->P_675;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_e5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_e5);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_i5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_i5);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_jtt, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_jtt);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1589_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_676;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1595_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_i5.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_jtt.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1589_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_253_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_e5.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_677 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_257_0) * ((Parameters *) ssGetDefaultParam(S))->P_678;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_l5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_l5);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_aa, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_aa);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_j4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_j4);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1599_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_679;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1605_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_aa.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_j4.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1599_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_183_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_l5.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_680 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_187_0) * ((Parameters *) ssGetDefaultParam(S))->P_681;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_hb, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_hb);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_i4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_i4);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_cj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_cj);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1609_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_682;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1615_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_i4.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_cj.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1609_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_283_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_hb.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_683 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_287_0) * ((Parameters *) ssGetDefaultParam(S))->P_684;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_p0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_p0);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_l0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_l0);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_dt, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_dt);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1619_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_685;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1625_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_l0.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_dt.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1619_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_233_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_p0.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_686 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_237_0) * ((Parameters *) ssGetDefaultParam(S))->P_687;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ld, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ld);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_cf, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_cf);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_kj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_kj);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1629_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_688;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1635_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_cf.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_kj.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1629_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_208_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ld.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_689 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_212_0) * ((Parameters *) ssGetDefaultParam(S))->P_690;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_lp, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_lp);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_kqa, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_kqa);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ii, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ii);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1639_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_691;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1645_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_kqa.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ii.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1639_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_258_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_lp.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_692 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_262_0) * ((Parameters *) ssGetDefaultParam(S))->P_693;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_i3, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_i3);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_nk, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_nk);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_d5o, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_d5o);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1649_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_694;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1655_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_nk.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_d5o.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1649_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_223_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_i3.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_695 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_227_0) * ((Parameters *) ssGetDefaultParam(S))->P_696;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_m4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_m4);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_fa, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_fa);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_o, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_o);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1659_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_697;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1665_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_fa.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_o.B_0_8_0 * ((BlockIO
    *) _ssGetBlockIO(S))->B_540_1659_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_178_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_m4.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_698 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_182_0) * ((Parameters *) ssGetDefaultParam(S))->P_699;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_k5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_k5);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_lz, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_lz);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_bf, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_bf);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1669_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_700;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1675_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_lz.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_bf.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1669_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_278_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_k5.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_701 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_282_0) * ((Parameters *) ssGetDefaultParam(S))->P_702;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_p2, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_p2);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_jv, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_jv);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_hl, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_hl);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1679_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_703;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1685_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_jv.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_hl.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1679_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_238_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_p2.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_704 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_242_0) * ((Parameters *) ssGetDefaultParam(S))->P_705;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_oh, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_oh);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_jd, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_jd);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ctc, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ctc);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1689_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_706;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1695_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_jd.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ctc.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1689_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_203_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_oh.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_707 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_207_0) * ((Parameters *) ssGetDefaultParam(S))->P_708;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ao, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ao);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_k0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_k0);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ctk, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ctk);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1699_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_709;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1705_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_k0.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ctk.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1699_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_263_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ao.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_710 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_267_0) * ((Parameters *) ssGetDefaultParam(S))->P_711;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_op, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_op);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ihf, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ihf);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_iit, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_iit);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1709_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_712;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1715_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ihf.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_iit.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1709_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_218_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_op.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_713 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_222_0) * ((Parameters *) ssGetDefaultParam(S))->P_714;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_hb2, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_hb2);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_g2, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_g2);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_jj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_jj);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1719_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_715;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1725_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_g2.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_jj.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1719_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_173_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_hb2.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_716 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_177_0) * ((Parameters *) ssGetDefaultParam(S))->P_717;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_iz, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_iz);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_czl, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_czl);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_pb, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_pb);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1729_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_718;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1735_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_czl.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_pb.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1729_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_273_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_iz.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_719 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_277_0) * ((Parameters *) ssGetDefaultParam(S))->P_720;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_hq, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_hq);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_bd, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_bd);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ix, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ix);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1739_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_721;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1745_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_bd.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ix.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1739_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_243_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_hq.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_722 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_247_0) * ((Parameters *) ssGetDefaultParam(S))->P_723;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_bt, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_bt);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_i1, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_i1);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_oe, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_oe);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1749_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_724;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1755_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_i1.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_oe.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1749_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_198_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_bt.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_725 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_202_0) * ((Parameters *) ssGetDefaultParam(S))->P_726;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_lb, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_lb);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_jc, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_jc);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_oev, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_oev);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1759_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_727;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1765_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_jc.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_oev.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1759_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_268_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_lb.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_728 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_272_0) * ((Parameters *) ssGetDefaultParam(S))->P_729;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_la, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_la);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ck, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ck);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_fd, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_fd);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1769_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_730;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1775_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ck.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_fd.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1769_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_248_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_la.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_731 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_252_0) * ((Parameters *) ssGetDefaultParam(S))->P_732;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_al, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_al);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_nc, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_nc);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_dx, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_dx);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1779_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_733;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1785_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_nc.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_dx.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1779_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_319_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_al.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_734 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_323_0) * ((Parameters *) ssGetDefaultParam(S))->P_735;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_gw, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_gw);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_maq, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_maq);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_bs, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_bs);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1789_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_736;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1795_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_maq.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_bs.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1789_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_618_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_gw.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_737 * B_540_622_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_738;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_kiy, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_kiy);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_id, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_id);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_fi, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_fi);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1799_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_739;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1805_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_id.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_fi.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1799_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_314_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_kiy.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_740 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_318_0) * ((Parameters *) ssGetDefaultParam(S))->P_741;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_bx, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_bx);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_oj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_oj);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_cb, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_cb);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1809_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_742;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1815_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_oj.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_cb.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1809_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_612_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_bx.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_743 * B_540_616_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_744;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ek, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ek);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_p0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_p0);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_au, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_au);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1819_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_745;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1825_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_p0.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_au.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1819_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_354_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ek.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_746 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_358_0) * ((Parameters *) ssGetDefaultParam(S))->P_747;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_l5u, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_l5u);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_fl, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_fl);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_i2, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_i2);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1829_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_748;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1835_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_fl.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_i2.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1829_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_339_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_l5u.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_749 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_343_0) * ((Parameters *) ssGetDefaultParam(S))->P_750;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_mm, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_mm);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_i5e, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_i5e);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_c2, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_c2);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1839_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_751;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1845_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_i5e.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_c2.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1839_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_655_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_mm.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_752 * B_540_659_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_753;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_n5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_n5);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_czx, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_czx);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_gx, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_gx);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1849_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_754;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1855_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_czx.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_gx.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1849_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_309_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_n5.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_755 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_313_0) * ((Parameters *) ssGetDefaultParam(S))->P_756;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_bxn, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_bxn);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_m2w, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_m2w);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_lf, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_lf);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1859_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_757;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1865_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_m2w.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_lf.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1859_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_606_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_bxn.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_758 * B_540_610_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_759;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_fs, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_fs);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_f4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_f4);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_aj2, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_aj2);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1869_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_760;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1875_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_f4.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_aj2.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1869_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_359_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_fs.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_761 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_363_0) * ((Parameters *) ssGetDefaultParam(S))->P_762;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_k5l, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_k5l);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_fel, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_fel);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_pw, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_pw);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1879_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_763;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1885_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_fel.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_pw.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1879_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_334_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_k5l.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_764 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_338_0) * ((Parameters *) ssGetDefaultParam(S))->P_765;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ah, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ah);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_of, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_of);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_me, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_me);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1889_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_766;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1895_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_of.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_me.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1889_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_649_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ah.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_767 * B_540_653_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_768;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_pu, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_pu);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_j5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_j5);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_mj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_mj);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1899_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_769;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1905_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_j5.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_mj.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1899_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_349_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_pu.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_770 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_353_0) * ((Parameters *) ssGetDefaultParam(S))->P_771;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ac, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ac);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_hf, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_hf);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ps, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ps);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1909_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_772;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1915_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_hf.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ps.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1909_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_304_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ac.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_773 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_308_0) * ((Parameters *) ssGetDefaultParam(S))->P_774;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_cq, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_cq);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_nf, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_nf);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_cf, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_cf);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1919_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_775;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1925_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_nf.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_cf.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1919_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_600_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_cq.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_776 * B_540_604_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_777;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_l5n, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_l5n);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_jk, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_jk);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_aty, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_aty);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1929_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_778;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1935_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_jk.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_aty.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1929_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_364_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_l5n.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_779 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_368_0) * ((Parameters *) ssGetDefaultParam(S))->P_780;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_bq, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_bq);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_dv, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_dv);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_bx, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_bx);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1939_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_781;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1945_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_dv.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_bx.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1939_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_329_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_bq.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_782 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_333_0) * ((Parameters *) ssGetDefaultParam(S))->P_783;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_kg, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_kg);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_hs, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_hs);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_fn, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_fn);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1949_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_784;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1955_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_hs.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_fn.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1949_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_643_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_kg.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_785 * B_540_647_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_786;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_nn, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_nn);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_grg, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_grg);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_jn, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_jn);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1959_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_787;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1965_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_grg.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_jn.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1959_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_344_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_nn.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_788 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_348_0) * ((Parameters *) ssGetDefaultParam(S))->P_789;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ex, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ex);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_dk, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_dk);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_mg, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_mg);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1969_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_790;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1975_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_dk.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_mg.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1969_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_299_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ex.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_791 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_303_0) * ((Parameters *) ssGetDefaultParam(S))->P_792;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_nj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_nj);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_nw, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_nw);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_kn, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_kn);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1979_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_793;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1985_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_nw.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_kn.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1979_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_594_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_nj.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_794 * B_540_598_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_795;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_eu, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_eu);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_pj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_pj);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_c0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_c0);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1989_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_796;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_1995_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_pj.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_c0.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1989_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_369_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_eu.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_797 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_373_0) * ((Parameters *) ssGetDefaultParam(S))->P_798;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_kic, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_kic);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_kn, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_kn);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ow, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ow);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1999_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_799;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2005_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_kn.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ow.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1999_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_324_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_kic.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_800 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_328_0) * ((Parameters *) ssGetDefaultParam(S))->P_801;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_f4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_f4);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_mia, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_mia);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_dj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_dj);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2009_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_802;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2015_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_mia.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_dj.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2009_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_637_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_f4.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_803 * B_540_641_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_804;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_m4j, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_m4j);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_jbd, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_jbd);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_o3, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_o3);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2019_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_805;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2025_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_jbd.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_o3.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2019_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_661_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_m4j.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_806 * B_540_665_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_807;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_n5k, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_n5k);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_kl, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_kl);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_jt4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_jt4);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2029_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_808;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2035_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_kl.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_jt4.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2029_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_893_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_n5k.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_809 * B_540_897_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_810;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_in, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_in);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_gn, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_gn);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_lwo, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_lwo);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2039_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_811;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2045_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_gn.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_lwo.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2039_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_925_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_in.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_812 * B_540_929_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_813;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_bqm, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_bqm);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_a0n, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_a0n);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_mjr, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_mjr);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2049_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_814;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2055_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_a0n.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_mjr.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2049_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_887_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_bqm.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_815 * B_540_891_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_816;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_fj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_fj);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ew, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ew);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_gi, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_gi);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2059_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_817;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2065_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ew.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_gi.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2059_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_919_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_fj.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_818 * B_540_923_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_819;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_bo, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_bo);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_p4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_p4);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ag, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ag);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2069_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_820;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2075_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_p4.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ag.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2069_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_950_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_bo.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_821 * B_540_954_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_822;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_lv, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_lv);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_fk, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_fk);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_nf, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_nf);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2079_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_823;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2085_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_fk.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_nf.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2079_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_981_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_lv.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_824 * B_540_985_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_825;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_nq, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_nq);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_et, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_et);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_hf, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_hf);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2089_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_826;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2095_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_et.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_hf.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2089_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_1012_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_nq.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_827 * B_540_1016_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_828;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_jc, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_jc);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_bq, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_bq);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ot, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ot);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2099_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_829;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2105_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_bq.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ot.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2099_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_879_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_jc.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_830 * B_540_883_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_831;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_mr, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_mr);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_kwd, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_kwd);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_lf1, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_lf1);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2109_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_832;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2115_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_kwd.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_lf1.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2109_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_913_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_mr.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_833 * B_540_917_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_834;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_m5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_m5);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_mzg, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_mzg);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_i21, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_i21);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2119_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_835;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2125_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_mzg.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_i21.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2119_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_944_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_m5.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_836 * B_540_948_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_837;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_jp, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_jp);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_dq, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_dq);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_oj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_oj);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2129_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_838;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2135_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_dq.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_oj.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2129_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_975_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_jp.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_839 * B_540_979_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_840;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ix, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ix);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ja, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ja);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_d3, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_d3);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2139_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_841;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2145_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ja.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_d3.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2139_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_1006_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ix.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_842 * B_540_1010_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_843;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_chy, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_chy);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_c4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_c4);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_g5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_g5);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2149_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_844;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2155_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_c4.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_g5.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2149_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_956_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_chy.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_845 * B_540_960_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_846;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ad, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ad);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_jbh, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_jbh);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_pbt, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_pbt);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2159_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_847;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2165_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_jbh.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_pbt.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2159_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_872_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ad.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_848 * B_540_876_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_849;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_lj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_lj);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_da, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_da);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_j3, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_j3);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2169_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_850;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2175_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_da.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_j3.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2169_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_907_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_lj.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_851 * B_540_911_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_852;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_io, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_io);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_bi, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_bi);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_mh, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_mh);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2179_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_853;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2185_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_bi.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_mh.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2179_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_938_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_io.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_854 * B_540_942_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_855;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_adl, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_adl);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_md, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_md);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_jh, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_jh);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2189_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_856;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2195_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_md.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_jh.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2189_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_969_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_adl.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_857 * B_540_973_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_858;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_aw, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_aw);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_mg, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_mg);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_gu, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_gu);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2199_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_859;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2205_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_mg.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_gu.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2199_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_1000_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_aw.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_860 * B_540_1004_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_861;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_cs, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_cs);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_d1, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_d1);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ja, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ja);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2209_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_862;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2215_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_d1.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ja.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2209_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_987_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_cs.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_863 * B_540_991_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_864;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_km, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_km);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_il, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_il);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_gj, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_gj);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2219_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_865;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2225_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_il.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_gj.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2219_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_866_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_km.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_866 * B_540_870_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_867;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_pm, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_pm);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_j0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_j0);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_oz, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_oz);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2229_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_868;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2235_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_j0.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_oz.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2229_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_901_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_pm.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_869 * B_540_905_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_870;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_lpe, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_lpe);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_nsc, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_nsc);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_hd, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_hd);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2239_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_871;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2245_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_nsc.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_hd.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2239_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_932_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_lpe.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_872 * B_540_936_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_873;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_b5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_b5);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_fd, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_fd);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_j4l, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_j4l);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2249_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_874;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2255_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_fd.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_j4l.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2249_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_963_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_b5.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_875 * B_540_967_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_876;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_jw, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_jw);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_cv, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_cv);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_er, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_er);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2259_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_877;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2265_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_cv.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_er.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2259_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_994_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_jw.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_878 * B_540_998_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_879;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_af, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_af);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_np, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_np);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ir, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ir);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2269_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_880;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2275_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_np.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ir.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2269_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_1018_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_af.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_881 * B_540_1022_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_882;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_o1, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_o1);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_pc, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_pc);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_mq, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_mq);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2279_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_883;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2285_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_pc.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_mq.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2279_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_395_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_o1.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_884 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_399_0) * ((Parameters *) ssGetDefaultParam(S))->P_885;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ht, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ht);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_dc, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_dc);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_pn, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_pn);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2289_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_886;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2295_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_dc.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_pn.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2289_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_703_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ht.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_887 * B_540_707_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_888;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_fx, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_fx);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_n5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_n5);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_hx, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_hx);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2299_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_889;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2305_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_n5.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_hx.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2299_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_390_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_fx.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_890 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_394_0) * ((Parameters *) ssGetDefaultParam(S))->P_891;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_nu, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_nu);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_gh, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_gh);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_jw, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_jw);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2309_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_892;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2315_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_gh.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_jw.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2309_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_697_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_nu.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_893 * B_540_701_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_894;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ij, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ij);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ov, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ov);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_eo, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_eo);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2319_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_895;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2325_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ov.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_eo.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2319_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_430_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ij.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_896 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_434_0) * ((Parameters *) ssGetDefaultParam(S))->P_897;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_pmf, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_pmf);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_k5m, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_k5m);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_hwr, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_hwr);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2329_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_898;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2335_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_k5m.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_hwr.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2329_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_415_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_pmf.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_899 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_419_0) * ((Parameters *) ssGetDefaultParam(S))->P_900;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_jf, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_jf);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_d1j, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_d1j);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_et, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_et);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2339_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_901;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2345_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_d1j.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_et.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2339_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_740_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_jf.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_902 * B_540_744_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_903;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_kf, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_kf);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_fv, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_fv);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_lwp, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_lwp);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2349_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_904;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2355_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_fv.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_lwp.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2349_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_385_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_kf.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_905 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_389_0) * ((Parameters *) ssGetDefaultParam(S))->P_906;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_mc, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_mc);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_f4v, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_f4v);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_cq, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_cq);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2359_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_907;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2365_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_f4v.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_cq.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2359_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_691_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_mc.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_908 * B_540_695_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_909;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_mo, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_mo);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_d3, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_d3);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_p5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_p5);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2369_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_910;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2375_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_d3.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_p5.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2369_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_435_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_mo.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_911 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_439_0) * ((Parameters *) ssGetDefaultParam(S))->P_912;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_f5, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_f5);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_dm, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_dm);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_e0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_e0);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2379_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_913;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2385_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_dm.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_e0.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2379_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_410_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_f5.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_914 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_414_0) * ((Parameters *) ssGetDefaultParam(S))->P_915;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_m4b, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_m4b);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_a1, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_a1);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_oze, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_oze);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2389_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_916;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2395_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_a1.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_oze.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2389_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_734_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_m4b.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_917 * B_540_738_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_918;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_a3, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_a3);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_c0, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_c0);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ac, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ac);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2399_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_919;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2405_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_c0.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ac.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2399_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_425_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_a3.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_920 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_429_0) * ((Parameters *) ssGetDefaultParam(S))->P_921;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_gm, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_gm);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_eu, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_eu);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_jb, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_jb);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2409_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_922;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2415_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_eu.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_jb.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2409_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_380_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_gm.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_923 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_384_0) * ((Parameters *) ssGetDefaultParam(S))->P_924;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ma, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ma);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_oj3, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_oj3);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_a4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_a4);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2419_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_925;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2425_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_oj3.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_a4.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2419_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_685_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ma.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_926 * B_540_689_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_927;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_d4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_d4);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_cx, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_cx);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_im, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_im);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2429_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_928;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2435_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_cx.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_im.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2429_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_440_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_d4.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_929 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_444_0) * ((Parameters *) ssGetDefaultParam(S))->P_930;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_elw, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_elw);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ed, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ed);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_e4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_e4);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2439_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_931;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2445_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ed.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_e4.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2439_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_405_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_elw.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_932 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_409_0) * ((Parameters *) ssGetDefaultParam(S))->P_933;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_a1, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_a1);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_fu, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_fu);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_pm, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_pm);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2449_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_934;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2455_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_fu.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_pm.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2449_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_728_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_a1.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_935 * B_540_732_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_936;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_ll, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_ll);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_oe, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_oe);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ak, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ak);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2459_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_937;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2465_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_oe.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ak.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2459_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_420_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_ll.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_938 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_424_0) * ((Parameters *) ssGetDefaultParam(S))->P_939;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_nz, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_nz);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_f4e, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_f4e);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_bz, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_bz);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2469_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_940;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2475_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_f4e.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_bz.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2469_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_375_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_nz.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_941 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_379_0) * ((Parameters *) ssGetDefaultParam(S))->P_942;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_p0c, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_p0c);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_it, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_it);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_gl, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_gl);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2479_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_943;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2485_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_it.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_gl.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2479_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_679_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_p0c.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_944 * B_540_683_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_945;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_hs, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_hs);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_kc, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_kc);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_lm, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_lm);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2489_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_946;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2495_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_kc.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_lm.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2489_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_445_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_hs.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_947 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_449_0) * ((Parameters *) ssGetDefaultParam(S))->P_948;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_lg, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_lg);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_lk, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_lk);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_dd, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_dd);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2499_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_949;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2505_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_lk.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_dd.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2499_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_400_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_lg.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_950 * ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_404_0) * ((Parameters *) ssGetDefaultParam(S))->P_951;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_k3, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_k3);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_nr, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_nr);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_ge, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_ge);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2509_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_952;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2515_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_nr.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_ge.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2509_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_722_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_k3.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_953 * B_540_726_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_954;
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->hui_e3, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->hui_e3);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, &((BlockIO *)
    _ssGetBlockIO(S))->fui_ng, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fui_ng);
  neuronchainv7_fui(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, &((BlockIO *)
    _ssGetBlockIO(S))->fuj_h4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->fuj_h4);
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2519_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_955;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2525_0 = ((((BlockIO *) _ssGetBlockIO(S))
    ->fui_ng.B_0_8_0 * ((BlockIO *) _ssGetBlockIO(S))->fuj_h4.B_0_8_0 *
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2519_0 - ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_746_0) * ((BlockIO *) _ssGetBlockIO(S))->hui_e3.B_0_8_0 -
    ((Parameters *) ssGetDefaultParam(S))->P_956 * B_540_750_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_957;
  if (ssIsSampleHit(S, 1, 0)) {
    for (i = 0; i < 10; i++) {
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2757_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_958[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2756_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_959[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2755_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_960[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2754_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_961[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2753_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_962[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2752_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_963[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2751_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_964[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2750_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_965[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2749_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_966[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2748_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_967[i];
    }
  }

  /* MATLABFcn: '<S7>/MATLAB Fcn' */

  /* Call into Simulink to run the Matlab Fcn block. */
  ssCallAccelRunBlock(S, 540, 2536, SS_CALL_MDL_OUTPUTS);

  /* Integrator: '<S1124>/Integrator' */
  B_540_2537_0 = ((ContinuousStates *) ssGetContStates(S))
    ->Integrator_CSTATE_mqu;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1124>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2538, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2539_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_969;
  }

  neuronchainv7_Sigmoid2(S, 0.0, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_162_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2539_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid2,
                         (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2538_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2537_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid1,
                    (rtP_fui_neuronchainv7 *) &((Parameters *) ssGetDefaultParam
                     (S))->Sigmoid1);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2546_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1.B_0_8_0 - B_540_2537_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_970;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2536_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_p, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_p);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1125>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2548, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_162_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2536_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_i,
                           (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_i);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2548_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_i.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2554_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_971;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2556_0 = ((((B_540_584_0 - B_540_2537_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_p.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_159_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_828_0[0]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2554_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_972;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2536_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_e, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_e);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1126>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2558, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_162_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2536_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_m,
                           (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_m);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2558_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_m.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  /* Integrator: '<S1128>/Integrator' */
  B_540_2562_0 = ((ContinuousStates *) ssGetContStates(S))->Integrator_CSTATE_py;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2565_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_974;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2567_0 = ((((B_540_584_0 - B_540_2562_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_e.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_160_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_828_0[1]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2565_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_975;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2536_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_a, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_a);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1127>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2569, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_159_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2536_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_p,
                           (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_p);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2569_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_p.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  /* Integrator: '<S1129>/Integrator' */
  B_540_2573_0 = ((ContinuousStates *) ssGetContStates(S))->Integrator_CSTATE_or;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2576_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_977;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2578_0 = ((((B_540_584_0 - B_540_2573_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_a.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_161_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_828_0[2]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2576_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_978;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1128>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2579, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2580_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_979;
  }

  neuronchainv7_Sigmoid2(S, 0.0, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_162_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2580_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_l,
                         (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_l);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2579_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_l.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2562_0, &((BlockIO *) _ssGetBlockIO(S))
                    ->Sigmoid1_pt, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_pt);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2587_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_pt.B_0_8_0 - B_540_2562_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_980;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1129>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2588, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2589_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_981;
  }

  neuronchainv7_Sigmoid2(S, 0.0, ((BlockIO *) _ssGetBlockIO(S))->B_540_160_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_159_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2589_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_b,
                         (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_b);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2588_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_b.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2573_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_c,
                    (rtP_fui_neuronchainv7 *) &((Parameters *) ssGetDefaultParam
                     (S))->Sigmoid1_c);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2596_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_c.B_0_8_0 - B_540_2573_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_982;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2536_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_f, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_f);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1130>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2598, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_160_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2536_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_a,
                           (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_a);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2598_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_a.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  /* Integrator: '<S1132>/Integrator' */
  B_540_2602_0 = ((ContinuousStates *) ssGetContStates(S))->Integrator_CSTATE_lu;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2605_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_984;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2607_0 = ((((B_540_584_0 - B_540_2602_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_f.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_162_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_828_0[3]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2605_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_985;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2536_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_g, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_g);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1131>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2609, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_162_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_160_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2536_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_ag, (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_ag);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2609_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_ag.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  /* Integrator: '<S1133>/Integrator' */
  B_540_2613_0 = ((ContinuousStates *) ssGetContStates(S))->Integrator_CSTATE_b3;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2616_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_987;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2618_0 = ((((B_540_584_0 - B_540_2613_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_g.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_163_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_828_0[4]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2616_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_988;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1132>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2619, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2620_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_989;
  }

  neuronchainv7_Sigmoid2(S, 0.0, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_160_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2620_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_a2, (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_a2);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2619_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_a2.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2602_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_n,
                    (rtP_fui_neuronchainv7 *) &((Parameters *) ssGetDefaultParam
                     (S))->Sigmoid1_n);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2627_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_n.B_0_8_0 - B_540_2602_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_990;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1133>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2628, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2629_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_991;
  }

  neuronchainv7_Sigmoid2(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_163_0, 0.0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_161_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_160_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_159_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2629_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_n,
                         (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_n);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2628_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_n.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2613_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_d,
                    (rtP_fui_neuronchainv7 *) &((Parameters *) ssGetDefaultParam
                     (S))->Sigmoid1_d);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2636_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_d.B_0_8_0 - B_540_2613_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_992;
  if (ssIsSampleHit(S, 1, 0)) {
    for (i = 0; i < 10; i++) {
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2748_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_993[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2749_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_994[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2750_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_995[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2751_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_996[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2752_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_997[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2753_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_998[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2754_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_999[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2755_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_1000[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2756_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_1001[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2757_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_1002[i];
    }
  }

  /* MATLABFcn: '<S8>/MATLAB Fcn' */

  /* Call into Simulink to run the Matlab Fcn block. */
  ssCallAccelRunBlock(S, 540, 2647, SS_CALL_MDL_OUTPUTS);

  /* Integrator: '<S1174>/Integrator' */
  B_540_2648_0 = ((ContinuousStates *) ssGetContStates(S))->Integrator_CSTATE_pg;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1174>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2649, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2650_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1004;
  }

  neuronchainv7_Sigmoid2(S, 0.0, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_170_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2650_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_h,
                         (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_h);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2649_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_h.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2648_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_j,
                    (rtP_fui_neuronchainv7 *) &((Parameters *) ssGetDefaultParam
                     (S))->Sigmoid1_j);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2657_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_j.B_0_8_0 - B_540_2648_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_1005;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2647_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_nw, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_nw);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1175>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2659, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_170_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2647_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_d,
                           (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_d);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2659_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_d.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2665_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1006;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2667_0 = ((((B_540_584_0 - B_540_2648_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_nw.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_167_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_1025_0[0]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2665_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_1007;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2647_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_ds, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_ds);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1176>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2669, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_170_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2647_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_hh, (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_hh);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2669_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_hh.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  /* Integrator: '<S1178>/Integrator' */
  B_540_2673_0 = ((ContinuousStates *) ssGetContStates(S))
    ->Integrator_CSTATE_bc3;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2676_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1009;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2678_0 = ((((B_540_584_0 - B_540_2673_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_ds.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_168_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_1025_0[1]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2676_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_1010;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2647_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_l, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_l);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1177>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2680, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_167_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2647_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_bs, (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_bs);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2680_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_bs.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  /* Integrator: '<S1179>/Integrator' */
  B_540_2684_0 = ((ContinuousStates *) ssGetContStates(S))->Integrator_CSTATE_fr;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2687_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1012;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2689_0 = ((((B_540_584_0 - B_540_2684_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_l.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_169_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_1025_0[2]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2687_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_1013;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1178>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2690, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2691_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1014;
  }

  neuronchainv7_Sigmoid2(S, 0.0, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_170_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2691_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_o,
                         (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_o);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2690_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_o.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2673_0, &((BlockIO *) _ssGetBlockIO(S))
                    ->Sigmoid1_jr, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_jr);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2698_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_jr.B_0_8_0 - B_540_2673_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_1015;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1179>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2699, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2700_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1016;
  }

  neuronchainv7_Sigmoid2(S, 0.0, ((BlockIO *) _ssGetBlockIO(S))->B_540_168_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_167_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2700_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_nd, (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_nd);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2699_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_nd.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2684_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_b,
                    (rtP_fui_neuronchainv7 *) &((Parameters *) ssGetDefaultParam
                     (S))->Sigmoid1_b);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2707_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_b.B_0_8_0 - B_540_2684_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_1017;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2647_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_i, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_i);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1180>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2709, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_168_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2647_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_mo, (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_mo);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2709_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_mo.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  /* Integrator: '<S1182>/Integrator' */
  B_540_2713_0 = ((ContinuousStates *) ssGetContStates(S))->Integrator_CSTATE_cx;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2716_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1019;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2718_0 = ((((B_540_584_0 - B_540_2713_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_i.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_170_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_1025_0[3]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2716_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_1020;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2647_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_fb, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_fb);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1181>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2720, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_170_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_168_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2647_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_ng, (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_ng);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2720_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_ng.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  /* Integrator: '<S1183>/Integrator' */
  B_540_2724_0 = ((ContinuousStates *) ssGetContStates(S))->Integrator_CSTATE_mz;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2727_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1022;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2729_0 = ((((B_540_584_0 - B_540_2724_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_fb.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_171_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_1025_0[4]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2727_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_1023;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1182>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2730, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2731_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1024;
  }

  neuronchainv7_Sigmoid2(S, 0.0, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_168_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2731_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_ao, (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_ao);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2730_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_ao.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2713_0, &((BlockIO *) _ssGetBlockIO(S))
                    ->Sigmoid1_dq, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_dq);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2738_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_dq.B_0_8_0 - B_540_2713_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_1025;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1183>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2739, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2740_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1026;
  }

  neuronchainv7_Sigmoid2(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_171_0, 0.0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_169_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_168_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_167_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2740_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_e,
                         (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_e);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2739_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_e.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2724_0, &((BlockIO *) _ssGetBlockIO(S))
                    ->Sigmoid1_du, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_du);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2747_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_du.B_0_8_0 - B_540_2724_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_1027;
  if (ssIsSampleHit(S, 1, 0)) {
    for (i = 0; i < 10; i++) {
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2748_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_1028[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2749_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_1029[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2750_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_1030[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2751_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_1031[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2752_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_1032[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2753_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_1033[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2754_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_1034[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2755_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_1035[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2756_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_1036[i];
      ((BlockIO *) _ssGetBlockIO(S))->B_540_2757_0[i] = ((Parameters *)
        ssGetDefaultParam(S))->P_1037[i];
    }
  }

  /* MATLABFcn: '<S9>/MATLAB Fcn' */

  /* Call into Simulink to run the Matlab Fcn block. */
  ssCallAccelRunBlock(S, 540, 2758, SS_CALL_MDL_OUTPUTS);

  /* Integrator: '<S1224>/Integrator' */
  B_540_2759_0 = ((ContinuousStates *) ssGetContStates(S))
    ->Integrator_CSTATE_fu1;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1224>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2760, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2761_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1039;
  }

  neuronchainv7_Sigmoid2(S, 0.0, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_580_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2761_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_lk, (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_lk);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2760_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_lk.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2759_0, &((BlockIO *) _ssGetBlockIO(S))
                    ->Sigmoid1_c4, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_c4);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2768_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_c4.B_0_8_0 - B_540_2759_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_1040;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2758_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_dg, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_dg);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1225>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2770, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_580_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2758_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_n0, (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_n0);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2770_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_n0.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2776_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1041;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2778_0 = ((((B_540_584_0 - B_540_2759_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_dg.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_577_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_829_0[0]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2776_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_1042;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2758_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_nm, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_nm);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1226>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2780, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_580_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2758_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_mm, (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_mm);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2780_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_mm.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  /* Integrator: '<S1228>/Integrator' */
  B_540_2784_0 = ((ContinuousStates *) ssGetContStates(S))
    ->Integrator_CSTATE_mio;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2787_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1044;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2789_0 = ((((B_540_584_0 - B_540_2784_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_nm.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_578_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_829_0[1]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2787_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_1045;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2758_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_is, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_is);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1227>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2791, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_577_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2758_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_hc, (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_hc);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2791_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_hc.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  /* Integrator: '<S1229>/Integrator' */
  B_540_2795_0 = ((ContinuousStates *) ssGetContStates(S))->Integrator_CSTATE_oj;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2798_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1047;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2800_0 = ((((B_540_584_0 - B_540_2795_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_is.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_579_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_829_0[2]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2798_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_1048;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1228>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2801, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2802_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1049;
  }

  neuronchainv7_Sigmoid2(S, 0.0, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_580_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2802_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_k,
                         (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_k);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2801_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_k.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2784_0, &((BlockIO *) _ssGetBlockIO(S))
                    ->Sigmoid1_di, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_di);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2809_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_di.B_0_8_0 - B_540_2784_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_1050;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1229>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2810, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2811_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1051;
  }

  neuronchainv7_Sigmoid2(S, 0.0, ((BlockIO *) _ssGetBlockIO(S))->B_540_578_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_577_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2811_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_ay, (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_ay);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2810_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_ay.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2795_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_o,
                    (rtP_fui_neuronchainv7 *) &((Parameters *) ssGetDefaultParam
                     (S))->Sigmoid1_o);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2818_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_o.B_0_8_0 - B_540_2795_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_1052;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2758_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_do, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_do);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1230>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2820, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_578_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2758_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_dz, (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_dz);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2820_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_dz.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  /* Integrator: '<S1232>/Integrator' */
  B_540_2824_0 = ((ContinuousStates *) ssGetContStates(S))
    ->Integrator_CSTATE_jks;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2827_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1054;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2829_0 = ((((B_540_584_0 - B_540_2824_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_do.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_580_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_829_0[3]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2827_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_1055;
  neuronchainv7_Sigmoid1(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2758_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid1_k, (rtP_Sigmoid1_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_k);
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1231>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2831, SS_CALL_MDL_OUTPUTS);
  }

  neuronchainv7_Sigmoid2_i(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_580_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_578_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, 0.0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2758_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_if, (rtP_Sigmoid2_neuronchainv7_n *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_if);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2831_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_if.B_483_7_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  /* Integrator: '<S1233>/Integrator' */
  B_540_2835_0 = ((ContinuousStates *) ssGetContStates(S))->Integrator_CSTATE_k5;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2838_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1057;
  }

  ((BlockIO *) _ssGetBlockIO(S))->B_540_2840_0 = ((((B_540_584_0 - B_540_2835_0)
    * ((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_k.B_482_7_0 - ((BlockIO *)
    _ssGetBlockIO(S))->B_540_581_0) + ((BlockIO *) _ssGetBlockIO(S))
    ->B_540_829_0[4]) + ((BlockIO *) _ssGetBlockIO(S))->B_540_2838_0) *
    ((Parameters *) ssGetDefaultParam(S))->P_1058;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1232>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2841, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2842_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1059;
  }

  neuronchainv7_Sigmoid2(S, 0.0, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_578_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2842_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_mf, (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_mf);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2841_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_mf.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2824_0, &((BlockIO *) _ssGetBlockIO(S))->Sigmoid1_h,
                    (rtP_fui_neuronchainv7 *) &((Parameters *) ssGetDefaultParam
                     (S))->Sigmoid1_h);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2849_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_h.B_0_8_0 - B_540_2824_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_1060;
  if (ssIsSampleHit(S, 1, 0)) {
    /* MATLABFcn: '<S1233>/MATLAB Fcn' */
    /* Call into Simulink to run the Matlab Fcn block. */
    ssCallAccelRunBlock(S, 540, 2850, SS_CALL_MDL_OUTPUTS);
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2851_0 = ((Parameters *)
      ssGetDefaultParam(S))->P_1061;
  }

  neuronchainv7_Sigmoid2(S, ((BlockIO *) _ssGetBlockIO(S))->B_540_581_0, 0.0,
    ((BlockIO *) _ssGetBlockIO(S))->B_540_579_0, ((BlockIO *) _ssGetBlockIO(S)
    )->B_540_578_0, ((BlockIO *) _ssGetBlockIO(S))->B_540_577_0, ((BlockIO *)
    _ssGetBlockIO(S))->B_540_2851_0, &((BlockIO *) _ssGetBlockIO(S))
    ->Sigmoid2_ai, (rtP_Sigmoid2_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid2_ai);
  for (i = 0; i < 10; i++) {
    B_540_2541_0[i] = ((BlockIO *) _ssGetBlockIO(S))->B_540_2850_0[i] *
      ((BlockIO *) _ssGetBlockIO(S))->Sigmoid2_ai.B_481_8_0[i];
  }

  B_540_584_0 = B_540_2541_0[0];
  for (i = 0; i < 9; i++) {
    tmp_1 = i + 1;
    if (tmp_1 > 2147483647L) {
      tmp_1 = 2147483647L;
    } else {
      if (tmp_1 <= -2147483648L) {
        tmp_1 = -2147483648L;
      }
    }

    B_540_584_0 += B_540_2541_0[(int32_T)tmp_1];
  }

  neuronchainv7_fui(S, B_540_2835_0, &((BlockIO *) _ssGetBlockIO(S))
                    ->Sigmoid1_fbd, (rtP_fui_neuronchainv7 *) &((Parameters *)
    ssGetDefaultParam(S))->Sigmoid1_fbd);
  ((BlockIO *) _ssGetBlockIO(S))->B_540_2858_0 = (B_540_584_0 * ((BlockIO *)
    _ssGetBlockIO(S))->Sigmoid1_fbd.B_0_8_0 - B_540_2835_0) * ((Parameters *)
    ssGetDefaultParam(S))->P_1062;
  if (ssIsSampleHit(S, 1, 0)) {
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2859_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay_X;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2860_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay1_X;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2861_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay2_X;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2862_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay3_X_k;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2863_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay4_X;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2864_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay5_X;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2865_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay_X_k;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2866_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay1_X_k;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2867_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay2_X_a;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2868_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay3_X_o;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2869_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay4_X_e;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2870_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay5_X_n;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2871_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay3_X_oj;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2872_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay4_X_g;
    ((BlockIO *) _ssGetBlockIO(S))->B_540_2873_0 = ((D_Work *) ssGetRootDWork(S))
      ->TappedDelay5_X_k;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
#define MDL_UPDATE

static void mdlUpdate(SimStruct *S, int_T tid)
{
  if (ssIsSampleHit(S, 1, 0)) {
    ((D_Work *) ssGetRootDWork(S))->TappedDelay3_X = ((BlockIO *) _ssGetBlockIO
      (S))->B_540_2861_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay6_X = ((BlockIO *) _ssGetBlockIO
      (S))->B_540_2864_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay3_X_m = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2867_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay6_X_c = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2870_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay6_X_f = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2873_0;
  }

  if (ssIsSampleHit(S, 1, 0)) {
    ((D_Work *) ssGetRootDWork(S))->TappedDelay_X = ((BlockIO *) _ssGetBlockIO(S))
      ->B_540_141_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay1_X = ((BlockIO *) _ssGetBlockIO
      (S))->B_540_2859_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay2_X = ((BlockIO *) _ssGetBlockIO
      (S))->B_540_2860_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay3_X_k = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_145_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay4_X = ((BlockIO *) _ssGetBlockIO
      (S))->B_540_2862_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay5_X = ((BlockIO *) _ssGetBlockIO
      (S))->B_540_2863_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay_X_k = ((BlockIO *) _ssGetBlockIO
      (S))->B_540_149_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay1_X_k = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2865_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay2_X_a = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2866_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay3_X_o = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_153_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay4_X_e = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2868_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay5_X_n = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2869_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay3_X_oj = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_157_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay4_X_g = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2871_0;
    ((D_Work *) ssGetRootDWork(S))->TappedDelay5_X_k = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2872_0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
#define MDL_DERIVATIVES

static void mdlDerivatives(SimStruct *S)
{
  /* Derivatives for Integrator: '<S211>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1405_0;
  }

  /* Derivatives for Integrator: '<S203>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_g = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1325_0;
  }

  /* Derivatives for Integrator: '<S208>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_a = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1375_0;
  }

  /* Derivatives for Integrator: '<S214>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_e = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1435_0;
  }

  /* Derivatives for Integrator: '<S220>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_h = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1495_0;
  }

  /* Derivatives for Integrator: '<S221>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_b = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1505_0;
  }

  /* Derivatives for Integrator: '<S215>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_m = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1445_0;
  }

  /* Derivatives for Integrator: '<S209>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_o = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1385_0;
  }

  /* Derivatives for Integrator: '<S204>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_l = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1335_0;
  }

  /* Derivatives for Integrator: '<S217>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_j = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1465_0;
  }

  /* Derivatives for Integrator: '<S218>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_j0 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1475_0;
  }

  /* Derivatives for Integrator: '<S212>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_bd = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1415_0;
  }

  /* Derivatives for Integrator: '<S206>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_n = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1355_0;
  }

  /* Derivatives for Integrator: '<S201>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_h1 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1305_0;
  }

  /* Derivatives for Integrator: '<S199>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_no = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1285_0;
  }

  /* Derivatives for Integrator: '<S223>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_k = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1525_0;
  }

  /* Derivatives for Integrator: '<S205>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_c = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1345_0;
  }

  /* Derivatives for Integrator: '<S210>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_b0 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1395_0;
  }

  /* Derivatives for Integrator: '<S216>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_k4 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1455_0;
  }

  /* Derivatives for Integrator: '<S222>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_gk = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1515_0;
  }

  /* Derivatives for Integrator: '<S219>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_p = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1485_0;
  }

  /* Derivatives for Integrator: '<S213>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_d = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1425_0;
  }

  /* Derivatives for Integrator: '<S207>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_cw = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1365_0;
  }

  /* Derivatives for Integrator: '<S202>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_aa = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1315_0;
  }

  /* Derivatives for Integrator: '<S200>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_oh = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1295_0;
  }

  /* Derivatives for Integrator: '<S1125>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_l5 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2556_0;
  }

  /* Derivatives for Integrator: '<S1126>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_bt = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2567_0;
  }

  /* Derivatives for Integrator: '<S1127>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_mj = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2578_0;
  }

  /* Derivatives for Integrator: '<S1130>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ks = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2607_0;
  }

  /* Derivatives for Integrator: '<S1131>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_j4 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2618_0;
  }

  /* Derivatives for Integrator: '<S1175>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_gi = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2667_0;
  }

  /* Derivatives for Integrator: '<S1176>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_mr = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2678_0;
  }

  /* Derivatives for Integrator: '<S1177>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_gz = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2689_0;
  }

  /* Derivatives for Integrator: '<S1180>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_cs = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2718_0;
  }

  /* Derivatives for Integrator: '<S1181>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ch = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2729_0;
  }

  /* Derivatives for Integrator: '<S403>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ow = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1725_0;
  }

  /* Derivatives for Integrator: '<S397>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_nz = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1665_0;
  }

  /* Derivatives for Integrator: '<S391>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_nr = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1605_0;
  }

  /* Derivatives for Integrator: '<S386>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_i = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1555_0;
  }

  /* Derivatives for Integrator: '<S384>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ix = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1535_0;
  }

  /* Derivatives for Integrator: '<S406>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ns = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1755_0;
  }

  /* Derivatives for Integrator: '<S400>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_gw = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1695_0;
  }

  /* Derivatives for Integrator: '<S394>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_g5 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1635_0;
  }

  /* Derivatives for Integrator: '<S389>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_dm = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1585_0;
  }

  /* Derivatives for Integrator: '<S402>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_nb = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1715_0;
  }

  /* Derivatives for Integrator: '<S396>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_f = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1655_0;
  }

  /* Derivatives for Integrator: '<S388>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_h4 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1575_0;
  }

  /* Derivatives for Integrator: '<S393>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_dx = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1625_0;
  }

  /* Derivatives for Integrator: '<S399>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_g3 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1685_0;
  }

  /* Derivatives for Integrator: '<S405>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_km = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1745_0;
  }

  /* Derivatives for Integrator: '<S408>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_nc = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1775_0;
  }

  /* Derivatives for Integrator: '<S390>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_bk = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1595_0;
  }

  /* Derivatives for Integrator: '<S395>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_hg = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1645_0;
  }

  /* Derivatives for Integrator: '<S401>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_fz = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1705_0;
  }

  /* Derivatives for Integrator: '<S407>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ms = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1765_0;
  }

  /* Derivatives for Integrator: '<S404>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_gzl = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1735_0;
  }

  /* Derivatives for Integrator: '<S398>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_f3 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1675_0;
  }

  /* Derivatives for Integrator: '<S392>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_k1 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1615_0;
  }

  /* Derivatives for Integrator: '<S387>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_lk = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1565_0;
  }

  /* Derivatives for Integrator: '<S385>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_bn = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1545_0;
  }

  /* Derivatives for Integrator: '<S588>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_jk = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1975_0;
  }

  /* Derivatives for Integrator: '<S582>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_dc = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1915_0;
  }

  /* Derivatives for Integrator: '<S576>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_pf = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1855_0;
  }

  /* Derivatives for Integrator: '<S571>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_hq = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1805_0;
  }

  /* Derivatives for Integrator: '<S569>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_mp = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1785_0;
  }

  /* Derivatives for Integrator: '<S591>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_fb = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2005_0;
  }

  /* Derivatives for Integrator: '<S585>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_gf = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1945_0;
  }

  /* Derivatives for Integrator: '<S579>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_an = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1885_0;
  }

  /* Derivatives for Integrator: '<S574>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ex = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1835_0;
  }

  /* Derivatives for Integrator: '<S587>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_if = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1965_0;
  }

  /* Derivatives for Integrator: '<S581>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_hb = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1905_0;
  }

  /* Derivatives for Integrator: '<S573>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_fa = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1825_0;
  }

  /* Derivatives for Integrator: '<S578>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_i4 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1875_0;
  }

  /* Derivatives for Integrator: '<S584>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_il = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1935_0;
  }

  /* Derivatives for Integrator: '<S590>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_nw = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1995_0;
  }

  /* Derivatives for Integrator: '<S958>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_k3 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2475_0;
  }

  /* Derivatives for Integrator: '<S952>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_jy = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2415_0;
  }

  /* Derivatives for Integrator: '<S946>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ng = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2355_0;
  }

  /* Derivatives for Integrator: '<S941>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_pr = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2305_0;
  }

  /* Derivatives for Integrator: '<S939>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_hl = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2285_0;
  }

  /* Derivatives for Integrator: '<S961>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ep = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2505_0;
  }

  /* Derivatives for Integrator: '<S955>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_hq4 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2445_0;
  }

  /* Derivatives for Integrator: '<S949>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_e1 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2385_0;
  }

  /* Derivatives for Integrator: '<S944>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_cv = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2335_0;
  }

  /* Derivatives for Integrator: '<S957>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ne = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2465_0;
  }

  /* Derivatives for Integrator: '<S951>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_kd = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2405_0;
  }

  /* Derivatives for Integrator: '<S943>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_jq = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2325_0;
  }

  /* Derivatives for Integrator: '<S948>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ov = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2375_0;
  }

  /* Derivatives for Integrator: '<S954>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ck = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2435_0;
  }

  /* Derivatives for Integrator: '<S960>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_hc = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2495_0;
  }

  /* Derivatives for Integrator: '<S33>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_bw = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1225_0;
  }

  /* Derivatives for Integrator: '<S27>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_kx = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1165_0;
  }

  /* Derivatives for Integrator: '<S21>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_nn = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1105_0;
  }

  /* Derivatives for Integrator: '<S16>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_di = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1055_0;
  }

  /* Derivatives for Integrator: '<S14>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_bc = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1035_0;
  }

  /* Derivatives for Integrator: '<S36>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_lf = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1255_0;
  }

  /* Derivatives for Integrator: '<S30>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_dt = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1195_0;
  }

  /* Derivatives for Integrator: '<S24>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_kso = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1135_0;
  }

  /* Derivatives for Integrator: '<S19>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ht = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1085_0;
  }

  /* Derivatives for Integrator: '<S32>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ls = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1215_0;
  }

  /* Derivatives for Integrator: '<S26>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_g5k = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1155_0;
  }

  /* Derivatives for Integrator: '<S18>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_lq = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1075_0;
  }

  /* Derivatives for Integrator: '<S23>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_af = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1125_0;
  }

  /* Derivatives for Integrator: '<S29>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ir = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1185_0;
  }

  /* Derivatives for Integrator: '<S35>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_m3 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1245_0;
  }

  /* Derivatives for Integrator: '<S38>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_jt = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1275_0;
  }

  /* Derivatives for Integrator: '<S20>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ah = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1095_0;
  }

  /* Derivatives for Integrator: '<S25>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_lp = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1145_0;
  }

  /* Derivatives for Integrator: '<S31>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_j2 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1205_0;
  }

  /* Derivatives for Integrator: '<S37>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_cc = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1265_0;
  }

  /* Derivatives for Integrator: '<S34>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_mq = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1235_0;
  }

  /* Derivatives for Integrator: '<S28>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ahl = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1175_0;
  }

  /* Derivatives for Integrator: '<S22>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ap = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1115_0;
  }

  /* Derivatives for Integrator: '<S17>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_al = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1065_0;
  }

  /* Derivatives for Integrator: '<S15>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_fu = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1045_0;
  }

  /* Derivatives for Integrator: '<S1225>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_kh = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2778_0;
  }

  /* Derivatives for Integrator: '<S1226>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_n3 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2789_0;
  }

  /* Derivatives for Integrator: '<S1227>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_by = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2800_0;
  }

  /* Derivatives for Integrator: '<S1230>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ia = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2829_0;
  }

  /* Derivatives for Integrator: '<S1231>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_jh = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2840_0;
  }

  /* Derivatives for Integrator: '<S589>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_j3 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1985_0;
  }

  /* Derivatives for Integrator: '<S583>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_d4 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1925_0;
  }

  /* Derivatives for Integrator: '<S577>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_d2 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1865_0;
  }

  /* Derivatives for Integrator: '<S572>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ckt = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1815_0;
  }

  /* Derivatives for Integrator: '<S570>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_go = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1795_0;
  }

  /* Derivatives for Integrator: '<S592>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_oa = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2015_0;
  }

  /* Derivatives for Integrator: '<S586>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ows = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1955_0;
  }

  /* Derivatives for Integrator: '<S580>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ej = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1895_0;
  }

  /* Derivatives for Integrator: '<S575>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_p0 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_1845_0;
  }

  /* Derivatives for Integrator: '<S593>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_da = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2025_0;
  }

  /* Derivatives for Integrator: '<S959>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_oi = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2485_0;
  }

  /* Derivatives for Integrator: '<S953>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_do = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2425_0;
  }

  /* Derivatives for Integrator: '<S947>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_f0 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2365_0;
  }

  /* Derivatives for Integrator: '<S942>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_gfn = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2315_0;
  }

  /* Derivatives for Integrator: '<S940>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_iv = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2295_0;
  }

  /* Derivatives for Integrator: '<S962>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_mjo = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2515_0;
  }

  /* Derivatives for Integrator: '<S956>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_c5 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2455_0;
  }

  /* Derivatives for Integrator: '<S950>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_kf = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2395_0;
  }

  /* Derivatives for Integrator: '<S945>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_gkg = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2345_0;
  }

  /* Derivatives for Integrator: '<S963>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_mt = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2525_0;
  }

  /* Derivatives for Integrator: '<S773>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ki = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2225_0;
  }

  /* Derivatives for Integrator: '<S767>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_px = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2165_0;
  }

  /* Derivatives for Integrator: '<S761>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ml = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2105_0;
  }

  /* Derivatives for Integrator: '<S756>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_mi = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2055_0;
  }

  /* Derivatives for Integrator: '<S754>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_fn = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2035_0;
  }

  /* Derivatives for Integrator: '<S774>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_mpg = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2235_0;
  }

  /* Derivatives for Integrator: '<S768>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_i1 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2175_0;
  }

  /* Derivatives for Integrator: '<S762>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_hd = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2115_0;
  }

  /* Derivatives for Integrator: '<S757>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_nd = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2065_0;
  }

  /* Derivatives for Integrator: '<S755>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_nek = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2045_0;
  }

  /* Derivatives for Integrator: '<S775>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_j0t = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2245_0;
  }

  /* Derivatives for Integrator: '<S769>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_jf = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2185_0;
  }

  /* Derivatives for Integrator: '<S763>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_et = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2125_0;
  }

  /* Derivatives for Integrator: '<S758>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_du = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2075_0;
  }

  /* Derivatives for Integrator: '<S766>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_o2 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2155_0;
  }

  /* Derivatives for Integrator: '<S776>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_gfb = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2255_0;
  }

  /* Derivatives for Integrator: '<S770>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_fq = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2195_0;
  }

  /* Derivatives for Integrator: '<S764>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_od = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2135_0;
  }

  /* Derivatives for Integrator: '<S759>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_jw = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2085_0;
  }

  /* Derivatives for Integrator: '<S772>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_iz = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2215_0;
  }

  /* Derivatives for Integrator: '<S777>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_hv = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2265_0;
  }

  /* Derivatives for Integrator: '<S771>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ph = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2205_0;
  }

  /* Derivatives for Integrator: '<S765>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ec = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2145_0;
  }

  /* Derivatives for Integrator: '<S760>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_ie = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2095_0;
  }

  /* Derivatives for Integrator: '<S778>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_co = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2275_0;
  }

  /* Derivatives for Integrator: '<S1124>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_mqu = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2546_0;
  }

  /* Derivatives for Integrator: '<S1128>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_py = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2587_0;
  }

  /* Derivatives for Integrator: '<S1129>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_or = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2596_0;
  }

  /* Derivatives for Integrator: '<S1132>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_lu = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2627_0;
  }

  /* Derivatives for Integrator: '<S1133>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_b3 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2636_0;
  }

  /* Derivatives for Integrator: '<S1174>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_pg = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2657_0;
  }

  /* Derivatives for Integrator: '<S1178>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_bc3 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2698_0;
  }

  /* Derivatives for Integrator: '<S1179>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_fr = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2707_0;
  }

  /* Derivatives for Integrator: '<S1182>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_cx = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2738_0;
  }

  /* Derivatives for Integrator: '<S1183>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_mz = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2747_0;
  }

  /* Derivatives for Integrator: '<S1224>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_fu1 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2768_0;
  }

  /* Derivatives for Integrator: '<S1228>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_mio = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2809_0;
  }

  /* Derivatives for Integrator: '<S1229>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_oj = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2818_0;
  }

  /* Derivatives for Integrator: '<S1232>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_jks = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2849_0;
  }

  /* Derivatives for Integrator: '<S1233>/Integrator' */
  {
    ((StateDerivatives *) ssGetdX(S))->Integrator_CSTATE_k5 = ((BlockIO *)
      _ssGetBlockIO(S))->B_540_2858_0;
  }
}

/* ZeroCrossings for root system: '<Root>' */
#define MDL_ZERO_CROSSINGS

static void mdlZeroCrossings(SimStruct *S)
{
  int32_T i;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_5_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_3;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_g =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_11_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_6;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_k =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_16_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_9;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_j =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_21_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_12;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_a =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_26_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_15;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_p =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_31_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_18;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_i =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_36_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_21;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_jd =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_41_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_24;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_h =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_46_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_27;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_iv =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_51_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_30;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_jw =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_56_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_33;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_o =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_61_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_36;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_d =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_66_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_39;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_n =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_71_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_42;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ko =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_76_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_45;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_jf =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_81_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_48;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_kn =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_86_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_51;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_c =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_91_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_54;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_hp =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_96_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_57;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_b =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_101_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_60;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_bc =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_106_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_63;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_e =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_111_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_66;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_bp =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_116_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_69;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_nk =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_121_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_72;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_kc =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_126_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_75;
  for (i = 0; i < 5; i++) {
    ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Saturation_UprLim_ZC[i] =
      ((BlockIO *) _ssGetBlockIO(S))->B_540_135_0[i] - ((Parameters *)
      ssGetDefaultParam(S))->P_83;
    ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Saturation_LwrLim_ZC[i] =
      ((BlockIO *) _ssGetBlockIO(S))->B_540_135_0[i] - ((Parameters *)
      ssGetDefaultParam(S))->P_84;
  }

  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Saturation_UprLim_ZC_a =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_140_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_90;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Saturation_LwrLim_ZC_a =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_140_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_91;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Saturation1_UprLim_ZC =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_144_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_96;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Saturation1_LwrLim_ZC =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_144_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_97;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Saturation_UprLim_ZC_l =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_148_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_102;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Saturation_LwrLim_ZC_j =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_148_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_103;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Saturation1_UprLim_ZC_a =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_152_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_108;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Saturation1_LwrLim_ZC_p =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_152_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_109;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Saturation1_UprLim_ZC_i =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_156_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_114;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Saturation1_LwrLim_ZC_h =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_156_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_115;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_b5 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_176_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_130;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_h4 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_181_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_133;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_gt =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_186_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_136;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_l =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_191_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_139;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ck =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_196_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_142;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_o1 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_201_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_145;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_m =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_206_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_148;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_eh =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_211_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_151;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_an =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_216_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_154;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_jt =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_221_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_157;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_c4 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_226_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_160;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_hf =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_231_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_163;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_o14 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_236_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_166;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_jm =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_241_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_169;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_gu =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_246_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_172;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ka =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_251_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_175;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_pb =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_256_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_178;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_pj =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_261_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_181;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_pa =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_266_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_184;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_iu =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_271_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_187;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ik =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_276_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_190;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_gq =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_281_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_193;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_f =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_286_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_196;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_mf =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_291_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_199;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ov =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_296_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_202;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_nf =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_302_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_205;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_pm =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_307_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_208;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ev =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_312_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_211;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_po =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_317_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_214;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_pe =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_322_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_217;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_f1 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_327_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_220;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_bf =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_332_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_223;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_eb =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_337_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_226;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_bl =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_342_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_229;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_fb =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_347_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_232;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_f3 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_352_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_235;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_n2 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_357_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_238;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ps =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_362_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_241;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_kk =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_367_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_244;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_lq =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_372_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_247;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ms =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_378_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_250;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ea =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_383_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_253;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_az =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_388_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_256;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ang =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_393_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_259;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_b2 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_398_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_262;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_gj =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_403_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_265;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ew =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_408_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_268;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_bj =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_413_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_271;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_iw =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_418_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_274;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_evn =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_423_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_277;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ld =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_428_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_280;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_i5 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_433_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_283;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_nz =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_438_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_286;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ky =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_443_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_289;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_l4 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_448_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_292;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_mh =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_454_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_295;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_av =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_459_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_298;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ldi =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_464_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_301;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_jfm =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_469_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_304;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ez =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_474_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_307;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ig =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_479_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_310;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_nb =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_484_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_313;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_cd =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_489_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_316;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_lk =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_494_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_319;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_py =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_499_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_322;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_cn =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_504_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_325;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_koh =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_509_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_328;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_pd =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_514_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_331;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_dg =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_519_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_334;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_km =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_524_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_337;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_b1 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_529_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_340;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_cl =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_534_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_343;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ehh =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_539_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_346;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_en =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_544_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_349;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_he =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_549_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_352;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ed =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_554_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_355;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ezc =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_559_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_358;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_jdw =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_564_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_361;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_o4 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_569_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_364;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_m5 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_574_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_367;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_mhi =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_597_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_375;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_it =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_603_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_378;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_hv =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_609_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_381;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_fh =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_615_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_384;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_im =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_621_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_387;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_kz =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_640_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_390;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ej =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_646_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_393;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_o2 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_652_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_396;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_m2 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_658_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_399;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_clm =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_664_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_402;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ol =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_682_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_405;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_fn =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_688_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_408;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_by =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_694_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_411;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ik5 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_700_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_414;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_fe =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_706_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_417;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_bs =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_725_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_420;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_nu =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_731_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_423;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_f3w =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_737_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_426;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_jm4 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_743_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_429;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_m2w =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_749_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_432;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ce =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_869_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_435;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_p2 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_875_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_438;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ij =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_882_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_441;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_gi =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_890_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_444;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_k2 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_896_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_447;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_oa =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_904_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_450;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_guk =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_910_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_453;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_pi =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_916_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_456;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_k3 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_922_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_459;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ac =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_928_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_462;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_nl =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_935_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_465;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_fc =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_941_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_468;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_mq =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_947_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_471;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_h5 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_953_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_474;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_ak =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_959_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_477;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_hvw =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_966_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_480;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_k2c =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_972_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_483;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_a3 =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_978_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_486;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_bca =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_984_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_489;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_fnl =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_990_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_492;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_dn =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_997_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_495;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_jmo =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1003_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_498;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_au =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1009_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_501;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_cnk =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1015_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_504;
  ((ZCSignalValues *) ssGetSolverZcSignalVector(S))->Switch1_SwitchCond_ZC_cj =
    ((BlockIO *) _ssGetBlockIO(S))->B_540_1021_0 - ((Parameters *)
    ssGetDefaultParam(S))->P_507;
}

/* Function to initialize sizes */
static void mdlInitializeSizes(SimStruct *S)
{
  /* checksum */
  ssSetChecksumVal(S, 0, 3009896705U);
  ssSetChecksumVal(S, 1, 4000928707U);
  ssSetChecksumVal(S, 2, 3147887363U);
  ssSetChecksumVal(S, 3, 2147939340U);

  /* options */
  ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);

  /* Accelerator check memory map size match for DWork */
  if (ssGetSizeofDWork(S) != sizeof(D_Work)) {
    ssSetErrorStatus(S,"Unexpected error: Internal DWork sizes do "
                     "not match for accelerator mex file.");
  }

  /* Accelerator check memory map size match for BlockIO */
  if (ssGetSizeofGlobalBlockIO(S) != sizeof(BlockIO)) {
    ssSetErrorStatus(S,"Unexpected error: Internal BlockIO sizes do "
                     "not match for accelerator mex file.");
  }

  /* model parameters */
  _ssSetDefaultParam(S, (real_T *) &rtDefaultParameters);
}

/* mdlInitializeSampleTimes function (used to set up function-call connections) */
static void mdlInitializeSampleTimes(SimStruct *S)
{
}

/* Empty mdlTerminate function (never called) */
static void mdlTerminate(SimStruct *S)
{
}

/* MATLAB MEX Glue */
#include "simulink.c"
