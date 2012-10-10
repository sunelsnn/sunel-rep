#!/usr/bin/perl
use Getopt::Std;

getopts('s:');
$str = $opt_s ;
@strarr = split(//,$str) ;
$strtest ;
for($i=0;$i<scalar(@strarr);$i++)
{
$strtest=$strtest.$strarr[$i] ;
}

print "\n printingconcat $strtest" ;
