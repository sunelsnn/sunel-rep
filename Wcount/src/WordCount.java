

	import java.io.IOException;
import java.sql.Timestamp;
	import java.util.*;
	
	import org.apache.hadoop.fs.Path;
	import org.apache.hadoop.conf.*;
	import org.apache.hadoop.io.*;
//	import org.apache.hadoop.mapred.OutputCollector;
// import org.apache.hadoop.mapred.JobConf;
//import org.apache.hadoop.mapred.lib.ChainMapper;
 import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.MultipleOutputs;
import org.apache.hadoop.mapreduce.lib.output.SequenceFileOutputFormat;
import org.apache.hadoop.mapreduce.lib.chain.* ;
import org.apache.hadoop.util.*;
	
	public class WordCount {
		private static String file1 ;
		private static String file2 ;
		private static MultipleOutputs mos = null ;
		private  static boolean startMAP2 = false ;
		
	
	    public static class WCMap extends Mapper<Object, Text, Text, IntArrayWritable> {
	      private final static IntWritable one = new IntWritable(1);
	      private Text word = new Text();
	      private static int maptaskcount=0 ;
	  //  private LongWritable word = new LongWritable() ;
	      
	      protected void setup (Context context) throws IOException, InterruptedException
	      {
	    	  
	    	  super.setup(context) ;
	    	  System.out.println("In MAP setup  WCMAP and sleeping for 10 seconds " + new Timestamp(System.currentTimeMillis())) ;
	    //	  Thread.sleep(10000) ;
	    	//  System.out.println("After sleep " + new Timestamp(System.currentTimeMillis())) ;
	    	//  mos = new MultipleOutputs(context) ;
	    //	  Runtime rt = Runtime.getRuntime();
	    //	  String tempfilename =  "touch " + new  String ("~/file") + new  String (  Long.toString(new Date().getTime())) ;
	    //	  Process proc = rt.exec( "touch file1");
	    	  Configuration conf = context.getConfiguration();
	    //	  System.out.println( conf.get("map.input.file")) ;
	    //	  System.out.println( conf.toString()) ;
	    	 // System.out.println( conf.) ;
	      }
	      public void map(Object key, Text value, Context context ) throws IOException , InterruptedException {
	    	  
	    	  maptaskcount++ ;
	    	  System.out.println(" WCMAP :the map count index " + maptaskcount  ) ;
	    	  Configuration conf = context.getConfiguration();
	    	//  String param = conf.get("PARM1");
	    	 // System.out.println("pringint PARM" + param) ;
	    	  
	        String line = value.toString();
	        StringTokenizer tokenizer = new StringTokenizer(line);
	        while (tokenizer.hasMoreTokens()) {
	          word.set(tokenizer.nextToken());
	          int[] val= new int[1] ;
	          val[0] = one.get();
	          IntArrayWritable IAW = new IntArrayWritable(val) ;
	          context.write(word, IAW);
	        }
	      }
	      
	      public void cleanup(Context context)
	      {
	    	  System.out.println("finishing up WCMAP . in the cleanup function") ;
	    	//   startMAP2 = true ;
	    	  
	      }
	    }
	
	    
 // public static class WCMap2 extends  Mapper<Text, IntArrayWritable, WritableComparable, Writable> {
	    public static class WCMap2 extends  Mapper<Text, IntArrayWritable, Text, IntArrayWritable> {
	    	
	    	private static int maptaskcount=0 ;
	    	public void setup(Context context)
			{
				System.out.println("in WCMAP2 setup function \n context to string"+ context.toString()) ;
				 mos = new MultipleOutputs(context) ;
				 System.out.println (" mos to string "+ mos.toString() );
				
			/*	  
		    	  try {
		    	  while(startMAP2 != true)
					 {
						 Thread.sleep(10000) ;
					 }
		    	  }
		    	  catch(InterruptedException ie)
		    	  {
		    		  ie.printStackTrace() ;
		    	  }
		    	  
		    	  System.out.println("map2 start status " + startMAP2) ;
			*/	 
			}
	    	
	    	
	    	 public void map(Text key, IntArrayWritable valuesobj, Context context) throws IOException , InterruptedException  {
	    		 
	    		 
	    		 int sum = 0;
	 	        
	    		 
	 	       int[] intarray = valuesobj.getInt() ;
	 	       for(int i=0; i <intarray.length ;i++)
	 	       {
	 	    	   sum= sum+intarray[i] ;
	 	       }
	 	       
	 	       System.out.println("MAP2: Key,value" + key +","+sum) ;
	 	       int[]  sumIAW = new int[1] ;
	 	       sumIAW[0] = sum ;
	 	       context.write(key, new IntArrayWritable(sumIAW)) ;
	    		 
	    		 
	    	 }
	    	
	    	
	    	
	    	/*
	      public void map(Text key, Iterable<IntArrayWritable> valuesobj, Context context) throws IOException , InterruptedException  {
	    	  
	    	
	    	  maptaskcount++ ;
	    	  System.out.println("WCMAP2 : map task count " + maptaskcount) ;
	    	  
	    	//  System.out.println(" startMAP2 turns true") ;
	    	  
	    	  Configuration conf = context.getConfiguration();
	    // 	  String param = conf.get("PARM1");
	    	  //System.out.println("pringint PARM in reducer" + param) ;
	  //  	  if(startMAP2 == true)
	  //  	  {
	        int sum = 0;
	        
	        Iterator<IntArrayWritable> values = valuesobj.iterator() ; 
	        while (values.hasNext()) {
	          int[] valints = values.next().getInt();
	          for(int i=0;i<valints.length ;i++)
	        	  sum+=valints[i] ;
	        }
	        
	        //
	       // for (IntWritable val: values)
	       // {
	       // 	sum += val.get() ;
	       // }
	        //
	         int[] valout = new int[1] ;
	         valout[0] = sum ;
	         context.write(key, new IntArrayWritable(valout));
	         mos.write("COUNT",key, new IntArrayWritable(valout),  "file1") ;
	         mos.write("REVERSECOUNT",key, new IntArrayWritable(valout),  "file2") ;
	        
	         //
	        // mos.write("COUNT",key, new IntArrayWritable(valout)) ;
	         //mos.write("REVERSECOUNT",key, new IntArrayWritable(valout)) ;
	        //
	         
	    	//  }
	      }
	      */
	   
	      public void cleanup(Context context)
	      {
	    	  System.out.println(" clean up in WCMAP2 .") ;
	      }
	    }
 
	//     public static class WCReduce extends  Reducer<Text, IntArrayWritable, WritableComparable, Writable> {
	    	
 public static class WCReduce extends  Reducer<Text, IntArrayWritable,Text, IntArrayWritable> {
	    	public void setup(Context context)
			{
				System.out.println("in WCReduce setup function \n context to string"+ context.toString()) ;
				 mos = new MultipleOutputs(context) ;
				 System.out.println (" mos to string "+ mos.toString() );
			}
	      public void reduce(Text key, Iterable<IntArrayWritable> valuesobj, Context context) throws IOException , InterruptedException  {
	    	  Configuration conf = context.getConfiguration();
	    	//   String param = conf.get("PARM1");
	    	  //System.out.println("pringint PARM in reducer" + param) ;
	        int sum = 0;
	        
	        Iterator<IntArrayWritable> values = valuesobj.iterator() ; 
	        while (values.hasNext()) {
	          int[] valints = values.next().getInt();
	          for(int i=0;i<valints.length ;i++)
	        	  sum+=valints[i] ;
	        }
	        
	        /*
	        for (IntWritable val: values)
	        {
	        	sum += val.get() ;
	        }
	        */
	         int[] valout = new int[1] ;
	         valout[0] = sum ;
	        //context.write(key, new IntArrayWritable(valout));
	         mos.write("COUNT",key, new IntArrayWritable(valout),  "file1") ;
	         mos.write("REVERSECOUNT",key, new IntArrayWritable(valout),  "file2") ;
	        /*
	         mos.write("COUNT",key, new IntArrayWritable(valout)) ;
	         mos.write("REVERSECOUNT",key, new IntArrayWritable(valout)) ;
	         */
	      }
	    }
	    /*

	    public void testfunction()
	    {}
	    */
	    public static void main(String[] args) throws Exception {
	    	System.out.println("Entering job config dsfds") ;
	    	// System.in.read() ;
	    	file1 = new String("file1") ;
	    	file2 = new String("file2") ;
	    	Configuration conf = new Configuration();
	    	 conf.set("PARM1", "PARM1value");
		      conf.set("PARM2", "PARM2value") ;
		      Job job = new Job (conf, "WordCount");
		      Configuration mapAConf = new Configuration(false);
		      Configuration mapBConf = new Configuration(false);
		      Configuration reduceConf = new Configuration(false);
		      Configuration reduceBConf = new Configuration(false);
		      ChainReducer<Text, IntArrayWritable, Text, IntArrayWritable> a = new ChainReducer<Text, IntArrayWritable, Text, IntArrayWritable>();
		      ChainReducer<Text, IntArrayWritable, Text, IntArrayWritable> b = new ChainReducer<Text, IntArrayWritable, Text, IntArrayWritable>();
		      
		      
		      ChainMapper.addMapper(job, WCMap.class, Object.class, Text.class, Text.class, IntArrayWritable.class, mapAConf) ;
		  //    ChainMapper.addMapper(job, WCMap2.class, Text.class, IntArrayWritable.class, WritableComparable.class, Writable.class, mapBConf) ;
		  //    ChainReducer.setReducer(job, WCReduce.class, Text.class, IntArrayWritable.class, WritableComparable.class, Writable.class, reduceConf) ;
		      
		   //   ChainMapper.addMapper(job, WCMap2.class, Text.class, IntArrayWritable.class, Text.class, IntArrayWritable.class, mapBConf) ;
		   //   ChainReducer.setReducer(job, WCReduce.class, Text.class, IntArrayWritable.class, Text.class, IntArrayWritable.class, reduceConf) ;
		      a.setReducer(job, WCReduce.class, Text.class, IntArrayWritable.class, Text.class, IntArrayWritable.class, reduceConf) ;
		      
		      ChainMapper.addMapper(job, WCMap2.class, Text.class, IntArrayWritable.class, Text.class, IntArrayWritable.class, mapBConf) ;
		      // ChainReducer.setReducer(job, WCReduce.class, Text.class, IntArrayWritable.class, Text.class, IntArrayWritable.class, reduceBConf) ;
		      b.setReducer(job, WCReduce.class, Text.class, IntArrayWritable.class, Text.class, IntArrayWritable.class, reduceBConf) ;
	   //    Job job = new Job (conf, "WordCount");
		      /*
	      job.setJarByClass(WordCount.class);
	      job.setMapperClass(WCMap.class);
	      job.setCombinerClass(WCReduce.class);
	      job.setReducerClass(WCReduce.class);
	      job.setMapOutputKeyClass (Text.class);
	      job.setMapOutputValueClass(IntArrayWritable.class) ;
	      */
	      //job.setOutputKeyClass(Text.class);
	      //job.setOutputValueClass(IntArrayWritable.class);
	      // job.setOutputFormatClass(SequenceFileOutputFormat.class) ;
	      
	      MultipleOutputs.addNamedOutput(job, "COUNT", SequenceFileOutputFormat.class,	 Text.class, IntArrayWritable.class);
			MultipleOutputs.addNamedOutput(job, "REVERSECOUNT", SequenceFileOutputFormat.class,
					 Text.class, IntArrayWritable.class);
			
	 // job.setLong("temparm","someval") ;
	   
	      /*
	      conf.setJar("Wcountjar.jar") ;
	      conf.setJobName("WordCount");
	      conf.setOutputKeyClass(Text.class);
	      conf.setOutputValueClass(IntWritable.class);
	
	      conf.setMapperClass(Map.class);
	      conf.setCombinerClass(Reduce.class);
	      conf.setReducerClass(Reduce.class);
	
	      conf.setInputFormat(TextInputFormat.class);
	      conf.setOutputFormat(TextOutputFormat.class);
	      */
	      /*
	       * Job job = new Job(conf, "word count");
    job.setJarByClass(WordCount.class);
    job.setMapperClass(TokenizerMapper.class);
    job.setCombinerClass(IntSumReducer.class);
    job.setReducerClass(IntSumReducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
	       */
	
	      FileInputFormat.addInputPath(job, new Path(args[0]));
	      FileOutputFormat.setOutputPath( job, new Path(args[1]));
	      FileOutputFormat.setOutputPath(job, new Path ("file1")) ;
	      FileOutputFormat.setOutputPath(job, new Path ("file2")) ;
	      
	      
	      System.exit(job.waitForCompletion(true) ? 0 : 1);
	
	     // JobClient.runJob(conf);
	    
	}
	    
	    }
	
/*
 * conf.setJobName("chain");
 conf.setInputFormat(TextInputFormat.class);
 conf.setOutputFormat(TextOutputFormat.class);
 

 JobConf mapAConf = new JobConf(false);
 ...
 ChainMapper.addMapper(conf, AMap.class, LongWritable.class, Text.class,
   Text.class, Text.class, true, mapAConf);
 


 JobConf mapBConf = new JobConf(false);
 ...
 ChainMapper.addMapper(conf, BMap.class, Text.class, Text.class,
   LongWritable.class, Text.class, false, mapBConf);
 


 JobConf reduceConf = new JobConf(false);
 ...
 ChainReducer.setReducer(conf, XReduce.class, LongWritable.class, Text.class,
   Text.class, Text.class, true, reduceConf);
 


 ChainReducer.addMapper(conf, CMap.class, Text.class, Text.class,
   LongWritable.class, Text.class, false, null);
 


 ChainReducer.addMapper(conf, DMap.class, LongWritable.class, Text.class,
   LongWritable.class, LongWritable.class, true, null);
 


 FileInputFormat.setInputPaths(conf, inDir);
 FileOutputFormat.setOutputPath(conf, outDir);
 ...
 


 JobClient jc = new JobClient(conf);
 RunningJob job = jc.submitJob(conf);
 ...*/
