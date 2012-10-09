#!/usr/bin/perl

#print "\n helloworld" ;

$t1=shift  ;
$t2=shift ;
$t3=shift;
$t4=shift ;
$t5=shift ;

open(file1, $t1) ;
open(file2, $t2);
open(file3, $t3) ;
open(file4, $t4) ;
open (file5, $t5) ;
	open(sum, ">sum.txt") ; 
my $a1,$a2,$a3,$a4,$a5 ;
my $s1=0, $s2=0, $s3=0, $s4=0, $s5=0 ;
my $c1=0,$c2=0;$c3=0;$c4=0;$c5=0 ;
for ($i=1;$i<=1600;$i++)
{

$a = <file1> ;
($a1,$a2,$a3,$a4,$a5) = split( /\s/,$a) ;
$s1=$s1+$a1 ;
$s2=$s2+$a2 ;
$s3=$s3+$a3 ;
$s4=$s4+$a4 ;
$s5=$s5+$a5 ;
if($a3==0){ $c3++ ; }
if($a4==0){ $c4++ ; }
if($a5==0) {$c5++ ; }
if ($a1==0) { $c1++ ;}
if($a2==0) { $c2++;}
$a =<file2> ;
($a1,$a2,$a3,$a4,$a5) = split( /\s/,$a) ;
$s1=$s1+$a1 ;
$s2=$s2+$a2 ;
$s3=$s3+$a3 ;
$s4=$s4+$a4 ;
$s5=$s5+$a5 ;
if($a3==0){ $c3++ ; }
if($a4==0){ $c4++ ; }
if($a5==0) {$c5++ ; }
if ($a1==0) { $c1++ ;}
if($a2==0) { $c2++;}
$a =<file3> ;
($a1,$a2,$a3,$a4,$a5) = split( /\s/,$a) ;
$s1=$s1+$a1 ;
$s2=$s2+$a2 ;
$s3=$s3+$a3 ;
$s4=$s4+$a4 ;
$s5=$s5+$a5 ;
if($a3==0){ $c3++ ; }
if($a4==0){ $c4++ ; }
if($a5==0) {$c5++ ; }
if ($a1==0) { $c1++ ;}
if($a2==0) { $c2++;}
$a =<file4> ;
($a1,$a2,$a3,$a4,$a5) = split( /\s/,$a) ;
$s1=$s1+$a1 ;
$s2=$s2+$a2 ;
$s3=$s3+$a3 ;
$s4=$s4+$a4 ;
$s5=$s5+$a5 ;
if($a3==0){ $c3++ ; }
if($a4==0){ $c4++ ; }
if($a5==0) {$c5++ ; }
if ($a1==0) { $c1++ ;}
if($a2==0) { $c2++;}
$a =<file5> ;
($a1,$a2,$a3,$a4,$a5) = split( /\s/,$a) ;
$s1=$s1+$a1 ;
$s2=$s2+$a2 ;
$s3=$s3+$a3 ;
$s4=$s4+$a4 ;
$s5=$s5+$a5 ;
if($a3==0){ $c3++ ; }
if($a4==0){ $c4++ ; }
if($a5==0) {$c5++ ; }
if ($a1==0) { $c1++ ;}
if($a2==0) { $c2++;}
$s1=$s1/(5-$c1) if($c1 != 5) ;
$s2=$s2/(5-$c2) if($c2 != 5) ;
$s3=$s3/(5-$c3) if($c3 != 5) ;
$s4=$s4/(5-$c4) if($c4 != 5) ;
$s5=$s5/(5-$c5) if($c5 != 5) ;
print sum "$s1 $s2 $s3 $s4 $s5\n" ;
$s1=0;$s2=0;$s3=0;$s4=0;$s5=0 ;
$c1=0;$c2=0;$c3=0;$c4=0;$c5=0;
}

close(file1) ;close(file2) ;close(file3) ;close(file4) ;close(file5) ;
close(sum) ;
#print "${s1}, ${s2}, ${s3}, ${s4},${s5}" ;
