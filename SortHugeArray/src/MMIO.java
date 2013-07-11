import java.io.BufferedReader;
import java.io.FileReader;
import java.io.RandomAccessFile;
import java.nio.IntBuffer;
	import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.util.Date;

	
public class MMIO {

	    private static int writebuffer = 10000000; //10 MB
	    private static int inputbuffer = 10000000;
	    private static int totalInts=102000000;
	    private static String inputfile = "/tmp/largefile";

	    public static void main(String[] args) throws Exception {
	    	
	    	System.out.println(" start of main function  "
					+ (new Date(System.currentTimeMillis())));
	        FileChannel outputFC = new  RandomAccessFile("largeFilewrite.txt", "rw").getChannel();
	       
	        //Mapping a file into memory
	        IntBuffer out =null ;// = outputFC.map(FileChannel.MapMode.READ_WRITE, 0, writebuffer).asIntBuffer();
	        //out.asIntBuffer();
	        FileChannel inputFC =  new RandomAccessFile(inputfile, "r").getChannel();
	        IntBuffer infile = null;
	     //   int[]  intarray = { 500,2,3};
	     //   BufferedReader br = new BufferedReader(new FileReader(inputfile));
	        
	        //Writing into Memory Mapped File
	        int bufferno=0;
	        int size=0;
	        long writetime=0;
	        int tempInteger=0;
	        int inputBufferIndex=0;
	        int totalwrites=0;
	        for (int i = 0; i < totalInts; i++) {
	        		//System.out.println(" this is current positing and inserting at this position "+out.position()) ;
	        	//tempInteger=Integer.parseInt(br.readLine());
	        	if((4*i)%inputbuffer==0){
	        		infile=inputFC.map(FileChannel.MapMode.READ_ONLY, 4*i, 4*i+inputbuffer).asIntBuffer();
	        	}
	           // out.put((int)intarray[i]);
	        	writetime=writetime-System.currentTimeMillis();
	        	if((4*i)%writebuffer==0) {
	        		out = outputFC.map(FileChannel.MapMode.READ_WRITE, 4*i, 4*i+writebuffer).asIntBuffer();
	        		inputBufferIndex=0;
	        	}
	      //  	out.put(tempInteger);
	        	out.put((int)infile.get(inputBufferIndex));
	        	inputBufferIndex++;
	        	totalwrites++;
	        	writetime=writetime+System.currentTimeMillis();
	        }
	        System.out.println("Writing to Memory Mapped File is completed  time="+  writetime/1000+ " total writes "+ totalwrites);
	      
	      //  br.close();
	    //  out.position(0);
	        
	        inputFC.close();
	        outputFC.close();
	        
	        /*
	        System.out.println(" reading from memory file start time "
					+ (new Date(System.currentTimeMillis())));
	        //reading from memory file in Java
	        int cnt=0;
	        tempInteger=0;
	        while(cnt<totalInts) {
	        for (int i = 0; i < writebuffer/4 ; i++) {
	        	
	   
	        	if((4*cnt)%writebuffer==0) {
	        		out = memoryMappedFile.getChannel().map(FileChannel.MapMode.READ_WRITE, 4*cnt, 4*cnt+writebuffer).asIntBuffer();
	        	}
	        
	        	out.get(i);
	        	
	            cnt++;
	            if(cnt >= totalInts) break;
	           
	        }
	        }
	        
	        System.out.println(" the total rewritebuffer "+ cnt);
	        System.out.println("reading from memory file end time: "
					+ (new Date(System.currentTimeMillis())));
	        memoryMappedFile.close();
	       
	        
	       
	        
	        BufferedReader br1 = new BufferedReader(new FileReader(inputfile));
	        
	        System.out.println("buffered reading : start time "
					+ (new Date(System.currentTimeMillis())));
	      cnt=0;
	        while(br1.readLine()!=null ){
	        	cnt++;
	        	 if(cnt >= totalInts) break;
	        }
	        
	        System.out.println(" total writebuffer using buffered read line "+cnt);
	        System.out.println("buffered reading stop time "
					+ (new Date(System.currentTimeMillis())));
	        
	        //
	        br1.close();
	        //testing using 
	         * 
	         */
	    }
	


	
}
