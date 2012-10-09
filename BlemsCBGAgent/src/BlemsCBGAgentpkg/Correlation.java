package edu.isi.blems.BlemsCBGAgent;




public class Correlation {
	
	Correlation() {}
    public  double getPearsonCorrelation(double[] scores1,double[] scores2){
        double result = 0;
        double sum_sq_x = 0;
        double sum_sq_y = 0;
        double sum_coproduct = 0;
        double mean_x = scores1[0];
        double mean_y = scores2[0];
        for(int i=2;i<scores1.length+1;i+=1){
            double sweep =Double.valueOf(i-1)/i;
            double delta_x = scores1[i-1]-mean_x;
            double delta_y = scores2[i-1]-mean_y;
            sum_sq_x += delta_x * delta_x * sweep;
            sum_sq_y += delta_y * delta_y * sweep;
            sum_coproduct += delta_x * delta_y * sweep;
            mean_x += delta_x / i;
            mean_y += delta_y / i;
        }
        double pop_sd_x = (double) Math.sqrt(sum_sq_x/scores1.length);
        double pop_sd_y = (double) Math.sqrt(sum_sq_y/scores1.length);
        double cov_x_y = sum_coproduct / scores1.length;
                
        result = cov_x_y / (pop_sd_x*pop_sd_y);
        System.out.println("result " + result +" pop_sdx " + pop_sd_x+" pop_sd_y "+ pop_sd_y+" cov_x_y" + cov_x_y ) ;
        return result;
    }
    public  double getPearsonCorrelation(double[] scores1,double[] scores2, int serlen){
        double result = 0;
        double sum_sq_x = 0;
        double sum_sq_y = 0;
        double sum_coproduct = 0;
        double mean_x = scores1[0];
        double mean_y = scores2[0];
        for(int i=2;i<serlen+1;i+=1){
            double sweep =Double.valueOf(i-1)/i;
            double delta_x = scores1[i-1]-mean_x;
            double delta_y = scores2[i-1]-mean_y;
            sum_sq_x += delta_x * delta_x * sweep;
            sum_sq_y += delta_y * delta_y * sweep;
            sum_coproduct += delta_x * delta_y * sweep;
            mean_x += delta_x / i;
            mean_y += delta_y / i;
        }
        double pop_sd_x = (double) Math.sqrt(sum_sq_x/serlen);
        double pop_sd_y = (double) Math.sqrt(sum_sq_y/serlen);
        double cov_x_y = sum_coproduct / serlen;
                
        result = cov_x_y / (pop_sd_x*pop_sd_y);
        System.out.println("result " + result +" pop_sdx " + pop_sd_x+" pop_sd_y "+ pop_sd_y+" cov_x_y" + cov_x_y ) ;
        return result;
    }
    
    
    public static void main(String args[])
    {
     double[] s1 = {3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
     double[] s2 = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
     
     Correlation c1 = new Correlation() ;
     System.out.println( c1.getPearsonCorrelation(s1,s2)) ;
    }
    
}