
/**
 *   textualHistogram.java
 *   Author: Sunil Mamidi
 *   Description:  Sorts a File with 1 million integers with atmost 2500 integers in memory in ascending order
 *   Logic : Linearly read the file into  block chunks of 2500 integers, and do in place sorting using java functions
 *   and store the stored blocks into different files. Merge the sorted files . Store the minimum most element
 *   from each file into the Array  (the size of this Array is 400 which is less than 2500 ). 
 *   Scan the above Array for minimum and it's count and repeat the scanning process until a there is no different in countvalue.
 *   The above scanning process repeats on maximum to 100000.
 *   time with out memory managed files 1:30 min
 * 
 */
import java.io.* ;
import java.math.*; 
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;




public class Tex1Histogram {



	public int[] Integerarray  ; 
	public int[] mergeWindow;  //mergeWindow fileBlockSortBuffer
	public int[] fileBlockSortBuffer;
	int Totalelements ;
	int Blocksize; 
    int TotalBlockCount ; 
    String InputFileName ;
    int NUM_THREADS=8;
    String[] fileList;
    int[]  fileSize;
    
    Map<String,FileInfo>  fileInfoMap = new HashMap<String,FileInfo>();
    

	public void mergeThreadController() throws InterruptedException, NumberFormatException, ExecutionException {
		
		ExecutorService executorService = Executors.newFixedThreadPool(this.NUM_THREADS);
		
		int filePerThread =  this.TotalBlockCount/this.NUM_THREADS ;
		
		List<MergeThread>  tasks = new ArrayList<MergeThread>();
		
			
		int totalFileProcessed=0;
		int totalOutputFiles=0;
		MergeThread mt =null;
		
		ArrayList<FileInfo> currIterFiles = new ArrayList<FileInfo>();		
		
		
		while(fileInfoMap.size()!=0) {
		
			Set<Entry<String,FileInfo>> currIterSet = fileInfoMap.entrySet();
			// List<Entry<String,FileInfo>> currIterList = new ArrayList<Entry<String,FileInfo>>(currIterSet); 
			
			@SuppressWarnings("unchecked")
			List<Entry<String,FileInfo>> currIterList = (List<Entry<String, FileInfo>>) fileInfoMap.entrySet();
			
			for (int i=0 ; i <=this.NUM_THREADS ; i++) {
			
			
				List<Entry<String,FileInfo>> subCurrIterList = currIterList.subList(totalFileProcessed,totalFileProcessed +filePerThread );
				String outputfile = "outputfile"+totalOutputFiles;
				totalOutputFiles++;
				int outputFileSize =0;
				Entry<String,FileInfo> currEntry=null;
				
				for(int j=0; j<subCurrIterList.size(); j++) {
					currEntry = subCurrIterList.get(j);
					// not a valid output
					outputFileSize=outputFileSize+ currEntry.getValue().fileSize;
					fileInfoMap.put(currEntry.getKey(), new FileInfo(currEntry.getKey(),currEntry.getValue().fileSize, true));
					}
				
				mt = new MergeThread(subCurrIterList, outputfile);
				tasks.add(mt);
				
				
				fileInfoMap.put(outputfile, new FileInfo(outputfile, outputFileSize,false));
					
			}
				List<Future<String>> ft = executorService.invokeAll(tasks);
							
				for(Future<String> futureObject : ft) {					
					if(futureObject.isDone()!=true||futureObject.isCancelled()) {
						System.exit(0);
					}
			
					fileInfoMap.put(futureObject.get().split(",")[0], new FileInfo(futureObject.get().split(",")[0], Integer.parseInt(futureObject.get().split(",")[1]),false));
				}
				
							
				for(Entry<String,FileInfo> eset : fileInfoMap.entrySet()) {
					if(eset.getValue().status==true) {
						fileInfoMap.remove(eset.getKey());
					}
				}
				
				
				
			
		}
				
	}

    public Tex1Histogram(String InputFile) {
    	 
    	
    	 Blocksize = 2500 ;
    	 Integerarray   = new int[Blocksize] ;
    	 InputFileName =  new String (InputFile) ;
    	 Totalelements  = countFileLength() ;
    	 TotalBlockCount =  (int) Math.ceil(Totalelements/Blocksize) ;
    	  
    }
    
    public  Tex1Histogram(String InputFile, int BlockSize)
    {
    	 
    	
    	 Blocksize = BlockSize ;
    	// Integerarray   = new int[Blocksize] ;
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
    	
    	int[] fileBlockSortBuffer = new int[this.Blocksize];
    	BufferedReader Inputfilereader = new BufferedReader(new FileReader (this.InputFileName)) ;

        for (int i=0 ; i< this.getTotalBlockCount() ;i++)
        {
        	String filenameindex =  new String ("SortedBlockFile"+i) ;
        	BufferedWriter	BFileWriter = new BufferedWriter ( new FileWriter(filenameindex)) ;
        	
        	for (int j=0 ; j< this.getBlockSize() ; j++)
        	{
        		this.fileBlockSortBuffer[j] = Integer.parseInt(Inputfilereader.readLine()) ;
        	}
        	
        	for(int k=0 ; k< Blocksize ;k++)
        	{	
        		Arrays.sort(fileBlockSortBuffer) ; // this function presumably does inarray sorting 
        		BFileWriter.write(Integer.toString(fileBlockSortBuffer[k])+"\n");
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
    
    
    
    public static void main(String[] args) 
    {

    	System.out.println("start time "+  (new Date(System.currentTimeMillis()))) ;
    	
    	String InputFileName = new String() ;
    	
    	//Usage
    	try
    	{
    	if(args.length !=1 && args.length !=2)
    	{
    		System.out.println("\n TextualHistogram: \n Description: This program sorts the Inputfile with integers with limited memory " +
							"\n Usage "+
							"\n		Linux:		java -classpath $CLASSPATH:$PWD TextualHistogram InputFileName " +
							"\n				java -classpath $CLASSPATH:$PWD TextualHistogram InputFileName  MemoryBlockSize" +
							"\n		Windows:	java -classpath %CLASSPATH%;%PWD% TextualHistogram InputFileName" +
							"\n Note: The system will process the InputFile even if the total Integers are less than 1 million ") ;

    		System.out.println("\n Please enter a input file with integers or type 'quit' for quit \n\n") ; ;
    		InputStreamReader converter = new InputStreamReader(System.in);
    		BufferedReader in = new BufferedReader(converter);
    		InputFileName = in.readLine().trim();
    		if(InputFileName.equals("quit"))
    		{	
    			System.runFinalization() ;
    			System.exit(0);
    		}
    		/*
    		else if (!( new File(InputFileName).exists()) )
    		{
    			System.out.println("\n Sorry File does not exists. Please run the program again") ;
    			System.exit(0) ;
    		}
			*/
    	}
    	else
    	{
    		InputFileName = args[0] ;
    		System.out.println(" given input file "+ InputFileName);
    		
    		if (!( new File(InputFileName).exists())) {
    			System.out.println("input file doesn't exists");
    		}
    		
    	
    	}

    	}
    	catch(Exception E)
    	{
    		E.printStackTrace() ;
    	}
    	
    	/*
    	finally
    	{
    		System.out.println("some error reading file");
    		System.exit(0);
    		
    	}
    	*/
    	
    	Tex1Histogram   TextualHistogram_object  = new Tex1Histogram(InputFileName)  ;
    	if(args.length == 1)
    	{
    		TextualHistogram_object = new Tex1Histogram(args[0]) ;
    	}
    	else if (args.length == 2)
    	{
    		TextualHistogram_object = new Tex1Histogram(args[0], Integer.parseInt(args[1])) ;
    	}

    

    	try{
    		
    		
    		
    		 //Sort Block Wise
    			TextualHistogram_object.partitionAndSort() ;
    
    		// Resize the Array 
    			TextualHistogram_object.allocateArrayMemory(TextualHistogram_object.getTotalBlockCount()) ;

    		// Merge the Sorted Block Files
    			TextualHistogram_object.MergeSortedBlockFiles() ;
    			
    		    System.out.println("start time "+  (new Date(System.currentTimeMillis()))) ;

    
    		}
    	catch(Exception E)
    		{
    			E.printStackTrace() ;
    		}
    	/*	
    	finally 
    	{
    		System.out.println("\n there was some exception") ;
    	}
    	*/
   
   
    }



};
