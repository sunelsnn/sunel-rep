#!/usr/bin/perl
use DBI;
use DBD::mysql;

eval {
my $dsn = "dbi:mysql:hw3" ;
my $dbh = DBI->connect($dsn, 'root','SNNsnn126',);
$mystmt = 'select ID,name, latlong, types, frequency from navaids' ;
my $exec_stmt = $dbh->prepare($mystmt) ;
$exec_stmt->execute();
while((@parm_value = $exec_stmt->fetchrow_array())) {
print "\n @parm_value";  }
$exec_stmt->finish() ;
$dbh->disconnect();
};
warn $@ if $@;	


