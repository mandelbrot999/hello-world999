Subversion treats these scripts as binary files (presumably due to the lack
of file extension).  If these scripts are edited on a Windows machine,
"dos2unix" or a similar utility must be used to convert the line endings
before committing.  Otherwise, if the files are checked out on a Linux server,
the anomalous line endings will prevent the scripts from running as expected.
