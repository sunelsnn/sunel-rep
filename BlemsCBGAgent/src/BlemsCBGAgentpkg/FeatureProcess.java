package edu.isi.blems.BlemsCBGAgent;


import weka.core.*;


/*
*
*/
import weka.core.converters.*;
import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Random ; 
import java.util.logging.Level;
import java.util.logging.Logger;
  

// Item to complete , mark if completed when feature processing next record for a estimation makesure there is next record availabe in 
// SensorFeatures table and then calculate features for it.
  public class FeatureProcess {
	  
	  private static Logger log ;
	  private static String userid;//  = "blems" ;
		private static String password ;//  = "flat2#isi" ;
		private static String url ;// = "jdbc:mysql://cb.isi.edu:3306/blems" ;
		private static String driver; // = "com.mysql.jdbc.Driver" ;
		private static String IpAdd ; //= "http://128.9.160.95:28081" ;
		private static String lab ; //= "CBG" ;
		public static String  loading_mode;// valid values "estimation" , "regular", "groundtruth"   
		private static String outputesttable ;
		  private static String primaryconfig = "primary"; //= "blems" ;
		    private static String secconfig = "secconfig" ;//  "cbg" ;
		    private static boolean is_pplcounter=false ;
		    private static String peoplecounter ;// 
		    private static int batchsize ;
		    private static String inputinfotable ;
		    
		public  FeatureProcess(Logger log) {
			//String  logclass = new String( getClass().getName()) ;
	    	// log = Logger.getLogger(new String (logclass));
			this.log = log ;
		} 
		
		public static void reset_config() 
		  {
			  
			  driver="" ;
			  password="";
			  url="";
			  userid="";
		  }
		  
		
		 public static void  ExtractRawDatadbinfo() throws IOException
		  {
				BufferedReader  freader = new  BufferedReader ( new  FileReader("./dbconfig.txt" ) ) ;
				String testline = new String() ;
				String[] testlinearr ;
				while((testline=freader.readLine())!= null )
				{
					 // System.out.println("Program-FeatureProcess "+testline);
					 
			   /*		if(testline.contains("IpAdd")) 
					{
					  	testlinearr = testline.split("=") ;
					  	  IpAdd=testlinearr[1].trim() ;
					  	  System.out.println("Program-FeatureProcess "+IpAdd);
					}
					
					
					
					if(testline.contains("lab")) 
					{
					  	testlinearr = testline.split("=") ;
					  	  lab=testlinearr[1].trim() ;
					  	 System.out.println("Program-FeatureProcess "+lab) ;
					}
					
					*/
					if(testline.contains("inputinfotable"))
					{
						testlinearr= testline.split("=") ;
						inputinfotable = testlinearr[1].trim();
						System.out.println("Program-FeatureProcess "+inputinfotable) ;
						log.log(Level.INFO,"Program-FeatureProcess "+inputinfotable) ;
					}
					if(testline.contains("outputesttable"))
					{
						testlinearr=testline.split("=") ;
						outputesttable=testlinearr[1].trim();
						System.out.println("Program-FeatureProcess "+outputesttable) ;
						log.log(Level.INFO,"Program-FeatureProcess "+outputesttable) ;
					}
					if(testline.contains("peoplecounter"))
					{  testlinearr=testline.split("=") ;
					peoplecounter = testlinearr[1].trim() ;
					System.out.println("Program-FeatureProcess "+peoplecounter) ;
					log.log(Level.INFO,"Program-FeatureProcess "+peoplecounter) ;
						}
					if(testline.contains("is_pplcounter"))
					{  testlinearr = testline.split("=") ;
					is_pplcounter = Boolean.parseBoolean(testlinearr[1].trim());
					System.out.println("Program-FeatureProcess "+is_pplcounter) ;
					log.log(Level.INFO,"Program-FeatureProcess "+is_pplcounter) ;
						
					}
					if(testline.contains("batchsize"))
					{
						testlinearr = testline.split("=") ;
						batchsize = Integer.parseInt(testlinearr[1].trim());
						System.out.println("Program-FeatureProcess "+batchsize) ;
						log.log(Level.INFO,"Program-FeatureProcess "+batchsize) ;
					}
				}
				
				freader.close() ; 
				}
		 
		 
		
		public static void load_config(String configname ) throws Exception
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
				  	 System.out.println("Program-FeatureProcess "+password) ;
				  	log.log(Level.INFO,"Program-FeatureProcess "+password) ;
				}
				
				if(testline.contains("url")) 
				{
				  	testlinearr = testline.split("=") ;
				  	  url=testlinearr[1].trim() ;
				  	  System.out.println("Program-FeatureProcess "+url) ;
				  	log.log(Level.INFO,"Program-FeatureProcess "+url) ;
				}
				
				if(testline.contains("driver")) 
				{
				  	testlinearr = testline.split("=") ;
				  	  driver=testlinearr[1].trim() ;
				  	 System.out.println("Program-FeatureProcess "+driver) ;
				  	log.log(Level.INFO,"Program-FeatureProcess "+driver) ;
				}
				
		
				if(testline.contains("userid")) 
				{
				  	testlinearr = testline.split("=") ;
				  	  userid=testlinearr[1].trim() ;
				  	 System.out.println("Program-FeatureProcess "+userid) ;
				  	log.log(Level.INFO,"Program-FeatureProcess "+userid) ;
				}
				} 
				} else { continue ;}
				}
				
				freader.close();
		  }
		
		public static void setIpAdd( String ipadd )
		{
			IpAdd = ipadd ;
		}
		public static void setLab(String labstr)
		{
			lab = labstr ;
		}
		
		public static void setLogger(Logger loger)
		{
			log = loger ;
		}
		
		public static void setloading_mode(String teststatus)
		{
			loading_mode=teststatus ;
		}
		public static  Connection getDBconnection()  throws SQLException 
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
	    
    /*  public static void main(String[] args) throws Exception {
    	
    	String arfffile  = new String("/opt/weka/weka-3-6-4/timeofdaypplcntsep22.arff") ;
    	String strdate = new String("2011-09-22 00:00:00") ;
    	
    	
    	dataprocess(arfffile, strdate) ;
    	
    }  */ 
    
   //  public  static void dataprocess(String arfffile,String strdate) throws Exception 
		
		public static void dataProcessSingleInst(Calendar calstrdate, String roomid, String ipadd) throws Exception
		{

			
			System.out.println("Program-FeatureProcess "+ "FeatureProcess: data Process ===== Single Instance") ;
			log.log(Level.INFO,"Program-FeatureProcess "+ "FeatureProcess: data Process ===== Single Instance") ;
			lab = roomid ;
			IpAdd = ipadd ;
			
			ExtractRawDatadbinfo() ;
			
			// below two lines are blanked out because this function for single Instance processing doesn't require a previous estimation upload 
			// because form the blemsRoom we know that lastextractionupdate is same as lastestimatorupdate .
   /*    Instances data = new Instances(new BufferedReader(new FileReader(arfffile)));
      data.setClassIndex(data.numAttributes() - 1);
      
      */  
			
      DateFormat df =  new SimpleDateFormat("yyyy-MM-dd HH:mm:ss") ;
	// 	 Date start_date = df.parse(strdate) ;
		 Random rangen = new Random() ;
		  //  Date end_date = df.parse("2011-08-18 00:00:00") ;
		    Calendar sc1 = Calendar.getInstance() ; 
		    sc1.setTimeInMillis(calstrdate.getTimeInMillis()) ;
		    Calendar  ec1 = Calendar.getInstance() ;
		    ec1.setTimeInMillis(sc1.getTimeInMillis()+  60*1000 ) ;
		    
		   //  sc1.setTimeInMillis(sc1.getTimeInMillis()+  ((long)data.instance(i).value(timeofdayindex))*60*1000) ;
      
      //  data.attribute(1).name()
      
		    
		 // below paragraph commented  because this function for single Instance processing doesn't require a previous estimation upload 
			// because form the blemsRoom we know that lastextractionupdate is same as lastestimatorupdate .
       
		    /*
		    String collist = new String() ;
      int timeofdayindex =0,predictionindex=0 ;
      for ( int i=0 ; i <data.numAttributes() ; i++ )
      {  
    	  if(data.attribute(i).name().matches("timeofday")) 
    	  { timeofdayindex = i ;}
    	  if(data.attribute(i).name().matches("predictedpplcnt"))
    	  { predictionindex = i; }
    	  if (i==0)
    	  collist =  data.attribute(i).name() ;
    	  else 
    		  collist = collist +"," +data.attribute(i).name() ;
      }
      
      collist = collist + ",curtime " ;
      
      */
      
      load_config(primaryconfig) ;          
      Connection dbcon = getDBconnection() ;
     
                
      Statement st =  dbcon.createStatement() ;
      Statement st2 = dbcon.createStatement() ;
      reset_config();
      
      load_config(secconfig) ;
     Connection secdbcon = getDBconnection();
     reset_config();
     
    Statement secst = secdbcon.createStatement();
      
 // below paragraph commented  because this function for single Instance processing doesn't require a previous estimation upload 
	// because from the blemsRoom we know that lastextractionupdate is same as lastestimatorupdate .
    // in this commented paragraph a for loop that runs the critical part of dataprocessing function is commented out 
    // so it doesn't not loop but the core instructions of the for loop needs to run once so  for loop statement and it's ending brace 
    // are commented out technically
    
     /* for ( int i=0 ; i< data.numInstances() ; i++ )
                  {
                	   //String instsql =  new String ("insert into  Sensor_est_data ("+collist+")  values('"+timeofday+"',"+rs1.getInt(1)+",0,"+motiondiff+","+beamdiff+","+
     	            //		 rs1.getFloat(5)+",0,"+rs1.getFloat(7)+","+rs1.getFloat(8)+","+rs1.getInt(2)+","+ppcnt+",'"+rs1.getTimestamp(6)+"' );") ;
    	  String arglist = new String() ;
    	  for(int j=0; j<data.numAttributes() ; j++)
    	  {
    		  if (j==0)
    			  arglist = Double.toString(data.instance(i).value(j)) ;
    		  else 
    		 arglist = arglist + ","+ Double.toString(data.instance(i).value(j)) ;
    	  }
    	*/ 
    	     
    	  /* sc1.setTime(start_date) ;timeofdaypplcntaug2223.arff
    	  sc1.setTimeInMillis(sc1.getTimeInMillis()+  ((long)data.instance(i).value(timeofdayindex))*60*1000) ;
    	  String IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
     			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
     	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
     	  Integer.toString( sc1.get(sc1.SECOND ) )) ; 
     	       	     	  arglist= arglist + ",'"+ IntervalStartstr +"'"  ;
     	       	 */    	  
    	  // String instsql =  new String ("insert into  Sensor_est_datav2 ("+collist+")  values("+arglist+") ;" );
    	  
    	  
    /////////////////////////////////////////////////////////////// CORRELATION 1 
    	  
    	 // sc1.setTime(start_date) ;
    	  sc1.setTimeInMillis(calstrdate.getTimeInMillis()) ; // Feb 18: this is useless  but for generality
    	   // ec1.setTimeInMillis(sc1.getTimeInMillis()+  ((long)data.instance(i).value(timeofdayindex))*60*1000) ;
    	  
    	  ec1.setTimeInMillis(calstrdate.getTimeInMillis()) ;  //  Feb 18
    	  // sc1.setTimeInMillis( ec1.getTimeInMillis() - 3*60*60*1000) ; //sep 14
    	  sc1.setTimeInMillis( ec1.getTimeInMillis() - 30*60*1000) ; //edited sep 14
    	 String  IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
       			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
       	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
       	  Integer.toString( sc1.get(sc1.SECOND ) )) ;
    	  String IntervalEndstr = new String( Integer.toString( ec1.get(ec1.YEAR))+"-"+Integer.toString(ec1.get(ec1.MONTH)+1)
       			 +"-"+ Integer.toString(ec1.get(ec1.DATE))+" "+
       	  Integer.toString(ec1.get(ec1.HOUR_OF_DAY)) +":"+ Integer.toString( ec1.get(ec1.MINUTE) ) + ":" +
       	  Integer.toString( ec1.get(ec1.SECOND ) )) ;
          System.out.println ( IntervalStartstr +"  "+ IntervalEndstr ) ;
          log.log(Level.INFO,IntervalStartstr +"  "+ IntervalEndstr ) ;
    	  String corsql = "select co2, estimatedpplcnt  from " + outputesttable + "   where   ipadd like '%"+ IpAdd +"%'  and    curtime between '"+ IntervalStartstr +"' and '"+ IntervalEndstr + "' ; "  ;
    	   System.out.println("Program-FeatureProcess "+"corr1 "+ corsql) ;
    	   log.log(Level.INFO,"Program-FeatureProcess "+"corr1 "+ corsql) ;
    	  ResultSet rs6 = st2.executeQuery(corsql) ;
    	  int rowcount =0 ;
    	  while(rs6.next())
    	  {
    		  rowcount++ ;
    	  }
    	//  ResultSetConverter 
    	   System.out.println("Program-FeatureProcess "+" no of rows "+rowcount ) ;
    	   log.log(Level.INFO,"Program-FeatureProcess "+" no of rows "+rowcount ) ;
    	  double[] cotwo_1 = new double [rowcount]; double[] estimatedpplcnt_1  = new double [rowcount] ;
    	  int doubleindex=0 ;
    	  rs6.beforeFirst() ;
    	  float cotwototal1=0,cotwoavg1=0 ;
    	  float pplcnttotal1=0,pplcntavg1=0 ;
    	  while (rs6.next())
    	  {   
    		  cotwototal1 += rs6.getFloat(1) ;
    		  pplcnttotal1  += rs6.getFloat(2) ;
    		  cotwo_1[doubleindex] = rs6.getFloat(1);
    		 //  estimatedpplcnt[doubleindex] = rs6.getFloat(2) + rangen.nextGaussian()/20 ;
    		  estimatedpplcnt_1[doubleindex] = rs6.getFloat(2) ;
    		  doubleindex++ ;
    	  }
    	  
    	  rs6.close();
    	  Correlation corr1 = new Correlation() ;  
    	  double corrout1=0 ;
    	  if(rowcount!=0)
    	  {
    	  cotwoavg1 = cotwototal1/rowcount ;
    	  pplcntavg1 = pplcnttotal1/rowcount ;
    	    	  
    	   corrout1 = corr1.getPearsonCorrelation ( cotwo_1, estimatedpplcnt_1) ; }
    	   System.out.println("Program-FeatureProcess "+"corr1 "+corrout1) ;
    	   log.log(Level.INFO,"Program-FeatureProcess "+"corr1 "+corrout1) ;
    	   
    	   
    	   /////////////////////////////////////////// CORRELATION 2 
    	   
    	   
    	 //   ec1.setTimeInMillis(ec1.getTimeInMillis() - 3*60*60*1000) ;
    	   ec1.setTimeInMillis(ec1.getTimeInMillis() - 15*60*1000) ;
     	 //  sc1.setTimeInMillis( sc1.getTimeInMillis()  -3*60*60*1000) ;
    	   sc1.setTimeInMillis( sc1.getTimeInMillis() - 15*60*1000) ;
    	   
     	   IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
        			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
        	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
        	  Integer.toString( sc1.get(sc1.SECOND ) )) ;
     	  IntervalEndstr = new String( Integer.toString( ec1.get(ec1.YEAR))+"-"+Integer.toString(ec1.get(ec1.MONTH)+1)
        			 +"-"+ Integer.toString(ec1.get(ec1.DATE))+" "+
        	  Integer.toString(ec1.get(ec1.HOUR_OF_DAY)) +":"+ Integer.toString( ec1.get(ec1.MINUTE) ) + ":" +
        	  Integer.toString( ec1.get(ec1.SECOND ) )) ;
        
     	   corsql = "select co2, estimatedpplcnt  from "+ outputesttable  + "   where   ipadd like '%"+ IpAdd +"%'  and    curtime between '"+ IntervalStartstr +"' and '"+ IntervalEndstr + "' ; "  ;
     	  System.out.println("Program-FeatureProcess "+"corr2 "+ corsql) ;
     	 log.log(Level.INFO,"Program-FeatureProcess "+"corr2 "+ corsql) ;
     	   rs6 = st2.executeQuery(corsql) ;
     	  // System.out.println("Program-FeatureProcess "+rs6.getRow()) ;
     	   rowcount=0 ;
     	  while(rs6.next())
    	  {
    		  rowcount++ ;
    	  }
    	//  ResultSetConverter 
    	  System.out.println("Program-FeatureProcess "+" no of rows "+rowcount ) ;
    	  log.log(Level.INFO,"Program-FeatureProcess "+" no of rows "+rowcount ) ;
     	   double[] cotwo_2 = new double [rowcount]; double[]  estimatedpplcnt_2  = new double [rowcount];
     	  doubleindex=0;
     	  rs6.beforeFirst() ;
     	  float cotwototal2=0, cotwoavg2=0 ;
     	  float pplcnttotal2=0,pplcntavg2=0 ;
     	  while (rs6.next())
     	  { 
     		   cotwototal2 += rs6.getFloat(1);
     		   pplcnttotal2 += rs6.getFloat(2) ;
     		  cotwo_2[doubleindex] = rs6.getFloat(1);
     		  //estimatedpplcnt[doubleindex] =  rs6.getFloat(2) + rangen.nextGaussian()/20  ;
     		  estimatedpplcnt_2[doubleindex] = rs6.getFloat(2) ;
     		  doubleindex++ ;
     	  }
     	  rs6.close();double corrout2=0.0 ;double autocor2_1 =0 ;
     	  if( rowcount != 0 ) {
     	  cotwoavg2 = cotwototal2/rowcount ;
     	  pplcntavg2 = pplcnttotal2/rowcount ;
     	
     	    
     	    corrout2 = corr1.getPearsonCorrelation ( cotwo_2, estimatedpplcnt_2) ; 
     	   
     	   if ( cotwo_2.length >= cotwo_1.length && cotwo_1.length!=0)
     	   {      autocor2_1 = corr1.getPearsonCorrelation(cotwo_2, cotwo_1,cotwo_1.length) ; }
     	   else if(cotwo_1.length!=0)
     	   {
     		   autocor2_1 = corr1.getPearsonCorrelation(cotwo_2, cotwo_1,cotwo_2.length) ;
     	   }
     	   
     	  }
     	  System.out.println("Program-FeatureProcess "+"corr2 "+ corrout2 +" autocor cotwo "+autocor2_1) ;
     	 log.log(Level.INFO,"Program-FeatureProcess "+"corr2 "+ corrout2 +" autocor cotwo "+autocor2_1) ;
    	  
    	  
    	   ///////////////////////////////// CORRELATION 3
     	   
     	 //  ec1.setTimeInMillis(ec1.getTimeInMillis() - 3*60*60*1000) ;
     	 ec1.setTimeInMillis(ec1.getTimeInMillis() - 15*60*1000) ;
     	  // sc1.setTimeInMillis( sc1.getTimeInMillis()  -3*60*60*1000) ;
     	sc1.setTimeInMillis( sc1.getTimeInMillis()  - 15*60*1000) ;
    	  IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
       			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
       	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
       	  Integer.toString( sc1.get(sc1.SECOND ) )) ;
    	  IntervalEndstr = new String( Integer.toString( ec1.get(ec1.YEAR))+"-"+Integer.toString(ec1.get(ec1.MONTH)+1)
       			 +"-"+ Integer.toString(ec1.get(ec1.DATE))+" "+
       	  Integer.toString(ec1.get(ec1.HOUR_OF_DAY)) +":"+ Integer.toString( ec1.get(ec1.MINUTE) ) + ":" +
       	  Integer.toString( ec1.get(ec1.SECOND ) )) ;
       
    	  corsql = "select co2, estimatedpplcnt  from "+ outputesttable +"   where   ipadd like '%"+ IpAdd +"%'  and    curtime between '"+ IntervalStartstr +"' and '"+ IntervalEndstr + "' ; "  ;
    	  System.out.println("Program-FeatureProcess "+"corr3 "+ corsql) ;
    	  log.log(Level.INFO,"Program-FeatureProcess "+"corr3 "+ corsql) ;
    	 rs6 = st2.executeQuery(corsql) ;
    	// System.out.println("Program-FeatureProcess "+rs6.getRow()) ;
    	 rowcount=0;
    	 while(rs6.next())
   	  {
   		  rowcount++ ;
   	  }
   	//  ResultSetConverter 
   	  System.out.println("Program-FeatureProcess "+" no of rows "+rowcount ) ;
   	log.log(Level.INFO,"Program-FeatureProcess "+" no of rows "+rowcount ) ;
    	   double[]  cotwo_3 = new double [rowcount]; double[] estimatedpplcnt_3  = new double [rowcount];
    	  doubleindex=0;
    	  rs6.beforeFirst() ;
    	  float cotwototal3=0,cotwoavg3 = 0;
    	  float pplcnttotal3=0,pplcntavg3=0 ;
    	  while (rs6.next())
    	  {   cotwototal3 += rs6.getFloat(1);
    	      pplcnttotal3 += rs6.getFloat(2) ;
    		  cotwo_3[doubleindex] = rs6.getFloat(1);
    		 //  estimatedpplcnt[doubleindex] = rs6.getFloat(2)+ rangen.nextGaussian()/20  ;
    		  estimatedpplcnt_3[doubleindex] = rs6.getFloat(2) ;
    		  doubleindex++ ;
    	  }
    	 
    	  rs6.close();
    	  double autocor3_2 =0 ;double corrout3=0 ;
    	  
    	  
    	  if( rowcount != 0) {
    	  cotwoavg3 = cotwototal3/rowcount ;
    	  pplcntavg3 = pplcnttotal3/rowcount ;
    	  //   autocor3_2 = corr1.getPearsonCorrelation(cotwo_3, cotwo_2) ;
    	  corrout2 = corr1.getPearsonCorrelation ( cotwo_3, estimatedpplcnt_3) ; 
    	   
     	   if ( cotwo_3.length >= cotwo_2.length && cotwo_2.length!=0)
     	   {      autocor3_2 = corr1.getPearsonCorrelation(cotwo_3, cotwo_2, cotwo_2.length) ; ; }
     	   else if (cotwo_2.length!=0 ) 
     	   {
     		   autocor3_2 = corr1.getPearsonCorrelation(cotwo_3, cotwo_2,cotwo_3.length) ;
     	   }
    	  }
    	   System.out.println("Program-FeatureProcess "+"corr3 "+ corrout3+ " autocor3_2 "+ autocor3_2) ;
    	   log.log(Level.INFO,"Program-FeatureProcess "+"corr3 "+ corrout3+ " autocor3_2 "+ autocor3_2) ;
    	   /////////////////////////////////////////////////////////// CORRELATION 4
    	   
    	   
    	  //  ec1.setTimeInMillis(ec1.getTimeInMillis() - 3*60*60*1000) ;
    	   ec1.setTimeInMillis(ec1.getTimeInMillis() - 15*60*1000) ;
      	 //  sc1.setTimeInMillis( sc1.getTimeInMillis()  -3*60*60*1000) ;
    	   sc1.setTimeInMillis( sc1.getTimeInMillis()  - 15*60*1000) ;
     	  IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
        			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
        	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
        	  Integer.toString( sc1.get(sc1.SECOND ) )) ;
     	   IntervalEndstr = new String( Integer.toString( ec1.get(ec1.YEAR))+"-"+Integer.toString(ec1.get(ec1.MONTH)+1)
        			 +"-"+ Integer.toString(ec1.get(ec1.DATE))+" "+
        	  Integer.toString(ec1.get(ec1.HOUR_OF_DAY)) +":"+ Integer.toString( ec1.get(ec1.MINUTE) ) + ":" +
        	  Integer.toString( ec1.get(ec1.SECOND ) )) ;
        
     	 corsql = "select co2, estimatedpplcnt  from " + outputesttable +"   where   ipadd like '%"+ IpAdd +"%'  and    curtime between '"+ IntervalStartstr +"' and '"+ IntervalEndstr + "' ; "  ;
     	 System.out.println("Program-FeatureProcess "+"corr4 "+ corsql) ;
     	log.log(Level.INFO,"Program-FeatureProcess "+"corr4 "+ corsql) ;
     	   rs6 = st2.executeQuery(corsql) ;
     	  //System.out.println("Program-FeatureProcess "+rs6.getRow()) ;
     	   rowcount=0 ;
     	  while(rs6.next())
    	  {
    		  rowcount++ ;
    	  }
    	//  ResultSetConverter 
    	  System.out.println("Program-FeatureProcess "+" no of rows "+rowcount ) ;
    	  log.log(Level.INFO,"Program-FeatureProcess "+" no of rows "+rowcount ) ;
     	  double[] cotwo_4 = new double [rowcount];  double[]  estimatedpplcnt_4  = new double [rowcount];
     	  doubleindex=0;
     	  rs6.beforeFirst();
     	  float cotwototal4=0,cotwoavg4=0;
     	  float pplcnttotal4=0, pplcntavg4=0 ;
     	  while (rs6.next())
     	  { 
     		  cotwototal4 += rs6.getFloat(1);
     		  pplcnttotal4 += rs6.getFloat(2) ;
     		  cotwo_4[doubleindex] = rs6.getFloat(1);
     		//  estimatedpplcnt[doubleindex] = rs6.getFloat(2) + rangen.nextGaussian()/20 ;
     		 estimatedpplcnt_4[doubleindex] = rs6.getFloat(2) ;
     		  doubleindex++ ;
     	  }
     	  
     	 rs6.close();double autocor4_3 =0 ; double corrout4=0 ;
     	  
     	 if(rowcount != 0) {
     	 cotwoavg4 = cotwototal4/rowcount ;
     	  pplcntavg4 = pplcnttotal4/rowcount ;
     	  
     	 
     	   corrout4 = corr1.getPearsonCorrelation ( cotwo_4, estimatedpplcnt_4) ;
     	   // double  autocor4_3 = corr1.getPearsonCorrelation(cotwo_4, cotwo_3) ;
     	 
   	   if ( cotwo_4.length >= cotwo_3.length && cotwo_3.length!=0)
   	   {      autocor4_3 = corr1.getPearsonCorrelation(cotwo_4, cotwo_3, cotwo_3.length) ; ; }
   	   else if (cotwo_3.length!=0)
   	   {
   		   autocor4_3 = corr1.getPearsonCorrelation(cotwo_4, cotwo_3,cotwo_4.length) ;
   	   }
   	   
     	 }
  	   // System.out.println("Program-FeatureProcess "+"corr3 "+ corrout3+ " autocor3_2 "+ autocor3_2) ;
     	  System.out.println("Program-FeatureProcess "+"corr4 "+ corrout4+ "  autocor4_3" + autocor4_3) ;
     	 log.log(Level.INFO,"Program-FeatureProcess "+"corr4 "+ corrout4+ "  autocor4_3" + autocor4_3) ;
    	   
    	   ///////////////////////////////////////////////////
    	   ////////////////////////////////////////UPDATE SECTION
    	  sc1.setTimeInMillis(calstrdate.getTimeInMillis() ) ;
    	 // ec1.setTimeInMillis(sc1.getTimeInMillis()+  24*60*60*1000) ; Feb: 18 just single instance update so change end date to 60 secs 
    	  // from calstrdate.
    	  
    	  ec1.setTimeInMillis(sc1.getTimeInMillis()+  60*1000) ;
    	  // sc1.setTimeInMillis(sc1.getTimeInMillis()+  ((long)data.instance(i).value(timeofdayindex))*60*1000) ;
    	  
    	  
    	  IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
      			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
      	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
      	  Integer.toString( sc1.get(sc1.SECOND )   )) ; 
    	  
    	  IntervalEndstr = new String( Integer.toString( ec1.get(ec1.YEAR))+"-"+Integer.toString(ec1.get(ec1.MONTH)+1)
      			 +"-"+ Integer.toString(ec1.get(ec1.DATE))+" "+
      	  Integer.toString(ec1.get(ec1.HOUR_OF_DAY)) +":"+ Integer.toString( ec1.get(ec1.MINUTE) ) + ":" +
      	  Integer.toString( ec1.get(ec1.SECOND ) )) ; 
    	  
    	     
    	   if( Double.isNaN(corrout1) == true  )
    	   {   corrout1 = 0  ;}
    	   if( Double.isNaN(corrout2) == true  )
    	   { 		   corrout2 = 0  ;   	   }
    	   if( Double.isNaN(corrout3) == true  )
    	   { 		   corrout3 = 0  ;   	   }
    	   if( Double.isNaN(corrout4) == true  )
    	   { 		   corrout4 = 0  ;   	   }
    	   
    	   if( Double.isNaN(autocor2_1) == true  )
    	   { 		   autocor2_1 = 0  ;   	   }
    	   
    	   if( Double.isNaN(autocor3_2) == true  )
    	   { 		   autocor3_2 = 0  ;   	   }
    	   if( Double.isNaN(autocor4_3) == true  )
    	   { 		   autocor4_3 = 0  ;   	   }
    	   
    	   
    	   String instsql = new String() ;
    	 
    	   
    	   /*if( i==0 )  // not sure why I have coded this. Need to fix and update this comment.
    	   {
    	   
    	   instsql = new String ("update Sensor_est_data set estimatedpplcnt =" +Double.toString(data.instance(i).value(predictionindex))+    			 
    			  " where  ipadd like '"+IpAdd +"' and  curtime  between '"+IntervalStartstr+"' and '"+IntervalEndstr+"' and  timeofday = "+  Integer.toString((int)data.instance(i).value(timeofdayindex))+ ";" ) ;
    	   }  
    	   else */
    	   
    	   
    	   
    	   if(loading_mode=="regular")  
    	   {
    		   instsql = new String ("update "+ outputesttable +"  set coravgco23 = "+Double.toString(corrout1) + "," +
    	    			   " coravgco26 = "+Double.toString(corrout2) +"," +
    	    			   " coravgco29 = "+Double.toString(corrout3) +"," +
    	    			   " coravgco212 = "+Double.toString(corrout4) + "," +
    	    			   " avgco23 = "+Double.toString(cotwoavg1) +","+
    	    			   "avgco26 = "+Double.toString(cotwoavg2) +","+
    	    			   "avgco29 = "+ Double.toString(cotwoavg3) +","+
    	    			   	"avgco212 = "+Double.toString(cotwoavg4) + "," +
    	    			   	"asavg0_6 = "+Double.toString(pplcntavg1) + "," +
    	    			   	"asavg6_9 = "+Double.toString(pplcntavg2) + "," +
    	    			   	"asavg9_12 = "+Double.toString(pplcntavg3) + "," +
    	    			   	"asavg12_15 = "+Double.toString(pplcntavg4) +"," +
    	    			   	"autocor2_1 = "+Double.toString(autocor2_1) +"," +
    	    			   	"autocor3_2 = "+Double.toString(autocor3_2) +"," +
    	    			   	"autocor4_3 = "+Double.toString(autocor4_3) +
    	    			  " where ipadd like '"+IpAdd +"' and  curtime  between '"+IntervalStartstr+"' and '"+IntervalEndstr+"';" );
    	    			  	//	" and  timeofday = "+  Integer.toString((int)data.instance(i).value(timeofdayindex))+ ";" ) ;
    	   }
    	 
    	  /*
    	   if(loading_mode == "estimation" && i>0 )
    	   {
    		   instsql = new String ("update "+ outputesttable +" set estimatedpplcnt ="+Double.toString(data.instance(i).value(predictionindex))+ 
    				   ", coravgco23 = "+Double.toString(corrout1) + "," +
	    			   " coravgco26 = "+Double.toString(corrout2) +"," +
	    			   " coravgco29 = "+Double.toString(corrout3) +"," +
	    			   " coravgco212 = "+Double.toString(corrout4) + "," +
	    			   " avgco23 = "+Double.toString(cotwoavg1) +","+
	    			   "avgco26 = "+Double.toString(cotwoavg2) +","+
	    			   "avgco29 = "+ Double.toString(cotwoavg3) +","+
	    			   	"avgco212 = "+Double.toString(cotwoavg4) + "," +
	    			   	"asavg0_6 = "+Double.toString(pplcntavg1) + "," +
	    			   	"asavg6_9 = "+Double.toString(pplcntavg2) + "," +
	    			   	"asavg9_12 = "+Double.toString(pplcntavg3) + "," +
	    			   	"asavg12_15 = "+Double.toString(pplcntavg4) +"," +
	    			   	"autocor2_1 = "+Double.toString(autocor2_1) +"," +
	    			   	"autocor3_2 = "+Double.toString(autocor3_2) +"," +
	    			   	"autocor4_3 = "+Double.toString(autocor4_3) +
	    			  " where ipadd like '%"+IpAdd +"%' and  curtime  between '"+IntervalStartstr+"' and '"+IntervalEndstr+"' and  timeofday = "+  Integer.toString((int)data.instance(i).value(timeofdayindex))+ ";" ) ; 
    	   }
    	   else if (loading_mode == "estimation" && i==0)
    	   {
    		   
    		   instsql = new String ("update "+outputesttable+" set estimatedpplcnt =" +Double.toString(data.instance(i).value(predictionindex))+    			 
    	    			  " where  ipadd like '"+IpAdd +"' and  curtime  between '"+IntervalStartstr+"' and '"+IntervalEndstr+"' and  timeofday = "+  Integer.toString((int)data.instance(i).value(timeofdayindex))+ ";" ) ;
    		   
    	   }
    	   
    	   if(loading_mode == "groundtruth")
    	   {
    		   instsql = new String ("update "+outputesttable+" set pplcnt =" +Double.toString(data.instance(i).value(predictionindex))+    			 
 	    			  " where  ipadd like '"+IpAdd +"' and  curtime  between '"+IntervalStartstr+"' and '"+IntervalEndstr+"' and  timeofday = "+  Integer.toString((int)data.instance(i).value(timeofdayindex))+ ";" ) ;
    		   
    	   }
    	   */
    	  //curtime between '"+IntervalStartstr+"' and '"+IntervalEndstr+"' and
    	  System.out.println("Program-FeatureProcess "+instsql) ;
    	  log.log(Level.INFO,"Program-FeatureProcess "+instsql) ;
    	  if(instsql.length() > 0) 
    	  {
    	  st.executeUpdate(instsql) ;
    	  secst.executeUpdate(instsql) ; 
    	  }
    	
    	  /////////////////////////////////////////////
    	  
     	//  tempts.setTime(ts.getTime()- 3*60*60*1000)  ;
    	 
    	  
    	  
          
       /* String avgssql6 = "select cotwo from sensor_info_v2    where   ip like '%"+ IpAdd +"%'  and    curtime between '"+ tempts2.toString() +"' and '"+ tempts.toString() + "' ; "  ;
       
       
       String avgssql9 = "select avg(cotwo ) from sensor_info_v2    where   ip like '%"+ IpAdd +"%'  and    curtime between '"+ tempts2.toString() +"' and '"+ tempts.toString() + "' ; "  ;
       
       
       String avgssql12 = "select avg(cotwo ) from sensor_info_v2    where   ip like '%"+ IpAdd +"%'  and    curtime between '"+ tempts2.toString() +"' and '"+ tempts.toString() + "' ; "  ;
       
       */
     	             
                //  }
      
		// Feb 18: below lines are temporary comments, need to check them
      //st2.close() ;
      
       st.close() ;
       secst.close();
      // dbcon.close() ;
      // secdbcon.close();
      
 
     /* DatabaseSaver save = new DatabaseSaver();
      save.setUrl(url);
      save.setUser(userid);
      save.setPassword(password);
      save.setInstances(data);
      save.setRelationForTableName(false);
      save.setTableName("mytable");
      save.connectToDatabase();
      save.writeBatch(); */
    
		}
		
		
		public  static void dataProcess(String arfffile, Calendar  calstrdate, String roomid, String ipadd) throws Exception 
    {
			
			System.out.println("Program-FeatureProcess "+ "FeatureProcess: data Process") ;
			log.log(Level.INFO,"Program-FeatureProcess "+ "FeatureProcess: data Process") ;
			lab = roomid ;
			IpAdd = ipadd ;
			
			ExtractRawDatadbinfo() ;
			
      Instances data = new Instances(new BufferedReader(new FileReader(arfffile)));
      data.setClassIndex(data.numAttributes() - 1);
      DateFormat df =  new SimpleDateFormat("yyyy-MM-dd HH:mm:ss") ;
	// 	 Date start_date = df.parse(strdate) ;
		 Random rangen = new Random() ;
		  //  Date end_date = df.parse("2011-08-18 00:00:00") ;
		    Calendar sc1 = Calendar.getInstance() ; 
		    sc1.setTimeInMillis(calstrdate.getTimeInMillis()) ;
		    Calendar  ec1 = Calendar.getInstance() ;
		    ec1.setTimeInMillis(sc1.getTimeInMillis()+  60*1000 ) ;
		    
		   //  sc1.setTimeInMillis(sc1.getTimeInMillis()+  ((long)data.instance(i).value(timeofdayindex))*60*1000) ;
      
      //  data.attribute(1).name()
      
      String collist = new String() ;
      int timeofdayindex =0,predictionindex=0 ;
      for ( int i=0 ; i <data.numAttributes() ; i++ )
      {  
    	  if(data.attribute(i).name().matches("timeofday")) 
    	  { timeofdayindex = i ;}
    	  if(data.attribute(i).name().matches("predictedpplcnt"))
    	  { predictionindex = i; }
    	  if (i==0)
    	  collist =  data.attribute(i).name() ;
    	  else 
    		  collist = collist +"," +data.attribute(i).name() ;
      }
      
      collist = collist + ",curtime " ;
      
      load_config(primaryconfig) ;          
      Connection dbcon = getDBconnection() ;
     
                
      Statement st =  dbcon.createStatement() ;
      Statement st2 = dbcon.createStatement() ;
      reset_config();
      
      load_config(secconfig) ;
     Connection secdbcon = getDBconnection();
     reset_config();
     
    Statement secst = secdbcon.createStatement();
      for ( int i=0 ; i< data.numInstances() ; i++ )
                  {
                	   //String instsql =  new String ("insert into  Sensor_est_data ("+collist+")  values('"+timeofday+"',"+rs1.getInt(1)+",0,"+motiondiff+","+beamdiff+","+
     	            //		 rs1.getFloat(5)+",0,"+rs1.getFloat(7)+","+rs1.getFloat(8)+","+rs1.getInt(2)+","+ppcnt+",'"+rs1.getTimestamp(6)+"' );") ;
    	  String arglist = new String() ;
    	  for(int j=0; j<data.numAttributes() ; j++)
    	  {
    		  if (j==0)
    			  arglist = Double.toString(data.instance(i).value(j)) ;
    		  else 
    		 arglist = arglist + ","+ Double.toString(data.instance(i).value(j)) ;
    	  }
    	 
    	  /* sc1.setTime(start_date) ;timeofdaypplcntaug2223.arff
    	  sc1.setTimeInMillis(sc1.getTimeInMillis()+  ((long)data.instance(i).value(timeofdayindex))*60*1000) ;
    	  String IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
     			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
     	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
     	  Integer.toString( sc1.get(sc1.SECOND ) )) ; 
     	       	     	  arglist= arglist + ",'"+ IntervalStartstr +"'"  ;
     	       	 */    	  
    	  // String instsql =  new String ("insert into  Sensor_est_datav2 ("+collist+")  values("+arglist+") ;" );
    	  
    	  
    /////////////////////////////////////////////////////////////// CORRELATION 1 
    	  
    	 // sc1.setTime(start_date) ;
    	  sc1.setTimeInMillis(calstrdate.getTimeInMillis()) ;
    	  ec1.setTimeInMillis(sc1.getTimeInMillis()+  ((long)data.instance(i).value(timeofdayindex))*60*1000) ;
    	  // sc1.setTimeInMillis( ec1.getTimeInMillis() - 3*60*60*1000) ; //sep 14
    	  sc1.setTimeInMillis( ec1.getTimeInMillis() - 30*60*1000) ; //edited sep 14
    	 String  IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
       			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
       	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
       	  Integer.toString( sc1.get(sc1.SECOND ) )) ;
    	  String IntervalEndstr = new String( Integer.toString( ec1.get(ec1.YEAR))+"-"+Integer.toString(ec1.get(ec1.MONTH)+1)
       			 +"-"+ Integer.toString(ec1.get(ec1.DATE))+" "+
       	  Integer.toString(ec1.get(ec1.HOUR_OF_DAY)) +":"+ Integer.toString( ec1.get(ec1.MINUTE) ) + ":" +
       	  Integer.toString( ec1.get(ec1.SECOND ) )) ;
          System.out.println ( IntervalStartstr +"  "+ IntervalEndstr ) ;
          log.log(Level.INFO,IntervalStartstr +"  "+ IntervalEndstr ) ;
    	  String corsql = "select co2, estimatedpplcnt  from " + outputesttable + "   where   ipadd like '%"+ IpAdd +"%'  and    curtime between '"+ IntervalStartstr +"' and '"+ IntervalEndstr + "' ; "  ;
    	   System.out.println("Program-FeatureProcess "+"corr1 "+ corsql) ;
    	   log.log(Level.INFO,"Program-FeatureProcess "+"corr1 "+ corsql) ;
    	  ResultSet rs6 = st2.executeQuery(corsql) ;
    	  int rowcount =0 ;
    	  while(rs6.next())
    	  {
    		  rowcount++ ;
    	  }
    	//  ResultSetConverter 
    	   System.out.println("Program-FeatureProcess "+" no of rows "+rowcount ) ;
    	   log.log(Level.INFO,"Program-FeatureProcess "+" no of rows "+rowcount ) ;
    	  double[] cotwo_1 = new double [rowcount]; double[] estimatedpplcnt_1  = new double [rowcount] ;
    	  int doubleindex=0 ;
    	  rs6.beforeFirst() ;
    	  float cotwototal1=0,cotwoavg1=0 ;
    	  float pplcnttotal1=0,pplcntavg1=0 ;
    	  while (rs6.next())
    	  {   
    		  cotwototal1 += rs6.getFloat(1) ;
    		  pplcnttotal1  += rs6.getFloat(2) ;
    		  cotwo_1[doubleindex] = rs6.getFloat(1);
    		 //  estimatedpplcnt[doubleindex] = rs6.getFloat(2) + rangen.nextGaussian()/20 ;
    		  estimatedpplcnt_1[doubleindex] = rs6.getFloat(2) ;
    		  doubleindex++ ;
    	  }
    	  
    	  rs6.close();
    	  Correlation corr1 = new Correlation() ;  
    	  double corrout1=0 ;
    	  if(rowcount!=0)
    	  {
    	  cotwoavg1 = cotwototal1/rowcount ;
    	  pplcntavg1 = pplcnttotal1/rowcount ;
    	    	  
    	   corrout1 = corr1.getPearsonCorrelation ( cotwo_1, estimatedpplcnt_1) ; }
    	   System.out.println("Program-FeatureProcess "+"corr1 "+corrout1) ;
    	   log.log(Level.INFO,"Program-FeatureProcess "+"corr1 "+corrout1) ;
    	   
    	   
    	   /////////////////////////////////////////// CORRELATION 2 
    	   
    	   
    	 //   ec1.setTimeInMillis(ec1.getTimeInMillis() - 3*60*60*1000) ;
    	   ec1.setTimeInMillis(ec1.getTimeInMillis() - 15*60*1000) ;
     	 //  sc1.setTimeInMillis( sc1.getTimeInMillis()  -3*60*60*1000) ;
    	   sc1.setTimeInMillis( sc1.getTimeInMillis() - 15*60*1000) ;
    	   
     	   IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
        			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
        	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
        	  Integer.toString( sc1.get(sc1.SECOND ) )) ;
     	  IntervalEndstr = new String( Integer.toString( ec1.get(ec1.YEAR))+"-"+Integer.toString(ec1.get(ec1.MONTH)+1)
        			 +"-"+ Integer.toString(ec1.get(ec1.DATE))+" "+
        	  Integer.toString(ec1.get(ec1.HOUR_OF_DAY)) +":"+ Integer.toString( ec1.get(ec1.MINUTE) ) + ":" +
        	  Integer.toString( ec1.get(ec1.SECOND ) )) ;
        
     	   corsql = "select co2, estimatedpplcnt  from "+ outputesttable  + "   where   ipadd like '%"+ IpAdd +"%'  and    curtime between '"+ IntervalStartstr +"' and '"+ IntervalEndstr + "' ; "  ;
     	  System.out.println("Program-FeatureProcess "+"corr2 "+ corsql) ;
     	 log.log(Level.INFO,"Program-FeatureProcess "+"corr2 "+ corsql) ;
     	   rs6 = st2.executeQuery(corsql) ;
     	  // System.out.println("Program-FeatureProcess "+rs6.getRow()) ;
     	   rowcount=0 ;
     	  while(rs6.next())
    	  {
    		  rowcount++ ;
    	  }
    	//  ResultSetConverter 
    	  System.out.println("Program-FeatureProcess "+" no of rows "+rowcount ) ;
    	  log.log(Level.INFO,"Program-FeatureProcess "+" no of rows "+rowcount ) ;
     	   double[] cotwo_2 = new double [rowcount]; double[]  estimatedpplcnt_2  = new double [rowcount];
     	  doubleindex=0;
     	  rs6.beforeFirst() ;
     	  float cotwototal2=0, cotwoavg2=0 ;
     	  float pplcnttotal2=0,pplcntavg2=0 ;
     	  while (rs6.next())
     	  { 
     		   cotwototal2 += rs6.getFloat(1);
     		   pplcnttotal2 += rs6.getFloat(2) ;
     		  cotwo_2[doubleindex] = rs6.getFloat(1);
     		  //estimatedpplcnt[doubleindex] =  rs6.getFloat(2) + rangen.nextGaussian()/20  ;
     		  estimatedpplcnt_2[doubleindex] = rs6.getFloat(2) ;
     		  doubleindex++ ;
     	  }
     	  rs6.close();double corrout2=0.0 ;double autocor2_1 =0 ;
     	  if( rowcount != 0 ) {
     	  cotwoavg2 = cotwototal2/rowcount ;
     	  pplcntavg2 = pplcnttotal2/rowcount ;
     	
     	    
     	    corrout2 = corr1.getPearsonCorrelation ( cotwo_2, estimatedpplcnt_2) ; 
     	   
     	   if ( cotwo_2.length >= cotwo_1.length && cotwo_1.length!=0)
     	   {      autocor2_1 = corr1.getPearsonCorrelation(cotwo_2, cotwo_1,cotwo_1.length) ; }
     	   else if(cotwo_1.length!=0)
     	   {
     		   autocor2_1 = corr1.getPearsonCorrelation(cotwo_2, cotwo_1,cotwo_2.length) ;
     	   }
     	   
     	  }
     	  System.out.println("Program-FeatureProcess "+"corr2 "+ corrout2 +" autocor cotwo "+autocor2_1) ;
     	 log.log(Level.INFO,"Program-FeatureProcess "+"corr2 "+ corrout2 +" autocor cotwo "+autocor2_1) ;
    	  
    	  
    	   ///////////////////////////////// CORRELATION 3
     	   
     	 //  ec1.setTimeInMillis(ec1.getTimeInMillis() - 3*60*60*1000) ;
     	 ec1.setTimeInMillis(ec1.getTimeInMillis() - 15*60*1000) ;
     	  // sc1.setTimeInMillis( sc1.getTimeInMillis()  -3*60*60*1000) ;
     	sc1.setTimeInMillis( sc1.getTimeInMillis()  - 15*60*1000) ;
    	  IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
       			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
       	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
       	  Integer.toString( sc1.get(sc1.SECOND ) )) ;
    	  IntervalEndstr = new String( Integer.toString( ec1.get(ec1.YEAR))+"-"+Integer.toString(ec1.get(ec1.MONTH)+1)
       			 +"-"+ Integer.toString(ec1.get(ec1.DATE))+" "+
       	  Integer.toString(ec1.get(ec1.HOUR_OF_DAY)) +":"+ Integer.toString( ec1.get(ec1.MINUTE) ) + ":" +
       	  Integer.toString( ec1.get(ec1.SECOND ) )) ;
       
    	  corsql = "select co2, estimatedpplcnt  from "+ outputesttable +"   where   ipadd like '%"+ IpAdd +"%'  and    curtime between '"+ IntervalStartstr +"' and '"+ IntervalEndstr + "' ; "  ;
    	  System.out.println("Program-FeatureProcess "+"corr3 "+ corsql) ;
    	  log.log(Level.INFO,"Program-FeatureProcess "+"corr3 "+ corsql) ;
    	 rs6 = st2.executeQuery(corsql) ;
    	// System.out.println("Program-FeatureProcess "+rs6.getRow()) ;
    	 rowcount=0;
    	 while(rs6.next())
   	  {
   		  rowcount++ ;
   	  }
   	//  ResultSetConverter 
   	  System.out.println("Program-FeatureProcess "+" no of rows "+rowcount ) ;
   	log.log(Level.INFO,"Program-FeatureProcess "+" no of rows "+rowcount ) ;
    	   double[]  cotwo_3 = new double [rowcount]; double[] estimatedpplcnt_3  = new double [rowcount];
    	  doubleindex=0;
    	  rs6.beforeFirst() ;
    	  float cotwototal3=0,cotwoavg3 = 0;
    	  float pplcnttotal3=0,pplcntavg3=0 ;
    	  while (rs6.next())
    	  {   cotwototal3 += rs6.getFloat(1);
    	      pplcnttotal3 += rs6.getFloat(2) ;
    		  cotwo_3[doubleindex] = rs6.getFloat(1);
    		 //  estimatedpplcnt[doubleindex] = rs6.getFloat(2)+ rangen.nextGaussian()/20  ;
    		  estimatedpplcnt_3[doubleindex] = rs6.getFloat(2) ;
    		  doubleindex++ ;
    	  }
    	 
    	  rs6.close();
    	  double autocor3_2 =0 ;double corrout3=0 ;
    	  
    	  
    	  if( rowcount != 0) {
    	  cotwoavg3 = cotwototal3/rowcount ;
    	  pplcntavg3 = pplcnttotal3/rowcount ;
    	  //   autocor3_2 = corr1.getPearsonCorrelation(cotwo_3, cotwo_2) ;
    	  corrout2 = corr1.getPearsonCorrelation ( cotwo_3, estimatedpplcnt_3) ; 
    	   
     	   if ( cotwo_3.length >= cotwo_2.length && cotwo_2.length!=0)
     	   {      autocor3_2 = corr1.getPearsonCorrelation(cotwo_3, cotwo_2, cotwo_2.length) ; ; }
     	   else if (cotwo_2.length!=0 ) 
     	   {
     		   autocor3_2 = corr1.getPearsonCorrelation(cotwo_3, cotwo_2,cotwo_3.length) ;
     	   }
    	  }
    	   System.out.println("Program-FeatureProcess "+"corr3 "+ corrout3+ " autocor3_2 "+ autocor3_2) ;
    	   log.log(Level.INFO,"Program-FeatureProcess "+"corr3 "+ corrout3+ " autocor3_2 "+ autocor3_2) ;
    	   /////////////////////////////////////////////////////////// CORRELATION 4
    	   
    	   
    	  //  ec1.setTimeInMillis(ec1.getTimeInMillis() - 3*60*60*1000) ;
    	   ec1.setTimeInMillis(ec1.getTimeInMillis() - 15*60*1000) ;
      	 //  sc1.setTimeInMillis( sc1.getTimeInMillis()  -3*60*60*1000) ;
    	   sc1.setTimeInMillis( sc1.getTimeInMillis()  - 15*60*1000) ;
     	  IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
        			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
        	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
        	  Integer.toString( sc1.get(sc1.SECOND ) )) ;
     	   IntervalEndstr = new String( Integer.toString( ec1.get(ec1.YEAR))+"-"+Integer.toString(ec1.get(ec1.MONTH)+1)
        			 +"-"+ Integer.toString(ec1.get(ec1.DATE))+" "+
        	  Integer.toString(ec1.get(ec1.HOUR_OF_DAY)) +":"+ Integer.toString( ec1.get(ec1.MINUTE) ) + ":" +
        	  Integer.toString( ec1.get(ec1.SECOND ) )) ;
        
     	 corsql = "select co2, estimatedpplcnt  from " + outputesttable +"   where   ipadd like '%"+ IpAdd +"%'  and    curtime between '"+ IntervalStartstr +"' and '"+ IntervalEndstr + "' ; "  ;
     	 System.out.println("Program-FeatureProcess "+"corr4 "+ corsql) ;
     	log.log(Level.INFO,"Program-FeatureProcess "+"corr4 "+ corsql) ;
     	   rs6 = st2.executeQuery(corsql) ;
     	  //System.out.println("Program-FeatureProcess "+rs6.getRow()) ;
     	   rowcount=0 ;
     	  while(rs6.next())
    	  {
    		  rowcount++ ;
    	  }
    	//  ResultSetConverter 
    	  System.out.println("Program-FeatureProcess "+" no of rows "+rowcount ) ;
    	  log.log(Level.INFO,"Program-FeatureProcess "+" no of rows "+rowcount ) ;
     	  double[] cotwo_4 = new double [rowcount];  double[]  estimatedpplcnt_4  = new double [rowcount];
     	  doubleindex=0;
     	  rs6.beforeFirst();
     	  float cotwototal4=0,cotwoavg4=0;
     	  float pplcnttotal4=0, pplcntavg4=0 ;
     	  while (rs6.next())
     	  { 
     		  cotwototal4 += rs6.getFloat(1);
     		  pplcnttotal4 += rs6.getFloat(2) ;
     		  cotwo_4[doubleindex] = rs6.getFloat(1);
     		//  estimatedpplcnt[doubleindex] = rs6.getFloat(2) + rangen.nextGaussian()/20 ;
     		 estimatedpplcnt_4[doubleindex] = rs6.getFloat(2) ;
     		  doubleindex++ ;
     	  }
     	  
     	 rs6.close();double autocor4_3 =0 ; double corrout4=0 ;
     	  
     	 if(rowcount != 0) {
     	 cotwoavg4 = cotwototal4/rowcount ;
     	  pplcntavg4 = pplcnttotal4/rowcount ;
     	  
     	 
     	   corrout4 = corr1.getPearsonCorrelation ( cotwo_4, estimatedpplcnt_4) ;
     	   // double  autocor4_3 = corr1.getPearsonCorrelation(cotwo_4, cotwo_3) ;
     	 
   	   if ( cotwo_4.length >= cotwo_3.length && cotwo_3.length!=0)
   	   {      autocor4_3 = corr1.getPearsonCorrelation(cotwo_4, cotwo_3, cotwo_3.length) ; ; }
   	   else if (cotwo_3.length!=0)
   	   {
   		   autocor4_3 = corr1.getPearsonCorrelation(cotwo_4, cotwo_3,cotwo_4.length) ;
   	   }
   	   
     	 }
  	   // System.out.println("Program-FeatureProcess "+"corr3 "+ corrout3+ " autocor3_2 "+ autocor3_2) ;
     	  System.out.println("Program-FeatureProcess "+"corr4 "+ corrout4+ "  autocor4_3" + autocor4_3) ;
     	 log.log(Level.INFO,"Program-FeatureProcess "+"corr4 "+ corrout4+ "  autocor4_3" + autocor4_3) ;
    	   
    	   ///////////////////////////////////////////////////
    	   ////////////////////////////////////////UPDATE SECTION
    	  sc1.setTimeInMillis(calstrdate.getTimeInMillis() ) ;
    	  ec1.setTimeInMillis(sc1.getTimeInMillis()+  24*60*60*1000) ;
    	  // sc1.setTimeInMillis(sc1.getTimeInMillis()+  ((long)data.instance(i).value(timeofdayindex))*60*1000) ;
    	  
    	  
    	  IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
      			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
      	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
      	  Integer.toString( sc1.get(sc1.SECOND )   )) ; 
    	  
    	  IntervalEndstr = new String( Integer.toString( ec1.get(ec1.YEAR))+"-"+Integer.toString(ec1.get(ec1.MONTH)+1)
      			 +"-"+ Integer.toString(ec1.get(ec1.DATE))+" "+
      	  Integer.toString(ec1.get(ec1.HOUR_OF_DAY)) +":"+ Integer.toString( ec1.get(ec1.MINUTE) ) + ":" +
      	  Integer.toString( ec1.get(ec1.SECOND ) )) ; 
    	  
    	     
    	   if( Double.isNaN(corrout1) == true  )
    	   {   corrout1 = 0  ;}
    	   if( Double.isNaN(corrout2) == true  )
    	   { 		   corrout2 = 0  ;   	   }
    	   if( Double.isNaN(corrout3) == true  )
    	   { 		   corrout3 = 0  ;   	   }
    	   if( Double.isNaN(corrout4) == true  )
    	   { 		   corrout4 = 0  ;   	   }
    	   
    	   if( Double.isNaN(autocor2_1) == true  )
    	   { 		   autocor2_1 = 0  ;   	   }
    	   
    	   if( Double.isNaN(autocor3_2) == true  )
    	   { 		   autocor3_2 = 0  ;   	   }
    	   if( Double.isNaN(autocor4_3) == true  )
    	   { 		   autocor4_3 = 0  ;   	   }
    	   
    	   
    	   String instsql = new String() ;
    	 
    	   
    	   /*if( i==0 )  // not sure why I have coded this. Need to fix and update this comment.
    	   {
    	   
    	   instsql = new String ("update Sensor_est_data set estimatedpplcnt =" +Double.toString(data.instance(i).value(predictionindex))+    			 
    			  " where  ipadd like '"+IpAdd +"' and  curtime  between '"+IntervalStartstr+"' and '"+IntervalEndstr+"' and  timeofday = "+  Integer.toString((int)data.instance(i).value(timeofdayindex))+ ";" ) ;
    	   }  
    	   else */
    	   
    	   
    	   
    	   if(loading_mode=="regular")  
    	   {
    		   instsql = new String ("update "+ outputesttable +"  set coravgco23 = "+Double.toString(corrout1) + "," +
    	    			   " coravgco26 = "+Double.toString(corrout2) +"," +
    	    			   " coravgco29 = "+Double.toString(corrout3) +"," +
    	    			   " coravgco212 = "+Double.toString(corrout4) + "," +
    	    			   " avgco23 = "+Double.toString(cotwoavg1) +","+
    	    			   "avgco26 = "+Double.toString(cotwoavg2) +","+
    	    			   "avgco29 = "+ Double.toString(cotwoavg3) +","+
    	    			   	"avgco212 = "+Double.toString(cotwoavg4) + "," +
    	    			   	"asavg0_6 = "+Double.toString(pplcntavg1) + "," +
    	    			   	"asavg6_9 = "+Double.toString(pplcntavg2) + "," +
    	    			   	"asavg9_12 = "+Double.toString(pplcntavg3) + "," +
    	    			   	"asavg12_15 = "+Double.toString(pplcntavg4) +"," +
    	    			   	"autocor2_1 = "+Double.toString(autocor2_1) +"," +
    	    			   	"autocor3_2 = "+Double.toString(autocor3_2) +"," +
    	    			   	"autocor4_3 = "+Double.toString(autocor4_3) +
    	    			  " where ipadd like '"+IpAdd +"' and  curtime  between '"+IntervalStartstr+"' and '"+IntervalEndstr+"' and  timeofday = "+  Integer.toString((int)data.instance(i).value(timeofdayindex))+ ";" ) ;
    	   }
    	 
    	   if(loading_mode == "estimation" && i>0 )
    	   {
    		   instsql = new String ("update "+ outputesttable +" set estimatedpplcnt ="+Double.toString(data.instance(i).value(predictionindex))+ 
    				   ", coravgco23 = "+Double.toString(corrout1) + "," +
	    			   " coravgco26 = "+Double.toString(corrout2) +"," +
	    			   " coravgco29 = "+Double.toString(corrout3) +"," +
	    			   " coravgco212 = "+Double.toString(corrout4) + "," +
	    			   " avgco23 = "+Double.toString(cotwoavg1) +","+
	    			   "avgco26 = "+Double.toString(cotwoavg2) +","+
	    			   "avgco29 = "+ Double.toString(cotwoavg3) +","+
	    			   	"avgco212 = "+Double.toString(cotwoavg4) + "," +
	    			   	"asavg0_6 = "+Double.toString(pplcntavg1) + "," +
	    			   	"asavg6_9 = "+Double.toString(pplcntavg2) + "," +
	    			   	"asavg9_12 = "+Double.toString(pplcntavg3) + "," +
	    			   	"asavg12_15 = "+Double.toString(pplcntavg4) +"," +
	    			   	"autocor2_1 = "+Double.toString(autocor2_1) +"," +
	    			   	"autocor3_2 = "+Double.toString(autocor3_2) +"," +
	    			   	"autocor4_3 = "+Double.toString(autocor4_3) +
	    			  " where ipadd like '%"+IpAdd +"%' and  curtime  between '"+IntervalStartstr+"' and '"+IntervalEndstr+"' and  timeofday = "+  Integer.toString((int)data.instance(i).value(timeofdayindex))+ ";" ) ; 
    	   }
    	   else if (loading_mode == "estimation" && i==0)
    	   {
    		   
    		   instsql = new String ("update "+outputesttable+" set estimatedpplcnt =" +Double.toString(data.instance(i).value(predictionindex))+    			 
    	    			  " where  ipadd like '"+IpAdd +"' and  curtime  between '"+IntervalStartstr+"' and '"+IntervalEndstr+"' and  timeofday = "+  Integer.toString((int)data.instance(i).value(timeofdayindex))+ ";" ) ;
    		   
    	   }
    	   
    	   if(loading_mode == "groundtruth")
    	   {
    		   instsql = new String ("update "+outputesttable+" set pplcnt =" +Double.toString(data.instance(i).value(predictionindex))+    			 
 	    			  " where  ipadd like '"+IpAdd +"' and  curtime  between '"+IntervalStartstr+"' and '"+IntervalEndstr+"' and  timeofday = "+  Integer.toString((int)data.instance(i).value(timeofdayindex))+ ";" ) ;
    		   
    	   }
    	   
    	  //curtime between '"+IntervalStartstr+"' and '"+IntervalEndstr+"' and
    	  System.out.println("Program-FeatureProcess "+instsql) ;
    	  log.log(Level.INFO,"Program-FeatureProcess "+instsql) ;
    	  st.executeUpdate(instsql) ;
    	  secst.executeUpdate(instsql) ;
    	
    	  /////////////////////////////////////////////
    	  
     	//  tempts.setTime(ts.getTime()- 3*60*60*1000)  ;
    	 
    	  
    	  
          
       /* String avgssql6 = "select cotwo from sensor_info_v2    where   ip like '%"+ IpAdd +"%'  and    curtime between '"+ tempts2.toString() +"' and '"+ tempts.toString() + "' ; "  ;
       
       
       String avgssql9 = "select avg(cotwo ) from sensor_info_v2    where   ip like '%"+ IpAdd +"%'  and    curtime between '"+ tempts2.toString() +"' and '"+ tempts.toString() + "' ; "  ;
       
       
       String avgssql12 = "select avg(cotwo ) from sensor_info_v2    where   ip like '%"+ IpAdd +"%'  and    curtime between '"+ tempts2.toString() +"' and '"+ tempts.toString() + "' ; "  ;
       
       */
     	             
                  }
      
      st2.close() ;
      
      st.close() ;secst.close();
      dbcon.close() ;secdbcon.close();
 
     /* DatabaseSaver save = new DatabaseSaver();
      save.setUrl(url);
      save.setUser(userid);
      save.setPassword(password);
      save.setInstances(data);
      save.setRelationForTableName(false);
      save.setTableName("mytable");
      save.connectToDatabase();
      save.writeBatch(); */
    }
  }