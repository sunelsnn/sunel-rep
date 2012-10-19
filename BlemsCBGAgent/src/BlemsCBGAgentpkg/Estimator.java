package edu.isi.blems.BlemsCBGAgent;

import java.io.BufferedReader;
import java.lang.Math ;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import weka.classifiers.Classifier;
import weka.core.Instances;
import weka.core.converters.ConverterUtils.DataSource;


public class Estimator {

	/**
	 * 
	 * Estimator.java interacts with FeatureProcess in following way. 
	 * It inserts two instances in an arff file , one instance has the timeofday, estimated pplcnt, 
	 * and other instance has timeofday, with estimatedpplcnt=0.  The FeatureProcess uploads the estimatedpplcnt for the first instance and calculates
	 * correlational features for the second one.  
	 * 
	 * 
	 * param
	 *  a model file , SVM15, MLP10
	 *  a arff file with all the features (can't it just take day and time and start the estimation ?)
	 *  a Date with out time information
	 *  start timeofday
	 *  end timeofday
	 * 	 *  
	 */
	 // private static String  logclass = new String( getClass().getName()) ;
	
	private static Logger log ;// = Logger.getLogger(new String (logclass));
	    private static String userid ; //
		private static String password ;// 
		private static String url; //
		private static String driver; // 
		 private static String IpAdd ;//
		// private static String IpAdd = "" ;
	    private static String lab; // = "CBG" ;
	    private static String outputesttable ;
	    private static String primaryconfig= "primary" ;// 
	    private static String secconfig=  "secconfig" ; //
	    private static boolean is_pplcounter=false ;
	    private static String peoplecounter ;// 
	    private static int batchsize ;
	    private static String inputinfotable ;
		
	    
// TestModels
	    
	   public  Estimator(Logger log) throws Exception
	    {
	    	
	    	//String  logclass = new String( getClass().getName()) ;
	    	//log = Logger.getLogger(new String (logclass));
	    	
	    	this.log = log ;
	    	load_config("primary") ;	
	    	 ExtractRawDatadbinfo() ;
	    }
	    
	    public void  ExtractRawDatadbinfo() throws IOException
		  {
				BufferedReader  freader = new  BufferedReader ( new  FileReader("./dbconfig.txt" ) ) ;
				String testline = new String() ;
				String[] testlinearr ;
				while((testline=freader.readLine())!= null )
				{
					 // System.out.println(testline);
					 
			   /*		if(testline.contains("IpAdd")) 
					{
					  	testlinearr = testline.split("=") ;
					  	  IpAdd=testlinearr[1].trim() ;
					  	  System.out.println(IpAdd);
					}
					
					
					
					if(testline.contains("lab")) 
					{
					  	testlinearr = testline.split("=") ;
					  	  lab=testlinearr[1].trim() ;
					  	 System.out.println(lab) ;
					}
					
					*/
					if(testline.contains("inputinfotable"))
					{
						testlinearr= testline.split("=") ;
						inputinfotable = testlinearr[1].trim();
						System.out.println("Program:Estimator:"+ inputinfotable) ;
						log.log(Level.INFO,"Program:Estimator:"+ inputinfotable) ;
					}
					if(testline.contains("outputesttable"))
					{
						testlinearr=testline.split("=") ;
						outputesttable=testlinearr[1].trim();
						System.out.println("Program:Estimator:"+outputesttable) ;
						log.log(Level.INFO,"Program:Estimator:"+outputesttable) ;
					}
					if(testline.contains("peoplecounter"))
					{  testlinearr=testline.split("=") ;
					peoplecounter = testlinearr[1].trim() ;
					System.out.println("Program:Estimator:"+peoplecounter) ;
					log.log(Level.INFO,"Program:Estimator:"+peoplecounter) ;
						}
					if(testline.contains("is_pplcounter"))
					{  testlinearr = testline.split("=") ;
					is_pplcounter = Boolean.parseBoolean(testlinearr[1].trim());
					System.out.println("Program:Estimator:"+is_pplcounter) ;
					log.log(Level.INFO,"Program:Estimator:"+is_pplcounter) ;
						
					}
					if(testline.contains("batchsize"))
					{
						testlinearr = testline.split("=") ;
						batchsize = Integer.parseInt(testlinearr[1].trim());
						System.out.println("Program:Estimator:"+batchsize) ;
						log.log(Level.INFO,"Program:Estimator:"+batchsize) ;
					}
				}
				
				freader.close() ; 
				}
		public static void reset_config() 
		  {
			  
			  driver="" ;
			  password="";
			  url="";
			  userid="";
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
				  	 System.out.println(password) ;
				  	log.log(Level.INFO,password) ;
				}
				
				if(testline.contains("url")) 
				{
				  	testlinearr = testline.split("=") ;
				  	  url=testlinearr[1].trim() ;
				  	  System.out.println(url) ;
				  	log.log(Level.INFO,url) ;
				}
				
				if(testline.contains("driver")) 
				{
				  	testlinearr = testline.split("=") ;
				  	  driver=testlinearr[1].trim() ;
				  	 System.out.println(driver) ;
				  	log.log(Level.INFO,driver) ;
				}
				
		
				if(testline.contains("userid")) 
				{
				  	testlinearr = testline.split("=") ;
				  	  userid=testlinearr[1].trim() ;
				  	 System.out.println(userid) ;
				  	log.log(Level.INFO,userid) ;
				}
				} 
				} else { continue ;}
				}
				
				freader.close();
		  }
	
	    
	    /*  returns a Connection object
	     *  
	     */
	    public static  Connection getDBconnection()  throws SQLException //String driver, String url, String userid, String password )  throws SQLException 
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
	    
		
		
	 /* public static void main(String[] args) throws Exception  {
		// TODO Auto-generated method stub

		if( args.length != 5 ) { 
			System.out.println(args.length) ;
			System.exit(0) ;}
		String modelfilename = args[0] ;
		String arfffile = args[1] ; 
		String strdate1 = args[2] ;
		int  timeofdaystart = Integer.parseInt(args[3]);
		int  timeofdayend = Integer.parseInt(args[4]);
		
		*/ 
		
	    /* estimates 
	     * we dont need second argument arfffilename here because,given a date and timeofday, the database is queried and the features are retrieved 
	     * and then processed into a arfffile, which will be subjected to the given model and the results are loaded into the database.
	     * 
	     */
		public  void estimate(String modelfile, String arfffilename, Calendar strt, int temporalreadingstart , int  temporalreadingend, String featurelist, int featurecount, int[] featureDataType, String roomid, String ipadd ) throws Exception
				{
			
			System.out.println( "Program:Estimator: Estimate") ;
			log.log(Level.INFO,"Program:Estimator: Estimate") ;
		lab = roomid ;
		IpAdd = ipadd ;
			String modelfilename = modelfile ;
			String arfffile = arfffilename ;
		// 	String strdate1 = stringdate ;
		 int timeofdaystart = (int)(strt.get(strt.HOUR_OF_DAY)*60+ strt.get(strt.MINUTE) + temporalreadingstart)%1440 ;
			int  timeofdayend =  (int)(strt.get(strt.HOUR_OF_DAY)*60+ strt.get(strt.MINUTE) + temporalreadingend)%1440 ;
			
			
		
		 DateFormat df =  new SimpleDateFormat("yyyy-MM-dd HH:mm:ss") ;
		//  Date start_date = df.parse(strdate1) ;
		 Calendar sc1 = Calendar.getInstance() ; 
		    
		    Calendar  ec1 = Calendar.getInstance() ;
		    // ec1.setTimeInMillis(sc1.getTimeInMillis()+  24*60*60*1000 ) ;
		     
		    
		 
		      /////////////// NOT REQUIRED JUST INTIALISATION WITH JUNK INFORMATION
		      
		      sc1.setTimeInMillis(strt.getTimeInMillis() + temporalreadingstart*60*1000)  ;
		      ec1.setTimeInMillis(strt.getTimeInMillis() + temporalreadingend*60*1000 )  ;
		      
		      String IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
	    			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
	    	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
	    	  Integer.toString( sc1.get(sc1.SECOND ) )) ;
	    	  
	    	  //Integer.toString( 15*(int)(startInt.get(startInt.MINUTE)/15) ) + ":00" ) ;
	    	    	 
		  //  String IntervalEndstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
	    //			 +"-"+ Integer.toString(sc1.get(sc1.DATE)+1)+" 0:0:0") ;//+
		    
		    String IntervalEndstr = new String( Integer.toString( ec1.get(ec1.YEAR))+"-"+Integer.toString(ec1.get(ec1.MONTH)+1)
	    			 +"-"+ Integer.toString(ec1.get(ec1.DATE))+" "+
	    	  Integer.toString(ec1.get(ec1.HOUR_OF_DAY)) +":"+ Integer.toString( ec1.get(ec1.MINUTE) ) + ":" +
	    	  Integer.toString( ec1.get(ec1.SECOND ) )) ;
		    ////////////////////////////NOT REQUIRED JUST INTIALISATION WITH JUNK INFORMATION
	    	  //Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
	    	  // Integer.toString( sc1.get(sc1.SECOND ) )) ;
		    
		    
	    	    	
		
		// System.out.println(args[0]+ " "+ args[1]) ;
		
		
		
		StringBuffer Dsource = new StringBuffer();
		BufferedReader  freader = new  BufferedReader ( new  FileReader(arfffile ) ) ;
		String testline = new String() ;
		while( ((testline = freader.readLine())!= null) && (!testline.matches("@data")))
		{
			//testline = freader.readLine() ;
			 Dsource.append(testline + "\n") ;
		}
		Dsource.append("@data \n") ;
		// if(testline)
		// Dsource.append("@data\n") ;
		freader.close() ;
		
		 Instances testdata = new DataSource( arfffile).getDataSet() ;
		//  testdata.
		 //DataSource source = new DataSource(in);
        // Instances instances = source.getDataSet();
		 ExtractRawDatadbinfo() ;
		 load_config("primary") ;	
		 Connection dbcon = getDBconnection(); // driver, url, userid, password) ;
		 reset_config() ;
		 load_config("secconfig") ;
		// Connection dbcon = getDBconnection(); 
		
		Connection Secdbcon = getDBconnection();
		 reset_config();
		 
    Statement st1= dbcon.createStatement() ;//  = new Statement();
    Statement Secst1= Secdbcon.createStatement() ;
    
 	String tmpfile = "/root/workspace2/tmparff.arff" ;
 	String predictpplcntfile = "/root/workspace2/prepplcnt.arff" ;
 	StringBuffer prepplcntbuffer = new StringBuffer() ;
 	prepplcntbuffer.append("@relation occupancy\n\n@attribute timeofday numeric\n@attribute predictedpplcnt numeric\n\n@data\n") ; 
 	
 	FeatureProcess.setLogger(log); 
 	FeatureProcess.setIpAdd(IpAdd) ;
 	FeatureProcess.setLab(lab) ;
 	int timeofday_cal ;
 			
		// for ( int i =0 ; i< testdata.numInstances() ;i++)
 // 	for ( int i =timeofdaystart ; i<=timeofdayend ;i++)
 	for(int indexep =temporalreadingstart ; indexep<=temporalreadingend ; indexep++)
 	//for ( int i =0 ; i< 10  ;i++)
		{    
			 StringBuffer  tempbuff = new StringBuffer(Dsource) ;
			// tempbuff.append(testdata.instance(i)) ;
			 
		/* String  sqlinst = new String("select timeofday,co2, avgco23,avgco26,avgco29,avgco212, asavg0_6,asavg6_9,asavg9_12,asavg12_15"+
",coravgco23,coravgco26,coravgco29,coravgco212,autocor2_1,autocor3_2,autocor4_3, motioncntdiff,beamcntdiff,motion, pplcnt"+
 " from Sensor_est_data where curtime between '"+ IntervalStartstr +"' and '"+ IntervalEndstr +"' and timeofday = "+ i+";") ;  */
			 
			 
//			 String  sqlinst = new String("select timeofday,co2, avgco23,avgco26,avgco29,avgco212, asavg0_6,asavg6_9,asavg9_12,asavg12_15"+
//					 ",autocor2_1,autocor3_2,autocor4_3, motioncntdiff,beamcntdiff,motion, pplcnt"+
//					  " from "+ outputesttable +"where curtime between '"+ IntervalStartstr +"' and '"+ IntervalEndstr +"' and timeofday = "+ i+";") ;
			 
			 sc1.setTimeInMillis(strt.getTimeInMillis() + indexep*60*1000)  ;
			 ec1.setTimeInMillis(strt.getTimeInMillis() +  (indexep+1)*60*1000 )  ;
			 
			IntervalStartstr = new String( Integer.toString( sc1.get(sc1.YEAR))+"-"+Integer.toString(sc1.get(sc1.MONTH)+1)
	    			 +"-"+ Integer.toString(sc1.get(sc1.DATE))+" "+
	   	    	  Integer.toString(sc1.get(sc1.HOUR_OF_DAY)) +":"+ Integer.toString( sc1.get(sc1.MINUTE) ) + ":" +
	   	    	  Integer.toString( sc1.get(sc1.SECOND ) )) ;
			
			  IntervalEndstr = new String( Integer.toString( ec1.get(ec1.YEAR))+"-"+Integer.toString(ec1.get(ec1.MONTH)+1)
	    			 +"-"+ Integer.toString(ec1.get(ec1.DATE))+" "+
	    	  Integer.toString(ec1.get(ec1.HOUR_OF_DAY)) +":"+ Integer.toString( ec1.get(ec1.MINUTE) ) + ":" +
	    	  Integer.toString( ec1.get(ec1.SECOND ) )) ;
	   	    	  
			 
			  timeofday_cal = (strt.get(strt.HOUR_OF_DAY)*60+ strt.get(strt.MINUTE) + (indexep+1))%1440  ;
			  String  sqlinst = new String("select " +	featurelist+ " from "+ outputesttable +" where ipadd ='"+ipadd+"' and curtime between '"+ IntervalStartstr +"' and '"+ IntervalEndstr +"' and timeofday = "+ timeofday_cal +";") ;
			 System.out.println(sqlinst) ;
			 log.log(Level.INFO,sqlinst) ;
 //timestamp('2011-07-29 00:00:00')"  ;
			ResultSet rs1 = st1.executeQuery(sqlinst) ;
	// rs1.beforeFirst() ;
				int countrs1 = 0 ;
				while(rs1.next()) { 
			// System.out.println( rs1.getInt(1)) ; 
	
			
			/* KAP /CBG   10 attrib model
			tempbuff.append(Integer.toString(rs1.getInt(1))
					  +","+Float.toString(rs1.getFloat(2))+","+ Float.toString(rs1.getFloat(3))+","+ Float.toString(rs1.getFloat(4)) +","+ 
					  Float.toString(rs1.getFloat(5))+","+ Float.toString(rs1.getFloat(6))+","+Float.toString(rs1.getInt(7))+","+
					  Float.toString(rs1.getInt(8))+","+ Float.toString(rs1.getInt(9)) +
					 ","+ Float.toString(rs1.getInt(10)) +"\n");
					 */
			
			
			
			// use this for CBG 17 attrib 
			/*		 tempbuff.append(Integer.toString(rs1.getInt(1))
			  +","+Float.toString(rs1.getFloat(2))+","+ Float.toString(rs1.getFloat(3))+","+ Float.toString(rs1.getFloat(4)) +","+ 
			  Float.toString(rs1.getFloat(5))+","+ Float.toString(rs1.getFloat(6))+","+Float.toString(rs1.getFloat(7))+","+
			  Float.toString(rs1.getFloat(8))+","+ Float.toString(rs1.getFloat(9)) +
			 ","+ Float.toString(rs1.getFloat(10)) +","+
			 Float.toString(rs1.getFloat(11))
			  +","+Float.toString(rs1.getFloat(12))+","+Float.toString(rs1.getFloat(13))+","+
			  Integer.toString(rs1.getInt(14))+","+ Integer.toString(rs1.getInt(15))+ ","+Integer.toString(rs1.getInt(16))+","+ 
			  Integer.toString(rs1.getInt(17))+"\n") ;
			  
			  
			  */
			
			// use this for CBG 15 attrib
			
			String argString = new String() ;
			for (int index5=0 ; index5< featurecount ;index5++)
			{
				if(featureDataType[index5]==0)
				{    
					if(argString.length() == 0)
						argString = Integer.toString(rs1.getInt(index5+1)) ;
					else 
					argString = argString +","+Integer.toString(rs1.getInt(index5+1)) ; 
					
				}
				else if (featureDataType[index5]==1)
					{ 
					if(argString.length() == 0)
						argString = Float.toString(rs1.getFloat(index5+1)) ;
					else
					argString = argString +","+Float.toString(rs1.getFloat(index5+1)) ; 
					
					}
				else if (featureDataType[index5]==2)
					{ 
					if(argString.length() == 0)
					argString =  rs1.getString(index5+1) ; 
					else 
						argString = argString+"," + rs1.getString(index5+1) ; 	
					}
		
			}
			
			
//			 tempbuff.append(Integer.toString(rs1.getInt(1))
//					  +","+Float.toString(rs1.getFloat(2))+","+ Float.toString(rs1.getFloat(4)-rs1.getFloat(3))+","+
//					  Float.toString(rs1.getFloat(5)-rs1.getFloat(4)) +","+  Float.toString(rs1.getFloat(6)-rs1.getFloat(5))+","+ 
//					//   Float.toString(rs1.getFloat(6))+","+Float.toString(rs1.getFloat(7))+","+
//					  Float.toString(rs1.getFloat(8)-rs1.getFloat(7))+","+ Float.toString(rs1.getFloat(9)-rs1.getFloat(8)) +
//					 ","+ Float.toString(rs1.getFloat(10)-rs1.getFloat(9)) +","+
//					 Float.toString(rs1.getFloat(11))
//					 +","+Float.toString(rs1.getFloat(12))+","+Float.toString(rs1.getFloat(13))+","+  Integer.toString(rs1.getInt(14))+","+ 
//					  Integer.toString(rs1.getInt(15))+ ","+Integer.toString(rs1.getInt(16))+","+ 
//					  Integer.toString(rs1.getInt(17))+"\n") ; 
			
			tempbuff.append(argString+"\n") ;
			System.out.println("Program-Estimator:Program:Estimator: arg string in tempbuff "+ argString) ;
			log.log(Level.INFO,"Program-Estimator:Program:Estimator: arg string in tempbuff "+ argString) ;
			
			countrs1++ ;
			
		
		}
		
		/*Float.toString(rs1.getFloat(11)) +","+ Float.toString(rs1.getFloat(12))+","+ 
			 Float.toString(rs1.getFloat(13))+","+ Float.toString(rs1.getFloat(14))+"," */
		System.out.println("Program-Estimator: count "+ countrs1 );
		log.log(Level.INFO,"Program-Estimator: count "+ countrs1 );
		
		// rsinst1.beforeFirst() ;
		// System.out.println("Program-Estimator: count "+ countrs1+" "+rsinst1.getObject(1) ) ;
		
			//  tempbuff.append(Float.toString(rsinst1.getFloat(1)) ) ;
					  //+","+rs1.getFloat(2)+","+ rs1.getFloat(3)+","+ rs1.getFloat(4) +","+ 
					 // rs1.getFloat(5)+","+ rs1.getFloat(6)					 +","+rs1.getFloat(7)+","+ rs1.getFloat(8)+","+ rs1.getFloat(9) +
					 //","+ rs1.getFloat(10) +","+
					 // rs1.getFloat(11) +","+ rs1.getFloat(12)+","+ rs1.getFloat(13)+","+ rs1.getFloat(14)+","+rs1.getFloat(15)
					 // +","+rs1.getFloat(16)+","+rs1.getFloat(17)+","+rs1.getInt(18)+","+ rs1.getInt(19)+ ","+rs1.getInt(20)+","+ rs1.getInt(21)+"\n") ;
			 
			 rs1.close() ;
		
			 if(countrs1!=0)
			 {
			 try { 
					FileWriter fwriter = new FileWriter( tmpfile);
					fwriter.write(tempbuff.toString(), 0, tempbuff.toString().length()) ;
					fwriter.close() ;
			 }catch(Exception E) { E.printStackTrace() ; }
			 
			 System.out.println("Program-Estimator: call "+indexep) ;
			 log.log(Level.INFO,"Program-Estimator: call "+indexep) ;
			 
			 
			double pplcntlabel =  runexp(modelfilename, tmpfile) ;
			StringBuffer temppplcntbuff = new StringBuffer(prepplcntbuffer) ;
			// temppplcntbuff.append(testdata.instance(i).value(0)+","+pplcntlabel+"\n"+testdata.instance(i+1).value(0)+",0\n") ;
			temppplcntbuff.append(Integer.toString(timeofday_cal)+","+pplcntlabel+"\n");//+Integer.toString(i+1)+",0\n") ;
			// the file should contain single instance for which prediction needs to be made
			// As soon as a instance is received process features and estimation and prediction.
			
			try {
				FileWriter fwriter = new FileWriter( predictpplcntfile);
				fwriter.write(temppplcntbuff.toString(), 0, temppplcntbuff.toString().length()) ;
				fwriter.close() ;
			}catch(Exception E) { E.printStackTrace() ; }
			 
			// FeatureProcess ad = new FeatureProcess()  ;
			
			System.out.println("Program-Estimator:Program:Estimator: Feature process is called for the next record") ;
			log.log(Level.INFO,"Program-Estimator:Program:Estimator: Feature process is called for the next record") ;
			// FeatureProcess.loading_mode = "estimation" ;
			Calendar testdate = Calendar.getInstance(); 
			testdate.setTimeInMillis(strt.getTimeInMillis()+ (indexep+1)*60*1000) ; // why was 60 seconds added ??
			// call Featureprocess to process features for next record that are already extracted by extractor.
		//	FeatureProcess.dataProcess(predictpplcntfile, testdate, lab, IpAdd) ;
			String pplcntpredupdate = new String("update SensorFeatures set estimatedpplcnt= " + pplcntlabel +" where curtime between '"+ IntervalStartstr +"' and '"+ IntervalEndstr +"' and timeofday = "+ timeofday_cal +" and ipadd ='"+ipadd+"';") ;
			System.out.println("Program:Estimator: Estimator "+ pplcntpredupdate) ;
			log.log(Level.INFO,"Program:Estimator: Estimator "+ pplcntpredupdate) ;
			st1.executeUpdate(pplcntpredupdate) ;
			Secst1.executeUpdate(pplcntpredupdate) ;
			
			FeatureProcess.loading_mode = "regular" ;
			FeatureProcess.dataProcessSingleInst( testdate, lab, IpAdd) ;
			FeatureProcess.loading_mode = "" ;
			String updatelastestimate =  new String ("update blemsRoom set estimatorlastupdate = '"+  new Timestamp(strt.getTimeInMillis()+(indexep+1)*60*1000).toString() +"' where roomid='"+lab+"';" );
			st1.executeUpdate(updatelastestimate) ;
			Secst1.executeUpdate(updatelastestimate) ;
			System.out.println("Program:Estimator: Estimator lastupdate time updated") ;
			log.log(Level.INFO,"Program:Estimator: Estimator lastupdate time updated") ;
			 }
		}
 	
 	st1.close() ;Secst1.close(); dbcon.close(); Secdbcon.close() ;
	}

	
	
	/**
	 *  runexp will need a learned model 
	 * 
	 * @param modelfilename    a learned model , MLP or SVM 
	 * @param arfffile   single instance arff file  for estimation 
	 * @return   estimation.
	 * @throws Exception
	 */
	
	public static double runexp(String modelfilename , String arfffile ) throws Exception
	{
		
		System.out.println("Program-Estimator: In runexp ") ;
		log.log(Level.INFO,"Program-Estimator: In runexp ") ;
		
		double labelreturn  = -1000 ;
		try { 
			 //FileWriter fwriter = new FileWriter( arfffile);
		//	fwriter.write(Dsource.toString(), 0, Dsource.toString().length()) ;
		//	fwriter.close() ;
			
		 // Classifier cls = (Classifier) weka.core.SerializationHelper.read(modelDir+"/"+modelfilename);
			Classifier cls = (Classifier) weka.core.SerializationHelper.read(modelfilename);
		  Instances testdata = new DataSource( arfffile).getDataSet() ;
		  Process p=Runtime.getRuntime().exec("cat "+arfffile);
		  System.out.println(p.getInputStream()) ;
		  System.out.println("Program-Estimator: total no of attributes " + testdata.numAttributes() ) ;
		  log.log(Level.INFO,"Program-Estimator: total no of attributes " + testdata.numAttributes() ) ;
		  
		  System.out.println("Program-Estimator: total no of instances " + testdata.numInstances() ) ;
		  log.log(Level.INFO,"Program-Estimator: total no of instances " + testdata.numInstances() ) ;
		  	  testdata.setClassIndex(testdata.numAttributes() - 1);
		   // double[]  attriarray = testdata.instance(0).toDoubleArray();
		  
		  
		  System.out.println("Program-Estimator: index 1 " + testdata.instance(0).value(1) +" index 2" + 
				  testdata.instance(0).value(2) ) ;
		  log.log(Level.INFO,"Program-Estimator: index 1 " + testdata.instance(0).value(1) +" index 2" +
				  testdata.instance(0).value(2) ) ;
		  double  timeofdayval = testdata.instance(0).value(0) ;
		  
		   double timetransform= 0.0 ;
		  //  Math mathobject = null ; 
		   
		   
		   
		   /***************** to make the timeofday feature to have a curve distribution
		    * *****************/
		    
		   if(timeofdayval > 1)
		   {
		   if(timeofdayval/60 > 12  ) 
		     testdata.instance(0).setValue(0, 1/( 1+Math.exp(-3*(7.5-timeofdayval/120))) ) ;
		   else 
			   testdata.instance(0).setValue(0, 1/( 1+Math.exp(3*(5.0-timeofdayval/120))) ) ;
		   }
		   	  double label =  cls.classifyInstance( testdata.instance(0)) ;
		   	  labelreturn = label ;
		   
		//  System.out.println(label+"\n") ;
		 System.out.println("Program-Estimator:"+ label) ;
		 log.log(Level.INFO,"Program-Estimator:"+ label) ;
		// return label ;
		}catch (Exception e) {  e.printStackTrace() ; }
		return labelreturn ;
	

	}
	
}
