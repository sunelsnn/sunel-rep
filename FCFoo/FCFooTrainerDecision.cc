/* -*- Mode: C++ -*-
 * $Id: FCFooTrainerDecision.cc,v 1.4 2003/08/27 09:25:42 petan Exp $
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
 * Filename: FCFooTrainerDecision.cc
 * Unitname: Framework/example/FCFooCoach
 * $Revision: 1.4 $
 * Created by: David Ros�n 2002-12-07
 * Last modified by $Author: petan $ $Date: 2003/08/27 09:25:42 $
 *
 *
 * HISTORY
 *
 * $Log: FCFooTrainerDecision.cc,v $
 * Revision 1.4  2003/08/27 09:25:42  petan
 * Fixed warnings at compile time
 *
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
 * @file FCFooTrainerDecision.cc
 * Implementation of the class FCFooTrainerDecision.
 *
 * @par Unit:
 *      Framework/example/FCFooCoach
 * $Revision: 1.4 $
 * $Author: petan $
 * $Date: 2003/08/27 09:25:42 $
 *
 * Modified: Functionality change
 * Author: Sunil Mamidi
 * Date: 2011/01/20
 */

#include "FCFooTrainerDecision.h"

#include <unistd.h>
#include <errno.h>

#include "ViewManager.h"
#include "ActuatorInterface.h"
#include "TrainerInitCommand.h"

#include "EyeCommand.h"
#include "EarCommand.h"
#include "CheckBallCommand.h"
#include "ChangeModeCommand.h"
#include "MoveObjectCommand.h"
#include "StartCommand.h"
#include "RecoverCommand.h"
#include "TrainerSubstitutionCommand.h"
#include "LookCommand.h"
#include "TeamNamesCommand.h"

#include "rs_assert.h"
#include "rs_log.h"
#include "BallView.h"
#include "view_constants.h"

RS_BEGIN_NAMESPACE

FCFooTrainerDecision::FCFooTrainerDecision(ActuatorInterface* const actuator_interface)
  : Decision(actuator_interface),
    viewManager(ViewManager::instance()),
    worldModelInterface(WorldModelInterface::instance()),
    facts(worldModelInterface->getWorldFacts()) {
  getView(gameView, GAME_VIEW_ID);
  getView(ballView, BALL_VIEW_ID);
  getView(playerView, PLAYER_VIEW_ID);
}

FCFooTrainerDecision::~FCFooTrainerDecision() {
  viewManager->releaseView(GAME_VIEW_ID);
  viewManager->releaseView(BALL_VIEW_ID);
  viewManager->releaseView(PLAYER_VIEW_ID);
}

ServerCommand* FCFooTrainerDecision::initAgent() {
  TrainerInitCommand* init_cmd = new TrainerInitCommand(facts->SP_version);
  return init_cmd;
}

bool FCFooTrainerDecision::start() {
  RS_REQUIRE( initialized == true );
  return true;
}

bool FCFooTrainerDecision::decide() {
  // static int say_counter = 0;

  static int player_counter = 0;
  static int started = false;
  int team_counter = 0;
  int pcount;
  pcount = playerView->getOpponents().size() + playerView->getTeammates().size();
  if (playerView->getOpponents().size() > 0) team_counter++;
  if (playerView->getTeammates().size() > 0) team_counter++;

  RS_LOG (LA_COACH, "Trainer: " << worldModelInterface->getCurrentTime());
  RS_LOG (LA_COACH, "Trainer: " << playerView->getOpponents().size() << " opponents (r) "
	  << playerView->getTeammates().size() << " teammates (l) " 
	  << playerView->getUnknownPlayers().size() << " unknowns = "
	  << pcount << " (last " << player_counter << ") team(s) " 
	  << team_counter);
  
  
  if ((pcount > player_counter) && 
      (team_counter <= 2) && 
      (gameView->getPlayMode() == PM_BEFORE_KICK_OFF) &&
      (!started)) {
    RS_LOG (LA_COACH, "Trainer detects new player, checking team names.");
    TeamNamesCommand *tnc = new TeamNamesCommand();
    actuatorInterface->addToPlan(tnc);
    delete tnc;
    player_counter = pcount;
  } else if ((team_counter == 2) && 
	     (player_counter >= 2) && 
	     (gameView->getPlayMode() == PM_BEFORE_KICK_OFF) &&
	     (!started)) {
    RS_LOG (LA_COACH, "Trainer: " << playerView->getOpponents().size() << " opponents (r) "
	    << playerView->getTeammates().size() << " teammates (l) " 
	    << playerView->getUnknownPlayers().size() << " unknowns ");
    RS_LOG (LA_COACH, "Trainer detects two teams and correct number of players. Starting the 'game'");
    StartCommand *sc = new StartCommand();
    actuatorInterface->addToPlan(sc);
    delete sc;
    started = true;
  }

//    if (gameView->getCurrentTime().getT() > 0) {
//      static int pmint = 1;
//      if ((gameView->getCurrentTime().getT() % 5) == 0) {
//        ChangeModeCommand *cmc = new ChangeModeCommand((PlayMode) pmint);
//        actuatorInterface->addToPlan(cmc);
//        delete cmc;
//        pmint++;
//      }
//    }
  
  PlayerObject player = playerView->getOpponentClosestToBall();
  
  if (player.getPosition().isKnown() && ballView->getPosition().isKnown())
    if (player.getPosition().getDistanceTo(ballView->getPosition()) < 10) {
      Vector pTob(player.getPosition().getPoint() - ballView->getPosition().getPoint());
      pTob.setLength(10);
      pTob.rotate(2);
      Point newBallPos = player.getPosition().getPoint() - pTob;
      RS_LOG (LA_COACH, "Trainer is moving ball and player." << worldModelInterface->getCurrentTime());
      MoveObjectCommand *moc = new MoveObjectCommand(ballView->getBallObject(),
						     newBallPos);
      actuatorInterface->addToPlan(moc);
      delete moc;

      MoveObjectCommand *moc2 = new MoveObjectCommand(player, 
						      facts->CP_their_team_name,
						      player.getPosition().getPoint() +
						      pTob * 0.1);
      actuatorInterface->addToPlan(moc2);
      delete moc2;
    }
  
  return true;
}

void FCFooTrainerDecision::onInit() {
  EyeCommand *ec = new EyeCommand(true);
  actuatorInterface->addToPlan(ec);
  delete ec;
//    EarCommand *eec = new EarCommand(true);
//    actuatorInterface->addToPlan(eec);
//    delete eec;
}

void FCFooTrainerDecision::onAfterSensorData() {
  decide();
}

RS_END_NAMESPACE
