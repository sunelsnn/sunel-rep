#!/usr/bin/perl
sub trim($); 

my $range = 10000;
my $random_number = int rand($range);
open(infileranname, "userlist1.txt");
#open(infileranitem, "ranfilechar2") ;
$infileranitems = "itemlist1.txt" ;
open(userpref, ">>userpref1.csv") ;
@itemlist=`/bin/cat $infileranitems` ; 

while(<infileranname>)
{
$username = trim($_) ;

$rand_noitems = int  rand(10);
for($index1=0;$index1<$rand_noitems;$index1++)
{
$randitemno = int rand(100);
$randval = int rand(10) ;
$randitemname = trim($itemlist[$randitemno]) ;
print userpref "$username\n" ;
}
}

close(userpref) ;
close(infileranname);



sub trim($)
{
	my $string = shift;
	$string =~ s/^\s+//;
	$string =~ s/\s+$//;
	return $string;
}
