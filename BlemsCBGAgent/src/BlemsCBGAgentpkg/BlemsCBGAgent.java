package edu.isi.blems.BlemsCBGAgent;

import java.io.BufferedReader;

import java.io.FileReader;
import java.io.FileWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date ;
import java.util.Hashtable;
import java.util.Timer;
import java.util.TimerTask;
import java.util.logging.Level;
import java.util.logging.Logger;

import edu.isi.blems.DirectBlemsAgent;
import edu.isi.blems.Reading;
import edu.isi.blems.ReadingTypes;
import edu.isi.blems.SensorRecord;


//***********************************************************************************************************************
//import edu.isi.blems.behavior.OccupancyEstimatorAgent.EstimateOccupancyTask;

// a room table with columns  room#,ipadd, lastudate model , no of features
// Test settings BlemsRaw <==> BlemsAgent DB and CBG <==> Blems DB and dont touch  or directly access tatiana's DB tables. 
//simulate appropriately.
//***********************************************************************************************************************   

public class BlemsCBGAgent extends  DirectBlemsAgent
{

	/**
	 * @param args
	 */
	    
		    
		    private Logger log = Logger.getLogger(getClass().getName());
			private Timer timer; // scheduled task
 		    private long delay = 900000;
		    private String baseDir = ".";

			/** Output writer. Debug time */
		    // 	private FileWriter writer;

			public String getBaseDir() {
				return baseDir;
			}

			public void setBaseDir(String dir) {
				this.baseDir = dir;
			}

			public void setDelayS(long delay) {
				this.delay = delay * 1000;
			}

			public long getDelayS() {
				return this.delay / 1000;
			}
			
		//Function Comments : a startup function for scheduler to run on startup check the Proto4.xml for scheduler settings.	
		  public void startup () 
		  {
			 
			  log.log(Level.INFO, "Starting " + getID());
				super.startup();
				
				
				
				 /*EstimateOccupancyTask task = new EstimateOccupancyTask();
				timer = new Timer("Estimator");
				timer.scheduleAtFixedRate(task, 0, delay);
				*/
				
				ArrayList<SensorRecord>  TempSensorIds =  getSensors(  null ,ReadingTypes.CURRENT_TEMP ,null) ;
				
				try{
				CBGAgentTask task = new CBGAgentTask() ;
				timer= new Timer("BlemsCBGAgent") ;
				timer.scheduleAtFixedRate(task,0,delay) ;
				} catch (Exception E)
				{E.printStackTrace() ;}
	
		
			 
		  }
		  //Funtion Comments :  a shutdown function for scheduler to run shutdown function 
		 public void shutdown()
		 {
				log.log(Level.INFO, "Shutting down " + getID());
				timer.cancel();
		 }
		 

	 /* public static void main(String[] args) throws SQLException, Exception {

		// BlemsAgentAPI BAA = new BlemsAgentAPI() ;
		BlemsCBGAgent cbgAgent =  new BlemsCBGAgent() ;
		CBGAgentTask tsk =  new CBGAgentTask() ;
		  tsk.run() ;
  */
		// TODO Auto-generated method stub

	
		


	// A class to extend Timertask. the Timer of the scheduler runs the code each time it wakes up after sleep.  	 
	class CBGAgentTask extends TimerTask 
	{
	
	 	private  String userid;//  = "blems" ;
		private  String password ;//  = "flat2#isi" ;
		private  String url ;// = "jdbc:mysql://cb.isi.edu:3306/blems" ;
		private  String driver; // = "com.mysql.jdbc.Driver" ;
		private  String IpAdd ; //= "http://128.9.160.95:28081" ;
		private  String lab ; //= "CBG" ;
	// 	public static String  loading_mode;// valid values "estimation" , "regular", "groundtruth"   
		private  String outputesttable ;
		private String primaryconfig = "blems" ;
		private  String secconfig = "cbg" ;
		private String spaceDB ;
		private  String localmodeldir ;
		private boolean insertException = false ;
		private Hashtable  SensorIDMap ;
		 
		    
		    public CBGAgentTask() throws Exception
		    {
		    	loadHashmap() ;
		    	
		    }
		    
		    public void run()
		    {
		    	try {
			 
		    		onAgentwakeup() ;
		    		} catch (SQLException e) {
			// TODO Auto-generated catch block
		    		e.printStackTrace();
		    		} catch (Exception e) {
			// TODO Auto-generated catch block
		    		e.printStackTrace();
		    		}
		    }  

	
		    
		public void  loadHashmap () throws Exception 
		{
			SensorIDMap = new Hashtable() ;
	    	load_config("primary") ;
	    	Connection dbcon = getDBconnection() ;
	    	Statement Hashmapst = dbcon.createStatement() ;
	    	String hashmapquery = new String ("select * from sensorIDMap ;") ; 
	    	ResultSet Hashmap_rs = Hashmapst.executeQuery(hashmapquery) ;
	    	while(Hashmap_rs.next())
	    	{
	    		SensorIDMap.put(Hashmap_rs.getString(1), Hashmap_rs.getString(2)) ;
	    	}
	    	
	    	dbcon.close();
	    	
			
		}
	    public  void reset_config() 
		  {
			  
			  driver="" ;
			  password="";
			  url="";
			  userid="";
		  }
	
	    
	    	public void loadInitialParam() throws Exception
	    	{
					  
			BufferedReader  freader = new  BufferedReader ( new  FileReader("./dbconfig.txt" ) ) ;
			String testline = new String() ;
			String[] testlinearr ;
						
			while((testline=freader.readLine())!= null )
				
			{  if(testline.contains("localmodeldir"))
			{
				testlinearr=testline.split("=") ;
				localmodeldir=testlinearr[1].trim();
				 // System.out.println("Program-BlemsCBGAgent"+localmodeldir) ;
				// log.log(Level.INFO,"Program-BlemsCBGAgent"+localmodeldir) ;
			}
			}	
			freader.close();
	    	}
	
	    	
	    	
	    	public void load_config(String configname ) throws Exception
	    	{
				  
	    		BufferedReader  freader = new  BufferedReader ( new  FileReader("./dbconfig.txt" ) ) ;
	    		String testline = new String() ;
	    		String[] testlinearr ;
					
	    		while((testline=freader.readLine())!= null )
	    		{
	    			if(testline.contains("configstart:"+configname))
	    			{
	    				while((testline=freader.readLine())!= null && !testline.contains("configend")  )
	    				{
	    					if(testline.contains("password")  ) 
	    					{
	    						testlinearr = testline.split("=") ;
	    						password=testlinearr[1].trim() ;
	    						//System.out.println("Program-BlemsCBGAgent"+password) ;
	    					//	log.log(Level.INFO,"Program-BlemsCBGAgent"+password);
	    					}
					
	    					if(testline.contains("url")) 
	    					{
	    						testlinearr = testline.split("=") ;
	    						url=testlinearr[1].trim() ;
	    					//	System.out.println("Program-BlemsCBGAgent"+url) ;
	    					//	log.log(Level.INFO,"Program-BlemsCBGAgent"+url);
	    					}
					
	    					if(testline.contains("driver")) 
	    					{
	    						testlinearr = testline.split("=") ;
	    						driver=testlinearr[1].trim() ;
	    						//System.out.println("Program-BlemsCBGAgent"+driver) ;
	    						// log.log(Level.INFO,"Program-BlemsCBGAgent"+driver);
	    					}
					
	    					if(testline.contains("spaceDB"))
	    					{
	    						testlinearr=testline.split("=") ;
	    						spaceDB=testlinearr[1].trim();
	    						//System.out.println("Program-BlemsCBGAgent"+spaceDB) ;
	    						// log.log(Level.INFO,"Program-BlemsCBGAgent"+spaceDB);
	    					}
					
	    					if(testline.contains("userid")) 
	    					{
	    						testlinearr = testline.split("=") ;
	    						userid=testlinearr[1].trim() ;
	    					//	System.out.println("Program-BlemsCBGAgent"+userid) ;
	    					//	log.log(Level.INFO,"Program-BlemsCBGAgent"+userid) ;
	    					}
	    				} 
					}  // end of if config start
	    			else 
	    			{ continue ;}
				} // end of top level while
					
					freader.close();
	    	}
					
		
	
	
	
	
	public   Connection getDBconnection()  throws SQLException 
		     {
		   	 Connection   con ;
		   	 try {
					Class.forName(driver);	
				} catch(java.lang.ClassNotFoundException e) {
					 //System.err.print(”ClassNotFoundException: “);
					// System.err.println(e.getMessage());
					
					throw new SQLException( "ClassNotFoundException " + e.getMessage()) ;
				}

				try {
				    con = DriverManager.getConnection(url, userid, password);
				} catch(SQLException ex) {
					// System.err.println(”SQLException: ” + ex.getMessage());
					throw new SQLException( ex.getMessage()) ;
				}

				return con;
				
		            	  
		   	  
		     }	
	
	 
	
	
	
	
	public  void onAgentwakeup() throws SQLException, Exception
	          {
	        	  
	        	  
				// get all the sensors and then retrieve the readings.
	        	  
	        	loadInitialParam() ;
	        	load_config("primary") ;
	        //	System.out.println("Program-BlemsCBGAgent"+driver ) ;
	        //	log.log(Level.INFO,"Program-BlemsCBGAgent"+driver );
	         
	        	Connection  prim_con=  getDBconnection()  ;
	        	reset_config();
	        	load_config("secconfig") ;
	        	Connection sec_con = getDBconnection() ;
	        	reset_config() ;
	        	
	        	// Statement room_st = prim_con.createStatement() ;
	        	Statement lastupdate_st= prim_con.createStatement();
	        	//	Statement getSensors = prim_con.createStatement();
	        	// 	Statement  getReadType = prim_con.createStatement();
	        	Statement insertblemsraw = prim_con.createStatement();
	        	Statement insertCBGraw = sec_con.createStatement();
	        	Statement updateblemslastupdatetime = prim_con.createStatement() ;
	        	Statement updateCBGlastupdatetime = sec_con.createStatement() ;
	        	Statement modelfeaturest = prim_con.createStatement() ;
	        	
	        	// Statement StReading =dbcon.createStatement() ;
	        	
	        	/*** carefully test this part accessing a different schema when using jdbc connection to a different database */
	        	// String getRoomnoSql = "Select spaceid  from "+spaceDB+".spaces" ;
	        	
	        	//	DirectBlemsAgent dba = new DirectBlemsAgent() ;
	        	 
	        	ArrayList<SensorRecord>  TempSensorIds =  getSensors(  null ,ReadingTypes.CURRENT_TEMP ,null) ;
	        	
	        	   
	        	   String[]   roomlist = new String[TempSensorIds.size()];
	        	   
	        	   for (int i=0 ; i< TempSensorIds.size() ; i++)
	        	   {
	        		   roomlist[i] = TempSensorIds.get(i).getRoom() ;
	        	   }
	        	   
	        	        	
	        	String getSensorSql = new String();
	        	String  getSensorPointsSql = new String() ;  // = "Select sensorId, readingtype from sensors  " ;
	        	
	        	// 	ResultSet roomno_rs = room_st.executeQuery(getRoomnoSql) ;
	        	
	        	// get the rooms using getSensor for currenttemp reading type and using each room id get all the sensorids in that room 
	        	// and then using sensorids get the information for varying time range. 
	        	
	        	// for (int index=0 ; index < rs.g)
	        	insertException = false ;
	        	for(int index=0 ; index< roomlist.length ; index++)
	        	{
	          		
	        	// 	String  getLastUpdateTimeSql =  "select lastupdatetime from blemsRoom where roomid="+roomno_rs.getString(1)+";" ;
	        		String  getLastUpdateTimeSql =  "select lastupdatetime,ip,estimatormodel, featurelist, featurecount, extractdatalastupdate , estimatorlastupdate, arffmodelfile from blemsRoom where roomid='"+ roomlist[index].trim()+"';" ;
	        	   //  String getReadingTypeSql = " select * from readtype" ;
 	        		
	        	//	System.out.println("Program-BlemsCBGAgent"+"room processed is "+ roomlist[index].trim()) ;
	        	//	log.log(Level.INFO,"Program-BlemsCBGAgent"+"room processed is "+ roomlist[index].trim());
	        	  //   ResultSet  readtype_rs =  getReadType.executeQuery(getReadingTypeSql) ;
	        	    ResultSet lastupdate_rs =   lastupdate_st.executeQuery(getLastUpdateTimeSql) ;
	        	       //lastupdate_rs.next() ;
	        	  //  System.out.println("Program-BlemsCBGAgent"+"test1") ;
	        	   // log.log(Level.INFO,"Program-BlemsCBGAgent"+"test1");
	        	    int roomreccount = 0 ;
	        	    while(lastupdate_rs.next())
	        	    {
	        	    	  roomreccount++ ;
	        	    }
	        	    if (roomreccount==0)
	        	    {  
	        	    	//System.out.println("Program-BlemsCBGAgent"+" no room match found continuing to next room "+ roomlist[index].trim()) ;
	        	    // log.log(Level.INFO,"Program-BlemsCBGAgent"+" no room match found continuing to next room "+ roomlist[index].trim());
	        	       		continue ;
	        	    }
	        	    lastupdate_rs.beforeFirst() ;
	        	    lastupdate_rs.next();
	        	       
	        	       
	        	     //  if(lastupdate_rs.isAfterLast())
	        	      // { continue ;}
	        	  
	        	    Date dt = new Date(System.currentTimeMillis()) ;
	        	    
	        	  //   while (readtype_rs.next())
	        	  //  {
	        	    dt.setTime(System.currentTimeMillis())  ;
	        	    	
	        	    	 // ArrayList<SensorRecord>   ALSR = getSensors(roomno_rs.getString(1),"" ,"" ) ;
	        	    	
	        	    ArrayList<SensorRecord>   ALSR = getSensors(roomlist[index],null ,null ) ;
	        	  //   System.out.println("Program-BlemsCBGAgent"+System.currentTimeMillis() +" "+ lastupdate_rs.getTimestamp(1).getTime() ) ;
	        	   //  log.log(Level.INFO,"Program-BlemsCBGAgent"+System.currentTimeMillis() +" "+ lastupdate_rs.getTimestamp(1).getTime());
	        	   	int temporalreadings = (int) Math.floor( (Double)( ( (long)(System.currentTimeMillis() - lastupdate_rs.getTimestamp(1).getTime()) )/60000.0) ) ;
	        	   //	System.out.println("Program-BlemsCBGAgent"+(int)(System.currentTimeMillis()) + " time system current on left "+ (int)lastupdate_rs.getTimestamp(1).getTime()) ;
	        	   // 	log.log(Level.INFO,"Program-BlemsCBGAgent"+(int)(System.currentTimeMillis()) + " time system current on left "+ (int)lastupdate_rs.getTimestamp(1).getTime());
	        	    	//int temporalreadings =  Double. (System.currentTimeMillis() - lastupdate_rs.getTimestamp(1).getTime()) /60000.0 ;;
	        	  //  System.out.println("Program-BlemsCBGAgent"+"no of sensordevs "+ ALSR.size() +" temporal readings " + temporalreadings) ;
	        	   //	log.log(Level.INFO,"Program-BlemsCBGAgent"+"no of sensordevs "+ ALSR.size() +" temporal readings " + temporalreadings) ;
	        	    Reading[][] SensorRead=  new Reading [ALSR.size()][ temporalreadings+1] ;
	        	    boolean[][] temporalreadstatus2d = new boolean [ALSR.size()][temporalreadings+1] ;
	        	    int[][] temporalreadstatus2dint = new int [ALSR.size()][temporalreadings+1] ;
	        	    boolean[] temporalreadstatus= new boolean[temporalreadings+1] ;
	        	    	
	        	    	
	        	    for (int readstatupindex = 0 ; readstatupindex < ALSR.size(); readstatupindex++)
	        	    {
	        	    	for (int readstatindex=0 ; readstatindex< temporalreadings; readstatindex++)
	        	    	{
	        	    		temporalreadstatus2d[readstatupindex][readstatindex]= false ;
	        	    		temporalreadstatus2dint [readstatupindex][readstatindex]= 0 ;
	        	    	}
	        	    }
	        	    	
	        	    for (int readstatindex=0 ; readstatindex< temporalreadings; readstatindex++)
	        	    {
	        	    		temporalreadstatus[readstatindex]= true ;
	        	    }
	        	    	
	        	    int  count=0;
	        	    int thisroomvalidsensorcount = 0 ;
	        	    String  insertargstr = new String();
	        	    int[] validsensors = new int[ALSR.size()] ;
	        	    for (int tempindex=0 ; tempindex< ALSR.size() ;tempindex++)
	        	    {
	        	    	validsensors[tempindex] =0 ;
	        	    }
	        	    
	        	    int  sensorindex = -1 ;
	        	    for (SensorRecord  sr : ALSR)
	        	    {
	        	    	sensorindex++ ;
	        	    	String SensorNamestrip = new StringBuffer(new StringBuffer(sr.getSensorId().trim()).reverse().toString().split(new StringBuffer(sr.getRoom().trim()).reverse().toString())[1]).reverse().toString() ;
	        	    	
	        	    //	System.out.println(  "SensorDevice name"+ sr.getRoom().trim()+ "  "+ sr.getSensorId().trim()+" "+(sr.getSensorId()).split(sr.getRoom())[0] 
	        	   // 	  +" "+ SensorNamestrip ) ;
	        	    	
	        	    	if ((String)SensorIDMap.get( SensorNamestrip) == null )
	        	    		{
	        	    		       	    		
		        	    	for (int readstatindex=0 ; readstatindex< temporalreadings; readstatindex++)
		        	    	{
		        	    	        	    		
		        	    		temporalreadstatus2d[count][readstatindex] = true ;
		        	    		//System.out.println(" this sensor device readings are set true " + count) ;
		        	    		        	    		
		        	    	} 
		        	    // 	System.out.println(" this sensor device readings are set true " + count) ;
		        	    	count++ ;
		        	    	continue ;
		        	    	}
	        	    	  
	        	    	thisroomvalidsensorcount++ ; 
	        	    	 validsensors[sensorindex]=1 ; 
	        	        if (insertargstr.length() == 0 )
	        	    	    {  
	        	        		if  ( SensorNamestrip.equals("AS") )
	        	    		    {  insertargstr = "ASOUND" ;  }
	        	    		    else {
	        	    		    	insertargstr = (String)SensorIDMap.get(SensorNamestrip) ; }
	        	    		    //	System.out.println("Program-BlemsCBGAgent"+" got sensor id" + SensorNamestrip ) ;
	        	    		    //	log.log(Level.INFO,"Program-BlemsCBGAgent"+" got sensor id" + SensorNamestrip) ;
	        	    		    	
	        	    		    }
	        	        else {

	        	    	    	if  ( SensorNamestrip.equals("AS"))
	        	    	    	{  insertargstr = insertargstr+","+ "ASOUND" ;}
	        	    	    	else {
	        	    	    		insertargstr = insertargstr+","+ (String)SensorIDMap.get(SensorNamestrip) ; }
	        	    			// 	System.out.println("Program-BlemsCBGAgent"+" got sensor id" + sr.getSensorId().trim().split(sr.getRoom().trim())[0]) ;
	        	    			 //	log.log(Level.INFO,"Program-BlemsCBGAgent"+" got sensor id" + sr.getSensorId().trim().split(sr.getRoom().trim())[0]) ;
	        	    			 	
	        	    		    }
	        	    		    
	        	    			ArrayList<Reading>  sensorReadings =   getReadings(sr.getSensorId() , new  Date(lastupdate_rs.getTimestamp(1).getTime()),   dt   );
	        	    		//	System.out.println("Program-BlemsCBGAgent"+"Sensor readings retrieved "+ sr.getSensorId()+" "+ sr.getReadingType()+ " "+ sensorReadings.size()) ;
	        	    		//	log.log(Level.INFO,"Program-BlemsCBGAgent"+"Sensor readings retrieved "+ sr.getSensorId()+" "+ sr.getReadingType()+ " "+ sensorReadings.size())  ;
	        	    			
	        	    	 // int internalcount=0 ;
	        	    			for (Reading rd: sensorReadings)
	        	    			{
	        	    				SensorRead[count][ (int) Math.floor( (Double)( (  (rd.getStart().getTime() - lastupdate_rs.getTimestamp(1).getTime()))/60000.0))]= rd ;
	        	    				temporalreadstatus2d[count][(int) Math.floor( (Double)( (  (rd.getStart().getTime() - lastupdate_rs.getTimestamp(1).getTime()))/60000.0))] = true  ;
	        	    				temporalreadstatus2dint[count][(int) Math.floor( (Double)( (  (rd.getStart().getTime() - lastupdate_rs.getTimestamp(1).getTime()))/60000.0))] = 1 ;
	        	    	//			System.out.println (roomlist[index].trim()+ " index that are true "+ count +" " +  Math.floor( (Double)( ( (int) (rd.getStart().getTime() - lastupdate_rs.getTimestamp(1).getTime()))/60000.0))) ;
	        	    	//			log.log(Level.INFO,roomlist[index].trim()+ " index that are true "+ count +" " +  Math.floor( (Double)( ( (int) (rd.getStart().getTime() - lastupdate_rs.getTimestamp(1).getTime()))/60000.0))) ;
	        	    	//			System.out.println(temporalreadstatus2d[count][(int) Math.floor( (Double)( (  (rd.getStart().getTime() - lastupdate_rs.getTimestamp(1).getTime()))/60000.0))]) ;
	        	    	//			log.log(Level.INFO," bool val"+temporalreadstatus2d[count][(int) Math.floor( (Double)( (  (rd.getStart().getTime() - lastupdate_rs.getTimestamp(1).getTime()))/60000.0))]) ;
	        	    				
	        	    			//	if ((int) Math.floor( (Double)( ( (int) (rd.getStart().getTime() - lastupdate_rs.getTimestamp(1).getTime()))/60000.0)) >=10 )
	        	    				//	break ;
	        	    		 // 	        	    		  internalcount++;
	        	    			}
	        	    			count++;  
	        	    		// 	if (count >= 10 ) break ;
	        	    		}
	        	    	
	        	    	
	        	      int validreadingcount =0 ;
	        	    	for (int readstatindex=0 ; readstatindex< temporalreadings; readstatindex++)
	        	    	{
	        	    		for (int readstatupindex = 0 ; readstatupindex < ALSR.size(); readstatupindex++)
		        	    	{
	        	    		    if ( temporalreadstatus2d[readstatupindex][readstatindex] == false ) 
	        	    		    {   temporalreadstatus[readstatindex] = false ;  
	        	    		    
	        	    		 //   System.out.println("the sensor device causing miss is " + readstatupindex) ;
	        	    		    	        	    		  //  System.out.println( roomlist[index].trim()+ " these are false readstatupindex "+ readstatupindex +" readstatindex "+ readstatindex ) ;
	        	    		   // System.out.println(  temporalreadstatus2d[readstatupindex][readstatindex] + " "+ temporalreadstatus2dint [readstatupindex][readstatindex]) ;
	        	    		    }
		        	    	}
	        	    		if(temporalreadstatus[readstatindex] == true )
	        	    		{ validreadingcount++ ;}
	        	    	}
	        	    	
	        	   // 	System.out.println("valid reading count"+ validreadingcount ) ;
	        	    	/* for(int indextest =0 ; indextest < temporalreadings ; indextest++)
	        	    	{
	        	    		if (temporalreadstatus[indextest] == false)
	        	    		{  	System.out.print( indextest+" " ) ; }
	        	    		if(indextest%10 == 0)
	        	    			{ System.out.print("\n"); }
	        	    	} */
	        	    	
	        	    	insertargstr = insertargstr+ ",curtime,ip" ;
	        	    //	System.out.println("Program-BlemsCBGAgent"+"\n\n this is insertargstr \n "+ insertargstr) ;
	        	    //	log.log(Level.INFO,"Program-BlemsCBGAgent"+"\n\n this is insertargstr \n "+ insertargstr) ; 
	        	    	int totalupdatecount = 0 ;
	        	        String lastupdatetime = new String() ; 
	        	    	for (int ind=0; ind< temporalreadings; ind++)
	        	    	{
	        	//  String insertsql = "insert into blemsRaw("+insertargstr+") values("+)" " 	 ;
	        	    		
	        	    		
	        	    		if (temporalreadstatus[ind] == false)
        	    			{         	    				
        	    				/*	nulltemporalvaluedetect = true ;
        	    					System.out.println("Temporal reading missing") ;
        	    					break ; */
	        	    			
	        	    			continue ;
        	    					
        	    			}
	        	    		
	        	    		String valuesstring = new String();
	        	    		boolean nulltemporalvaluedetect = false ;
	        	    		int  countstartofvalidsensorindex=0 ;
	        	    		 // for(int ind1=0 ; ind1 < ALSR.size(); ind1++)
	        	    		for(int ind1=0 ; ind1 < ALSR.size(); ind1++)
	        	    		{
	        	    			if (validsensors[ind1]== 0)
	        	    				{   
	        	    				// System.out.println(" this is sensor is not required") ;
	        	    				continue ; }
	        	    			
	        	    				// check if any of the temporalreading is missing, if there any point on time line missing, then go to next time point
	        	    			
	        	    			countstartofvalidsensorindex++ ;
		        	    		if (temporalreadstatus[ind] == false)
	        	    			{         	    				
	        	    					nulltemporalvaluedetect = true ;
	        	    					// System.out.println("Temporal reading missing") ;
	        	    					break ; 
		        	    			
		        	    			
	        	    					
	        	    			}
	        	    			
	        	    			
	        	    	//		System.out.println("Program-BlemsCBGAgent"+ "temporal index "+Integer.toString(ind) +" sensor index "+ Integer.toString(ind1)) ;
	        	    	//		log.log(Level.INFO,"Program-BlemsCBGAgent"+ "temporal index "+Integer.toString(ind) +" sensor index "+ Integer.toString(ind1)) ;
	        	    		// 	System.out.println("Program-BlemsCBGAgent"+ SensorRead[ind1][ind].getStart()+" "+ SensorRead[ind1][ind].getEnd()) ;
	        	    	//		System.out.println("Program-BlemsCBGAgent"+ SensorRead[ind1][ind].getStart()+" ");
	        	    		// 	log.log(Level.INFO,"Program-BlemsCBGAgent"+ SensorRead[ind1][ind].getStart()+" "+ SensorRead[ind1][ind].getEnd()) ;
	        	    	//		System.out.println("Program-BlemsCBGAgent"+ SensorRead[ind1][ind].getVmax() +" "+  SensorRead[ind1][ind].getVmin()) ;
	        	    	//		log.log(Level.INFO,"Program-BlemsCBGAgent"+ SensorRead[ind1][ind].getVmax() +" "+  SensorRead[ind1][ind].getVmin()) ;
	        	    			
	        	    				// check if the any of the sensor readings are invalid, in times it could happen that all the sensors are not read and 
	        	    				// 	hence that reading is not valid for further processing.
	        	    			
	        	    			if ( Double.isNaN(SensorRead[ind1][ind].getVmax())   )
	        	    			{ nulltemporalvaluedetect = true ; 
	        	    	//		System.out.println("Some of the sensors readings are not valid") ;
	        	    			break ;
	        	    			
	        	    			}
	        	    			
	        	    			 
	        	    				// 	for the valuesstring of the sql construction if it's first value  don't preceed with a comma 
	        	    				// note all the values are Doubles.
	        	    			// if(ind1==0)
	        	    			if(countstartofvalidsensorindex==1)
	        	    			{ 	
	        	    					// valuesstring =    (Double.toString((SensorRead[ind1][ind].getVmax()+SensorRead[ind1][ind].getVmin())/2)) ; }
	        	    					valuesstring =    Double.toString(SensorRead[ind1][ind].getVmax()) ;
	        	    			}
	        	    			else
	        	    			{ 	 
	        	    				// valuesstring = valuesstring+ ","+   (Double.toString((SensorRead[ind1][ind].getVmax()+SensorRead[ind1][ind].getVmin())/2)) ; }
	        	    					valuesstring = valuesstring+ ","+   Double.toString(SensorRead[ind1][ind].getVmax()) ; }
	        	    				
	        	    			}// end for loop to get the valuesstring for one record to insert into SensorRaw.
	        	    		
	        	    		// check if the null temporal value detected in previous loop for a particular sensor if so discard further processing 
	        	    		// for that temporal reading and proceed to next point.
	        	    			if(nulltemporalvaluedetect == true )
	        	    			{ continue ;
	        	    			}
	        	    	 ///	insertargstr = insertargstr+ ","+"curtime" ;
	        	    		
	        	    			Calendar temptimestamp = Calendar.getInstance();
	        	    		//	long timeprogress =  ind
	        	    			long timeprogress =  ind+1 ;
	        	    			 timeprogress = timeprogress*60*1000 ;
	        	    			temptimestamp.setTimeInMillis((long)lastupdate_rs.getTimestamp(1).getTime()+ timeprogress ) ;
	        	    			String  IntervalStartstr = new String( Integer.toString( temptimestamp.get(temptimestamp.YEAR))+"-"+Integer.toString(temptimestamp.get(temptimestamp.MONTH)+1)
	        	          			 +"-"+ Integer.toString(temptimestamp.get(temptimestamp.DATE))+" "+
	        	          			 Integer.toString(temptimestamp.get(temptimestamp.HOUR_OF_DAY)) +":"+ Integer.toString( temptimestamp.get(temptimestamp.MINUTE) ) + ":" +
	        	          			 Integer.toString( temptimestamp.get(temptimestamp.SECOND ) )) ;
	        	    			valuesstring =  valuesstring +",'"+ IntervalStartstr+"'"   ;
	        	    			
	        	    	//		temptimestamp.setTimeInMillis((long)lastupdate_rs.getTimestamp(1).getTime()+ timeprogress +60*1000) ;
	        	    	//	lastupdatetime = new String( Integer.toString( temptimestamp.get(temptimestamp.YEAR))+"-"+Integer.toString(temptimestamp.get(temptimestamp.MONTH)+1)
		        	     //     			 +"-"+ Integer.toString(temptimestamp.get(temptimestamp.DATE))+" "+
		        	      //    			 Integer.toString(temptimestamp.get(temptimestamp.HOUR_OF_DAY)) +":"+ Integer.toString( temptimestamp.get(temptimestamp.MINUTE) ) + ":" +
		        	       //   			 Integer.toString( temptimestamp.get(temptimestamp.SECOND ) )) ;
	        	    			
	        	    		 	lastupdatetime = IntervalStartstr ;
	        	    			System.out.println( "lastupdate "+ ind +"  timeprogress "+timeprogress +" " +lastupdatetime) ;
	        	    			
	        	    	//   insertargstr = insertargstr+ ","+"ip" ;
	        	    			valuesstring = valuesstring +",'"+lastupdate_rs.getString(2)+"'" ;
	        	    		//	System.out.println("Program-BlemsCBGAgent"+insertargstr+" "+ valuesstring) ;
	        	    		//	log.log(Level.INFO,"Program-BlemsCBGAgent"+insertargstr+" "+ valuesstring) ;
	        	    			String insertsql = new String ("insert into SensorRaw("+insertargstr+") values("+ valuesstring+ ");" ) ;
	        	    			//log.log(Level.INFO,
	        	    			totalupdatecount++ ;
	        	    			System.out.println("Program-BlemsCBGAgent"+"total update count" + Integer.toString(totalupdatecount) + " "+insertsql) ;
	        	    		//	log.log(Level.INFO,"Program-BlemsCBGAgent"+"total update count" + Integer.toString(totalupdatecount) + " "+insertsql) ;
	        	   
	        	    			
	        	    			insertblemsraw.addBatch(insertsql) ;
	        	    			insertCBGraw.addBatch(insertsql) ;
	        	    			
	        	    			
	        	   	        	   
	        	    	} 
	        	   
	        	   
	        	    	
	        	    //	System.out.println("Program-BlemsCBGAgent"+"\n\n\n  executing batch ") ;
	        	    //	log.log(Level.INFO,"Program-BlemsCBGAgent"+"\n\n\n  executing batch ") ;
	        	    	int[] sqlexeccnt = new int[totalupdatecount]; 
	        	    	int[] sqlexecntcbg = new int[totalupdatecount];
	        	    	try{
	        	    	sqlexeccnt=  insertblemsraw.executeBatch();
	        	    sqlexecntcbg = 
	        	    		insertCBGraw.executeBatch();
	        	    	} catch( SQLException e)
	        	    	{
	        	    		
	        	    		e.printStackTrace() ;
        	    			 insertException = true ;	
        	    			
        	    			  String insertExceptionremedysql = "delete from SensorRaw where curtime >= '" + lastupdate_rs.getTimestamp(1) +"' and ip like '%"+lastupdate_rs.getString(2)+"%' ;" ;
        	    			 
	        	    		insertblemsraw.clearBatch() ;
	        	    		insertCBGraw.clearBatch() ;
	        	    		insertblemsraw.execute(insertExceptionremedysql) ;
	        	    		insertCBGraw.execute(insertExceptionremedysql) ;
	        	    		
        	    			}
	        	    	
	        	    //	System.out.println("Program-BlemsCBGAgent"+"\n\n\n  batch execution done ") ;
	        	    //	log.log(Level.INFO,"Program-BlemsCBGAgent"+"\n\n\n  batch execution done ") ;
	        	    	int totalupdatedrecords=0;
	        	    	
	        	  
	        	    	for ( int index1=0 ; index1 <totalupdatecount-1; index1++)
	        	    	{ 
	        	    		if(sqlexeccnt[index1] == 0 )
	        	    	    continue ;
	        	    		
	        	    		totalupdatedrecords++ ;
	        	    	}
	        	    	
	        	   
	              	//    System.out.println("Program-BlemsCBGAgent"+"\n total   records updated" + totalupdatedrecords) ;
	              	 // log.log(Level.INFO,"Program-BlemsCBGAgent"+"\n total   records updated" + totalupdatedrecords) ;
	        	    	
	        	    	
	        	    	long 	lastupdatetimetoupdate = System.currentTimeMillis() -  (long) (totalupdatedrecords*60*1000) ;
	        	    	String lastupdatesqlupdate = "update blemsRoom  set lastupdatetime ='"+lastupdatetime +"' " +
	        	    			"where TRIM(roomid) = '"+roomlist[index].trim()+"';" ;
	        	    	
	        	    //	System.out.println(lastupdatesqlupdate) ;
	        	    	
	        	    	System.out.println("Program-BlemsCBGAgent"+"\n total   records updated" + totalupdatedrecords) ;
	        	    	System.out.println("Program-BlemsCBGAgent"+"\n total   records updated" + totalupdatecount) ;
	        	    	System.out.println("Program-BlemsCBGAgent"+"\n total   records updated" + lastupdatetime) ;
	        	     	if(totalupdatecount !=0  &&  totalupdatedrecords !=0 )
	        	    	//if(totalupdatedrecords !=0 )
	        	    	{  	
	        	    	//	System.out.println("Program-BlemsCBGAgent"+ "\n\n\n executing blemsroom") ;
	        	    	//	log.log(Level.INFO,"Program-BlemsCBGAgent"+ "\n\n\n executing blemsroom") ;
	        	    		updateblemslastupdatetime.executeUpdate(lastupdatesqlupdate) ;
	        	    		updateCBGlastupdatetime.executeUpdate(lastupdatesqlupdate) ;
	        	    	}
	        	    	/*
	        	    	if(insertException==true)
	        	    	{
	        	    		String insertExceptionremedysql = "delete from SensorRaw where curtime > '" + lastupdate_rs.getTimestamp(1) +"' and ip like '%"+lastupdate_rs.getString(2)+"%' ;" ;
	        	    		insertblemsraw.clearBatch() ;
	        	    		insertCBGraw.clearBatch() ;
	        	    		insertblemsraw.execute(insertExceptionremedysql) ;
	        	    		insertCBGraw.execute(insertExceptionremedysql) ;
	        	    		insertException=false;
	        	    		
	        	    	}
	        	    	*/
	        	        
	        	        ExtractRawData  ERD = new ExtractRawData() ;
	        	        Calendar strt = Calendar.getInstance() ;
	        	        strt.setTimeInMillis(lastupdate_rs.getTimestamp(6).getTime()+60*1000) ;
	        	       // strt.setTimeInMillis(lastupdate_rs.getTimestamp(6).getTime() );
	        	        Calendar enddate = Calendar.getInstance() ;
	        	        enddate.setTimeInMillis(dt.getTime()) ;
	        	        
	        	        ERD.dataProcess(strt, enddate, roomlist[index].trim(), lastupdate_rs.getString(2) ) ;
	        	       
	        	        
	        	        // start and end time settings based on  estimatorlastupdate
	        	        
	        	        strt.setTimeInMillis(lastupdate_rs.getTimestamp(7).getTime()) ;
	        	        enddate.setTimeInMillis(dt.getTime()) ;
	        	        
	        	        // get model from the database.
	        	        // feature first or estimation first chicken or hen problem.
	        	        // if the last estimation update is same as the start of the extract date, then call the feature process.
	        	        String strdate  = new String() ;
	        	        		
	        	        		 //Integer.toString(strt.get(strt.YEAR)) + "-"+Integer.toString(strt.get(strt.MONTH)+1)+"-"+
	        	        		//Integer.toString(strt.DAY_OF_MONTH)+" "+Integer.toString(strt.HOUR_OF_DAY)+":"+Integer.toString(strt.MINUTE)+":"+
	        	        		// Integer.toString(strt.SECOND) ) ;
	        	        
	        	        Estimator es = new Estimator( log);
	        	        
	        	       int  [] featureDataType = new int[lastupdate_rs.getInt(5)] ;
	        	        String modelfeaturesql = "Select * from modelfeature where model like '"+lastupdate_rs.getString(3)+"';" ;
	        	        ResultSet modelfeaturers = modelfeaturest.executeQuery(modelfeaturesql) ;
	        	        modelfeaturers.next();
	        	        for(int  index7=0 ; index7 < lastupdate_rs.getInt(5) ; index7++)
	        	        {
	        	          featureDataType[index7] =  modelfeaturers.getInt(index7+2) ;
	        	        }
	        	        
	        	        if(lastupdate_rs.getTimestamp(6).getTime() - lastupdate_rs.getTimestamp(7).getTime() <= 60000) 
	        	        {
	        	        	// call FeatureProcess
	        	        	
	        	        	FeatureProcess fp = new FeatureProcess(log) ;
	        	        	
	        	        	if(temporalreadstatus[0]== true) {	
	   	        	   //      String strdate = new String( Integer.toString(strt.get(strt.YEAR)) + "-"+Integer.toString(strt.get(strt.MONTH)+1)+"-"+
	   	        	     //   		Integer.toString(strt.DAY_OF_MONTH)+" "+Integer.toString(strt.HOUR_OF_DAY)+":"+Integer.toString(strt.MINUTE)+":"+
	   	        	      //  		Integer.toString(strt.SECOND) ) ;
	   	        	         Calendar fpcalendar = Calendar.getInstance() ;
	   	        	         fpcalendar.setTimeInMillis(lastupdate_rs.getTimestamp(6).getTime()) ;
	   	        	         FeatureProcess.loading_mode  = "regular" ;
	   	        	           	FeatureProcess.dataProcessSingleInst(fpcalendar, roomlist[index].trim(), lastupdate_rs.getString(2)) ;
	   	        	           	FeatureProcess.loading_mode ="" ;
	        	        	}
	        	        }
	        	        else
	        	        {
	        	        	
	        	        	 strt.setTimeInMillis(lastupdate_rs.getTimestamp(7).getTime()) ;
	        	        	 strdate  = new String( Integer.toString(strt.get(strt.YEAR)) + "-"+Integer.toString(strt.get(strt.MONTH)+1)+"-"+
	 	        	        		Integer.toString(strt.DAY_OF_MONTH)+" "+Integer.toString(strt.HOUR_OF_DAY)+":"+Integer.toString(strt.MINUTE)+":"+
	 	        	        		Integer.toString(strt.SECOND) ) ;
	        	        	 // start index is 0 
	        	        	int  endindex =  (int)(lastupdate_rs.getTimestamp(6).getTime() - lastupdate_rs.getTimestamp(7).getTime())/60000 ;
	        	        
	        	        	
	        	        	 es.estimate(localmodeldir+lastupdate_rs.getString(3), localmodeldir+lastupdate_rs.getString(8),  
			        	        		strt,  0 ,endindex, lastupdate_rs.getString(4), lastupdate_rs.getInt(5), featureDataType, roomlist[index].trim(), lastupdate_rs.getString(2) ) ;
	        	        	
	        	        }
	        	               	       	        	       
	        	      
	        	       
	        	        
	        	        // es.estimate(localmodeldir+lastupdate_rs.getString(3), arfffilename,  stringdate, timestart, timeend, lastupdate_rs.getString(4), lastupdate_rs.getInt(5)) ;
	        	        
	        	        

       	        	 	strt.setTimeInMillis(lastupdate_rs.getTimestamp(6).getTime()) ;
       	        	 	strdate  = new String( Integer.toString(strt.get(strt.YEAR)) + "-"+Integer.toString(strt.get(strt.MONTH)+1)+"-"+
	        	        		Integer.toString(strt.DAY_OF_MONTH)+" "+Integer.toString(strt.HOUR_OF_DAY)+":"+Integer.toString(strt.MINUTE)+":"+
	        	        		Integer.toString(strt.SECOND) ) ;
       	        	
	        	        
       	        	 
       	        	 //	System.out.println("entering estimation") ;
       	        	//	log.log(Level.INFO,"entering estimation") ;
	        	        for (int  index6=0 ; index6<temporalreadings ; index6++)
	        	        {
	        	        	
	        	        	if(temporalreadstatus[index6]== true) 
	        	        	{	
	        	        
	        	        	
	        	        //	 String strdate = new String( Integer.toString(strt.get(strt.YEAR)) + "-"+Integer.toString(strt.get(strt.MONTH)+1)+"-"+
		        	      //  		Integer.toString(strt.DAY_OF_MONTH)+" 0:0:0") ;	
	        	        	
	        	        	//***************************************************
	        	        	// CORRECT NEEDED strdate has to be incremental
	        	        	//**************************
        	        	// 	strt.MINUTE + strt.HOUR_OF_DAY*60+index6, strt.MINUTE + strt.HOUR_OF_DAY*60+index6 ;
	        	        	  
	        	       /* es.estimate(localmodeldir+lastupdate_rs.getString(3), localmodeldir+lastupdate_rs.getString(8),  
	        	        		strdate,	strt.MINUTE + strt.HOUR_OF_DAY*60+index6, strt.MINUTE + strt.HOUR_OF_DAY*60+index6+1, lastupdate_rs.getString(4), lastupdate_rs.getInt(5), featureDataType) ;
	        	        		*/
	        	         
	        	        		es.estimate(localmodeldir+lastupdate_rs.getString(3), localmodeldir+lastupdate_rs.getString(8),  
		        	        		strt,  index6 ,index6, lastupdate_rs.getString(4), lastupdate_rs.getInt(5), featureDataType, roomlist[index].trim(), lastupdate_rs.getString(2) ) ;
	        	         
	        	        	}
	        	        }
	        	
	        	      //  System.out.println("exiting estimation") ;
	        	       // log.log(Level.INFO,"exiting estimation");
	        	}  // for each room.
	        	    	
	        	//     }
//	        		
	        		
	        		
	        		
	        		
	        		
	        		
	        		
	        		/*
	        		getSensors = "Select sensorId, readingtype from sensors where room = " + rs.getString(1) ;
	        		
	        		getSensorPoints  = "Select sensorId, vmax, vmin from points where sensorId in " +
	        				" (select sensorId   from sensors where room = " + rs.getString(1) +");" ;
	        		
	        		ResultSet rsreading = StReading.executeQuery(getSensorPoints) ; 
	        		*/
	        		
	        		
	        	lastupdate_st.close() ;
	        	insertblemsraw.close() ;
	        	insertCBGraw.close();
	        	updateblemslastupdatetime.close();
	        	updateCBGlastupdatetime.close();
	        	modelfeaturest.close();
	        	prim_con.close() ;
	        	sec_con.close();
	        	
	        		
	        	
	   }  //on wakeup
	           
	          
	          
	        	
	        	  
	        	// for (int )
	        	  
	        	  // for the each room# / sensorbox  with a new record run the preprocessing agents.
	        		// 
	        	  
	
	
	
	 
}

}
