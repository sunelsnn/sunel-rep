import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;


public class ThreadUtil  extends Thread {
		
	
	int threadtype ;
	int id ;
//	int limit = 1000 ;
//	static BlockingQueue  BQobj= null ; 
	 private  static List queue = null ; // = new LinkedList();
	 private static int  limit = 1000;

	
	/*ThreadUtil (int limit, int type)
	{
		BQobj = new BlockingQueue(limit) ;
		threadtype = type ;
	}
	*/
	
	 ThreadUtil(int idno)
	 {
		 if (queue == null)
		 {
			 queue = new LinkedList(); 
			  System.out.println("static queue intialized") ;
		 }
		 id =idno ;
	 }
	 public void  setType(int type)
	 {
		 if ( ! (type ==0 || type ==1 ) )
		 {
			 
			 System.out.println("Type is neither 0 or 1") ;
			 System.exit(0) ;
		 }
		 threadtype = type ;
		 
	 }
	 /*
	ThreadUtil (int type)
	{
	
		if(BQobj == null )
		{
			BQobj = new BlockingQueue(limit) ;
			System.out.println("BQ object instantiated") ;
		}
		
		threadtype = type ;
		
		
	}
	*/
	 public synchronized void enqueue(Object item)
	  throws InterruptedException  {
		 
	    while(this.queue.size() == this.limit) {
	    	   System.out.println(" Enqueue waiting ID#" + id) ;
	      wait();
	      System.out.println(" Enqueue Resume ID#" + id) ;
	    }
	   
	    if(this.queue.size() == 0) {
	        System.out.println("Notifying all") ;
	      notify();
	    }
	    this.queue.add(item);
	  //  notify() ;
	    System.out.println("Enqueue") ;
	  }


	  public synchronized Object dequeue()
	  throws InterruptedException{
	    while(this.queue.size() == 0){
	    	 System.out.println("Dequeue waiting ID# "+id) ;
	          wait();
	          System.out.println("Dequeue Resume ID# "+id) ;
	    }
	   
	    if(this.queue.size() == this.limit){
	      notify();
	    }
	    System.out.println("Dequeue") ; 	
	    return this.queue.remove(0) ;
	  }
	
	public void run()
	{
		int count =0 ;
		
		while(count < 10)
		{
		try {
		if (threadtype == 0)
			
			{ enqueue( (int )Math.random()) ;
			
			}
		else if(threadtype == 1)
		{
			dequeue() ;
		}
		}
		catch(Exception E)
		{
			E.printStackTrace() ;
			
		}
		/*
		finally 
		{
			System.out.println("Some exception and exiting") ;
		//	System.exit(0) ;
		}
			*/
		count++ ;
		}
	}
	
	
	
	
	public static void main (String[] args) 
	{
		try{
		
		ArrayList<ThreadUtil> TUobjP =  new ArrayList<ThreadUtil>() ;//   = new ThreadUtil(1) ;
		ArrayList<ThreadUtil> TUobjC =  new ArrayList<ThreadUtil> () ;
	
		// Iterator<ThreadUtil> iter ;
		for (int i=0; i< 10 ;i++)
		{
			
			TUobjP.add(new ThreadUtil(i)) ;
			TUobjC.add(new ThreadUtil(10+i)) ;
			TUobjP.get(i).setType(0); // = new ThreadUtil(0) ;
			TUobjC.get(i).setType(1) ; //= new ThreadUtil(1) ;
			TUobjP.get(i).start() ;
			TUobjC.get(i).start() ;
			
			
		}
		
		for (int i=0; i< 10 ;i++)
		{
			TUobjP.get(i).join() ;
			System.out.println("joined "+i+" consumer") ;
			TUobjC.get(i).join();
			// TUobjC[i].run() ;
			System.out.println("joined "+ (int)(i+10)+" consumer") ;
		}
		
				
		
		}
		catch(Exception E)
		{
			E.printStackTrace() ;
		}
		finally
		{
			
			
		}
		
	}

}
