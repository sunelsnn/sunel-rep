/* -*- Mode: C++ -*-
 * $Id: FCFooDecision.h,v 1.18 2004/08/13 11:48:30 petan Exp $
 *
 *
 * COPYRIGHT INFORMATION
 *
 * This file is part of RoboSoc created by Fredrik Heintz <frehe@ida.liu.se>
 * Copyright (C) 1999, 2000 Fredrik Heintz, Linkping University, Sweden
 *
 * You are allowed to modify and use this code as long as you retain this
 * notice. If you make any changes or have any comments I would appreciate
 * it if you send me a message. For more information, please see
 * http://www.ida.liu.se/~frehe/RoboCup/RoboSoc/
 *
 *
 * IDENTIFICATION
 *
 * Filename: FCFooDecision.h
 * Unitname: Framework/example/FCFoo
 * $Revision: 1.18 $
 * Created by: Fredrik Heintz 1999-xx-xx
 * Last modified by $Author: petan $ $Date: 2004/08/13 11:48:30 $
 *
 *
 * HISTORY
 *
 * $Log: FCFooDecision.h,v $
 * Revision 1.18  2004/08/13 11:48:30  petan
 * Turned off logging, updated with better running
 *
 * Revision 1.17  2004/08/10 15:03:48  petan
 * Removed GotoBall from FCFoo
 *
 * Revision 1.16  2003/09/02 18:02:57  frehe
 * Updated to the new command pointer semantics.
 *
 * Revision 1.15  2003/08/27 09:25:42  petan
 * Fixed warnings at compile time
 *
 * Revision 1.14  2003/08/20 12:33:46  s02davro
 * onDelayedActions function
 *
 * Revision 1.13  2003/07/21 09:28:10  s02davro
 * Updated FCFoo to test v.9 features
 *
 * Revision 1.12  2002/09/04 14:48:05  s02davro
 * Updated FCFoos desision making
 *
 * Revision 1.11  2002/08/31 15:17:17  s02davro
 * FCFoo now run coach with -coach option, changed the main loop
 *
 * Revision 1.10  2002/08/02 22:03:38  s02davro
 * Changed FCFoo to test the modifications done (WorldModelInterface, Errors ...)
 *
 * Revision 1.9  2001/10/14 21:21:44  frehe
 * Added better support for messages from self and from other players.
 *
 * Revision 1.8  2001/10/14 14:41:39  frehe
 * Added a sample communication between the agent and itself.
 *
 * Revision 1.7  2001/09/26 13:06:50  frehe
 * Added the WorldViewState.
 *
 * Revision 1.6  2001/08/29 14:16:23  frehe
 * Made a simpler decision maker to avoid skills (until I get them to work).
 *
 * Revision 1.5  2000/10/24 15:15:46  frehe
 * Made minor updates and tests.
 *
 * Revision 1.4  2000/10/19 00:05:35  frehe
 * Made minor changes.
 *
 * Revision 1.3  2000/10/11 18:40:30  frehe
 * Upgraded FCFoo.
 *
 * Revision 1.2  2000/09/05 21:12:55  frehe
 * Made FCFoo compile with RoboSoc 2.5.0
 *
 * Revision 1.1.1.1  2000/08/31 13:26:05  frehe
 * Importet the current version of RoboSoc (soon to be v2.5.0)
 *
 */

/**
 * @file FCFooDecision.h
 * Include file for the class FCFooDecision.
 *
 * @par Unit:
 *      Framework/example/FCFoo
 * $Revision: 1.18 $
 * $Author: petan $
 * $Date: 2004/08/13 11:48:30 $
 */


#ifndef FCFOODECISION_H
#define FCFOODECISION_H


#include "basic_system_compiler_directives.h"
#include "Decision.h"
#include "WorldModelInterface.h"
#include "SearchBall.h"
#include "DashToPoint.h"
#include "TurnBodyToPoint.h"

RS_BEGIN_NAMESPACE

class ViewManager;
class BallView;
class AgentView;
class PlayerView;
class GameView;

/**
 * @class FCFooDecision FCFooDecision.h
 * Example class for what a decision maker might look like.
 *
 * <!-- @todo-->
 *
 * @par Unit:
 *      Library
 * $Revision: 1.18 $
 * $Author: petan $
 * $Date: 2004/08/13 11:48:30 $
 *
 * Modified:  Added new functionality, dashtopointdir, different viewer.
 * Author: Sunil Mamidi
 * $Date:  2011/01/10
 */
class FCFooDecision : public Decision {
public:
  FCFooDecision(ActuatorInterface* const actuator_interface = NULL);
  virtual ~FCFooDecision();

  virtual ServerCommand* initAgent();
  virtual bool start();
  virtual bool decide();

  // Event handlers
  //virtual void onActuatorSensorData();
  virtual void onAuralCoachSensorData();
  virtual void onAuralRefereeSensorData();
  virtual void onAuralPlayerSensorData();
  virtual void onAuralSelfSensorData();
  virtual void onInit();
  //virtual void onPhysicalSensorData();
  //virtual void onVisualSensorData();

  //virtual void onBeforeSensorData();
  //virtual void onAfterSensorData();
  //virtual void onBeforeTick();
  //virtual void onAfterTick();

  //virtual void onNewCycle(const bool forced);
  //virtual bool onEstimatedNewCycle(UInt16 estimated_time, UInt16 ticks);
  virtual void onCommandWarning();
  virtual void onDelayedActions();
  bool readQFile() ;
  void writeQFile() ;
  void ActionSelection(int, Point, int ) ;
  void initQtab() ;
  void predictedState() ;
//  void getPlayerInfo(const std::vector<PlayerObject>& opps_wm, const std::vector<PlayerObject>& team_wm,
//			const std::vector<PlayerObject>&  opps_pv,WorldModel&  , float *rec_theta1  , float *rec_theta2) ;

   void getPlayerInfo(WorldModel&  ,WorldModelInterface *, AgentView *, BallView *, PlayerView * ,  float* , float*, float*,float*) ;
   void getPlayerInfo() ;
  // void passM( PlayerObject& rec, int Uno) ;
   void passM(int Uno) ;
  void thetaCorrection() ;
  void predThetaCorrection() ;
  void qvalUpdate() ;
  void predictedWorldstate(ServerCommand *scmd, ServerCommand *scmd2 ) ;
  void updateQtab() ;
  void updateQInf(int Agentno, int CURRTIME, int theta1, int theta2 , int ratio1, int ratio2 ,int act , float stateval) ;
  void turnAroundBall() ;

protected:
  ViewManager* const viewManager;
  const WorldModelInterface* const worldModelInterface;
  const WorldFacts *facts;
  GameView* gameView;
  BallView* ballView;
  PlayerView* playerView;
  AgentView* agentView;
  int aural_data;
  SearchBall searchBall;
  DashToPoint dashToPoint;
  TurnBodyToPoint turnBodyToPoint;
};


RS_END_NAMESPACE


#endif // !FCFOODECISION_H
