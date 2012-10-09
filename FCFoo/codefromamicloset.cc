 else if ( CURRTIME > PREVTIME  and amIClosest == true ) {


	  if (ballView->getRelativeDirection().isKnown() ) {
	      			if (abs(ballView->getRelativeDirection().getDeg()) > 0 ) {
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
	  			if(scmd != 0) {
	  			actuatorInterface->addToPlan(scmd) ;
	  			std::cout<<"\n dash to ball command executed" ;
	  			RS_LOG(LA_AGENT, "\n dash to ball command executed") ;}
	  			else {  std::cout<<"\n dash to ball command has NULL value " ;
	  			 RS_LOG(LA_AGENT, "\n dash to ball command has NULL value " );}

	  			cmdty = "DASHTOPoint" ;
	  }
	  } else
	  {
		  Point ball = ballView->getPosition().getPoint();
		 	  			dashToPoint.setPosition(ball);
		 	  			cmd = dashToPoint.generateStep().getNextCommand();
		 	  			scmd = dynamic_cast<ServerCommand*>(cmd);
		 	  			if(scmd != 0) {
		 	  			actuatorInterface->addToPlan(scmd) ;
		 	  			std::cout<<"\n dash to ball command executed" ;
		 	  			RS_LOG(LA_AGENT, "\n dash to ball command executed") ;}
		 	  			else {  std::cout<<"\n dash to ball command has NULL value " ;
		 	  			 RS_LOG(LA_AGENT, "\n dash to ball command has NULL value " );}

		 	  			cmdty = "DASHTOPoint" ;
	  }
	  			PREVTIME = CURRTIME ;
	  			CURRTIME = TIME.getT() ;
	  			     if (CURRTIME-PREVTIME > 0 and CURRTIME != 0 ) {
	  			    	 std::cout<<"exiting because CURRTIME-PREVTIME > 0 " ;
	  			    	 RS_LOG(LA_AGENT,"exiting because CURRTIME-PREVTIME > 0 ") ; exit(0); }
	  			     actionstatus = true ;

  }
  else if (CURRTIME > PREVTIME )
  {

	  if (ballView->getRelativeDirection().isKnown()) {
	      			if (abs(ballView->getRelativeDirection().getDeg()) > 0 ) {
	      				turnBodyToPoint.setPosition(ballView->getPosition().getPoint());
	      				cmd = turnBodyToPoint.generateStep().getNextCommand();
	      				scmd = dynamic_cast<ServerCommand*>(cmd);
	      				cmdty = "TURNBODYTOPOINT" ;
	      			}
	  else
	  if( ballView->getPosition().getPoint().getDistanceTo(agentView->getPosition().getPoint()) < 10 )
					  {    scmd = new  DashCommand (10, -180) ;
					   actuatorInterface->addToPlan(scmd) ;
					  }

	  else
	  {
		  //scmd = new  DashCommand (100, ) ;
		  Point ball = ballView->getPosition().getPoint();
		 	  			dashToPoint.setPosition(ball);
		 	  			cmd = dashToPoint.generateStep().getNextCommand();
		 	  			scmd = dynamic_cast<ServerCommand*>(cmd);
		 	  			if(scmd != 0) {
		 	  			actuatorInterface->addToPlan(scmd) ; }
		  	   //	   actuatorInterface->addToPlan(scmd) ;
	  }
	  }
	  else {
		  if( ballView->getPosition().getPoint().getDistanceTo(agentView->getPosition().getPoint()) < 10 )
		  					  {    scmd = new  DashCommand (10, -180) ;
		  					   actuatorInterface->addToPlan(scmd) ;
		  					  }

		  	  else
		  	  {
		  		  //scmd = new  DashCommand (100, ) ;
		  		  Point ball = ballView->getPosition().getPoint();
		  		 	  			dashToPoint.setPosition(ball);
		  		 	  			cmd = dashToPoint.generateStep().getNextCommand();
		  		 	  			scmd = dynamic_cast<ServerCommand*>(cmd);
		  		 	  			if(scmd != 0) {
		  		 	  			actuatorInterface->addToPlan(scmd) ; }

	  }
	  }

  }

