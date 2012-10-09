/* -*- Mode: C++ -*-
 * $Id: FCFooCoachDecision.cc,v 1.14 2003/12/07 17:07:20 frehe Exp $
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
 * Filename: FCFooCoachDecision.cc
 * Unitname: Framework/example/FCFooCoach
 * $Revision: 1.14 $
 * Created by: Fredrik Heintz 2001-11-15
 * Last modified by $Author: frehe $ $Date: 2003/12/07 17:07:20 $
 *
 *
 * HISTORY
 *
 * $Log: FCFooCoachDecision.cc,v $
 * Revision 1.14  2003/12/07 17:07:20  frehe
 * Print ball state in coach logfile.
 *
 * Revision 1.13  2003/11/30 12:45:18  frehe
 * Removed erroneous code.
 *
 * Revision 1.12  2003/11/26 07:59:21  frehe
 * Send a valid coach command every 10 cycles.
 *
 * Revision 1.11  2003/11/23 17:01:12  frehe
 * Removed say command which causes a crash, but I don't know why...
 *
 * Revision 1.10  2003/08/27 09:25:41  petan
 * Fixed warnings at compile time
 *
 * Revision 1.9  2003/07/22 14:47:23  s02davro
 * Updated coach/trainer/player for testing new features
 *
 * Revision 1.8  2003/07/21 09:26:28  s02davro
 * Update of coach agent
 *
 * Revision 1.7  2002/09/04 14:48:05  s02davro
 * Updated FCFoos desision making
 *
 * Revision 1.6  2002/08/31 15:17:17  s02davro
 * FCFoo now run coach with -coach option, changed the main loop
 *
 * Revision 1.5  2002/01/16 09:54:19  frehe
 * Minor changes.
 *
 * Revision 1.4  2002/01/15 17:20:44  frehe
 * Changed the message sent by the coach.
 *
 * Revision 1.3  2002/01/14 17:33:10  frehe
 * Fixed the freeform message from the coach.
 *
 * Revision 1.2  2001/12/20 14:58:55  frehe
 * Call the decide method in onVisualSensorData.
 *
 * Revision 1.1  2001/11/15 16:50:13  frehe
 * Added a coach agent
 *
 */

/**
 * @file FCFooCoachDecision.cc
 * Implementation of the class FCFooCoachDecision.
 *
 * @par Unit:
 *      Framework/example/FCFooCoach
 * $Revision: 1.14 $
 * $Author: frehe $
 * $Date: 2003/12/07 17:07:20 $
 */

#include "FCFooCoachDecision.h"

#include <unistd.h>
#include <errno.h>

#include "ViewManager.h"
#include "ActuatorInterface.h"
#include "InitCommand.h"
#include "EyeCommand.h"
#include "LookCommand.h"
#include "CoachSubstitutionCommand.h"
#include "SayCommand.h"
#include "rs_assert.h"
#include "rs_log.h"
#include "BallView.h"
#include "view_constants.h"


RS_BEGIN_NAMESPACE

FCFooCoachDecision::FCFooCoachDecision(ActuatorInterface* const actuator_interface)
  : Decision(actuator_interface),
    viewManager(ViewManager::instance()),
    worldModelInterface(WorldModelInterface::instance()),
    facts(worldModelInterface->getWorldFacts()) {
}

FCFooCoachDecision::~FCFooCoachDecision() {
}

ServerCommand* FCFooCoachDecision::initAgent() {
  InitCommand* init_cmd = new InitCommand(facts->CP_team_name,
					  facts->SP_version,
					  false);
  return init_cmd;
}

bool FCFooCoachDecision::start() {
  RS_REQUIRE( initialized == true );
  return true;
}

bool FCFooCoachDecision::decide() {
  static int say_counter = 0;
  static bool eye = true;
  
  const WorldModel& wm = worldModelInterface->getWorld();
  
  for (std::vector<PlayerObject>::const_iterator i = wm.getTeammates().begin();
       i != wm.getTeammates().end(); ++i) 
    RS_LOG ( LA_COACH, "Coach: " 
	     << Time::currentTime
	     << "\n        "
	     << i->getUniformNumber()
	     << "\n        "
	     << i->getPosition().getPoint()
	     << "\n        "
	     << i->getPointDirection()
	     << "\n        "
	     << i->getTackling());
  
  /*
  BallView* ballView;
  getView(ballView, BALL_VIEW_ID);
  RS_LOG ( LA_COACH, "Coach: "
	   << Time::currentTime
	   << " ball pos = " << ballView->getPosition() );
  viewManager->releaseView(BALL_VIEW_ID);
  */
  RS_LOG ( LA_COACH, "Coach: "
	   << Time::currentTime
	   << " ball pos = " << wm.getBall().getPosition() );


  // TODO CLang communication.
  if ( say_counter == 0 ) {
    /*
    SayCommand* coachcmd = new SayCommand("(freeform \"Test\")");
    actuatorInterface->addToPlan(coachcmd);
    */
    /*
    EyeCommand* ec = new EyeCommand(eye);
    actuatorInterface->addToPlan(ec);
    eye = !eye;
    */
    SayCommand* coachcmd = new SayCommand("(info (clear))");
    //LookCommand* coachcmd = new LookCommand();
    actuatorInterface->addToPlan(coachcmd);
    
    say_counter = 9;
  } else {
    --say_counter;
  }
  return true;
}

void FCFooCoachDecision::onInit() {
  /*
  const std::vector<PlayerType> types = facts->getPlayerTypes();
  UInt fastestplayer = 0;
  for (unsigned int i = 1; i < types.size(); ++i) {
    if (types[i].dash_power_rate > types[fastestplayer].dash_power_rate)
      fastestplayer = i;
  }
  CoachSubstitutionCommand *sc = new CoachSubstitutionCommand(1, fastestplayer);
  actuatorInterface->addToPlan(sc);
  delete sc;
  */

  EyeCommand* ec = new EyeCommand(true);
  actuatorInterface->addToPlan(ec);
  delete ec;
}

void FCFooCoachDecision::onAfterSensorData() {
  decide();
}

RS_END_NAMESPACE
