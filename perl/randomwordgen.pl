#!/usr/bin/perl
use integer; 

my $range = 2147483647;
$range = 2*$range ;
my $random_number = int rand($range);
open(fileran, ">>numberfile.txt");

for ( $i=0;$i<1000000; $i++)
{
$random_number = int rand($range);
$random_number = $random_number-2147483647 ;

print fileran "$random_number\n" ;
}
close(fileran) ;
