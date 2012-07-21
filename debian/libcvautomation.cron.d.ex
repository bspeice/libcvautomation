#
# Regular cron jobs for the libcvautomation package
#
0 4	* * *	root	[ -x /usr/bin/libcvautomation_maintenance ] && /usr/bin/libcvautomation_maintenance
