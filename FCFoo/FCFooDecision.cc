/* -*- Mode: C++ -*-
 * $Id: FCFooDecision.cc,v 1.33 2005/08/13 13:33:11 frehe Exp $
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
 * Filename: FCFooDecision.cc
 * Unitname: Framework/example/FCFoo
 * $Revision: 1.33 $
 * Created by: Fredrik Heintz 1999-xx-xx
 * Last modified by $Author: frehe $ $Date: 2005/08/13 13:33:11 $
 *
 *
 * HISTORY
 *
 * $Log: FCFooDecision.cc,v $
 * Revision 1.33  2005/08/13 13:33:11  frehe
 * Test the point to command.
 *
 * Revision 1.32  2004/08/16 13:12:55  petan
 * Made decision a bit leaner using AgentStep instead of Step
 *
 * Revision 1.31  2004/08/13 11:48:30  petan
 * Turned off logging, updated with better running
 *
 * Revision 1.30  2004/08/10 15:03:48  petan
 * Removed GotoBall from FCFoo
 *
 * Revision 1.29  2003/09/02 18:03:00  frehe
 * Updated to the new command pointer semantics.
 *
 * Revision 1.28  2003/08/27 09:25:42  petan
 * Fixed warnings at compile time
 *
 * Revision 1.27  2003/08/20 12:33:38  s02davro
 * onDelayedActions function
 *
 * Revision 1.26  2003/07/22 14:47:23  s02davro
 * Updated coach/trainer/player for testing new features
 *
 * Revision 1.25  2003/07/21 09:28:10  s02davro
 * Updated FCFoo to test v.9 features
 *
 * Revision 1.24  2002/09/04 14:48:05  s02davro
 * Updated FCFoos desision making
 *
 * Revision 1.23  2002/08/31 15:17:16  s02davro
 * FCFoo now run coach with -coach option, changed the main loop
 *
 * Revision 1.22  2002/08/02 22:03:38  s02davro
 * Changed FCFoo to test the modifications done (WorldModelInterface, Errors ...)
 *
 * Revision 1.21  2001/10/14 21:21:43  frehe
 * Added better support for messages from self and from other players.
 *
 * Revision 1.20  2001/10/14 14:41:42  frehe
 * Added a sample communication between the agent and itself.
 *
 * Revision 1.19  2001/09/26 13:05:37  frehe
 * Changed the order of include files to make circular updates less likely.
 *
 * Revision 1.18  2001/09/01 23:55:08  frehe
 * Made minor changes.
 *
 * Revision 1.17  2001/08/30 22:08:26  frehe
 * Wrote two simple decision makers that goes to the ball and scores.
 *
 * Revision 1.16  2001/08/29 16:31:19  frehe
 * Added some exception handling.
 *
 * Revision 1.15  2001/08/29 14:16:27  frehe
 * Made a simpler decision maker to avoid skills (until I get them to work).
 *
 * Revision 1.14  2001/08/29 08:38:34  petan117
 * Unreachable code found, marked with a FIXME
 *
 * Revision 1.13  2001/08/17 07:15:16  frehe
 * Made changes to compile RoboSoc with RCCParser-0.10.
 *
 * Revision 1.12  2001/01/08 13:41:40  frehe
 * Fixed a minor bug in FCFooDecision.
 *
 * Revision 1.11  2001/01/08 13:27:45  frehe
 * Fixed a minor bug in FCFooDecision.
 *
 * Revision 1.10  2000/11/08 09:41:10  frehe
 * Updated the FCFooDecision to use the Score skill.
 *
 * Revision 1.9  2000/11/02 16:33:45  frehe
 * Minor updates.
 *
 * Revision 1.8  2000/10/24 15:15:46  frehe
 * Made minor updates and tests.
 *
 * Revision 1.7  2000/10/19 00:05:35  frehe
 * Made minor changes.
 *
 * Revision 1.6  2000/10/18 23:07:11  frehe
 * Added a say message and a display of them.
 *
 * Revision 1.5  2000/10/11 18:40:29  frehe
 * Upgraded FCFoo.
 *
 * Revision 1.4  2000/10/10 11:55:37  frehe
 * Fixed FCFooDecision to work with the new skills.
 *
 * Revision 1.3  2000/10/08 17:34:11  frehe
 * Fixed FCFoo.
 *
 * Revision 1.2  2000/09/05 21:12:55  frehe
 * Made FCFoo compile with RoboSoc 2.5.0
 *
 * Revision 1.1.1.1  2000/08/31 13:26:05  frehe
 * Importet the current version of RoboSoc (soon to be v2.5.0)
 *
 */

/**
 * @file FCFooDecision.cc
 * Implementation of the class FCFooDecision.
 *
 * @par Unit:
 *      Framework/example/FCFoo
 * $Revision: 1.33 $
 * $Author: frehe $
 * $Date: 2005/08/13 13:33:11 $
 *
 *
 * Modified: Incorporated Reinforcement learning, CMAC
 * Author: Sunil Mamidi
 * Date:  2011/01/25
 */


#include "FCFooDecision.h"

#include <unistd.h>
#include <errno.h>
#include <iostream>

#include "BallView.h"
#include "GameView.h"
#include "AgentView.h"
#include "PlayerView.h"
#include "ActuatorInterface.h"
#include "ViewManager.h"
#include "view_constants.h"
#include "InitCommand.h"
#include "ClangVersionCommand.h"
#include "MoveCommand.h"
#include "SayCommand.h"
#include "DashCommand.h"
#include "KickCommand.h"
#include "TurnCommand.h"
#include "TurnNeckCommand.h"
#include "TurnNeckToAbsoluteDirection.h"
#include "TurnNeckToPoint.h"
#include "TurnNeckToBall.h"
#include "TurnBodyToAbsoluteDirection.h"
#include "TurnBodyToPoint.h"
#include "PointToCommand.h"
#include "TackleCommand.h"
#include "SetTicksBeforeCommandWarning.h"
#include "rs_assert.h"
#include "rs_log.h"
#include "DashToPointDir.h"
#include "AlignNeckToBody.h"
#include "Time.h"
#include "math.h"
#include "AngleDegreesUE.h"
#include "CoordPointUE.h"
#include <fstream>
#include <stdio.h>
#include <string.h>
//#include </opt/cmac/cmac.h>
//#include </opt/cmac/interface_classes.h>
#include <cmac.h>

RS_BEGIN_NAMESPACE
// Defines the max angle before turning when dashing to a point
#define DASH_MAX_ANGLE 15

FCFooDecision::FCFooDecision(ActuatorInterface* const actuator_interface)
  : Decision(actuator_interface),
    viewManager(ViewManager::instance()),
    worldModelInterface(WorldModelInterface::instance()),
    facts(worldModelInterface->getWorldFacts()),
    gameView(NULL),
    ballView(NULL),
    playerView(NULL),
    agentView(NULL),
    aural_data(0),
    dashToPoint(Point(0,0)),
    turnBodyToPoint(Point(0,0)) {
  getView(ballView, BALL_VIEW_ID);
  getView(playerView, PLAYER_VIEW_ID);
  getView(gameView, GAME_VIEW_ID);
  getView(agentView, AGENT_VIEW_ID);
}

FCFooDecision::~FCFooDecision() {
  viewManager->releaseView(GAME_VIEW_ID);
  viewManager->releaseView(BALL_VIEW_ID);
  viewManager->releaseView(PLAYER_VIEW_ID);
  viewManager->releaseView(AGENT_VIEW_ID);
}

ServerCommand* FCFooDecision::initAgent() {
  InitCommand* init_cmd = new InitCommand(facts->CP_team_name,
					  facts->SP_version,
					  facts->CP_goalie);
  return init_cmd;
}

bool mapstatus[11] ;
bool FCFooDecision::start() {
  RS_REQUIRE( initialized == true );
 // initQtab() ;
  for (int i= 1 ; i<=11 ;i++){ mapstatus[i]= false ; }
  RS_LOG(LA_AGENT, "intialised "<<mapstatus[1]<<" "<<mapstatus[2]) ;
  // if ( readQFile() == false ) initQtab() ;
  //if ( readQFile() == false ) exit(0) ;
  // readQFile() ;
  return true;
}



static const WorldModelInterface* wmi = WorldModelInterface::nonConstInstance();
 const  WorldModel& wm = wmi->getWorld();
Time TIME ;

UInt PREVTIME=0 ;
UInt CURRTIME=0;
int angleinc=0;
// const std::vector<PlayerObject>& opps_wm =0 ;
// const std::vector<PlayerObject>& team_wm =0;
PlayerObject opps[11] , teamm[11] , opps_p[11] ;
int notheta1 = 10 ; int notheta2 = 10 ; int noratio1 = 4 ; int noratio2 = 4 ;
int nostates = notheta1*notheta2*noratio1*noratio2;
int noratio, noaction=4 ; int noactionqtab =5 ; int qtabstruct = 1 ;
char* filecmac = "cmacfile.txt" ;
 CMAC cma1(filecmac);
 CMAC cma2(filecmac) ;
 CMAC  cma3(filecmac) ;
 CMAC cma4(filecmac) ;
 CMAC cma5(filecmac) ;
 State cmstate[1600] ;
double DECAYFACTOR = 0.4 ;

float rec_theta1[11] ;
float rec_theta2[11] ;
float  rec_dist1[11] ;
float rec_dist2[11] ;
int rec_rtheta1[11] ;
int rec_rtheta2[11] ;
float rec_ratio1[11] ;
float rec_ratio2[11] ;
int rec_rratio1[11] ;
int rec_rratio2[11] ;
float recp_theta1[11] ;
float recp_theta2[11] ;
int recp_rtheta1[11] ;
int recp_rtheta2[11] ;
float recp_ratio1[11] ;
float recp_ratio2[11] ;
int recp_rratio1[11] ;
int recp_rratio2[11] ;
float Qtab[1600][5] ;
bool  Qex[1600][5] ;
int AgeUno , AGENUNO ;
//float rec_ptheta1[11] ;
//float rec_ptheta2[11] ;


Point *opp_loc ;
bool kick_status = false ;
bool turn_status = false ;
Point TurnPoint_P1, TurnPoint_P2, TurnPoint_P3, TurnPoint_P4 ;
std::vector<PlayerObject> opps_wm  ; // = wm.getOpponents();
 std::vector<PlayerObject> team_wm ; //=  wm.getTeammates() ;
 std::vector<PlayerObject> opps_pv ; //= wm.getOpponents()  ;
 std::string cmdty  ;
 bool amIClosest =false  ;
 int MapUnoToPass[4] ; int MapPassToUno[11] ;
 ServerCommand *gscmd_1=0, *gscmd2_1=0, *gscmd_2=0, *gscmd2_2=0, *gscmd_3=0, *gscmd2_3=0, *gscmd_4=0, *gscmd2_4=0 ;
bool FCFooDecision::readQFile()
{

	std::ifstream file1("qfile.txt", std::ios_base::in) ;
	if (!file1.is_open())
	{ std::cout<< "\n couldnt open file " ;
	RS_LOG(LA_AGENT,  "\n couldnt open file ") ; return false;}

	int i=0,j=0,k=0,k1=0,num1=0; char a[2000]; // , a1[2000] ;

	float a1,a2,a3,a4, a5 ;
	 k=0;j=0; State st(1) ; st.x = new double [4] ;
	for (i=0; i<nostates; i++)
	{
	     file1.getline(a,2000) ;

	     std::sscanf(a,"%f %f %f %f %f", &a1,&a2,&a3,&a4, &a5) ;
	     Qtab[i][0] = a1 ; if (a1!=0) Qex[i][0] = true ;
	     Qtab[i][1] = a2 ; if (a2!=0) Qex[i][1] = true ;
	     Qtab[i][2] = a3 ; if (a3!=0) Qex[i][2] = true  ;
	     Qtab[i][3] = a4 ; if (a4!=0) Qex[i][3] = true ;
	     Qtab[i][4] = a5 ; if (a5!=0) Qex[i][4] = true  ;
	     RS_LOG(LA_AGENT, "\n"<<Qtab[i][0]<<" "<<Qtab[i][1]<<" "<<Qtab[i][2]<<" "<<Qtab[i][3]<<" "<<Qtab[i][4]) ;



	     st.x[0] = int(i/160)  ;
	     st.x[1] = int(  (i-st.x[0]*160)/16) ;
         st.x[2] = int ( (i -st.x[0]*160 -st.x[1]*16)/4) ;
         st.x[3] = int(i - st.x[0]*160 - st.x[1]*16 - st.x[2]*4 ) ;
         std::cout<<" state info before cmac is called "<<st.x[0]<<" "<<st.x[1]<<" "<<st.x[2]<<" "<<st.x[3] ;
          if(Qtab[i][0] !=  0 and Qex[i][0] == true ) {
        	  for (int i = 0 ; i < cma1.T ; i++ )
        	  {   cma1.tilings[i].decayTraces(0) ; }
        	  	  cma1.replaceTraces(st, double(1.0)) ;
        	  	  cma1.learn(st ,double( a1)) ;
                    }
          if (Qtab[i][1] != 0 and Qex[i][1] == true ) {
        	  for (int i = 0 ; i < cma2.T ; i++ )
        	  { cma2.tilings[i].decayTraces(0) ; }
        	  cma2.replaceTraces(st, 1) ;
        	  cma2.learn(st, double(a2)) ; }
          if (Qtab[i][2] != 0 and Qex[i][2] == true ){
        	  for (int i = 0 ; i < cma3.T ; i++ )
        	   {   cma3.tilings[i].decayTraces(0) ; }
        	  cma3.replaceTraces(st, 1) ;
        	  cma3.learn(st, double(a3)) ;      }
          if (Qtab[i][3] != 0 and Qex[i][3] == true ) {
        	  for (int i = 0 ; i < cma4.T ; i++ )
        	 {   cma4.tilings[i].decayTraces(0) ; }
        	  cma4.replaceTraces(st, 1) ;
        	  cma4.learn(st, double(a4)) ; }
          if (Qtab[i][4] != 0 and Qex[i][4] == true  ) {
        	  for (int i = 0 ; i < cma5.T ; i++ )
        	  {   cma5.tilings[i].decayTraces(0) ; }
        	  cma5.replaceTraces(st, 1) ;
        	  cma5.learn(st, double(a5)) ;
        	  }

	     //NEED TO IMPLEMENT CODE TO TRAIN A PRE LEARNED POLICY

//	     while(a[k]!='\n')
//	     { k1=0;num1=0;
//	       while(a[k]!=' ')
//	       { a1[k1] =a[k]; k1++ ;k++ ;
//	       a1[k1] = '\0' ; num1 = std::atof(a1) ;
//	       Qtab[i][j] = num1 ;
//	       j++;k++; if(j>=noaction) { std::cout << "some error" ;
//	       RS_LOG(LA_AGENT,"some error") ; break ;}
//
//	       } // while
//	     } // while

	     } // for
file1.close() ;

return true ;


} // readQfile


//line format: theta1 theta2 ratio1 ratio2 action value
void FCFooDecision::updateQtab()
{
std::ifstream file2("qfileinf.txt", std::ios_base::in ) ;
if(!file2.is_open())
{ RS_LOG(LA_AGENT,"couldnt open file") ; }
char buf[100], a[100] , a1[100], a2[100] ;
file2.seekg( -100,  std::ios_base::end);
while( !file2.eof())
{    strcpy(a,a2) ;
	file2.getline(a2,100) ;
     RS_LOG(LA_AGENT, "the get line a "<<a) ;
	//std::strcpy(a , buf) ;
} // while
file2.close();
RS_LOG(LA_AGENT, "QINF READ:"<<a) ;
float states[8] ;int i=0,k1=0,k=0 ;
//for( int i=0 ; i<8 ; i++)
//{
//		k1=0;
//		       while(a[k]!=' ')
//		       { a1[k1] =a[k]; k1++ ;k++ ; }
//		       states[i]= std::atof(a1); i++ ;
//		        } // for

int Uno, currtime, the1,the2,rat1, rat2, act ; float staval ;
//std::sscanf(a,"%d %d %d %d %d %d %d %f\n", states[0], states[1], states[2],states[3],states[4], states[5],states[6],states[7]) ;

std::sscanf(a,"%d %d %d %d %d %d %d %f\n",&Uno, &currtime, &the1,&the2,&rat1,&rat2,&act,&staval) ;

states[0]= Uno ;
states[1]=currtime ;
states[2]=the1 ;
states[3] = the2 ;
states[4]=rat1 ;
states[5] = rat2 ;
states[6]=act ;
states[7] = staval ;
if( AGENUNO!= int(states[0]) and CURRTIME > (states[1]))
{
int st = int(states[2])*notheta2*noratio1*noratio2 +  int(states[3])*noratio1*noratio2  +  int(states[4])*noratio2 + int(states[5]) ;
int ac =  int(states[6])-qtabstruct ; ;
Qtab[st][ac] = states[7] ; Qex[st][ac] = true ;
State st1(1) ; st1.x  = new double[4];
st1.x[0] = int(states[2]) ;
st1.x[1] = int(states[3]) ;
st1.x[2] = int(states[4]) ;
st1.x[3] = int(states[5]) ;
std::cout<<" state info before cmac is called "<<st1.x[0]<<" "<<st1.x[1]<<" "<<st1.x[2]<<" "<<st1.x[3] ;
double* tr[10] ;
switch(ac)
{
case 1: {
	for (int i = 0 ; i < cma1.T ; i++ )
	{ 	 tr[i] = cma1.tilings[i].saveTrace() ; 	cma1.tilings[i].decayTraces(0) ; }
	RS_LOG(LA_AGENT , "DONE SAVE TRACE AND DECAY TRACE") ;
	cma1.replaceTraces(st1, 1) ;
	RS_LOG(LA_AGENT, "DONE REPLACE TRACE") ;
	cma1.learn( st1,double(states[7]) ) ;
	RS_LOG(LA_AGENT, "DONE LEARNING ") ;
     for (int i =0 ; i<cma1.T ; i++)
	{ cma1.tilings[i].loadTrace(tr[i]) ; }
     RS_LOG(LA_AGENT, "DONE LOAD TRACE") ;
	break ;}
case 2: {
	for (int i = 0 ; i < cma2.T ; i++ )
	{  tr[i] = cma2.tilings[i].saveTrace() ; 	 cma2.tilings[i].decayTraces(0) ; }
	RS_LOG(LA_AGENT , "DONE SAVE TRACE AND DECAY TRACE") ;
	cma2.replaceTraces(st1, 1) ;
	RS_LOG(LA_AGENT, "DONE REPLACE TRACE") ;
	cma2.learn( st1,double(states[7]) ) ;
	RS_LOG(LA_AGENT, "DONE LEARNING ") ;
	for (int i =0 ; i<cma2.T ; i++)
		{ cma2.tilings[i].loadTrace(tr[i]) ; }
	 RS_LOG(LA_AGENT, "DONE LOAD TRACE") ;
break ;}
case 3: {
	for (int i = 0 ; i < cma3.T ; i++ )
		{ 	 tr[i] = cma3.tilings[i].saveTrace() ; 	cma3.tilings[i].decayTraces(0) ; }
	RS_LOG(LA_AGENT , "DONE SAVE TRACE AND DECAY TRACE") ;
	cma3.replaceTraces(st1, 1) ;
	RS_LOG(LA_AGENT, "DONE REPLACE TRACE") ;
		cma3.learn( st1,double(states[7]) ) ;
		RS_LOG(LA_AGENT, "DONE LEARNING ") ;
			for (int i =0 ; i<cma3.T ; i++)
					{ cma3.tilings[i].loadTrace(tr[i]) ; }
			RS_LOG(LA_AGENT, "DONE LOAD TRACE") ;
			break ;
			}
case 4: {
	for (int i = 0 ; i < cma4.T ; i++ )
			{ 	 tr[i] = cma4.tilings[i].saveTrace() ; 	cma4.tilings[i].decayTraces(0) ; }
	RS_LOG(LA_AGENT , "DONE SAVE TRACE AND DECAY TRACE") ;
	cma4.replaceTraces(st1, 1) ;
	RS_LOG(LA_AGENT, "DONE REPLACE TRACE") ;
		cma4.learn( st1,double(states[7]) ) ;
		RS_LOG(LA_AGENT, "DONE LEARNING ") ;
		for (int i =0 ; i<cma4.T ; i++)
							{ cma4.tilings[i].loadTrace(tr[i]) ; }
		RS_LOG(LA_AGENT, "DONE LOAD TRACE") ;

		break ;
}
case 5: {
	for (int i = 0 ; i < cma5.T ; i++ )
				{ 	 tr[i] = cma5.tilings[i].saveTrace() ; 	cma5.tilings[i].decayTraces(0) ; }
	RS_LOG(LA_AGENT , "DONE SAVE TRACE AND DECAY TRACE") ;
	cma5.replaceTraces(st1, 1) ;
	RS_LOG(LA_AGENT, "DONE REPLACE TRACE") ;
	cma5.learn( st1,double(states[7]) ) ;
	RS_LOG(LA_AGENT, "DONE LEARNING ") ;
	for (int i =0 ; i<cma5.T ; i++)
		{ cma5.tilings[i].loadTrace(tr[i]) ; }
	RS_LOG(LA_AGENT, "DONE LOAD TRACE") ;
	break ;
}

}


RS_LOG(LA_AGENT, "\n updating state from other learner "<<int(states[0])<<" "<<st<<" "<<ac<<" "<< states[7]) ;
std::cout<<"\n updating state from other learner "<<int(states[0])<<" "<<st<<" "<<ac<<" "<< states[7] ;
}
}// func updateqtab

void FCFooDecision::updateQInf( int AUno, int CURRTIME, int theta1, int theta2 , int ratio1, int ratio2 ,int act , float stateval)
{

	RS_LOG(LA_AGENT, "in updateQInf") ;

	char a[100] ;
//	a = std::itoa(CURRTIME)+' '+std::itoa(theta1)+' '+std::itoa(theta2)+' '+std::itoa(ratio1)+' '+ std::itoa(ratio2)
	//	+' '	+ std::itoa(act)+ ' '+ std::ftoa(stateval)+ '\n' ;

	 if (AUno > 11 ) { RS_LOG(LA_AGENT, "Agetn uno is greater than 11");
	     RS_LOG(LA_AGENT, "Auno currtime theta1 theta2 ratio1 ratio2 act stateval" <<AUno<<""<<CURRTIME<<" "<<theta1<<" "<<theta2<<" "<<
	    		 ratio1<<" "<<ratio2<<" "<<act<<" "<<stateval);exit(0) ; }
	 std::sprintf(a, "%d %d %d %d %d %d %d %f\n", AUno, CURRTIME-1, theta1,theta2,ratio1, ratio2, act, stateval) ;


		std::ofstream file1("qfileinf.txt", std::ios_base::app) ;
			if (!file1.is_open())
			{ std::cout<< "\n couldnt open file " ;
			RS_LOG(LA_AGENT,"\n couldnt open file ") ; exit(0);}
			RS_LOG(LA_AGENT, "FILE Qinf:"<<a) ;
			file1 << a ;

			file1.close() ;

}

void FCFooDecision::writeQFile()
{


	char file_name[100] ;
	sprintf(file_name, "qfile%d.txt", AGENUNO) ;
//	 file_name = "qfile"+ std::toString(AgeUno)+ ".txt" ;

	std::ofstream file1(file_name, std::ios_base::out) ;
		if (!file1.is_open())
		{ std::cout<< "\n couldnt open file " ;
		RS_LOG(LA_AGENT,"\n couldnt open file ") ; exit(0);}

		  int i=0,j=0 ; char a1[100] ;
	for (i=0; i<nostates ;i++)
	{   for(j=0 ; j< noactionqtab; j++)
	{    sprintf(a1,"%f", Qtab[i][j]) ;
		file1<< a1 <<" " ; }
		file1 <<"\n" ;
	}

	file1.close();

}


  ServerCommand *turnscmd1=0 ; ServerCommand *turnscmd2=0 ;
void FCFooDecision::turnAroundBall()
{
	turnscmd1 = 0 ; turnscmd2 = 0 ;
	Point ball_pos = ballView->getPosition().getPoint();
	float  ang1= ball_pos.getVectorTo(agentView->getPosition().getPoint()).getAngle().getDeg() ;

	//Point destPoint(ball_pos.getX() + 0.5*facts->SP_kickable_margin*cos( AngleDeg(90+ ang1) ) ,
	//		     	   ball_pos.getY() + 0.5*facts->SP_kickable_margin*sin( AngleDeg(90+ ang1 ) )) ;
	 Point destPoint ;
	         if (ballView->getSpeedVector().isKnown()){
	                 Vector v1 = ballView->getSpeedVector().getVector() ;
	          Point tempPoint(ball_pos.getX() + 0.5*facts->SP_kickable_margin*cos( AngleDeg(90+ ang1) )
	                            + v1.getLength()*cos(v1.getAngle())  ,
	                                    ball_pos.getY() + 0.5*facts->SP_kickable_margin*sin(AngleDeg(90+ ang1 )) +
	           v1.getLength()*cos(v1.getAngle())) ;
	         RS_LOG(LA_AGENT, "speed vector "<<v1) ;
	         destPoint = tempPoint ;}
	         else
	         {
	                 Point tempPoint(ball_pos.getX() + 0.5*facts->SP_kickable_margin*cos( AngleDeg(90+ ang1)  ) ,
	                                                    ball_pos.getY() + 0.5*facts->SP_kickable_margin*sin( AngleDeg(90+ ang1 ) )) ;
	                 destPoint = tempPoint ;

	         }


	RS_LOG(LA_AGENT, "TURN AROND BALL \n dest point "<< destPoint) ;
	float deg ;
				      		if ( (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg() ) > 180)
				      		{  deg =  (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg()) - 360 ;}
				      		else if (  (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg() )   < -180 )
				      		{  deg = 360 + (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg()) ; }
				      		else
				      		{ deg = (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg()) ; }

Point agent_pos ;
       if(agentView->getPosition().isKnown())
       {  agent_pos = agentView->getPosition().getPoint() ;}

       RS_LOG( LA_AGENT, " ball pass , agent pos , dest pos "<< ball_pos<<" "<<agent_pos<<" "<<destPoint) ;
	 RS_LOG(LA_AGENT, "dash degree "<< deg) ;
				      		 turnscmd1 = new DashCommand( 100,  deg );
				      		  DashToPointDir  DTPD( turnscmd1) ;
				      		     turnscmd2 = dynamic_cast<ServerCommand*>(DTPD.generateStep().getNextCommand()) ;


} // TURN around ball.

ServerCommand *gscmd=0, *gscmd2=0 ;


//note clean the file contents and then write
void FCFooDecision::ActionSelection (int CMDNO, Point TurnPoint_P, int Uno )
{


	std::cout<<" action selection cmdno and turn piont "<<CMDNO<<" "<<TurnPoint_P ;
	RS_LOG(LA_AGENT," action selection cmdno and turn piont "<<CMDNO<<" "<<TurnPoint_P ) ;

	  gscmd = 0 ; gscmd2=0 ;
	 ServerCommand * scmd=0 ;
	 ServerCommand * scmd2=0 ;
	 Command *cmd=0 ;


	// AngleDegUE TurnAngChk_P1 = float(agentView->getPosition().getDirectionTo(TurnPoint_P1).getDeg()) - float (agentView->getBodyDirection().getAngle().getDeg()) ;
	 //	  AngleDegUE TurnAngChk_P2 = float(agentView->getPosition().getDirectionTo(TurnPoint_P2).getDeg()) - float (agentView->getBodyDirection().getAngle().getDeg()) ;
	 //	  AngleDegUE TurnAngChk_P3 = float(agentView->getPosition().getDirectionTo(TurnPoint_P3).getDeg()) - float (agentView->getBodyDirection().getAngle().getDeg()) ;
	 //	  AngleDegUE TurnAngChk_P4 = float(agentView->getPosition().getDirectionTo(TurnPoint_P4).getDeg()) - float (agentView->getBodyDirection().getAngle().getDeg()) ;

	 float TurnAngChk_P ;
	 if( agentView->getPosition().getDirectionTo(TurnPoint_P).isKnown() and agentView->getBodyDirection().isKnown()) {
	 TurnAngChk_P = float(agentView->getPosition().getDirectionTo(TurnPoint_P).getDeg()) - float (agentView->getBodyDirection().getAngle().getDeg()) ;

	 RS_LOG(LA_AGENT, " agent direction to TurnAngchk_p "<<float(agentView->getPosition().getDirectionTo(TurnPoint_P).getDeg())
			 <<" "<<float (agentView->getBodyDirection().getAngle().getDeg()) ) ;
	 } else if ( CMDNO == 1) return ;



	// CMDNO=1;
	switch( CMDNO)

		  {


		  case 1 :

		  {

//
			  if (
					  // gameView->isKickAllowed()  and
			    	      ( ballView->getRelativeDistance() <= facts->SP_kickable_margin + 2)   //  and kick_status == true
			    	     // and   ( float (goal_dir.getDeg()) - 	float (agentView->getBodyDirection().getAngle().getDeg() ) > facts->SP_maxmoment
			    	      // or    float (goal_dir.getDeg()) - 	float (agentView->getBodyDirection().getAngle().getDeg() ) < facts->SP_minmoment  ) )
			    	     //  and ( TurnAngChk_P > facts->SP_maxmoment or TurnAngChk_P < facts-> SP_minmoment )
			    	      // the TurnAngChkp is to check if the body direction is more than the body turning ability
			    	      )
			      {

				  RS_LOG (LA_AGENT, " TURN AROUND THE BALL  PASSM  "<< MapPassToUno[Uno]) ;
			   //  TurnBodyToAbsoluteDirection   tbtad( agentView->getBodyDirection().getAngle() + 180)	 ;
			    // scmd  = dynamic_cast<ServerCommand*>(tbtad.generateStep().getNextCommand()) ;re
			     // kick_status = true ;
			      		if (CURRTIME > PREVTIME )
			      			{	std::cout<<"\n \n Dash command executed " ;
			      			RS_LOG(LA_AGENT, "\n \n Dash command executed " ) ;
			      			std::cout<<"\n agent postition "<<agentView->getPosition().getPoint() ;
			      			RS_LOG(LA_AGENT, "\n agent postition "<<agentView->getPosition().getPoint()) ;
			      			}

			   // std::cin.get() ;
			      		Point ball_pos = ballView->getPosition().getPoint();
			      		float  ang1= ball_pos.getVectorTo(agentView->getPosition().getPoint()).getAngle().getDeg() ;
			      		float ang2 = ball_pos.getVectorTo(TurnPoint_P).getAngle().getDeg() ;
			      		float moment ;
                     RS_LOG(LA_AGENT, "ball_pos.getVectorTo(agentView->getPosition().getPoint()).getAngle().getDeg() "<< ang1
                    		 <<" ball_pos.getVectorTo(TurnPoint_P).getAngle().getDeg() " << ang2 ) ;
			      		if(ang1 < 0 ) ang1 = 360+ang1 ;
			      		if(ang2 < 0 ) ang2 = 360 +ang2 ;

			      		if (CURRTIME > PREVTIME )  std::cout << "\n angle1 and angl2"<<ang1<<" " <<ang2 ;
			      		if (abs(ang1-ang2) > 180 )
			      			{
			      					 moment = 180 - abs(ang1 -ang2) ;
			      			       if(moment > -90)  moment = -1*facts->SP_maxmoment ; }

			      		else {
			      			      moment = 180 -abs(ang1-ang2) ;
			      			    if (moment > 90 )  moment = facts->SP_maxmoment ; }

			      		RS_LOG(LA_AGENT, "ang1 ang2 moment" << ang1<<" "<<ang2<<" "<<moment) ;

			      		Point destPoint(ball_pos.getX() + 0.5*facts->SP_kickable_margin*cos( AngleDeg(moment+ ang1) ) ,
			      			     	   ball_pos.getY() + 0.5*facts->SP_kickable_margin*sin( AngleDeg(moment+ ang1 ) )) ;


//			     Point destPoint(ball_pos.getX() + 2*facts->SP_kickable_margin*cos( (ang1/abs(ang1))*AngleDeg(moment)+ ang1 ) ,
//			     	   ball_pos.getY() + 2*facts->SP_kickable_margin*sin( (ang1/abs(ang1))*AngleDeg(moment)+ ang1) ) ;

			      	//	Point destPoint(ball_pos.getX() + 3*facts->SP_kickable_margin*cos( AngleDeg(90) + ang1 ) ,
			      		//		ball_pos.getY() + 3*facts->SP_kickable_margin*sin( AngleDeg(90) + ang1) ) ;

			      		if (CURRTIME > PREVTIME )
			      			{std::cout<< "\n ball_pos and dest point"<<ball_pos <<" "<<destPoint ;
			      			RS_LOG(LA_AGENT,"\n ball_pos and dest point"<<ball_pos <<" "<<destPoint ) ;
			      			}

			      		if (CURRTIME > PREVTIME )
			   { std::cout<<"\n vector angle with new location"<<(ball_pos.getVectorTo(destPoint).getAngle() -  ang2) ;
			    RS_LOG(LA_AGENT, "\n vector angle with new location"<<(ball_pos.getVectorTo(destPoint).getAngle() -  ang2) ) ;
			   }

			      		Point relativePoint = destPoint - agentView->getPosition().getPoint();
			      		float  dashPower = agentView->getPowerForDash(relativePoint);

			      		std::cout<<"\n  angle agent to dest  "<<agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()
			      				<<"  body direction"<<agentView->getBodyDirection().getAngle().getDeg() ;
			      		RS_LOG(LA_AGENT,"\n  angle agent to dest  "<<agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()
			      				<<"  body direction"<<agentView->getBodyDirection().getAngle().getDeg() ) ;
			      		Vector  agenttodest(agentView->getPosition().getPoint(), destPoint) ;
			      		std::cout<<" vector angle "<<agenttodest.getAngle() ;
			      		RS_LOG(LA_AGENT, " vector angle "<<agenttodest.getAngle()) ;

			      		float deg ;
			      		if ( (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg() ) > 180)
			      		{  deg = 360 - (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg())  ;}
			      		else if (  (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg() )   < -180 )
			      		{  deg = 360 + (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg()) ; }
			      		else
			      		{ deg = (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg()) ; }

			      		  RS_LOG(LA_AGENT, "dash degree "<< deg) ;
			      		 scmd = new DashCommand( dashPower,  deg );
			      		  DashToPointDir  DTPD(scmd) ;
			      		     scmd2 = dynamic_cast<ServerCommand*>(DTPD.generateStep().getNextCommand()) ;

			      		 		 //  dashPower) ;
			      		// turnBodyToPoint.setPosition(ballView->getPosition().getPoint());
			      		// scmd2 = dynamic_cast<ServerCommand*>(turnBodyToPoint.generateStep().getNextCommand()) ;
			      		          //  dashToPoint.setPosition(destPoint) ;
			      		           // scmd = dynamic_cast<ServerCommand*>(dashToPoint.generateStep().getNextCommand()) ;
			      		turn_status = true ;
			      		cmdty="Turn around" ;

			      	}

			  	 break ;
		  }  // case 3

		  case 3 :
		  {

			  if ( ballView->getPosition().isKnown())
				       {          Point ball = ballView->getPosition().getPoint();
			 		  			dashToPoint.setPosition(ball);
			 		  			cmd = dashToPoint.generateStep().getNextCommand();
			 		  			scmd = dynamic_cast<ServerCommand*>(cmd);
			 		  			cmdty = "DASH_FORWARD_TO_BALL" ;
				       }

			 		  			break ;
		  } // case 4


		  case 4 :
		  {
			  // Point ball = ballView->getPosition().getPoint();
			  		//	dashToPoint.setPosition(ball);
			  	  scmd = new  DashCommand (50, -180) ;
			  			//cmd = dashToPoint.generateStep().getNextCommand();
			  			// scmd = dynamic_cast<ServerCommand*>(DC.generateStep().getNextCommand());
			  			cmdty = "DASH_BACKWARDFROM_BALL" ;

			  			break ;

		  } // case 5

		  case 2 :
		  {

			  if (ballView->getRelativeDirection().isKnown()) {
			  		// 	if (abs(ballView->getRelativeDirection().getDeg()) > DASH_MAX_ANGLE) {
			  				turnBodyToPoint.setPosition(ballView->getPosition().getPoint());
			  				cmd = turnBodyToPoint.generateStep().getNextCommand();
			  				scmd = dynamic_cast<ServerCommand*>(cmd);
			  				cmdty = "TURNBODYTOBALL" ;
			  			//																	}
			  	  	  	  	    	  	  	  	  	  	  	  	}

			  	  break ;
		  }

		  }


	gscmd = scmd ; gscmd2=scmd2 ;
	if(gscmd == 0 and gscmd2 == 0 ) {
		std::cout <<" in actio nselection both the commands are zero " ;
		RS_LOG(LA_AGENT," in actio nselection both the commands are zero " ) ; }


	RS_LOG(LA_AGENT, "Uno and its PASSM maping "<< Uno<<" "<< MapPassToUno[Uno]) ;
//	switch(MapPassToUno[Uno])
//		           {
//		           case 1:  	  { gscmd_1 = gscmd ; gscmd2_1 = gscmd2 ;  RS_LOG(LA_AGENT, "action for PASS1 activated" );
//		           if( gscmd_1 ==0 and gscmd2_1 == 0 )   { RS_LOG(LA_AGENT, "case 1 commands are null" ) ;  }break ;}
//		           case 2:       {  gscmd_2 = gscmd ; gscmd2_2 = gscmd2 ;  RS_LOG(LA_AGENT, "action for PASS2 activated" ) ;
//		           if( gscmd_2 ==0 and gscmd2_2 == 0 )   { RS_LOG(LA_AGENT, "case 2 commands are null" ) ;  }break ; }
//		           case 3:        { gscmd_3 = gscmd ; gscmd2_3 = gscmd2 ;  RS_LOG(LA_AGENT, "action for PASS3 activated" ) ;
//		           if( gscmd_3 ==0 and gscmd2_3 == 0 )   { RS_LOG(LA_AGENT, "case 3 commands are null" ) ;  }break ;}
//		           case 4: 			{ gscmd_4 = gscmd ; gscmd2_4 = gscmd2 ; RS_LOG(LA_AGENT, "action for PASS4 activated" ) ;
//		           if( gscmd_4 ==0 and gscmd2_4 == 0 )   { RS_LOG(LA_AGENT, "case 1 commands are null" ) ;  }break ;}
//		           }

}

//const std::vector<PlayerObject>& opps_wm   = wm.getOpponents();
 //const std::vector<PlayerObject>& team_wm =  wm.getTeammates() ;
// const std::vector<PlayerObject>& opps_pv =  playerView->getOpponents(0);

float minballdist = 105 ; int minballdistUno = 0  ;
//void FCFooDecision::getPlayerInfo( const std::vector<PlayerObject>& opps_wm, const std::vector<PlayerObject>& team_wm,
//		const std::vector<PlayerObject>&  opps_pv,WorldModel&  wm ,WorldModelInterface& wmi, AgentView agentView,
//		BallView ballView, PlayerView playerView, float *rec_theta1  , float *rec_theta2 )
void FCFooDecision::getPlayerInfo(WorldModel& wm ,WorldModelInterface* wmi, AgentView* agentView, BallView* ballView
		, PlayerView* playerView,  float  rec_theta1[]  , float  rec_theta2[], float rec_ratio1[], float rec_ratio2[])
{

	std::cout<<"\n in  predicted getplayer info" ;
    RS_LOG(LA_AGENT, "\n in  predicted getplayer info") ;
   minballdist = 105 ; minballdistUno=0 ;
     for ( int i =1; i <=11; i++)
     {
    	 rec_theta1[i] = -1000000 ;
    	 rec_theta2[i] = -1000000 ;
    	 rec_ratio1[i] = -1000000 ;
    	 rec_ratio2[i] = -1000000 ;

     }
	  std::vector<PlayerObject> opps_wm =  wm.getOpponents() ;
	  std::vector<PlayerObject>	 team_wm =  wm.getTeammates() ;
	  std::vector<PlayerObject>    opps_pv =  playerView->getOpponents(0);
	  PlayerObject opps[11] , teamm[11] , opps_p[11] ;

	std::cout << "\n player view opponents \n" ;
	RS_LOG(LA_AGENT,"\n player view opponents \n"  ) ;

	  int Pindex=0 ;
	  for ( std::vector<PlayerObject>::const_iterator i = opps_pv.begin();
	   	   							i != opps_pv.end(); ++i )
	   	   						{
		  	  	  	  	  	  	  	  	  	  if (i->getUniformNumber().isKnown())
		   	   											{   int Uno = 0 ;
		   	   										   Uno =  i->getUniformNumber().getValue()  ;
		   	   														if (Uno > 11) { std::cout<<" Uno >11" ; exit(0); }
		   	   														std::cout<<" uniform number " << i->getUniformNumber() << "\n" ;
		   	   														RS_LOG(LA_AGENT," uniform number " << i->getUniformNumber() << "\n" ) ;
		   	   	                            //opps1.remove(&Uno) ;
		   	   	                            //opps1.insert(Uno, i) ;
		   	   								//opps2[Uno] = dynamic_cast<PlayerObject>(i) ;
		   	   														opps_p[Uno] =  opps_pv.at(Pindex) ; Pindex++ ;
		   	   											}  // if uniform

	   	   						}

	  std::cout<< "\n world model opponents \n" ;
	  RS_LOG(LA_AGENT, "\n world model opponents \n") ;
	 	    Pindex =0 ; // int Uno=0 ;
	 	   	for ( std::vector<PlayerObject>::const_iterator i = opps_wm.begin();
	 	   							i != opps_wm.end(); ++i )
	 	   						{

	 	   									if (i->getUniformNumber().isKnown())
	 	   											{   int Uno = 0 ;
	 	   										   Uno =  i->getUniformNumber().getValue()  ;
	 	   														if (Uno > 11) {std::cout<<"exit UNo>11" ; exit(0); }
	 	   														std::cout<<" uniform number " << i->getUniformNumber() << "\n" ;
	 	   														RS_LOG(LA_AGENT," uniform number " << i->getUniformNumber() << "\n" ) ;
	 	   	                            //opps1.remove(&Uno) ;
	 	   	                            //opps1.insert(Uno, i) ;
	 	   								//opps2[Uno] = dynamic_cast<PlayerObject>(i) ;
	 	   														opps[Uno] =  opps_wm.at(Pindex) ; Pindex++ ;
	 	   											}  // if uniform
	 	   									if( i->getPosition().isKnown())
	 	   											{ std::cout<<"x and y pos" <<i->getPosition().getX().getValue()<<"  " <<i->getPosition().getY().getValue()<<"\n"  ;
	 	   											   RS_LOG(LA_AGENT, "x and y pos" <<i->getPosition().getX().getValue()<<"  " <<i->getPosition().getY().getValue()<<"\n") ;}
	 	   									if (i->getNeckDirection().isKnown())
	 	   											{ std::cout<<"neck direction " << i->getNeckDirection().getDeg()<<"\n" ;
	 	   											RS_LOG(LA_AGENT,"neck direction " << i->getNeckDirection().getDeg()<<"\n" ) ;}
	 	   									if( i->getBodyDirection().isKnown()) {
	 	   											std::cout<<"body direction "<<i->getBodyDirection().getDeg()<<"\n" ;
	 	   									RS_LOG(LA_AGENT, "body direction "<<i->getBodyDirection().getDeg()<<"\n" ) ;}

	 	   									if( i->getPointDirection().isKnown() )
	 	   											{ std::cout<<"point direction " <<i->getPointDirection().getDeg()<<"\n" ;
	 	   									 RS_LOG(LA_AGENT, "point direction " <<i->getPointDirection().getDeg()<<"\n") ;}



	 	   						} // for

	 	   				// if ( opps_pv.size() > opps_wm.size() ) {   opps = opps_p ; }
	 	   	std::cout<<"\n # of  oppn_wm opp_pv teammates "<< opps_wm.size()<<" "<<opps_pv.size()<<" "<<team_wm.size() ;
	 	   	RS_LOG(LA_AGENT, "\n # of  oppn_wm opp_pv teammates "<< opps_wm.size()<<" "<<opps_pv.size()<<" "<<team_wm.size()) ;
	 	   //	std::cout<<"\n \n team mates \n # of teammates"<<opps_pv.size() ;


	 // bool amIClosest =false ;
	 float ball_dist[11] ;

	 for(int i=0 ; i<11 ; i++)  {ball_dist[i] = 1000 ; }
	 	   	std::cout<<"\n team mates \n " ;
	 	   	RS_LOG(LA_AGENT, "\n team mates \n ") ;
	                                  Pindex=0 ;
	 		for ( std::vector<PlayerObject>::const_iterator i = team_wm.begin();
	 	 	   							i != team_wm.end(); ++i )

	 		{
	 										int Uno = 0 ;
	 											if (i->getUniformNumber().isKnown())
	 			 	   											{
	 			 	   										   Uno =  i->getUniformNumber().getValue()  ;
	 			 	   														if (Uno > 11) {std::cout<<"exiting uno > 11" ;
	 			 	   														  RS_LOG(LA_AGENT,"exiting uno > 11" ) ; exit(0); }
	 			 	   														std::cout<<" uniform number " << i->getUniformNumber() << "\n" ;
	 			 	   														RS_LOG(LA_AGENT," uniform number " << i->getUniformNumber() << "\n" ) ;
	 			 	   	                            //opps1.remove(&Uno) ;
	 			 	   	                            //opps1.insert(Uno, i) ;
	 			 	   								//opps2[Uno] = dynamic_cast<PlayerObject>(i) ;
	 			 	   														teamm[Uno] =  team_wm.at(Pindex) ; Pindex++ ;
	 			 	   											}  // if uniform

	 											double mindist = 105  , mindistang = 359, minang =359,minangdist=105 ,minang2=359,minangdist2=109, dist=0 , ang1= 0, recoppdist=0,
	 													mindist_ratio, minangdist2_ratio, minangdist_ratio ;
	 											if( i->getPosition().isKnown())
	 											{ std::cout<<"x and y pos" <<i->getPosition().getX().getValue()<<"  "
	 												<<i->getPosition().getY().getValue()<<"\n"  ;
	 											RS_LOG(LA_AGENT,"x and y pos" <<i->getPosition().getX().getValue()<<"  "
	 												<<i->getPosition().getY().getValue()<<"\n" ) ;

	 											  if(ballView->getPosition().isKnown()){
	 											        ball_dist[Uno] = ballView->getPosition().getPoint().getDistanceTo(i->getPosition().getPoint()) ;
	 											        if (minballdist > ball_dist[Uno]) { minballdist = ball_dist[Uno] ; minballdistUno = Uno ; }
	 											  }
	 												AngleDeg recdir =  AngleDeg(agentView->getPosition().getDirectionTo(i->getPosition()).getValue() ) ;

	 												double recdist = agentView->getPosition().getDistanceTo(i->getPosition()).getValue();
	 												std::cout<<"\n recdist"<<recdist;
	 												RS_LOG(LA_AGENT, "\n recdist"<<recdist) ;

	 												if (opps_pv.size() >  opps_wm.size())
	 												{
	 													for (int ind2= 0 ; ind2<11; ind2++)
	 													{

	 														if  ( opps_p[ind2].getPosition().isKnown() )
	 													  {   dist = agentView->getPosition().getDistanceTo( opps_p[ind2].getPosition()).getValue() ;
	 													     ang1 = abs( AngleDeg(agentView->getPosition().getDirectionTo(opps_p[ind2].getPosition()).getValue()).getDeg()
	 													    		 - recdir.getDeg() ) ;
	 													     recoppdist = i->getPosition().getDistanceTo(opps_p[ind2].getPosition()).getValue() ;
	 													     if(mindist >= dist) { mindist = dist ; mindistang = ang1 ;mindist_ratio =  dist/recdist ;}

	 													    if(minang2 >= ang1 and recoppdist -dist >= -3 ) { minang2 = ang1 ; minangdist2 = dist ;  minangdist2_ratio = dist/recdist ;}

	 													    if(minang >= ang1 and ( recoppdist - dist  >= -3  or ( recoppdist <= 15 and dist <= 15 ) )
	 													    		 and ( dist - recdist  <= 3 or ( dist <= 15 and recdist <= 15 ) )
	 													    		 ) { minang = ang1 ; minangdist = dist ; minangdist_ratio = dist/recdist ;}
	 													     std::cout<<"\n loop "<<ind2<<" dist and ang1 "<<dist<<" "<<ang1<<" "<<recoppdist<<" \n " ;
	 													     RS_LOG(LA_AGENT, "\n loop "<<ind2<<" dist and ang1 "<<dist<<" "<<ang1<<" "<<recoppdist<<" \n " ) ;
	 													   } // if opp pos
	 													  } // for

	 												} // if opps size
	 												else
	 												{

	 													for (int ind2= 0 ; ind2<11; ind2++)
	 													{

	 														if  ( opps[ind2].getPosition().isKnown() )
	 													  {   dist = agentView->getPosition().getDistanceTo( opps[ind2].getPosition()).getValue() ;

	 													     ang1 = abs(
	 													   AngleDeg(agentView->getPosition().getDirectionTo(opps[ind2].getPosition()).getValue()).getDeg()
	 													    		 - recdir.getDeg() ) ;
	 													     if (ang1 > 180 ) { ang1 = 360-ang1 ;}
	 													     recoppdist = i->getPosition().getDistanceTo(opps[ind2].getPosition()).getValue() ;
	 													     if(mindist >= dist) { mindist = dist ; mindistang = ang1 ; mindist_ratio =  dist/recdist ;}
	 													    if(minang2 >= ang1 and recoppdist  - dist >= -3 ) { minang2 = ang1 ; minangdist2 = dist ;  minangdist2_ratio = dist/recdist ;}


	 													     if(minang >= ang1 and
	 													    		 (recoppdist  - dist >= -3  or ( recoppdist <= 15 and dist <= 15 ))
	 													     	 	 and
	 													    		 ( dist - recdist <= 3 or ( dist <= 15 and recdist <= 15 ) )
	 													    		 ) { minang = ang1 ; minangdist = dist ; minangdist_ratio = dist/recdist ;}

	 													    std::cout<<"\n loop "<<ind2<<" dist and ang1 "<<dist<<" "<<ang1<<" "<<recoppdist<<" \n " ;
	 													    RS_LOG(LA_AGENT,"\n loop "<<ind2<<" dist and ang1 "<<dist<<" "<<ang1<<" "<<recoppdist<<" \n " ) ;
	 													   } // if opp pos
	 													  } // for

	 												} // else
	 													} //if position

	 											//theta1 = min angle and agent opponentdist  < receiver oppponent dist  and agent opponent dist < reciever dist
	 											// theta1 > theta1_2 , then theta1 = theta1_2
	 												if ( minang > minang2 and minang < 180  )
	 												{ minang= minang2 ; minangdist = minangdist2 ; minangdist_ratio = minangdist2_ratio ; }
	 												else if ( 360 - minang > 360 - minang2  and minang > 180 )
	 												{ minang= minang2 ; minangdist = minangdist2 ;  minangdist_ratio = minangdist2_ratio ; }

	 												//if theta1 > 180 , display all parameters
	 											 if (minang >= 180 or mindistang >= 180 )
	 											 { std::cout<< "\n  mindist " << mindist << " mindistang "<<mindistang
	 												 <<" minang "<<minang <<" minangdist "<<minangdist << " dist " << dist<< " ang1 "<< ang1
	 												 <<" recoppdist "<< recoppdist ;
	 											 RS_LOG(LA_AGENT,"\n  mindist " << mindist << " mindistang "<<mindistang
	 												 <<" minang "<<minang <<" minangdist "<<minangdist << " dist " << dist<< " ang1 "<< ang1
	 												 <<" recoppdist "<< recoppdist ) ;


	 											 }

	 											 if (minang == 359)
	 											 {  minang= minang2 ; minangdist = minangdist2 ; minangdist_ratio = minangdist2_ratio ; }

	 											 // theta1 > 180 and theta2 < 180 , theta1 = theta2 .
	 										// 	 if ( minang >= 180 and mindistang < 180 and (360-minang) >= mindistang  )  { minang = mindistang ; }
	 											 	 	 rec_theta1[Uno] = minang ;
	 													rec_theta2[Uno] = mindistang ;
	 													rec_ratio1[Uno] = mindist_ratio ;
	 													rec_ratio2[Uno] = minangdist_ratio ;

	 			 	   									if (i->getNeckDirection().isKnown())
	 			 	   											{ std::cout<<"neck direction " << i->getNeckDirection().getDeg()<<"\n" ;
	 			 	   											RS_LOG(LA_AGENT, "neck direction " << i->getNeckDirection().getDeg()<<"\n") ;}
	 			 	   									if( i->getBodyDirection().isKnown()) {
	 			 	   											std::cout<<"body direction "<<i->getBodyDirection().getDeg()<<"\n" ;
	 			 	   									RS_LOG(LA_AGENT,"body direction "<<i->getBodyDirection().getDeg()<<"\n" ) ;}

	 			 	   									if( i->getPointDirection().isKnown() )
	 			 	   											{ std::cout<<"point direction " <<i->getPointDirection().getDeg()<<"\n" ;
	 			 	   											RS_LOG(LA_AGENT,"point direction " <<i->getPointDirection().getDeg()<<"\n" ) ;}

	 			 	   										std::cout<<"\n \n  theta1 and theta2 values "<<rec_theta1[Uno]<<" "<<rec_theta2[Uno] ;
	 			 	   										RS_LOG(LA_AGENT," \n \n  theta1 and theta2 values "<<rec_theta1[Uno]<<" "<<rec_theta2[Uno]) ;
	 		}



std::cout<<"\n out of predicted get player info" ;
RS_LOG(LA_AGENT, "\n out of predicted get player info") ;


}


void FCFooDecision::getPlayerInfo()
{

	std::cout<<"\n in regular   getplayer info" ;
	RS_LOG(LA_AGENT, "\n in regular   getplayer info") ;

   minballdist = 105 ; minballdistUno=0 ;

	  opps_wm =  wm.getOpponents() ;
	 	 team_wm =  wm.getTeammates() ;
	       opps_pv =  playerView->getOpponents(0);

	std::cout << "\n player view opponents \n" ;
	RS_LOG(LA_AGENT, "\n player view opponents \n") ;

	  int Pindex=0 ;
	  for ( std::vector<PlayerObject>::const_iterator i = opps_pv.begin();
	   	   							i != opps_pv.end(); ++i )
	   	   						{
		  	  	  	  	  	  	  	  	  	  if (i->getUniformNumber().isKnown())
		   	   											{   int Uno = 0 ;
		   	   										   Uno =  i->getUniformNumber().getValue()  ;
		   	   														if (Uno > 11) { std::cout<<"UNo > 11" ;
		   	   														  RS_LOG(LA_AGENT,"UNo > 11" );  exit(0); }
		   	   														std::cout<<" uniform number " << i->getUniformNumber() << "\n" ;
		   	   														RS_LOG(LA_AGENT, " uniform number " << i->getUniformNumber() << "\n") ;
		   	   	                            //opps1.remove(&Uno) ;
		   	   	                            //opps1.insert(Uno, i) ;
		   	   								//opps2[Uno] = dynamic_cast<PlayerObject>(i) ;
		   	   														opps_p[Uno] =  opps_pv.at(Pindex) ; Pindex++ ;
		   	   											}  // if uniform

	   	   						}

	  std::cout<< "\n world model opponents \n" ;
	 	    Pindex =0 ; // int Uno=0 ;
	 	   	for ( std::vector<PlayerObject>::const_iterator i = opps_wm.begin();
	 	   							i != opps_wm.end(); ++i )
	 	   						{

	 	   									if (i->getUniformNumber().isKnown())
	 	   											{   int Uno = 0 ;
	 	   										   Uno =  i->getUniformNumber().getValue()  ;
	 	   														if (Uno > 11) {exit(0); }
	 	   														std::cout<<" uniform number " << i->getUniformNumber() << "\n" ;
	 	   														RS_LOG(LA_AGENT, " uniform number " << i->getUniformNumber() << "\n") ;
	 	   	                            //opps1.remove(&Uno) ;
	 	   	                            //opps1.insert(Uno, i) ;
	 	   								//opps2[Uno] = dynamic_cast<PlayerObject>(i) ;
	 	   														opps[Uno] =  opps_wm.at(Pindex) ; Pindex++ ;
	 	   											}  // if uniform
	 	   									if( i->getPosition().isKnown())
	 	   											{ std::cout<<"x and y pos" <<i->getPosition().getX().getValue()<<"  " <<i->getPosition().getY().getValue()<<"\n"  ;
	 	   											 RS_LOG(LA_AGENT,"x and y pos" <<i->getPosition().getX().getValue()<<"  " <<i->getPosition().getY().getValue()<<"\n" ) ;}

	 	   									if (i->getNeckDirection().isKnown())
	 	   											{ std::cout<<"neck direction " << i->getNeckDirection().getDeg()<<"\n" ;
	 	   											RS_LOG(LA_AGENT,"neck direction " << i->getNeckDirection().getDeg()<<"\n"  ) ;}
	 	   									if( i->getBodyDirection().isKnown()) {
	 	   											std::cout<<"body direction "<<i->getBodyDirection().getDeg()<<"\n" ;
	 	   									 RS_LOG(LA_AGENT,"body direction "<<i->getBodyDirection().getDeg()<<"\n" ) ;}

	 	   									if( i->getPointDirection().isKnown() )
	 	   											{ std::cout<<"point direction " <<i->getPointDirection().getDeg()<<"\n" ;
	 	   											 RS_LOG(LA_AGENT,"point direction " <<i->getPointDirection().getDeg()<<"\n" ) ;}



	 	   						} // for

	 	   				// if ( opps_pv.size() > opps_wm.size() ) {   opps = opps_p ; }
	 	   	std::cout<<"\n # of  oppn_wm opp_pv teammates "<< opps_wm.size()<<" "<<opps_pv.size()<<" "<<team_wm.size() ;
	 	   	RS_LOG(LA_AGENT, "\n # of  oppn_wm opp_pv teammates "<< opps_wm.size()<<" "<<opps_pv.size()<<" "<<team_wm.size()) ;
	 	   //	std::cout<<"\n \n team mates \n # of teammates"<<opps_pv.size() ;


	 // bool amIClosest =false ;
	 float ball_dist[11] ;
	 	   	std::cout<<"\n team mates \n " ;
	 	   	RS_LOG(LA_AGENT, "\n team mates \n ") ;
	                                  Pindex=0 ;
	 		for ( std::vector<PlayerObject>::const_iterator i = team_wm.begin();
	 	 	   							i != team_wm.end(); ++i )

	 		{
	 										int Uno = 0 ;
	 											if (i->getUniformNumber().isKnown())
	 			 	   											{
	 			 	   										   Uno =  i->getUniformNumber().getValue()  ;
	 			 	   														if (Uno > 11) {exit(0); }
	 			 	   														std::cout<<" uniform number " << i->getUniformNumber() << "\n" ;
	 			 	   														RS_LOG(LA_AGENT," uniform number " << i->getUniformNumber() << "\n"  ) ;
	 			 	   	                            //opps1.remove(&Uno) ;
	 			 	   	                            //opps1.insert(Uno, i) ;
	 			 	   								//opps2[Uno] = dynamic_cast<PlayerObject>(i) ;
	 			 	   														teamm[Uno] =  team_wm.at(Pindex) ; Pindex++ ;
	 			 	   											}  // if uniform

	 											double mindist = 105  , mindistang = 359, minang =359,minangdist=105 ,minang2=359,minangdist2=109, dist=0 , ang1= 0, recoppdist=0,
	 													mindist_ratio, minangdist2_ratio, minangdist_ratio ;
	 											if( i->getPosition().isKnown())
	 											{ std::cout<<"x and y pos" <<i->getPosition().getX().getValue()<<"  "
	 												<<i->getPosition().getY().getValue()<<"\n"  ;
	 											RS_LOG(LA_AGENT, "x and y pos" <<i->getPosition().getX().getValue()<<"  "
	 												<<i->getPosition().getY().getValue()<<"\n") ;
	 											        if(ballView->getPosition().isKnown()) {
	 											        ball_dist[Uno] = ballView->getPosition().getPoint().getDistanceTo(i->getPosition().getPoint()) ; }
	 											        if (minballdist > ball_dist[Uno]) { minballdist = ball_dist[Uno] ; minballdistUno = Uno ; }
	 												AngleDeg recdir =  AngleDeg(agentView->getPosition().getDirectionTo(i->getPosition()).getValue() ) ;

	 												double recdist = agentView->getPosition().getDistanceTo(i->getPosition()).getValue();
	 												std::cout<<"\n recdist"<<recdist;
	 												RS_LOG(LA_AGENT, "\n recdist"<<recdist) ;

	 												if (opps_pv.size() >  opps_wm.size())
	 												{
	 													for (int ind2= 0 ; ind2<11; ind2++)
	 													{

	 														if  ( opps_p[ind2].getPosition().isKnown() )
	 													  {   dist = agentView->getPosition().getDistanceTo( opps_p[ind2].getPosition()).getValue() ;
	 													     ang1 = abs( AngleDeg(agentView->getPosition().getDirectionTo(opps_p[ind2].getPosition()).getValue()).getDeg()
	 													    		 - recdir.getDeg() ) ;
	 													     recoppdist = i->getPosition().getDistanceTo(opps_p[ind2].getPosition()).getValue() ;
	 													     if(mindist >= dist) { mindist = dist ; mindistang = ang1 ;mindist_ratio =  dist/recdist ;}

	 													    if(minang2 >= ang1 and recoppdist -dist >= -3 ) { minang2 = ang1 ; minangdist2 = dist ;  minangdist2_ratio = dist/recdist ;}

	 													    if(minang >= ang1 and ( recoppdist - dist  >= -3  or ( recoppdist <= 15 and dist <= 15 ) )
	 													    		 and ( dist - recdist  <= 3 or ( dist <= 15 and recdist <= 15 ) )
	 													    		 ) { minang = ang1 ; minangdist = dist ; minangdist_ratio = dist/recdist ;}
	 													     std::cout<<"\n loop "<<ind2<<" dist and ang1 "<<dist<<" "<<ang1<<" "<<recoppdist<<" \n " ;
	 													     RS_LOG(LA_AGENT,"\n loop "<<ind2<<" dist and ang1 "<<dist<<" "<<ang1<<" "<<recoppdist<<" \n " ) ;
	 													   } // if opp pos
	 													  } // for

	 												} // if opps size
	 												else
	 												{

	 													for (int ind2= 0 ; ind2<11; ind2++)
	 													{

	 														if  ( opps[ind2].getPosition().isKnown() )
	 													  {   dist = agentView->getPosition().getDistanceTo( opps[ind2].getPosition()).getValue() ;

	 													     ang1 = abs(
	 													   AngleDeg(agentView->getPosition().getDirectionTo(opps[ind2].getPosition()).getValue()).getDeg()
	 													    		 - recdir.getDeg() ) ;
	 													     if (ang1 > 180 ) { ang1 = 360-ang1 ;}
	 													     recoppdist = i->getPosition().getDistanceTo(opps[ind2].getPosition()).getValue() ;
	 													     if(mindist >= dist) { mindist = dist ; mindistang = ang1 ; mindist_ratio =  dist/recdist ;}
	 													    if(minang2 >= ang1 and recoppdist  - dist >= -3 ) { minang2 = ang1 ; minangdist2 = dist ;  minangdist2_ratio = dist/recdist ;}


	 													     if(minang >= ang1 and
	 													    		 (recoppdist  - dist >= -3  or ( recoppdist <= 15 and dist <= 15 ))
	 													     	 	 and
	 													    		 ( dist - recdist <= 3 or ( dist <= 15 and recdist <= 15 ) )
	 													    		 ) { minang = ang1 ; minangdist = dist ; minangdist_ratio = dist/recdist ;}

	 													    std::cout<<"\n loop "<<ind2<<" dist and ang1 "<<dist<<" "<<ang1<<" "<<recoppdist<<" \n " ;
	 													    RS_LOG(LA_AGENT, "\n loop "<<ind2<<" dist and ang1 "<<dist<<" "<<ang1<<" "<<recoppdist<<" \n ") ;
	 													   } // if opp pos
	 													  } // for

	 												} // else
	 													} //if position

	 											//theta1 = min angle and agent opponentdist  < receiver oppponent dist  and agent opponent dist < reciever dist
	 											// theta1 > theta1_2 , then theta1 = theta1_2
	 												if ( minang > minang2 and minang < 180  )
	 												{ minang= minang2 ; minangdist = minangdist2 ; minangdist_ratio = minangdist2_ratio ; }
	 												else if ( 360 - minang > 360 - minang2  and minang > 180 )
	 												{ minang= minang2 ; minangdist = minangdist2 ;  minangdist_ratio = minangdist2_ratio ; }

	 												//if theta1 > 180 , display all parameters
	 											 if (minang >= 180 or mindistang >= 180 )
	 											 { std::cout<< "\n  mindist " << mindist << " mindistang "<<mindistang
	 												 <<" minang "<<minang <<" minangdist "<<minangdist << " dist " << dist<< " ang1 "<< ang1
	 												 <<" recoppdist "<< recoppdist ;
	 											 RS_LOG(LA_AGENT, "\n  mindist " << mindist << " mindistang "<<mindistang
	 												 <<" minang "<<minang <<" minangdist "<<minangdist << " dist " << dist<< " ang1 "<< ang1
	 												 <<" recoppdist "<< recoppdist) ;


	 											 }

	 											 if (minang == 359)
	 											 {  minang= minang2 ; minangdist = minangdist2 ; minangdist_ratio = minangdist2_ratio ; }

	 											 // theta1 > 180 and theta2 < 180 , theta1 = theta2 .
	 										// 	 if ( minang >= 180 and mindistang < 180 and (360-minang) >= mindistang  )  { minang = mindistang ; }
	 											 	 	 rec_theta1[Uno] = minang ;
	 													rec_theta2[Uno] = mindistang ;
	 													rec_ratio1[Uno] = mindist_ratio ;
	 													rec_ratio2[Uno] = minangdist_ratio ;

	 			 	   									if (i->getNeckDirection().isKnown())
	 			 	   											{ std::cout<<"neck direction " << i->getNeckDirection().getDeg()<<"\n" ;
	 			 	   											RS_LOG(LA_AGENT, "neck direction " << i->getNeckDirection().getDeg()<<"\n") ;}
	 			 	   									if( i->getBodyDirection().isKnown()) {
	 			 	   											std::cout<<"body direction "<<i->getBodyDirection().getDeg()<<"\n" ;
	 			 	   									RS_LOG(LA_AGENT,"body direction "<<i->getBodyDirection().getDeg()<<"\n" ) ;}

	 			 	   									if( i->getPointDirection().isKnown() )
	 			 	   											{ std::cout<<"point direction " <<i->getPointDirection().getDeg()<<"\n" ;
	 			 	   											RS_LOG(LA_AGENT,"point direction " <<i->getPointDirection().getDeg()<<"\n" ) ;}

	 			 	   										std::cout<<"\n \n  theta1 and theta2 values "<<rec_theta1[Uno]<<" "<<rec_theta2[Uno] ;
	 			 	   										RS_LOG(LA_AGENT, "\n \n  theta1 and theta2 values "<<rec_theta1[Uno]<<" "<<rec_theta2[Uno] ) ;
	 		}

	 		 PointUE postemp ; postemp.makeUnknown() ;
	 		for (int i=0 ; i< 11 ; i++)
	 		{  if (teamm[i].getPosition().isKnown()) { RS_LOG(LA_AGENT, "\n the position is known  and observation time "
	 				<<i<<" "<<teamm[i].getObservationTime()) ;
	 		  if  (CURRTIME - teamm[i].getObservationTime().getT() > 30 ) {
	 			     teamm[i].setPosition(postemp) ;
	 		  }
	 		              } }

	 		for ( int i=0; i<11 ; i++)
	 		{
	 			if (teamm[i].getPosition().isKnown()) { RS_LOG(LA_AGENT, "\n the position is known  and observation time "
	 				 				<<i<<" "<<teamm[i].getObservationTime()) ; }
	 		}



std::cout<<"\n out of  regular get player info" ;
RS_LOG(LA_AGENT, "\n out of  regular get player info") ;


}
void FCFooDecision::initQtab()
{

	for (int i=0; i< nostates ; i++)
	{
		for (int j=0;j<noactionqtab;j++)
		{ Qtab[i][j] = 0 ; Qex[i][j] = false ; }
	}
}


void FCFooDecision::thetaCorrection()
 {

	std::cout<<"\n  in theta correction" ;
	RS_LOG(LA_AGENT, "\n  in theta correction") ;
	 for (int i=1; i<=11 ; i++)
	 {   if( rec_theta1[i] > 180 )  {rec_theta1[i] = 360 - rec_theta1[i] ; }
	      if (rec_theta2[i] > 180 ) { rec_theta2[i] = 360 - rec_theta2[i] ; }
	      rec_rtheta1[i] =   int( rec_theta1[i] / 10 ) ;
	      rec_rtheta2[i] = int( rec_theta2[i]/ 10 ) ;

	        if(rec_rtheta1[i] > 9) rec_rtheta1[i] = 9 ;
	        if(rec_rtheta2[i] > 9) rec_rtheta2[i] = 9 ;
	      rec_rratio1[i] = int(rec_ratio1[i]*3) ;
	      rec_rratio2[i]= int( rec_ratio2[i]*3) ;
	      if (rec_rratio1[i] > 3 ) rec_rratio1[i] = 3;
	      if( rec_rratio2[i] > 3 )  rec_rratio2[i] = 3 ;
	 }

std::cout<<"\n out of theta corr" ;
 }

void FCFooDecision::predThetaCorrection()
 {

	std::cout<<"\n in pred theta correctoin" ;
	RS_LOG(LA_AGENT,"\n in pred theta correctoin" ) ;
	 for (int i=1; i<=11 ; i++)
	 {   if( recp_theta1[i] > 180 )  {recp_theta1[i] = 360 - recp_theta1[i] ; }
	      if (recp_theta2[i] > 180 ) { recp_theta2[i] = 360 - recp_theta2[i] ; }
	      recp_rtheta1[i] =   int( recp_theta1[i] / 10 ) ;
	      recp_rtheta2[i] = int( recp_theta2[i]/ 10 ) ;

	      if (recp_rtheta1[i] > 9 ) { recp_rtheta1[i] = 9 ; }
	      if (recp_rtheta2[i] > 9 ) { recp_rtheta2[i] = 9 ; }

	      recp_rratio1[i] = int(recp_ratio1[i]*3) ;
	      recp_rratio2[i]= int( recp_ratio2[i]*3) ;
	      if (recp_rratio1[i] > 3 ) recp_rratio1[i] = 3;
	      if( recp_rratio2[i] > 3 )  recp_rratio2[i] = 3 ;
	 }

	 std::cout<<"\n out of pred theta " ;
	 RS_LOG(LA_AGENT, "\n out of pred theta ") ;

 }


//  std::cout<<"\n curr time "<< CURRTIME <<" PREV TIME "<<PREVTIME ;
  // Example of a simple decision maker using skills.
  // If the ball's position is known, the agent will run
  // To that position, and try to kick the ball towards the
  // opponents goal.

// initialise q table to Zero,
// action space  go forward , go backward , turn around anti clock wise , turn clock wise.
 // selection an action with max Q value .

int maxQvalactindex  ;
float maxQvalact = -10000 ;
// float Gamma = 0.2 ;

bool greedy = true ;
int PrevAction ;

struct cmd_rec {

	int command_type  ;
	int player_Uno ;
	int rec_Uno ;
	int theta1 ;
	int theta2 ;
	int ratio1 ;
	int ratio2 ;
	float theta1val ;
	float theta2val ;
	bool Q_status  ;
    float kick_absangle ;
   Point  kick_pos ;
   Point rec_pos ;
   Vector ballSpeedVector ;
   UInt  time ;

}   ;

cmd_rec  cmdr[100000] ; int cmdrind=0 ;int last_kickind = -1 ;
float alph = 0.4 ; float gamma = 0.3 ; int lastkickprocess=0 , lastactprocess=0 ;
// bool lastkick_updatestatus  = false ;

void FCFooDecision::qvalUpdate()
{
       if (cmdrind<1) return ;

       if(last_kickind >= 0 ){
	std::cout<<"\n in QVALUPDATE " ;
	RS_LOG(LA_AGENT,"\n in QVALUPDATE " ) ;
	if (ballView->getPosition().isKnown() == false   )
		{std::cout<< "\n unable to find ball" ; RS_LOG(LA_AGENT, "\n unable to find ball" ) ; return ;}

	 Point ball_pos1 ; State st1(1) ; st1.x  = new double[4];

	if( ballView->getPosition().isKnown()) {
	 ball_pos1 = ballView->getPosition().getPoint() ;
	 RS_LOG(LA_AGENT, "rec postion dist to ball "<<cmdr[last_kickind].rec_pos.getDistanceTo(ball_pos1) ) ;
	 RS_LOG(LA_AGENT, "KICK POS DIRECTIN TO BALL "<< cmdr[last_kickind].kick_pos.getDirectionTo(ball_pos1).getDeg()) ;
	 RS_LOG(LA_AGENT, "cmdr kickabs angle "<<cmdr[last_kickind].kick_absangle) ;
	 				RS_LOG(LA_AGENT, " cmdr ball speed vector ange "<<cmdr[last_kickind].ballSpeedVector.getAngle()) ;
	}
	else { return ;}

	PlayerObject oppnear( wm.getOpponentClosestToBall()) ;




				if (ballView->getSpeedVector().isKnown()) {
				RS_LOG(LA_AGENT, "ball speed vector current" << ballView->getSpeedVector().getVector().getAngle()) ;
								} else return ;

	if( oppnear.getPosition().isKnown() == false )
				{ std::cout<<"\n opponent position that is nearest to balll is not known" ;
				RS_LOG(LA_AGENT, "\n opponent position that is nearest to balll is not known") ;
				}
	// check if the reward from last passing kick effort was updated to Q table, if its false then go further
	RS_LOG(LA_AGENT, "LAST KICK IND "<<last_kickind<<" status "<< cmdr[last_kickind].Q_status) ;
	if ( last_kickind - lastkickprocess > 1 and lastkickprocess != 0)
		RS_LOG(LA_AGENT, "THE KICK IND MISSED lastkickind , lastkickind- lastkickprocess"<<last_kickind<<" "<<(last_kickind -lastkickprocess)) ;
	if(cmdr[last_kickind].Q_status == false and last_kickind != -1 )
	{

		//  if the receiver is with in the ball kickable margin , that implies ball is received by the receiver and hence reward of 10
		 // to the state and action pair that resulted the state where Kick was possible
		// changed from team_wm to teamm

	//	if(teamm[cmdr[last_kickind].rec_Uno].getPosition().isKnown() == false )
	//		std::cout<<"\n unable to know position of last kick reciever " ;
	//	    RS_LOG(LA_AGENT, "unable to know position of last kick reciever ") ;

		//if (teamm[cmdr[last_kickind].rec_Uno].getPosition().getPoint().getDistanceTo(ball_pos1) <= facts->SP_kickable_margin )
		 RS_LOG(LA_AGENT,"last rec pos away from ball_pos"<<cmdr[last_kickind].rec_pos.getDistanceTo(ball_pos1) ) ;
		  if (cmdr[last_kickind].rec_pos.getDistanceTo(ball_pos1) <= facts->SP_kickable_margin)
		 		 	{  Qtab[ cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*noratio2 +cmdr[last_kickind].ratio2 ][4] =
		 		 	  (1-alph) * Qtab[cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*noratio2 +cmdr[last_kickind].ratio2][4] +
		 		 	  alph*( 10 ) ;

		 		 						Qex[cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*noratio2 +cmdr[last_kickind].ratio2][4]
		 		 						                       = true ;

		 		 						st1.x[0] = cmdr[last_kickind].theta1 ;
		 		 	 		 		 	st1.x[1] = cmdr[last_kickind].theta2 ;
		 		 	 		 		 	st1.x[2] = cmdr[last_kickind].ratio1 ;
		 		 	 		 		 	st1.x[3] = cmdr[last_kickind].ratio2 ;
		 		 	 		 		const double tar = double (Qtab[ cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*noratio2 +cmdr[last_kickind].ratio2 ][4]) ;
		 		 	 		 		RS_LOG(LA_AGENT, "learning called") ;
		 		 	 		 		 cma5.decayTraces(DECAYFACTOR) ;
		 		 	 		 		cma5.accumulateTraces(st1, 1.0) ;
		 		 	 		 		cma5.learn(st1, tar ) ;
		 		 	RS_LOG(LA_AGENT, "SUCCESSFUL PASS") ;
		 		 	if (cmdr[last_kickind].command_type !=5) { RS_LOG(LA_AGENT,"command type mismatch in kick qtab process ") ; exit(0) ;}
		 		 	updateQInf(AGENUNO, CURRTIME,cmdr[last_kickind].theta1, cmdr[last_kickind].theta2,cmdr[last_kickind].ratio1, cmdr[last_kickind].ratio2,cmdr[last_kickind].command_type,
		 		 			Qtab[ cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*noratio2 +cmdr[last_kickind].ratio2 ][4] ) ;
		 		 	cmdr[last_kickind].Q_status = true ;
		 		 	lastkickprocess = last_kickind ;
		 		 	}

		  else 	if (oppnear.getPosition().isKnown() )
				// and  teamm[cmdr[last_kickind].rec_Uno].getPosition().isKnown() == true  )
		{

			// if theres an opponent closer to ball than the intended reciever and if it can kick the ball ,
					// if the direction of the ball vector  is not same then negative reward.

					// if (teamm[cmdr[last_kickind].rec_Uno].getPosition().isKnown() == false)
					//	{ std::cout<<"\nlast kick reciver is not known" ; RS_LOG(LA_AGENT, "\nlast kick reciver is not known") ;  }


			RS_LOG(LA_AGENT, "opponet closest to ball dist "<< oppnear.getPosition().getPoint().getDistanceTo(ball_pos1) ) ;

		if ( (oppnear.getPosition().getPoint().getDistanceTo(ball_pos1) <= (facts->SP_kickable_margin +2) )  and
				 // (  teamm[cmdr[last_kickind].rec_Uno].getPosition().getPoint().getDistanceTo(ball_pos1) >= facts->SP_kickable_margin )
				( cmdr[last_kickind].rec_pos.getDistanceTo(ball_pos1) >= ( facts->SP_kickable_margin+2) )
				and  (  (cmdr[last_kickind].kick_pos.getDirectionTo(ball_pos1).getDeg() !=  cmdr[last_kickind].kick_absangle)
						or (cmdr[last_kickind].ballSpeedVector.getAngle() != ballView->getSpeedVector().getVector().getAngle()) ) )
		{
			if (cmdr[last_kickind].command_type !=5) { RS_LOG(LA_AGENT,"command type mismatch in kick qtab process ") ; exit(0) ;}

			Qtab[cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*noratio2 +cmdr[last_kickind].ratio2][4] =
		 (1-alph) * Qtab[cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*4 +cmdr[last_kickind].ratio2][4] +
					 		 	  alph*( -10 ) ;

					Qex[cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*noratio2 +cmdr[last_kickind].ratio2 ][4]
					                                                                                                                                                                       = true ;
			st1.x[0] = cmdr[last_kickind].theta1 ;
					 		 	 		 		 	st1.x[1] = cmdr[last_kickind].theta2 ;
					 		 	 		 		 	st1.x[2] = cmdr[last_kickind].ratio1 ;
					 		 	 		 		 	st1.x[3] = cmdr[last_kickind].ratio2 ;
					 		 	 		 		const double tar = double (Qtab[ cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*noratio2 +cmdr[last_kickind].ratio2 ][4]) ;
					 		 	 		 		RS_LOG(LA_AGENT, "learning called") ;
					 		 	 		 	cma5.decayTraces(DECAYFACTOR) ;
					 		 	 		cma5.accumulateTraces(st1, 1.0) ;
					 		 	 		 		cma5.learn(st1, tar ) ;
			updateQInf(AGENUNO, CURRTIME,cmdr[last_kickind].theta1, cmdr[last_kickind].theta2,cmdr[last_kickind].ratio1, cmdr[last_kickind].ratio2,cmdr[last_kickind].command_type,
					 		 			Qtab[ cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*noratio2 +cmdr[last_kickind].ratio2 ][4] ) ;
			RS_LOG(LA_AGENT, "UNSUCCESSFUL PASS") ;  cmdr[last_kickind].Q_status = true ; lastkickprocess = last_kickind ;
		}  // if oppnear.getpostion.getpoint
		else  if (ballView->getSpeedVector().isKnown()) {

			if (  (cmdr[last_kickind].kick_pos.getDirectionTo(ball_pos1).getDeg() -  cmdr[last_kickind].kick_absangle  < 10)
				 and  (cmdr[last_kickind].ballSpeedVector.getAngle() - ballView->getSpeedVector().getVector().getAngle() < 10))
		{
				// exit if the command type kick mismatches to type 5
				if (cmdr[last_kickind].command_type !=5) { RS_LOG(LA_AGENT,"command type mismatch in kick qtab process ") ; exit(0) ;}

				Qtab[ cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*4 +cmdr[last_kickind].ratio2 ][4] =
	 		 	  (1-alph) * Qtab[cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*noratio2 +cmdr[last_kickind].ratio2][4] +
	 		 	  alph*( 10 ) ;
		updateQInf(AGENUNO, CURRTIME,cmdr[last_kickind].theta1, cmdr[last_kickind].theta2,cmdr[last_kickind].ratio1, cmdr[last_kickind].ratio2,cmdr[last_kickind].command_type,
				 		 			Qtab[ cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*noratio2 +cmdr[last_kickind].ratio2 ][4] ) ;
		cmdr[last_kickind].Q_status = true ;  RS_LOG(LA_AGENT, "SUCCESSFUL PASS"); lastkickprocess = last_kickind ;

				Qex[cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*noratio2 +cmdr[last_kickind].ratio2 ][4]
				                                                                                                                                                                       = true ;
												st1.x[0] = cmdr[last_kickind].theta1 ;
				 		 	 		 		 	st1.x[1] = cmdr[last_kickind].theta2 ;
				 		 	 		 		 	st1.x[2] = cmdr[last_kickind].ratio1 ;
				 		 	 		 		 	st1.x[3] = cmdr[last_kickind].ratio2 ;
				 		 	 		 		const double tar = double (Qtab[ cmdr[last_kickind].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind].theta2*noratio1*noratio2+cmdr[last_kickind].ratio1*noratio2 +cmdr[last_kickind].ratio2 ][4]) ;
				 		 	 		 		RS_LOG(LA_AGENT, "learning called") ;
				 		 	 		 	cma5.decayTraces(DECAYFACTOR) ;
				 		 	 		  cma5.accumulateTraces(st1, 1.0) ;
				 		 	 		 		cma5.learn(st1, tar ) ;

		} // if cmdr last_kickind.kicpos.getdirectionTOballpos1getdeg

		} // if ball view speed vector

		}   // else if opposition position is known

	}  // if(cmdr[last_kickind].Q_status == false and last_kickind != 10001 )

	// malicious code found this is duplicate

	/*if (  (cmdr[last_kickind].kick_pos.getDirectionTo(ball_pos1).getDeg() -  cmdr[last_kickind].kick_absangle  < 10)
					 and  (cmdr[last_kickind].ballSpeedVector.getAngle() - ballView->getSpeedVector().getVector().getAngle() < 10 )
					  and cmdr[last_kickind].Q_status == false )
			{          Qtab[ cmdr[last_kickind-1].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind-1].theta2*noratio1*noratio2+cmdr[last_kickind-1].ratio1*4 +cmdr[last_kickind-1].ratio2 ][cmdr[last_kickind-1].command_type-1] =
		 		 	  (1-alph) * Qtab[cmdr[last_kickind-1].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind-1].theta2*noratio1*noratio2+cmdr[last_kickind-1].ratio1*noratio2 +cmdr[last_kickind-1].ratio2][cmdr[last_kickind-1].command_type-1] +
		 		 	  alph*( 10 ) ;   cmdr[last_kickind].Q_status = true ;  RS_LOG(LA_AGENT, "SUCCESSFUL PASS") ;
			updateQInf(AGENUNO, CURRTIME,cmdr[last_kickind-1].theta1, cmdr[last_kickind-1].theta2,cmdr[last_kickind-1].ratio1, cmdr[last_kickind-1].ratio2,cmdr[last_kickind-1].command_type,
							 		 			Qtab[ cmdr[last_kickind-1].theta1*notheta2*noratio1*noratio2 + cmdr[last_kickind-1].theta2*noratio1*noratio2+cmdr[last_kickind-1].ratio1*noratio2 +cmdr[last_kickind-1].ratio2 ][cmdr[last_kickind-1].command_type-1] ) ;
			}
*/
	//  duplicate code

} // if last kickind >=0
		// update the Q status of the last action
       if( (rec_theta1[cmdr[cmdrind-1].rec_Uno]	- cmdr[cmdrind-1].theta1val == 0 ) and (rec_theta2[cmdr[cmdrind-1].rec_Uno]- cmdr[cmdrind-1].theta1val == 0 ) )
       { lastactprocess = cmdrind-1 ; return ;}

	 if(cmdrind- lastactprocess > 1 and lastactprocess !=0 )
		 RS_LOG(LA_AGENT, "LAST ACTION PROCESSING MISSED : cmdrind , cmdrind-lastactprocess  "<< cmdrind<<" "<<(cmdrind- lastactprocess)) ;

	 if (cmdr[cmdrind-1].Q_status == false and cmdrind >=1 and cmdr[cmdrind-1].command_type != 5 and  cmdr[cmdrind-1].command_type != 0)
		{

			RS_LOG(LA_AGENT, "in the if of last action q status processing ") ;
			float state_out_Qval = -100000.0 ;

			// get the max Q value from output state after executing action .  Q(s,a) = R +  arg 'a1' max (Q(s',a1))
			for (int i=0; i<noactionqtab ; i++)
			{

				if (Qex[rec_rtheta1[cmdr[cmdrind-1].rec_Uno]*notheta2*noratio1*noratio2 + rec_rtheta2[cmdr[cmdrind-1].rec_Uno]*noratio1*noratio2 + rec_rratio1[cmdr[cmdrind-1].rec_Uno]*noratio2 +
						      rec_rratio2[cmdr[cmdrind-1].rec_Uno]][i] == true )
				{
				if (
						// Qtab[cmdr[cmdrind].theta1*18*16 + cmdr[cmdrind].theta1*16 + cmdr[cmdrind].ratio1*4 + cmdr[cmdrind].ratio2*4 ][i] > state_out_Qval
						Qtab[ rec_rtheta1[cmdr[cmdrind-1].rec_Uno]*notheta2*noratio1*noratio2 + rec_rtheta2[cmdr[cmdrind-1].rec_Uno]*noratio1*noratio2 + rec_rratio1[cmdr[cmdrind-1].rec_Uno]*noratio2 +
						      rec_rratio2[cmdr[cmdrind-1].rec_Uno]][i] > state_out_Qval)
				{	// state_out_Qval = Qtab[cmdr[cmdrind].theta1*18*16 + cmdr[cmdrind].theta1*16 + cmdr[cmdrind].ratio1*4 + cmdr[cmdrind].ratio2 ][i] ;
					state_out_Qval = Qtab[ rec_rtheta1[cmdr[cmdrind-1].rec_Uno]*notheta2*noratio1*noratio2 + rec_rtheta2[cmdr[cmdrind-1].rec_Uno]*noratio1*noratio2 + rec_rratio1[cmdr[cmdrind-1].rec_Uno]*noratio2 +
										      rec_rratio2[cmdr[cmdrind-1].rec_Uno]][i] ;
					// lastactprocess = cmdrind ;

				} // if
				} else
				{

					State st(1) ;  st.x = new double[4] ; double outp1 ;
					st.x[0] =  rec_rtheta1[cmdr[cmdrind-1].rec_Uno] ;
					st.x[1] =  rec_rtheta2[cmdr[cmdrind-1].rec_Uno] ;
					st.x[2] =  rec_rratio1[cmdr[cmdrind-1].rec_Uno] ;
					st.x[3] =  rec_rratio2[cmdr[cmdrind-1].rec_Uno] ;
					 std::cout<<" state info before cmac is called "<<st.x[0]<<" "<<st.x[1]<<" "<<st.x[2]<<" "<<st.x[3] ;
					switch (i+1)
					{
					case 1: {  RS_LOG(LA_AGENT, "predict called case 1") ;  cma1.predict(st, outp1 ) ;break  ;}
					case 2: { RS_LOG(LA_AGENT, "predict called case 2 ") ;cma2.predict(st, outp1 ) ;break  ;}
					case 3: { RS_LOG(LA_AGENT, "predict called case 3 ") ;cma3.predict(st, outp1 ) ;break  ;}
					case 4: { RS_LOG(LA_AGENT, "predict called case 4 ") ;cma4.predict(st, outp1 ) ;break  ;}
					}

					if (outp1 > state_out_Qval ) { state_out_Qval = outp1 ; }

				}
			} // for int i =0



			float thetaincent = 0; // incentive from theta increase
		//	 if (cmdr[cmdrind-1].theta1val != 0 and cmdr[cmdrind-1].theta2val != 0)
		//	{

				thetaincent = (( rec_theta1[cmdr[cmdrind-1].rec_Uno]	- cmdr[cmdrind-1].theta1val)/90.0   //(cmdr[cmdrind-1].theta1val)
						  +  ( rec_theta2[cmdr[cmdrind-1].rec_Uno] - cmdr[cmdrind-1].theta2val)/90.0 ) ;
			Qtab[cmdr[cmdrind-1].theta1*notheta2*noratio1*noratio2 + cmdr[cmdrind-1].theta2*noratio1*noratio2+cmdr[cmdrind-1].ratio1*noratio2 + cmdr[cmdrind-1].ratio2  ][cmdr[cmdrind-1].command_type - 1] =
			//		(cmdr[cmdrind].theta1 - cmdr[cmdrind-1].theta1)/(cmdr[cmdrind].theta1) +  // if the theta1 increase then positive credit
			//		(cmdr[cmdrind].theta2 - cmdr[cmdrind-1].theta2)/(cmdr[cmdrind].theta2) // same for theta2
					alph*Qtab[cmdr[cmdrind-1].theta1*notheta2*noratio1*noratio2 + cmdr[cmdrind-1].theta2*noratio1*noratio2+cmdr[cmdrind-1].ratio1*noratio2 + cmdr[cmdrind-1].ratio2  ][cmdr[cmdrind-1].command_type -1]
					+  (1-alph)*thetaincent //(cmdr[cmdrind-1].theta2val)
				   + gamma*state_out_Qval ; // max Q value from output state
			cmdr[cmdrind-1].Q_status = true ; lastactprocess = cmdrind-1 ;
												State st2(1) ; st2.x  = new double[4];

          Qex[cmdr[cmdrind-1].theta1*notheta2*noratio1*noratio2 + cmdr[cmdrind-1].theta2*noratio1*noratio2+cmdr[cmdrind-1].ratio1*noratio2 + cmdr[cmdrind-1].ratio2  ][cmdr[cmdrind-1].command_type - 1]
                                                                                                                                                                       = true ;
													st2.x[0] = cmdr[cmdrind-1].theta1 ;
					 		 	 		 		 	st2.x[1] = cmdr[cmdrind-1].theta2 ;
					 		 	 		 		 	st2.x[2] = cmdr[cmdrind-1].ratio1 ;
					 		 	 		 		 	st2.x[3] = cmdr[cmdrind-1].ratio2 ;
					 		 	 		 		 std::cout<<" state info before cmac is called "<<st2.x[0]<<" "<<st2.x[1]<<" "<<st2.x[2]<<" "<<st2.x[3] ;
					 		 	 		 		const double tar1 = double (Qtab[ cmdr[cmdrind-1].theta1*notheta2*noratio1*noratio2 + cmdr[cmdrind-1].theta2*noratio1*noratio2+cmdr[cmdrind-1].ratio1*noratio2 +cmdr[cmdrind-1].ratio2 ]
					 		 	 		 		                                  [cmdr[cmdrind-1].command_type - 1]) ;
					 		 	 		 		RS_LOG(LA_AGENT, "learning called for normal action ") ;
					 		 	 		 		switch(cmdr[cmdrind-1].command_type)
					 		 	 		 		{
					 		 	 		 		case 1:  {  cma1.decayTraces(DECAYFACTOR) ;
					 		 	 		 		cma1.accumulateTraces(st2, 1) ;  cma1.learn(st2, tar1 ) ; break ; }
					 		 	 		 		case 2: { cma2.decayTraces(DECAYFACTOR) ;
					 		 	 		 		cma2.accumulateTraces(st2, 1) ; cma2.learn(st2, tar1) ; break ; }
					 		 	 		 		case 3: { cma3.decayTraces(DECAYFACTOR) ;
					 		 	 		 		cma3.accumulateTraces(st2, 1) ; cma3.learn(st2, tar1) ; break ; }
					 		 	 		 		case 4: { cma4.decayTraces(DECAYFACTOR) ;
					 		 	 		 		cma4.accumulateTraces(st2, 1) ; cma4.learn(st2, tar1) ; break ; }
					 		 	 		 				}

			updateQInf(AGENUNO, CURRTIME,cmdr[cmdrind-1].theta1, cmdr[cmdrind-1].theta2,cmdr[cmdrind-1].ratio1, cmdr[cmdrind-1].ratio2,cmdr[cmdrind-1].command_type,
					 		 			Qtab[ cmdr[cmdrind-1].theta1*notheta2*noratio1*noratio2 + cmdr[cmdrind-1].theta2*noratio1*noratio2+cmdr[cmdrind-1].ratio1*noratio2 + cmdr[cmdrind-1].ratio2 ][cmdr[cmdrind-1].command_type-1] ) ;
			RS_LOG(LA_AGENT, " UPDATED QSTATUS OF LAST ACTION: action index  "<< cmdrind-1<< " increase and in theta "<<thetaincent<<" orginal state value "
					<< Qtab[cmdr[cmdrind-1].theta1*notheta2*noratio1*noratio2 + cmdr[cmdrind-1].theta2*noratio1*noratio2+cmdr[cmdrind-1].ratio1*noratio2 + cmdr[cmdrind-1].ratio2  ][cmdr[cmdrind-1].command_type-1]
				<<" stateoutput "<<state_out_Qval	) ;

		//	}
		/*	else
			{
// THIS IS BULL SHIT CODE BUT LETS RUN IT FOR NOW jan 27 10:47
				thetaincent = (( rec_theta1[cmdr[cmdrind-1].rec_Uno]	- cmdr[cmdrind-1].theta1val)/90.0   //(cmdr[cmdrind-1].theta1val)
										  +  ( rec_theta2[cmdr[cmdrind-1].rec_Uno] - cmdr[cmdrind-1].theta2val)/90.0 ) ;
				Qtab[cmdr[cmdrind-1].theta1*notheta2*noratio1*noratio2 + cmdr[cmdrind-1].theta2*noratio1*noratio2+cmdr[cmdrind-1].ratio1*noratio2 + cmdr[cmdrind-1].ratio2  ][cmdr[cmdrind-1].command_type] =
							//		(cmdr[cmdrind].theta1 - cmdr[cmdrind-1].theta1)/(cmdr[cmdrind].theta1) +  // if the theta1 increase then positive credit
							//		(cmdr[cmdrind].theta2 - cmdr[cmdrind-1].theta2)/(cmdr[cmdrind].theta2) // same for theta2
						alph*Qtab[cmdr[cmdrind-1].theta1*notheta2*noratio1*noratio2 + cmdr[cmdrind-1].theta2*noratio1*noratio2+cmdr[cmdrind-1].ratio1*noratio2 + cmdr[cmdrind-1].ratio2  ][cmdr[cmdrind-1].command_type]
						+    	(1-alph)* thetaincent  +  gamma*state_out_Qval ; // max Q value from output state
								cmdr[cmdrind-1].Q_status = true ; lastactprocess = true ;
								updateQInf(AGENUNO, CURRTIME,cmdr[cmdrind-1].theta1, cmdr[cmdrind-1].theta2,cmdr[cmdrind-1].ratio1, cmdr[cmdrind-1].ratio2,cmdr[cmdrind-1].command_type,
													 		 			Qtab[ cmdr[cmdrind-1].theta1*notheta2*noratio1*noratio2 + cmdr[cmdrind-1].theta2*noratio1*noratio2+cmdr[cmdrind-1].ratio1*noratio2 + cmdr[cmdrind-1].ratio2 ][cmdr[cmdrind-1].command_type] ) ;
								RS_LOG(LA_AGENT, " UPDATED QSTATUS OF LAST ACTION: action index  "<< cmdrind-1<< " increase and in theta "<<thetaincent<<" orginal state value "
													<< Qtab[cmdr[cmdrind-1].theta1*notheta2*noratio1*noratio2 + cmdr[cmdrind-1].theta2*noratio1*noratio2+cmdr[cmdrind-1].ratio1*noratio2 + cmdr[cmdrind-1].ratio2 ][cmdr[cmdrind-1].command_type]
												<<" stateoutput "<<state_out_Qval	) ;

			} */




		}


}


float pass1_theta1 , pass1_theta2 , pass1_ratio1, pass1_ratio2 , pass1_q ; int pass1_act;
float pass2_theta1 , pass2_theta2 , pass2_ratio1, pass2_ratio2  , pass2_q ; int pass2_act ;
float pass3_theta1 , pass3_theta2 , pass3_ratio1, pass3_ratio2  , pass3_q  ; int pass3_act ;
float pass4_theta1 , pass4_theta2 , pass4_ratio1, pass4_ratio2  , pass4_q ; int pass4_act ;
float pass_q[11] ; int pass_act[11] ;
float maxacttemp[4]; int maxacttempind[4] ;

// ServerCommand *gscmd_1

void FCFooDecision::passM(  int Uno)
{

	std::cout<<"\n starting PASSM "<<Uno ;
	RS_LOG(LA_AGENT, "\n starting PASSM "<<Uno) ;

	float maxQvalact = -10001.0 ; float maxQvalact_p= -10001.0 ;
	int maxQvalactindex_p= 100 ; int maxQvalactindex = 100 ;
	for (int i =0; i<4 ; i++)
	{ maxacttemp[i] =0 ;
	maxacttemp[i] = -1 ;}

	// if (CURRTIME%5 == 0 ) greedy=false ;
	greedy = true ; // temporary test

	if ( greedy == true)
	{


		// use max Q function  Q = q(s,a) + Gamma*q(s',a')
		// use just max Q value  max (q(s,a)
		maxQvalact = -100000 ; float testQval = 0 ; ServerCommand *tempgscmd=0, *tempgscmd2=0 ;
		bool actstatus = false ; float tempmaxQvalact_p = -1000 ; int tempmaxQvalactindex_p = -1000 ;
           for (int i = 0 ; i<noaction ; i++)
           {

        	   //maxacttemp[i] =  Qtab[rec_rtheta1[Uno]*18*4*4+ rec_rtheta2[Uno]*16 + rec_rratio1[Uno]*4 + rec_rratio2[Uno]][i] ;
    	   	   //	   maxacttempind[i] = i ;
        	   //if ( Qtab[ (rec_rtheta1[Uno]*18*4*4+ rec_rtheta2[Uno]*16 + rec_rratio1[Uno]*4 + rec_rratio2[Uno] )][i] > maxQvalact  )  {
        	   //maxQvalact =  Qtab[rec_rtheta1[Uno]*18*4*4+ rec_rtheta2[Uno]*16 + rec_rratio1[Uno]*4 + rec_rratio2[Uno]][i] ; maxQvalactindex = i ;
        	   	   //       	   }

        	   ActionSelection(i+1, teamm[Uno].getPosition().getPoint(), Uno) ;
        	   if(gscmd!=0) {
        	   predictedWorldstate(gscmd, gscmd2) ;
        	   if( recp_theta1[Uno] == -1000000 or recp_theta2[Uno]== -1000000
        			   or recp_ratio1[Uno] == -1000000 or recp_ratio2[Uno] == -1000000)
        	   {    RS_LOG(LA_AGENT, "following action has generated null state "<<i+1<<" "<<recp_theta1[Uno]
        	          <<" "<<recp_theta2[Uno]<<" "<<recp_ratio1[Uno]<<" "<<recp_ratio2[Uno]) ;
        		 continue ;
        	   }
        	   predThetaCorrection() ; tempmaxQvalact_p = -1000 ;  tempmaxQvalactindex_p = -1000 ;
        	   for (int j = 0 ; j<noactionqtab ; j++)
        	          {
        		      if (Qex[recp_rtheta1[Uno]*notheta2*noratio1*noratio2+ recp_rtheta2[Uno]*noratio1*noratio2 +
        		              recp_rratio1[Uno]*noratio2 + recp_rratio2[Uno] ][j] == false )
        		      {

        		           State st2(1) ; st2.x = new double [4] ; double outp1 ;
        		           st2.x[0] = recp_rtheta1[Uno] ; st2.x[1] = recp_rtheta2[Uno] ;  st2.x[2] = recp_rratio1[Uno] ;
        		           st2.x[3] = recp_rratio2[Uno] ;
        		           std::cout<<" state info before cmac is called "<<st2.x[0]<<" "<<st2.x[1]<<" "<<st2.x[2]<<" "<<st2.x[3] ;
        		    	  switch(j+1)
        		    	  {
        		    	  case 1: { cma1.predict(st2, outp1)  ; break ; }
        		    	  case 2: { cma2.predict(st2,outp1 ); break  ;}
        		    	  case 3: { cma3.predict(st2, outp1); break ; }
        		    	  case 4: {  cma4.predict(st2,outp1 ) ;break ;  }

        		    	  }

        		    	  if ( outp1 > tempmaxQvalact_p )  {
        		    	          	                   	   tempmaxQvalact_p =  outp1 ;
        		    	          	                   	   tempmaxQvalactindex_p = j ;
        		    	          	                   	   RS_LOG(LA_AGENT, "\n predicted action "<<j<<" Q(s',a') "<< tempmaxQvalact_p );
        		    	          	                   	   } //. if

        		      }

        		   if ( Qtab[ (recp_rtheta1[Uno]*notheta2*noratio1*noratio2+ recp_rtheta2[Uno]*noratio1*noratio2 + recp_rratio1[Uno]*noratio2 + recp_rratio2[Uno] )][j] > tempmaxQvalact_p )  {
        	                   	   tempmaxQvalact_p =  Qtab[(recp_rtheta1[Uno]*notheta2*noratio1*noratio2+ recp_rtheta2[Uno]*noratio1*noratio2 + recp_rratio1[Uno]*noratio2 + recp_rratio2[Uno])][j] ;
        	                   	   tempmaxQvalactindex_p = j ;
        	                   	   RS_LOG(LA_AGENT, "\n predicted action "<<j<<" Q(s',a') "<< tempmaxQvalact_p );
        	                   	   } //. if

        		    //  } // else
        	             } // for int j

        	   testQval = (recp_theta1[Uno] - rec_theta1[Uno])/90 + (recp_theta2[Uno] - rec_theta2[Uno])/90 +  gamma*tempmaxQvalact_p ;
        	   if(testQval > maxQvalact)
        	   { maxQvalact = testQval ; tempgscmd = gscmd ; tempgscmd2 = gscmd2 ; maxQvalactindex = i ;  actstatus = true ;
        	         maxQvalact_p = tempmaxQvalact_p ;  maxQvalactindex_p = tempmaxQvalactindex_p ;

        	         RS_LOG(LA_AGENT, "\n at S (t1,t2,r1,r2) "
        	        		 << rec_theta1[Uno]<<" "<< rec_theta2[Uno]<<" "<< rec_ratio1[Uno]<<" "<< rec_ratio2[Uno]
        	                 <<"after applying the command "<< i <<" the resulting state S'"<< recp_theta1[Uno]<<" "<<recp_theta2[Uno]
        	                  <<" "<<recp_ratio1[Uno] <<" "<<recp_ratio2[Uno]<<"  here a=(0,1,2,3) Q(S', "<<i<<") is "<<
        	                   			maxQvalact_p<<" ") ;
        	         RS_LOG(LA_AGENT, "\n    justREWard, totalreward( R+Q(s',a')),     maxQvalactindex,  Q(s',a'),  maxQvalactindex_p"<<
        	        		 ((recp_theta1[Uno] - rec_theta1[Uno])/20 + (recp_theta2[Uno] - rec_theta2[Uno])/20 )<<" "<<
        	        		 maxQvalact<<" "<<maxQvalactindex << " "<<maxQvalact_p<<" "<<maxQvalactindex_p) ;
        	   }
        	        	   } // if gscmd !=0
           } // for

//
//              float tempval=0 ; int tempind ;
//           //sort the max actions
//            for (int i =0 ; i<4 ; i++)
//            {  for (int j=i+1 ; j< 4 ; j++)
//            {    if (maxacttemp[i] > maxacttemp[j])
//            {   tempval = maxacttemp[j] ;
//            	maxacttemp[j] = maxacttemp[i] ;
//            	maxacttemp[i] = maxacttemp[j] ;
//            	tempind = maxacttempind[j] ;
//            	maxacttempind[j] = maxacttempind[i] ;
//            	maxacttempind[i] = tempind ;
//            }
//
//            } // for j
//            } // for i

            if(isinf(maxQvalact)) { RS_LOG(LA_AGENT, "maxQvalact is infinity") ;}
           // ActionSelection(maxQvalactindex+1, rec.getPosition().getPoint()) ;

//             for (int i=0 ; i<4 ; i++)
//             { std::cout<<"index and Qval "<< maxacttemp[i]<<" "<<maxacttempind[i] ;
//               RS_LOG(LA_AGENT, "index and Qval "<< maxacttemp[i]<<" "<<maxacttempind[i]); }
//            if (maxacttempind[3] != maxQvalactindex )
//            { std::cout<<"exit123 " ; RS_LOG(LA_AGENT, "EXIT123") ; //exit(0) ; }
//            }

//            bool actstatus = false ;
//            for (int i =3 ; i>=0 ; i--)
//            {
//
//            	RS_LOG(LA_AGENT, "executing action for "<<(maxacttempind[i]+1)) ;
//           ActionSelection(maxacttempind[i]+1, teamm[Uno].getPosition().getPoint(), Uno) ;
//
//           switch(MapPassToUno[Uno])
//           		           {
//           		           case 1:  	  { gscmd_1 = gscmd ; gscmd2_1 = gscmd2 ;  RS_LOG(LA_AGENT, "action for PASS1 activated" ); actstatus = true ;
//           		           if( gscmd_1 ==0 and gscmd2_1 == 0 )   { RS_LOG(LA_AGENT, "case 1 commands are null" ) ; actstatus = false ;  }break ;}
//           		           case 2:       {  gscmd_2 = gscmd ; gscmd2_2 = gscmd2 ;  RS_LOG(LA_AGENT, "action for PASS2 activated" ) ; actstatus = true ;
//           		           if( gscmd_2 ==0 and gscmd2_2 == 0 )   { RS_LOG(LA_AGENT, "case 2 commands are null" ) ; actstatus = false ; }break ; }
//           		           case 3:        { gscmd_3 = gscmd ; gscmd2_3 = gscmd2 ;  RS_LOG(LA_AGENT, "action for PASS3 activated" ) ; actstatus = true ;
//           		           if( gscmd_3 ==0 and gscmd2_3 == 0 )   { RS_LOG(LA_AGENT, "case 3 commands are null" ) ; actstatus = false ;  }break ;}
//           		           case 4: 			{ gscmd_4 = gscmd ; gscmd2_4 = gscmd2 ; RS_LOG(LA_AGENT, "action for PASS4 activated" ) ;actstatus = true ;
//           		           if( gscmd_4 ==0 and gscmd2_4 == 0 )   { RS_LOG(LA_AGENT, "case 1 commands are null" ) ;  actstatus = false ;}break ;}
//           		           }
//           if (actstatus == true ) break ;
//
//            }
//
//

            //predictedWorldstate(gscmd) ;
            //predThetaCorrection() ;
// since each pass module has to find  max ( Q(s,a)  = R

           // use the predicted states and get the max Q value ;
         // maxQvalact = -1000 ;
           // maxQvalactindex_p
//        for (int i = 0 ; i<noaction ; i++)
//                   {  if ( Qtab[ (recp_rtheta1[Uno]*18*4*4+ recp_rtheta2[Uno]*16 + recp_rratio1[Uno]*4 + recp_rratio2[Uno] )][i] > maxQvalact  )  {
//                 	   maxQvalact_p =  Qtab[recp_rtheta1[Uno]*18*4*4+ recp_rtheta2[Uno]*16 + recp_rratio1[Uno]*4 + recp_rratio2[Uno]][i] ; maxQvalactindex_p = i ;
//                 	   RS_LOG(LA_AGENT, "\n at S (t1,t2,r1,r2) "<< rec_theta1[Uno]<<" "<< rec_theta2[Uno]<<" "<< rec_ratio1[Uno]<<" "<< rec_ratio2[Uno]
//                 			   <<"after applying the command "<< maxacttempind[i]+1<<" the resulting state S'"<< recp_theta1[Uno]<<" "<<recp_theta2[Uno]
//                 			  <<" "<<recp_ratio1[Uno] <<" "<<recp_ratio2[Uno]<<"  here a=(0,1,2,3) Q(S', "<<i<<") is "<<
//                 			Qtab[recp_rtheta1[Uno]*18*4*4+ recp_rtheta2[Uno]*16 + recp_rratio1[Uno]*4 + recp_rratio2[Uno]][i]) ;
//                 	   }
//                    }
           // return intial and predicted  states and Q values .

//           switch(Uno)
//
//           {
//
//           case 1:
//           {
//        	   //pass1_q =   maxQvalact + gamma*maxQvalact_p ; pass1_act = maxQvalactindex_p ;
//        	   pass_q[Uno] =
//        	   break ;    }
//           case 2:
//           {     pass2_q =   maxQvalact + gamma*maxQvalact_p ; pass2_act = maxQvalactindex_p ; break ; }
//           case 3:
//           {     pass3_q =   maxQvalact + gamma*maxQvalact_p ;  pass3_act= maxQvalactindex_p ;break ; }
//           case 4:
//           {     pass4_q =   maxQvalact + gamma*maxQvalact_p ; pass4_act = maxQvalactindex_p;  break ; }
//
//           }



            switch(MapPassToUno[Uno])
                      		           {
                      		           case 1:  	  { gscmd_1 = tempgscmd ; gscmd2_1 = tempgscmd2 ;  RS_LOG(LA_AGENT, "action for PASS1 activated" ); actstatus = true ;
                      		           if( gscmd_1 ==0 and gscmd2_1 == 0 )   { RS_LOG(LA_AGENT, "case 1 commands are null" ) ; actstatus = false ;  }break ;}
                      		           case 2:       {  gscmd_2 = tempgscmd ; gscmd2_2 = tempgscmd2 ;  RS_LOG(LA_AGENT, "action for PASS2 activated" ) ; actstatus = true ;
                      		           if( gscmd_2 ==0 and gscmd2_2 == 0 )   { RS_LOG(LA_AGENT, "case 2 commands are null" ) ; actstatus = false ; }break ; }
                      		           case 3:        { gscmd_3 = tempgscmd ; gscmd2_3 = tempgscmd2 ;  RS_LOG(LA_AGENT, "action for PASS3 activated" ) ; actstatus = true ;
                      		           if( gscmd_3 ==0 and gscmd2_3 == 0 )   { RS_LOG(LA_AGENT, "case 3 commands are null" ) ; actstatus = false ;  }break ;}
                      		           case 4: 			{ gscmd_4 = tempgscmd ; gscmd2_4 = tempgscmd2 ; RS_LOG(LA_AGENT, "action for PASS4 activated" ) ;actstatus = true ;
                      		           if( gscmd_4 ==0 and gscmd2_4 == 0 )   { RS_LOG(LA_AGENT, "case 1 commands are null" ) ;  actstatus = false ;}break ;}
                      		           }

            if (actstatus == false )
            { RS_LOG(LA_AGENT, "THIS PASS doesnt have any action associated PASSM "<< MapPassToUno[Uno]) ; }
            else {
            		RS_LOG(LA_AGENT, "\n After processing all the actions maxQvalact  maxQvalactindex maxQvalact_p maxQvalactindex_p"<< maxQvalact<<" "<<maxQvalactindex <<
            				" "<<maxQvalact_p<<" "<<maxQvalactindex_p) ;

            		pass_q[Uno] = maxQvalact ;// + gamma*maxQvalact_p ;
            		pass_act[Uno]= maxQvalactindex+1 ;
            		RS_LOG( LA_AGENT , " Uno,  MAX PASS_Q value , max action  "<<pass_q[Uno]<<" "<<pass_act[Uno]) ;
            }

	}else
	{

		std::cout<<"\n in the else portion of the PASSM " ;
		RS_LOG(LA_AGENT, "\n in the else portion of the PASSM ") ;
             maxQvalactindex = std::rand() ;
             std::cout<<"\n the random pass # "<<maxQvalactindex ;
             RS_LOG(LA_AGENT, "\n the random pass # "<<maxQvalactindex) ;
             if(teamm[Uno].getPosition().isKnown() == false )
            	 { std::cout<<"\n recievers position in random selection is not know " ;
            	 RS_LOG(LA_AGENT, "\n recievers position in random selection is not know ") ;
            	 }
             // ActionSelection((maxQvalactindex%noaction + 1 ), teamm[Uno].getPosition().getPoint()) ;
             ActionSelection((maxQvalactindex + 1 ), teamm[Uno].getPosition().getPoint(), Uno ) ;
            //  predictedWorldstate(gscmd) ;
	}


	std::cout<<"\n completed PASSM  UNO : mappassuno "<<Uno<<" "<<MapPassToUno[Uno] ;
	RS_LOG(LA_AGENT, "\n completed PASSM  UNO : mappassuno "<<Uno<<" "<<MapPassToUno[Uno] ) ;

}
//float reward ;
//int ACTION ;
//if ( ACTION == 2 ) { reward = 10 ; } else { reward = 0 ;}
//
//
//
//
//
//Expected_afteract_state =
//for ( ACTION =1 ; ACTION < 5; ACTION++ )
//{
//
//}
//
//switch (ACTION)
//{
//if(ACTION =='TURNAROUND' )
//{
//
//	Expected_afteract_state = rec_rtheta1 }
//
//}
//     float E_QVAL =  reward + Gamma*(maxQS2A) ;
//    if ( )
//	ActionSelection() ;



void FCFooDecision::predictedWorldstate(ServerCommand *scmd , ServerCommand *scmd2)
{

	std::cout<<"\n predicted world state" ;
	RS_LOG(LA_AGENT, "\n predicted world state") ;
	const CommandStrategy* cmd_strategy
			    		 	    = WorldModelInterface::instance()->getCommandStrategy();
			    		 	  const NewCycleStrategy* new_cycle_strategy
			    		 	    = WorldModelInterface::instance()->getNewCycleStrategy();
			    		 	 WorldModel predicted_wm =(WorldModelInterface::instance()->getWorld(NOW));
			    		 	 //  predicted_wm[0] =

			    		 	 if ( scmd != 0  ) {
			    		 		    		 	    cmd_strategy->updateAfterCommand(predicted_wm, scmd);
			    		 		    		 	      }
			    		 	 if( scmd2!=0)
			    		 	 {   cmd_strategy->updateAfterCommand(predicted_wm, scmd2) ; }

			    		 		    		 	  new_cycle_strategy->updateBeforeNewCycle(predicted_wm);

			    		 		    		 	  AgentObject& agent = predicted_wm.getAgent() ;
			    		 		    		 	 PointUE predictedPosition = agent.getPosition();


			    		 		    		 	 ViewManager *vm = ViewManager::instance() ;
			    		 		    		 // 	 aview.viewManager(vm) ;
			    		 		    		  WorldModelInterface* wmip= WorldModelInterface::nonConstInstance()  ;
			    		 		    		 	wmip->setWorld(predicted_wm, NOW) ;
			    		 		    		 	//  aview.worldModelInterface(wmip) ;
			    		 		    		 	AgentView aview(AGENT_VIEW_ID, vm, wmip) ;
			    		 		    		 	BallView  bview(BALL_VIEW_ID, vm, wmip) ;
			    		 		    		 	PlayerView pview(PLAYER_VIEW_ID, vm,wmip) ;

			    		 		    		 	//const std::vector<PlayerObject>& opps_pwm   = predicted_wm[0].getOpponents();
			    		 		    		 	 // const std::vector<PlayerObject>& team_pwm =  predicted_wm[0].getTeammates() ;
			    		 		    		 	// const std::vector<PlayerObject>& opps_ppv =  0 ;
			    		 		    		 	//float *recp_theta1 = new float [11] ;
			    		 		    		 	//float *recp_theta2 = new float [11] ;

			    		 		    		 	 std::cout<<"\n predicted player info" ;
			    		 		    		 	 RS_LOG(LA_AGENT,"\n predicted player info" ) ;
			    		 		    		 	 getPlayerInfo(predicted_wm,  wmip, &aview, &bview,&pview,recp_theta1,recp_theta2, recp_ratio1, recp_ratio2) ;

			    		 		    		 	 std::cout<<"\n done predicted player info" ;
			    		 		    		 	 RS_LOG(LA_AGENT,"\n done predicted player info" ) ;

			    		 		    		 	  vm->releaseView(BALL_VIEW_ID);
			    		 		    		 	  vm->releaseView(PLAYER_VIEW_ID);
			    		 		    		 	  vm->releaseView(AGENT_VIEW_ID);


			    		 		    		 	 aview.AgentView::~AgentView() ;
			    		 		    		 	  bview.BallView::~BallView() ;
			    		 		    			  pview.PlayerView::~PlayerView() ;
			    		 		    		 //	  wmip->WorldModelInterface::~WorldModelInterface() ;
			    		 		    	     //	  predicted_wm.WorldModel::~WorldModel() ;
			    		 		    		 	  std::cout<<"out of predicted world state" ;
			    		 		    		 	  RS_LOG(LA_AGENT,"out of predicted world state" ) ;


}



 int 	  mapcnt=1 ; bool  Qfilewritestatus = false ; bool Qfilereadstatus = false ; int lastdisperse =0; float lastdispersedashang  ;
 int STOPCLOCK = 0 ; bool cmacstat = false ;
 std::vector<ServerCommand*> vscmd ;
bool FCFooDecision::decide() {

	if(vscmd.size() > 0)
	   { actuatorInterface->addToPlan(vscmd.back()) ;
	    vscmd.pop_back() ;
	    return  true ;
	   }
	//CMAC::Tiling til();
	RS_LOG ( LA_DECISION, "Decide" );
	    char* testch1 = new char[20] ;
	    char* testch2 = new char[20] ;
	    char* testch3 = new char[20] ;
	    char* testch4 = new char[20] ;
	    char* testch5 = new char[20] ;
	       strcpy( testch1 , "sparm1.txt") ;
	       strcpy( testch2 , "sparm2.txt") ;
	       strcpy( testch3 , "sparm3.txt") ;
	       strcpy( testch4 , "sparm4.txt") ;
	       strcpy( testch5 , "sparm5.txt") ;

	    State::dimensionality = 4 ;

  static int say_counter = 10;
  Command *cmd = 0;
  ServerCommand *scmd = 0, *scmd2=0;
  ServerCommand *neckcmd = 0;
  ServerCommand *saycmd = 0;
  ServerCommand *pointcmd = 0;
  gscmd_1 = 0 ; gscmd2_1=0 ; gscmd_2=0 ; gscmd2_2 =0 ; gscmd_3=0 ; gscmd2_3=0 ; gscmd_4=0;gscmd2_4=0 ;
   bool actionstatus=false ;
    TIME = Time::currentTime ;
      CURRTIME = TIME.getT() ;

      if(agentView->getUniformNumber().isKnown())
      { std::cout<<"\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< NEW AGENT DECIDE CLOCK CYCLE :CYCLE# "<<CURRTIME<<" AgentUniform  "<<agentView->getUniformNumber()
    	  <<" >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
      RS_LOG(LA_AGENT, "\n<<<<<<<<< NEW AGENT DECIDE CLOCK CYCLE :CYCLE# "<<CURRTIME<<" AgentUniform  "<<agentView->getUniformNumber()
        	  <<" >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" );
      AgeUno = agentView->getUniformNumber().getValue() ;
      AGENUNO = AgeUno ;

      RS_LOG(LA_AGENT,"agent uno"<<AgeUno<<" "<<AGENUNO) ;}
      else   {std::cout<<"\n NEW CYCLE DECIDE "<<CURRTIME<<" Uno " ;
      RS_LOG(LA_AGENT,  "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< NEW AGENT DECIDE CLOCK CYCLE :CYCLE# "<<CURRTIME
    	  <<" >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n AGENT DOESNT KNOW ITS UNIFORM NUMBER ") ;
      }

  	if (cmacstat == false )
   	{

   //	char* filecmac = "cmacfile.txt" ;/
   //	CMAC cma(filecmac);
   	double lef[] = {0,0,0,0} ;
   	double rig[] = {9,9,3,3} ;
   	std::cout<<"\n init finished" ;
   	cma1.setInputBounds(lef, rig) ;
   	cma2.setInputBounds(lef, rig) ;
   	cma3.setInputBounds(lef, rig) ;
   	cma4.setInputBounds(lef, rig) ;
   	cma5.setInputBounds(lef, rig) ;
   	CMAC::Tiling::setTraceDecay(0.5) ;
   	for (int i=0 ; i<cma1.T;i++)
   	{
   	cma1.tilings[i].setAlpha(0.2) ;
	cma2.tilings[i].setAlpha(0.2) ;
	cma3.tilings[i].setAlpha(0.2) ;
	cma4.tilings[i].setAlpha(0.2) ;
	cma5.tilings[i].setAlpha(0.2) ;
   	}
   	std::cout<< cma1.getSize() ; // exit(0);
   	std::cout<< cma2.getSize() ;
   	std::cout<< cma3.getSize() ;
   	std::cout<< cma4.getSize() ;
   	std::cout<< cma5.getSize() ;


   	//State cmstate[1600] ;
   	cmstate[0].dimensionality = 4 ;
   	for (int thet1=0 ;thet1<10 ; thet1++ )
   	{	for ( int thet2=0 ; thet2<10;thet2++)
   		{	for(int rat1=0; rat1<4 ; rat1++)
   			{	for (int rat2=0 ; rat2<4 ; rat2++)
   				{    cmstate[thet1*160+ thet2*16+rat1*4 + rat2].x = new double[4] ;
   					cmstate[thet1*160+ thet2*16+rat1*4 + rat2].x[0] = thet1*1.0 ;
   					cmstate[thet1*160+ thet2*16+rat1*4 + rat2].x[1] = thet2*1.0 ;
   					cmstate[thet1*160+ thet2*16+rat1*4 + rat2].x[2] = rat1*1.0 ;
   					cmstate[thet1*160+ thet2*16+rat1*4 + rat2].x[3] = rat2*1.0 ;

   				}
   			}
   		}
   	}
   	std::cout<<"seg no fault" ;

   //     char** argv ;
   //     argv[0] = testch ;
   	cma1.saveArchitectureParameters(1,&testch1) ;
   	cma2.saveArchitectureParameters(1,&testch2) ;
   	cma3.saveArchitectureParameters(1,&testch3) ;
   	cma4.saveArchitectureParameters(1,&testch4) ;
   	cmacstat = true ;
   	}

   	if( CURRTIME % 100 == 0 )
 	{
 		cma1.saveArchitectureParameters(1,&testch1) ;
 		cma2.saveArchitectureParameters(1,&testch2) ;
 		cma3.saveArchitectureParameters(1,&testch3) ;
 		cma4.saveArchitectureParameters(1,&testch4) ;
 	}


  if ( agentView->getPosition().isKnown())
  { RS_LOG(LA_AGENT, "   AGENTS POSITION "<<agentView->getPosition().getPoint()) ; }
      for(int i =1 ; i<=11; i++)
      { pass_q[i] = -1000000000000000   ; pass_act[i] = -1; }
//      test_qval = -10000 ; test_qval_ind = 0 ;
 // const std::vector<PlayerObject>&      opps_wmcopy  = wm.getOpponents();

 // for ( int ind123=0 ; ind123< 11 ; ind123++)
 // {   opps_wm[ind123] = NULL ;}
// for (int ind123=0 ; ind123 < opps_wmcopy.size(); ind123++)
// {   opps_wm[ind123]= opps_wmcopy[ind123] ; }

      opps_wm =  wm.getOpponents() ;
      team_wm =  wm.getTeammates() ;
      opps_pv =  playerView->getOpponents(0);



   if( (gameView->getPlayMode() == PM_TIME_OVER or gameView->getPlayMode() == PM_BEFORE_KICK_OFF ) and CURRTIME !=0 and Qfilewritestatus == false )
  {

	   std::cout<<"\n   WRITE  Q-table TO QFILE AFTER HALF TIME OR TOTAL TIME OVER  " ;
	  writeQFile() ; Qfilewritestatus = true ;
     }



  if ( gameView->getPlayMode() == PM_BEFORE_KICK_OFF ) {


	  if (Qfilereadstatus == false )
	  { readQFile() ;  Qfilereadstatus = true ; }

	  if(agentView->getBodyDirection().isKnown()) {
	  AngleDeg bodyangle ( 10 + agentView->getBodyDirection().getDeg()) ;
	  TurnBodyToAbsoluteDirection TurnBody(bodyangle) ;
	  scmd =  dynamic_cast<ServerCommand*> (TurnBody.generateStep().getNextCommand()) ;
	  actuatorInterface->addToPlan( scmd) ;}
	//  getPlayerInfo(wm, wmi, agentView, ballView, playerView, rec_theta1, rec_theta2, rec_ratio1, rec_ratio2) ;
	  getPlayerInfo() ;
	  thetaCorrection() ;

  //   RS_LOG(LA_AGENT, "intialised "<<mapstatus[1]<<" "<<mapstatus[2]) ;
	        for (int i=1 ; i<11 ; i++)
	     	 {

	     	   if(teamm[i].getPosition().isKnown() and mapstatus[i]== false )
	     	   { MapUnoToPass[mapcnt] = i ; mapstatus[i]= true ;
	     	     MapPassToUno[i]= mapcnt ;
	     	    mapcnt++ ; }
	       }

	        if ( agentView->getBodyDirection().isKnown() and agentView->getUniformNumber().isKnown()) {
	        AgeUno =  agentView->getUniformNumber().getValue() ; }


  } else
  {


//	   if(CURRTIME == PREVTIME )
//	   {
//		   float NeckAng ;
//		     switch( STOPCLOCK%4)
//		     {
//		     case 0 : { NeckAng = 45 ; break ;}
//		     case 1 : {NeckAng = 0 ; break ;}
//		     case 2  : { NeckAng = -45 ; break ;}
//		     case 3: { NeckAng = 0 ; break ; }
//		     }
//
//		   if ( agentView->getBodyDirection().isKnown()  )
//		   {            TurnNeckToAbsoluteDirection   TurnNeck(
//			   AngleDeg(agentView->getBodyDirection().getDeg() + NeckAng ), 0) ;
//		   ServerCommand *scmd1 = dynamic_cast<ServerCommand*> (TurnNeck.generateStep().getNextCommand()) ;
//		   		   actuatorInterface->addToPlan(scmd1) ;
//		   		   RS_LOG(LA_AGENT, "TURN NECK IS EXECUTED WHEN CLOCK STOPPED"<<CURRTIME ) ;
//		   		   getPlayerInfo() ;
//		   } // if agent
//                      STOPCLOCK++ ;
//
//	   } // if CURR == PREVIMT

	   // STOPCLOCK = 0;
	  RS_LOG( LA_AGENT, "MAPPING INFORMATION OF AGENT TO PASS Modules  ") ;
	  for (int i=1; i<=4 ; i++)
	  {
		  RS_LOG(LA_AGENT,"\n mapstatus PASS module : Agent Uniformn# : Reverse Mapping AGENTUno TO PASSM = "
				  <<i<<" : "<<MapUnoToPass[i] <<" : "<< MapPassToUno[MapUnoToPass[i]] ) ;
	  }

	  updateQtab() ;


     //  if (CURRTIME > PREVTIME ) {
    //	   std::cin.get() ;
     // scmd = new DashCommand(5, 180) ;
     // actuatorInterface->addToPlan(scmd);
     //angleinc++ ;if(angleinc > 9 ) { angleinc = angleinc -9 ;} }
      // PREVTIME =CURRTIME ;
      // return true ;


	  if(CURRTIME%5 == 0 ) {greedy = true ; } else { greedy = true ;}

	  if(ballView->getPosition().isKnown() == false  )  { std::cout<<"\n ALERT FLAG : ballview position is not known " ;
	 	  RS_LOG(LA_AGENT, "\n ALERT FLAG  ballview position is not known " ) ;}


	  if (ballView->getPosition().isUnknown()) {
	  if (searchBall.applicable()) {
	       			        RS_LOG ( LA_DECISION, "SearchBall" );
	       			    cmd = searchBall.generateStep().getNextCommand();
	       			        scmd = dynamic_cast<ServerCommand*>(cmd); cmdty = "SEARCH" ;

	       			        if (scmd !=0)  {actuatorInterface->addToPlan(scmd ) ;
	       			        actionstatus = true ;
	       			        std::cout<<"\n  BALL IS NOT VISIBLE EXECUTING SEARCHBALL " ;
	       			        RS_LOG(LA_AGENT, "\n  BALL IS NOT VISIBLE EXECUTING SEARCHBALL " ) ;
	       			         } else {   std::cout<<"\n search ball cmd is NULL" ; RS_LOG(LA_AGENT, "search ball cmd is NULL") ; }
	       			  	  	  	  	  	  	  	 return true ;
	  }
	  }
 //  qvalUpdate() ;

	  if ( (gameView->getPlayMode() == PM_OUR_KICK_OFF ) and
	                          gameView->isKickAllowed() and
	                   ( ballView->getRelativeDistance() <= facts->SP_kickable_margin))
	          {

	                  ServerCommand *kickcm = new KickCommand(75, 0) ;
	                  if (kickcm != 0) { actuatorInterface->addToPlan(kickcm) ;	   return true ;}
	          }


  // getPlayerInfo(wm, wmi, agentView, ballView, playerView, rec_theta1, rec_theta2, rec_ratio1, rec_ratio2) ;
	  getPlayerInfo() ;
   thetaCorrection() ;
   for (int i=1 ; i<11 ; i++)
  	     	 {

  	     	   if(teamm[i].getPosition().isKnown() and mapstatus[i]== false )
  	     	   { MapUnoToPass[mapcnt] = i ; mapstatus[i]= true ;
  	     	     MapPassToUno[i]= mapcnt ;
  	     	    mapcnt++ ; }
  	       }



float    agentballdist = ballView->getPosition().getPoint().getDistanceTo(agentView->getPosition().getPoint()) ;
       std::cout<<"\n AGENT IS CHECKING IF ITS CLOSEST TO BALL ELSE SOME OTHER TEAM MATE IS CLOSEST : agent_to_ball_dist and min_teammate_balldist "<<agentballdist<<" "<<minballdist ;
       RS_LOG(LA_AGENT,"\n AGENT IS CHECKING IF ITS CLOSEST TO BALL ELSE SOME OTHER TEAM MATE IS CLOSEST : agent_to_ball_dist and min_teammate_balldist "<<agentballdist<<" "<<minballdist  ) ;
    	             if( agentballdist < minballdist )  {  amIClosest	= true ;  minballdist = agentballdist ;  minballdistUno = AgeUno ;
    	             RS_LOG(LA_AGENT, "\n Agent is closest to the Ball ") ;
    	             }
    	             else { amIClosest = false ;
    	             RS_LOG(LA_AGENT, "\n Agent is Not closest to the Ball ") ;
    	              }

    	             std::cout<<"\n  curr time : amiclosest : min_balldist_Uno "<<CURRTIME<<" "<<amIClosest<<" "<<minballdistUno ;
    	             RS_LOG(LA_AGENT , "\n  curr time : amiclosest : min_balldist_Uno "<<CURRTIME<<" "<<amIClosest<<" "<<minballdistUno ) ;



    	             std::cout<<"\n about to go qvalupdate" ;
    	                 RS_LOG(LA_AGENT, "\n <<<<<<<<<<<<<ENTERING IN Q-table Update, To update the results of Last Action >>>>>>>>>>>>>>>>>> " ) ;
    	                    qvalUpdate() ;
    	                   std::cout<<"\n out of quval" ;
    	                   RS_LOG(LA_AGENT, "\n <<<<<<<<<<<<<<<<<<<< Q-table Update finished >>>>>>>>>>>>>>>>>>>>>>>>> ") ;
  if (CURRTIME > PREVTIME  and amIClosest == true and agentballdist < 2  ) {

	  std::cout<< "\n the player is closest and in loop" ;
	  RS_LOG(LA_AGENT,"\n <<<<<<<<The Agent is Closest and its with in Close Range of the BALL >>>>>>>>>>>>>>>> "  ) ;

	  Point TurnPoint_P(0.0,0.0) ;
	  float  TurnAngChk_P=359.0;


       int randtest=0 ;
       bool recknown = false ;
       float maxtheta = -1000 ; int maxthetaind =0 ;
          	   float maxkicktheta = -1000 ; int maxkickthetaind = 0 ;
       //mapping table MapUnoToPassagentballdist and minballdist
       if (cmdrind >=1 ) {

    	   //int AgeUno =  agentView->getUniformNumber().getValue() ;
    	   //while(recknown == false  )exiting because action status is false

    	   // {   randtest = (std::rand())%5  ;

    	   //if( !(teamm[randtest+1].getPosition().isKnown() ) and randtest == AgeUno )
    	//	   { std::cout<<"\n teamm  recno position is not known "<<randtest ;
    	//	    RS_LOG(LA_AGENT,"\n teamm  recno position is not known " <<randtest) ; recknown = false ;
    	//	   }
    	 //  else { recknown = true ; }
    	  // }

    	   if ( gameView->isKickAllowed() &&
	  	      ( ballView->getRelativeDistance() <= facts->SP_kickable_margin))  {




    		   RS_LOG(LA_AGENT, "\n <<<<<< Checking if a Kick Action can be executed since the ball is close in range >>>>>>>>>>>>>>>>>") ;
    		   RS_LOG(LA_AGENT, "\n  Checking if it can be Kicked to a Reciever") ;
    	   for(int i=1 ; i<=4;i++)
    	   {
    		    if (teamm[MapUnoToPass[i]].getPosition().isKnown())
    		    {  if(rec_theta1[MapUnoToPass[i]] + rec_theta2[MapUnoToPass[i]]  > maxtheta )
    		   {

    		    	  maxtheta =  rec_theta1[MapUnoToPass[i]] + rec_theta2[MapUnoToPass[i]] ;
    		          maxthetaind = MapUnoToPass[i] ;
    		          RS_LOG(LA_AGENT,  "\n  Reciever Uniform# "<<"  "<<MapUnoToPass[i])<<" its Kickable state value "<<maxtheta ;
    		          TurnPoint_P =   teamm[MapUnoToPass[i]].getPosition().getPoint() ;
    		          TurnAngChk_P = float(agentView->getPosition().getDirectionTo(TurnPoint_P).getDeg()) - float (agentView->getBodyDirection().getAngle().getDeg()) ;
    		          RS_LOG(LA_AGENT , "TurnAngChk_p "<<TurnAngChk_P) ;
    		             if( TurnAngChk_P <= facts->SP_maxmoment and  TurnAngChk_P >= facts-> SP_minmoment )
    		             {
    		            	   maxkicktheta = rec_theta1[MapUnoToPass[i]] + rec_theta2[MapUnoToPass[i]] ;
    		            	   maxkickthetaind = MapUnoToPass[i] ;
    		            	   RS_LOG(LA_AGENT, "max kick theta and its ind" << maxkicktheta<<" "<<maxkickthetaind) ;
    		             } // if TurnAng
    		   } // if rec_the
    		    } // if teamm

    	   }// for

    	   } // if game

    	   else {

    		   RS_LOG(LA_AGENT, " the KICK IS NOT ALLOWED IN THIS CYCLE BECAUSE THE BALL IS AWAY ") ;
    	   }
       }


        if ( maxkicktheta == -1000 and maxtheta != -1000) { maxkickthetaind = maxthetaind ; }
      // this code is to hit the goal if no receiver is visible.
        //if(maxkicktheta == -1000 )
       // {
       // 	TurnPoint_P =  facts->getTheirGoal().getPosition() ; //teamm[maxkickthetaind].getPosition().getPoint() ;
       // 	       TurnAngChk_P = float(agentView->getPosition().getDirectionTo(TurnPoint_P).getDeg()) - float (agentView->getBodyDirection().getAngle().getDeg()) ;
        // }

       std::cout<<"\n the reciever selected for kick "<<maxkickthetaind<<" its theta value "<<maxkicktheta ;
       RS_LOG(LA_AGENT,"\n the reciever selected for kick "<<maxkickthetaind<<" its theta value "<<maxkicktheta) ;
    	   // if (agentView->getPosition().getDirectionTo(TurnPoint_P).isKnown() and agentView->getBodyDirection().isKnown()){
    	if ( teamm[maxkickthetaind].getPosition().isKnown() and maxkicktheta != -1000)
    	   {
       TurnPoint_P =   teamm[maxkickthetaind].getPosition().getPoint() ;
       TurnAngChk_P = float(agentView->getPosition().getDirectionTo(TurnPoint_P).getDeg()) - float (agentView->getBodyDirection().getAngle().getDeg()) ;
    	   }

    	    // if (agentView->getPosition().getDirectionTo(TurnPoint_P).isKnown() and agentView->getBodyDirection().isKnown()){
      //  }
      float test_qval = -10000.0 ; int test_qval_ind = 0 ;

      std::cout<<"\n gameview->iskick" ;
      RS_LOG(LA_AGENT, "\n gameview->iskick") ;

      if ( gameView->isKickAllowed() &&
	  	      ( ballView->getRelativeDistance() <= facts->SP_kickable_margin) and cmdrind >=1
	         and  (  ( TurnAngChk_P <= facts->SP_maxmoment and  TurnAngChk_P >= facts-> SP_minmoment and maxkicktheta != -1000 )
	       // 		 or ( maxkicktheta == -1000)
	        		 ) )
      {
    	  	  RS_LOG(LA_AGENT, " in kicking if block ");
	  	  	  RS_LOG ( LA_DECISION, "Kicking" );
// 			  		  	  angleinc = angleinc - 18*floor(angleinc/18) ;
// The ball is kickable, can we kick it to the ball. // Get the direction to the receiver .  //AngleDegUE goal_dir = 20*(angleinc+1.0);  //angleinc = angleinc+1.0 ; //Kick the ball towards the receiver


	  	  	 // scmd = new KickCommand(50,AngleDeg(TurnAngChk_P));
	  	  	 if( maxkicktheta != -1000) {
	  	  	                       scmd = new KickCommand(50,AngleDeg(TurnAngChk_P)); }
	  	  	                        else { scmd = new KickCommand(100,AngleDeg(TurnAngChk_P)); }

	  	  	  kick_status=false ;
	  	  	  cmdty = "kick" ;
	  	  	 // if (scmd!=0)  { actuatorInterface->addToPlan(gscmd_1 ) ; }
	  	  	if (scmd!=0)  { actuatorInterface->addToPlan(scmd ) ; }

	  	  //if (gameView->getPlayMode() != PM_PLAY_ON ) {  RS_LOG(LA_AGENT, " playmode is not play on , so the CMDR is not updated" );
	  	    //  	      return true ; }

           if(maxkicktheta != -1000) {
	  	  	cmdr[cmdrind].command_type =   5 ;
	  	  	    	      cmdr[cmdrind].rec_Uno =  maxkickthetaind ; //randtest+1 ; //cmdr[cmdrind-1].rec_Uno ;
	  	  	    	      cmdr[cmdrind].Q_status = false ;
	  	  	    	      cmdr[cmdrind].theta1 =  rec_rtheta1[maxkickthetaind ] ; //  rec_rtheta1[cmdr[cmdrind-1].rec_Uno] ;
	  	  	    	      cmdr[cmdrind].theta2 =  rec_rtheta2[maxkickthetaind ] ; //rec_rtheta2[cmdr[cmdrind-1].rec_Uno] ;
	  	  	    	      cmdr[cmdrind].ratio1 =  rec_rratio1[maxkickthetaind ] ; // rec_rratio1[cmdr[cmdrind-1].rec_Uno] ;
	  	  	    	      cmdr[cmdrind].ratio2 =    rec_rratio2[maxkickthetaind ] ;//  rec_rratio2[cmdr[cmdrind-1].rec_Uno] ;
	  	  	    	      cmdr[cmdrind].theta1val =    rec_theta1[maxkickthetaind ] ;//rec_theta1[cmdr[cmdrind-1].rec_Uno] ;
	  	  	    	      cmdr[cmdrind].theta2val =   rec_theta2[maxkickthetaind ] ; // rec_theta2[cmdr[cmdrind-1].rec_Uno] ;
	  	  	    	      if( ballView->getSpeedVector().isKnown()) {
	  	  	    	      cmdr[cmdrind].ballSpeedVector = ballView->getSpeedVector().getVector() ; }
	  	  	    	      cmdr[cmdrind].time = CURRTIME ;
	  	  	    	      cmdr[cmdrind].rec_pos = TurnPoint_P ;
	  	  	    	      if (agentView->getPosition().isKnown()) {
	  	  	    	      cmdr[cmdrind].kick_pos = agentView->getPosition().getPoint(); }
	  	  	    	      cmdr[cmdrind].kick_absangle =  cmdr[cmdrind].kick_pos.getDirectionTo(TurnPoint_P).getDeg() ;
	  	  	    	      last_kickind = cmdrind ;
	  	  	    	    //  cmdrind++ ;
	  	  	    	      actionstatus == true ;
	  	  	    	      std::cout<<"\n EXECUTING KICK COMMAND " ;
	  	  	    	      RS_LOG(LA_AGENT,"\n EXECUTING KICK COMMAND " ) ;
	  	  	    	      RS_LOG( LA_AGENT, "CMDR actionrecord "<<
	  	  	    	    		  cmdr[cmdrind].time << " "<<CURRTIME<<" cmdind "<<cmdrind<<
	  	  	    	    		  " \n recUno "<<cmdr[cmdrind].rec_Uno <<
	  	  	    	    		  " cmdtype " <<cmdr[cmdrind].command_type
	  	  	    	    		  <<" Qstatus "<<cmdr[cmdrind].Q_status
	  	  	    	    		  <<" theta1 "<<cmdr[cmdrind].theta1
	  	  	    	    		  <<" theta2 "<<cmdr[cmdrind].theta2
	  	  	    	    		  <<" ratio1 "<<cmdr[cmdrind].ratio1<<
	  	  	    	    		  " ratio2 " <<cmdr[cmdrind].ratio2
	  	  	    	    		  <<" theta1val "<< cmdr[cmdrind].theta1val<<" theta2val"<< cmdr[cmdrind].theta2val
	  	  	    	    		  <<" ballspeedvec "<<cmdr[cmdrind].ballSpeedVector <<" kick_pas "<<cmdr[cmdrind].kick_pos<<" kick abs angle "
	  	  	    	    		  <<cmdr[cmdrind].kick_absangle
	  	  	    	               <<" receiver pos"<<cmdr[cmdrind].rec_pos ) ;

                                            cmdrind++ ; }
	  	  	    	      PREVTIME = CURRTIME ;  // cmdrind++ ;
	  	  	    	  	  CURRTIME = TIME.getT() ;
	  	  	    	  	   if (CURRTIME-PREVTIME > 0) {
	  	  	    	  	  			    	 std::cout <<"  CURRTIME-PREVTIME > 0" ;
	  	  	    	  	  			    	 RS_LOG(LA_AGENT,"  CURRTIME-PREVTIME > 0"  ) ;
	  	  	    	  	  			    	 exit(0);}

      }

      else  {

    	  int cntpass = 0 ;
       for (int i=1;i<= 4 ; i++)
       {
    	   if ( teamm[MapUnoToPass[i]].getPosition().isKnown())
    	   {  // passM( teamm[MapUnoToPass[i]] , MapUnoToPass[i]) ;
    		   passM(  MapUnoToPass[i]) ; cntpass++ ;
               std::cout<<"\n rec Uno its pass_q pass_act "<<MapUnoToPass[i]<<" "<<pass_q[MapUnoToPass[i]]<< " "<<pass_act[MapUnoToPass[i]] ;
               RS_LOG(LA_AGENT, "\n rec Uno its pass_q pass_act "<<MapUnoToPass[i]<<" "<<pass_q[MapUnoToPass[i]]<< " "<<pass_act[MapUnoToPass[i]]) ;

               if(  isinf(pass_q[MapUnoToPass[i]]) ) {
            	   RS_LOG(LA_AGENT, "infinity ") ; exit(0) ;
               }
    		   if (test_qval <= pass_q[MapUnoToPass[i]] )  { test_qval = pass_q[MapUnoToPass[i]] ; test_qval_ind = i;
    		       		   }  RS_LOG(LA_AGENT, " index,  UNo , test qval and test_qval_ind "<<i<<" "<<MapUnoToPass[i]<<" "<<
    				   test_qval<<" "<<test_qval_ind) ;

    	   }
       }
       if (cntpass == 0 )
       {
//        Point    ballp = ballView->getPosition().getPoint() ;
//    	   DashToPoint dtp(ballp);
//    	   ServerCommand *scmddtp =  dynamic_cast<ServerCommand*>(dtp.generateStep().getNextCommand()) ;
    	   turnAroundBall();
    	   if(turnscmd1 != 0 )
    	   {    	   actuatorInterface->addToPlan(turnscmd1) ; }
    	   else { RS_LOG( LA_AGENT," turnscmd1 = 0 ") ; }
    	   if(turnscmd2 != 0)
    	   {  actuatorInterface->addToPlan(turnscmd2) ;} else { RS_LOG( LA_AGENT," turnscmd2 = 0 ") ; }

    	   RS_LOG(LA_AGENT, "turn around the ball  since no team mate is visible ") ;
    	   PREVTIME= CURRTIME ; return  true;
       }

       std::cout<<"\n completed all pass modules  maxqvalue and the maxq pass module"<< test_qval<<" "<<test_qval_ind;
       RS_LOG(LA_AGENT,"\n completed all pass modules  maxqvalue and the maxq pass module"<< test_qval<<" "<<test_qval_ind ) ;

       int map_ind = 0 ;  //mapping to pass no to Uno

       if(CURRTIME%5 == 0 and greedy == false ) {  // to process the random actions

         	    	int randno = std::rand();
         	    	std::cout<<"\n the random no for selecting a random action of four passM "<<randno ;
         	    	RS_LOG(LA_AGENT,"\n the random no for selecting a random action of four passM "<<randno ) ;
         	    	  switch(randno%4 + 1)
         	    	    	   {
         	    	    	   case 1 :  {  if (gscmd_1 != 0)  actuatorInterface->addToPlan(gscmd_1 ) ; else { std::cout<<"\n selected action is null" ; RS_LOG(LA_AGENT, "\n selected action is null") ; }
         	    	    	   	   	   	   	if (gscmd2_1 !=0 ) actuatorInterface->addToPlan(gscmd2_1 ) ; else { std::cout<<"\n selected action is null" ;  RS_LOG(LA_AGENT, "\n selected action is null") ;} break ;  }
         	    	    	   case 2:   {  if (gscmd_2 != 0)  actuatorInterface->addToPlan(gscmd_2 ) ; else { std::cout<<"\n selected action is null" ; RS_LOG(LA_AGENT, "\n selected action is null") ;}
         	    	    	   	   	   	   if (gscmd2_2 !=0 ) actuatorInterface->addToPlan(gscmd2_2 ) ;  else { std::cout<<"\n selected action is null" ; RS_LOG(LA_AGENT, "\n selected action is null") ;}  break ;}
         	    	    	   case 3: {  if (gscmd_3 != 0)  actuatorInterface->addToPlan(gscmd_3 ) ; else { std::cout<<"\n selected action is null" ; RS_LOG(LA_AGENT, "\n selected action is null") ;}
         	    		   	   	   if (gscmd2_3 !=0 ) actuatorInterface->addToPlan(gscmd2_3 ) ;   else { std::cout<<"\n selected action is null" ; RS_LOG(LA_AGENT, "\n selected action is null") ;}   break ;}
         	    	    	   case 4:   {  if (gscmd_4 != 0)  actuatorInterface->addToPlan(gscmd_4 ) ; else {std::cout<<"\n selected action is null" ; RS_LOG(LA_AGENT, "\n selected action is null") ;}
         	    	    	       	   	   	   	   if (gscmd2_4 !=0 ) actuatorInterface->addToPlan(gscmd2_4 ) ;   else { std::cout<<"\n selected action is null" ; RS_LOG(LA_AGENT, "\n selected action is null") ;}  break ;}

         	    	    	   }  // switch



         	    }

       else  {
       for (int i=1 ; i<=4 ; i++)
       {


    	   if ( teamm[MapUnoToPass[i]].getPosition().isKnown())
    	   {
    	   if (i== test_qval_ind ) {

    	   switch(i)
    	   {
    	   case 1 :  {  if (gscmd_1 != 0)  {  actuatorInterface->addToPlan(gscmd_1 )  ; std::cout<<"\n executing case 1 of greedy passmodules " ;
    	    RS_LOG(LA_AGENT, "\n executing case 1 of greedy passmodules ") ;
    	    }
    	   	   	   	   	if (gscmd2_1 !=0 ) { actuatorInterface->addToPlan(gscmd2_1 ) ;
    	   	   	   	   		std::cout<<"\n executing case 1 of greedy passmodules " ;
    	   	   	   	   	RS_LOG(LA_AGENT, "\n executing case 1 of greedy passmodules " ) ;}
    	   	   	  std::cout<<"\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]] ;
    	   	   	  RS_LOG(LA_AGENT,"\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]] ) ;
    	   	   	   	   	  if(gscmd_1 == 0 and gscmd2_1 == 0) { std::cout<<"\n COMMANDS  PASS1 have null values";
    	   	   	   	   	    RS_LOG(LA_AGENT,"\n COMMANDS  PASS1 have null values" ) ; //exit(0) ;
    	   	   	   	   	    }
    	   	   	   	   	break ;  }

    	   case 2:   {  if (gscmd_2 != 0)  { actuatorInterface->addToPlan(gscmd_2 ) ;
    	   std::cout<<"\n executing case 2 of greedy passmodules " ;
    	   RS_LOG(LA_AGENT,"\n executing case 2 of greedy passmodules " ) ;
    	   std::cout<<"\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]] ;
    	   RS_LOG(LA_AGENT,"\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]] ) ;
    	   }
    	   	   	   	   if (gscmd2_2 !=0 )  { actuatorInterface->addToPlan(gscmd2_2 ) ;
    	   	   	   	   std::cout<<"\n executing case 2 of greedy passmodules " ;
    	   	   	   	   RS_LOG(LA_AGENT, "\n executing case 2 of greedy passmodules ") ;
    	   	   	   	     }
    	   	   	 std::cout<<"\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]] ;
    	   	   	 RS_LOG(LA_AGENT, "\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]]) ;
    	   	   	   	   if(gscmd_2 ==0 and gscmd2_2 ==0) { std::cout<<"\n COMMANDS PASS2 have null values";
    	   	   	   	    RS_LOG(LA_AGENT,"\n COMMANDS PASS2 have null values");  //exit(0) ;
    	   	   	   	    } break ;}

    	   case 3: {  if (gscmd_3 != 0) { actuatorInterface->addToPlan(gscmd_3 ) ;
    	   std::cout<<"\n executing case 3 of greedy passmodules " ;
    	   RS_LOG(LA_AGENT,"\n executing case 3 of greedy passmodules "  ) ;
    	   std::cout<<"\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]] ;
    	   RS_LOG(LA_AGENT,"\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]] ) ;
    	   }
	   	   	   if (gscmd2_3 !=0 ) { actuatorInterface->addToPlan(gscmd2_3 ) ;
	   	   	   std::cout<<"\n executing case 3 of greedy passmodules " ;
	   	   	   	   	   	   RS_LOG(LA_AGENT, "\n executing case 3 of greedy passmodules ") ;}
	   	    std::cout<<"\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]] ;
	   	    RS_LOG(LA_AGENT,"\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]] ) ;
	   	   	   if(gscmd_3 ==0 and gscmd2_3 ==0)
	   	   	   { std::cout<<"\n COMMANDS pass3 have null values";
	   	   	     RS_LOG(LA_AGENT,"\n COMMANDS pass3 have null values") ; //exit(0) ;
	   	   	     }    break ;}

    	   case 4:   {  if (gscmd_4 != 0){  actuatorInterface->addToPlan(gscmd_4 ) ;
    	   std::cout<<"\n executing case 4 of greedy passmodules " ;
    	   RS_LOG(LA_AGENT, "\n executing case 4 of greedy passmodules ") ;
    	   std::cout<<"\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]] ;
    	   RS_LOG(LA_AGENT,"\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]] ); }
    	       	   	   	   	   if (gscmd2_4 !=0 ) { actuatorInterface->addToPlan(gscmd2_4 ) ;
    	       	   	   	   	   std::cout<<"\n executing case 4 of greedy passmodules " ;
                               RS_LOG(LA_AGENT,"\n executing case 4 of greedy passmodules " ); }
    	       	   	   	 std::cout<<"\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]] ;
    	       	   	   	 RS_LOG(LA_AGENT,"\n UNo, pass act type by"<<MapUnoToPass[i]<<" "<<pass_act[MapUnoToPass[i]] ) ;
    	       	   	   	   	   if(gscmd_3 ==0 and gscmd2_3 ==0) {
    	       	   	   	   		   std::cout<<"\n COMMANDS pass3 have null values";
    	       	   	   	   		   RS_LOG(LA_AGENT, "\n COMMANDS pass3 have null values") ;
    	       	   	   	   		  // exit(0) ;
    	       	   	   	   		   }
    	       	   	   	   		   break ;}

    	   }  // switch


    	      if (pass_act[MapUnoToPass[i]] == 0 ) { RS_LOG(LA_AGENT, "pass_act[MapUnoToPass] = 0 ") ; return  true ; }
    	      // if (gameView->getPlayMode() != PM_PLAY_ON ) {  RS_LOG(LA_AGENT, " playmode is not play on , so the CMDR is not updated" );
    	      // return true  ; }

    	      cmdr[cmdrind].command_type = pass_act[MapUnoToPass[i]] ;
    	      cmdr[cmdrind].rec_Uno = MapUnoToPass[i] ;
    	      cmdr[cmdrind].Q_status = false ;
    	      cmdr[cmdrind].theta1 = rec_rtheta1[MapUnoToPass[i]] ;
    	      cmdr[cmdrind].theta2 = rec_rtheta2[MapUnoToPass[i]] ;
    	      cmdr[cmdrind].ratio1 = rec_rratio1[MapUnoToPass[i]] ;
    	      cmdr[cmdrind].ratio2 = rec_rratio2[MapUnoToPass[i]] ;
    	      cmdr[cmdrind].theta1val = rec_theta1[MapUnoToPass[i]] ;
    	      cmdr[cmdrind].theta2val = rec_theta2[MapUnoToPass[i]] ;
    	      cmdr[cmdrind].rec_pos = teamm[MapUnoToPass[i]].getPosition().getPoint() ;
    	      if (ballView->getSpeedVector().isKnown()) {
    	      cmdr[cmdrind].ballSpeedVector = ballView->getSpeedVector().getVector() ; }
    	      cmdr[cmdrind].time = CURRTIME ;
    	       //cmdrind++ ;

    	      RS_LOG( LA_AGENT, "CMDR actionrecord "<<cmdr[cmdrind].time <<" \n recUno"<<cmdr[cmdrind].rec_Uno <<
    	     	  	  	    	    		  " cmdtype " <<cmdr[cmdrind].command_type <<" Qstatus "<<cmdr[cmdrind].Q_status
    	     	  	  	    	    		  <<" theta1 "<<cmdr[cmdrind].theta1<<" theta2 "<<cmdr[cmdrind].theta2<<" ratio1 "<<cmdr[cmdrind].ratio1<<
    	     	  	  	    	    		  " ratio2 "<<cmdr[cmdrind].ratio2<<" theta1val "<< cmdr[cmdrind].theta1val<<" theta2val"<< cmdr[cmdrind].theta2val
    	     	  	  	    	    		  <<" ballspeedvec "<<cmdr[cmdrind].ballSpeedVector<<" rec pos "<<cmdr[cmdrind].rec_pos) ;
    	      cmdrind++ ;
       actionstatus = true ;
    	   }  // if test

    	   else {
//
//    	   map_ind = MapUnoToPass[i] ;  // mapping to pass no to Uno
//
//    	   if(map_ind==0) { std::cout<<"\n error the unable to map to a correct receiver" ;
//    	    RS_LOG(LA_AGENT,"\n error the unable to map to a correct receiver" ) ;
//    	   }
//
//    	   Qtab[rec_rtheta1[map_ind]*18*16 + rec_rtheta2[map_ind]*16 + rec_rratio1[map_ind]*4 + rec_rratio2[map_ind]][pass_act[map_ind]]
//    	                    =  alph* Qtab[rec_rtheta1[map_ind]*18*16 + rec_rtheta2[map_ind]*16 + rec_rratio1[map_ind]*4 + rec_rratio2[map_ind]][pass_act[map_ind]]
//    	                                  + (1-alph)* pass_q[map_ind] ;
//
//    	   std::cout<<"\n q pred update " ;
//    	   RS_LOG(LA_AGENT,"\n q pred update "  ) ;
    	   }     // else


       }  // if teamm

       } // for
        std::cout<<"\n out of for loop" ;
        RS_LOG(LA_AGENT,"\n out of for loop" ) ;

       } //  else of if for currtime%5 and greedy==false

      }

    PREVTIME = CURRTIME ;
    CURRTIME = TIME.getT() ;
     if (CURRTIME-PREVTIME > 0) { std::cout<<"CURRTIME-PREVTIME > 0"  ;
       RS_LOG(LA_AGENT,"CURRTIME-PREVTIME > 0" ); exit(0);}
  }
  else if ( CURRTIME > PREVTIME  and amIClosest == true  ) {

        std::cout<<" in currtime > prevtime and amIclosest = true " ;
        RS_LOG(LA_AGENT, " in currtime > prevtime and amIclosest = true ") ;
	  if (ballView->getRelativeDirection().isKnown()) {
	      			if (abs(ballView->getRelativeDirection().getDeg()) > 2) {
	      				turnBodyToPoint.setPosition(ballView->getPosition().getPoint());
	      				cmd = turnBodyToPoint.generateStep().getNextCommand();
	      				scmd = dynamic_cast<ServerCommand*>(cmd);
	      				actuatorInterface->addToPlan(scmd) ;
	      				cmdty = "TURNBODYTOPOINT" ;
	      				RS_LOG(LA_AGENT, "turn body to point executed when amiclosest") ;
	      				PREVTIME = CURRTIME ;
	      				return true  ;
	      			} }

	  Point ballp = ballView->getPosition().getPoint();
	        DashToPoint dtp(ballp);
	  			//dtp.setPosition(ballp);
	  			cmd = dtp.generateStep().getNextCommand();
	  			scmd = dynamic_cast<ServerCommand*>(cmd);
	  			if(scmd != 0) {
	  			actuatorInterface->addToPlan(scmd) ;
	  			std::cout<<"\n dash to ball command executed" ;
	  			RS_LOG(LA_AGENT, "\n dash to ball command executed") ;}
	  			else {  std::cout<<"\n dash to ball command has NULL value " ;
	  			 RS_LOG(LA_AGENT, "\n dash to ball command has NULL value " );}

	  			cmdty = "DASHTOPoint" ;
	  			PREVTIME = CURRTIME ;
	  			CURRTIME = TIME.getT() ;
	  			     if (CURRTIME-PREVTIME > 0 and CURRTIME != 0 ) {
	  			    	 std::cout<<"exiting because CURRTIME-PREVTIME > 0 " ;
	  			    	 RS_LOG(LA_AGENT,"exiting because CURRTIME-PREVTIME > 0 ") ; exit(0); }
	  			     actionstatus = true ;

  }
  else if (CURRTIME > PREVTIME )
  {

	  std::cout<<" in currtime > prevtime " ;
	 	         RS_LOG(LA_AGENT, " in currtime > prevtime ") ;


	 	         float relang[3 ] ; for (int i =0 ; i< 3 ; i++) { relang[3] = -1000 ;}
	 	         		  	  	  	  	   float agentrelang = ballView->getPosition().getPoint().getDirectionTo(agentView->getPosition().getPoint()).getDeg() ;
	 	         		  	  	  	  	   int cntang =0 ; float dashang = -1000 ;
	 	   	  for (int i=0 ; i<4 ;i++)
	 	   	  		              {
	 	   	  		            	  if (teamm[MapUnoToPass[i]].getPosition().isKnown() and MapUnoToPass[i] != minballdistUno )
	 	   	  		            	   {
	 	   	  		            		   relang[i] =  ballView->getPosition().getPoint().getDirectionTo(teamm[MapUnoToPass[i]].getPosition().getPoint()).getDeg()  ;
	 	   	  		            		   RS_LOG(LA_AGENT, "ball relative direction of team mate"<<relang[i]) ;
	 	   	  		            		   if (agentrelang >  relang[i]) cntang++ ;
	 	   	  		                  	   }
	 	   	  		            	  else continue ;

	 	   	  		              }

	 	   	  		              	  RS_LOG(LA_AGENT, "cnt ang "<<cntang ) ;

	 	   	  		              switch((std::rand())%4)
	 	   	  		              {  case 0 :  {   dashang = -45; break ;     }
	 	   	  		              	 case 1 : { dashang = 135 ; break ; }
	 	   	  		              	 case 2 : { dashang = 45 ; break ;}
	 	   	  		              	 case 3 : { dashang = - 135 ; break ; }
	 	   	  		                }
	 	   	  		              	 Point dashp1 ;
	 	   	  		              	 if(dashang == -1000){ RS_LOG(LA_AGENT,"dash angle = -1000"); exit(0) ;}
	 	   	  		              Point ballp1 = ballView->getPosition().getPoint();
	 	   	  		              if( teamm[minballdistUno].getPosition().isKnown())
	 	   	  		              {
	 	   	  		            	  	  RS_LOG(LA_AGENT, "teamm minballdistUno position is known ") ;
	 	   	  		            	  if(teamm[minballdistUno].getBodyDirection().isKnown())
	 	   	  		            	  {

	 	   	  		            		  RS_LOG(LA_AGENT, " teamm minballdistUno body direction is known ") ;
	 	   	  		            		dashp1 =  Point(ballView->getPosition().getPoint().getX() + 15*cos( teamm[minballdistUno].getBodyDirection().getAngle().getDeg() + dashang) ,
	 	   	  		            			   	  		            		ballView->getPosition().getPoint().getX() +15*sin( teamm[minballdistUno].getBodyDirection().getAngle().getDeg() + dashang)) ;

	 	   	  		            	  }
	 	   	  		              else if(ballView->getSpeedVector().isKnown())
	 	   	  		            	  {

	 	   	  		            	  RS_LOG(LA_AGENT, " ballspeedvector is known but not team minballdistuno body diretion ") ;
	 	   	  		              dashp1 =  Point(ballView->getPosition().getPoint().getX() + 15*cos( ballView->getSpeedVector().getAngle().getValue() + dashang) ,
	 	   	  		            		ballView->getPosition().getPoint().getX() +15*sin( ballView->getSpeedVector().getAngle().getValue() + dashang)) ;
	 	   	  		            	  }
	 	   	  		            	  else
	 	   	  		            	  {

	 	   	  		            		  RS_LOG(LA_AGENT," both teamm minballdistUno direction and ball speed vector is not known ") ;
	 	   	  		            		dashp1 =  Point(ballView->getPosition().getPoint().getX() + 15*cos(  dashang) ,
	 	   	  		            			ballView->getPosition().getPoint().getX() +15*sin(  dashang)) ;

	 	   	  		            	  }
	 	   	  		            //   Point dashplastdisp =  Point(ballp1.getX() + 15*cos(lastdispersedashang) , ballp1.getY()+15*sin(lastdispersedashang)) ;

	 	   	  		              }
	 	   	  		              RS_LOG(LA_AGENT, " point ballp1 , dashp, dashplastdip"<<ballp1<<" "<<dashp1 ) ;// <<" "<<dashplastdisp) ;

	 	  // if (ballView->getRelativeDirection().isKnown()) {
	 	   //   			if (abs(ballView->getRelativeDirection().getDeg()) > 5  ) {

	 	   	  		         if( ballView->getPosition().getPoint().getDistanceTo(agentView->getPosition().getPoint()) < 15
	 	   	  		        		 and agentView->getBodyDirection().isKnown() and agentView->getPosition().isKnown())
	 	   	  		         {
	 	   	  		        	 if( abs(agentView->getPosition().getPoint().getDirectionTo(dashp1).getDeg() - agentView->getBodyDirection().getAngle().getDeg()) > 10 and
	 	   	  		        			 (360 - abs(agentView->getPosition().getPoint().getDirectionTo(dashp1).getDeg() - agentView->getBodyDirection().getAngle().getDeg()) > 10) )
	 	   	  		             {
	 	      				RS_LOG(LA_AGENT, " in turnbody to point when ball dist less than 10  and the relative angle between agent and dashp is more than 10 ") ;
	 	      				 TurnBodyToPoint tbtp(dashp1);
	 	      				scmd = dynamic_cast<ServerCommand*>(tbtp.generateStep().getNextCommand());
	 	      				actuatorInterface->addToPlan(scmd) ; }

	 	      				// else  {
	 	      					RS_LOG(LA_AGENT, "the relative angle between agent and dashp is less than 10 ") ;
	 	      				ServerCommand *testscmd=0 ;
	 	      				for (int i=0 ; i< 5 ; i++)
	 	      				{
	 	      					testscmd =  new DashCommand(100,agentView->getPosition().getPoint().getDirectionTo(dashp1).getDeg() - agentView->getBodyDirection().getDeg() ) ;
	 	      					vscmd.push_back(testscmd) ;
	 	      				}
	 	      				cmdty = "TURNBODYTOPOINT" ;
	 	      				RS_LOG(LA_AGENT, "turn body to point when  closest to ball ") ;
	 	      				PREVTIME =CURRTIME ; return  true ;
	 	      		//	}

	   	  	  	  	  	  }
	              // } //   if (ballView->getRelativeDirection().isKnown())



	 //	  if( ballView->getPosition().getPoint().getDistanceTo(agentView->getPosition().getPoint()) < 15 )
	 //					  {
	 //
	 //		  	  	  	  	  RS_LOG(LA_AGENT, "\n ballview get position get point getDistance ") ;
	 //		             //  lastdisperse = CURRTIME ;
	 //		                if (CURRTIME - lastdisperse > 20 ) {
	 //		                	if ( agentView->getBodyDirection().isKnown()) {
	 //		  	  	  	  scmd = new DashCommand (100, dashang  //-agentView->getBodyDirection().getDeg()
	 //		  	  	  			  ) ; }
	 //		                	else
	 //		                	{ scmd = new DashCommand (100, dashang ) ; }
	 //		  	  	  			 // DashCommand (100,  agentView->getPosition().getPoint().getDirectionTo(dashp).getDeg() -
	 //		  	  	  			  // agentView->getBodyDirection().getDeg()) ;
	 //		  	  	  	  lastdisperse = CURRTIME ; lastdispersedashang = dashang ;
	 //		                } else  {
	 //
	 //		                	if ( agentView->getBodyDirection().isKnown()) {
	 //		                	 scmd =  new DashCommand (100, lastdispersedashang  //-agentView->getBodyDirection().getDeg()
	 //		                			 ) ; }
	 //		                	else {
	 //		                		scmd =  new DashCommand (100, lastdispersedashang ) ;
	 //		                	}
	 //		                }
	 //
	 //		                	// DashCommand (100, agentView->getPosition().getPoint().getDirectionTo(dashplastdisp).getDeg()
	 //		                	//	- agentView->getBodyDirection().getDeg() ) ; }
	 //					   actuatorInterface->addToPlan(scmd) ;
	 //					    RS_LOG(LA_AGENT, "DASH backwards when not lcose ") ;
	 //					    PREVTIME =CURRTIME ; return true  ;
	 //					  }
	 	  else if (agentView->getBodyDirection().isKnown() and agentView->getPosition().isKnown()
			 )
	 	  {


	 		  RS_LOG(LA_AGENT, " in the else block ");
	 		  //scmd = new  DashCommand (100, ) ;

	 		  if(    abs(agentView->getBodyDirection().getAngle().getDeg() - agentView->getPosition().getPoint().getDirectionTo(ballp1).getDeg() ) > 2)
	 		  {
	 			  RS_LOG(LA_AGENT, "turning body towards the ball when ball is away more than 10 ") ;
	 		  TurnBodyToPoint  tbtp(ballp1);
	 		  	  scmd = dynamic_cast<ServerCommand*>(tbtp.generateStep().getNextCommand());
	 		  	  actuatorInterface->addToPlan(scmd) ;
	 		  	      				PREVTIME = CURRTIME ; return true ;
	 		  }
	 		//  Point ball = ballView->getPosition().getPoint();
	 		  else {
	 		 	   //  DashToPoint dtp(ballp1);
	 			  scmd = new DashCommand(100, agentView->getPosition().getPoint().getDirectionTo(ballp1).getDeg() - agentView->getBodyDirection().getAngle().getDeg() ) ;
	 		 	  			//scmd = dynamic_cast<ServerCommand*>(.generateStep().getNextCommand());

	 		 	  			RS_LOG(LA_AGENT, "agent pos "<<agentView->getPosition().getPoint()) ;
	 		 	  			if(scmd != 0) {
	 		 	  			actuatorInterface->addToPlan(scmd) ;
	 		 	  			RS_LOG(LA_AGENT, "dash  to ball forwards  when distance to ball is greater than 10 ") ;}
	 		 	  			PREVTIME = CURRTIME ; return true ;
	 		  	   //	   actuatorInterface->addToPlan(scmd) ;
	 		 	  			}
	 	  }

  }


  if (actionstatus == false ) { std::cout<<"exiting because action status is false " ;
  RS_LOG(LA_AGENT,"exiting because action status is false " );} //exit(0) ; }
  return true ;



//
//	  if ( ballView->getRelativeDistance() <= facts->SP_kickable_margin )
//	  {
//	  std::cout<<"\n the kick moment "<<float( goal_dir.getDeg() )- float (agentView->getBodyDirection().getAngle().getDeg() )
//			  << " kick maxmoment " << facts->SP_maxmoment;
//	  }

	 // if( turn_status == true ){ scmd =0 ;
	  //turnBodyToPoint.setPosition(ballView->getPosition().getPoint());
	   //   		scmd2 = dynamic_cast<ServerCommand*>(turnBodyToPoint.generateStep().getNextCommand()) ;
	    //  		cmdty = "SCMD2" ;

	  //}
	  // else

	  //CMDNO =1 =>  searchball, CMDNO=2 => kickball
	  //passer module action space  CMDno=3 turnaround , CMDNO = 4 =>GOFORWARD , CMDNO =5 GOBACKWARD ,  6 TURN HEAD CLOCKWISE




/*		  if (searchBall.applicable()) {
      RS_LOG ( LA_DECISION, "SearchBall" );
      cmd = searchBall.generateStep().getNextCommand();
      scmd = dynamic_cast<ServerCommand*>(cmd); cmdty = "SEARCH" ;
	  	  	  	  	  	  	  	  	  	  }
	  else if ( gameView->isKickAllowed() &&
	      ( ballView->getRelativeDistance() <= facts->SP_kickable_margin)   // and kick_status == true
	       and  (float( goal_dir.getDeg() )- float (agentView->getBodyDirection().getAngle().getDeg() ) < facts->SP_maxmoment
	       and  float (goal_dir.getDeg()) - 	float (agentView->getBodyDirection().getAngle().getDeg() ) > facts->SP_minmoment )

	  )
	      {
		  	  	  RS_LOG ( LA_DECISION, "Kicking" );
      // The ball is kickable, can we kick it to the ball.
      // Get the direction to the opponents goal.

       //AngleDegUE goal_dir = 20*(angleinc+1.0);
       //angleinc = angleinc+1.0 ;

      //Kick the ball towards the goal.


		  	  	  scmd = new KickCommand(50,(goal_dir -
		  	  	  agentView->getBodyDirection()).getAngle());
		  	  	  kick_status=false ;
		  	  	  cmdty = "kick" ;

      //scmd = new KickCommand(50, ( AngleDeg(angleinc*20) + agentView->getBodyDirection()).getAngle()) ;
      //angleinc = angleinc+1 ;
     // angleinc = angleinc - 18*floor(anngleinc/18) ;
      //if (angleinc >= 18 ){ angleinc= angleinc-18 ;}

      //std::cout <<"\n angleinc "<<angleinc ;
      // std::cin.get() ;
	      }
    else if ( gameView->isKickAllowed()  and
  	      ( ballView->getRelativeDistance() <= facts->SP_kickable_margin)   //  and kick_status == true
  	     and   ( float (goal_dir.getDeg()) - 	float (agentView->getBodyDirection().getAngle().getDeg() ) > facts->SP_maxmoment
  	      or    float (goal_dir.getDeg()) - 	float (agentView->getBodyDirection().getAngle().getDeg() ) < facts->SP_minmoment  ) )
    {

 //  TurnBodyToAbsoluteDirection   tbtad( agentView->getBodyDirection().getAngle() + 180)	 ;
  // scmd  = dynamic_cast<ServerCommand*>(tbtad.generateStep().getNextCommand()) ;
   // kick_status = true ;
    		if (CURRTIME > PREVTIME )
    			{	std::cout<<"\n \n Dash command executed " ;
    			std::cout<<"\n agent postition "<<agentView->getPosition().getPoint() ;
    			}

 // std::cin.get() ;
    		Point ball_pos = ballView->getPosition().getPoint();
    		AngleDeg  ang1= ball_pos.getVectorTo(agentView->getPosition().getPoint()).getAngle() ;
    		AngleDeg ang2 = ball_pos.getVectorTo(facts->getTheirGoal().getPosition()).getAngle() ;
    		float moment ;

    		if(ang1 < 0 ) ang1 = AngleDeg(360)+ang1 ;
    		if(ang2 < 0 ) ang2 = AngleDeg(360) +ang1 ;

    		if (CURRTIME > PREVTIME )  std::cout << "\n angle1 and angl2"<<ang1<<" " <<ang2 ;
    		if (abs(ang1-ang2) > 180 )
    			{   moment = -1*facts->SP_maxmoment ; }  else { moment = facts->SP_maxmoment ; }


   Point destPoint(ball_pos.getX() + 2*facts->SP_kickable_margin*cos( (ang1/abs(ang1))*AngleDeg(moment)+ ang1 ) ,
   	   ball_pos.getY() + 2*facts->SP_kickable_margin*sin( (ang1/abs(ang1))*AngleDeg(moment)+ ang1) ) ;

    	//	Point destPoint(ball_pos.getX() + 3*facts->SP_kickable_margin*cos( AngleDeg(90) + ang1 ) ,
    		//		ball_pos.getY() + 3*facts->SP_kickable_margin*sin( AngleDeg(90) + ang1) ) ;

    		if (CURRTIME > PREVTIME ) std::cout<< "\n ball_pos and dest point"<<ball_pos <<" "<<destPoint ;

    		if (CURRTIME > PREVTIME ) std::cout<<"\n vector angle with new location"<<(ball_pos.getVectorTo(destPoint).getAngle() -  ang2) ;
    		Point relativePoint = destPoint - agentView->getPosition().getPoint();
    		float  dashPower = agentView->getPowerForDash(relativePoint);

    		std::cout<<"\n  angle agent to dest  "<<agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()
    				<<"  body direction"<<agentView->getBodyDirection().getAngle().getDeg() ;
    		Vector  agenttodest(agentView->getPosition().getPoint(), destPoint) ;
    		std::cout<<" vector angle "<<agenttodest.getAngle() ;

    		float deg ;
    		if ( (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg() ) > 180)
    		{  deg = 360 - (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg())  ;}
    		else if (  (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg() )   < -180 )
    		{  deg = 360 + (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg()) ; }
    		else
    		{ deg = (agentView->getPosition().getPoint().getDirectionTo(destPoint).getDeg()  - agentView->getBodyDirection().getAngle().getDeg()) ; }

    		 scmd = new DashCommand( 3*dashPower,  deg );
    		  DashToPointDir  DTPD(scmd) ;
    		     scmd2 = dynamic_cast<ServerCommand*>(DTPD.generateStep().getNextCommand()) ;

    		 		 //  dashPower) ;
    		// turnBodyToPoint.setPosition(ballView->getPosition().getPoint());
    		// scmd2 = dynamic_cast<ServerCommand*>(turnBodyToPoint.generateStep().getNextCommand()) ;
    		          //  dashToPoint.setPosition(destPoint) ;
    		           // scmd = dynamic_cast<ServerCommand*>(dashToPoint.generateStep().getNextCommand()) ;
    		turn_status = true ;
    		cmdty="DASH and turn" ;

    	}
    else 	{
    	if (ballView->getRelativeDirection().isKnown()) {
    			if (abs(ballView->getRelativeDirection().getDeg()) > DASH_MAX_ANGLE) {
    				turnBodyToPoint.setPosition(ballView->getPosition().getPoint());
    				cmd = turnBodyToPoint.generateStep().getNextCommand();
    				scmd = dynamic_cast<ServerCommand*>(cmd);
    				cmdty = "TURNBODYTOPOINT" ;
    			}
	else {
			Point ball = ballView->getPosition().getPoint();
			dashToPoint.setPosition(ball);
			cmd = dashToPoint.generateStep().getNextCommand();
			scmd = dynamic_cast<ServerCommand*>(cmd);
			cmdty = "DASHTOPoint" ;
	}  // else
      }  // if iskwnown
    } // else

    if ( CURRTIME > PREVTIME ) {
      // Look at the ball




    	if( scmd!=0) {
     //  TurnNeckToBall turnNeckToBall(scmd);
      actuatorInterface->addToPlan(scmd);
     // actuatorInterface->addToPlan(turnNeckToBall.generateStep());
      scmd=0 ;
      std::cout<<"\n  scmd main command "<<cmdty ;

    	}
    	if(scmd2!=0)
    	{  actuatorInterface->addToPlan(scmd2);
    	scmd2=0;
    	}


    	//else {
    	//	// TurnNeckToBall turnNeckToBall(scmd2) ;
    	//actuatorInterface->addToPlan(scmd2);
    	//// actuatorInterface->addToPlan(turnNeckToBall.generateStep());
    	//scmd2=0 ; turn_status = false ;
    	// std::cout<<"\n  scmd2 sub  command " ;
    	//}



    	PREVTIME =CURRTIME ;
      // Send the commands to the actuators.


    }  // if PREVTIME
*/
    // Example of pointing.

    /*  if (agentView->getPosition().isKnown() && (say_counter == 5)) {
	RS_LOG ( LA_DECISION, "Pointing" );
	Vector v = agentView->getPosition().getVectorTo(facts->getTheirGoal().getPosition()).getVector();
	pointcmd = new PointToCommand(v);
	actuatorInterface->addToPlan(pointcmd);
	}
	else if (say_counter == 8) {
	RS_LOG ( LA_DECISION, "Pointing off" );
	pointcmd = new PointToCommand();
	actuatorInterface->addToPlan(pointcmd);
	}

	// Example of communication.

	if ( say_counter == 0 ) {
	RS_LOG ( LA_DECISION, "Talking" );
	saycmd = new SayCommand("Hello" + toString(aural_data));
	actuatorInterface->addToPlan(saycmd);
	say_counter = 9;
	} else {
	--say_counter;
	} */
  }  // else for playmode

  return true;
} // function

void FCFooDecision::onAuralCoachSensorData() {
  std::cerr << "I got " << agentView->getCoachMessage()
	    << " from the coach (trainer or non-CLang coach)" << std::endl;
}

void FCFooDecision::onAuralRefereeSensorData() {
  std::cerr << "I got message from the referee." << std::endl;
}

void FCFooDecision::onAuralPlayerSensorData() {
  if (agentView->getTeammateMessageDirection().isKnown()) {
    std::cerr << "I got " << agentView->getTeammateMessage()
	      << " from teammate nr " << agentView->getTeammateSpeaker()
	      << " from direction " << agentView->getTeammateMessageDirection()
	      << std::endl;
    if (agentView->getOpponentMessageDirection().isKnown()) {
      std::cerr << " and " << std::endl;
    }
  }
  if (agentView->getOpponentMessageDirection().isKnown()) {
    std::cerr << "I got " << agentView->getOpponentMessage()
	      << " from an opponent from direction "
	      << agentView->getOpponentMessageDirection()
	      << std::endl;
  }
  ++aural_data;
}

void FCFooDecision::onAuralSelfSensorData() {
  std::cerr << "I got " << agentView->getOwnMessage()
	    << " from myself" << std::endl;
  ++aural_data;
}

void FCFooDecision::onInit() {
  // Position the players with some distance at the beginning of game.
  Point movePoint = Point(-10,-10);
  if (agentView->getUniformNumber().isKnown()) {
    UInt nr = agentView->getUniformNumber().getValue();
    switch (nr) {
    case 1:
      movePoint = Point(-10, 0);
      break;
    case 2:
      movePoint = Point(-5, -15);
      break;
    case 3:
      movePoint = Point(-5, 15);
      break;
    case 4:
      movePoint = Point(-25, 10);
      break;
    case 5:
      movePoint = Point(-25, -10);
      break;
    case 6:
      movePoint = Point(-25, 20);
      break;
    case 7:
      movePoint = Point(-25, -20);
      break;
    case 8:
      movePoint = Point(-45, 10);
      break;
    case 9:
      movePoint = Point(-25, -10);
      break;
    case 10:
      movePoint = Point(-25, 20);
      break;
    case 11:
      movePoint = Point(-25, -20);
      break;
    default:
      movePoint = Point(-10,-10);
    }
  }
  MoveCommand* move_cmd = new MoveCommand(movePoint);
  actuatorInterface->addToPlan(move_cmd);

  // Tell server (and coach) what coachlanguage versions we're supporting.
  ClangVersionCommand* clangvCommand = new ClangVersionCommand(facts->CP_clang_version_min,
							       facts->CP_clang_version_max);
  actuatorInterface->addToPlan(clangvCommand);
}

void FCFooDecision::onCommandWarning() {
  decide();
}

void FCFooDecision::onDelayedActions() {
  if (facts->CP_ticks_before_command_warning > facts->CP_min_ticks_before_sending_command) {
    SetTicksBeforeCommandWarning* st =
      new SetTicksBeforeCommandWarning(facts->CP_ticks_before_command_warning - 1);
    RS_LOG(LA_DECISION, "Responding to server command hole by lowering " <<
	   "'ticks_before_command_warning' to " <<
	   toString((facts->CP_ticks_before_command_warning - 1)));
    actuatorInterface->addToPlan(st);
  }
}

RS_END_NAMESPACE