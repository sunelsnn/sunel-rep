package javautils;
//File   : data-arrays/dblsort/Dblsrt.java
//Purpose: To show how Arrays.sort() works with arrays
//       of both primitive and object values.
//Author : Fred Swartz 2006-08-23.  Public domain.

import java.util.Arrays;
import java.util.Vector;

public class Dblsrt {
	
	private Vector<String> teststring ;
	
	Dblsrt(String s) {  
		teststring = new Vector<String>() ;
		teststring.add(s) ; }
	
	public Vector<String> getString() 
	{
		return teststring ;
	}
 //========================================================= main
 public static void main(String[] args) {
     //... 1. Sort strings - or any other Comparable objects.
     String[] names = {"Zoe", "Alison", "David"};
     Arrays.sort(names);
     System.out.println(Arrays.toString(names));

     //... 2. Sort doubles or other primitives.
     double[] lengths = {120.0, 0.5, 0.0,120.0, 999.0, 77.3};
     Arrays.sort(lengths);
     System.out.println(Arrays.toString(lengths));
     
     Dblsrt d1= new Dblsrt("ABC") ;
     Vector<String> t1 = d1.getString() ;
     System.out.println(t1) ;
     t1.add("DEF") ;
     System.out.println(d1.getString()) ;
     System.out.println(t1) ;
     
     
     // afadsf
 }
}