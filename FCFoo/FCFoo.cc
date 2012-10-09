/* -*- Mode: C++ -*-
 * $Id: FCFoo.cc,v 1.22 2005/08/13 13:32:57 frehe Exp $
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
 * Filename: FCFoo.cc
 * Unitname: Framework/example/FCFoo
 * $Revision: 1.22 $
 * Created by: Fredrik Heintz 1999-xx-xx
 * Last modified by $Author: frehe $ $Date: 2005/08/13 13:32:57 $
 *
 *
 * HISTORY
 * $Log: FCFoo.cc,v $
 * Revision 1.22  2005/08/13 13:32:57  frehe
 * Produce a logfile.
 *
 * Revision 1.21  2004/08/13 11:48:30  petan
 * Turned off logging, updated with better running
 *
 * Revision 1.20  2003/12/07 17:07:19  frehe
 * Print ball state in coach logfile.
 *
 * Revision 1.19  2003/11/26 07:59:03  frehe
 * Added a special logfile for the coach.
 *
 * Revision 1.18  2003/07/22 14:47:23  s02davro
 * Updated coach/trainer/player for testing new features
 *
 * Revision 1.17  2003/07/21 09:25:45  s02davro
 * Logging
 *
 * Revision 1.16  2002/12/07 17:25:10  s02davro
 * Added trainer
 *
 * Revision 1.15  2002/09/04 14:48:04  s02davro
 * Updated FCFoos desision making
 *
 * Revision 1.14  2002/09/03 10:59:24  s02davro
 * Minor update
 *
 * Revision 1.13  2002/08/31 15:17:16  s02davro
 * FCFoo now run coach with -coach option, changed the main loop
 *
 * Revision 1.12  2002/08/02 22:03:38  s02davro
 * Changed FCFoo to test the modifications done (WorldModelInterface, Errors ...)
 *
 * Revision 1.11  2002/01/15 17:20:19  frehe
 * Turned on logging of the sensors.
 *
 * Revision 1.10  2001/10/14 15:38:20  frehe
 * Changed the logging policies.
 *
 * Revision 1.9  2001/09/29 18:55:16  frehe
 * Removed TRUE, FALSE, and UNKNOWN.
 *
 * Revision 1.8  2001/09/01 23:54:53  frehe
 * Added some debug info.
 *
 * Revision 1.7  2001/08/29 16:31:19  frehe
 * Added some exception handling.
 *
 * Revision 1.6  2000/10/24 15:15:46  freheactuatorInterface->addToPlan(scmd4) ;
 * Made minor updates and tests.
 *
 * Revision 1.5  2000/10/11 18:40:29  frehe
 * Upgraded FCFoo.
 *
 * Revision 1.4  2000/10/04 11:57:03  frehe
 * Removed all the Makefile.in.
 *
 * Revision 1.3  2000/09/13 11:06:19  frehe
 * Fixed a bug in FCFoo that didn't read the command line.
 *
 * Revision 1.2  2000/09/05 21:12:54  frehe
 * Made FCFoo compile with RoboSoc 2.5.0
 *
 */

/**
 * @file FCFoo.cc
 * Implementation file for the example agent FCFoo.
 *
 * @par Unit:
 *      Framework/example/FCFoo
 * $Revision: 1.22 $
 * $Author: frehe $
 * $Date: 2005/08/13 13:32:57 $
 */


#include <fstream>

#include "framework_compiler_directives.h"
#include "view_constants.h"
#include "FrameworkAgent.h"
#include "WorldModelInterface.h"
#include "FCFooDecision.h"
#include "FCFooCoachDecision.h"
#include "FCFooTrainerDecision.h"
#include "LogStream.h"
#include "BasicSeeStrategy.h"
#include "BasicHearStrategy.h"
#include "BasicCommandStrategy.h"
#include "BasicSenseStrategy.h"
#include "BasicInitStrategy.h"
#include "BasicCoachMessageStrategy.h"
#include "BasicNewCycleStrategy.h"
#include "BasicCoachInformationStrategy.h"
#include "NewSeeStrategy.h"
#include "string_utils.h"
#include </usr/include/time.h>

RS_BEGIN_NAMESPACE


#if defined(RS_USE_ERROR) && !defined(RS_LOG_ERROR)
extern void rs_warning(const std::string& str,
		       const std::string& file,
		       int line)
{
  std::cerr << "WARNING: " << str
	    << " at line " << line 
	    << " in file " << file
	    << std::endl;
  RS_LOG (LA_WARNING, "WARINING: " << str);
}

extern void rs_error(const std::string& str,
		     const std::string& file,
		     int line)
{
  std::cerr << "ERROR: " << str
	    << " at line " << line 
	    << " in file " << file
	    << std::endl;
  RS_LOG (LA_ERROR, "ERROR: " << str);
}

extern void rs_fatal(const std::string& str,
		     const std::string& file,
		     int line)
{
  std::cerr << "FATAL: " << str
	    << " at line " << line 
	    << " in file " << file
	    << std::endl;
  RS_LOG (LA_FATAL, "ERROR: " << str);
  abort();
}
#endif

#if !defined(RS_USE_EXCEPTION) && !defined(RS_LOG_EXCEPTION)
extern void rs_throw(const std::string& exception,
		     const std::string& msg,
		     const std::string& file,
		     int line)
{
  std::cerr << "RAISED: " << exception << "(\"" << msg << "\")"
	    << " at line " << line 
	    << " in file " << file
	    << std::endl;
}
#endif

RS_END_NAMESPACE

int main(int argc, char** argv) {
#ifdef RS_USE_NAMESPACE
  using namespace RS_NAMESPACE;
#endif

//  struct tm
//  {
//    int tm_sec;                   /* Seconds.     [0-60] (1 leap second) */
//    int tm_min;                   /* Minutes.     [0-59] */
//    int tm_hour;                  /* Hours.       [0-23] */
//    int tm_mday;                  /* Day.         [1-31] */
//    int tm_mon;                   /* Month.       [0-11] */
//    int tm_year;                  /* Year - 1900.  */
//    int tm_wday;                  /* Day of week. [0-6] */
//    int tm_yday;                  /* Days in year.[0-365] */
//    int tm_isdst;                 /* DST.         [-1/0/1]*/
//
//  #ifdef  __USE_BSD


  try {
    std::cerr << "Initializing the world...\n";
    WorldFacts::nonConstInstance()->CP_team_name = "RoboSoc";
    WorldFacts::init(argc, argv);

    
    time_t *ttt = new time_t ;
      const  time_t tt123 = time(ttt) ;
      tm *localtime1 = localtime( &tt123) ;
      //std::cout<<"\n time m day "<<localtime1->tm_mday<<" " ;

    std::string lf_name, lf_name1;
    if (WorldFacts::instance()->SP_coach) {
      lf_name = "logfile-coach.txt";
    } else {
      lf_name = "logfile.txt"
	+ toString(WorldFacts::instance()->CP_clang_version_min);
    }

    lf_name1 = "logfile.txt."+ toString(localtime1->tm_year) + "." + toString(localtime1->tm_mon)+"." +
    		toString(localtime1->tm_mday)+"."+toString(localtime1->tm_hour)+"."+ toString(localtime1->tm_min)+"."+
    		 toString(localtime1->tm_sec);
    std::ofstream logFile1(lf_name.c_str());
    std::ofstream logFile2(lf_name1.c_str()) ;
    /*
    std::ofstream logFile2("commands.txt");
    std::ofstream logFile3("sensor_data.txt");
    std::ofstream logFile4("sensors.txt");
    std::ofstream coachLog("coachLog.txt");
    */
  
    LogStream *logStream = LogStream::instance();
    
    logStream->addLogArea(LA_ROBOSOC, LA_TOP, true, &std::cerr);
    logStream->addLogArea(LA_WARNING, LA_ROBOSOC, false, &logFile1,
			  true, &std::cerr);
    logStream->addLogArea(LA_ERROR, LA_ROBOSOC, false, &logFile1,
			  false, &std::cerr);
    logStream->addLogArea(LA_FATAL, LA_ROBOSOC, false, &logFile1,
			  false, &std::cerr);

    logStream->addLogArea(LA_ACTUATORS, LA_ROBOSOC, true, &logFile1);
    logStream->addLogArea(LA_CONTROLLER, LA_ROBOSOC, true, &logFile1);
    logStream->addLogArea(LA_SENSOR_DATA, LA_ROBOSOC, true, &logFile1);
    logStream->addLogArea(LA_SENSORS, LA_ROBOSOC, true, &logFile1);
    logStream->addLogArea(LA_SERVER_COMMANDS, LA_ROBOSOC, true, &logFile1);
    logStream->addLogArea(LA_STRATEGY, LA_ROBOSOC, true, &logFile1);
    logStream->addLogArea(LA_SENSOR_INTERFACE, LA_ROBOSOC, true, &logFile1);
    logStream->addLogArea(LA_DECISION, LA_ROBOSOC, true, &logFile1);
    logStream->addLogArea(LA_FRAMEWORK_AGENT, LA_ROBOSOC, true, &logFile1);
    logStream->addLogArea(LA_AGENT, LA_ROBOSOC, true, &logFile2);
    logStream->addLogArea(LA_SKILL, LA_ROBOSOC, true, &logFile1);
    logStream->addLogArea(LA_COACH, LA_ROBOSOC, true, &logFile1);
    logStream->addLogArea(LA_WORLDMODEL, LA_ROBOSOC, true, &logFile1);
    logStream->addLogArea(LA_TIME, LA_ROBOSOC, true, &logFile1);
    
    std::cerr << "Initializing the worldModelInterface...\n";
    WorldModelInterface *wmi = WorldModelInterface::nonConstInstance();
    
    std::cerr << "Setting worldModel update strategies...\n";
    wmi->setSeeStrategy(new NewSeeStrategy());
    wmi->setHearStrategy(new BasicHearStrategy());
    wmi->setCommandStrategy(new BasicCommandStrategy());
    wmi->setInitStrategy(new BasicInitStrategy());
    wmi->setSenseStrategy(new BasicSenseStrategy());
    wmi->setCoachMessageStrategy(new BasicCoachMessageStrategy());
    wmi->setNewCycleStrategy(new BasicNewCycleStrategy());
    wmi->setCoachInformationStrategy(new BasicCoachInformationStrategy());
    
    Decision* decision;
    
    std::cerr << "Starting decision...\n";
    if (WorldFacts::instance()->SP_coach) {
      std::cerr << "As a coach...\n";
      decision = new FCFooCoachDecision();
    }
    else if (WorldFacts::instance()->CP_trainer) {
      std::cerr << "As a trainer...\n";
      decision = new FCFooTrainerDecision();
    }
    else {
      std::cerr << "As a player...\n";
      decision = new FCFooDecision();
    }
    
    std::cerr << "Initializing the FrameworkAgent...\n";
    FrameworkAgent agent(decision);

    std::cerr << "Starting the agent...\n";
    agent.start();

  } catch (RSException &excpt) {
    std::cerr << "Caught a RoboSoc exception: " << excpt.What() << std::endl;
    return 1;
  } catch (std::exception &excpt) {
    std::cerr << "Caught a standard exception: " << excpt.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "Caught an unknown exception: " << std::endl;
    return 1;
  }
  
  return 0;
  
}


