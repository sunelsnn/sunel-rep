
	 sunil Kumar <sunelsnn@gmail.com>
(no subject)
Sunil Kumar <sunelsnn@gmail.com>	 Sat, Jul 17, 2010 at 5:34 PM
To: sunelsnn@gmail.com
/usr/tools/oracle/Standard/script cat mvdc_archivelog_utl.pl
#!/oracle/product/perl
#!/usr/local/bin/perl
###################################################################################
# Name    : archivelog_utl.pl
# Version : 1.0
# Date    : 07-25-2005
# Author  : raraveet
#
# Description :
#   ------------- on PROD and DR hosts
----------------------------------------------
#   * This utility purges the archive-dir directory of all  /archdir/SID*.dbf.gz
#       o Starts purging if %usage > pct_upper_limit
#                        and until %usage < pct_lower_limit
#                        and archivelog is applied on the standby
#                        and archivelog exists on tape
#                         (currently any log morethan 1d is considered
to be on tape)
#   * Ability to zip/unzip in multiple streams & Option to
ENABLE/DISABLE zipping
#   * Other parameters can be specified through cron exception form from DBTS
#
#   ------------- on PROD host
------------------------------------------------------
#   * If sad_parfile exists , then switch archive destination is auto enabled
#       o if %used is > pct_upper_limit even after purge then looks for
#         possible switch archive log
#   * If DR exists then,
#       o oracle logswitch is auto enabled,
#         if last archivelog generated is more than 20m,then logswitch happens.
#   * If DR exists then following alerts are auto enabled,
#               Alert1-> alerts if DR host ARCHIVELOG LAGS BEHIND
production host
#                        by certain no. of minutes
#               Alert2-> alerts if DR APPLIED LOG LAGS BEHIND
production log archive
#                        by certain no. of minutes
#               o touch flag like ORACLE_SID.nodrhost.2h at
prodhost:/usr/tools/oracle
#                 in case of know issues when dr host is down
#
#   ------------- on DR host
--------------------------------------------------------
#   * If host is DR,
#       o zips archive logs applied on DR ,
#       o unzips window of logs and
#       o purges applied archive logs
#           o touch flag like SID.nopage.24h at
drhost:/usr/tools/oracle/recovery/norecover
#             to disable email/paging dr alerts during know issues
#

$Synopsis = <<X;
  Syntax  : archivelog_utl -i<SID|ALL>
  Example1: archivelog_utl -iCAPPROD
  Example2: archivelog_utl -iALL [ scans oratab ]

  Other Options:
  Example: archivelog_utl -iCAPPROD -O ziponly|purgeonly|sadonly|nosad
           archivelog_utl -iCAPPROD -O drmonitoronly|nodrmonitor
           archivelog_utl -iCAPPROD -P3 -S120m

 Defaults: [command line options]
  MAXPROCS       (opt -P) = 4   [multiple process for zip/unzip]
  TIMEOUT        (opt -S) = 30m [script timeout]
  TAPE_CHECK_TIME(opt -T) = 1d  [check tape exists(use this option with CAUTION]

 Defaults: [Modifiable thro' DBTS cron exception]
  pct_upper_limit       = 85
  pct_lower_limit       = 65
  throttle_window       = 100
  zip_option            = ENABLE

X
#
# MODIFICATION HISTORY:
# NAME          DATE            COMMENTS
# raraveet      07/25/2005      Initial Version (1.0)
# raraveet      12/20/2005      Bug fixes after testing
# raraveet      01/18/2006      Done with Final modifications to v1.0
# raraveet      06/16/2006      Fixed bug related to fuser
# raraveet      07/17/2006      Enhanced script to look at log_archive_format
#                               while deriving log_archive_dest .
# raraveet      08/02/2006      fix issue related to high archive
#                               generation to check %usage inbetween
#                               zipping process
# raraveet      08/04/2006      Introduce checkNopage to disable paging
#                               related to dr logs during known issues/refreshes
# raraveet      11/10/2006      Added fuseropt,sshopt,document,alarm,
#                                     drhost,retry options, etc., ...
###################################################################################

use POSIX                                               ;
$SIG{PIPE} ='IGNORE'                                    ;
require "stat.pl"                                       ;
use Getopt::Std                                         ;
use FileHandle                                          ;
use File::Basename                                      ;
use Time::Local                                         ;
require "/usr/tools/oracle/Standard/script/perllib.pl"  ;
use lib "/usr/tools/oracle/Standard/lib/"               ;
use StdDBPackage                                        ;
use Lock                                                ;
eval "use lib '/usr/cisco/packages/oracle/current/Perlmod/lib'";
eval "use DBI" ;
eval "use DBD::Oracle" ;

$| = 1; # don't buffer output , flush std out
$SIG{ALRM} = sub (){ alarm($TIMEOUT_EVERY);
                     &showError("$pname:running long ... ,please check
",$instanceI) };
############################ MAIN ############################################
&mainFnc();
############################ MAIN ############################################

#-----------------------------------------------------------------------------
# mainFnc :
#     This is the main function that calls all other modules
#-----------------------------------------------------------------------------
sub mainFnc()
{

#system ("touch ./abcd");
#print DOUT "\n in the mvdc archive log util" ;
        #------------ Read/process Input parameters -------------------------#

        $mvdc_flag = "TRUE" ; $DB_role ;
         @remote_dg ;
        @remot_dglist ;
        #%dgthread ;
        @standby_host ;@standby_inst ;@standby_instno ;@standby_dbname ;
        &readInput();


        #------------ check if process already running ----------------------#
        &Lock::lock("$lockfile");

###     #------------ Set oraenv,drthread,mountFilesystems ------------------#
        &setEnv() ;
        eval { alarm($TIMEOUT);

        $DB_role=&chkDatabaseRoleReturn($instance) ;
        chomp($DB_role);
        print LOGFILE "\n DATABASE role $DB_role" ;
        #------------ Force Swicth Archive Destination
---------------------- for Primary "
        if( $DB_role eq "PRIMARY" ) {
        &switchArchDestOnly($instance) if ( lc($opt_O) eq "sadonly" );
        &switchArchDest($instance) if ( lc($opt_O) eq "force_sadonly" ) ;
          }

 #------------ Force Swicth Archive Destination ----------------------
for standby its recovering"

        if ( $DB_role  eq "STANDBY" )
           { print "\n db status $DB_role" ; $isdghost_f="YES" ;
               my $recovery_status =
&checkRecoveryInst($instance_l);chomp($recovery_status) ;
                print LOGFILE  "\n recovery status $recovery_status" ;
                 print LOGFILE  "\n is set standby
$dbinfo_arr{$instance}{isSetstandby_archive_dest}"  ;
                if  ( $recovery_status eq "TRUE")
                {print LOGFILE " \n recovery status $recovery_status" ;
        &switchArchDestOnly($instance) if ( lc($opt_O) eq "sadonly" );
        &switchArchDest($instance) if ( lc($opt_O) eq "force_sadonly" );
                }
        }
        #------------ Zip and Purge process ---------------------------------#
        &zipArchive("compress")   if ( $option_O eq "Y" or lc($opt_O)
eq "ziponly" );
        &purgeArchive()           if ( $option_O eq "Y" or lc($opt_O)
eq "purgeonly" );
        &zipArchive("uncompress") if ( $isdghost_f eq "YES" ) ;
###        &findDupLogs() ;
###     &checkDRhealth()          if ( $option_O eq "Y" or lc($opt_O)
eq "drmonitoronly" );
        &exitProgram(0); };
}

#-----------------------------------------------------------------------------
# readInput :
#       o sets env paths
#       o sets defaults
#-----------------------------------------------------------------------------
sub readInput()
{
        &Usage if ( !getopts('h:d:u:l:a:w:z:i:P:L:O:T:Z:S:') ||
defined($opt_h) );
        $instance= $opt_i ? uc($opt_i) : uc($ARGV[0]) ;
        &Usage if ( !$instance );
        $instanceI= $instance ;

        # as constants for most envs, but can be overwritten
        # from command line arguments
        $MAXPROCS               = int($opt_P) ? $opt_P : 4;
        $MAXLOGCYCLE            = int($opt_L) ? $opt_L : 7;
        $TAPE_CHECK_TIME        = $opt_T      ? $opt_T :"1d";
        $ZIP_ARCHIVE_TIME       = $opt_Z      ? $opt_Z :"2m";
        $SCRIPT_TIMEOUT         = $opt_S      ? $opt_S :"30m";
        &Usage if ( defined($opt_O) and  !( lc($opt_O) eq "ziponly"
or lc($opt_O) eq "purgeonly" or
                                         lc($opt_O) eq "sadonly"
or lc($opt_O) eq "nosad"     or
                                         lc($opt_O) eq "force_sadonly" or
                                         lc($opt_O) eq "nodrmonitor"
or lc($opt_O) eq "drmonitoronly"
                                        ) ) ;
        $option_O               = "Y" if ( ! defined($opt_O)     or
                                           lc($opt_O) eq "nosad" or
                                           lc($opt_O) eq "nodrmonitor" );
        # set default paths
        $pname                  = "new_mvdc_archivelog_utl.pl";
        $exceptfile             =
"/usr/tools/oracle/Standard/script/exceptionDB.par";
        $sad_parfile            = $exceptfile ;
        $thread_path            = "/usr/tools/oracle/recovery/thread";
        $norecover_path         = "/usr/tools/oracle/recovery/norecover";
        $sync_arch_path         = "/usr/tools/oracle/sync_arch/adm";
        $tape_parfile           = "/usr/tools/oracle/tapefiles" ;
#currently not in use

        # these values should be modified thro' cron exception
        # if cron exception exists then command line input parameters
are ignored
        $pct_upper_limit_d      = $opt_u ? $opt_u : 20;
        $pct_lower_limit_d      = $opt_l ? $opt_l : 10;
        $archive_retain_time_d  = $opt_a ? $opt_a : "1d" ;
        $throttle_window_d      = $opt_w ? $opt_w : 100 ;
        $zipmode_d              = $opt_z ? uc($opt_z) : "ENABLE";
        $sync_arch_mail_limit_d = "2h";
        $sync_arch_page_limit_d = "4h";
        $drlog_mail_limit_d     = "6h";
        $drlog_page_limit_d     = "10h";

        # derived or almost like constants variables
        $LOGSWITCH_TIME     = "19m";
        $DEFAULT_THREAD     = 10000000000;
        $TIMEOUT            = &convertTime($SCRIPT_TIMEOUT);
        $TIMEOUT_EVERY      = 1200 ; # this is in seconds (default 20m)
        $instance_number    = 1;
        chomp($local_host = `hostname`);
        $archformat         = "(.*)\\/(\\w*).arch[_]*(\\d)_(\\d*)[_]*(.*).dbf";
#        $archformatG        =
"(.*)\\/[GZIP\\.]*(\\w*).arch[_]*(\\d)_(\\d*)[_]*(.*).dbf";
# $archformat         = "(.*)\/(\w*).arch[_]*(\d)_(\d*)[_]*(.*).dbf" ;
         $archformatG        =
"(.*)\/[GZIP\.]*(\w*).arch[_]*(\d)_(\d*)[_]*(.*).dbf";
        $archsuffix         = ".gz"; #currently in use for DG envs., only
        my ($sec,$min,$hour,$mday,$mon,$year,$wday,
        $yday,$isdst)=localtime(time);
        $year=$year+1900;
        $mon=$mon+1 ;

        $lockfile           = "$pname.$instance";
        $lockfile           = "$pname.$instance.".lc($opt_O) if (
defined($opt_O));
   #     $logfile            = "/var/tmp/${lockfile}.LOG";
         $logfile            =
"/var/tmp/${lockfile}_$year.$mon.$mday.$hour.$min.$sec.LOG";
        $statfile           = "/var/tmp/".$lockfile.".statfile";

        # sets os specific commands
        &setOSCommands();

        # log rotation
        &logRotation();
}

#-----------------------------------------------------------------------------
# setEnv :
#     set env , defaults certain parameters
#     calls modules getDRInfo and prepareMountFS to get archive mount points
#-----------------------------------------------------------------------------
sub setEnv(){

        open(LOGFILE, ">>${logfile}") || die "Cannot open logfile
$logfile. $!\n";
        LOGFILE->autoflush(1);
        print "\n$pname: Started : ",&ctime(time);
        print LOGFILE "\n$pname: Started : ",&ctime(time);
        print LOGFILE "\n IN MVDC ARCHIVE LOG UTIL" ;
        print "\nsetEnv:";
        print LOGFILE "\nsetEnv:";
        $isdrhost_f  = "NO"; # indicates whether the host is
production or DR server
        $isdghost_f ="NO" ; # indicates where the host is a DG standby server

        if($instanceI eq "ALL"){
         #  pop(@instanceA);
         #  open (ALLTAB,"/var/opt/oracle/oratab") ||
&showError("$pname:Can't Open oratab $!");
         #  while (<ALLTAB>) {
    #           next if (/^#/ || /^\s/ );
        #       next if (/OIDPRD/ or /LISTENER/ or /CLIENT/) ;
    #           ($instance,$ora_home,$db_flag) = split(/:/);
#               push(@instanceA,$instance);
#          }
#          close(ALLTAB);

                print LOGFILE "\n cannot proces for -IALL" ; exit(0);
                }
        else{
           $instance          = $instanceI;
           $instance          = split(',',$instanceI) if ( $instanceI =~ /,/);
        }

        #foreach(@instanceA){
        $instance=$instanceI; chomp($instance) ;
        $DB_role=&chkDatabaseRoleReturn($instance) ;
        print LOGFILE "THIS IS THE INSTANCE THAT IS WILL BE  PROCESSED
IN THIS SCRIPT  $instance AND its role is $DB_role " ;
        $dbinfo_arr{$instance}{zip_cnt}   = 0;
        $dbinfo_arr{$instance}{unzip_cnt} = 0;
        $dbinfo_arr{$instance}{unzip_num} = 0;
        $dbinfo_arr{$instance}{purge_cnt} = 0;
        $drthread{$instance}              = 0;
#       @dgthread{$instance} ;
        $drexists_f{$instance}            = "NO";
        $dbinfo_arr{$instance}{isDataguard}= "YES";
        $dbinfo_arr{$instance}{isMVDCDataguard}="YES" ; # set yes for
MVDC since all of them are DG based.
        $dbinfo_arr{$instance}{isSetlog_archive_dest_1}= "NO";
        $dbinfo_arr{$instance}{isSetstandby_archive_dest} = "NO" ;
        if($instance =~ /(\w+)(\d)/)
                        {       $dbinfo_arr{$instance}{instance_number} = $2 ;
                                $dbinfo_arr{$instance}{dbname} = $1 ;
                        }
        &setOraclehome($instance);
        &prepareMountFS($instance);
        &getExceptionValues();
        &getDbParameters($instance);
#       print LOGFILE  $instanceI $dbinfo_arr{$instance} ;
        &getDGInfo($instance) ;
        print LOGFILE  "\n is set standby
$dbinfo_arr{$instance}{isSetstandby_archive_dest}  is set log archive
$dbinfo_arr{$instance}{isSetlog_archive_dest_1}" ;
                # } ### DG for MVDC
        print "\n";print LOGFILE "\n" ;
        print LOGFILE  $instanceI ; #print LOGFILE @dbinfo_arr{$instance} ;
}

#-----------------------------------------------------------------------------
# checkProcessRunning :
#     Check if process is already running,
#     Uses 'ps' to find if there is same job is already running and also
#     doing grep for 'perl' to distinguish same job being open by diff
#     commands like 'vi'
#-----------------------------------------------------------------------------
sub checkProcessRunning()
{
        print "checkProcessRunning:";
        if ( -f "/tmp/$pname.${instance}.lock") {
                open (PID, "/tmp/$pname.${instance}.lock")
                        || &showError("$pname:Cannot open
/tmp/$pname.${instance}.lock $!");
                $old_pid = <PID>;
                print "old pid=$old_pid ,new pid=$$ ,";
                close (PID);
                $pcnt=`$PS -ef |grep -v grep |grep perl |grep -w
$old_pid |grep $pname|wc -l`;
                #print "$PS -ef |grep -v grep |grep perl |grep -w
$old_pid |grep $pname|wc -l";
                chomp($pcnt);
                if ( $pcnt != 0 )
                {
                        print "The $pname process is already running
under pid $old_pid\n";
                        exit
                }
        }
        open (NEW_PID, ">/tmp/$pname.${instance}.lock");
        print NEW_PID $$;
        close (NEW_PID);
}

#-----------------------------------------------------------------------------
# setOraclehome :
#    Sets  ORACLE_HOME based on /etc/oratab
#    sets envs like mailto ,pageto from standard package, job exists if database
#    is not found in /etc/oratab
#-----------------------------------------------------------------------------
sub setOraclehome()
{
    my $dbname = shift;
    $db_check="N";
    open(ORATAB, "/var/opt/oracle/oratab") ||
&showError("$pname:setOraclehome:Can't Open oratab $!");
    while (<ORATAB>) {
        if (/^${dbname}:/)
        {
            $db_check              = "Y";
            $oracle_home           = (split(':'))[1];
            $ENV{'ORACLE_SID'}     = $dbname;
            $ENV{'ORACLE_HOME'}    = $oracle_home;
            $ENV{'LD_LIBRARY_PATH'}= "$oracle_home/lib";
            $ENV{'SHLIB_PATH'}     = "$oracle_home/lib";
           # ($mailto_d,$pageto_d,$warn_d,$alert_d)=&StdDBPackage::get_default_value($dbname);
            $mailto_d=$pageto_d=""; # TEST-while testing
            $dbinfo_arr{$dbname}{mailto} = $mailto_d;
         #   $dbinfo_arr{$dbname}{pageto} = $pageto_d;
        #   $dbinfo_arr{$dbname}{pageto} = "db-monitor-duty"
             $dbinfo_arr{$dbname}{pageto} = ""
                                        if ( !
defined($dbinfo_arr{$dbname}{pageto}) );
        }

    }
    close(ORATAB);

    if( $db_check eq "N"){
            print "$pname:!! Invalid database name\n";
            print LOGFILE "$pname:!! Invalid database name\n";
            exit;
    }
}

#-----------------------------------------------------------------------------
# setOSCommands :
#    Set os independant commands ,
#    - Using grep % on HP/Linux but not on Solaris as the command 'df'
#      not working along with grep
#    - force gzip is required in case if prev run is killed for some
#      reason and have both dbf and dbf.gz files
#-----------------------------------------------------------------------------
sub setOSCommands()
{
        $os=`uname`;
        chomp($os);
        if ( $os eq "HP-UX" ) {
                $dfopt  ="| grep %";
                $DF     ="/usr/bin/bdf";
                $PS     ="/usr/bin/ps";
                $MOUNT  ="/etc/mount";
                $MAILX  ="/usr/bin/mailx";
                $GZIP   ="/usr/local/bin/gzip -f";
                $SSH    ="/usr/local/bin/ssh";
                $sshopt ="-o BatchMode=yes -o
NumberOfPasswordPrompts=1 -o KeepAlive=no " ;
                $FUSER  ="/usr/tools/oracle/fuser";
                $FUSER  ="/usr/sbin/fuser" if(! -x "$FUSER");
        }
        elsif ( $os eq "SunOS" ) {
                $DF     ="/usr/bin/df -k";
                $PS     ="/usr/bin/ps";
                $MOUNT  ="/etc/mount";
                $MAILX  ="/usr/bin/mailx";
                $GZIP   ="/usr/local/bin/gzip -f";
                $SSH    ="/usr/local/bin/ssh";
                $sshopt ="-o BatchMode=yes -o
NumberOfPasswordPrompts=1 -o KeepAlive=no " ;
                $FUSER  ="/usr/sbin/fuser";
        }
        elsif ( $os eq "Linux" ) {
                $dfopt    ="| grep %";
                $DF       ="/usr/local/bin/df";
                $PS       ="/bin/ps";
                $MOUNT    ="/etc/mount";
                $MAILX    ="/bin/mailx";
                $GZIP     ="/usr/local/bin/gzip";
                $SSH      ="/usr/local/bin/ssh";
                $sshopt ="-o BatchMode=yes -o
NumberOfPasswordPrompts=1 -o KeepAlive=no " ;
                $fuseropt = "-t ";
                $FUSER    ="/usr/local/bin/lsof";
        }
        # validation of os commands
        if(! -x "$FUSER"){
                print "\n  Error!! Unable to find $FUSER executable ";
                print "\n  Program terminated ";
                exit(1);
        }
}

#-----------------------------------------------------------------------------
# getCurrArchDest :
#  - Wrapper function that invokes appropiate functions
#    based on whether DR exists or not
#  - thread_file is verified to determine DR host
#-----------------------------------------------------------------------------
sub getCurrArchDest()
{
        my $dbname      = shift;
        print LOGFILE "\n getting currarchdest: for instance $dbname" ;
     #   $thread_file    = "$thread_path/${dbname}_thread1.dat";
#       if ( -f  "$thread_file" ){
        if ( &chkDatabaseRoleReturn($dbname) eq "STANDBY" )     {
                &getCurrArchDestFromFile($dbname);
        }
        elsif ( &chkDatabaseRoleReturn($dbname) eq "PRIMARY" ) {
                        print LOGFILE "\n database role is primary " ;
                        &getCurrArchDestFromDB($dbname);
        }
}

#-----------------------------------------------------------------------------
# getCurrArchDestFromDB :
#  -Determines current archive destination from database.
#   if database is in NOARCHIVE mode or cannot be connected then the
#   function returns null log_archive_dest and the DB is IGNORED
#   for archive management.
#  -the format expected ( need atleast SID,arch,dbf in archivelog
#         Ex:  log_archive_dest      = /archive/CAPPROD_arch/CAPPROD.arch
#              log_archive_format    = %t_%s.dbf
#  -log_archive_dest_2 is used to determine if DG is implemented
#-----------------------------------------------------------------------------
sub getCurrArchDestFromDB()
{
    my $instance_l       = shift;
    my $log_archive_dest = "";
    my $log_archive_dir  = "";
    undef($dg_dbname);
    undef($db_unique_name);

    if ( -f "$ENV{ORACLE_HOME}/dbs/init${instance_l}.ora" ) {
        print "\n getCurrArchDestFromDB:$instance_l:";
        print LOGFILE "\n getCurrArchDestFromDB  : $instance_l:";
        my $sqlstmt="SELECT name,'string' string ,value
                     FROM   v\\\$parameter
                     WHERE  name IN
('instance_number','db_name','log_archive_format','log_archive_dest_1',

'log_archive_dest_2','standby_archive_dest','compatible')";
        open(SQLDBA, "$oracle_home/bin/sqlplus /nolog << END
        connect /as sysdba
        alter system archive log current ;
        archive log list
        col type for a10
        col name for a24
        col string for a6
        col value for a400
        set pagesize 1000 linesize 500
        --show parameter instance_number
        --show parameter db_name
        --show parameter log_archive_format
        --show parameter log_archive_dest_2
        --show parameter standby_archive_dest
        $sqlstmt ;
        exit
        END |") || &showError("$pname:getCurrArchDestFromDB:sqlplus
error: $!",$instance_l,1);

        @data = <SQLDBA>;
        (@data1 = grep (/Database log mode/,@data)) ;
        $archive_mode=(split(' ', $data1[0]))[4];

        #$archive_mode=""; #TEST-simulate node is down
        if ( $archive_mode eq "" ){
                print "Warning:$instance_l: Ignore/Unable to connect ";
                print LOGFILE "Warning:$instance_l: Ignore/Unable to connect ";
                return(1);
        }
        else{
        if ( $archive_mode =~ /No/ ) {
                print " is in No Archivemode";
                print LOGFILE " is in No Archivemode";
                return(1);
        }

        # find db_name
        #       print LOGFILE "\n getcurrarchfromdb: @data" ;
        (@data3  = grep(/^db_name/, @data)) ||
&showError("$pname:Can't Find db_name: @data",$instance_l,1);
        $db_name = (split(' ', $data3[0]))[2];

        (@data4  = grep(/^log_archive_format/, @data))
                        || &showError("$pname:Can't Find
instance_number: @data",$instance_l);
        $log_archive_format = (split(' ', $data4[0]))[2];

        (@data2  = grep(/^Archive destination/, @data))
                        || &showError("$pname:Can't Find Archive
Location: @data",$instance_l,1);
        $log_archive_dest   = (split(' ', $data2[0]))[2];
        $log_archive_dest   = $log_archive_dest."/"
                        if ( -d $log_archive_dest and
!($log_archive_dest =~/\/$/) );
        $log_archive_dest   = $log_archive_dest.$log_archive_format;
        $log_archive_dest   = (split('%',$log_archive_dest))[0];
        ($log_archive_dir)  =  $log_archive_dest  =~ /(.*)\/(\w*).arch/ ;

        # forcing standard format
        print LOGFILE " \n currarchdest $2 , $db_name , $instance_l " ;
        if ( !($2 eq ${db_name} or $2 eq ${instance_l}) ){
             print "Warning:$instance_l: Invalid log_archive_dest format ";
             print LOGFILE "Warning:$instance_l: Invalid
log_archive_dest format :$log_archive_dest";
             $log_archive_dir ="";
             return(1);
           }

        # find last log sequence
        (@data3 = grep(/^Next log sequence to archive/, @data))
                                ||&showError("$pname:Can't Find Next
log sequence: @data",$instance_l,1);
        $next_log_sequence      = (split(' ', $data3[0]))[5];
        $last_arch_sequence     = int($next_log_sequence) - 1;
        print LOGFILE "\n last arch sequence  $last_arch_sequence" ;

        # find instance number
        (@data4  = grep(/^instance_number/, @data))
                        || &showError("$pname:Can't Find
instance_number: @data",$instance_l);
        $instance_number        = (split(' ', $data4[0]))[2];
        $instance_number        = $instance_number +1 if (
$instance_number  == 0 )  ;
        #print "$instance_number:";
        #print LOGFILE "$instance_number:";

        (@data4  = grep(/^compatible/, @data))
                        || &showError("$pname:Can't Find compatible:
@data",$instance_l);
        $compatible        = (split(' ', $data4[0]))[2];


        # find log_archive_dest_1
        (@data4  = grep(/^log_archive_dest_1/, @data))
                        || &showError("$pname:Can't Find
log_archive_dest_1: @data",$instance_l);
        $log_archive_dest_1     = (split(' ', $data4[0]))[2];
        $dbinfo_arr{$instance_l}{isSetlog_archive_dest_1}="YES"
                        if ( defined($log_archive_dest_1) ) ;

        # find log_archive_dest_2 and standby_archive_dest for Datagaurd
        (@data4  = grep(/^log_archive_dest_2/, @data))
                        || &showError("$pname:Can't Find
log_archive_dest_2: @data",$instance_l,1);
          print LOGFILE "\n LOG ARCHIVE DEST 2 RAW DATA @data4 " ;

        #$log_archive_dest_2     = (split(' ', $data4[0]))[2];
        $log_archive_dest_2 = &getDBParm("log_archive_dest_2",$instance_l) ;
        $log_archive_dest_2 =
&getDBParmFile("log_archive_dest_2",$instance_l) if (!
defined($log_archive_dest_2)) ;
        if ( defined($log_archive_dest_2) )
                        {
                                if ( ! ($log_archive_dest_2 =~ /DESCRIPTION/i))
                                        {

$dg_dbname=(split('=',$log_archive_dest_2))[1];
                                                $dg_dbname=(split('
',$dg_dbname))[0];
                                                my $tnsping_data
       = qx($ENV{'ORACLE_HOME'}/bin/tnsping $dg_dbname);
                                                $tnsping_data
    =~s/\s+//g ;
                                                $standby_host[0] =
(split('\)',(split('host=',lc($tnsping_data) ))[1]))[0];
                                                if ($tnsping_data =~
/instance_name/i)
                                                        {

$tnsping_data =~ /instance_name(\s*)=(\s*)(\w+)\)(.*)/i ;

#$standby_inst[0]= split ( /instance_name(\s*)=(\s*)(\w+)\)(.*)/i
,$tnsping_data) ;

$standby_inst[0] = $3 ;
                                                                if
($standby_inst[0]  =~ /(\w+)(\d)/ )
                                                                        {

         $standby_dbname[0] = $1 ;

         $standby_instno[0]= $2 ;
                                                                        }
                                                                else {
$standby_dbname[0]  = $standby_inst[0] ;  undef ($standby_instno[0]) ;
                                                                     }
                                                        }
                                        }
                                else  {
                                                $log_archive_dest_2
=~ /(.*)\(INSTANCE_NAME=(\w*)\)(.*)/i ;
                                                $standby_inst[0]= $2 ;
print LOGFILE "\n standby inst $standby_inst[0] " ;
                                                $log_archive_dest_2 =~
/(.*)HOST=(\w+)\-(.+)/i ;
                                                $standby_host[0]
=(split(/\(HOST=/i,$log_archive_dest_2))[1] ;
                                                print LOGFILE "\n
standby host  $standby_host[0] " ;

$standby_host[0]=(split ( /\)/, $standby_host[0]))[0] ;
                                                print LOGFILE
$standby_host[0]  ;

                                                if ($standby_inst[0]
=~ /(\w+)(\d)/)
                                                        {

 $standby_dbname[0] = $1 ;

 $standby_instno[0]= $2 ;
                                                        }
                                                else
                                                        {
 $standby_dbname[0]  = $standby_inst[0] ;
                                                                undef
($standby_instno[0] ) ;
                                                        }
                                                print LOGFILE "\n
STANDBY HOST INFO  $standby_host[0]  $standby_dbname[0]
$standby_inst[0]  $standby_instno[0]" ;
                                        } # else DES
                        } # if define

        (@data4  = grep(/^log_archive_dest_3/, @data)) ;
#                               || &showError("$pname:Can't Find
log_archive_dest_3: @data",$instance_l);
#        $log_archive_dest_3 = (split(' ', $data4[0]))[2] ;
         $log_archive_dest_3 = &getDBParm("log_archive_dest_3",$instance_l) ;
        $log_archive_dest_3 =
&getDBParmFile("log_archive_dest_3",$instance_l) if (!
defined($log_archive_dest_3)) ;
        if ( defined($log_archive_dest_3) )
                                { if (! ($log_archive_dest_3 =~ /DESCRIPTION/i))
                                        {

$dg_dbname1=(split('=',$log_archive_dest_3))[1] ;
                                                $dg_dbname1=(split('
',$dg_dbname))[0];
                                                $tnsping_data
    = qx($ENV{'ORACLE_HOME'}/bin/tnsping $dg_dbname1);
                                                $tnsping_data
    =~s/\s+//g ;
                                                 $standby_host[1] =
(split('\)',(split('host=',lc($tnsping_data) ))[1]))[0];
                                                 if ($tnsping_data =~
/instance_name/i)
                                                        {

$tnsping_data =~ /instance_name(\s*)=(\s*)(\w+)\)(.*)/i ;

#$standby_inst[0]= split ( /instance_name(\s*)=(\s*)(\w+)\)(.*)/i
,$tnsping_data) ;

$standby_inst[1] = $3 ;
                                                                if (
$standby_inst[1]  =~ /(\w*)(\d)/)
                                                                        {

         $standby_dbname[1] = $1 ;

         $standby_instno[1]= $2 ;
                                                                        }
                                                                else
                                                                        {

          $standby_dbname[1]=$standby_inst[1] ;

         undef ( $standby_instno[1]) ;
                                                                        }
                                                        }
                                        }
                                  else {
                                                $log_archive_dest_3
=~ /(.*)\(INSTANCE_NAME=(\w*)\)(.*)/i ;
                                                $standby_inst[1]= $2 ;
                                                $log_archive_dest_3 =~
/(.*)HOST=(\w+)\-(.+)/i ;
                                                $standy_host[1]
=(split(/\(HOST=/i,$log_archive_dest_3))[1] ;

$standby_host[1]=(split ( /\)/, $standby_host[1]))[0] ;
                                                if ( $standby_inst[1]
=~ /(\w*)(\d)/)
                                                        {

$standby_dbname[1] = $1 ;

$standby_instno[1] = $2 ;
                                                        }
                                                else    {

$standby_dbname[1] = $standby_inst[1] ;
                                                                undef
($standby_instno[1]) ;
                                                        }
                                        }

        # need checking                 }

                # find standby arch dest
                (@data4  = grep(/^standby_archive_dest/, @data))
                        || &showError("$pname:Can't Find
standby_archive_dest: @data",$instance_l);
                $standby_archive_dest     = (split(' ', $data4[0]))[2];
                if ( $standby_archive_dest =~ /$db_name/ ){
                        print "DG=Y";
                        print LOGFILE "DG=Y";
                        $standby_archive_dest = "$standby_archive_dest/"
                          if ( !($log_archive_format =~ /^%t/) and
!($standby_archive_dest =~/\/$/));
                        $standby_archive_dest =
$standby_archive_dest.$log_archive_format;
                        $standby_archive_dest =
(split('%',$standby_archive_dest))[0];
                        $dbinfo_arr{$instance_l}{standby_archive_dest}
= $standby_archive_dest;
                        $dbinfo_arr{$instance_l}{isDataguard}          = "YES";
                        $dbinfo_arr{$instance_l}{db_unique_name}
= &getDBUniqueName($instance_l)
                                                        if (
$compatible =~ /^10/ );
                }

        }

        $dbinfo_arr{$instance_l}{instance}           = $instance_l;
        $dbinfo_arr{$instance_l}{database}           = $db_name;
        $dbinfo_arr{$db_name}{instance}              = $instance_l;
        $dbinfo_arr{$instance_l}{last_arch_sequence} = $last_arch_sequence;
        $dbinfo_arr{$instance_l}{log_archive_dest}   = $log_archive_dest;
        $dbinfo_arr{$instance_l}{log_archive_dest_2} = $log_archive_dest_2;
         $dbinfo_arr{$instance_l}{log_archive_dest_3} = $log_archive_dest_3 ;
        $dbinfo_arr{$instance_l}{log_archive_dir}    = $log_archive_dir;
        $dbinfo_arr{$instance_l}{log_archive_format} = $log_archive_format;
        $dbinfo_arr{$instance_l}{dg_dbname}          = $dg_dbname ;
        $dbinfo_arr{$instance_l}{compatible}          = $compatible ;
        $dbinfo_arr{$instance_l}{last_archfile}      =
&findArchFile($instance_l,$last_arch_sequence);
        }
        print LOGFILE "\n compatible
$dbinfo_arr{$instance_l}{last_archfile} " ;
        if ( $dbinfo_arr{$instance_l}{log_archive_dir} ){
        print "\n  db_name                 =
$dbinfo_arr{$instance_l}{database}";
        print LOGFILE "\n  db_name                 =
$dbinfo_arr{$instance_l}{database}";
        print "\n  instance_number         = $instance_number";
        print LOGFILE "\n  instance_number         = $instance_number";
        print "\n  log_archive_dest        =
$dbinfo_arr{$instance_l}{log_archive_dest}" ;
        print LOGFILE "\n  log_archive_dest        =
$dbinfo_arr{$instance_l}{log_archive_dest}" ;
        print "\n  log_archive_dest_2      =
$dbinfo_arr{$instance_l}{log_archive_dest_2}"

if(defined($log_archive_dest_2)) ;
        print LOGFILE "\n  log_archive_dest_2      =
$dbinfo_arr{$instance_l}{log_archive_dest_2}"

if(defined($log_archive_dest_2)) ;
         print "\n  log_archive_dest_3      =
$dbinfo_arr{$instance_l}{log_archive_dest_3}"

if(defined($log_archive_dest_3));
        print LOGFILE "\n  log_archive_dest_3  =
$dbinfo_arr{$instance_l}{log_archive_dest_3}"

if(defined($log_archive_dest_3));
        print "\n  prod_last_archfile      =
$dbinfo_arr{$instance_l}{last_archfile}";
        print LOGFILE "\n  prod_last_archfile      =
$dbinfo_arr{$instance_l}{last_archfile}";
        print "\n  last_arch_sequence      =
$dbinfo_arr{$instance_l}{last_arch_sequence}";
        print LOGFILE "\n  last_arch_sequence      =
$dbinfo_arr{$instance_l}{last_arch_sequence}";
        print "\n  dg_dbname               =
$dbinfo_arr{$instance_l}{dg_dbname}"
                                                        if(defined($dg_dbname));
        print "\n  db_unique_name          =
$dbinfo_arr{$instance_l}{db_unique_name}"

if(defined($dbinfo_arr{$instance_l}{db_unique_name}));
        print LOGFILE "\n  dg_dbname               =
$dbinfo_arr{$instance_l}{dg_dbname}"
                                                        if(defined($dg_dbname));
        }
    }
}

#-----------------------------------------------------------------------------
# getCurrArchDestFromFile :
#  - Finds log_archive_dest from init ora if there exists a DR or DG
#  - this function is effective on DR hosts
#  - on certain cases when one of RAC node is down , this function is used
#    to get required init parameters from init file
#-----------------------------------------------------------------------------
sub getCurrArchDestFromFile()
{
        my $instance_l = shift;
        my $db_name_l;
        my $instance_number_l;
        my $log_archive_format_l;
        my $ifile;
        my $log_archive_dest_init_l;

        print "\n getCurrArchDestFromFile:$instance_l:";
        print LOGFILE "\n getCurrArchDestFromFile: $instance_l ";
#        $init_ora          = "$ENV{ORACLE_HOME}/dbs/init${instance_l}.ora";
#       $init_ora =  &checkSPFromInit(
"$ENV{ORACLE_HOME}/dbs/init${instance_l}.ora" ) ;
        $init_ora = &checkSPFile($instance_l) ;
        print LOGFILE "\n init or spfile in currearchdestfromfile  $init_ora" ;
        $log_archive_format = "";

        for ($retry=1;$retry <=10;$retry++){
                last if ( -f "$init_ora" );
                &mysleep(5);
        }
        open(INITORA, "cat $init_ora |strings |  ")
                || &showError("$pname:getCurrArchDestFromFile:Cannot
open init_ora",$instance_l,1);
        while (<INITORA>) {
                next if (/^#/ );
                chomp;
                s/['"]//g;
                $log_archive_dest_init= $_ if ( /log_archive_dest[_1]*\b/i );
                s/\s+//g;
                $ifile                = $_ if (/ifile/i);
                $db_name              = $_ if (/db_name/i);
                $compatible           = $_ if (/compatible/i);
                $log_archive_format   = $_ if (/log_archive_format/i) ;
                $instance_number      = $_ if (/instance_number/i);
        }
        close(INITORA);
        $ifile             = (split('=', $ifile))[1];
        if ( -f $ifile ) {
           open(IFILEORA,"cat $ifile |");
           while(<IFILEORA>){
                next if (/^#/);
                chomp;
                s/['"]//g;
                $log_archive_dest_init= $_ if ( /log_archive_dest[_1]*\b/i );
                s/\s+//g;
                $db_name              = $_ if (/db_name/i );
                $compatible           = $_ if (/compatible/i );
                $log_archive_format   = $_ if (/log_archive_format/i );
                $instance_number      = $_  if (/instance_number/i );

           }
           close(IFILEORA);
        }
        $db_name           = (split('=', $db_name  ))[1];
        $instance_number   = (split('=', $instance_number  ))[1]
if($instance_number  );
        $instance_number   = 1 if ( not $instance_number or (-f
"$thread_path/${db_name}_thread1.dat"));
        $compatible        = (split('=', $compatible  ))[1];
        $log_archive_format= (split('=', $log_archive_format  ))[1];
        $log_archive_dest  = (split('=', $log_archive_dest_init  ))[1];
        if ( lc($log_archive_dest_init  ) =~/log_archive_dest_1/ ) {
          $log_archive_dest  = (split('=', $log_archive_dest_init  ))[2];
          $log_archive_dest  = (split(' ', $log_archive_dest  ))[0];
           $dbinfo_arr{$instance_l}{isSetlog_archive_dest_1} = "YES" ;
        }
        $log_archive_dest   = $log_archive_dest."/"
                                if ( -d $log_archive_dest and
!($log_archive_dest =~/\/$/) );
        $log_archive_dest  = $log_archive_dest.$log_archive_format;
        $log_archive_dest  = (split('%',$log_archive_dest))[0];
        ($log_archive_dir)  = $log_archive_dest =~ /(.*)\/(\w*).arch/;

        if ( ! ($2 =~ m/${db_name}/) ){
                print "Warning:$instance_l: Invalid log_archive_dest format ";
                print LOGFILE "Warning:$instance_l: Invalid
log_archive_dest format ";
                $log_archive_dir ="";
                return(1);
        }
                my $inst_no =
$dbinfo_arr{$instance_l}{instance_number} ;chomp($inst_no) ;
          my  $last_arch_file = qx(ls -ltr
"$log_archive_dest$inst_no\* " |tail -1 ) ;
        &showError("$pname:$instance_l : getcurrarchfromfile : unable
to get last arch file",$instance_l,1)      if(
!defined($last_arch_file)) ;

        $last_arch_file =~ /(.*)\/(\w*).arch[_]*(\d)_(\d*)[_]*(.*).dbf/ ;
        $dbinfo_arr{$instance_l}{last_arch_sequence}  = $4 ;
        $dbinfo_arr{$instance_l}{compatible}        = $compatible ;
        $dbinfo_arr{$instance_l}{instance}          = $instance_l;
        $dbinfo_arr{$instance_l}{database}          = $db_name;
        $dbinfo_arr{$db_name}{instance}             = $instance_l;
        $dbinfo_arr{$instance_l}{log_archive_dest}  = $log_archive_dest;
        $dbinfo_arr{$instance_l}{log_archive_dir}   = $log_archive_dir;
        $dbinfo_arr{$instance_l}{log_archive_format}= $log_archive_format;
        $dbinfo_arr{$instance_l}{db_unique_name}       =
&getDBParm("db_unique_name",$instance_l)   if ( $compatible =~ /^10/
);
         $dbinfo_arr{$instance_l}{db_unique_name}      =
&getDBParmFile("db_unique_name",$instance_l)   if ( $compatible =~
/^10/  and ! defined( $dbinfo_arr{$instance_l}{db_unique_name})) ;

        print LOGFILE "\n getcurrarchdestfromfile db compatible
$dbinfo_arr{$instance_l}{compatible} " ;
        print "\n  log_archive_dest        =
$dbinfo_arr{$instance_l}{log_archive_dest}" ;
        print LOGFILE "\n getcurrarchdestfrom file  log_archive_dest
     = $dbinfo_arr{$instance_l}{log_archive_dest}" ;
        print "\n  log_archive_dir         =
$dbinfo_arr{$instance_l}{log_archive_dir} " ;
        print LOGFILE "\n getcurrarchdestfromfile  log_archive_dir
    = $dbinfo_arr{$instance_l}{log_archive_dir} " ;
        #print "\n  log_archive_format      =
$dbinfo_arr{$instance_l}{log_archive_format} " ;
        print LOGFILE "\n  log_archive_format      =
$dbinfo_arr{$instance_l}{log_archive_format} " ;
        &showError("$pname : $instance_l : getcurrachdestfromfile
unable to get db unique name",$instance_l, 1)         if (! defined
($dbinfo_arr{$instance_l}{db_unique_name})) ;
        print LOGFILE "\n db unique name" ,
$dbinfo_arr{$instance_l}{db_unique_name} ;
}

#-----------------------------------------------------------------------------
# getUsedSpace :
#       gets %usgae using commands 'dbf' or 'df'
#       'df' returns either 5 or 6 columns on some os and hence doing a
#       left shift if first column is null
#-----------------------------------------------------------------------------
sub getUsedSpace
{
    local($file_system) = shift;

    open(DF, "$DF $file_system $dfopt |") ||
                &showError("$pname:getUsedSpace:Unable to do $DF
$file_system $!",1);
    while (<DF>) {
        ($total = <DF>) || &showError("$pname:getUsedSpace:can't read
total from $DF $file_system $!",1);
        @data = split(' ',$total);
        shift(@data) if( $#data == 5);

        $file_system = $data[4];
        $usage_p     = $data[3];
        $free_blocks = $data[2];
        $used_blocks = $data[1];
        $total_blocks= $data[0];

        #print "\n data|0=$total_blocks|1=$used_blocks|2=$free_blocks|";
        #print "3=$usage_p|4=$file_system == \n ";
    }
    $usage_pct = (split('%',$usage_p))[0] ;
    return ( int ( $usage_pct ) );
}

#-----------------------------------------------------------------------------
# purgeArchive :
#  - purge algorithm checks
#     %usage,
#     if archive log is applied to DR and
#     if exists in tape ( default 1d, assuming that files older than 1d exists
#     in tape.
#  - recent_files is used to track if recent logs are purged and to send
#  - expects format of archivelog *SID*arch*dbf* , it also purges *.dbf files
#    in case of DG
#  - sends email if recent logs ( ARCHIVE_RETAIN_TIME) are removed sothat dba
#    knows how recent the logs are removed
#  - sends alert if %usage is > upper_threshold even after purging
#-----------------------------------------------------------------------------
sub purgeArchive()
{
  print "\npurgeArchive:";
  print LOGFILE "\npurgeArchive:";
  my $logdate_l=qx(date +'[%T]');chomp($logdate_l);
  print $logdate_l; print LOGFILE $logdate_l;
  my $status = 'NO';

  undef %recentFiles;
  foreach $mfs ( keys %mountfs){
    $archive_file_sys=$mountfs{$mfs};
    next if ( ! defined($archive_file_sys ) );
    $archive_file_dir=(split(' ',$archive_file_sys))[0];
    $archive_file_dir =~ s/\*//;
    &getParameters($mfs);

    print "\n mount filesystem         = $mfs";
    print LOGFILE "\n mount filesystem         = $mfs";
    print "\n archive_file_sys         =";
    print LOGFILE "\n archive_file_sys         =";
    my @ptmp=split(' ',$archive_file_sys);
    # this piece of junk is very much required for easy
    # reading on the output .
    my $pflag = 1;
    foreach (@ptmp) {
      if ( $pflag == 1 ){
          print " $_" ;
          print LOGFILE " $_" ;
          $pflag =0;
          next;
      }
      print "\n                            $_";
      print LOGFILE "\n                            $_";
   }

    $ARCHIVE_RETAIN_SEC = &convertTime($archive_retain_time);
    print "\n  Parameters              = $mfs:$pct_lower_limit:";
    print LOGFILE "\n  Parameters              = $mfs:$pct_lower_limit:";
    print "$pct_upper_limit:$archive_retain_time:$mailto:$pageto";
    print LOGFILE "$pct_upper_limit:$archive_retain_time:$mailto:$pageto";
    $pct_used = &getUsedSpace($archive_file_dir);
    print "\n  Before purge:pct_used   = $pct_used% ";
    print LOGFILE "\n  Before purge:pct_used   = $pct_used% ";
    print "\n";
    print LOGFILE "\n percent used and limit $pct_used    $pct_upper_limit ";

    if ($pct_used >= $pct_upper_limit - 2)
    {
      open(PURGEFILES, "find ${archive_file_sys} -follow -name \"*dbf*\" |")
                        || &showError("$pname:Cannot open archive files. $!");;
      chomp(@pfiles=<PURGEFILES>);
      @spfiles=(map{$_->[0]} sort{$a->[1]<=>$b->[1]} map{[$_,(stat
$_)[9]]} @pfiles);
#       print LOGFILE "\n @spfiles" ;
        print LOGFILE "\n archformat  $archformat" ;
      foreach (@spfiles) {
                 chomp($archfile=$_); print LOGFILE "\n $archfile " ;
        # ($db_log_archive_dir,$dbname)
         $archfile =~ /(.*)\/(\w*).arch[_]*(\d)_(\d*)[_]*(.*).dbf(.*)/ ;
                my $db_log_archive_dir = $1 ; my $dbname = $2 ;
         print LOGFILE "\n $db_log_archive_dir $dbname" ;
         my $instance_l = $dbinfo_arr{$dbname}{instance};
         $archsuffix= ".gz";
         #$archsuffix= "" if ($dbinfo_arr{$instance_l}{isDataguard} eq "YES" );
         &getDbParameters($instance_l);
         $archsuffix= "(\.\*)" if ( $zipmode eq "DISABLE" );
#        next if (
(/(.*)\/(\w*).arch[_]*(\d)_(\d*)[_]*(.*).dbf${archsuffix}/) );
         next if ( $zipmode eq "DISABLE") ;
         &Stat("${archfile}");
                print LOGFILE "\n ${archfile} check tape exists " ;
                print LOGFILE &checkTapeExists("${archfile}") ;
                print LOGFILE "\n check DGapplied " ;
                print LOGFILE  &checkDGApplied("${archfile}") ;
         if ( (&checkDGApplied("${archfile}") eq "YES")  &&
             ( &checkTapeExists("${archfile}") eq "YES") &&
             ( &isOpen("${archfile}") =~ /no/)             )
         {     print LOGFILE "\n in the if block to purge" ;
               if ($st_mtime >= (time - $ARCHIVE_RETAIN_SEC)){
                        $recentFiles{$dbname}=$db_log_archive_dir;
                }
                printf " (%10d)",$threadno if ( $threadno != $DEFAULT_THREAD) ;
                print LOGFILE "  ($threadno)" if ( $threadno !=
$DEFAULT_THREAD) ;
                print " unlink:${archfile}:$pct_used %:";
                print LOGFILE "  unlink:${archfile}:$pct_used %:";
                print "\n";
                print LOGFILE "\n";
                unlink("${archfile}")
                  || print "$pname:Can't Unlink $_: $!" if (-e ${archfile});
                $dbinfo_arr{$instance_l}{purge_cnt}++;
                alarm($TIMEOUT);
                #print ".";
         }
         else {
                print "";
                print LOGFILE "\n in the else block ";
                #print "\n No delete: ${archfile}";
         }

         $pct_used = &getUsedSpace($archive_file_dir);
         last if ($pct_used <= $pct_lower_limit);
        }
        close(PURGEFILES);
  }

  #$pct_used=100; #TEST-simulate sad
  print "  After  purge:pct_used   = $pct_used% ";
  print LOGFILE "  After  purge:pct_used   = $pct_used% ";
  if ( $pct_used > $pct_upper_limit ){
     $dbname="";
     foreach $db ( keys %dbinfo_arr){
        if ( "$dbinfo_arr{$db}{log_archive_dir}" eq "$archive_file_dir" ){
                $instance_l=$db;
                last;
        }
      }
      &getDbParameters($instance_l);
      if( &isSwitch($instance_l) eq "YES" and
          defined(lc($opt_O)) ne "nosad" ) {
                $status=&switchArchDest($instance_l);
                if ( $status eq "NO" ) {
                  print "\n  ERROR! Unable to do Switch Archive ";
                  print LOGFILE "\n  ERROR! Unable to do Switch Archive ";
                  &showError("$pname:Unable to do Switch Archive",$instance_l);
               }
      }
      else{
        print "\n  Sending page $pageto :$local_host:$mfs:%usage ";
        print "is greater than $pct_upper_limit% after purge. ";
        print LOGFILE "\n  Sending page $pageto :$local_host:$mfs:%usage ";
        print LOGFILE "is greater than $pct_upper_limit% after purge. ";
        &showError("$mfs:%usage is greater than $pct_upper_limit%
after purge.",$instance_l);
     }
  }
  }

  foreach $db ( keys %dbinfo_arr ){
    if ( $dbinfo_arr{$db}{connected} eq "Y" ) {
       printf "\n No. of logs purged(%-8s) = %2d",$db,
$dbinfo_arr{$db}{purge_cnt};
       printf LOGFILE "\n No. of logs purged(%-8s) = %2d",$db,
$dbinfo_arr{$db}{purge_cnt};
    }
  }

  foreach $db ( keys %recentFiles ){
    if( $isdrhost_f eq "NO" ) {
        &getDbParameters($instance_l);
        &showError("Recent Archive logs removed.",$recentFiles{$db},0,'N');
    }
  }
  print "\n";
  print LOGFILE "\n entering purge next archive ";
  &purgeNextArchive() ;
}

#-----------------------------------------------------------------------------
# getDRInfo :
#  - Finds DR host based on the below sync arch file
#         /usr/tools/oracle/sync_arch/adm/sync_arch_CAPPROD.cfg
#        or from standby_archive_dest in case of DG
#  - Gets the lastest archive log sequence applied to DR  ,
#    location of thread file  on a DR host
#         /usr/tools/oracle/recovery/thread/CAPPROD_thread1.dat
#  - set thread=DFAULT_THREAD if no DR
#  - set thread=-1 in case  unable to read thread file
#-----------------------------------------------------------------------------
sub getDRInfo()
{
  my $instance_l        = shift;
  my $dbname            = $dbinfo_arr{$instance_l}{database};
  my $nodrhost_alert ;
  my $dr_log_archive_dir,$dr_log_archive_dest;
  $ENV{sid}             = $instance_l ;
  $sync_arch_file       = "sync_arch_${dbname}.cfg";
  $sync_arch_file       = "sync_arch_${dbname}_thread${instance_number}.cfg";
  $sync_arch_file       = "sync_arch_${dbname}.cfg"
                           if(!-f "$sync_arch_path/$sync_arch_file");

  for ($racnode=2;$racnode <=5;$racnode++){
     $thread_file          = "${dbname}_thread$racnode.dat";
     #precheck for dir uto/recovery/thread
     &chkDatabaseRole("${thread_path}/${thread_file}");

     if ( -f "${thread_path}/${thread_file}" ){
      #print "\ngetDRInfo: $instance_l:";
      $drthread{$instance_l.$racnode} = qx(cat ${thread_path}/${thread_file});
      chomp($drthread{$instance_l.$racnode});
      $drthread{$instance_l.$racnode}  = int($drthread{$instance_l.$racnode});
      $isdrhost_f                = "YES";
      $drthread{$instance_l.$racnode} = $DEFAULT_THREAD
                                if( !$drthread{$instance_l.$racnode});
     }
  }

   $thread_file          = "${dbname}_thread${instance_number}.dat";
   #precheck for dir uto/recovery/thread
   &chkDatabaseRole("${thread_path}/${thread_file}");

   if ( -f "${thread_path}/${thread_file}" ){
       #print "\ngetDRInfo: $instance_l:";
       $drthread{$instance_l} = qx(cat ${thread_path}/${thread_file});
       chomp($drthread{$instance_l});
       $drthread{$instance_l}       = int($drthread{$instance_l});
       $isdrhost_f             = "YES";
       $drthread{$instance_l}  = $DEFAULT_THREAD if( !$drthread{$instance_l});
       return;
   }
   if( $dbinfo_arr{$instance_l}{isDataguard} eq "YES")
   {
      print "\n getDRInfo:$instance_l:DG=Y:";
      print LOGFILE "\n getDRInfo:$instance_l:DG=Y:";
      $tnsping_data              = qx($ENV{'ORACLE_HOME'}/bin/tnsping
$dg_dbname);
      $tnsping_data              =~s/\s+//g ;
      $remote_host               =
(split('\)',(split('host=',lc($tnsping_data) ))[1]))[0];
      $dr_log_archive_dest       =
$dbinfo_arr{$instance_l}{standby_archive_dest};
      $drexists_f{$instance_l}   = "YES";
    }
    else{
      if(-f "$sync_arch_path/$sync_arch_file") {
         print "\n getDRInfo:$instance_l:";
         print LOGFILE "\n getDRInfo:$instance_l:";
         open(DRHOST,"$sync_arch_path/$sync_arch_file")
                    || &showError("$pname:Can't Open
$sync_arch_path/$sync_arch_file ",$instance_l);
         while(<DRHOST>){
            if ( /^remote_sys/ ) {
                chomp($remote_host=(split('='))[1]) ;
                $drexists_f{$instance_l} = "YES";
            }
            if ( /^remote_arch_dir/ ) {
                chomp($dr_log_archive_dir  = (split('='))[1]);
                chomp($dr_log_archive_dir  = qx{echo ${dr_log_archive_dir}}) ;
                $dr_log_archive_dest       =
"${dr_log_archive_dir}.${dbname}\.arch";
                #print "\n  dr_log_archive_dest     = $dr_log_archive_dest";
            }

      ####        if ( /^remote_dg1/ ) {
chomp($remote_dg[1]=(split('=')[1]); $remote_dglist[1]="YES" ; }
      ####                if ( /^remote_dg2/ ) {
chomp($remote_dg[2]=(split('=')[1]);  $remote_dglist[2]="YES" ;}
####      if ( /^remote_dg3/ ){ chomp($remote_dg[3]=(split('=')[1]);
$remote_dglist[3]="YES" ;}
####              if ( /^remote_dg4/ ) {
chomp($remote_dg[4]=(split('=')[1]); $remote_dglist[4]="YES" ; }
####                            if ( /^remote_dg5/
){chomp($remote_dg[5]=(split('=')[1]);  $remote_dglist[5]="YES";}
####               if ( /^remote_dg6/
){chomp($remote_dg[6]=(split('=')[1]);  $remote_dglist[6]="YES";}
####               if ( /^remote_dg7/
){chomp($remote_dg[7]=(split('=')[1]);  $remote_dglist[7]="YES" ;}
        }
         close(DRHOST);
         }
      }
      if (( -f "$sync_arch_path/$sync_arch_file")
||($dbinfo_arr{$instance_l}{isDataguard} eq "YES") ) {
           print "\n  dr_host                 = $remote_host";
           print LOGFILE "\n  dr_host                 = $remote_host";
           print "\n  dr_log_archive_dest     = $dr_log_archive_dest";
           print LOGFILE "\n  dr_log_archive_dest     = $dr_log_archive_dest";

           #alert if remote host doesn't exists
           if(not $remote_host ){
              print "\n  Error!! Unable to get DR hostname";
              print LOGFILE "\n  Error!! Unable to get DR hostname";
              &showError("$pname: Unable to get DR host",$instance_l);
           }
#############CHECKING RAC STANDBY INSTANCES info from CFG file.
####            my $cnt1 ;
####            for ( $cnt1=1;$cnt1<=7;$cnt1++)
####            {  if ( $remote_dglist[$cnt1]  eq "YES" and not
$remote_dg[$cnt1] )
####                    { print "\n  Error!! Unable to get DR rac
standby instance $cnt1  hostname";
####                          print LOGFILE "\n  Error!! Unable to get
DR rac standby instance $cnt1  hostname";
####                    }
###             }
### identify the rac standby recovery instance.
####            $rac_Standby_rec_node = &getRecoveryStandbynode();


           if ( &checkNodrhost($instance_l) eq 'N'){
#          $ssh_status=0;
           for ($retry=1;$retry <=10;$retry++){
             chomp($drthread{$instance_l} = qx{$SSH -qn ${remote_host}
$sshopt "cat ${thread_path}/${thread_file}"});
             last if ( $drthread{$instance_l} );
             &mysleep(6);
           }
           }

#### get the thread info from standby recovery instance
####            if (defined($rac_standby_rec_node)
####            { my $tempstr;
####            for ($retry=1; $retry <=10 ;$retry ++ )
###             { chomp( $tempstr =qx{$SSH -qn ${rac_Standby_rec_node}
 $sshopt "cat ${thread_path}/${thread_file}"});
###
###               @tempstr1=(split (/\n/)) ;
###             if ( defined($tempstr) )
###             {
###             while $i ( 0 .. $#tempstr1)
###             {
$dgthread{$instance_l}{int(chomp(split(/:/,$tempstr1[$i])[0]))}=
int(chomp(split(/:/,$tempstr1[$i])[1]));}
###             }
###             last if ( $tempstr) ;
###
###             &mysleep(6) ;
###             }
###             }

          #$drthread{$instance_l}=""; #TEST-simulate drhost is down
#         $ssh_status=1 if ( not  $drthread{$instance_l} ) ;
#         system("rm /usr/tools/oracle/$instance_l.nodrhost.* 2>/dev/null" )
#                                               if ($ssh_status == 0);

           #alert if thread is not found

###             if ( $rac_standby_rec_node and not $dgthread {$instance_l})
###                     {  &showError("$pname: Unable to get RAC
STANDBY RECOVERY THREAD Info" $instance_l,0,$nodghost_alert)
###                                     if ( &checkNodghost(
$instance_l) eq 'N' ) ;
###                       }

           if ( $remote_host and not $drthread{$instance_l} ){
#                $nodrhost_alert = &checkNodrhost($instance_l);
                &showError("$pname: Unable to get DR thread
info",$instance_l,0,$nodrhost_alert,$nodrhost_alert)
                                if ( &checkNodrhost($instance_l) eq 'N' );
           }
           $drthread{$instance_l}       = -1  if( !$drthread{$instance_l});
           $drthread{$instance_l}       = int($drthread{$instance_l});
           print "\n  dr_thread               = $drthread{$instance_l}";
           print LOGFILE "\n  dr_thread               = $drthread{$instance_l}";

           # trying to get last arch sequence shipped to DR site
           my $drlogpath="${dr_log_archive_dest}${instance_number}";
        if ( &checkNodrhost($instance_l) eq 'N'){
           for ($retry=1;$retry <=10;$retry++){
             ($dr_log_archive_dir)  =  $dr_log_archive_dest  =~
/(.*)\/(\w*).arch/ ;
             @dr_last_archfile_a = qx($SSH -qn ${remote_host} $sshopt
"ls -1tr ${drlogpath}\* | tail -50" 2>/dev/null);
             @dr_last_archfile_a = qx($SSH -qn ${remote_host} $sshopt
"find $dr_log_archive_dir/ -name
'${dbname}\.arch$instance_number\*'|xargs ls -1tr|tail -50"
2>/dev/null) if (! @dr_last_archfile_a and $dr_log_archive_dir);

             last if ( @dr_last_archfile_a );
             &mysleep(6);
           }

           # sorting by sequence is required for possibility of
zip/unzip happening on DR/DG host
           # at the time of polling
           $dr_last_archfile=(map{$_->[0]} sort{$b->[1]<=>$a->[1]}
map{[$_,/_(\d+)[\._]/]} @dr_last_archfile_a)[0];
           chomp($dr_last_archfile);

           if (!$dr_last_archfile) {
               print "\n       $SSH -qn ${remote_host} ls -1tr
${dr_log_archive_dest}${instance_number}\*|tail -1";
               print LOGFILE "\n       $SSH -qn ${remote_host} ls -1tr
${dr_log_archive_dest}${instance_number}\*|tail -1";
               $nodrhost_alert = &checkNodrhost($instance_l);
               print "\n  nodrhost_alert = $nodrhost_alert ";
               &showError("$pname: Unable to get
archinfo($dr_last_archfile) from DR host ${remote_host}
",$instance_l,0,$nodrhost_alert,$nodrhost_alert);
           }
         }
           $dr_last_archfile                               =~
/${archformat}(.*)/ ;
           $dr_last_arch_sequence                          = int(${4});
           $dbinfo_arr{$instance_l}{dr_last_arch_sequence} =
$dr_last_arch_sequence;
           print "\n  dr_last_arch_sequence   = $dr_last_arch_sequence ";
           print LOGFILE "\n  dr_last_arch_sequence   =
$dr_last_arch_sequence ";
      }
      else{
          print "\n  DR_exists?              = None"
                        if( $dbinfo_arr{$instance_l}{connected} eq "Y");
      }
      $drthread{$instance_l} = $DEFAULT_THREAD if( !$drthread{$instance_l});
      $drinfo_arr{$instance_l}{dr_log_archive_dest} = $dr_log_archive_dest;
      if (&checkNodrhost($instance_l) eq 'Y' ){
        print "\n  Ignore DR pages due to nodrhost flag set at $nodrhost_f \n";
        print LOGFILE "\n  Ignore DR pages due to nodrhost flag set at
$nodrhost_f \n";
      }
}
sub getDGInfo()
{
        my $instance_l        = shift; chomp($instance_l) ;
        my $dbname            = $dbinfo_arr{$instance_l}{database};
        my $nodrhost_alert ;my $instno ;
        my $dg_log_archive_dir,$dg_log_archive_dest;
        $ENV{sid}             = $instance_l ;
        $sync_arch_file       = "sync_arch_${dbname}.cfg";
      #  $sync_arch_file       =
"sync_arch_${dbname}_thread${instance_number}.cfg";
        print LOGFILE "database $dbname instance $instance_l" ;
        print LOGFILE "the sync file is $sync_arch_path/$sync_arch_file" ;
   #     $sync_arch_file       = "sync_arch_${dbname}.cfg"
        if ($instance_l =~ /(\w+)(\d)/ ) {      $instno = $2 ;}
        $thread_file = "mvdc_${dbname}_thread${instno}.dat" if (
defined($instno) and defined($dbname)) ;
        $thread_file = "mvdc_${instance_l}.dat" if ( ! defined($instno) ) ;
        $sync_arch_file  = "sync_arch_${dbname}_thread${instno}.cfg"
if ( defined($instno) and defined($dbname)) ;

        &showError("$pname:getDGInfo: the thread file is not availabe
for this standby database , hence exiting the process",$instance_l,1)
if ( ! (-f "$thread_path/$thread_file")  and  $DB_role eq "STANDBY" )
;

        &showError("$pname::getDGInfo: the sync file is not available
for this primary database , hence exiting the process", $instance_l,1)
if ( ! (-f "$sync_arch_path/$sync_arch_file") and $DB_role eq
"PRIMARY" ) ;

           #                if(!-f "$sync_arch_path/$sync_arch_file");
        my $tmpthread ;my $tmplogseq ;
                #       print LOGFILE "\n  thread file $thread_file sync

       if ( -f  "$thread_path/$thread_file"  and
&chkDatabaseRoleReturn($instance_l) eq "STANDBY" )
                {
                         chomp( $tempstr =qx(cat
${thread_path}/${thread_file})); print LOGFILE "\n $tempstr" ;
                         @tempstr1=split (/\n/, $tempstr ) ;my $i=0;
                         while ($tempstr1[$i])
                                {
                                        $tmpthread
=(split(':',$tempstr1[$i]))[0] ;
                                        $tmplogseq =
(split(':',$tempstr1[$i]))[1] ;

$dgthread{$instance_l}{$tmpthread}= int($tmplogseq);print LOGFILE "\n"
;
                                        print LOGFILE
$dgthread{$instance_l}{$tmpthread} ;$i++ ; last if (not
defined($tempstr1[$i])) ;

                                }# WHILE
                         if( &checkRecoveryInst($instance_l)  eq
"FALSE" ) { &showError("$pname : getDGInfo not an recovery instance so
exiting ", $instance_l,1)  ; }
                        #  my $standby_arch_dest =
&getDBParm("standby_archive_dest", $instance_l);

chomp($dg_log_arch_dir=&getDBParm("standby_archive_dest",
$instance_l));

$dbinfo_arr{$instance_l}{isSetstandby_archive_dest}= "YES" if
(defined($dg_log_arch_dir)) ;

$dbinfo_arr{$instance_l}{standby_archive_dest} = $dg_log_arch_dir if
(defined ($dg_log_arch_dir)) ;
                        print LOGFILE
$dbinfo_arr{$instance_l}{standby_archive_dest} ;
                        $dg_log_arch_dir_1=
&getDBParm("log_archive_dest_1", $instance_1); # if (!
defined($dg_log_arch_dir));

$dbinfo_arr{$instance_l}{isSetlog_archive_dest_1} = "YES" if (defined
($dg_log_arch_dir_1) ) ;

#        and ! (defined ( $dbinfo_arr{$instance_l}{standby_archive_dest}))) ;
                         $dbinfo_arr{$instance_l}{log_archive_dest_1}
= $dg_log_arch_dir_1  if (defined ($dg_log_arch_dir_1)) ;
#        and ! (defined ( $dbinfo_arr{$instance_l}{standby_archive_dest}))) ;

                        print LOGFILE " \n is set log archive dest 1",
$dbinfo_arr{$instance_l}{isSetlog_archive_dest_1} ;

                        if (
$dbinfo_arr{$instance_l}{isSetlog_archive_dest_1} eq "YES" and
$dbinfo_arr{$instance_l}{standby_archive_dest} eq "YES" )
                        {               my $flag_standbydest= "TRUE" ;
my $flag_logdest1= "TRUE" ;
                                $dg_log_arch_dir =~ s/'//g ;
$dg_log_arch_dir =~ s/\s//g ;
                                 $dg_log_arch_dir_1 =~  s/'//g ;
$dg_log_arch_dir_1  =~ s/\s//g  ;
                                 if ( ! ($dg_log_arch_dir =~
/(.*)\/(.*).arch(.*)/ )) { print LOGFILE "\n standbyarchdest is not in
correct format $dg_log_arch_dir" ;  $flag_standbydest = "FALSE" ; }
                                if ( ! ($dg_log_arch_dir_1  =~
/(.*)\/(.*).arch(.*)/ ))  { print LOGFILE "\n logarchivedest is in
correct format $dg_log_arch_dir_1" ;   $flag_logdest1 = "FALSE" ;}
                                if ( $flag_standbydest  eq "TRUE" and
$flag_logdest1= "TRUE" )
                                 {   print LOGFILE "\n both standby
and logdest1 are same " ;}
                                if ( $flag_standbydest  eq "FALSE" and
$flag_logdest1 eq "TRUE" )
                                {       $dg_log_arch_dir =
$dg_log_arch_dir_1 ; }
                                if ($flag_standbydest  eq "FALSE" and
$flag_logdest1 eq "FALSE" )
                                { &showError("$pname : $instance_1
both the standby and log arch dest are not in format ",$instance_l,1)
; }

                        }
                                print LOGFILE "\n in format archive
destination $dg_log_arch_dir " ;
#                       $dg_log_arch_dir =~ /(.*)\/(.*).arch(.*)/ ;
                        chomp($dg_log_arch_dir1 = ${1}) ;
                        my @threadinfo = &getStandbyThreadInfo($instance_l);
                        print LOGFILE "\n thread info" ;
                        print LOGFILE $#threadinfo ;
                        $dginfo_arr{$instance_l}{dg_log_archive_dest}
= $dg_log_arch_dir;
                        print LOGFILE
$dginfo_arr{$instance_l}{dg_log_archive_dest} ;

$dginfo_arr{$instance_l}{dg_last_arch_sequence} =
$dgthread{$instance_l}{$inst_no}  ;


                }

                if ( -f  "$sync_arch_path/$sync_arch_file"  and
&chkDatabaseRoleReturn($instance_l) eq "PRIMARY" )
                {
                                         print LOGFILE "\n sync file
in PRIMARY  $sync_arch_path/$sync_arch_file " ;
                                        print "\n getDGInfo:$instance_l:";
                                        print LOGFILE "\n
getDGInfo:$instance_l:";

open(DRHOST,"$sync_arch_path/$sync_arch_file")
                                                ||
&showError("$pname:Can't Open $sync_arch_path/$sync_arch_file
",$instance_l);
                                                while(<DRHOST>){
                                                if ( /^remote_dg1/ ) {
chomp($remote_dg[1]=(split('='))[1]); $remote_dglist[1]="YES" ; }
                                                  if ( /^remote_dg2/ )
{ chomp($remote_dg[2]=(split('='))[1]);  $remote_dglist[2]="YES" ;}
                                                if ( /^remote_dg3/ ){
chomp($remote_dg[3]=(split('='))[1]);  $remote_dglist[3]="YES" ;}
                                                 if ( /^remote_dg4/ )
{ chomp($remote_dg[4]=(split('='))[1]); $remote_dglist[4]="YES" ; }
                                                if ( /^remote_dg5/
){chomp($remote_dg[5]=(split('='))[1]);  $remote_dglist[5]="YES";}
                                                if ( /^remote_dg6/
){chomp($remote_dg[6]=(split('='))[1]);  $remote_dglist[6]="YES";}
                                                if ( /^remote_dg7/
){chomp($remote_dg[7]=(split('='))[1]);  $remote_dglist[7]="YES" ;}
                                                if ( /^remote_sys/) {
chomp($remote_host=(split('='))[1]); }                    }
                                                close(DRHOST);


                                                 $remote_host=""  if
(! defined($remote_host)) ;
#############CHECKING RAC STANDBY INSTANCES info from CFG file.
                                                my $cnt1 ;
                                                for ( $cnt1=1;$cnt1<=7;$cnt1++)
                                                {       if (
$remote_dglist[$cnt1]  eq "YES" and not $remote_dg[$cnt1] )
                                                                {
print "\n  Error!! Unable to get DR rac standby instance $cnt1
hostname";
                                                                print
LOGFILE "\n  Error!! Unable to get DR rac standby instance $cnt1
hostname";
                                                                }
                                                        else   {
                                                                 print
LOGFILE "\n $remote_dglist[$cnt1]  $remote_dg[$cnt1] " ;
                                                                }
                                                }
### identify the rac standby recovery instance.
                                                my (
$rac_standby_rec_node,$rec_inst,$rec_instno) =
&getRecoveryStandbynode();
                                                print LOGFILE
"recovernodeinfo $rac_standby_rec_node , $rec_inst , $rec_instno" ;
  $dgexists_f{$instance_l} = "YES" ;
                                                if
(defined($rac_standby_rec_node))
                                                        { my @tempstr;
my $inst_no ;if (defined ($rec_instno) and ($rec_inst =~
/(\w*)(\d)/)){my $rec_db = $1 ;
                                                        $thread_file =
"mvdc_${rec_db}_thread${rec_instno}.dat" ;
                                                        }
                                                else  { $thread_file =
"mvdc_${rec_inst}.dat" ; }
                                                print LOGFILE "\n
$thread_path/$thread_file" ;
                                                        my $thread_f =
"$thread_path/$thread_file" ;
                                                        my $cmd_l =
"$SSH ${rac_standby_rec_node} hostname " ;
                                                print LOGFILE "\n $cmd_l " ;
                                                @tempstr = `$cmd_l` ;
                                                   print LOGFILE "\n @tempstr" ;
                        #               if($rac_standby_rec_node ==
$standby_host[0]) { $inst_no = $standby_instno[0] ;}
                        #                 if ($rac_standby_rec_node ==
$standby_host[1]) {$inst_no = $standby_instno[1];}
                                                for ($retry=1; $retry
<=10 ;$retry++ )
                                                        {  @tempstr =
qx($SSH -qn ${rac_standby_rec_node}  $sshopt cat $thread_f) ;
                                                        print LOGFILE
"\n @tempstr" ;

@tempstr1=(split (/\n/),@tempstr) ;my $cnt5=0 ;
                                                        if ( defined(@tempstr) )
                                                                {

 for $cnt5 ( 0 .. $#tempstr1)

         {  $tmpthread = (split(':',$tempstr1[$cnt5]))[0] ;

                 $tmplogseq =(split(':',$tempstr1[$cnt5]))[1];

                 chomp($tmpthread) ; chomp($tmplogseq) ;

                 #print LOGFILE "\n  $tmpthread   $tmplogseq" ;

                 $dgthread{$instance_l}{int($tmpthread)}=
int($tmplogseq);print LOGFILE "\n thread info as recorded $tmpthread
$dgthread{$instance_l}{$tmpthread} " ;
 $cnt5++ ;

         }
                                                                }
                                                last if ( defined( @tempstr)) ;
                                               &mysleep(6) ;
                                                        }
#                  } # end of primary dg processing



                                                if (
$rac_standby_rec_node and not $dgthread {$instance_l})
                                                                {
&showError("$pname: Unable to get RAC STANDBY RECOVERY THREAD Info"
,$instance_l,1,$nodghost_alert) if ( &checkNodghost( $instance_l) eq
'N' ) ;
                                                                }

$dbinfo_arr{$instance_l}{rec_node} = $rac_standby_rec_node ;

$dbinfo_arr{$instance_l}{rec_inst} = $rec_inst ;

$dbinfo_arr{$instance_l}{rec_instno} = $rec_instno ;
                                                print LOGFILE " \n
looking for log arch dest" ;
#                                               my $standby_ohome =
qx($SSH -qn $rac_standby_rec_node $sshopt "cat /var/opt/oracle/oratab
|grep $rec_inst" ) ;
#### write the code for spfile consideration
#                                               $standby_ohome =
(split (':', $standby_ohome ))[1] ;
#                                               &showError("$pname :
getDGInfo unable to get standby home from /etc/oratab",$instance_l) if
(! defined($standby_ohome)) ;
#                                               print LOGFILE "\n
standby home $standby_ohome" ;
#                                               my $standby_init ;
#                                               my $standby_initfile =
qx($SSH  -qn $rac_standby_rec_node $sshopt "cat
${standby_ohome}/dbs/init${rec_inst}.ora | grep spfile ") ;
#                                               if (
defined($standby_initfile) )
#                                                       {       if
($standby_initfile = /(.*)spfile(\s+)=(.*)/)
#
 {  $standby_init = $3 ; }
#                                                       }
#                                               $standby_init =
"${standby_ohome}/dbs/init${rec_inst}.ora"  if ( !
defined($standby_init) ) ;
                                        #       my $parmcount =
#                                               $dg_log_arch_dir=  qx(
$SSH  -qn $rac_standby_rec_node $sshopt "cat $standby_init | strings |
grep standby_archive_dest " );
#                                               $dg_log_arch_dir =
(split('=', $dg_log_arch_dir ))[1] ;
                                                $dg_log_arch_dir =
&getStandbyDBParmFile($rac_standby_rec_node, $rec_inst,
"standby_archive_dest" ) ;
                                                &showError("$pname :
getDGInfo unable to get standby archive dest from recovery standby
node ", $instance_l) if (! defined($dg_log_arch_dir)) ;
                                                print LOGFILE "\n
standby archive dest from standby $dg_log_arch_dir" ;
#
chomp($dg_log_arch_dir=&getStandbyArchdest($rac_standby_rec_node,$rec_instno
));
                                                  $dg_log_arch_dir =~
s/['"]//g ;
                                                  $dg_log_arch_dir =~
/(.*)\/(.*).arch(.*)/ ;

chomp($dg_log_arch_dir1 = ${1}) ;

                                                print  LOGFILE "\n dg
directory $dg_log_arch_dir1" ;
                                                my $logcnt1 = qx($SSH
-qn $rac_standby_rec_node $sshopt "ls -ltr
${dg_log_arch_dir1}/${dbname}\.arch\* |wc -l" ) ;
                       print LOGFILE "\n log coutn from standby arch
dest $logcnt1" ;
                                                &showError("$pname :
getDGInfo log count on standby archive dest on standy is zero
",$instance_l) if ( $logcnt1 <= 0 ) ;

##### write additional code to consider log_arch_dest_1 in case
standby arch dest is not set "
                                                $cnt2=1;my
$dg_last_archfile_list ;
                                                  my $cnt3=0 ;
                                                 while (defined
($dgthread{$instance_l}{$cnt2 }))
                                                {


                                                        for
($retry=1;$retry <= 10; $retry++)
                                                        {



$dg_last_archfile_list = qx($SSH -qn ${rac_standby_rec_node} $sshopt
"ls -1tr ${dg_log_arch_dir1}/${dbname}\.arch${cnt2}\* | tail -1"
2>/dev/null);
                                                                print
LOGFILE "\n dg last arch file $dg_last_archfile_list" ;

$dg_last_archfile_list = qx($SSH -qn ${rac_standby_rec_node} $sshopt
"find $dg_log_arch_dir1/ -name '${dbname}\.arch${cnt2}\*'|xargs ls
-1tr|tail -1" 2>/dev/null) if ( ! defined ($dg_last_archfile_list)) ;

 last if (defined( $dg_last_archfile_list) );
                                                         }




 print LOGFILE "\n retries $retry" ;     #print LOGFILE "\n  dg last
arch file list @dg_last_archfile_list " ;

 $cnt3 = 0 ;chomp ($dg_last_archfile_list ) ;

 if(!($dg_last_archfile_list =~
/(.*)\/(\w*).arch[_]*(\d)_(\d*)[_]*(.*).dbf/)){&showError("$pname :
getDGInfo the dg last archfile is not in arch format
$dg_last_archfile_list" ,$instance_l)  ;}

 $dg_last_archfile_list =~
/(.*)\/(\w*).arch[_]*(\d)_(\d*)[_]*(.*).dbf/ ;

 $dg_last_arch_sequence{$3} = $4;

 print LOGFILE "\n last arch sequence " ;print LOGFILE
$dg_last_arch_sequence{$cnt2}  ;
                                                                        $cnt2++;
                                                } #$cnt2-- ;print
LOGFILE "\n dglogarch $dg_last_arch_sequence{$cnt2}" ;
                                                my $instance_no =
$dbinfo_arr{$instance_l}{instance_number} ;
                                                $dginfo_arr
{$instance_l}{dg_last_arch_sequence} =
$dg_last_arch_sequence{$instance_no}  ;



                                                         if ( !
defined( $dg_last_archfile_list ))
                                                                {

 $cnt2 =1 ;

 while( defined ( $dgthread{ $instance_l } {$cnt2 }))

 { $dg_last_arch_sequence{$cnt2} = $dgthread{$instance_l}{$cnt2} ;

         $cnt2++ ;
                                                                        }

 print LOGFILE "\n dg last arch seq %dg_last_arch_sequence" ;

 $dginfo_arr {$instance_l}{dg_last_arch_sequence} =
$dg_last_arch_sequence{$instance_no}  ;
                                                                }
                                                                        }

#               $dgthread{$instance_l} = $DEFAULT_THREAD if(
!$dgthread{$instance_l});

 $dginfo_arr{$instance_l}{dg_log_archive_dest} = $dg_log_arch_dir;

 print LOGFILE "\n" ; print LOGFILE
$dginfo_arr{$instance_l}{dg_log_archive_dest} ;

 if (&checkNodghost($instance_l) eq 'Y' ){
                                         print "\n  Ignore DG pages
due to noDGhost flag set at $nodghost_f \n";
                                        print LOGFILE "\n  Ignore DR
pages due to nodrhost flag set at $nodghost_f \n";
                                        }
                }
print LOGFILE "end of DG INFO" ;
}


#-----------------------------------------------------------------------------
# checkDRApplied :
#     Checks whether a log has been applied to DR
#-----------------------------------------------------------------------------
sub checkDRApplied()
{
        my $log=shift;
        my ($archdir,$archname,$instance_node,$logseq) = $log =~
/${archformat}(.*)/;

        foreach $db ( keys %dbinfo_arr ){
             if ( $dbinfo_arr{$db}{instance} eq $archname ){
                $instance_l = $archname;
                last;
             }
             if ( $dbinfo_arr{$db}{database} eq $archname ){
                 $instance_l = $dbinfo_arr{$db}{instance} ;
                 last;
             }
        }

        $threadno=$drthread{$instance_l};
        $threadno=$drthread{${instance_l}.${instance_node}}
                if ( $instance_node > 1  and $isdrhost_f eq "YES" ) ;

        #print " ($threadno)" if ( $logseq < $threadno && $threadno !=
$DEFAULT_THREAD) ;
        return("YES") if ( $logseq < $threadno ) ;
        return("NO");
}

sub checkDGApplied()
{
  my $log=shift;
        my ($archdir,$archname,$instance_node,$logseq) = $log =~
/(.*)\/(\w*).arch[_]*(\d)_(\d*)[_]*(.*).dbf(.*)/;

                print LOGFILE "\n $logseq  $instanceI
$dgthread{$instanceI}{$instance_node} " ;
        if ( $logseq < $dgthread{$instanceI}{$instance_node} ) {
return ("YES") ; }
        else { return ("NO");}


}
#-----------------------------------------------------------------------------
# checkTapeExists :
#     Checks whether a log has been backuped on tape, currently it is assumed
#     that archive logs older than 1day exists in tape.
#     BUT once sysadmins provide a standard file on all servers to look for
#     logs that are in tape , at that moment we  have to change this algorithm
#-----------------------------------------------------------------------------
sub checkTapeExists()
{
        my $archfile=shift;
        # if it is a DR host , no need to check for tape
        return("YES") if ( $isdrhost_f eq "YES" ) ;

        $TAPE_CHECK_SEC=&convertTime($TAPE_CHECK_TIME);
        &Stat("${archfile}");
        return("NO")  if ( ! defined($st_mtime) );
        return("YES") if ( (time - $st_mtime)  > $TAPE_CHECK_SEC ) ;
        print "\n $archfile:Cannot remove latest files" if ( -f
$tape_parfile ) ;
        print LOGFILE "\n $archfile:Cannot remove latest files" if (
-f $tape_parfile ) ;
        return("NO");

        # below code will be used once sysadmin give us file for
checking tape file
        $cnt=`cat $tape_parfile | grep $archfile | wc -l`;
        print "Tape cnt = $cnt ";
        print LOGFILE "Tape cnt = $cnt ";
        return("YES") if ( $cnt == 1 )   ;
        return("NO");
}

#-----------------------------------------------------------------------------
# convertTime :
#  - convert time variable from days ,hours or minutes into seconds
#    for later comparison
#-----------------------------------------------------------------------------
sub convertTime()
{
    $purge_param = shift;
    if ( $purge_param =~ /(\d*)h$/ ) {
        $purge_param = ${1};
        $purge_time = int(${1}) * 60 * 60;
        $interval   = "hours";
    }
    elsif ( $purge_param =~ /(\d*)m$/ ) {
        $purge_param = ${1};
        $purge_time = int(${1}) * 60;
        $interval   = "minutes";
    }
    elsif ( $purge_param =~ /(\d*)d$/ ) {
        $purge_param = ${1};
        $purge_time = int(${1}) * 24 * 60 * 60;
        $interval   = "days";
    }
    elsif ( $purge_param =~ /(\d*)s$/ ) {
        $purge_param = ${1};
        $purge_time = int(${1}) ;
        $interval   = "seconds";
    }
    else {
        $purge_time = $purge_param * 24 * 60 * 60;
        $interval   = "days";
    }
    return(int($purge_time));
}

#-----------------------------------------------------------------------------
# getNewArchDest :
# - this function is used in switchArchive to find the next archive dest
#   available for switching
# - read list of archive dests available from a sad parfile ,if any archive
#   dest is not available it scans through for next available destination .
# - The format expected in sad parfile is
SWITCH:INSTANCE_ID:log_archive_dest:ENABLE:
#    Ex: SWITCH:CTSPRD1:/archive1/CTSPRD/CTSPRD.arch:ENABLE:
#    ( use cron exception form to add/modify this parameter )
#-----------------------------------------------------------------------------
sub getNewArchDest()
{
        my ($instance_l,$curr_log_archive_dir)=@_;
        $currIndex=-99;

        if ( -r $sad_parfile ) {
           open(SADFILE, $sad_parfile   ) || &showError("$pname:Can't
Open $sad_parfile. $!",$instance_l);
           while(<SADFILE>) {
             if ( /^SWITCH/ and /$instance_l/ and !/DISABLE/ and
$DB_role eq "PRIMARY" ){
                my ($logfile) = (split(/:/))[2];
                chomp($logfile);
                push(@sadarr,$logfile);
                if($logfile =~ /$curr_log_archive_dir/){
                  #print "\nlogfile=$logfile
curr_log_archive_dir=$curr_log_archive_dir ::$#sadarr";
                  print "($#sadarr)";
                  print LOGFILE "($#sadarr)";
                  $currIndex=$#sadarr;
                }
              }if (/^STANDBY:SWITCH/ and /$instance_l/ and !/DISABLE/
and $DB_role eq "STANDBY"){
                my ($logfile) = (split(/:/))[3];
                chomp($logfile);
                push(@sadarr,$logfile);
                if($logfile =~ /$curr_log_archive_dir/){
                  #print "\nlogfile=$logfile
curr_log_archive_dir=$curr_log_archive_dir ::$#sadarr";
                  print "($#sadarr)";
                  print LOGFILE "($#sadarr)";
                  $currIndex=$#sadarr;

                  }
                }
           }
        }
        else
        {
                &showError("$pname:Unable to read
sad_parfile:$sad_parfile",$instance_l);
        }
        return if($currIndex == -99 );

        # running a forloop in case if next archive dest in sequence is either
        # incorrect or unavailable then proceed with the list until one found
        for ($cnt=1;$cnt < @sadarr; $cnt++){
            $index=($currIndex+$cnt)%@sadarr;
            $sadarr[$index] =~ /(.*)\/(\w*).arch/ ;
            my $new_log_archive_dir=$1;
            if ( -d $new_log_archive_dir ) {
                if ( $sadarr[$index] =~ /(.*)\/(\w*).arch/ ){
                    if ( $2 eq $dbinfo_arr{$instance_l}{database} or
                         $2 eq $dbinfo_arr{$instance_l}{instance} ){
                        return($sadarr[$index],$new_log_archive_dir);
                    }
                }
            }
            else{
               print "\n  skip.. $new_log_archive_dir"
            }
        }
        print "\n:Unable to get new archive dest:";
        print LOGFILE "\n:Unable to get new archive dest:";
        return;
}

#-----------------------------------------------------------------------------
# switchArchDest :
# - swtiches archive dest in database and also in init.ora file
#-----------------------------------------------------------------------------
sub switchArchDest()
{
        my $dbname=shift; chomp($dbname) ;
        print "\n switchArchDest:$dbname:";
        print LOGFILE "\n switchArchDest:$dbname:";
        my ($new_log_archive_dest,$new_log_archive_dir)
                                =
&getNewArchDest($dbname,$dbinfo_arr{$dbname}{log_archive_dir});
        $switch_archive_dest    = $new_log_archive_dest;
        $switch_archive_dest    = "$new_log_archive_dir/"
                        if (
!($dbinfo_arr{$dbname}{log_archive_format} =~ /^%t/ ) ) ;
        $curr_log_archive_dir   = $dbinfo_arr{$dbname}{log_archive_dir};

        print "\n  curr_log_archive_dir    = $curr_log_archive_dir";
        print "\n  new_log_archive_dir     = $new_log_archive_dir";
        print "\n  new/switch_archive_dest = $switch_archive_dest";
        print LOGFILE "\n  curr_log_archive_dir    = $curr_log_archive_dir";
        print LOGFILE "\n  new_log_archive_dir     = $new_log_archive_dir";
        print LOGFILE "\n  new/switch_archive_dest = $switch_archive_dest";

        if ( $new_log_archive_dest eq "" )
                {
                        print "\n  ERROR:Possible invalid file format
$sad_parfile";
                        print LOGFILE "\n  ERROR:Possible invalid file
format $sad_parfile";
                        print "\n  ERROR:Archive destination is not changed";
                        print LOGFILE "\n  ERROR:Archive destination
is not changed";
                        &showError("$pname:Unable to get new archive
dest",$dbname);
                        return;
                }
        my ($spfile_flag, $file) = &checkSPFile($dbname) ; my $spfile_opt="" ;
        $spfile_opt = " scope=both " if ($spfile_flag eq "TRUE" ) ;
        print LOGFILE "\n switch archive dest : SPFILE STATUS
$spfile_flag  spfile options $spfile_opt" ;
        my $lad_options="";
        if ($dbinfo_arr{$dbname}{compatible} =~ /^10/ )
                {
                        if ($dbinfo_arr{$dbname}{isDataguard} eq "YES" )
                        {
                                        $lad_options="
VALID_FOR=(ALL_LOGFILES, ALL_ROLES)
DB_UNIQUE_NAME=".$dbinfo_arr{$dbname}{db_unique_name}
if(defined($dbinfo_arr{$dbname}{db_unique_name}));
                        }
                        $lad_cmd1="select sysdate from dual";
                        my $switch_archive_dest_sql =
"LOCATION=${switch_archive_dest} ${lad_options}";
                        $lad_cmd2="alter system set
log_archive_dest='$switch_archive_dest' $spfile_opt";
                        $lad_cmd2="alter system set
log_archive_dest_1='$switch_archive_dest_sql'  $spfile_opt sid='*' "
                                                        if (
$dbinfo_arr{$dbname}{isSetlog_archive_dest_1} eq "YES" );
                }
                else
                {
                        my $switch_archive_dest_sql =
"LOCATION=".$switch_archive_dest.$lad_options;
                        $lad_cmd1="select sysdate from dual";
                        $lad_cmd2="alter system archive log start to
'$switch_archive_dest' $spfile_opt ";
                        $lad_cmd2="alter system set
log_archive_dest_1='$switch_archive_dest_sql'   $spfile_opt sid='*' "
                        if (
$dbinfo_arr{$dbname}{isSetlog_archive_dest_1} eq "YES" );
                }
                print LOGFILE "\n db role $DB_role db issetStandby
$dbinfo_arr{$instance}{isSetstandby_archive_dest} ";
                $lad_cmd3="" ;
                if ( $DB_role eq "STANDBY" and
$dbinfo_arr{$instance}{isSetstandby_archive_dest} eq "YES" )
                {
                $lad_cmd3= "alter system set
standby_archive_dest='$switch_archive_dest'  $spfile_opt sid='*' " ;
                }
                print LOGFILE "\n  db info arr standby archive dest
$dbinfo_arr{$db_name}{standby_archive_dest} " ;
                print LOGFILE "\n command $lad_cmd2" ;
        &setOraclehome($dbname);
        open(SQLDBA, "$oracle_home/bin/sqlplus /nolog << END
        connect /as sysdba
        $lad_cmd1;
        $lad_cmd2;
        $lad_cmd3 ;
        archive log list
        show parameter standby_archive_dest
        exit
        END |") || &showError("$pname:Cannot do switch archive dest.
$! ",$dbname);
        @data = <SQLDBA>;
        (@data2  = grep(/^Archive destination/, @data))
                   || &showError("$pname:Can't Find Archive Location:
@data",$dbname);
        $check_log_archive_dest = (split(' ', $data2[0]))[2];
        $check_log_archive_dest =~ /(\/\w+)\/(.*)/;

        if ( $check_log_archive_dest ne $switch_archive_dest ){
                print "\n  ERROR!After DB switch :";
                print LOGFILE "\n  ERROR!After DB switch :";
                print "\n  check_log_archive_dest = $check_log_archive_dest=";
                print LOGFILE "\n  check_log_archive_dest =
$check_log_archive_dest=";
                print "\n  new_log_archive_dest   = $new_log_archive_dest=";
                print LOGFILE "\n  new_log_archive_dest   =
$new_log_archive_dest=";
                print "\n  @data ";
                print LOGFILE "\n  @data ";
                if($lad_cmd3 =~ /(.*)standby_archive_dest(.*)/ )
                {
                        $lad_cmd3 =  "alter system set
standby_archive_dest='$check_log_archive_dest'  $spfile_opt" ;
                        open(SQLDBA, "$oracle_home/bin/sqlplus /nolog << END
                        connect /as sysdba
                        $lad_cmd3
                        exit
                         END |") || &showError("$pname:unable to
change standbyarchdest back to how it was because theres DB switch
error",$dbname) ;
                }
                return("NO") ;
        }
        print "\n  Alter system command executed successfully";
        print LOGFILE "\n  Alter system command executed successfully";

        # modify file init.ora
        $init_ora = "$ENV{ORACLE_HOME}/dbs/init${dbname}.ora" ;
#       $init_ora = "/oracle/admin/${dbname}/pfile/init${dbname}.ora";
#       if ( $spfile_flag eq "FALSE") {
                open(ORA, "$init_ora") || &showError("$pname:Cannot
open init_ora  file. $!",$dbname);
                rename($init_ora, $init_ora . '.bak');
                open(INIT_ORA_OUT, ">$init_ora");
                while (<ORA>)
                {
                   if ( /log_archive_dest[_1]*\b/i and !/^#/ ){
                        s/$curr_log_archive_dir/$new_log_archive_dir/;  }
                   if (/(.*)standby_archive_dest(.*)/i and $lad_cmd3
=~ /(.*)standby_archive_dest(.*)/ and !/^#/ )
                   {    s/$curr_log_archive_dir/$new_log_archive_dir/;
                   }
                   print INIT_ORA_OUT $_;  # this prints to original filename
                }
                close(INIT_ORA_OUT);
                close(ORA);
                print "\n  Changes applied to
/oracle/admin/${dbname}/pfile/init${dbname}.ora";
                print LOGFILE "\n  Changes applied to
/oracle/admin/${dbname}/pfile/init${dbname}.ora";
#                                       }
        #after switch , modify array elements to reflect changes for
multiple runs
        $new_mfs=&getMountFS("$new_log_archive_dir");
        undef($mountfs{$dbinfo_arr{$dbname}{mfs}});
        $mountfs{$new_mfs}        = "$new_log_archive_dir/* ";
        $dbinfo_arr{$dbname}{mfs} = $new_mfs ;

        $dbinfo_arr{$dbname}{log_archive_dest} = $new_log_archive_dest ;
        $dbinfo_arr{$dbname}{log_archive_dir}  = $new_log_archive_dir;
        $dbinfo_arr{$dbname}{standby_archive_dest} = $new_log_archive_dest
                                if ( $DB_role eq "STANDBY" and defined
($dbinfo_arr{$db_name}{standby_archive_dest}) );
        &getExceptionValues();
        print "\n";
        print LOGFILE "\n";
        return('YES');
}

#-----------------------------------------------------------------------------
# zipArchive :
# - zip/unzip depending on zipaction , by default zipmode=ENABLE
# - For DG and in cases where sync_arch is doing the job of zipping
#   you may have to disable zipping thro' cron exception
# - archformatG is required for dbs that starts with G* and also for
#   logs that have GZIP because of prev incomplete unzip
#-----------------------------------------------------------------------------
sub zipArchive()
{
  print "\nzipArchive:";
  print LOGFILE "\n in the zipArchive module :";
  my $zipaction;
  my $dbname;my $instance_node ; my $logseq ;my $ziplog ;
  my $time_s = time;
  $zipaction = shift ;
  print "$zipaction:";
  print LOGFILE "$zipaction:";
  my $logdate_l=qx(date +'[%T]');chomp($logdate_l);
  print $logdate_l; print LOGFILE $logdate_l;
  $ZIP_ARCHIVE_SEC=&convertTime($ZIP_ARCHIVE_TIME);
   my $instance_l = $instanceI ;
        print LOGFILE " \n instance that is zipped is $instance_l" ;
  &getDbParameters($instance_l);

 foreach $mfs ( keys %mountfs)
        {
                $archive_file_sys = $mountfs{$mfs};
 #              $archive_file_sys =~ s/[0-9]+/*[0-9]/g;
  #             print "\n archive_file_sys         =";
                print LOGFILE "\n $archive_file_sys         =";
 #              my @ptmp=split(' ',$archive_file_sys);
 #              my $pflag = 1;
 #               foreach (@ptmp)
 #                      {
 #                      if ( $pflag == 1 ){
 #                      print " $_" ;
 #                      print LOGFILE " $_" ;
 #                      $pflag =0;
 #                      next;
 #                      }
 #                      print "\n $_";
#                       print LOGFILE "\n  $_";
#                       }

                print LOGFILE "\n trying to find the zipfiles " ;
                open(ZIPFILES, "find $archive_file_sys -follow -name
'*dbf*' |")|| &showError("$pname:Cannot open zip files");;
                chomp(@zfiles=<ZIPFILES>);

                @szfiles=(map{$_->[0]} sort{$a->[1]<=>$b->[1]}
map{[$_,(stat $_)[9]]} @zfiles);
                print LOGFILE "\n @szfiles " ;
                foreach (@szfiles)
                {
                        chomp($ziplog  = $_);
                        print LOGFILE "\n $ziplog" ;
                        $ziplog  =~
/(.*)\/(\w*).arch[_]*(\d)_(\d*)[_]*(.*).dbf(.*)/ ;
                        $ziplog =~ /$archformatG(.*)/ if  ( $ziplog =~ /GZIP/) ;
                        $dbname        = $2;
                        $logseq        = $4;
                        $instance_node = $3;
                        print LOGFILE "\n $dbname $logseq $instance_node" ;
                         next if ( $zipaction =~ /^compress/ and
$ziplog =~ /.gz/ ) ;
                        next if (! ($instance_l =~ /$dbname(.*)/)) ;
                        next if ( ($zipaction =~ /^compress/) &&
($zipmode eq "DISABLE") );
                        print LOGFILE  "\n arch file to be zipped $ziplog " ;
                        $threadno = $dgthread{$instance_l}{$instance_node};
                        print LOGFILE "\n the threadinfo from standby
$threadno instance node $instance_node " ; # if (
&mvdc_check_inst($instance_l) eq "TRUE" ) ;
                        if (! defined($threadno))
                                { &showError("$pname : zipArchive :
unable to get threadinfo ,could be from thread file ,check DGinfo
module ", $instance_l) ;          }
#       &getDbParameters($instance_l);

                        if( ($zipaction =~ /^compress/) && ($ziplog =~
/(.*)\/(\w*).arch[_]*(\d)_(\d*)[_]*(.*).dbf/ ) )
                        {
                                 if ($logseq < $threadno)
                                 {      @testtime = stat ${ziplog} ;
                                        print LOGFILE time ;
                                        print LOGFILE  "\n zip log
stats @testtime zip archive sec  $ZIP_ARCHIVE_SEC" ;
                                        if ( ((stat ${ziplog})[9]  <
(time - $ZIP_ARCHIVE_SEC )) && (&isOpen("${ziplog}") =~ /no/) )
                                                {

$dbinfo_arr{$instance_l}{zip_cnt}++;
                                                # Check inbetween
zipping for possible purge and switchArchive
                                                if ( (defined($opt_O)
and (lc($opt_O) eq "ziponly" )) )
                                                        {
                                                        if ( (time -
$time_s) > 300 )
                                                        {
                                                        alarm($TIMEOUT);
                                                        print LOGFILE
"\n calling purge archive from ziparchive " ;
                                                        &purgeArchive();
                                                        $time_s = time;
                                                         }  }
                                                        print LOGFILE
"\n forking the process" ;

&processFork($zipaction,$ziplog);
                                                }
                                                else{
                                                        &mysleep(4);
                                                        print "\n
${ziplog} is in use or was cut ";
                                                        print LOGFILE
"\n  ${ziplog} is in use or was cut ";
                                                        print "less
than $ZIP_ARCHIVE_SEC seconds ago";
                                                        print LOGFILE
"less than $ZIP_ARCHIVE_SEC seconds ago";
                                                        }
                                                }
                                }
                                # unzip ONLY in dr host
                        if ( $zipaction =~ /^uncompress/ )
                                {
                                if ( $logseq >=
$dgthread{$instance_l}{$instance_node} )
                                        {
                                                next if(
$dbinfo_arr{$dbname}{unzip_num} == $throttle_window ) ;
                                                if ( ${ziplog} =~
/\.gz$/ or  ${ziplog} =~ /GZIP/ ){
                                                if
(&isOpen("${ziplog}") =~ /yes/)      {
                                                print "\n  ${ziplog}
is in use ...";
                                                next;

                 }

$dbinfo_arr{$instance_l}{unzip_cnt}++;

&processFork($zipaction,$ziplog) ;

                 }

$dbinfo_arr{$instance_l}{unzip_num}++;
                                        }
                                }
                }# for each zpfiles
    close(ZIPFILES);
    &mysleep(4);
    &processForkEnd();
  } # for each mfs

  #send info on no. of logs unzipped for each database
  foreach $db ( keys %dbinfo_arr )
                {
                if ( $dbinfo_arr{$db}{connected} eq "Y" ) {
                printf ("\n No. of logs zipped(%-8s) =
%2d",$db,$dbinfo_arr{$db}{zip_cnt})
                                if( $db && $zipaction eq "compress" );
                printf LOGFILE ("\n No. of logs zipped(%-8s) =
%2d",$db,$dbinfo_arr{$db}{zip_cnt})
                                if( $db && $zipaction eq "compress" );
                printf ("\n No. of logs unzipped(%-8s) =
%2d",$db,$dbinfo_arr{$db}{unzip_cnt})
                                if( $db && $zipaction =~ /uncompress/ );
                printf LOGFILE ("\n No. of logs unzipped(%-8s) =
%2d",$db,$dbinfo_arr{$db}{unzip_cnt})
                                if( $db && $zipaction =~ /uncompress/ );
                                                           }
                }
          print "\n";
        print LOGFILE "\n";
}

#-----------------------------------------------------------------------------
# isOpen :
#     checks  if log in use by other process using fuser
#-----------------------------------------------------------------------------
sub isOpen {
        my $file = $_[0];

        unlink "${statfile}";
        system "$FUSER $fuseropt $file > ${statfile} 2>/dev/null";
        if ( -s "${statfile}"){
          open(FUSERFILE, "${statfile}") ;
          chomp($pid2 = <FUSERFILE>);
          close(FUSERFILE);
        }
        return "no" if ($pid2 eq "");
        return "yes";
}

#-----------------------------------------------------------------------------
# switchOracleLog :
# - Does archive log switch if no log generated for certain period .
# - This is required in DR envs wherein there is low activity  to
#   avoid alerts due to log waiting
#   variable - ZIP_ARCHIVE_SEC
#-----------------------------------------------------------------------------
sub switchOracleLog()
{
        my $dbname = shift;

        $last_archfile=$dbinfo_arr{$dbname}{last_archfile};
        $last_archthread=$dbinfo_arr{$dbname}{last_arch_sequence};
        $last_archfile=$last_archfile.".gz" if ( ! -f $last_archfile );

        #print "\n  $last_archfile $last_archthread ";
        &Stat("${last_archfile}");
        $LOGSWITCH_SEC=&convertTime($LOGSWITCH_TIME);

        $a=(time - $st_mtime);
        #print "\nst_mtime=$st_mtime diff=$a LOGSWITCH_SEC=$LOGSWITCH_SEC";

        if ( (time - $st_mtime) >= $LOGSWITCH_SEC){
                print "\n\nswitchOracleLog:$dbname:";
                print LOGFILE "\nswitchOracleLog:$dbname:";
                print "\n last_archthread = $last_archthread";
                print LOGFILE "\n last_archthread = $last_archthread";
                print "\n last_archfile   = $last_archfile:";
                print LOGFILE "\n last_archfile   = $last_archfile:";
                open(SQLDBA, "$oracle_home/bin/sqlplus -s /nolog << END
                connect /as sysdba
                alter system switch logfile ;
                exit
                END |") || &showError("$pname:Cannot do alter system
switch logfile. $!",$dbname);
                @data = <SQLDBA>;
                print "\n Alter system command executed successfully.";
                print LOGFILE "\n Alter system command executed successfully.";
        } close(SQLDBA) ;
        print "\n";
        print LOGFILE "\n";
}

#-----------------------------------------------------------------------------
# isSwitch :
#    this function is used to find if switch archive is enabled or not
#    if sad_parfile exists then script archive destination is enabled.
#-----------------------------------------------------------------------------
sub isSwitch()
{
        my $dbname=shift;

        #print "\n$dbname : $sad_parfile :\n";
        #return("NO") if ( lc($opt_O) eq "nosad");
        return("NO") if( !-f $sad_parfile) ;
        my $cnt=`cat $sad_parfile | grep "SWITCH:$dbname" |grep -v
"DISABLE"| wc -l`;
        chomp($cnt);
        #print "\ncnt:$cnt:";
        if ( $cnt == 0  ) {
                return("NO");
        }
        else{
                return("YES");
        }
}

#-----------------------------------------------------------------------------
# Usage:
#     Displays about script usage when no arguments specified
#-----------------------------------------------------------------------------
sub Usage {
       $exit = shift(@_) || 0;
       print STDERR "\n usage: $Synopsis";
       exit $exit;
}

#-----------------------------------------------------------------------------
# prepareMountFS :
#     This is the main function for driving zip and purge process.
#     This function prepares mount points for all database archive locations
#-----------------------------------------------------------------------------
sub prepareMountFS()
{
        my $dbname = shift;
        print LOGFILE " \n preparing moutn fs for instance $dbname " ;
        &getCurrArchDest($dbname);
        return(0) if ( $dbinfo_arr{$dbname}{log_archive_dir} eq "" ) ;

        $dbinfo_arr{$dbname}{connected} = "Y";
        $mfs                     =
&getMountFS("$dbinfo_arr{$dbname}{log_archive_dir}");
        $mountfs{$mfs}          = "$dbinfo_arr{$dbname}{log_archive_dir} ";
        #mount_fscnt - currently not in use
        #$mount_fscnt{$mfs}       = $mount_fscnt{$mfs} + 1;
        $dbinfo_arr{$dbname}{mfs}= $mfs ;
}

#-----------------------------------------------------------------------------
# processFork :
#       used for forking multiple streams
#       currently this is used for modules zipping and unzipping
#-----------------------------------------------------------------------------
sub processFork()
{
    my ($zipaction,$ziplog) = @_;

    if ($pid = fork) {   # PARENT
        #system(date);
        push @pids_running, $pid;
        while ($#pids_running >= $MAXPROCS - 1 ) {
            foreach $pid (@pids_running) {
                if (($return = POSIX::waitpid( $pid, &POSIX::WNOHANG )) > 0) {
                    @pids_running = grep !/^${pid}$/, @pids_running;
                }
            }
            &mysleep(5);
        }
    }
    elsif (defined $pid) {  # CHILD
        select(STDOUT); $| = 1;
        select(STDERR); $| = 1;
        select(STDOUT);
        &zipCmd($zipaction,$ziplog);
        exit 0;
    }
    else {
        &showError("$pname:Can't Fork: $!\n");
    }
}

#-----------------------------------------------------------------------------
# processForkEnd :
#     function to do cleanup after child processes are done
#-----------------------------------------------------------------------------
sub processForkEnd()
{
        #print "\nprocess end $#pids_running";
        print "\n  in pids_running         = ";
        print LOGFILE "\n  in pids_running         = ";
        while ($#pids_running >= 0)
        {
                foreach $pid (@pids_running)
                {
                if (($return = POSIX::waitpid( $pid, &POSIX::WNOHANG )) > 0)
                {
                @pids_running = grep !/^${pid}$/, @pids_running;
                }
        }
        #print "\n in pids_running=$#pids_running ";
        print "$#pids_running";
        print LOGFILE "$#pids_running";
        &mysleep(5);
        }
}

#-----------------------------------------------------------------------------
# zipCmd :
#     function for actual gzip and gunzip
#     in case of uncompress the logs are renamed as GZIP.archlog before actual
#     gunzip to avoid standby to grab incomplete archive logs
#-----------------------------------------------------------------------------
sub zipCmd(){
        my $zipaction;
        my $flogfile;
        my $archfilename;
        my $dbname;
        ($zipaction,$flogfile) = @_;
        ($archdir,$archfile)   = $flogfile =~ /(.*)\/(\w+.*)/;

        print "\n";
        print LOGFILE "\n in the zipcmd ";
        printf " (%10d)",$threadno if ( $threadno != $DEFAULT_THREAD) ;
        print LOGFILE " ($threadno)" if ( $threadno != $DEFAULT_THREAD) ;
        if ( $zipaction =~ /^compress/ ){
                print " zipping:${flogfile}:";
                print LOGFILE "  zipping:${flogfile}:";
                `$GZIP --fast ${flogfile}`;
        }
        if ( $zipaction =~ /uncompress/ ){
                if ( ${flogfile} =~ /\.gz$/ ) {
                        if ( ${flogfile} =~ /GZIP/ )  {
                                #print " Type2:GZIP.File.dbf.gz
unzipping ${archdir}/${archfile}";
                                print " unzipping:${archdir}/${archfile}:";
                                print LOGFILE "
unzipping:${archdir}/${archfile}:";
                                `$GZIP -d ${archdir}/${archfile}`;
                                $archfile =~ s/\.gz$// ;
                                $archfile =~ s/GZIP\.// ;
                                rename("${archdir}/GZIP.${archfile}",
"${archdir}/${archfile}");
                        }
                        else{
                                #print " Type1:File.dbf.gz:
unzipping ${flogfile}:";
                                print " unzipping:${flogfile}:";
                                print LOGFILE " unzipping:${flogfile}:";
                                rename("${archdir}/${archfile}",
"${archdir}/GZIP.${archfile}");
                                `$GZIP -d ${archdir}/GZIP.${archfile}`;
                                $archfile =~ s/\.gz$// ;
                                rename("${archdir}/GZIP.${archfile}",
"${archdir}/${archfile}");
                        }
                }
                else {
                        if ( ${archfile} =~ /GZIP/ ){
                                #print " Type3:GZIP.File.dbf:unzipping
${flogfile}:";
                                print " unzipping:${flogfile}:";
                                print LOGFILE " unzipping:${flogfile}:";
                                $archfile =~ s/GZIP\.// ;
                                rename("${archdir}/GZIP.${archfile}",
"${archdir}/${archfile}");
                        }
                }
        }
}

#-----------------------------------------------------------------------------
# getExceptionValues:
#       Reads exceptionDB.par file for non-default parameters
#-----------------------------------------------------------------------------
sub getExceptionValues
{
    my $mfs_e ;
    my $archive_e ;
    my $pct_upper_limit_e ;
    my $pct_lower_limit_e ;
    my $archive_retain_e ;
    my $zipmode_e ;
    my $log_arch_dest_e ;
    my $mfs_t ;

    if (-r $exceptfile) {
        open(EXCEPTFILE, $exceptfile) || &showError("$pname:Can't Open
$exceptfile. $!");
        while (<EXCEPTFILE>)
        {    if (/^SWITCH/ and $DB_role eq "PRIMARY")
                        {        @data_e = split(/:/) ;
                                $log_arch_dest_e = $data_e[2] ;
                                chomp($log_arch_dest_e);
                                $log_arch_dest_e =~ /(.*)\/(\w+).arch(.*)/ ;
                                $log_arch_dir_e = $1 ;
                                print LOGFILE "\n new log dir from
except parfile $log_arch_dir_e " ;
                                $mfs_t = &getMountFS($log_arch_dir_e) ;
                                $mountfs{$mfs_t} = $log_arch_dir_e;
                        }

                if(/^STANDBY:SWITCH/ and $DB_role eq "STANDBY")
                        {
                                @data_e = split(/:/);
                                $log_arch_dest_e = $data_e[3];
                                 chomp($log_arch_dest_e);
                                $log_arch_dest_e =~ /(.*)\/(\w+).arch(.*)/ ;
                                $log_arch_dir_e = $1 ;
                                print LOGFILE "\n new log dir in
STANDBY ROLE from except parfile $log_arch_dir_e " ;
                                $mfs_t = &getMountFS($log_arch_dir_e) ;
                                $mountfs{$mfs_t} = $log_arch_dir_e;
                        }

           next unless (/^ARCHIVE:/ );
           {
             @data_e = split(/:/);
             $data_n = @data_e;
             chomp($data_e[$data_n-1]);

             $sid_e                             = $data_e[1];
             $mfs_e=$dbinfo_arr{$sid_e}{mfs};
             $pct_lower_limit_ea{$mfs_e}        = $data_e[2];
             $pct_upper_limit_ea{$mfs_e}        = $data_e[3];
             $archive_retain_ea{$mfs_e}         = $data_e[4];
             $zipmode_ea{$mfs_e}                = $data_e[5];
             $zipmode_ea{$sid_e}                = $data_e[5];

             $mailto_ea{$sid_e}                 = $data_e[6];
             $pageto_ea{$sid_e}                 = $data_e[7];
             $sync_arch_mail_limit_ea{$sid_e}   = $data_e[8];
             $sync_arch_page_limit_ea{$sid_e}   = $data_e[9];
             $drlog_mail_limit_ea{$sid_e}       = $data_e[10];
             $drlog_page_limit_ea{$sid_e}       = $data_e[11];
             $throttle_window_ea{$sid_e}        = $data_e[12];
             $throttle_window_ea{$mfs_e}        = $data_e[12];

             #print "\n ";
             #print "getExceptionValues:$mfs_e:";
             #print "\n  $sid_e:$pct_lower_limit_ea{$mfs_e}:";
             #print "$pct_upper_limit_ea{$mfs_e}:$archive_retain_ea{$mfs}:";
             #print "$zipmode_ea{$mfs_e}:";
             #print "$mailto_ea{$sid_e}:$pageto_ea{$sid_e}:";
             #print
"$sync_arch_mail_limit_ea{$sid_e}:$sync_arch_page_limit_ea{$sid_e}:";
             #print
"$drlog_mail_limit_ea{$sid_e}:$drlog_page_limit_ea{$sid_e}:";
             #print
"$manual_drstop_limit_ea{$sid_e}:$throttle_window_ea{$sid_e}";

           }
        }
        close(EXCEPTFILE);
    }
}

#-----------------------------------------------------------------------------
# getParameters :
#     gets exception/default values based on mount filesystem
#     these values will be specific to a mount fs
#-----------------------------------------------------------------------------
sub getParameters()
{
    my $mfs              = shift;
    $pct_lower_limit     = $pct_lower_limit_ea{$mfs} ?
$pct_lower_limit_ea{$mfs} : $pct_lower_limit_d;
    $pct_upper_limit     = $pct_upper_limit_ea{$mfs} ?
$pct_upper_limit_ea{$mfs} : $pct_upper_limit_d;
    $archive_retain_time = $archive_retain_ea{$mfs} ?
$archive_retain_ea{$mfs} : $archive_retain_time_d;
    $zipmode             = $zipmode_ea{$mfs} ? $zipmode_ea{$mfs} : $zipmode_d;
    $throttle_window     =
$throttle_window_ea{mfs}?$throttle_window_ea{$mfs}:$throttle_window_d;
}

#-----------------------------------------------------------------------------
# getDbParameters :
#  - gets exception/default values based on database name
#-----------------------------------------------------------------------------
sub getDbParameters()
{
    $dbname               = shift;
    #$mailto              = $mailto_ea{$dbname} ? $mailto_ea{$dbname}
: $mailto_d ;
    #$pageto              = $pageto_ea{$dbname} ? $pageto_ea{$dbname}
: $pageto_d ;
    $mailto               = $mailto_ea{$dbname} ? $mailto_ea{$dbname}
: $dbinfo_arr{$dbname}{mailto} ;
    $pageto               = $pageto_ea{$dbname} ? $pageto_ea{$dbname}
: $dbinfo_arr{$dbname}{pageto} ;
    $sync_arch_mail_limit =
$sync_arch_mail_limit_ea{$dbname}?$sync_arch_mail_limit_ea{$dbname}:$sync_arch_mail_limit_d;
    $sync_arch_page_limit =
$sync_arch_page_limit_ea{$dbname}?$sync_arch_page_limit_ea{$dbname}:$sync_arch_page_limit_d;
    $drlog_mail_limit     =
$drlog_mail_limit_ea{$dbname}?$drlog_mail_limit_ea{$dbname}:$drlog_mail_limit_d;
    $drlog_page_limit     =
$drlog_page_limit_ea{$dbname}?$drlog_page_limit_ea{$dbname}:$drlog_page_limit_d;
    $zipmode              = $zipmode_ea{$dbname} ?
$zipmode_ea{$dbname} : $zipmode_d;
    $throttle_window      =
$throttle_window_ea{$dbname}?$throttle_window_ea{$dbname}:$throttle_window_d;
}

#-----------------------------------------------------------------------------
# findArchFile :
#  - Input parameter is sequence number and finds the last archfile
#    based on sequence which is used to determine timestamp of the
#    later in getSyncArchLogLag()
#-----------------------------------------------------------------------------
sub findArchFile()
{
        my ($instance_l,$seq)      = @_;
        my $log_archive_dest       = $dbinfo_arr{$instance_l}{log_archive_dest};
  #     my $star_log_archive_dest  = $log_archive_dest ;
#       $star_log_archive_dest     =~ s/[0-9]+/*/;
        my $instance_number = $dbinfo_arr{$instance_l}{instance_number} ;
        my $archfile ;
        open(LASTFILE, "ls -1tr
$log_archive_dest${instance_number}*${seq}*dbf* | tail -1 |")
                                || &showError("$pname:Cannot find last
archive log. $!");
        while (<LASTFILE>) {
            chomp($archfile=$_);
       }
        close(LASTFILE);
        return ( $archfile ) ;
}

#-----------------------------------------------------------------------------
# getDRLogLag :
#  - Connects to database and gets the data and time of archive logs
#    of last sequence available on DR host and last archive sequence
#     applied on DR ,
#  - If required data is not available in database , then it tries to
#    get the same info from archive logs available on server
#-----------------------------------------------------------------------------
sub getDRLogLag()
{
   my $instance_l = shift ;
   my $dbname     = $dbinfo_arr{$instance_l}{database};
   my $log_arch_dest = $dbinfo_arr{$instance_l}{log_archive_dest};
   $current_thrd        = $dbinfo_arr{$instance_l}{last_arch_sequence};
   $dr_last_arch_seq    = $dbinfo_arr{$instance_l}{dr_last_arch_sequence};
   $remote_thrd         = $drthread{$instance_l};
   return if ( $remote_thrd == -1 );
   return if ( $dr_last_arch_seq == 0 );
   $logs_behind         = $current_thrd - $remote_thrd ;
   print "\ngetDRLogLag :$instance_l:";
   print LOGFILE "\ngetDRLogLag :$instance_l:";

   my $str              = qq(date +'%S:%M:%H:%d:%m:%Y';ls -1tr
${norecover_path}/${dbname}|wc -l);
   chomp(($cdate,$dbinfo_arr{$instance_l}{norecover_flag})=qx($SSH -qn
${remote_host} $sshopt "$str" 2>/dev/null));

   $norecover_flag      = int($dbinfo_arr{$instance_l}{norecover_flag} );
   print "$norecover_flag:";
   print LOGFILE "$norecover_flag:";

   $sync_arch_mail_sec = &convertTime($sync_arch_mail_limit);
   $sync_arch_page_sec = &convertTime($sync_arch_page_limit);
   $drlog_mail_sec     = &convertTime($drlog_mail_limit) ;
   $drlog_page_sec     = &convertTime($drlog_page_limit) ;

   $sql_stmt = "SELECT  'to_be_recovered_sec  ' ||
                        ROUND((plog.FIRST_TIME - dlog.FIRST_TIME)*24*60*60)
                FROM    v\\\$log_history dlog , v\\\$log_history plog,
                        v\\\$instance ins
                WHERE   dlog.SEQUENCE# = $remote_thrd
                AND     plog.SEQUENCE# = $current_thrd
                AND     d.log.thread#  = plog.thread#
                AND     p.log.thread#  = ins.instance_number
                UNION
                SELECT  'sync_arch_lag_sec '||
                        ROUND((plog.FIRST_TIME - slog.FIRST_TIME)*24*60*60)
                FROM    v\\\$log_history plog,v\\\$log_history slog,
                        v\\\$instance ins
                WHERE   slog.SEQUENCE# = $dr_last_arch_seq
                AND     plog.SEQUENCE# = $current_thrd
                AND     d.log.thread#  = plog.thread#
                AND     p.log.thread#  = ins.instance_number";

   open(SQLDBA, "$oracle_home/bin/sqlplus /nolog << END
        connect /as sysdba
        show parameter db_name
        alter session set nls_date_format = 'DD-MON-YY HH24:MI:SS';
        set heading off
        $sql_stmt ;
        exit
        END |") || &showError("$pname:getDRLogLag:sqlplus error:
$!",$instance_l);
        @data = <SQLDBA>; close(SQLDBA);

   if ( (@data1  = grep(/^to_be_recovered_sec/, @data)) ) {
      $to_be_recovered_sec= (split(' ', $data1[0]))[1];
   }
   else{
        $to_be_recovered_sec =
&getArchTimeFromHost($instance_l,$current_thrd,$remote_thrd);
   }
   $to_be_recovered_d   = &convertSecToHrs($to_be_recovered_sec);

   if( (@data1  = grep(/^sync_arch_lag_sec/, @data))  ) {
      $sync_arch_lag_sec        = (split(' ', $data1[0]))[1];
   }
   else{
        $sync_arch_lag_sec =
&getArchTimeFromHost($instance_l,$current_thrd,$dr_last_arch_seq);
   }
   $sync_arch_lag_d     = &convertSecToHrs($sync_arch_lag_sec);

   print "\n mailto            :pageto                 = [$mailto:$pageto]";
   print LOGFILE "\n mailto            :pageto                 =
[$mailto:$pageto]";
   print "\n current_thread    :dr_last_arch_seq       =
[$current_thrd:$dr_last_arch_seq]";
   print LOGFILE "\n current_thread    :dr_last_arch_seq       =
[$current_thrd:$dr_last_arch_seq]";
   print "\n current_thread    :dr_last_applied_thread =
[$current_thrd:$remote_thrd]";
   print LOGFILE "\n current_thread    :dr_last_applied_thread =
[$current_thrd:$remote_thrd]";
   print "\n dr_host           :No. of Logs behind     =
[${remote_host}:$logs_behind]";
   print LOGFILE "\n dr_host           :No. of Logs behind     =
[${remote_host}:$logs_behind]";
   print "\n to_be_recovered   :sync_arch_lag          =
[$to_be_recovered_d($to_be_recovered_sec):";
   print LOGFILE "\n to_be_recovered   :sync_arch_lag          =
[$to_be_recovered_d($to_be_recovered_sec):";
        print "$sync_arch_lag_d($sync_arch_lag_sec)]";
        print LOGFILE "$sync_arch_lag_d($sync_arch_lag_sec)]";
   print "\n";
   print LOGFILE "\n";

   # check for nopage flag on dr host ,
   # if flag exists ignore alerts
   return if ( &checkNopage($dbname) eq "YES" );

   if ( $sync_arch_lag_sec > $sync_arch_mail_sec )
   {
    print "\n   Sending email ... ";
    print LOGFILE "\n   Sending email ... ";
    $errmsg = &msgfmt("w","$local_host","$dbname","sync_arch lags log
shipping by more than $sync_arch_lag_d ");
    print " \n  WARN:$local_host:$dbname sync_arch lags log shipping
by more than  $sync_arch_lag_d \n";
    print LOGFILE " \n  WARN:$local_host:$dbname sync_arch lags log
shipping by more than  $sync_arch_lag_d \n";
    &mailit("$errmsg","/dev/null");
   }

   if ( $sync_arch_lag_sec > $sync_arch_page_sec )
   {
    print "\n   Sending epage ... ";
    print LOGFILE "\n   Sending epage ... ";
    &showError("sync_arch lags log shipping by more than
$sync_arch_lag_d",$dbname);
    #$errmsg = &msgfmt("w","$local_host","$dbname","sync_arch lags log
shipping by more than $sync_arch_lag_d ");
    #print " \n  WARN:$local_host:$dbname sync_arch lags log shipping
by more than  $sync_arch_lag_d\n";
    #&pageit("$errmsg");
   }
   #print "\n";

   if ( ($norecover_flag != 1 && $to_be_recovered_sec  > $drlog_mail_sec) ) {
        print "\n  Sending email ... ";
        print LOGFILE "\n  Sending email ... ";
        $errmsg = &msgfmt("w","$local_host","$dbname","DR is
$to_be_recovered_d behind production db");
        print " \n  WARN:$local_host:$dbname DR is $to_be_recovered_d
behind PROD\n";
        print LOGFILE " \n  WARN:$local_host:$dbname DR is
$to_be_recovered_d behind PROD\n";
        &mailit("$errmsg","/dev/null");
   }

   if ( ($norecover_flag != 1 && $to_be_recovered_sec  > $drlog_page_sec)   ) {
        print "\n  Sending epage ... ";
        print LOGFILE "\n  Sending epage ... ";
        &showError("DR is $to_be_recovered_d behind production db",$dbname);
        #$errmsg = &msgfmt("w","$local_host","$dbname","DR is
$to_be_recovered_d behind production db");
        #print " \n  WARN:$local_host:$dbname DR is $to_be_recovered_d
behind PROD\n";
        #&pageit("$errmsg");
  }
}


sub getDGLogLag()
{       my $instance_l = shift ;
        my $dbname = $dbinfo_arr{$instance_l}{database} ;
        my $instno = $dbinfo_arr{$instance_l}{instance_number} ;
        my $curr_seq = $dbinfo_arr{$instance_l}{last_arch_sequence} ;
        my $dg_last_arch_seq = $dbinfo_arr{$instance_l}{dg_last_arch_sequence} ;
        my  $dg_last_app_seq = $dgthread{$instance}{$instno} ;
        return if ( $dg_last_app_seq == -1 ) ;
        return if ( $dg_last_arch_seq == 0 ) ;
        $logs_behind = $curr_seq - $dg_last_app_seq ;
        my $rec_inst = $dbinfo_arr{$instance_l}{rec_inst} ;
        my $str  = qq(date +'%S:%M:%H:%d:%m:%Y';ls -1tr
${norecover_path}/${dbname}\* |wc -l);
        chomp(($cdate,$dbinfo_arr{$instance_l}{norecover_flag})=qx($SSH
-qn ${rec_inst} $sshopt "$str" 2>/dev/null));
        $norecover_flag      = int($dbinfo_arr{$instance_l}{norecover_flag} );
        print "$norecover_flag:";
         print LOGFILE "$norecover_flag:";

       $sync_arch_mail_sec = &convertTime($sync_arch_mail_limit);
       $sync_arch_page_sec = &convertTime($sync_arch_page_limit);
       $dglog_mail_sec     = &convertTime($drlog_mail_limit) ;
       $dglog_page_sec     = &convertTime($drlog_page_limit) ;


         $sql_stmt = "SELECT  'to_be_recovered_sec  ' ||
                             ROUND((plog.FIRST_TIME - dlog.FIRST_TIME)*24*60*60)
                         FROM    v\\\$log_history dlog , v\\\$log_history plog,
                                v\\\$instance ins
                        WHERE   dlog.SEQUENCE# = $dg_last_app_seq
                        AND     plog.SEQUENCE# = $curr_seq
                        AND     d.log.thread#  = plog.thread#
                        AND     p.log.thread#  = ins.instance_number
                          UNION
                        SELECT  'sync_arch_lag_sec '||
                        ROUND((plog.FIRST_TIME - slog.FIRST_TIME)*24*60*60)
                        FROM    v\\\$log_history plog,v\\\$log_history slog,
                        v\\\$instance ins
                         WHERE   slog.SEQUENCE# = $dg_last_arch_seq
                        AND     plog.SEQUENCE# = $curr_seq
                        AND     d.log.thread#  = plog.thread#
                        AND     p.log.thread#  = ins.instance_number";
            open(SQLDBA, "$oracle_home/bin/sqlplus /nolog << END
                 connect /as sysdba
                 show parameter db_name
                alter session set nls_date_format = 'DD-MON-YY HH24:MI:SS';
                set heading off
                $sql_stmt ;
                 exit
                END |") || &showError("$pname:getDRLogLag:sqlplus
error: $!",$instance_l);
                   @data = <SQLDBA>; close(SQLDBA);

                 if ( (@data1  = grep(/^to_be_recovered_sec/, @data)) )
                        {
                                $to_be_recovered_sec= (split(' ',
$data1[0]))[1];
                         }
                else    {
                                $to_be_recovered_sec =
&getArchTimeFromHost($instance_l,$curr_seq,$dg_last_app_seq);
                        }
                $to_be_recovered_d   = &convertSecToHrs($to_be_recovered_sec);

                 if( (@data1  = grep(/^sync_arch_lag_sec/, @data))  )
                        {
                                        $sync_arch_lag_sec  = (split('
', $data1[0]))[1];
                          }
                   else {
                                $sync_arch_lag_sec =
&getArchTimeFromHost($instance_l,$current_thrd,$dg_last_app_seq);
                          }
                                   $sync_arch_lag_d     =
&convertSecToHrs($sync_arch_lag_sec);


                        print "\n mailto            :pageto
     = [$mailto:$pageto]";
                        print LOGFILE "\n mailto            :pageto
             = [$mailto:$pageto]";
                        print "\n current_thread    :dr_last_arch_seq
     = [$curr_seq:$dg_last_arch_seq]";
                           print LOGFILE "\n current_thread
:dr_last_arch_seq       = [$curr_seq:$dg_last_arch_seq]";
                           print "\n current_thread
:dr_last_applied_thread = [$curr_seq:$dg_last_app_seq]";
                   print LOGFILE "\n current_thread
:dr_last_applied_thread = [$curr_seq:$dg_last_app_seq]";
                           print "\n dr_host           :No. of Logs
behind     = [${rec_host}:$logs_behind]";
                           print LOGFILE "\n dr_host           :No. of
Logs behind     = [${rec_host}:$logs_behind]";
                           print "\n to_be_recovered   :sync_arch_lag
        = [$to_be_recovered_d($to_be_recovered_sec):";
                           print LOGFILE "\n to_be_recovered
:sync_arch_lag          = [$to_be_recovered_d($to_be_recovered_sec):";
                           print "$sync_arch_lag_d($sync_arch_lag_sec)]";
                        print LOGFILE "$sync_arch_lag_d($sync_arch_lag_sec)]";
                           print "\n";

                         print LOGFILE "\n";

                         return if ( &checkNopage($dbname) eq "YES" );

                   if ( $sync_arch_lag_sec > $sync_arch_mail_sec )
                         {
                                    print "\n   Sending email ... ";
                                    print LOGFILE "\n   Sending email ... ";
                                    $errmsg =
&msgfmt("w","$local_host","$dbname","sync_arch lags log shipping by
more than $sync_arch_lag_d ");
                                    print " \n
WARN:$local_host:$dbname sync_arch lags log shipping by more than
$sync_arch_lag_d \n";
                                    print LOGFILE " \n
WARN:$local_host:$dbname sync_arch lags log shipping by more than
$sync_arch_lag_d \n";
                                    &mailit("$errmsg","/dev/null");
                        }

                   if ( $sync_arch_lag_sec > $sync_arch_page_sec )
                        {
                                    print "\n   Sending epage ... ";
                                    print LOGFILE "\n   Sending epage ... ";
                                    &showError("sync_arch lags log
shipping by more than $sync_arch_lag_d",$dbname);
                                    $errmsg =
&msgfmt("w","$local_host","$dbname","sync_arch lags log shipping by
more than $sync_arch_lag_d ");
                                    print " \n
WARN:$local_host:$dbname sync_arch lags log shipping by more than
$sync_arch_lag_d\n";
                                &pageit("$errmsg");
                           }
   #print "\n";

                   if ( ($norecover_flag != 1 && $to_be_recovered_sec
> $dglog_mail_sec) ) {
                        print "\n  Sending email ... ";
                        print LOGFILE "\n  Sending email ... ";

                         $errmsg =
&msgfmt("w","$local_host","$dbname","DR is $to_be_recovered_d behind
production db");
                         print " \n  WARN:$local_host:$dbname DR is
$to_be_recovered_d behind PROD\n";
                         print LOGFILE " \n  WARN:$local_host:$dbname
DR is $to_be_recovered_d behind PROD\n";
                        &mailit("$errmsg","/dev/null");
                        }

                   if ( ($norecover_flag != 1 && $to_be_recovered_sec
> $dglog_page_sec)   ) {
                         print "\n  Sending epage ... ";
                        print LOGFILE "\n  Sending epage ... ";
                        &showError("DR is $to_be_recovered_d behind
production db",$dbname);
                        #$errmsg =
&msgfmt("w","$local_host","$dbname","DR is $to_be_recovered_d behind
production db");
                        #print " \n  WARN:$local_host:$dbname DR is
$to_be_recovered_d behind PROD\n";
                        #&pageit("$errmsg");
                        }
#}


}
#-----------------------------------------------------------------------------
# checkNopage :
#  - This function takes care of alerts during know issues with DR recovery,
#    in case DR is unavailable for known time , we could stop DR alerts by
#    creating below flag ,
#    drhost:/usr/tools/oracle/recovery/norecover/SID.nopage.24h
#  - By default script itself creates a 24h flag to ignore pages when DR
#    is stopped for refreshes .This way it stops paging alerts during refresh
#    and certain time after the refresh
#-----------------------------------------------------------------------------
sub checkNopage(){
   my $dbname = shift;
   my $instance_l = $dbinfo_arr{$dbname}{instance} ;
   my $rec_node = $dbinfo_arr{$instance}{rec_node} ;
   $ENV{dbname} = $dbname;
   if ( $norecover_flag == 1 && $to_be_recovered_sec > 6*60*60 )
                {
                 print "\n  checkNopage:$dbname:$norecover_flag:${rec_node}";
                print LOGFILE "\n
checkNopage:$dbname:$norecover_flag:${rec_node}";
              $ssh_script='perl -e \' if ( system(\"ls -1tr
/usr/tools/oracle/recovery/norecover/${dbname}.nopage.* \") != 0 ) {
                                        system(\"touch
/usr/tools/oracle/recovery/norecover/${dbname}.nopage.24h\") ;
                                }
                                \' ';
                      #print "\n ssh_script = $ssh_script ";
                @nopage_value_a = `$SSH -qn ${rec_node} $sshopt
"$ssh_script" 2>/dev/null `;
                 print "\n nopage_value_a = @nopage_value_a";
                 print LOGFILE "\n nopage_value_a = @nopage_value_a";
                }
      #print "\n checkNopage:$dbname:$norecover_flag:";
      #print LOGFILE "\n checkNopage:$dbname:$norecover_flag:";
              $npv="ls -ltr ${norecover_path}/${dbname}.nopage.*
2>/dev/null| tail -1| tr -s ' '|";
              $npv=$npv."/usr/local/bin/perl -ne '`date`;";
              $npv=$npv."chomp(\@b=split(/ /,\$_)); print
\"\$b[5]:\$b[6]:\$b[7]:\$b[8]\"' ";
              $nopage_value=qx($SSH -qn ${rec_node} $sshopt $npv);

              if ( $nopage_value ){
                         print " nopage_value=$nopage_value";
                         print LOGFILE " nopage_value=$nopage_value";
                         chomp(($mon,$dd,$hh,$mm,$ff)
=split(/:/,$nopage_value));
                         $nopage_value_time   = (split(/\./,$ff))[2];
                        $nopage_value_sec =
&convertTime($nopage_value_time) if ( $nopage_value );
                         print "($nopage_value_sec)";
                         print LOGFILE "($nopage_value_sec)";


%month=('Jan',0,'Feb',1,'Mar',2,'Apr',3,'May',4,'Jun',5,
                         'Jul',6,'Aug',7,'Sep',8,'Oct',9,'Nov',10,'Dec',11);
                 ($ssc,$mmc,$hhc,$ddc,$monc,$yyc) = (split(/:/,$cdate));


$tdiff=timelocal($ssc,$mmc,$hhc,,$ddc,$monc-1,$yyc)-timelocal(1,$mm,$hh,$dd,$month{$mon},$yyc);
                 print "\n time passed after refresh/manual DR stop=$tdiff sec";
                 print LOGFILE "\n time passed after refresh/manual DR
stop=$tdiff sec";
                 if ( $tdiff < $nopage_value_sec ) {
                              print "\n Ignore pages due to
refresh/manual DR stop ...\n";
                              print LOGFILE "\n Ignore pages due to
refresh/manual DR stop ...\n";
                              return "YES";
                                }


        # remove file after 1hr sothat pages can go for sometime(1hr)
for dbas to respond
                         `$SSH -qn ${rec_node} $sshopt rm
${norecover_path}/${dbname}.nopage.* 2>/dev/null `
                                if($tdiff > ($nopage_value_sec+3600) );
      }
}

#-----------------------------------------------------------------------------
# convertSecToHrs:
#       Converts seconds to minutes/hrs for reporting purpose
#-----------------------------------------------------------------------------
sub convertSecToHrs(){
        my $sec = shift;
        my $time;
        if ( $sec/60 > 60 ) {
                $hrsa = floor( $sec/(60*60));
                $hrsb = ceil( ($sec-$hrsa*60*60)/60 ) ;
                #$hrsb = $sec % 60 ;
                $time = $hrsa."h".$hrsb."m";
        }
        else {
                if ( $sec > 60 ){
                  $mina = floor($sec/60);
                  $time = $mina."m";
                }
                else{
                        $time=$sec."s";
                }
        }
        return($time);
}

#-----------------------------------------------------------------------------
# getMountFS :
#  - gets root mount filesystem for archive destination
#  - this is put as seperate function inorder being called at
#    multiple places .
#-----------------------------------------------------------------------------
sub getMountFS(){
        my $log_archive_dir_l = shift;
        my $mfs;
        open(DF, "$DF  $log_archive_dir_l $dfopt |")
                        || &showError("$pname:getMountFS:Cannot do $DF
$log_archive_dir_l $dfopt $!");
        while(<DF>){
                ($total = <DF>) || &showError("$pname:getMountFS:can't
read total. $!");
                @data = split(' ',$total);
                shift(@data) if( $#data == 5);
                $mfs=$data[4];
        }

                print LOGFILE "\n the mount file system for
$log_archive_dir_l is $mfs" ;
        return($mfs);
}

#-----------------------------------------------------------------------------
# getArchTimeFromHost :
#  - gets lag times from archivelogs available from server
#    in case the info is not available in v$archived_logs
#-----------------------------------------------------------------------------
sub getArchTimeFromHost()
{
        print "-";
        print LOGFILE "-";
        my ( $instance_l,$current_seq,$arch_seq) = @_;
        my $current_archfile= &findArchFile($instance_l,$current_seq);
        my $archfile        = &findArchFile($instance_l,$arch_seq);

        &Stat("${current_archfile}");
        $current_archfile_s = $st_mtime;
        &Stat("${archfile}");
        $archfile_s = $st_mtime;

        $archfile_s = &getArchTimeFromDRhost($instance_l,$arch_seq )
if ( ! $archfile_s );
        &showError("$pname:getArchTimeFromHost:Unable to get info
about archseq $arch_seq",$instance_l)
        if ( ! $archfile_s ) ;

        $archlag_sec   = $current_archfile_s - $archfile_s ;
        return($archlag_sec);
}

#-----------------------------------------------------------------------------
# getArchTimeFromDRhost :
#  gets arch times from archivelogs available from DR server
#  in case the info is not available in v$archived_logs and on prod host
#-----------------------------------------------------------------------------
sub getArchTimeFromDRhost(){
    #print "\ngetArchTimeFromDRhost:";
    #print LOGFILE "\ngetArchTimeFromDRhost:";
    my ( $instance_l,$arch_seq) = @_;
    my $archfile_s;
    my $drarchfile_info;

    my $ssh_script = "ls -ltr
$drinfo_arr{$instance_l}{dr_log_archive_dest}*$arch_seq* |  tail -1|
tr -s ' '|";
    $ssh_script = $ssh_script."/usr/local/bin/perl -ne
'chomp(\@b=split(/ /,\$_)); print \"\$b[5]:\$b[6]:\$b[7]:\$b[8]\"' ";
    chomp($drarchfile_info=qx($SSH -qn ${remote_host} $sshopt $ssh_script)) ;
    #print "\n drarchfile_info=$drarchfile_info";

    if (  $drarchfile_info ){
       chomp(($mon,$dd,$hh,$mm,$ff) =split(/:/,$drarchfile_info));
       #print "\n == $mon,$dd,$hh,$mm,$ff ";

       my  %month=('Jan',0,'Feb',1,'Mar',2,'Apr',3,'May',4,'Jun',5,
                   'Jul',6,'Aug',7,'Sep',8,'Oct',9,'Nov',10,'Dec',11);
       my ($ssc,$mmc,$hhc,$ddc,$monc,$yyc) = (split(/:/,$cdate));
       $archfile_s=timelocal(1,$mm,$hh,$dd,$month{$mon},$yyc);
       #print "\n archfile_s=$archfile_s==\n";
   }
   return($archfile_s);
}


#-----------------------------------------------------------------------------
# checkDRhealth ;
#  - just wrapper to make code easy readable.
#  - If DR exists do switch log and
#    find sync_arch lag and dr applied log lag
#  - this is as seperate function to make code easy reading and handling
#    at main fnc .
#-----------------------------------------------------------------------------
sub checkDRhealth()
{
        #------------ DR and log Option in PROD ------------------------------#
        # do not check DR if option = nodrmonitor
        return("NO") if ( lc($opt_O) eq "nodrmonitor");
        foreach  $instance_l ( keys %dbinfo_arr ) {
           if(  $isdrhost_f eq "NO"             &&
                $drexists_f{$instance_l} eq "YES" )
           {
                 &setOraclehome($instance_l)   ;
                 &switchOracleLog($instance_l) ;
                 &getDbParameters($instance_l) ;
                 &getDRLogLag($instance_l)     ;
           }
        }
        return("YES");
}

sub checkDGhealth ()
{
 return("NO") if ( lc($opt_O) eq "nodrmonitor" or lc($opt_O) eq "nodgmonitor" );
 if ( $isdghost_f eq "NO"  && $dgexists_f{$instance_l} eq "YES" )
  {
        &setOraclehome($instance_l) ;
         &switchOracleLog($instance_l) ;
        &getDbParameters($instance_l) ;
         &getDGLogLag($instance_l) ;
  }
        return("YES") ;
}


#-----------------------------------------------------------------------------
# switchArchDestOnly:
#  wrapper sub module to provide swicth Archive dest functioanlity alone.
#  This function is same as old script sad.pl
#  The upper threshold for switching archive dest is got from cron exception
#-----------------------------------------------------------------------------
sub switchArchDestOnly()
{  my $instance = shift ;
   print "\nswitchArchDestOnly:$instance:";
   print LOGFILE "\nswitchArchDestOnly:$instance:";
   my $logdate_l=qx(date +'[%T]');chomp($logdate_l);
   print $logdate_l; print LOGFILE $logdate_l;
   foreach $mfs ( keys %mountfs){
     $archive_file_sys=$mountfs{$mfs};
     next if ( ! defined($archive_file_sys ) );
     my $archive_file_dir=(split(' ',$archive_file_sys))[0];
     print "\n archive_file_dir         = $archive_file_dir";
     print LOGFILE "\n archive_file_dir         = $archive_file_dir";

     &getParameters($mfs);
     print "\n Parameters               = $mfs:$pct_lower_limit:";
     print LOGFILE "\n Parameters               = $mfs:$pct_lower_limit:";
     print "$pct_upper_limit:$archive_retain_time:$mailto:$pageto";

     my $pct_used = &getUsedSpace($archive_file_dir);
     print "\n current %usage           = $pct_used% ";
     print LOGFILE "\n current %usage           = $pct_used% ";

    if ( $pct_used > $pct_upper_limit -1 ){
        &switchArchDest($instance);
    }
    else{
        print "\n ARCHIVE Destination NOT changed\n";
        print LOGFILE "\n ARCHIVE Destination NOT changed\n";
    }
  }
}

#-----------------------------------------------------------------------------
# findDupLogs:
#  - finds duplicate sequences/archive logs if any on a
#    multi archive dest envs.,
#  - This is fired only if isSwitch = YES ie., when multiple archive
#    dest specfied for a sad functionality
#-----------------------------------------------------------------------------
sub findDupLogs(){
  my $log_archive_dir ;
  my %archdir ;
  my $instance_node;
  #print "\n findDupLogs:$instance_l:";

  foreach $instance_l ( keys %dbinfo_arr ){
    if( $dbinfo_arr{$instance_l}{connected} eq "Y" and
        &isSwitch($instance_l)  eq "YES" ) {
        $log_archive_dir = $dbinfo_arr{$instance_l}{log_archive_dir};
        $log_archive_dir    =~ s/[0-9]+/*[0-9]/g;
        for $dir (<$log_archive_dir>) {
          for $_ (<$dir/*>) {
            #if( /${archformat}[\.gz]*$/ ){
            if(/${archformat}.gz/){
              $curr_archfile = $_;
              $curr_archdir  = $1;
              $thread        = $4;
              $instance_node = $3;
              $node_thread="${instance_node}_${thread}";

              if($got{$node_thread} and $curr_archdir ne
$prev_archdir{$node_thread}){
                print "\n findDupLogs:$instance_l:" if (! defined($pflag)) ;
                print LOGFILE "\n findDupLogs:$instance_l:" if (!
defined($pflag)) ;
                print "\n Found dup archive logs for threads:$thread";
                print LOGFILE "\n Found dup archive logs for threads:$thread";
                $curr_archsize = (stat($curr_archfile))[7];
                $prev_archsize = (stat($prev_archfile{$node_thread}))[7] ;
                print "\n  $curr_archfile(size-$curr_archsize) ";
                print LOGFILE "\n  $curr_archfile(size-$curr_archsize) ";
                print "\n  $prev_archfile{$node_thread}:(size-$prev_archsize)";
                print LOGFILE "\n
$prev_archfile{$node_thread}:(size-$prev_archsize)";
                $pflag = 1;
                if ( $curr_archsize  < $prev_archsize ){
                    print "\n  renaming... $curr_archfile ";
                    print LOGFILE "\n  renaming... $curr_archfile ";
                    rename($curr_archfile,$curr_archfile.'.dup') if
(&isOpen("${curr_archfile}") =~ /no/);
                }
                else{
                    print "\n  renaming... $prev_archfile{$node_thread}";
                    print LOGFILE "\n  renaming...
$prev_archfile{$node_thread}";

rename($prev_archfile{$node_thread},$prev_archfile{$node_thread}.'.dup')
 if ( &isOpen("$prev_archfile{$node_thread}") =~ /no/) ;
                }
               }
              push(@duplogs, $node_thread)
                        if($got{$node_thread} and $curr_archdir ne
$prev_archdir{$node_thread});
              $prev_archdir{$node_thread}  = $curr_archdir;
              $prev_archfile{$node_thread} = $curr_archfile;
              $got{$node_thread}           = 1;
            }
          }
        }
    }
 }
 print "\n";
 print LOGFILE "\n";
}

#-----------------------------------------------------------------------------
# logRotation:
#  - takes copy of log in /var/tmp and keeps logs for
#    MAXLOGCYCLE no. of days
#-----------------------------------------------------------------------------
sub logRotation(){

        $ldate  = (localtime((stat("$logfile"))[9]))[3];
        $ndate  = (localtime(time))[3];

        if ( $ldate != $ndate ){
           for (my $o=$MAXLOGCYCLE-2,$n=$MAXLOGCYCLE-1; $o >=0; $o--,$n--){
                $old=$o?"$logfile.$o":$logfile ; $new="$logfile.$n";
                `$GZIP $old` if ( -e $old );
                `$GZIP $new` if ( -e $new );
                rename "$old.gz","$new.gz" if ( -e "$old.gz" );
           }
        }
}

#-----------------------------------------------------------------------------
# checkNodrhost:
#  - This function takes care of alerts during know issues of with drhosts,
#    in case drhost is down for known time , we could stop DR alerts by
#    creating below flag ,
#       prodhost:/usr/tools/oracle/SID.nodrhost.2h
#  - By default script itself touches a 2hr flag and ignores alerts in case
#    of drhost is unavailable momentarily .
#-----------------------------------------------------------------------------
sub checkNodrhost(){
        my $instance_l       = shift ;
        my $nodrhost_noalert = 'N';
        chomp($nodrhost_f=`ls -1tr
/usr/tools/oracle/$instance_l.nodrhost.* 2>/dev/null| tail -1 `);
        if ( not $nodrhost_f ){
                return($nodrhost_noalert);
#                $nodrhost_f = "/usr/tools/oracle/$instance_l.nodrhost.2h";
#                system("touch $nodrhost_f") ;
        }
        $nodrhost_v = (split(/\./,$nodrhost_f))[2];
        &Stat("$nodrhost_f");
        $nodrhost_fs = $st_mtime;
        $nodrhost_vs = &convertTime($nodrhost_v);
        #print "\n nodrhost_f=$nodrhost_f ";
        $diff = ( time - $nodrhost_fs );
        if ( $nodrhost_vs < (time - $nodrhost_fs) ){
                system("rm /usr/tools/oracle/$instance_l.nodrhost.*
2>/dev/null" )
        }
        else{
                $nodrhost_noalert = 'Y';
        }
        return ( $nodrhost_noalert);
}

sub checkNodghost()
{

my $instance_l = shift ;
        my $nodghost_noalert = 'N';
        chomp($nodghost_f=`ls -1tr
/usr/tools/oracle/$instance_l.nodghost.* 2>/dev/null| tail -1 `);
        if ( not $nodghost_f ){
                return($nodghost_noalert);
#                $nodrhost_f = "/usr/tools/oracle/$instance_l.nodrhost.2h";
#                system("touch $nodrhost_f") ;
        }
        $nodghost_v = (split(/\./,$nodghost_f))[2];
        &Stat("$nodghost_f");
        $nodghost_fs = $st_mtime;
        $nodghost_vs = &convertTime($nodghost_v);
        #print "\n nodrhost_f=$nodrhost_f ";
        $diff = ( time - $nodghost_fs );
        if ( $nodghost_vs < (time - $nodghost_fs) ){
                system("rm /usr/tools/oracle/$instance_l.nodghost.*
2>/dev/null" )
        }
        else{
                $nodghost_noalert = 'Y';
        }
        return ( $nodghost_noalert);

}


sub mysleep() {
        my ($sleept)=@_;
        $timeleft=alarm(0);
        sleep $sleept;
        $timeleft= $timeleft - $sleept if ( $timeleft > $sleept );
        alarm($timeleft);
}

#sub checkNodghost ()
#{
#
#}
#-----------------------------------------------------------------------------
# exitProgram:
#  - exit program gracefully .
#  - removes lock file and also updates logfile
#-----------------------------------------------------------------------------
sub exitProgram($){
        &Lock::unlock("${lockfile}");
        print "\n$pname: End : ",&ctime(time),"\n";
        print LOGFILE "\n$pname: End : ",&ctime(time),"\n";
        close(LOGFILE);
        exit(shift);
}

#-----------------------------------------------------------------------------
# showError :
#  - sends alert/warning  on all errors captured .
#    one exit path for all page alerts
#  - try your best to  maintain this function at the end of this prg for
#    easy reading
#-----------------------------------------------------------------------------
sub showError
{
        my ($errmsg,$instance_l,$exit_status,$page_flag,$email_flag) = @_;
        $instance_l = $instance if( ! defined($instance_l) );
        $instance_l = "" if( $instance_l eq "NONE" );
        $page_flag  = "Y" if ( $page_flag eq "" );
        $email_flag = "Y" if ( $email_flag eq "" );
        $errmsg     = &msgfmt("w","$local_host","$instance_l","$errmsg");
        print "\n $errmsg";
        print LOGFILE "\n $errmsg";
        &getDbParameters($instance_l) if ( $mailto eq "");
        &mailit("$errmsg","/dev/null") if ( $email_flag eq "Y" );
        &pageit($errmsg) if ( $page_flag eq "Y" ) ;
        if ( $exit_status == 1 ){
                print "\n PProgram terminated ";
                print LOGFILE "\n PProgram terminated ";
                exit(1);
        }
}

#-----------------------------------------------------------------------------
# purgeNextArchive :
#  - This sub module executes ONLY if database has multiple archive destination
#  - tries to purge the next available archive destination and keep it
#    ready in case Switch archive destination occurs(sad)
#-----------------------------------------------------------------------------
sub purgeNextArchive(){
  return if( !( $instanceI ne "ALL" and
                &isSwitch($instance_l) eq "YES" and
                $dbinfo_arr{$instanceI}{connected} eq "Y"
               )
           ) ;

  print "\npurgeNextArchive:";
  print LOGFILE "\n purgeNextArchive:";
 ($next_log_archive_dest,$next_log_archive_dir)
                                   =
&getNewArchDest($dbname,$dbinfo_arr{$dbname}{log_archive_dir});
   $curr_mfs                       =
&getMountFS($dbinfo_arr{$dbname}{log_archive_dir});
   $next_mfs                       = &getMountFS("$next_log_archive_dir");
   $next_mountfs{$next_mfs}       .= $next_log_archive_dir;
   $dbinfo_arr{$dbname}{next_mfs}  = $next_mfs ;

  foreach $mfs ( keys %next_mountfs){
    $archive_file_sys=$next_mountfs{$mfs};
    next if ( ! defined($archive_file_sys ) );
    $archive_file_dir=(split(' ',$archive_file_sys))[0];
    $archive_file_dir =~ s/\*//;
    print "\n mount filesystem         = $mfs";
    print LOGFILE "\n mount filesystem         = $mfs";
    print "\n archive_file_sys         = $archive_file_dir";
    print LOGFILE "\n archive_file_sys         = $archive_file_dir";

    &getParameters($curr_mfs);
        print LOGFILE "\n percent upper limit in purgearchnext
$pct_upper_limit" ;
    $pct_upper_limit  = $pct_upper_limit-10 if ($pct_upper_limit >20);
    $pct_lower_limit = 20;
    print "\n  Parameters              = $mfs:$pct_lower_limit:";
    print LOGFILE "\n  Parameters              = $mfs:$pct_lower_limit:";
    print "$pct_upper_limit:$archive_retain_time:$mailto:$pageto";
    print LOGFILE "$pct_upper_limit:$archive_retain_time:$mailto:$pageto";
    $pct_used = &getUsedSpace($archive_file_dir);
    print "\n  Before purge:pct_used   = $pct_used% ";
    print LOGFILE "\n  Before purge:pct_used   = $pct_used% ";
    print "\n";
    print LOGFILE "\n";

    if ($pct_used >= $pct_upper_limit - 2)
    {
      open(PURGEFILES, "find ${archive_file_sys} -follow -name \"*dbf*\" |")
                        || &showError("$pname:Cannot open archive files. $!");;
      chomp(@pfiles=<PURGEFILES>);
      @spfiles=(map{$_->[0]} sort{$a->[1]<=>$b->[1]} map{[$_,(stat
$_)[9]]} @pfiles);
      foreach (@spfiles) {
         chomp($archfile=$_);
         ($db_log_archive_dir,$dbname) = $archfile =~ /${archformat}(.*)/ ;
         my $instance_l = $dbinfo_arr{$dbname}{instance};
        print LOGFILE "\n $instance_l" ;
         $archsuffix= ".gz";
         #$archsuffix= "" if ($dbinfo_arr{$instance_l}{isDataguard} eq "YES" );
         &getDbParameters($instance_l);
         $archsuffix= "(\.\*)" if ( $zipmode eq "DISABLE" );
         next if ( !/$archformat$archsuffix/ );

         &Stat("${archfile}");
         if ( (&checkDGApplied("${archfile}") eq "YES")  && ## modified for DG
             ( &checkTapeExists("${archfile}") eq "YES") &&
             ( &isOpen("${archfile}") =~ /no/)             )
         {
               if ($st_mtime >= (time - $ARCHIVE_RETAIN_SEC)){
                        $recentFiles{$dbname}=$db_log_archive_dir;
                }
                printf " (%10d)",$threadno if ( $threadno != $DEFAULT_THREAD) ;
                print LOGFILE "  ($threadno)" if ( $threadno !=
$DEFAULT_THREAD) ;
                print "  unlink:${archfile}:$pct_used %:";
                print LOGFILE "   unlink:${archfile}:$pct_used %:";
                print "\n";
                print LOGFILE "\n";
                unlink("${archfile}")
                          || print "$pname:Can't Unlink $_: $!" if (-e
${archfile});
                $dbinfo_arr{$instance_l}{purge_cnt}++;
                alarm($TIMEOUT);
                #print ".";
         }
         else {
                print "";
                print LOGFILE "";
                #print "\n No delete: ${archfile}";
         }

         $pct_used = &getUsedSpace($archive_file_dir);
         last if ($pct_used <= $pct_lower_limit);
        }
        close(PURGEFILES);
     }
     print "  After  purge:pct_used   = $pct_used% ";
     }

  foreach $db ( keys %dbinfo_arr ){
    if ( $dbinfo_arr{$db}{connected} eq "Y" ) {
       printf "\n No. of logs purged(%-8s) = %2d",$db,
$dbinfo_arr{$db}{purge_cnt};
       printf LOGFILE "\n No. of logs purged(%-8s) = %2d",$db,
$dbinfo_arr{$db}{purge_cnt};
    }
  }

}

sub getDBUniqueName()
{
        my $instance_l = shift;
        my $sqlstmt="SELECT 'DB_UNIQUE_NAME' name,DB_UNIQUE_NAME
                     FROM   v\\\$archive_dest
                     WHERE  dest_id = 1";

        open(SQLDBA, "$oracle_home/bin/sqlplus /nolog << END
        connect /as sysdba
        set heading off
        set echo on
        $sqlstmt ;
        exit
        END |") || &showError("$pname:getDBUniqueName:sqlplus error:
$!",$instance_l,1);
        my @data = <SQLDBA>;

        my @data1;
        (@data1  = grep(/^DB_UNIQUE_NAME/, @data)) ||
&showError("$pname:Can't Find db_unique_name: @data",$instance_l,1);
        my $db_unique_name = (split(' ', $data1[0]))[1];
        return($db_unique_name);

}

sub chkDatabaseRole()
{
  my $thread_file=shift;
  if (-f "$thread_file"){
    my $sqlstmt="SELECT 'DATABASE_ROLE:'||database_role||':'
                FROM   v\\\$database";
    open(SQLDBA, "$oracle_home/bin/sqlplus /nolog << END
    connect /as sysdba
    set heading off
    set echo on
    $sqlstmt ;
    exit
    END |") ;
    my @data = <SQLDBA>;

    my @data1;
    (@data1  = grep(/^DATABASE_ROLE/,@data));
    my $database_role=(split(/:/ , $data1[0]))[1];
   if ($database_role eq "PRIMARY"){
    #   qx(mv ${thread_file} ${thread_file}.not_needed_in_prod);
   }
  }
}




sub chkDatabaseRoleReturn()
{
        my $inst = shift  ;
my $cmd = <<XX ;
. ~/setdb  $inst
XX
qx($cmd) ;
        my $sqlstmt="SELECT 'DATABASE_ROLE:'||database_role||':'
                FROM   v\\\$database";
    open(SQLDB, "$ENV{ORACLE_HOME}/bin/sqlplus /nolog << END
    connect /as sysdba
    set heading off
    set echo on
    $sqlstmt ;
    exit
    END |") || die "chkDatabaseRoleReturn : unable to connect to database" ;
     my @data1,$data2  ;my @data= <SQLDB> ;close(SQLDB) ;
                print LOGFILE "\n @data" ;
    (@data1  = grep(/^DATABASE_ROLE:/,@data));
    my $database_role=(split(/:/ , $data1[0]))[1];print LOGFILE "\n
database_role in chkdbrr $database_role " ;
        chomp( $database_role) ;

   if ($database_role eq "PRIMARY"){
    #   qx(mv ${thread_file} ${thread_file}.not_needed_in_prod);
                                        }
#if ($database_role =~ /STANDBY/ ) {$database_role = "STANDBY" ;}

print LOGFILE "\n chkdatabaserolereturn ::  $database_role " ;
#/usr/tools/oracle/Standard/script/flags/{INSTANCE_NAME}_IS_STANDBY or
{INSTANCE_NAME}_IS_PRIMARY
my $status_file =  qx(ls -ltr
/usr/tools/oracle/Standard/script/flags/${inst}_IS\* ) ;
if ($status_file =~ /(.*)_IS_STANDBY/ ) { $database_role = "STANDBY" ;}
if ($status_file =~ /(.*)_IS_PRIMARY/ )  { $database_role = "PRIMARY" ;}

&showError( "$pname : chkDatabaseRoleReturn : unable to identify the
role of database " ,$instance_l) if ( ! defined($database_role)) ;

return $database_role;
}

## note: code should be written to be able to figure out   DB role
with out connecting to database.
##assuming atleast one instance that is recovery instance would be
running for standby , the Idea is to program
## SAD ZIPPING and other features only for recovery instance.
## used dg config and fal server/client information to connect to
other site and identify the role of the database .






### used by a standby .
sub checkRecoveryInst()
{
my $inst = shift ; print "\n $inst" ;
#my $cmd = <<XX;
#. ~/setdb $inst
#XX

#qx($cmd ) ;
my $sqlcmd="select process from v\$managed_standby where process like
'\%MRP\%'" ;
my $MRP_FLAG;
open(SQLDBA, "$ENV{ORACLE_HOME}/bin/sqlplus /nolog << END
CONNECT / AS SYSDBA
$sqlcmd ;
exit
END |") || die "CheckRecoveryInst() :unable to connect to database and
get process info" ;
while(<SQLDBA>)
{
if(/MRP/)
 { $MRP_FLAG="TRUE" ;}
}
close(SQLDBA) ;
my @tempstr = qx( ps -ef|grep ora_mrp ) ;
if ( @tempstr =~ /$instance_l/ ) { $MRP_FLAG = "TRUE" ; }
$MRP_FLAG = "FALSE" if (! defined($MRP_FLAG)) ;

return $MRP_FLAG ;
}
## used by primary

sub getRecoveryStandbynode()

{

# get from log _archive_dest 2 and compare with the remote_sys
parameter to check if its a DR , if its a DR get the
log_archive_dest_3 and check if its a DG

my $rec_node ;my $rec_inst ;my $rec_instno ;
 if ($standby_host[0] ne $remote_host ) { $rec_node = $standby_host[0]
;$rec_inst = $standby_inst[0] ; $rec_instno = $standby_instno[0] ;}
elsif ( $standby_host[1] ne $remote_host ) { $rec_node =
$standby_host[1] ;$rec_inst = $standby_inst[1] ;$rec_instno =
$standby_instno[1] ;}
### check if rec node is one of the DGs
#chomp($rec_node);
print LOGFILE "\n recovery node info $rec_node $rec_inst $rec_instno" ;

### additional check for  recovery
 my @rec_check = qx( $SSH -qn $rec_node $ssh_opt  "ps -ef|grep mrp" ) ;
my $cnt=0 ;my $flag= "FALSE" ;my $flag1 = "FALSE" ;
while($rec_check[$cnt]) { if ( $rec_check[$cnt] =~
/ora_mrp(\d)_${db_name}(.*)/) { $flag="TRUE" ;} $cnt++; }
print LOGFILE "\n rec flag $flag" ;
my $sqlcmd = "select process from v\\\$managed_standby  " ;
print LOGFILE $sqlcmd ;
#my @res_set = &conStandby($rec_node, $rec_inst, $sqlcmd ) ;
#$cnt = 0 ;my $teststr ;
#while (defined($res_set[$cnt])) { if ($res_set[$cnt] =~
/(\s*)MRP(.*)/) { $flag1 = "TRUE" ;last ;} $cnt++ ;}
#print LOGFILE "\n rec flag 2 $flag1" ;
  if ($flag eq "TRUE"  ) {return ($rec_node, $rec_inst, $rec_instno)
;} else { return  "" ;}

}





#####  conStandby ( $hostname , $instancename , $sqlstatement )
sub getStandbyThreadInfo()
{
my $inst = shift ;
$ENV{ORACLE_SID} = $inst ;
print LOGFILE "  this is the inst $inst   home " ;  # set ORACLE_SID as needed
delete $ENV{TWO_TASK};      # make sure TWO_TASK isn't set
my $dsn = "dbi:Oracle:"; my @threadinfo ;
eval {
my $dbh = DBI->connect( $dsn, '', '',{ ora_session_mode => 2 }
#{ ora_session_modes =>  [ qw( ORA_SYSDBA ORA_SYSOPER ) ]  }
                         ) || die "Database connection not made: ";
$dbh->{AutoCommit}    = 0;
$dbh->{RaiseError}    = 1;
my $sql_stmt = 'select distinct thread#  from v$archived_log ' ;
my $exec_stmt = $dbh->prepare($sql_stmt) ;
#$exec_stmt->bind_param(":PARM",$parm) ;
$exec_stmt->execute() ;my $cnt = 0;
while ($parm_value = $exec_stmt->fetchrow_array()){ print LOGFILE
$parm_value ;$threadinfo[$cnt]=$parm_value ;print LOGFILE
$threadinfo[$cnt] ;$cnt++ ;}
#$parm_value = chomp ($exec_stmt->fetchrow_array()) ;
#chomp($parm_value) ;
#return $parm_value ;
$exec_stmt->finish() ;
$dbh->disconnect() ;
};
warn $@ if $@ ;$cnt-- ; print "\n  $threadinfo[0]" ;
#if( defined($threadinfo[0])) { return  @threadinfo ;}else { print
LOGFILE "IN ELSE BLOCK OF GETSTANDBY THREAD " ;return ;}
return @threadinfo ;
}





sub conStandby()
{
 my  ($host1, $inst , $sqlcmd) = @_ ;
print LOGFILE "\n connecting to standby $host1 $inst $sqlcmd " ;
print LOGFILE "\n $sqlcmd" ;
 $sshcmd= <<XX ;
export \$TERM=""
export \$SETDB_ASK=Y
. ~/setdb $inst
echo \$ORACLE_HOME
sqlplus /nolog <<YY
connect / as sysdba
set heading off
set pagesize 100
set linesize 500
$sqlcmd ;
exit
YY
XX
#$host1 = qw(${host1}) ;
@sqlout = qx($SSH -qn $host1 $sshcmd  <<ZZ
exit
ZZ ) || die "unable to connect" ;

print LOGFILE "\n  @sqlout" ;
@sqloutput = split( /\n/,@sqlout ) ;
$cnt=0;
while (!($sqloutput[$cnt] =~ /SQL\>/ ))
{$cnt++ ;}
while ($sqloutput[$cnt] =~ /SQL\>/ )
{$cnt++ ;} $cnt3=0; @sqloutr;
while (!($sqloutput[$cnt] =~ /SQL\>/ ))
{  $sqloutr[$cnt3]= $sqloutput[$cnt]  ; $cnt++;$cnt3++;}

return @sqloutr ;
}






sub getStandbyArchdest()
{
## get from standby initfile or

my ($hostname , $inst ) = @_ ; my $standby_dest ;
## get from connecting to standby
my $sqlcmd = qw(select 'STANDBY_ARCHIVE_DEST:' value from v$parameter
where upper(name) = 'STANDBY_ARCHIVE_DEST' ) ;
my @sqlout = &conStandby ($hostname, $inst, $sqlcmd) ;
my $cnt =0;
while ($sqlout[$cnt]) { if ($sqlout[$cnt] =~ /^STANDBY_ARCHIVE_DEST/)
{  chomp($standby_dest = (split(':',$sqlout[$cnt]))[1]) ;}
last if(defined($standby_dest)) ;  }

return $standby_dest ;
}



sub mvdc_check_inst( )
{


#my $argst = "" ;my $i ;
#for( $i=0;$i<=$#ARGV;$i++)
#{ $argst= $argst.$ARGV[$i]." ";
#  if($ARGV[$i] =~ /-i/) { $instance = $ARGV[$i];}
#}
# my $instance =~ s/-i// ;


my $instance  = shift  ;
my $pname="archivelog_utl.pl" ;
#($sec,$min,$hour,$mday,$mon,$year,$wday,
#$yday,$isdst)=localtime(time);
#$year=$year+1900;
#$mon=$mon+1 ;


# my $lockfile= "$pname.$instance.mvdc_check";
# my $logfile="/var/tmp/${lockfile}_$year.$mon.$mday.$hour.$min.$sec.LOG" ;
#open(LOGFILE, ">>${logfile}") || die "Cannot open logfile $logfile. $!\n";
#        LOGFILE->autoflush(1);
        print "\n$pname: $instance mvdc check Started : ",&ctime(time);
        print LOGFILE "\n$pname: $instance  mvdccheck Started : ",&ctime(time);

print LOGFILE "\n argument $argst" ;
 my $sync_arch_path="/usr/tools/oracle/sync_arch/adm" ;
 my $sync_arch_file ;
my $racdb_flag =&getDBParmFile("cluster_database", $instance);# if
(!defined($racdb_flag)) ;
print LOGFILE "\n cluster database $racdb_flag" ;
chomp($racdb_flag);
my $instance_number=&getDBParmFile("INSTANCE_NUMBER", $instance);# if
(!defined($instance_number)) ;
chomp($instance_number);
print LOGFILE "\n instance parameter $instance_number" ;
my $database = uc(&getDBParmFile("db_name",$instance)) ;#if
(!defined($database)) ;
chomp($database);
print LOGFILE  "\n database parameter $database" ;
my $mvdc_flag ;

#$sync_arch_file  = "$sync_arch_${database}.cfg";

if( uc($racdb_flag) eq "TRUE" )
         {  $sync_arch_file  =
"sync_arch_".$database."_thread".$instance_number.".cfg";
print LOGFILE "\n sync file $sync_arch_path/$sync_arch_file" ;
         }
else
        {
                $sync_arch_file  = "sync_arch_".$database.".cfg"
if(!-f "$sync_arch_path/$sync_arch_file");
        }

print LOGFILE "\n  mvdc_check(): NO SYNC CONFIG FILE"   if(!-f
"$sync_arch_path/$sync_arch_file") ;


#print LOGFILE "\n mvdc_check() : CONFIG FILE IS IN SINGLE INSTANCE
FORMAT WHEN THE DATABASE IS RAC"
if ( -f "$sync_arch_path/$sync_arch_file"   )
{
open (CFGFILE, "$sync_arch_path/$sync_arch_file") ||
&showError("$pname: mvdc_check() : Can't Open
$sync_arch_path/$sync_arch_file ",$instance);

while(<CFGFILE>){
if(/^mvdc_enabled/) {
chomp($mvdc_flag=(split('='))[1]) ;
} }

close(CFGFILE) ;}
if ( !defined($mvdc_flag)) { print LOGFILE "\n mvdc_check() :
MVDC_ENABLED PARAMETER IS NOT PRESENT IN CFG FILE, Therefore its
considered to be a non MVDC database" ; }

## get DG init parms from database
## if the value cannot be obtained from DB ,since DB  could be down,
get it from Init.ora file
#$dg_broker_start= lc(&getDBParm("dg_broker_start")) ;
$dg_broker_start= &getDBParmFile("dg_broker_start", $instance ) ; #if
(! defined($dg_broker_start)) ;
chomp($dg_broker_start);
print LOGFILE "\n dg_broker_start status $dg_broker_start" ;
#$log_archive_config= lc(&getDBParm("log_archive_config"));
$log_archive_config= &getDBParmFile("log_archive_config", $instance);#
if (! defined($log_archive_config));
print LOGFILE "\n  log archive config status $log_archive_config" ;
chomp($log_archive_config);
print LOGFILE "\n mvdc flag $mvdc_flag  log broker start
$dg_broker_start log archive config $log_archive_config" ;
if( uc($mvdc_flag) eq  "TRUE" and uc($dg_broker_start) eq "TRUE" and
lc($log_archive_config) =~ /dg_config/i )
{
print LOGFILE "\n $instance : mvdc check is satisfied and now calling
mvdc archive util script" ;
print  "\n $instance :mvdc check is satisfied and now calling mvdc
archive util script" ;
#my $cmd= "./mvdc_archivelog_utl.pl ".$argst ; print "\n $cmd" ;
#qx($cmd);
close(LOGFILE) ;
return "TRUE" ;
#exit(0) ;
}
elsif (uc($mvdc_flag) eq  "TRUE" or uc($dg_broker_start) eq "TRUE" or
lc($log_archive_config) =~ /dg_config/i )
{ return "NULL" ;}
 else { return "FALSE" ;}
undef($pname ) ;
undef($instance);
undef($logfile);
undef($lockfile);
undef($sync_arch_file);
undef($sync_arch_path);
undef($instance_number) ;
print "\n $instance: end of mvdc ,mvdc not found, proceeding to
original script" ;
} # end of mvdc_check()





#### subroutine to return spfile if its available otherwise returns pfile
sub checkSPFile()
{

my $db_name = shift ;
# Returns spfile if its preesent otherwise returns Init.ora file
my $spfile ;my $initfile ;
my $ohome ;
my $oratab = "/var/opt/oracle/oratab" ; # only linux supported need to
check for the script if there is other module for /etc/oratab and
oracle home identification

########################## use oratab to find the initSID.ora file :Begin
if ( -f $oratab ) {
open (ORATABF,"$oratab") || &showError("$pname: mvdc_check(): Can't
Open $oratab",$instance) ;
}
else { print LOGFILE "\n mvdc_check(): unable to fined oratab file" ;
# program should exit at this point
}

while(<ORATABF>)
{
#if(/^spfile/)
#{ chomp($spfile=(split('='))[1]) ; }
if(/^${db_name}/){chomp($ohome=(split(/:/))[1]) ;}
}
print LOGFILE "\n $db_name" ;
print LOGFILE "\n ORACLE Home $ohome" ;
close(ORATABF) ;
&showError("$pname :$db_name : unable to find oracle home ",$db_name,
1) if (! defined($ohome))  ;
##### use oratab to find the initSID.ora file :End
$initfile= "${ohome}/dbs/init${db_name}.ora" ;

$spfile= "${ohome}/dbs/spfile${db_name}.ora"  ;
#if (-f $initfile )
#{ open(INITF,"$initfile")||  &showError("$pname: mvdc_check():cant
open initfile for this database ",$instance);
#
#while(<INITF>)
#{ if (/spfile=/) { chomp($spfile=(split('='))[1]);} }
#undef($spfile) if(! -r $spfile);
#
#close(INITF) ;
#}

if ( -f $spfile )
{       return ("TRUE", $spfile) ; }
elsif  (-f $initfile)
{ return ("FALSE", $initfile ) ; }
else
{  &showError ("$pname : $db_name : theres neither spfile not initfile
",$db_name,1) ; }



#if (defined($spfile))
#{ return ("TRUE", $spfile); }
#else { return ("FALSE", $initfile) ;}

} ##### SUB ROUTINE SPFILE CHECK ENDS


sub checkSPFromInit()
{
my $initfile = shift ;$initfile =~ /(.*)init(\w+).ora/ ;
my $instance = $2 ;
if (-f $initfile )
{               open(INITF,"$initfile")||
&showError("$pname:checkspfromInit() :cant open initfile for this
database ",$instance);
                while(<INITF>)
                        {               if (/(.*)spfile(\s*)=/ and
!/^#/ ) { chomp($spfile=(split('='))[1]);

  undef($spfile) if(! -r $spfile);

 &showError("$pname : spfilecheck() unable to read spfile
",$db_name,1)  if ( ! -r $spfile)                               ;

                        }                                               }
                close(INITF) ;
}

if (defined($spfile))
        { return ( $spfile); }
        else { return ( $initfile) ;}


}



sub getStandbyDBParmFile()
{
my ($shost, $sinst , $parm ) = @_ ;
my $parm_value ; chomp($parm) ; chomp($sinst) ;chomp($shost) ; my
$flag1 = "FALSE" ; my $flag2 = "FALSE" ;
my $parm_val1, $parm_val2 ; my $parm1 = uc($parm) ;  my $inst =
uc($sinst) ;my $inst1 = lc($sinst) ;
my $standby_ohome = qx($SSH -qn $shost $sshopt "cat
/var/opt/oracle/oratab | grep -v \"^#\" |grep $sinst" );
$standby_ohome = (split (':', $standby_ohome ))[1] ;
&showError("$pname : getStandbyDB  unable to get standby home from
/etc/oratab",$sinst) if (! defined($standby_ohome)) ;
 my $standby_init ;
 my $standby_initfile = qx($SSH  -qn $shost $sshopt "ls
${standby_ohome}/dbs/init${sinst}.ora  ") ;
 my $standby_spfile = qx( $SSH -qn $shost $sshopt "ls
${standby_ohome}/dbs/spfile${sinst}.ora ") ;
my $nofile = "No such file or directory" ;
if (!($standby_spfile =~ /$nofile/)) { $standby_init = $standby_spfile ;}
elsif ( ! ($standby_initfile =~ /$nofile/)){ $standby_init =
$standby_initfile ;}
else { &showError("$pname: $instanceI no spfile or init file on
standby", $instanceI, 1) ; }

#if ( defined($standby_initfile) )
#       {       if ($standby_initfile = /(.*)spfile(\s*)=(.*)/)
#                   {  $standby_init = $3 ; }
#        }
#$standby_init =  "${standby_ohome}/dbs/init${sinst}.ora"  if ( !
defined($standby_init) ) ;
print LOGFILE "\n standby init $standby_init" ;

open( STANDBYINIT, "$SSH -qn  $shost  $sshopt cat $standby_init | strings | ") ;
while(<STANDBYINIT>)
        {
        # print LOGFILE "\n $_ " ;
                next if (/^#/) ;
                if(/\*.${parm}(\s*)=(.*)/) { $parm_val1 = $2 ; $flag1
= "TRUE" ; }
                if(/${inst}.${parm}(\s*)=(.*)/) { $parm_val2 = $2 ;
$flag2 = "TRUE" ;}
                if(/\*.${parm1}(\s*)=(.*)/) { $parm_val1 = $2 ; $flag1
= "TRUE" ; }
                if(/${inst}.${parm1}(\s*)=(.*)/) {  $parm_val2 = $2 ;
$flag2 = "TRUE" ;}
                if(/${inst1}.${parm}(\s*)=(.*)/)  { $parm_val2 = $2 ;
$flag2 = "TRUE" ;}
                if(/${inst1}.${parm1}(\s*)=(.*)/)  { $parm_val2 = $2 ;
$flag2 = "TRUE" ;}
        }
        close (STANDBYINIT) ;


        if ($flag2 eq "TRUE" ) { $parm_value = $parm_val2 ; } elsif (
$flag1 eq "TRUE" ) { $parm_value = $parm_val1 ;}
        else { &showError("$pname: $inst unable to find parm  $parm
",$inst, 1) ; }

#my $parmcnt = qx( $SSH  -qn $shost  $sshopt "cat $standby_init |
strings |  grep -v \"^#\" | grep $parm  | wc -l  " );
#if ( $parmcnt > 1)
#               {       #print LOGFILE "\n $parm
#                       $parm_value= qx( $SSH  -qn $shost  $sshopt
"cat $standby_init | strings | grep -v \"^#\" |  grep $sinst | grep
$parm " );
#                       print LOGFILE "\n parm value after parmcnt > 1
$parm_value" ;
#                       $parm_value =~ s/'//g ;$parm_value =~ s/ //g ;
#                        print LOGFILE "\n parm value after parmcnt >
1 $parm_value" ;
#                       if(! ($parm_value =~ /$sinst.$parm=(.*)/) )
#                               { &showError("$pname : getStandbyDB
unable to find parm as the entry is not in right format $parm , the
standby node is $shost ",$sinst) ;                     }
#                       else {   $parm_value = $1 ; print LOGFILE "\n
standby init parameter $parm and value $parm_value" ; }
#
#               }
# else          {
#                  &showError("$pname : getStandbyDB  unable to find
standby parm $parm in standby node $shost  ",$sinst ) if ($parmcnt ==
0 ) ;
#                 $parm_value= qx( $SSH  -qn $shost  $sshopt "cat
$standby_init | strings |  grep -v \"^#\" | grep $parm ") ;
#                 $parm_value = (split('=',$parm_value))[1] ;
#               }
chomp($parm_value) ;print LOGFILE "\n parm value from
StandbyDBParmFile is $parm_value" ;
return $parm_value ;

}
######## getDBParmFile() get init parameters from spfile if its in use
,if its not present then init.ora file is used
#sub getDBParmFile()
#{
#
#my ($parm,$inst) =@_ ;
#print LOGFILE  "\n $parm $inst" ;
#my $parm_value ;
#my ($spfile_flag, $parm_file) = &checkSPFile($inst) ;# get spfile
name from checkSPFile()
#print LOGFILE "\n spfilestatus $spfile_flag   parameterfile  $parm_file" ;
#my $parm1 ;
## $parm1= lc(".".$parm."=") ;
#if( $spfile_flag eq  "TRUE" )
#{
##print "\n entering if block" ;
##my $cmd="cat ".$spfile."|strings|tr \'[:upper:]\' \'[:lower:]\'|
grep \"".$parm1."\"" ;
#my $cmd = "cat $spfile | strings | grep
#my $temp=qx($cmd) ;
#my @parm_values=split('=', $temp) ;
#$parm_value=$parm_values[1] ;
# }
#else {
#open (INITFILE, $parm_file)|| &showError("$pname: getDBParmFile
:cannot open initfile",$inst  ) ;
#while (<INITFILE>)
#{
#
#tr/[A-Z]/[a-z]/ ;
#s/['"]//g ;
##$parm1 = lc($parm1) ;
#my @tempstr ; my $cnt5 ;
#if (/${parm}(\s*)=(.*)/i) { $parm_value = $2 ;
##               =split('=');
#  print LOGFILE "\n parameter value from init file $parm_value" ;}
##$parm1= uc($parm1);
##if (/${parm1}/ and ! defined($parm_value)) { $parm_value
=(split('='))[1]; print "\n parameter value from init file
$parm_value" ;}
#}
#close(INITFILE) ;

# }

#return $parm_value ;
#}

sub getDBParmFile()
{

my ($parm,$inst) =@_ ;
print LOGFILE  "\n $parm $inst" ;
chomp($parm) ; $parm =~ s/ //g ;
chomp($inst) ; $inst =~ s/ //g ; $inst = uc($inst) ; $inst1 = lc($inst) ;
my $parm_value ; my $parm_val1; $parm_val2 ;my $flag1 = "FALSE" ; my
$flag2 = "FALSE" ;
my ($spfile_flag, $parm_file) = &checkSPFile($inst) ;# get spfile name
from checkSPFile()
print LOGFILE "\n spfilestatus $spfile_flag   parameterfile  $parm_file" ;
my $parm1=uc($parm) ; my  $spfile  ;
# $parm1= lc(".".$parm."=") ;
if( $spfile_flag eq  "TRUE" )
{
        $spfile = $parm_file ;
        my  $spname = "/var/tmp/${inst}spfile.tmp" ;
        qx(touch $spname) if (! -f $spname) ;
        qx( cat $spfile | strings > $spname) ;
#        my $cmd="cat $spname | strings | grep $parm1 | wc -l " ;
        open(SPFILE, $spname) || &showError("$pname: $inst unable to
open spfile",$inst, 1) ;
        while(<SPFILE>)
        {
        # print LOGFILE "\n $_ " ;
                if(/\*.${parm}(\s*)=(.*)/) { $parm_val1 = $2 ; $flag1
= "TRUE" ; }
                if(/${inst}.${parm}(\s*)=(.*)/) { $parm_val2 = $2 ;
$flag2 = "TRUE" ;}
                if(/\*.${parm1}(\s*)=(.*)/) { $parm_val1 = $2 ; $flag1
= "TRUE" ; }
                if(/${inst}.${parm1}(\s*)=(.*)/) {  $parm_val2 = $2 ;
$flag2 = "TRUE" ;}
                if(/${inst1}.${parm}(\s*)=(.*)/)  { $parm_val2 = $2 ;
$flag2 = "TRUE" ;}
                if(/${inst1}.${parm1}(\s*)=(.*)/)  { $parm_val2 = $2 ;
$flag2 = "TRUE" ;}
        }
        close (SPFILE) ;

        if ($flag2 eq "TRUE" ) { $parm_value = $parm_val2 ; } elsif (
$flag1 eq "TRUE" ) { $parm_value = $parm_val1 ;}
        else { &showError("$pname: $inst unable to find parm  $parm
",$inst, 1) ; }
 #       my $temp=qx($cmd) ; my $temp1 ;
 #       print LOGFILE "\n temp count $temp" ;
        unlink($spname) ;

}
else {
        #$parm1 = ".".$parm ;
       # my $cmd="cat $parm_file | strings | grep $parm1 | wc -l " ;
       # my $temp=qx($cmd) ; my $temp1 ;
        my $ifile ;
        open (INITFILE, $parm_file)|| &showError("$pname:
getDBParmFile :cannot open initfile",$inst  ) ;

        while (<INITFILE>)
        {

                 if(/\*.${parm}(\s*)=(.*)/) { $parm_val1 = $2 ; $flag1
= "TRUE" ; }
                  if(/${inst}.${parm}(\s*)=(.*)/) { $parm_val2 = $2 ;
$flag2 = "TRUE" ;}
                if(/\*.${parm1}(\s*)=(.*)/) { $parm_val1 = $2 ; $flag1
= "TRUE" ; }
                if(/${inst}.${parm1}(\s*)=(.*)/) {  $parm_val2 = $2 ;
$flag2 = "TRUE" ;}
                if(/${inst1}.${parm}(\s*)=(.*)/)  { $parm_val2 = $2 ;
$flag2 = "TRUE" ;}
                if(/${inst1}.${parm1}(\s*)=(.*)/)  { $parm_val2 = $2 ;
$flag2 = "TRUE" ;}
                if(/ifile/) {  $ifile=(split('='))[1] ; chomp($ifile) ; }

        }
        close(INITFILE) ;
         if ( -f $ifile)
        {   open (INITFILE, $ifile) ||&showError("$pname:
getDBParmFile :cannot open initfile",$inst  ) ;

                        while (<INITFILE>)
                        {

                                 if(/\*.${parm}(\s*)=(.*)/) {
$parm_val1 = $2 ; $flag1 = "TRUE" ; }
                                  if(/${inst}.${parm}(\s*)=(.*)/) {
$parm_val2 = $2 ; $flag2 = "TRUE" ;}
                                if(/\*.${parm1}(\s*)=(.*)/) {
$parm_val1 = $2 ; $flag1 = "TRUE" ; }
                                if(/${inst}.${parm1}(\s*)=(.*)/) {
$parm_val2 = $2 ; $flag2 = "TRUE" ;}
                                if(/${inst1}.${parm}(\s*)=(.*)/)  {
$parm_val2 = $2 ; $flag2 = "TRUE" ;}
                                if(/${inst1}.${parm1}(\s*)=(.*)/)  {
$parm_val2 = $2 ; $flag2 = "TRUE" ;}
                                if(/ifile/) {  $ifile=(split('='))[1]
; chomp($ifile) ; }

                        }
                close(INITFILE) ;

        }



        if ($flag2 eq "TRUE" ) { $parm_value = $parm_val2 ; } elsif (
$flag1 eq "TRUE" ) { $parm_value = $parm_val1 ;}
        else { &showError("$pname: $inst unable to find parm  $parm
",$inst, 1) ; }



 }


chomp($parm_value) ;
$parm_value = (split('#',$parm_value))[0] ;
$parm_value =~ s/['"]//g ;
return $parm_value ;
}





##### subroutine to get Init Parms from Database : written for MVDC
sub getDBParm()
{

my $inst =$instance ;
my $parm = shift ;
my $parm_value ;
my $dsn = "dbi:Oracle:";       # no dbname here
$ENV{ORACLE_SID} = $inst ;  # set ORACLE_SID as needed
delete $ENV{TWO_TASK};      # make sure TWO_TASK isn't set
eval {
my $dbh = DBI->connect( $dsn, '', '',{ora_session_mode => 2}
#{ ora_session_modes =>  [ qw( ORA_SYSDBA ORA_SYSOPER ) ]  }
                         ) || die "Database connection not made: ";
$db->{AutoCommit}    = 0;
$db->{RaiseError}    = 1;
my $sql_stmt = 'select value from v$parameter where name = :PARM' ;
my $exec_stmt = $dbh->prepare($sql_stmt) ;
$exec_stmt->bind_param(":PARM",$parm) ;
$exec_stmt->execute() ;
$parm_value = $exec_stmt->fetchrow_array();
#$parm_value = chomp ($exec_stmt->fetchrow_array()) ;
chomp($parm_value) ;
#return $parm_value ;
$exec_stmt->finish() ;
$dbh->disconnect() ;
};
warn $@ if $@ ;
if( defined($parm_value)) { return  $parm_value ;}else {return "" ;}
}
##### sub routine getDBParm ends
#} ## NEED TO resolve this issue
 c6-a1-db-svl-01 DGLIAS1
/usr/tools/oracle/Standard/script
A
A
A
A
A
A
A
A
A
A
A
A

