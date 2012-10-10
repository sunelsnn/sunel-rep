package javautils;
//File   : data-arrays/dblsort/Dblsrt.java
//Purpose: To show how Arrays.sort() works with arrays
//       of both primitive and object values.
//Author : Fred Swartz 2006-08-23.  Public domain.

import java.util.Arrays;

public class Dblsrt {
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
     
     
     // afadsf
 }
}