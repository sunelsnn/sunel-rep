package HW3585;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Hw3 {

	/**
	 * @param args
	 */
	
	/* public enum qtype {
		
		q1, q2, q3, q4, q5, q6, q7 }  */ 
	
	private  static String userid;
	private static   String password ;
	private  static  String url ;
	private static  String driver = "com.mysql.jdbc.Driver" ;
	
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
	
	
		
	
	public static void main(String[] args) throws IOException, SQLException {
		// TODO Auto-generated method stub

		
		// qtype qt = (qtype)(args[0]) ;
	
		if(args.length < 3)
		{ System.out.println("the args is greater than 3 for q1 :  totalsargs "+args.length) ; }
		
	String dbconfigfile = new String (args[0] ) ;
	
	BufferedReader  freader = new  BufferedReader ( new  FileReader(dbconfigfile ) ) ;
	   

	  url =  "jdbc:mysql://" +  freader.readLine().trim() + ":" + freader.readLine().trim() + "/" + freader.readLine().trim() ;
	  
	  userid = freader.readLine().trim() ;
	  
	  password = freader.readLine().trim();
	  
	  freader.close();
	  
	 Connection dbcon = getDBconnection() ;  
	  Statement qst = dbcon.createStatement() ;	
	 
	String questionno =  args[1].trim() ;	
	String[] qargs  = questionno.split("q") ;
	switch(Integer.parseInt(qargs[1])) 
	{
	case 1 :
		
		if(args.length != 3)
		{ System.out.println("the args is not equal to  3 for q1 :  totalsargs "+args.length) ; }
		
		String query1=  new String(" select callsign, concat( X(EndPoint(path)),',',Y(EndPoint(path))) from flights where type = '"+args[2].trim()+"';" );
		
		System.out.println(query1) ;
		ResultSet rs = qst.executeQuery(query1);
		
		
		while(rs.next())
		{
			System.out.println(rs.getString(1)+" "+ rs.getString(2)) ;
		}
		rs.close() ;
				
		break ;
		
	case 2 :	
		
		String polystr = new String() ;
		 for ( int index=0 ; index<args.length-2;)
		 {
			 if (polystr.length() == 0)
			 { polystr = args[3+index]+" "+args[2+index] ; }
			 else
				 { polystr = polystr+ ", "+args[3+index]+" "+ args[2+index] ; }
			 index=index+2 ;
		 }
		 
		 polystr = polystr+","+args[3]+" "+args[2] ;
		String polyset = "set @testp = PolygonFromText('Polygon(("+polystr+"))')" ;
		System.out.println(polyset) ;
		String query2= new String(" select ID,Name, concat( X(latlong),',', Y(latlong)) , types, frequency, contains(@testp, latlong ) from navaids  where contains(@testp, latlong) =1 ") ;
		System.out.println(query2) ;
		qst.execute(polyset) ;
		ResultSet rsq2 = qst.executeQuery(query2);
		
		while(rsq2.next())
		{
			System.out.println(rsq2.getString(1)+" "+ rsq2.getString(2)+" "+ rsq2.getString(3)+" "+ rsq2.getString(4)+" "+rsq2.getDouble(5)) ;
		}
		rsq2.close() ;
		
			
		
		break ;
		
	case 3 :	
		

		if(args.length != 4)
		{ System.out.println("the args is not equal to 4 for q3 :  totalsargs "+args.length) ; }
		
		String query3 = new String( "select F.callsign, gcdist( N.latlong, EndPoint(F.path)), F.type from flights F, navaids N where N.ID='"+args[2].trim()+"'  and gcdist(N.latlong, EndPoint(F.path)) <"+args[3].trim()+";") ;
		
		System.out.println(query3) ;
		ResultSet rsq3 = qst.executeQuery(query3);
		
		while(rsq3.next())
		{
			System.out.println(rsq3.getString(1)+" "+ rsq3.getDouble(2)+"nm "+ rsq3.getString(3)) ;
		}
		rsq3.close() ;
				
		break ;
		
		
     
	
	case 4 :
		

		if(args.length != 3)
		{ System.out.println("the args is not equal to 3 for q4 :  totalsargs "+args.length) ; }
		
		String query4 = new String( "select ID, name from restricted where ID = '"+args[2].trim()+"' union select F.callsign, F.type from flights F, restricted R where Intersects(R.poly, F.path)=1 and  R.ID = '"+args[2].trim()+"';") ;
		System.out.println(query4) ;
		ResultSet rsq4 = qst.executeQuery(query4);
		
		while(rsq4.next())
		{
			System.out.println(rsq4.getString(1)+" "+ rsq4.getString(2)) ;
		}
		rsq4.close() ;
				
		break ;
	
	case 5 :
		

		if(args.length != 3)
		{ System.out.println("the args is not equal to 3 for q5 :  totalsargs "+args.length) ; }
		
		
		String query5 = new String("select distinct F1.callsign, F2.callsign ,gcdist(EndPoint(F1.path),EndPoint(F2.path))  from flights F1, flights F2 where gcdist(EndPoint(F1.path),EndPoint(F2.path)) <"+ args[2].trim()+"  and F1.callsign <>  F2.callsign ") ;
		System.out.println(query5) ;		
		ResultSet rsq5 = qst.executeQuery(query5);
		
		while(rsq5.next())
		{
			System.out.println(rsq5.getString(1)+" "+ rsq5.getString(2)+" "+ rsq5.getDouble(3)) ;
		}
		rsq5.close() ;
				
					
				break ;
	case 6 :			
				

		if(args.length != 4 )
		{ System.out.println("the args is not equal to 4 for q6 :  totalsargs "+args.length) ; }
				String query6 = new String("update navaids set frequency ="+args[3].trim()+" where ID = '"+args[2].trim()+"'; ") ;
				System.out.println(query6) ;
				int rsq6 = qst.executeUpdate(query6);
				
				System.out.println(" total rows updates "+rsq6) ;
				
	
				break ;
	case 7 :
			

		if(args.length != 3)
		{ System.out.println("the args is not equal to 3 for q7 :  totalsargs "+args.length) ; }
		
		String query7 = new String( "delete from restricted where ID = '"+args[2].trim()+"'") ;
		System.out.println(query7) ;
		int rsq7 = qst.executeUpdate(query7);
		
		System.out.println(" total rows updates "+rsq7) ;
		
				break ;
				
	}
				

	qst.close();
	dbcon.close();
				
	}

}
