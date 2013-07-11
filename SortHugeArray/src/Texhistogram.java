
/**
 *   textualHistogram.java
 *   Author: Sunil Mamidi
 *   Description:  Sorts a File with 1 million integers with atmost 2500 integers in memory in ascending order
 *   Logic : Linearly read the file into  block chunks of 2500 integers, and do in place sorting using java functions
 *   and store the stored blocks into different files. Merge the sorted files . Store the minimum most element
 *   from each file into the Array  (the size of this Array is 400 which is less than 2500 ). 
 *   Scan the above Array for minimum and it's count and repeat the scanning process until a there is no different in countvalue.
 *   The above scanning process repeats on maximum to 100000.
 * 
 */
import java.io.* ;
import java.math.*; 
import java.util.Arrays;
import java.util.concurrent.Callable;
public class Texhistogram {
	
	
	public class MergeThread implements Callable {
		
		String[] fileList;
		int totalFileCount;
		int[] inputFileSize;
		int[]  mergeWindow=null;
		int totalElementCount;
		String outputFile=null;
		
		MergeThread(String[] filelist, int[] fileSize, String outputFile) {
			this.fileList=filelist;
			this.totalFileCount=filelist.length;
			this.inputFileSize = fileSize;
			if(this.inputFileSize.length != totalFileCount) {
				System.out.println("the filelist  and filesize array has different sizes");
			}
			this.mergeWindow = new int[this.totalFileCount];
			
			this.totalElementCount=0;
			
			for(int i=0;i<this.totalFileCount;i++) {
			this.totalElementCount+=this.inputFileSize[i];
			}
			
			this.outputFile=outputFile;
			
		}
		@Override
		public Object call() throws Exception {
			
			// TODO Auto-generated method stub
			mergeOperation();
			return null;
		}
		
		private void mergeOperation() throws IOException {
			
			int minElement=Integer.MAX_VALUE;
			int secondBestMinElement=Integer.MAX_VALUE;
			int currentFrequencyCount=0;
			String tempStr;
			int totalFileReads = 0;
			int previousFrequencyCount=0;
			int prevTotalFileReads=0;
			BufferedWriter SortOutputFileWriter=null;
			int totalSortedElements=0;
			
			
			SortOutputFileWriter= new BufferedWriter( new FileWriter(this.outputFile));
			BufferedReader[]  mReaders= new BufferedReader[this.totalFileCount];
			
			for (int i=0; i<this.totalFileCount ; i++)
		    {
		    	mReaders[i] =  new BufferedReader ( new FileReader (this.fileList[i])) ;
		    	this.mergeWindow[i] =  Integer.parseInt(mReaders[i].readLine()) ;
		    	if(minElement > this.mergeWindow[i] )
		    		{ minElement = this.mergeWindow[i] ;  }
		    	
		    }
		    
			
			 for(int i=0; i<=this.totalElementCount ;i++ )
			    {
			        	
			    	//Linearly scan the Array for  (minelement,count)  and secondbestminelement .
			    	    	
			    	for (int j=0;j<this.totalFileCount ; j++)
			    	{
			    		
			    		// compare minimum element with elements in the array,
			    		//  a) if the minimum repeats increment its count and read the nextline from the corresponding file
			    		//  b) if the minimum > and an element in array, throw error
			    		//  c) if the minimum is less the element in the array , check for the second most minimum element.
			    		if (minElement < this.mergeWindow[j])
			    		{
			    			 if (  secondBestMinElement >  this.mergeWindow[j] && minElement < secondBestMinElement)
			    			 {
			    				 secondBestMinElement = this.mergeWindow[j] ;
			    			 }
			    			 else if( minElement== secondBestMinElement)
			    			 {
			    				 secondBestMinElement = this.mergeWindow[j]  ; 
			    			 }
			    			
			    			continue ;
			    		}
			    		else if (minElement ==  this.mergeWindow[j])
			    		{
			    			currentFrequencyCount++ ; 
			    			i++ ;
			    			
			    			if ( (tempStr = mReaders[j].readLine())!= null )
			    			{		this.mergeWindow[j] = Integer.parseInt(tempStr) ;
			    				totalFileReads++ ;
			    				    			
			    			}
			    			else 
			    			{
			    				this.mergeWindow[j] = Integer.MAX_VALUE ;
			    			}
			    		    
			    			
			    		}
			    		else if(minElement > this.mergeWindow[j])
			    		{
			    			System.out.println("Some error in sorting") ;
			    			System.exit(0);
			    			
			    		}
			    	   		
			    	}  // end for inner for loop

			    	// if there is a count difference of minimum value in previous and current iteration, then store it.
			    	// else  write the minimum element to the sorted file.
			    	if (previousFrequencyCount < currentFrequencyCount )
			    	 {  previousFrequencyCount = currentFrequencyCount ;
			    	   	 i=i-1 ;		
			    	   	 
			    	   	if (totalFileReads - prevTotalFileReads != 1) {
							System.out
									.println(" there was no read from memory mapped file : current counter "
											+ i);
						}
						prevTotalFileReads = totalFileReads;
			    	 }
			    	else if ( previousFrequencyCount == currentFrequencyCount )
			    	{
			    		SortOutputFileWriter.write(minElement+","+currentFrequencyCount+"\n") ;
			    		minElement = secondBestMinElement ;
			    		previousFrequencyCount = 0 ;
			    		currentFrequencyCount =0  ;
			    		 i=i-1 ;
			    		totalSortedElements++ ;
			    	}
			    	
			    }  // end of outer for loop.
			 
			 SortOutputFileWriter.close();
			 
			 for (int i=0; i<this.totalFileCount ; i++)
			    {
			    	mReaders[i].close();
			    	File delfile = new File (fileList[i]);
			    	 if ( !delfile.delete() ) 
			    	 { System.out.println("unable to delete  file sorted"+fileList[i]) ; }
			    	
			    	
			    }
		}
		
	}
	


public static void main(String[] args) throws IOException
{
	
	
	if(args.length!=1)
	{
		System.out.println("please input a file with integers to sort") ;
		System.exit(0);
	}
	int[] Integerarray = new int[2500] ;
	FileReader  inputfile = new FileReader(args[0]);
	BufferedReader  Inputfilereader = new BufferedReader (inputfile) ;
	int Totalelements = 1000000;
	int Blocksize = 2500 ;
    int TotalBlockCount =  (int) Math.ceil(Totalelements/Blocksize) ; 
 
	
    //Linearly read the inputfile  and sort and store in fileblocks. 
    
    for (int i=0 ; i< TotalBlockCount ;i++)
    {
    	String filenameindex =  new String ("SortedBlockFile"+i) ;
    	BufferedWriter	BFileWriter = new BufferedWriter ( new FileWriter(filenameindex)) ;
    	
    	for (int j=0 ; j< Blocksize ; j++)
    	{
    		Integerarray[j] = Integer.parseInt(Inputfilereader.readLine()) ;
    	}
    	
    	for(int k=0 ; k< Blocksize ;k++)
    	{	
    		Arrays.sort(Integerarray) ; // this function presumably does inarray sorting 
    		BFileWriter.write(Integer.toString(Integerarray[k])+"\n");
    	}
    	BFileWriter.close();
    }
    Inputfilereader.close();
    
    
    // This is Merge Phase.
    
    Integerarray = new int[TotalBlockCount] ;  // resize the Integerarray from 2500 to 400
   
    BufferedReader[]  MReaders = new BufferedReader[TotalBlockCount] ;  //  400 file readers are initialized.
    BufferedWriter    SortfileWriter = new BufferedWriter(new FileWriter("Sortedfile.txt")) ;  // open a filewriter to store sorted information
    
    int minelement=Integer.MAX_VALUE ;   //  a int variable to track the minimum most element
    int secondbestminelement =Integer.MAX_VALUE ;  // a int variable to track second most minimum.
    int currentcount=0 ; // counter to count the repeat of integer while merging
    int previouscount = 0;  // counter to store the count and check the difference with next iteration
    String tempstr ;
    int totalsortedelements=0 ;
    int totallinereads =0 ;
    int prevtotallinereads=0;
    
    
    // initialize all the FileReaders and read the first element in them 
    for (int i=0; i<TotalBlockCount ; i++)
    {
    	MReaders[i] =  new BufferedReader ( new FileReader ("SortedBlockFile"+i)) ;
    	Integerarray[i] =  Integer.parseInt(MReaders[i].readLine()) ;
    	if(minelement > Integerarray[i] )
    		{ minelement = Integerarray[i] ;  }
    	
    }
    
    	totallinereads = TotalBlockCount ;
    	secondbestminelement= minelement ;
    	prevtotallinereads=totallinereads;
     
    // Iterate the process of linearly scanning until all the 1 million elements are retrieved.
    for(int i=0; i<=Totalelements ;i++ )
    {
        	
    	//Linearly scan the Array for  (minelement,count)  and secondbestminelement .
    	    	
    	for (int j=0;j<TotalBlockCount ; j++)
    	{
    		
    		// compare minimum element with elements in the array,
    		//  a) if the minimum repeats increment its count and read the nextline from the corresponding file
    		//  b) if the minimum > and an element in array, throw error
    		//  c) if the minimum is less the element in the array , check for the second most minimum element.
    		if (minelement < Integerarray[j])
    		{
    			 if (  secondbestminelement >  Integerarray[j] && minelement < secondbestminelement)
    			 {
    				 secondbestminelement = Integerarray[j] ;
    			 }
    			 else if( minelement== secondbestminelement)
    			 {
    				 secondbestminelement = Integerarray[j] ; ;
    			 }
    			
    			continue ;
    		}
    		else if (minelement == Integerarray[j])
    		{
    			currentcount++ ; 
    			i++ ;
    			
    			if ( (tempstr = MReaders[j].readLine())!= null )
    			{		Integerarray[j] = Integer.parseInt(tempstr) ;
    				totallinereads++ ;
    				    			
    			}
    			else 
    			{
    				Integerarray[j] = Integer.MAX_VALUE ;
    			}
    		    
    			
    		}
    		else if(minelement > Integerarray[j])
    		{
    			System.out.println("Some error in sorting") ;
    			System.exit(0);
    			
    		}
    	   		
    	}  // end for inner for loop

    	// if there is a count difference of minimum value in previous and current iteration, then store it.
    	// else  write the minimum element to the sorted file.
    	if (previouscount < currentcount )
    	 {  previouscount = currentcount ;
    	   	 i=i-1 ;		
    	   	 
    	   	if (totallinereads - prevtotallinereads != 1) {
				System.out
						.println(" there was no read from memory mapped file : current counter "
								+ i);
			}
			prevtotallinereads = totallinereads;
    	 }
    	else if ( previouscount == currentcount )
    	{
    		SortfileWriter.write(minelement+","+currentcount+"\n") ;
    		minelement = secondbestminelement ;
    		previouscount = 0 ;
    		currentcount =0  ;
    		 i=i-1 ;
    		totalsortedelements++ ;
    	}
    	
    }  // end of outer for loop.
    
    
    //Close all the files and delete the blockfiles
    SortfileWriter.close();
    for (int i=0; i<TotalBlockCount ; i++)
    {
    	MReaders[i].close();
    	File delfile = new File ("SortedBlockFile"+i);
    	 if ( !delfile.delete() ) 
    	 { System.out.println("unable to delete  file sorted"+i) ; }
     
    }
    
   
   
}


};