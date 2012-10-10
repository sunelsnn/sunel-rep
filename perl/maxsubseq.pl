#!/usr/bin/perl
use Getopt::Std;

getopts('n:');

$numarray = $opt_n ;
@numbers= split(' ',$numarray) ;

$thissum=0;
$maxsum=0 ;
@lowerbound;
@upperbound;
$maxlbound;
$maxubound;
$seqs=0;
$lowerbound[0]=0; 
for ($index=0;$index<scalar(@numbers);$index++)
{
$upperbound[$seqs]=$index;
$thissum=$thissum+$numbers[$index] ;
if($thissum > $maxsum)
{
$maxsum = $thissum ;
$maxlbound = $lowerbound[$seqs] ;
$maxubound = $upperbound[$seqs]=$index;
}
if($thissum < 0)
{ $thissum = 0 ;
$seqs++;
$lowerbound[$seqs]=$index+1;}

}

$maxlbound=$maxlbound+1 ;
$maxubound=$maxubound+1 ;
print $maxsum ;
print "\n $maxlbound $maxubound" ;
