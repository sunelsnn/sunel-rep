
	  if ( CURRTIME != PREVTIME )
	  {
	  //Position a ;

	 /*  if ( ballView->getPosition().isKnown())
	  	  	  	  {
	  	  	  TurnBodyToPoint TBTP (ballView->getPosition().getPoint()) ;
	  	  	  ServerCommand* scmd = dynamic_cast <ServerCommand*> (TBTP.generateStep().getNextCommand()) ;
	  	  	  DashToPointDir  DTPD( ballView->getPosition().getPoint(), scmd) ;
	  	  	 actuatorInterface->addToPlan(scmd) ;
	  	  	  actuatorInterface->addToPlan(DTPD.generateStep().getNextCommand()) ;
	  	          std::cout<< "commands are stacked in queue DASHTOPOINTDIR  "<<"\n\n\n" ;
	  	  	  	  } else
	  	  	  	  {

	  	  	  	  */   // join this code after testing multiple neck commands
	         //  std::cout<<" hit the key \n" ; std::cin.get() ;
	             std::cout<<"\n Neck direction " <<agentView->getNeckDirection().getDeg() ;
	              std::cout<<"\n body direction" << agentView->getBodyDirection().getDeg() ;

	              // std::cout<<" hit the key \n" ;    std::cin.get() ;
	  	  		        ServerCommand *scmd3=0, *scmd2=0, *scmd4=0, *scmd5=0 ;
	  	  		        TurnNeckToAbsoluteDirection TNTa( AngleDeg     //(0), 0) ;
	  	  		        		(agentView->getNeckDirection().getDeg() + 1  ) 	, 0	) ;
	  	  		       scmd3 = dynamic_cast <ServerCommand*> (TNTa.generateStep().getNextCommand()) ;
	  	  		//TurnNeckToBall turnNeckToBall(scmd3);
	  	  		       //AlignNeckToBody  antb123 ;
	  	  		   //  scmd4 = dynamic_cast <ServerCommand*> (antb.generateStep().getNextCommand()) ;

	  	  		    TurnNeckToAbsoluteDirection TNTb( AngleDeg
	  	         		( agentView->getNeckDirection().getDeg() + 1  )		,       scmd3		) ;
	  	  		         scmd2 = dynamic_cast <ServerCommand*> (TNTb.generateStep().getNextCommand()) ;
	  	  		      // TurnNeckToAbsoluteDirection TNTc( AngleDeg
	  	  		   // 	  		        		( 40) 	,     scmd2	) ;
	  	  		    		//       scmd4 = dynamic_cast <ServerCommand*> (TNTc.generateStep().getNextCommand()) ;


	  	  		     	// 	TurnNeckToAbsoluteDirection TNTd( AngleDeg
	  	  		     	  	//	  	  			  		        		( 60 ) ,     scmd4) ;
	  	  		     	 // scmd5 = dynamic_cast <ServerCommand*> (TNTd.generateStep().getNextCommand()) ;

	  	  		     	  		       //  AlignNeckToBody  antba123();
	  	  		     	    //  scmd5 = dynamic_cast <ServerCommand*> (antba.generateStep().getNextCommand()) ;


	  	  		//ServerCommand* scmd2 = dynamic_cast <ServerCommand*> (turnNeckToBall.generateStep().getNextCommand()) ;
	  	  		  // actuatorInterface->addToPlan(scmd3) ;
	  	  	// actuatorInterface->addToPlan(antb123.generatePlan()) ;
	  	  		actuatorInterface->addToPlan(scmd3);
	  	  		actuatorInterface->addToPlan(scmd2) ;
	  	  		// actuatorInterface->addToPlan(scmd4) ;
	  	  		// actuatorInterface->addToPlan(scmd5) ;
	  	  		// actuatorInterface->addToPlan(antba123.generatePlan()) ;

	  	  	  			 //actuatorInterface->addToPlan(scmd) ;
	  	  	  			 //actuatorInterface->addToPlan(DTPD.generateStep().getNextCommand()) ;
	  	  	  		        std::cout<< "commands are stacked in queue neck dirs  "<<"\n\n\n" ;




/////////////////// found duplicate extra snippet

	  	  	  	/*	if ( ballView->getPosition().isKnown()) {
	  	  	  		TurnBodyToPoint TBTP (ballView->getPosition().getPoint()) ;
	  	  	  		ServerCommand* scmd = dynamic_cast <ServerCommand*> (TBTP.generateStep().getNextCommand()) ;

	  	  	  		DashToPointDir  DTPD( ballView->getPosition().getPoint(), scmd) ;
	  	  	      // Send the commands to the actuators.

	  	  	      actuatorInterface->addToPlan(scmd);
	  	  	      actuatorInterface->addToPlan(DTPD.generateStep().getNextCommand()) ;
	  	  	  		}
	  	  	  		else { std::cout<< "ball position unknown"<<"\n" ;
	  	  	  				//std::cin.get() ;
	  	  	  		}

*/
	  	  	  	  // } open this bracket after testing multiple neck commands.

	  	  	  		        PREVTIME=CURRTIME ;
	  }

	  	  	  	return true ;


	  	  std::cout<<"commands after return"<<"\n\n\n" ;

