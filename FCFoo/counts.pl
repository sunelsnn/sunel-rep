#!/usr/bin/perl 

$filename = shift ;


open(FILE1, $filename) ;
$srcnt =1000 ;
$cnt=0;
$cnt1=0;
$cntsrt = 0 ;
my $str ;
while($str=<FILE1>)
{
if($str =~ /SUCCESSFUL PASS/)
{ $cnt++ ; }
if( $str =~ /UNSUCCESSFUL PASS/ )
{ $cnt1++ ; }

if ($str =~ /NEW AGENT DECIDE CLOCK CYCLE :CYCLE#/ )
{  $cntsrt++ ;
if ( $cntsrt > 800 )
{
for($i =0 ;$i<100;  $i++ ) {
$srterm = $srcnt+$i ;
if ($str =~ /NEW AGENT DECIDE CLOCK CYCLE :CYCLE# ${srterm}/ )
{   
  print "\n $srcnt,$cnt,$cnt1" ;
  $srcnt= $srcnt+1000 ;
  $cnt=0 ; $cntsrt=0 ; $cnt1=0;
$i=0 ;
break ;
} # if $str stterm
} # for 
} # if $cntsrt
} # if $str 
} # while


close(FILE1) ;



