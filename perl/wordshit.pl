#!/usr/bin/perl

use Getopt::Std ;
getopts('s:k:') ;

print "\n printing getopts $opt_k $opt_s" ; 
 $str = $opt_s ? $opt_s : $ARGV[0] ;
 $k = $opt_k ? $opt_k : $ARGV[1] ;
print($str);
print "\n" ;
print ($k) ;
print "\n" ;
@stringlist = split(' ', $str) ;
#$status[length(@stringlist) ;
@status; 
print scalar(@stringlist) ;	
print "\n" ;
if(scalar(@stringlist) < $k)
{ exit; }

print @stringlist ;
print "\n processing starts" ;
my $tempstr1, $tempstr2 ;
$index=0 ;
$i=0;
for ($i=0;$i<scalar(@stringlist);$i++)
{

print "\n $index  $status[$index] " ;
if($status[$index]==1)
{ $index=($index+1) % scalar(@stringlist); }

if ($i==0)
{ $tempstr1= $stringlist[$index] ;
 }
else 
{ $tempstr1= $tempstr2 ;
}
$status[$index]= 1 ;

if($status[($index+$k) % scalar(@stringlist)]==1) {
$tempstr2 = $stringlist[ ($index+$k+1) % scalar(@stringlist) ] ; }
else 
{ 
$tempstr2 = $stringlist[ ($index+$k) % scalar(@stringlist) ] ; 
}
$stringlist[($index+$k) % scalar(@stringlist) ]  =  $tempstr1 ; 

$index = ($index+$k) % scalar(@stringlist) ;


print " $tempstr1 $tempstr2 $index" ;
}
print "\n $i \n" ;

print(@stringlist) ;
print "\n" ;


