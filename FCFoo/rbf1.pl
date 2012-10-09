#!/usr/bin/perl
use POSIX                                               ;
$SIG{PIPE} ='IGNORE'                                    ;
require "stat.pl"                                       ;
use Getopt::Std                                         ;
use FileHandle                                          ;
use File::Basename                                      ;
use Time::Local                                         ;
$qfile = "sum.txt"  ;

my $sigt1 = 3 ;
my $sigt2 = 3 ;
my $sigr1 = 3 ;
my $sigr2 = 3 ;
#my $qfile = shift ;
if( $qfile eq  "" ) { print "exiting because qfile is 0" ;  exit(0) ; }
@qf ;
@ker ;
@uqf ;
my $a ;
open(qf1, $qfile) ;
open ( uqf1, ">uqfile.txt") ;
for ( $i=0 ; $i<1600 ; $i++)
{
$a = <qf1> ;
if($a eq  "" ) { print "qfile line read is null ",$i ; exit(0) ; }
($a1,$a2,$a3,$a4,$a5) = split(/\s/,$a) ;
#print "\n ${a1} ${a2} ${a3} ${a4} ${a5} " ;
$qf[$i][0] = $a1 ;
$qf[$i][1] = $a2 ;
$qf[$i][2] = $a3 ;
$qf[$i][3] = $a4 ;
$qf[$i][4] = $a5 ;
#print "\n",$qf[$i][0]," ",$qf[$i][1],$qf[$i][2],$qf[$i][3],$qf[$i][4] ;
}

my $i=0, $j=0,$k=0,$l=0,$t1=0 ;
for ($i = 0 ; $i < $sigt1 ; $i++ )
{
for ($j=0 ; $j < $sigt2 ; $j++ )
{
for ($k =0 ; $k < $sigr1 ; $k++ )
{

for ( $l=0 ; $l < $sigr2 ; $l++ )
{
$ker[$i][$j][$k][$l] =  exp(-1*abs(($i-1)*($i-1))/9)*exp(-1*abs(($j-1)*($j-1))/9)*exp(-1*abs(($k-1)*($k-1))/9)*exp(-1*abs(($l-1)*($l-1))/9) ; 

#print " ",$ker[$i][$j][$k][$l] ; 
}
print "\n" ;
}
print "\n" ;
} 
print "\n" ;
}


for ($i=0 ; $i<1600 ; $i++ )
{
print "\n $i " ;


if( $qf[$i][0]==0 ||  $qf[$i][1]==0 ||  $qf[$i][2]==0 || $qf[$i][3]==0 ||  $qf[$i][$4]==0 )
{
#print "\n processing the row" ;
$the1 = int(floor(($i)/160)) ;
$the2  = int(floor(($i-$the1*160)/16)) ;
$r1 = int(floor( ($i - $the1*160 -$the2*16)/4));
$r2 = $i  - $the1*160 - $the2*16 - $r1*4 ;
print " state  $the1 $the2 $r1 $r2" ;
$sumd0 = 0 ;  $sumn0 = 0 ;
$sumd1 = 0 ;  $sumn1 = 0 ;
$sumd2= 0 ;  $sumn2 = 0 ;
$sumd3 = 0 ;  $sumn3 = 0 ;
$sumd4 = 0 ;  $sumn4 = 0 ;
for ($t1 = 0 ; $t1 < $sigt1 ; $t1++ )
{
for ($j=0 ; $j < $sigt2 ; $j++ )
{
for ($k =0 ; $k < $sigr1 ; $k++ )
{

for ( $l=0 ; $l < $sigr2 ; $l++ )
{

$st = ($the1+$t1 -1)*160 + ($the2 +$j-1)*16 +   ($r1 + $k -1)*4 + ($r2 + $l -1) ;
if ($qf[$i][0] == 0 and $the1+$t1-1 >= 0 and $the2+$j-1 >= 0 and $r1+$k-1 >= 0 and $r2+$l-1 >= 0 )
{
if ( $qf[$st][0]  !=  0)
{
$sumd0 = $sumd0+   $ker[$t1][$j][$k][$l] ;
$sumn0 =  $sumn0 + $qf[$st][0]*$ker[$t1][$j][$k][$l] ; 
}
}


if ($qf[$i][1] == 0 and $the1+$t1 -1 >= 0 and $the2 +$j-1 >= 0 and $r1 + $k -1 >= 0 and $r2 + $l -1 >= 0 )
{

if ( $qf[$st ][1]  !=  0)
{
$sumd1 = $sumd1 +   $ker[$t1][$j][$k][$l] ;
$sumn1 =  $sumn1 + $qf[$st][1]*$ker[$t1][$j][$k][$l] ; 
}
}


if ($qf[$i][2] == 0 and $the1+$t1 -1 >= 0 and $the2 +$j-1 >= 0 and $r1 + $k -1 >= 0 and $r2 + $l -1 >= 0 )
{

if ( $qf[$st ][2]  !=  0)
{
$sumd2 = $sumd2 +   $ker[$t1][$j][$k][$l] ;
$sumn2 =  $sumn2  + $qf[$st][2]*$ker[$t1][$j][$k][$l] ; 
}
}

if ($qf[$i][3] == 0 and $the1+$t1 -1 >= 0 and $the2 +$j-1 >= 0 and $r1 + $k -1 >= 0 and $r2 + $l -1 >= 0 )
{

if ( $qf[$st ][3]  !=  0)
{
$sumd3 = $sumd3 +   $ker[$t1][$j][$k][$l] ;
$sumn3 =  $sumn3  + $qf[$st][3]*$ker[$t1][$j][$k][$l] ; 
}
}

if ($qf[$i][4] == 0 and $the1+$t1-1 >= 0 and $the2 +$j-1 >= 0 and $r1 + $k -1 >= 0 and $r2 + $l -1 >= 0 )
{

if ( $qf[$st ][4]  !=  0)
{
$sumd4 = $sumd4 +   $ker[$t1][$j][$k][$l] ;
$sumn4 =  $sumn4  + $qf[$st][4]*$ker[$t1][$j][$k][$l] ; 
}
}

}  # for l 
}  # for k 
}  # for j
}  # for t1

} # if qf
$stat = false ;
if( $qf[$i][0] !=0  or  $sumd0==0 ) {  $uqf[$i][0] = $qf[$i][0] ;
# print "in if " ,$qf[$i][0]; 
} else { $uqf[$i][0] = $sumn0/$sumd0 ; $stat = true ;}
if( $qf[$i][1] !=0  or $sumd1==0 ) { $uqf[$i][1] = $qf[$i][1] ;
#print "in if " ;
}  else { $uqf[$i][1] = $sumn1/$sumd1 ; $stat = true ;}
if( $qf[$i][2] !=0 or  $sumd2==0 ) {  $uqf[$i][2] = $qf[$i][2] ;
#print "in if " ;
} else { $uqf[$i][2] = $sumn2/$sumd2 ;$stat = true ; }
if( $qf[$i][3] !=0  or  $sumd3==0 ) { $uqf[$i][3] = $qf[$i][3] ;
# print "in if " ;
}else { $uqf[$i][3] = $sumn3/$sumd3 ;$stat = true ; }
if( $qf[$i][4] !=0 or $sumd4==0 )  { $uqf[$i][4] = $qf[$i][4] ; 
#print "in if " ;
} else { $uqf[$i][4] = $sumn4/$sumd4 ;$stat = true ;}


  # if qf $i 0 == 0 or 
if ( $stat == true ){
#print uqf1 "\n", $qf[$i][0]," ", $qf[$i][1], " ", $qf[$i][2]," ",$qf[$i][3]," ",$qf[$i][4] ;
print  uqf1  "\n", $uqf[$i][0]," ", $uqf[$i][1]," ", $uqf[$i][2]," ", $uqf[$i][3]," ",$uqf[$i][4] ; 
#print  "   ", $qf[$i][0]," ", $qf[$i][1]," ", $qf[$i][2]," ", $qf[$i][3]," ",$qf[$i][4] ; $stat = false ;
 }
} # for i



close(uqf1) ; close(qf1) ;



