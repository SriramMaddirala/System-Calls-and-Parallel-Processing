#!/bin/bash

#---------------------------------------------------------------------
# CSci 4061 Fall 2017
# Assignment# 1
# This work must be done individually.
# Student name: Sriram Maddirala
# Student:5014900
# x500 id: maddi011@umn.edu
# Operating system on which you tested your code: Linux
# CSELABS machine: KH4250-11.cselabs.umn.edu
#---------------------------------------------------------------------


echo " "

######################
# Directives for usage

 if [ $argv == 0 ]
   then
    output="Process argument missing \n"
    echo -e $output
   else
    output="SELECT THE FUNCTION YOU WANT TO EXECUTE: \n"
    echo -e $output
    output="1. Search for files"
    echo -e $output
    output="2. Calculate total length"
    echo -e $output
    output="3. Find zero length files"
    echo -e $output
    output="4. Create backup files"
    echo -e $output
    output="5. Exit"
    echo -e $output

 fi

  echo -e "\nEnter option "
  read option

#  echo $option

  case "$option" in

	1)  echo "Searching for files"
	   #here you should implement for search files
	    # Begin Code
	    #Prompt user for directory
		echo “Enter Directory: “
	    #Read the parameter
		read directory
	    #Check that directory name is valid
		if  test -d "$directory"
		  then
        #Prompt for and read file name
			     echo “Enter File Name: “
		       read filename
           # find the file path
         filefind="$(find $directory -name "$filename")"
       #check if file exists
		           if [ $filefind ]; then
                 #check if file is directory
			              if test -d "$filefind"
                    then
                      #if file is directory list in appropriate fashion
			                   ls -ld $filefind
                       fi
                       #check if file is regular file
			              if test -f "$filefind"
                    then
                      #if file is regular file list in appropriate fashion
                      ls -l $filefind
		                 fi
                          else
                            #output error statement for Non-existent file
		                          echo “File does not exist”
		fi
		else
      #output error statement for Non-existent directory
		echo “Directory does not exist”
		fi
	    #End Code
	    ;;
	2)  echo "Calculating total of the size of all files in the directory tree"
	    #here you should implement the code to calculate the size of all files in a folder
	    # Begin Code
	    #Step 1: make recursive function for directory
		size_directory(){
      #change file permissions to allow different directories to be passed
      chmod 700 $1
            # iterate through the contents of directory
		for file in $(ls "$1"); do
      #check if directory
		 if test -d "$file"; then
			# if directory then add recursive-call on that directory
       size_directory $file $accumsum
		   else
         # if file then find size of file
        size=$(stat -c '%s' $(find $1 -name "$file"));
        #add it to the accumulator
      accumsum=$(($accumsum + $size))
    fi
  done
  }
  #prompt for directory
  echo "Enter Directory: "
  #read directory
  read currentdirec
  #check if directory :will not work if directory is not accessible through current directory; I don't think that was requested in assignment
  if  test -d "$currentdirec"
  then
  #call function with accumulator and directory
		size_directory $currentdirec $accumsum
    #output size
		echo "The Total Size of this directory is: $accumsum"
  else
    #output error due to inaccessible or invalid Directory
    echo "Invalid Directory"
  fi
	    #End Code
	    ;;

	3) echo "Finding zero length files"
	    #here you should implement the code to find empty files
	    # Begin Code
	    #Prompt for directory
		echo “Enter Directory: “
	    # read directory
		read directory
	    # check directory exists
	if  test -d "$directory"
	 then
    #Find all regular files that are empty and print
    find $directory -type f -empty
  else
    # Return invalid input statement
    echo "Non-existent Directory"
  fi
	    #End Code
	    ;;

	 4) echo  "Creating backup files"
	    #here you should implement the backup code
	    # Begin Code
	    #step 1 ask for directory
		echo “Enter Directory: “
	    #step 2 read directory
		read directory
    #check directory
    if test -d "$directory"
    then
		# ask for file and read
		echo “Enter File Name: “
		read filename
    #find specified file in directory
  filefind="$(find $directory -name "$filename")"
  #check file exists
    if [ $filefind ]; then
      #make sure you have proper permissions for file
    chmod 700 $filefind
			# check if file is regular or directory
				if test -d $filefind; then
				# if file is directory then check if it has backup directory exists
					if test -d $filefind.bak; then
            #check if it differs
            if diff -q $filefind $filefind.bak; then
						# if it doesn’t differ then report same backup
							echo “Already has backup that has no difference”
            else
					# if exists and differs then move existing backup to new name with date appended
						mv -f $filefind.bak $filefind.bak-"$(date +"%m-%d-%y-%r")"
				 	 #make backup directory
            mkdir $filefind.bak
            #then recursively copy all filenames and directories inside it to the backup
            cp -R $filefind $filefind.bak
						echo “Backup directory exists, made new Backup and moved old one to date appended destination”
            #print pathname
            echo "$filefind.bak"
          fi
					else
            #make backup directory
          mkdir $filefind.bak
          #  if none then recursively copy all filenames and directories inside it to the backup
          cp -R $filefind $filefind.bak
						echo "$filefind.bak"
					fi
					# if file is regular check if it has backup
					else
						if test -e $filefind.bak; then
					# if it has backup check if backup differs (for some reason my code doesn’t seem to work when backup directory exists)
						if diff -q $filefind $filefind.bak; then
						# if it doesn’t differ then report same backup
							echo “Already has backup that has no difference”
            else
						# if it differs move existing backup to new name with date appended and report that
							mv -f $filefind.bak $filefind.bak-$(date +”%m-%d-%y-%r”)
							echo “Backup directory exists, made new Backup and moved old one to date appended destination”
							# then create backup and print full pathname of original file
							cp -R $filefind $filefind.bak
							echo "$filefind.bak"
            fi
          else
					# if it doesn’t have backup create new file
              touch $filefind.bak
              #backup and print full pathname of original file
              cp -R $filefind $filefind.bak
							echo “No existing backup. Created Backup”
							echo "$filefind.bak"
            fi
        fi
  else
    #if file is invalid print error statement
   echo "Invalid file"
  fi
  else
    #if directory is invalid print error statement
    echo "Invalid Directory"
  fi
	    #End Code
	    ;;
	5) echo "Exiting the program. Thanks"
	  exit
	  ;;
   esac
