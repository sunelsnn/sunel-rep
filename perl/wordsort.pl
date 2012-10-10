#!/usr/bin/perl

@words=qx(cat file\* | awk -F: '{print \$1}'|sort) ;
#print @words ;

print"\n$words[0]" ;
for($i=0;$i<scalar(@words);$i++)
{
$str1 =$words[$i] ;
$str2=$words[$i+1] ;
#print "\n" ;
chomp($str1) ;
chomp($str2) ;
#print "\n B  $str1  $str2  E";
if( $str1 ne $str2 )
{ print "\n$str2" ; }

}
