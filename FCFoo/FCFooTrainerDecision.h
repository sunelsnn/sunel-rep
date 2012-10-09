/* -*- Mode: C++ -*-
 * $Id: FCFooTrainerDecision.h,v 1.3 2003/07/22 14:47:23 s02davro Exp $
 *
 *
 * COPYRIGHT INFORMATION
 *
 * This file is part of RoboSoc created by Fredrik Heintz <frehe@ida.liu.se>
 * Copyright (C) 1999, 2000 Fredrik Heintz, Link�ping University, Sweden
 *
 * You are allowed to modify and use this code as long as you retain this
 * notice. If you make any changes or have any comments I would appreciate
 * it if you send me a message. For more information, please see
 * http://www.ida.liu.se/~frehe/RoboCup/RoboSoc/
 *
 *
 * IDENTIFICATION
 *
 * Filename: FCFooTrainerDecision.h
 * Unitname: Framework/example/FCFoo
 * $Revision: 1.3 $
 * Created by: Fredrik Heintz 2002-12-07
 * Last modified by $Author: s02davro $ $Date: 2003/07/22 14:47:23 $
 *
 *
 * HISTORY
 *
 * $Log: FCFooTrainerDecision.h,v $
 * Revision 1.3  2003/07/22 14:47:23  s02davro
 * Updated coach/trainer/player for testing new features
 *
 * Revision 1.2  2003/07/21 09:27:01  s02davro
 * Update of trainer agent
 *
 * Revision 1.1  2002/12/07 17:25:10  s02davro
 * Added trainer
 *
 *
 */

/**
 * @file FCFooTrainerDecision.h
 * Include file for the class FCFooTrainerDecision.
 *
 * @par Unit:
 *      Framework/example/FCFoo
 * $Revision: 1.3 $
 * $Author: s02davro $
 * $Date: 2003/07/22 14:47:23 $
 */


#ifndef FCFOO_TRAINER_DECISION_H
#define FCFOO_TRAINER_DECISION_H

#include "basic_system_compiler_directives.h"
#include "Decision.h"
#include "WorldModelInterface.h"
#include "GameView.h"
#include "BallView.h"
#include "PlayerView.h"

RS_BEGIN_NAMESPACE

class ViewManager;

/**
 * @class FCFooTrainerDecision FCFooTrainerDecision.h
 * Example class for what a trainers decision maker might look like.
 * A few notes:
 * Remember to start the soccerserver with the coach or coach_w_referee
 * option, otherwise the coach_port (6001) won't be open and the trainer
 * can't connect.
 * The coach must connect before the first player enters the game, and should
 * before starting the game, check the teamnames (using TeamNamesCommand) to
 * be able to move the players with the MoveObjectCommand.
 *
 * @par Unit:
 *      Framework/example/FCFoo
 * $Revision: 1.3 $
 * $Author: s02davro $
 * $Date: 2003/07/22 14:47:23 $
 *
 * Modified: Added new functions
 * Author: Sunil Mamidi
 * Date: 2011/01/15
 */
class FCFooTrainerDecision : public Decision {
public:
  FCFooTrainerDecision(ActuatorInterface* const actuator_interface = NULL);
  virtual ~FCFooTrainerDecision();

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
//    virtual void onBeforeTick();
  //virtual void onAfterTick();

  //virtual void onNewCycle(const bool forced);
  //virtual bool onEstimatedNewCycle(UInt16 estimated_time, UInt16 ticks);
  //virtual void onCommandWarning();

protected:
  ViewManager* const viewManager;
  const WorldModelInterface* const worldModelInterface;
  const WorldFacts* facts;
  GameView* gameView;
  BallView* ballView;
  PlayerView* playerView;
};


RS_END_NAMESPACE


#endif // !FCFOO_TRAINER_DECISION_H
