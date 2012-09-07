package HW4;

import java.util.Random;

public class HW4564 {

	/**
	 * @param args
	 */
	public static int[][] Amat = new int[2][2] ;
	public static float[][] qval = new float[2][2] ;
	public static  float[] player1_prob_action1_array = new float[10000] ;
	public static  int[] player1_action1_array = new int[10000] ;
	
	public static float player1_prob_action1=(float)0.5 ;
	public static float player2_prob_action1=(float)0.5 ;
	public static float alpha = (float) 0.3 ;
	public static float epsilon = (float) 0.2 ;
	public static int player1_action1_count=0 ;
	public static int player1_action2_count=0;
	public static int player2_action1_count=0;
	public static int player2_action2_count=0 ;
	
	public static void  initHW4564()
	{   Amat[0][0]= 3;
	    Amat[0][1]=0; 
	    Amat[1][0]=5;
	    Amat[1][1]=1 ;
	    }
	
	public  static float expectedpay(int val1, float otherplayer_p1, int val2, float otherplayer_p2)
	{
		return val1*otherplayer_p1+val2*otherplayer_p2 ;
		
		
	}
	public static void qupdate ()
	{
		qval[0][0] = (1-alpha)*qval[0][0] + alpha*expectedpay(Amat[0][0],player2_prob_action1,Amat[0][1],1-player2_prob_action1) ;
		qval[0][1] = (1-alpha)*qval[0][1]+  alpha* expectedpay(Amat[1][0],player2_prob_action1,Amat[1][1],1-player2_prob_action1) ;
		qval[1][0] = (1-alpha)*qval[1][0]+ alpha*expectedpay(Amat[0][0],player1_prob_action1,Amat[0][1],1-player1_prob_action1) ;
		qval[1][1] = (1-alpha)*qval[1][1]+ alpha*expectedpay(Amat[1][0],player1_prob_action1,Amat[1][1],1-player1_prob_action1) ;
		
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		initHW4564() ;
		Random r1 = new Random();
		Random r2 = new Random();
		qupdate () ;
		System.out.println(qval[0][0]+" "+qval[0][1]+" "+qval[1][0]+" "+qval[1][1]) ;
		for(int i=0 ; i <10000; i++)
		{
			
			 player1_action1_count=0 ;
			player1_action2_count=0;
			 player2_action1_count=0;
			 player2_action2_count=0 ;
			for (int j=0 ; j< 1000 ; j++)
			{
				
				
				
				////////////// PLAYER X /////////////////////////
				 if (r1.nextFloat() < epsilon)                       // EXPLORATION
				 {			   if(qval[0][0] <= qval[0][1])
				 				{     player1_action1_count++ ;} 
				 				else 
				 				{   player1_action2_count++ ;}
				 }
				 else												// EXPLOITATION 
				 {			 if(qval[0][0] > qval[0][1])
				 				{     player1_action1_count++ ;}   
				 			else
				 			{     player1_action2_count++ ;} 
					 
				 }
				 
				 ///////////////////// PLAYER Y ///////////////////////////
				 if (r2.nextFloat() < epsilon)                       // EXPLORATION
				 {			   if(qval[1][0] <= qval[1][1])
				 				{     player2_action1_count++ ;} 
				 				else 
				 				{   player2_action2_count++ ;}
				 }
				 else												// EXPLOITATION 
				 {			 if(qval[1][0] > qval[1][1])
				 				{     player2_action1_count++ ;}   
				 			else
				 			{     player2_action2_count++ ;} 
					 
				 }
				 
				 		
				 
				 
				 
			}
				
			player1_prob_action1 =   ( (float) player1_action1_count/1000 ) ;
			player2_prob_action1 =    ( (float) player2_action1_count/1000 ) ;
			player1_prob_action1_array[i] = player1_prob_action1 ;
			 player1_action1_array[i] = player1_action1_count ;
			qupdate() ;
			System.out.println(qval[0][0]+" "+qval[0][1]+" "+qval[1][0]+" "+qval[1][1]) ;
			
		}
		
		for (int i=0 ; i<10000 ; i++)
		{  System.out.println(player1_prob_action1_array[i] +" " + player1_action1_array[i] ) ; }
	}

}
