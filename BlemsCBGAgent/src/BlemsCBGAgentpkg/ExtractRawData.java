package edu.isi.blems.BlemsCBGAgent;


import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar ;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;


/*
 * This program will pick up the raw sensors values from the sensor table  sensor_info_v3 
 * and does minimum processing and inserts it into table Sensor_est_data.
 * (timeofday ,asavg,mean_asavg,motioncntdiff, beamcntdiff, co2,avgco2,dh,dt,motion,pplcnt,curtime,avgco23,avgco26,avgco29,avgco212,ipadd)
 * 
 * important dbconfig file
 *  
 *  It calculates
 *  1) Sensor_est_data.timeofday= sensor_info_v3.curtime.hours*60+sensor_info_v3.curtime.min
 *  2) Sensor_est_data.motioncountdiff =   Sensor_info_v3.currentmotioncntreading- sensor_info_v3.previousmotion
 *  3) Sensor_est_data.beamcntdiff =  Sensor_info_v3.currentbeamcnt - sensor_info_v3.previousbeamcnt
 *  4) and past avgs of co2. 
 * 
 * 
 */

/*
 * discussion with Yu-Han on friday dec 16
 *   Pick up a record from timeline, need to throw the record in Blems raw data and CBG raw data
 *    run ExtractRawData on the new record so that it throws it in , then run preprocessing, update it in Blems and CBG features database.
 *    run estimated and prediction and update it  in both blems and cbg features .
 *    
 */
public class ExtractRawData {

	/**
	 * @param args
	 * 
	 */
	 private Logger log = Logger.getLogger(getClass().getName());
	private static String userid ; //= "blems" ;
	private static String password ; //= "flat2#isi" ;
	private static String url ; //= "jdbc:mysql://cb.isi.edu:3306/blems" ;
	private static String driver; // = "com.mysql.jdbc.Driver" ;
 //   private static String IpAdd = "http://128.9.160.95:28081" ;
     private static String IpAdd ;//= "http://68.181.161.6/" ;
    private static String lab ;// = "KAP" ;
    private static String  inputinfotable ;
    private static String  outputesttable ;
    private static String peoplecounter ; 
    private static boolean  is_pplcounter ;
    private static String primaryconfig = "primary" ; // "blems" ;
    private static String secconfig = "secconfig" ; // "cbg" ;
    private static int batchsize ;
    private static boolean insertException= false ;
  //  private ResultSet rsavg ;

	  public ExtractRawData () {
		
		  //  userid = "blems" ;	}
		 // password = "flat2#isi" ;
		 // url= "jdbc:mysql://cb.isi.edu:3306/blems" ;
		 // driver = "com.mysql.jdbc.Driver" ;
		 // IpAdd = "http://68.181.161.6/" ;
		 // lab = "KAP" ;
		  
	//	  FileReader 
		   
		  try {
		  ExtractRawDatadbinfo() ;
		  } catch (Exception E){  E.printStackTrace() ;}
		  
	  }
	  
	  public void reset_config() 
	  {
		  
		  driver="" ;
		  password="";
		  url="";
		  userid="";
	  }
	  
	  /*public void load_config(String configname)
	  {
		  
	  } */
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
			  	 System.out.println("Program-ExtractRawData"+password) ;
			  	 log.log(Level.INFO,"Program-ExtractRawData"+password) ; 
			}
			
			if(testline.contains("url")) 
			{
			  	testlinearr = testline.split("=") ;
			  	  url=testlinearr[1].trim() ;
			  	  System.out.println("Program-ExtractRawData"+url) ;
			  	 log.log(Level.INFO,"Program-ExtractRawData"+url) ;
			}
			
			if(testline.contains("driver")) 
			{
			  	testlinearr = testline.split("=") ;
			  	  driver=testlinearr[1].trim() ;
			  	 System.out.println("Program-ExtractRawData"+driver) ;
			  	 log.log(Level.INFO,"Program-ExtractRawData"+driver) ;
			}
			
	
			
			if(testline.contains("userid")) 
			{
			  	testlinearr = testline.split("=") ;
			  	  userid=testlinearr[1].trim() ;
			  	 System.out.println("Program-ExtractRawData"+userid) ;
			  	 log.log(Level.INFO,"Program-ExtractRawData"+userid) ;
			}
			} 
			} else { continue ;}
			}
			
			freader.close();
	  }
	  
	  public void  ExtractRawDatadbinfo() throws IOException
	  {
			BufferedReader  freader = new  BufferedReader ( new  FileReader("./dbconfig.txt" ) ) ;
			String testline = new String() ;
			String[] testlinearr ;
			while((testline=freader.readLine())!= null )
			{
				 // System.out.println("Program-ExtractRawData"+testline);
				 
		   /*		if(testline.contains("IpAdd")) 
				{
				  	testlinearr = testline.split("=") ;
				  	  IpAdd=testlinearr[1].trim() ;
				  	  System.out.println("Program-ExtractRawData"+IpAdd);
				}
				
				
				
				if(testline.contains("lab")) 
				{
				  	testlinearr = testline.split("=") ;
				  	  lab=testlinearr[1].trim() ;
				  	 System.out.println("Program-ExtractRawData"+lab) ;
				}
				
				*/
				if(testline.contains("inputinfotable"))
				{
					testlinearr= testline.split("=") ;
					inputinfotable = testlinearr[1].trim();
					System.out.println("Program-ExtractRawData"+inputinfotable) ;
					 log.log(Level.INFO,"Program-ExtractRawData"+inputinfotable) ;
				}
				if(testline.contains("outputesttable"))
				{
					testlinearr=testline.split("=") ;
					outputesttable=testlinearr[1].trim();
					System.out.println("Program-ExtractRawData"+outputesttable) ;
					 log.log(Level.INFO,"Program-ExtractRawData"+outputesttable) ;
				}
				if(testline.contains("peoplecounter"))
				{  testlinearr=testline.split("=") ;
				peoplecounter = testlinearr[1].trim() ;
				System.out.println("Program-ExtractRawData"+peoplecounter) ;
				 log.log(Level.INFO,"Program-ExtractRawData"+peoplecounter) ;
					}
				if(testline.contains("is_pplcounter"))
				{  testlinearr = testline.split("=") ;
				is_pplcounter = Boolean.parseBoolean(testlinearr[1].trim());
				System.out.println("Program-ExtractRawData"+is_pplcounter) ;
				 log.log(Level.INFO,"Program-ExtractRawData"+is_pplcounter) ;
					
				}
				if(testline.contains("batchsize"))
				{
					testlinearr = testline.split("=") ;
					batchsize = Integer.parseInt(testlinearr[1].trim());
					System.out.println("Program-ExtractRawData"+batchsize) ;
					 log.log(Level.INFO,"Program-ExtractRawData"+batchsize) ;
				}
			}
			
			freader.close() ;
	  }
    public static  Connection getDBconnection()  throws SQLException 
     {
   	 Connection   con ;
   	 try {
   		  //System.out.println("Program-ExtractRawData"+lab) ;
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
    
    public float getAvg(ResultSet rsavg, Timestamp t1, Timestamp t2)  throws Exception
    {
    	float avgco2 =0 ;
    	float co2tot=0 ;
    	
    	rsavg.beforeFirst() ;
    	int reccnt=0 ;
    	while(rsavg.next())
    	{
    		
    		// System.out.println("Program-ExtractRawData"+" time "+rsavg.getTimestamp(1).getTime() +" "+t1.getTime() +" "+ t2.getTime()) ;
    		if ( rsavg.getTimestamp(1).getTime() >= t2.getTime() && rsavg.getTimestamp(1).getTime() < t1.getTime()) 
    		{
    			co2tot += rsavg.getFloat(2) ;reccnt++ ;
    		}
    	}
    	
    	avgco2 = co2tot/reccnt ;
    	System.out.println("Program-ExtractRawData"+"co2tot "+co2tot+" reccnt " + reccnt) ;
    	 log.log(Level.INFO,"Program-ExtractRawData"+"co2tot "+co2tot+" reccnt " + reccnt) ;
    	return  avgco2 ;
    }
    
    public void  dataProcess(Calendar startInt, Calendar endInt, String roomid, String ip)
    {
    	
    	System.out.println("Program-ExtractRawData"+ "Extract: data Process") ;
    	 log.log(Level.INFO,"Program-ExtractRawData"+ "Extract: data Process") ;
    	IpAdd = ip ;
    	lab = roomid ;
    	try {
    		
    		
    		load_config(primaryconfig) ;
    			Connection dbcon = getDBconnection() ;
    	Connection dbcon2 = getDBconnection() ;
    	Connection dbcon3 = getDBconnection() ;
    	Connection dbcon4_roomprocessingupdate = getDBconnection() ;
    	reset_config() ;
    	
    	load_config(secconfig) ;
    	  	Connection  secdbcon = getDBconnection();
    	reset_config();
    	
    	Calendar pplcntrstart =  Calendar.getInstance(); 
    	Calendar  pplcntrend =Calendar.getInstance() ;
    	pplcntrstart.setTimeInMillis(startInt.getTimeInMillis() - 2*24*60*60*1000) ;
    	pplcntrend.setTimeInMillis(endInt.getTimeInMillis() + 2*24*60*60*1000) ;
    	
    	Calendar co2avgstart = Calendar.getInstance(); 
    	co2avgstart.setTimeInMillis(startInt.getTimeInMillis() - 210*60*1000) ;
    	
    	String IntervalStartstr = new String( Integer.toString( startInt.get(startInt.YEAR))+"-"+Integer.toString(startInt.get(startInt.MONTH)+1)
    			 +"-"+ Integer.toString(startInt.get(startInt.DATE))+" "+
    	  Integer.toString(startInt.get(startInt.HOUR_OF_DAY)) +":"+ Integer.toString( startInt.get(startInt.MINUTE) ) + ":" +
    	  Integer.toString( startInt.get(startInt.SECOND ) )) ;
    	  
    	  //Integer.toString( 15*(int)(startInt.get(startInt.MINUTE)/15) ) + ":00" ) ;
    	    	 
    	    	 
    	    	 String IntervalEndstr = new String( Integer.toString( endInt.get(endInt.YEAR))+"-"+Integer.toString(endInt.get(endInt.MONTH)+1)
    	    			 +"-"+ Integer.toString(endInt.get(endInt.DATE))+" "+
    	    	  Integer.toString(endInt.get(endInt.HOUR_OF_DAY)) +":"+ Integer.toString( endInt.get(endInt.MINUTE) ) + ":" +
    	    	  Integer.toString( endInt.get(endInt.SECOND ) )) ;
    	    	  //Integer.toString( 15*(int)(endInt.get(endInt.MINUTE)/15)+14) + ":59" ) ;	
    	    	 
    	    	String co2avgstartstr =  new String( Integer.toString( co2avgstart.get(co2avgstart.YEAR))+"-"+Integer.toString(co2avgstart.get(co2avgstart.MONTH)+1)
   	    			 +"-"+ Integer.toString(co2avgstart.get(co2avgstart.DATE))+" "+
       	    	  Integer.toString(co2avgstart.get(co2avgstart.HOUR_OF_DAY)) +":"+ Integer.toString( co2avgstart.get(co2avgstart.MINUTE) ) + ":" +
       	    	  Integer.toString( co2avgstart.get(co2avgstart.SECOND ) )) ;
    	   
    	    	 
    	    	 String pplcntrStartstr = new String( Integer.toString( pplcntrstart.get(pplcntrstart.YEAR))+"-"+Integer.toString(pplcntrstart.get(pplcntrstart.MONTH)+1)
    	    			 +"-"+ Integer.toString(pplcntrstart.get(pplcntrstart.DATE))+" "+
    	    	  Integer.toString(pplcntrstart.get(pplcntrstart.HOUR_OF_DAY)) +":"+ Integer.toString( pplcntrstart.get(pplcntrstart.MINUTE) ) + ":" +
    	    	  Integer.toString( pplcntrstart.get(pplcntrstart.SECOND ) )) ;
    	    	 
    	    	 String pplcntrEndstr = new String( Integer.toString( pplcntrend.get(pplcntrend.YEAR))+"-"+Integer.toString(pplcntrend.get(pplcntrend.MONTH)+1)
    	    			 +"-"+ Integer.toString(pplcntrend.get(pplcntrend.DATE))+" "+
    	    	  Integer.toString(pplcntrend.get(pplcntrend.HOUR_OF_DAY)) +":"+ Integer.toString( pplcntrend.get(pplcntrend.MINUTE) ) + ":" +
    	    	  Integer.toString( pplcntrend.get(pplcntrend.SECOND ) )) ;
    	
    	
    	    	 
    	 // to extract the sensor records from SensorRaw databases into Sensor features table.   	 
    	 String selectsql =  new String ("select lastot ,bm,bmc,brc,cotwo,curtime, dh , dt  from "+ inputinfotable + " where   ip like '%"+ IpAdd +"%'  and curtime between '"+ IntervalStartstr +"' and '"+ IntervalEndstr + "' ; " ) ;
    	
    	// to obtain the ground truth from people counter
    	String pplcntsql = new String (" select curtime, people , operation from "+ peoplecounter+ "  where lab like'%"+ lab+"%' and curtime between '"+ pplcntrStartstr +"' and '"+ pplcntrEndstr + "' ;") ;
    	
    	// to count the total available ensembles in past for averages and correlation
    	String sqlall = new String ("select curtime , cotwo from "+inputinfotable +"   where   ip like '%"+ IpAdd +"%'  and    curtime between '"+ co2avgstartstr +"' and '"+ IntervalEndstr + "' ; "  );
    	
    	System.out.println("Program-ExtractRawData"+selectsql+"\n"+pplcntsql+"\n"+sqlall) ;
    	 log.log(Level.INFO,"Program-ExtractRawData"+selectsql+"\n"+pplcntsql+"\n"+sqlall) ;
    	
    	
    	Statement statement = dbcon.createStatement() ;
    	Statement statement2 = dbcon2.createStatement() ; 
    	Statement statement3 = dbcon3.createStatement() ;
    	Statement statement4 = dbcon.createStatement() ;
    	Statement secstatement = secdbcon.createStatement();
    	Statement secstatement2 = secdbcon.createStatement(); 
	    
    	// selectsql
    	statement.executeQuery(selectsql) ;
	    ResultSet rs1 =  statement.getResultSet() ;
	   
	     
	     // pplcntsql
	    ResultSet rs2 = null ;
	     if(is_pplcounter == true)
	     	{ 		statement2.executeQuery(pplcntsql) ;
	     			rs2 = statement2.getResultSet(); 
	     			}
	    
	     
	     // sqlall
	     statement4.executeQuery(sqlall) ;
	     ResultSet rsavg = statement4.getResultSet() ;
	     
	     int timeofday ;
	     Timestamp ts,tempts =new Timestamp(0) ; //= rs1.getTimestamp(6) ;
	     Timestamp tempts2 = new Timestamp(0) ;
	     Timestamp prevstamp = new  Timestamp(0) ; int prevppcnt =0 ,ppcnt=0,prevmotion=0,prevbeam=0,motiondiff=0, beamdiff=0;
	     Timestamp lastupdatedrecord  = new Timestamp(0) ;
	    int countsql = 0 ;
	   
	    while(rsavg.next())
	    { countsql++ ; }
	    System.out.println("Program-ExtractRawData"+" # ensembles available in past from the current time  "+IntervalEndstr +"  for calculation of averages and correlations is " + countsql) ;
	    log.log(Level.INFO,"Program-ExtractRawData"+" # ensembles available in past from the current time  "+IntervalEndstr +"  for calculation of averages and correlations is " + countsql) ;
	    countsql=0 ;
	    int totalrecordstoextract =  0 ;
	   
        // ResultSet rs10 = statement4.executeQuery(sqlall) ; 
	     while(rs1.next())
	     {
	    	 countsql++ ; totalrecordstoextract++ ;
	          ts = rs1.getTimestamp(6) ;
	             timeofday =   ts.getHours()*60+ts.getMinutes() ;
	             System.out.println("Program-ExtractRawData"+ts) ;
	             log.log(Level.INFO,"Program-ExtractRawData"+ts) ;
	           //  System.out.println("Program-ExtractRawData"+ "rs1 index "+ rs1.getRow() +"  fetch size "+rs2.getFetchSize() ) ;
	             
	              // pplcntsql =  " select curtime, people , operation from people_counter_v2 where lab ='"+ lab+"' and curtime between
	             
	         
	            // Timestamp prevstamp = new  Timestamp(0) ; int prevppcnt =0 ,ppcnt=0,prevmotion,prevbeam,motiondiff=0, beamdiff=0;

	        	 /* String avgStartstr = new String( Integer.toString( startInt.get(startInt.YEAR))+"-"+Integer.toString(startInt.get(startInt.MONTH)+1)
	        			 +"-"+ Integer.toString(startInt.get(startInt.DATE))+" "+
	        	  Integer.toString(startInt.get(startInt.HOUR_OF_DAY)) +":"+ Integer.toString( startInt.get(startInt.MINUTE) ) + ":" +
	        	  Integer.toString( startInt.get(startInt.SECOND ) )) ;
	        	  
	        	  */
	            
	             
	            tempts.setTime(ts.getTime())  ;
	        //	  tempts2.setTime(ts.getTime()- 3*60*60*1000)  ;
	            tempts2.setTime(ts.getTime()- 30*60*1000)  ;
	       //    String avgssql3 = "select avg(cotwo ) from sensor_info_v3    where   ip like '%"+ IpAdd +"%'  and    curtime between '"+ tempts2.toString() +"' and '"+ tempts.toString() + "' ; "  ;
	           float  avg3 = getAvg(rsavg, tempts, tempts2) ;         
	       //  tempts.setTime(ts.getTime()- 3*60*60*1000 )  ;
	          tempts.setTime(ts.getTime()- 15*60*1000 )  ;
	        //     tempts2.setTime(ts.getTime() - 6*60*60*1000 ) ;
	          tempts2.setTime(ts.getTime() - 45*60*1000 ) ;
	       //   String avgssql6 = "select avg(cotwo ) from sensor_info_v3    where   ip like '%"+ IpAdd +"%'  and    curtime between '"+ tempts2.toString() +"' and '"+ tempts.toString() + "' ; "  ;
	          float  avg6 = getAvg(rsavg,tempts, tempts2) ;    
	         //  tempts.setTime(ts.getTime()- 6*60*60*1000)  ;
	          tempts.setTime(ts.getTime()- 30*60*1000)  ;
	        //  tempts2.setTime(ts.getTime() - 9*60*60*1000 ) ;
	          tempts2.setTime(ts.getTime() - 60*60*1000 ) ;
	          //String avgssql9 = "select avg(cotwo ) from sensor_info_v3    where   ip like '%"+ IpAdd +"%'  and    curtime between '"+ tempts2.toString() +"' and '"+ tempts.toString() + "' ; "  ;
	          float  avg9 = getAvg(rsavg,tempts, tempts2) ;    
	         //  tempts.setTime(ts.getTime()- 9*60*60*1000)  ;
	          tempts.setTime(ts.getTime()- 45*60*1000)  ;
	         //  tempts2.setTime(ts.getTime() - 12*60*60*1000 ) ;
	          tempts2.setTime(ts.getTime() - 75*60*1000 ) ;
	          //String avgssql12 = "select avg(cotwo ) from sensor_info_v3    where   ip like '%"+ IpAdd +"%'  and    curtime between '"+ tempts2.toString() +"' and '"+ tempts.toString() + "' ; "  ;
	          float  avg12 = getAvg(rsavg,tempts, tempts2) ;    
	          
	          if ( Double.isNaN((double) avg3) == true )
	          { avg3 = 0 ; }
	          if ( Double.isNaN((double) avg6) == true )
	          { avg6 = 0 ; }
	          if ( Double.isNaN((double) avg9) == true )
	          { avg9 = 0 ; }
	          if ( Double.isNaN((double) avg12) == true )
	          { avg12 = 0 ; }
	          
	          /*  
	           * String sqlall ="select  curtime , co2 from sensor_info_v3 where  where   ip like '%"+ IpAdd +"%'  and    curtime between '"+ tempts2.toString() +"' and '"+ tempts.toString() + "' ; "  ;
	           * ResultSet rs10 = statement4.executeQuery(sqlall) ; 
	           * 
	           * rs10.beforeFirst() ;
	           * double avg1=0 ;
	           * int reccnt =0 ;
	           * while( rs10.getTimeStamp(1) => time1 && rs10.getTimestamp() < time2 )
	           * { avg1+= rs10.getFloat(2) ;
	           * reccnt++ ;
	           * 
	           *  }
	           * avg1 = avg1/reccnt ;a
	           * 
	           */
	          
	          /*
              ResultSet rs4 =  statement4.executeQuery(avgssql3) ;
              rs4.first();
              float avg3 = rs4.getFloat(1) ;
              rs4.close() ;
             
              rs4 = statement4.executeQuery(avgssql6) ; 
              rs4.first();
              float avg6 = rs4.getFloat(1) ;
              rs4.close() ;
              rs4 = statement4.executeQuery(avgssql9) ;
              rs4.first();
              float avg9 = rs4.getFloat(1) ;
              rs4.close();
              rs4 = statement4.executeQuery(avgssql12);
              rs4.first();  }Given a quantum computer with a sufficient number of qubits, Shor's algorithm can be used to break public-key cryptography schemes such as the widely used RSA scheme. RSA is based on the assumption that factoring large numbers is computationally infeasible. So far as is known, this assumption is valid for classical (non-quantum) computers; no classical algorithm is known that can factor in polynomial time. However, Shor's algorithm shows that factoring is efficient on a quantum computer, so an appropriately large quantum computer can break RSA. It was also a powerful motivator for the design and construction of quantum computers and for the study of new quantum computer algorithms. It has also facilitated research on new cryptosystems that are secure from quantum computers, collecti
    
              float avg12 = rs4.getFloat(1) ;
              rs4.close() ;
              
	          */
	          
	          if(is_pplcounter == true )
	          {
	          rs2.beforeFirst() ;
	             
	            boolean found_flag = false ;
	             while(rs2.next())
	             {     
	            	
	            	 // System.out.println("Program-ExtractRawData"+"rs2 index "+ rs2.getRow()) ;
	            	 if (rs2.isFirst()== false )
	            	 {
	            		if ( ts.getTime()  < rs2.getTimestamp(1).getTime()  &&  ts.getTime() >= prevstamp.getTime() )
	            			{ found_flag = true ; ppcnt = prevppcnt ; }
	            	    if ( rs2.isLast() == true && found_flag == false &&  ts.getTime() > rs2.getTimestamp(1).getTime()  )
	            	    {   ppcnt = rs2.getInt(2) ;  }
	            		
	            	 }
	            	 prevstamp = rs2.getTimestamp(1) ;
	            	 prevppcnt = rs2.getInt(2) ;
	             }
	             
	          }  // if is_pplcounter
	          
	          //if( found_flag == false )
	             //{   
	            //  }
	           

	          if(  rs1.isFirst()== false )
	             {
	            	  rs1.previous() ;
    	    		 prevmotion =  rs1.getInt(3) ;
    	    		  prevbeam = rs1.getInt(4) ;
    	    		  rs1.next();
    	    		 motiondiff =  rs1.getInt(3) -prevmotion ;
    	    		 if(motiondiff < 0 ) motiondiff = 0 ;
    	    		 beamdiff = rs1.getInt(4) - prevbeam ;
    	    		 if (beamdiff < 0)  beamdiff =0 ;
	             } 
	             
	             
	             
	              
	             // System.out.println("Program-ExtractRawData"+timeofday+","+rs1.getInt(1)+","+motiondiff+","+beamdiff+","+)
	            //   if( avg3 == 0 || avg6==0 || avg9==0|| avg12==0) { System.out.println("Program-ExtractRawData"+"avg found zero"); System.exit(0) ;}
	         
	         String instsql= null ;  
	            
	           if(is_pplcounter== true)
	           {
	          instsql =  new String ("insert into "+outputesttable+" (timeofday ,asavg,mean_asavg,motioncntdiff, beamcntdiff, co2,avgco2,dh,dt,motion,pplcnt,curtime,avgco23,avgco26,avgco29,avgco212,ipadd) values('"
	            		 +timeofday+"',"+rs1.getInt(1)+",0,"+motiondiff+","+beamdiff+","+
	            		 rs1.getFloat(5)+",0,"+rs1.getFloat(7)+","+rs1.getFloat(8)+","+rs1.getInt(2)+","+ppcnt+",'"+rs1.getTimestamp(6)+"',"+avg3+
	            		 ","+avg6+","+avg9+","+ avg12 +",'" + IpAdd +"' );") ;
	           }
	           else 
	           {
	        	   
	        	  instsql =  new String ("insert into "+outputesttable+ " (timeofday ,asavg,mean_asavg,motioncntdiff, beamcntdiff, co2,avgco2,dh,dt,motion,curtime,avgco23,avgco26,avgco29,avgco212,ipadd) values('"
		            		 +timeofday+"',"+rs1.getInt(1)+",0,"+motiondiff+","+beamdiff+","+
		            		 rs1.getFloat(5)+",0,"+rs1.getFloat(7)+","+rs1.getFloat(8)+","+rs1.getInt(2)+",'"+rs1.getTimestamp(6)+"',"+avg3+
		            		 ","+avg6+","+avg9+","+ avg12 +",'" + IpAdd +"' );") ;
	        	   
	           }
	             
	             System.out.println("Program-ExtractRawData"+instsql) ;
	             log.log(Level.INFO,"Program-ExtractRawData"+instsql) ;
	             
	             
	             statement3.addBatch(instsql) ;
	             secstatement.addBatch(instsql) ;
	             if(countsql == batchsize ) 
	             {  
	            	   try {
	            	 int[] executestatus =  statement3.executeBatch() ; 
	             secstatement.executeBatch() ;   countsql=0 ;
	             if ( executestatus[batchsize-1] !=0 )
	            lastupdatedrecord = rs1.getTimestamp(6) ;
	            	   }
	            	   catch(SQLException e)
	            	   {
	            		   //insertException= true;
	            		   String insertExceptionremedysql = "delete from "+outputesttable+" where curtime > '"+IntervalStartstr+"' and ipadd like '%"+ip+"%' ;"  ;
	           	    	statement3.clearBatch() ;
	           	    	secstatement.clearBatch() ;
	           	    	statement3.execute(insertExceptionremedysql) ;
	           	    	secstatement.execute(insertExceptionremedysql) ;
	           	    	
	           	    	System.out.println("DELETED PREVIOUS RECORDS   ") ;
	           	     log.log(Level.INFO,"DELETED PREVIOUS RECORDS   ") ;
	            	   }
	             }
	             //rs1.next();
	           ///  prevmotion =  rs1.getInt(3) ;
	    		// prevbeam = rs1.getInt(4) ;
	    		 
	    		 
	     } // while ( rs1.next ) all the available sensorrecords are extracted into a raw database.
	     
	     
	     	// not required.
	   /*  if(totalrecordstoextract == 1)
	     {
	    	 // check if the last estimation for previous record is completed 
	    	 // then call the feature process so it could take this new extraction and calculate features for it.
	     } */
	     
	    String updateextractdatalastupdatetime = new String() ;
	    
	    
	    updateextractdatalastupdatetime = "update blemsRoom set extractdatalastupdate = '"+lastupdatedrecord.toString()+"' where TRIM(roomid)='"+roomid.trim()+"';"  ;
	    Statement extractdatalastupdate_st = dbcon4_roomprocessingupdate.createStatement() ;
	    if(lastupdatedrecord.getTime() != 0) {
	    extractdatalastupdate_st.executeUpdate(updateextractdatalastupdatetime) ;
	    
	    secstatement2.executeUpdate(updateextractdatalastupdatetime);
	      }
	
	    /* if(insertException == true)
	    {
	    	String insertExceptionremedysql = "delete from "+outputesttable+" where curtime > '"+IntervalStartstr+"' and ipadd like '%"+ip+"%' ;"  ;
	    	
	    	extractdatalastupdate_st.execute(insertExceptionremedysql) ;
	    	secstatement.execute(insertExceptionremedysql) ;
	    	insertException = false;
	    	
	    } */
	   //  statement3.executeBatch() ;
	     rs1.close() ; 
	     if(is_pplcounter == true ){
	     rs2.close() ; }
	     rsavg.close() ;
	     statement.close() ;statement2.close();
	    // statement3.executeBatch() ;
	    secstatement.close(); statement3.close() ; dbcon.close() ;dbcon2.close() ; dbcon3.close() ;secdbcon.close();
	    System.out.println("ExtractRawdata completes") ;
	    log.log(Level.INFO,"ExtractRawdata completes") ;
    	
    	} catch(Exception E) {  E.printStackTrace() ;}
    }

    /* public static void main(String[] args) {
		
		
		try {
		DateFormat df =  new SimpleDateFormat("yyyy-MM-dd HH:mm:ss") ;
		 Date start_date = df.parse("2011-11-02 0:0:00") ;
		    Date end_date = df.parse("2011-11-02 23:59:59") ;
		    Calendar sc1 = Calendar.getInstance() ; 
		    sc1.setTime(start_date) ;
		    Calendar ec1 = Calendar.getInstance() ;
		    ec1.setTime(end_date) ;
		ExtractRawData sw = new ExtractRawData() ;
		sw.dataProcess(sc1, ec1) ;
		// TODO Auto-generated method stub
		} catch(Exception e) { e.printStackTrace() ;} 
	}  */

}
