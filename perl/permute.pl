#!/usr/bin/perl
use Getopt::Std;
require utilpac;
utilpac->import;
use DBD::mysql;
getopts('s:') ;
@chararray= split( //, $opt_s);

$length = scalar(@chararray) ;

#print "\n length $length" ;
#print "\n chararray @chararray" ;

$tpchar='';
$globalcount=0;
$globalprintcount=0 ;
@globalstrings;
permrecfunc($tpchar, $length) ;
my @globstrings = @globalstrings ; 
utilpac::dupstrings(@globalstrings);
#recfunc(reclevel, 

$globalcount=0;
$globalprintcount=0 ;








### permrecfunc 
sub permrecfunc()
{
my $tempchar;
my $level ;
my $tempcharloop ;
my $i ;
($tempchar, $level)= @_ ;
#print "\n  $tempchar $level" ;
if($level == 0)
{ 
# print "\n $tempchar" ;
$globalstrings[$globalprintcount]=$tempchar;
$globalprintcount++ ;

return ;
print "\n after return" ;
}

if ($level < 0)
{
print "\n level less than zero exiting" ;
 exit; }
for ($i=0;$i<$length;$i++)
{
$globalcount++ ;
if($globalcount > 1000000)
{ last ;}
#print "$globalcount " ;
$tempcharloop=$tempchar.$chararray[$i] ;
permrecfunc($tempcharloop,$level-1) ;
}

}



