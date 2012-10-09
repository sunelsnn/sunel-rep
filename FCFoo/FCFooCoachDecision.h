/* -*- Mode: C++ -*-
 * $Id: FCFooCoachDecision.h,v 1.2 2002/08/31 15:17:17 s02davro Exp $
 *
 *
 * COPYRIGHT INFORMATION
 *
 * This file is part of RoboSoc created by Fredrik Heintz <frehe@ida.liu.se>
 * Copyright (C) 1999, 2000 Fredrik Heintz, Linköping University, Sweden
 *
 * You are allowed to modify and use this code as long as you retain this
 * notice. If you make any changes or have any comments I would appreciate
 * it if you send me a message. For more information, please see
 * http://www.ida.liu.se/~frehe/RoboCup/RoboSoc/
 *
 *
 * IDENTIFICATION
 *
 * Filename: FCFooCoachDecision.h
 * Unitname: Framework/example/FCFoo
 * $Revision: 1.2 $
 * Created by: Fredrik Heintz 2001-11-15
 * Last modified by $Author: s02davro $ $Date: 2002/08/31 15:17:17 $
 *
 *
 * HISTORY
 *
 * $Log: FCFooCoachDecision.h,v $
 * Revision 1.2  2002/08/31 15:17:17  s02davro
 * FCFoo now run coach with -coach option, changed the main loop
 *
 * Revision 1.1  2001/11/15 16:50:13  frehe
 * Added a coach agent
 *
 */

/**
 * @file FCFooCoachDecision.h
 * Include file for the class FCFooCoachDecision.
 *
 * @par Unit:
 *      Framework/example/FCFoo
 * $Revision: 1.2 $
 * $Author: s02davro $
 * $Date: 2002/08/31 15:17:17 $
 */


#ifndef FCFOO_COACH_DECISION_H
#define FCFOO_COACH_DECISION_H

#include "basic_system_compiler_directives.h"
#include "Decision.h"
#include "WorldModelInterface.h"

RS_BEGIN_NAMESPACE

class ViewManager;

/**
 * @class FCFooCoachDecision FCFooCoachDecision.h
 * Example class for what a coach decision maker might look like.
 *
 * <!-- @todo-->
 *
 * @par Unit:
 *      Framework/example/FCFoo
 * $Revision: 1.2 $
 * $Author: s02davro $
 * $Date: 2002/08/31 15:17:17 $
 */
class FCFooCoachDecision : public Decision {
public:
  FCFooCoachDecision(ActuatorInterface* const actuator_interface = NULL);
  virtual ~FCFooCoachDecision();

  virtual ServerCommand* initAgent();
  virtual bool start();
  virtual bool decide();

  // Event handlers
  //virtual void onActuatorSensorData();
  //virtual void onAuralCoachSensorData();
  //virtual void onAuralRefereeSensorData();
  //virtual void onAuralPlayerSensorData();
  //virtual void onAuralSelfSensorData();
  virtual void onInit();
  //virtual void onPhysicalSensorData();
  //virtual void onVisualSensorData();

  //virtual void onBeforeSensorData();
  virtual void onAfterSensorData();
  //virtual void onBeforeTick();
  //virtual void onAfterTick();

  //virtual void onNewCycle(const bool forced);
  //virtual bool onEstimatedNewCycle(UInt16 estimated_time, UInt16 ticks);
  //virtual void onCommandWarning();

protected:
  ViewManager* const viewManager;
  const WorldModelInterface* const worldModelInterface;
  const WorldFacts* facts;
};


RS_END_NAMESPACE


#endif // !FCFOO_COACH_DECISION_H
