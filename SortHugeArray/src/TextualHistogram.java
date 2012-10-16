
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

public class TextualHistogram {
	
	
	public int[] Integerarray  ; 
	int Totalelements ;
	int Blocksize; 
    int TotalBlockCount ; 
    String InputFileName ;
	
    public TextualHistogram(String InputFile)
    {
    	 
    	
    	 Blocksize = 2500 ;
    	 Integerarray   = new int[Blocksize] ;
    	 InputFileName =  new String (InputFile) ;
    	 Totalelements  = countFileLength() ;
    	 TotalBlockCount =  (int) Math.ceil(Totalelements/Blocksize) ;
    	  
    }
    
    public  TextualHistogram(String InputFile, int BlockSize)
    {
    	 
    	
    	 Blocksize = BlockSize ;
    	 Integerarray   = new int[Blocksize] ;
    	 InputFileName =  new String (InputFile) ;
    	 Totalelements  = countFileLength() ;
    	 TotalBlockCount =  (int) Math.ceil(Totalelements/Blocksize) ;
    	  
    }
    
           
    public int countFileLength()
    {
    	int LineCounter=0 ;
    	try{
    	BufferedReader  InputFileReader  = new BufferedReader (new FileReader(InputFileName)) ;
		String TempStringStorage = new String();
		while( (TempStringStorage = InputFileReader.readLine()) != null )
		{
			LineCounter++ ;
		}
		
    	}
    	catch(IOException E)
    	{
    		E.printStackTrace() ;
    	}
    	
    	return LineCounter ;
    }
    
    public int getBlockSize()
    {
    	return this.Blocksize  ;
    }
    
    public int getTotalBlockCount()
    {
    	return this.TotalBlockCount ;
    }
    
    public int getTotalElements()
    {
    	return this.Totalelements ;
    }

    public void partitionAndSort()  throws Exception
    {
    	
    	BufferedReader Inputfilereader = new BufferedReader(new FileReader (this.InputFileName)) ;

        for (int i=0 ; i< this.getTotalBlockCount() ;i++)
        {
        	String filenameindex =  new String ("SortedBlockFile"+i) ;
        	BufferedWriter	BFileWriter = new BufferedWriter ( new FileWriter(filenameindex)) ;
        	
        	for (int j=0 ; j< this.getBlockSize() ; j++)
        	{
        		this.Integerarray[j] = Integer.parseInt(Inputfilereader.readLine()) ;
        	}
        	
        	for(int k=0 ; k< Blocksize ;k++)
        	{	
        		Arrays.sort(Integerarray) ; // this function presumably does inarray sorting 
        		BFileWriter.write(Integer.toString(Integerarray[k])+"\n");
        	}
        	BFileWriter.close();
        }
        Inputfilereader.close();
        
    }
    
    public void allocateArrayMemory(int memsize)
    {
      this.Integerarray  = new int[memsize] ;
          	
    }
    
    public void MergeSortedBlockFiles() throws Exception
    {
    	
    		
    	int minelement=Integer.MAX_VALUE ;   //  a int variable to track the minimum most element
	    int secondbestminelement =Integer.MAX_VALUE ;  // a int variable to track second most minimum.
	    int currentcount=0 ; // counter to count the repeat of integer while merging
	    int previouscount = 0;  // counter to store the count and check the difference with next iteration
	    String tempstr ;
	    int totalsortedelements=0 ;
	    int totallinereads =0 ;
	    
    	
    	   
	    BufferedReader[]  MReaders = new BufferedReader[this.TotalBlockCount] ;  //  400 file readers are initialized.
    	BufferedWriter    SortfileWriter = new BufferedWriter(new FileWriter("Sortedfile.txt")) ;  // open a filewriter to store sorted information
    	    
    	    
    	    
    	    // initialize all the FileReaders and read the first element in them 
    	for (int i=0; i<this.TotalBlockCount ; i++)
    	 {
    	  	MReaders[i] =  new BufferedReader ( new FileReader ("SortedBlockFile"+i)) ;
    	   	Integerarray[i] =  Integer.parseInt(MReaders[i].readLine()) ;
    	   	if(minelement > this.Integerarray[i] )
    			{ minelement = this.Integerarray[i] ;  }
    	    	
    	 }
    	    
    	totallinereads = this.TotalBlockCount ;
    	secondbestminelement= minelement ;
    	     
    	    // Iterate the process of linearly scanning until all the 1 million elements are retrieved.
    	for(int i=0; i<=this.Totalelements ;i++ )
    	{
    	        	
    	    	//Linearly scan the Array for  (minelement,count)  and secondbestminelement .
    	    	    	
    	   	for (int j=0;j<this.TotalBlockCount ; j++)
    	   	{
    	    		
    	   		// compare minimum element with elements in the array,
    	   		//  a) if the minimum repeats increment its count and read the nextline from the corresponding file
    	   		//  b) if the minimum > and an element in array, throw error
    	   		//  c) if the minimum is less the element in the array , check for the second most minimum element.
    	   		if (minelement < this.Integerarray[j])
    	   		{
    	   			 if (  secondbestminelement >  this.Integerarray[j] && minelement < secondbestminelement)
    	    			 {
    	    				 secondbestminelement = this.Integerarray[j] ;
    	    			 }
    	   			 else if( minelement== secondbestminelement)
    	    			 {
    	    				 secondbestminelement = this.Integerarray[j] ; ;
    	    			 }
    	    			
   	    			continue ;
   	    		}
  	    		else if (minelement == this.Integerarray[j])
   	    		{
    	    			currentcount++ ; 
    	    			i++ ;
    	    			
    	    			if ( (tempstr = MReaders[j].readLine())!= null )
    	    			{		this.Integerarray[j] = Integer.parseInt(tempstr) ;
    	    				totallinereads++ ;
    	    				    			
    	    			}
    	    			else 
    	    			{
    	    				this.Integerarray[j] = Integer.MAX_VALUE ;
    	    			}
    	    		    
    	    			
   	    		}
   	    		else if(minelement > this.Integerarray[j])
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
    	    for (int i=0; i<this.TotalBlockCount ; i++)
    	    {
    	    	MReaders[i].close();
    	    	File delfile = new File ("SortedBlockFile"+i);
    	    	if( !delfile.delete()) 
    	    	{
    	    		System.out.println("unable to delete  file sorted"+i) ; 
    	    	}
    	     
    	    }  // file close for loop
    	
    }
    
    
    
public static void main(String[] args) throws IOException, Exception
{
	
		
	if(args.length !=1  || args.length !=2)
	{
		System.out.println("\n TextualHistogram: \n Description: This program sorts the Inputfile with integers with limited memory " +
							"\n Usage "+
							"\n Linux: java -classpath $CLASSPATH:$PWD TextualHistogram InputFileName " +
							"\n        java -classpath $CLASSPATH:$PWD TextualHistogram InputFileName  MemoryBlockSize" +
							"\n Windows: \n java -classpath %CLASSPATH%;%PWD% TextualHistogram InputFileName" +
							"\n Note: The system will process the InputFile even if the total Integers are less than 1 million ") ;
		
		System.out.println("\n Please enter a input file with integers or type 'q' for quit \n\n") ; ;
		InputStreamReader converter = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(converter);
		if(in.readLine() == "q")
		{	
			System.exit(0);
		}
		else if (!( new File(args[0]).exists()))
		{
			System.out.println("\n Sorry File does not exists. Please run the program again") ;
		}
			
	}
	
	
	
	TextualHistogram   TextualHistogram_object  = new TextualHistogram(args[0])  ;
	if(args.length == 1)
	{
		TextualHistogram_object = new TextualHistogram(args[0]) ;
	}
	else if (args.length == 2)
	{
		TextualHistogram_object = new TextualHistogram(args[0], Integer.parseInt(args[1])) ;
	}
	
    //Linearly read the inputfile  and sort and store in fileblocks. 

	try{
    
    TextualHistogram_object.partitionAndSort() ;
    
    TextualHistogram_object.allocateArrayMemory(TextualHistogram_object.getTotalBlockCount()) ;
    // This is Merge Phase.
    
    TextualHistogram_object.MergeSortedBlockFiles() ;
	
    
  }
    catch(Exception E)
    {
    	E.printStackTrace() ;
    }
    
   
   
}


};