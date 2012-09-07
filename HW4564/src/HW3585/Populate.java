
package HW3585 ;


import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;


public class Populate {

	/**
	 * @param args
	 * @throws FileNotFoundException 
	 * 
	 * 
	 * 
	 */
	
	private  static String userid;
	private static   String password ;
	private  static  String url ;
	private static  String driver = "com.mysql.jdbc.Driver" ;
	
	public void Populate()
	{
		url = new String() ;
	}
public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub

if(args.length != 4)	{ System.out.println(" not enough args") ;System.exit(0) ; }

String dbconfigfile = new String (args[0] ) ;
String navaidsfile = new String (args[1]) ;
String restrictedfile = new String (args[2]) ;
String flightsfile = new String (args[3]) ;



BufferedReader  freader = new  BufferedReader ( new  FileReader(dbconfigfile ) ) ;
   

  url =  "jdbc:mysql://" +  freader.readLine().trim() + ":" + freader.readLine().trim() + "/" + freader.readLine().trim() ;
  
  userid = freader.readLine().trim() ;
  
  password = freader.readLine().trim();
  
  freader.close();
  
  Connection dbcon = getDBconnection() ;
  Statement navaidinsertst = dbcon.createStatement() ;
  Statement restrictst = dbcon.createStatement() ;
  Statement flightst = dbcon.createStatement() ;
  
  freader = new  BufferedReader ( new  FileReader(navaidsfile ) ) ;
  
  String testline = new String() ;
  String[] testlinearr ;
  String[] testlinearr1 ;
  String[] testlinearr2  ;
  while((testline=freader.readLine())!= null )
  {
	  
	 
	testlinearr = testline.split("\"") ;  
	testlinearr1 = testlinearr[0].split(",") ;
	testlinearr2= testlinearr[2].split (",")  ;
	
	String insertvalstr = "'"+testlinearr1[0]+"','"+testlinearr[1] + "',PointFromText('point("+testlinearr2[2]+" "+testlinearr2[1]+")'),'"
	+testlinearr2[3] +"',"+ testlinearr2[4] ;
	
	System.out.println(insertvalstr) ;
	navaidinsertst.execute("insert into navaids values ("+insertvalstr+");") ;

  }
  
    
  navaidinsertst.close();
  freader.close() ;
    
  freader = new  BufferedReader ( new  FileReader( restrictedfile) ) ;
  
  while((testline=freader.readLine())!= null)
  {
	testlinearr = testline.split(",") ;
	
	String insertarg = new String() ;
   for (int index=0; index< testlinearr.length-2 ; )
   {
	   insertarg= insertarg+ testlinearr[3+index]+" "+testlinearr[2+index]+", " ;
	      index=index+2 ;
   }
	insertarg= insertarg+ testlinearr[3]+" "+testlinearr[2] ;
	String insertvalstr = "'"+testlinearr[0]+"','"+testlinearr[1]+"',PolyFromText('POLYGON(("+insertarg+"))')" ; 
	  
	System.out.println("insert into restricted values ("+insertvalstr+");") ;
	restrictst.execute("insert into restricted values ("+insertvalstr+");") ;
  }
  
  restrictst.close();
  freader.close();
  
  freader = new  BufferedReader ( new  FileReader( flightsfile) ) ;
  while((testline=freader.readLine())!= null)
  {
	  testlinearr = testline.split(",") ;
	  String insertarg = new String() ;
	  
	  for (int index=0 ;index< testlinearr.length-2; )
	  {
		  
		  if(insertarg.length()==0)
		  {  insertarg=testlinearr[3+index]+" "+testlinearr[2+index] ; }
		  else {
		  insertarg= insertarg+","+ testlinearr[3+index]+" "+testlinearr[2+index] ; }
		  index=index+2 ;
	  }
	  String insertvalstr =  "'"+testlinearr[0]+"','"+testlinearr[1]+"',LineStringFromText('LINESTRING("+insertarg+")')" ;
	  
	  System.out.println("insert into flights values ("+insertvalstr+");") ;
	  flightst.execute("insert into flights values ("+insertvalstr+");");
	  
  }
  

  flightst.close() ;
  freader.close();
  dbcon.close() ;



	}


public static   Connection getDBconnection()  throws SQLException 
{
	 Connection   con ;
	 try {
		Class.forName(driver);	
	} catch(java.lang.ClassNotFoundException e) {
		 //System.err.print(”ClassNotFoundException: “);
		// System.err.println(e.getMessage());
		
		throw new SQLException( "ClassNotFoundException " + e.getMessage()) ;
	}

	System.out.println (url+"\n"+ userid+"\n"+password) ;
	try {
	    con = DriverManager.getConnection(url, userid, password);
	} catch(SQLException ex) {
		// System.err.println(”SQLException: ” + ex.getMessage());
		throw new SQLException( ex.getMessage()) ;
	}

	return con;
	
       	  
	  
}	

}
