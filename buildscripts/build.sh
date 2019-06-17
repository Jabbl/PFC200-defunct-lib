#!/bin/sh
set -e

#function to display commands 
exe() { /bin/echo -e "\e[1;36m\$ $@ \\e[0m" ; "$@" ; }

# Function for verifying numerical arguments
IS_NUMERICAL() {
		if ! [ $2 ]
		then
			/bin/echo -e "\e[91m$1 needs a number \e[0m" 
			exit 1
		fi
		if ! [ "$2" -eq "$2" ] 2> /dev/null
		then
			/bin/echo -e "\e[91mSyntax error: \""$2"\" is not a number \\e[0m" 
			exit 1 
		fi
		/bin/echo -e "\e[1;36m$1 set to $2\\e[0m"
		}

# Absolute path to this script, e.g. /home/user/bin/foo.sh
SCRIPT=$(readlink -f "$0")

# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=$(dirname "$SCRIPT")
PARENTDIR=$(dirname "$SCRIPTPATH")

# Path to output result to
OUTPATH=$PARENTDIR/publish
USERNAME=
PASSWORD=
RESULT=BACnet-dev-newest.ipk
QUIET_INTERNAL=

while [ $1 ]; do
	case $1 in
		-f | --filename)
			shift
			RESULT=$(echo "$1" | sed 's:/*$::')
			/bin/echo -e "\e[1;36mFilename set to \""$RESULT"\"\\e[0m";;
			
		-q | --quiet)
			IS_NUMERICAL $1 $2
			if [ $2 -eq 1 ]
			then
				QUIET_INTERNAL="-q"
				/bin/echo -e "\e[1;36mSuppressing output\\e[0m"
			else
				/bin/echo -e "\e[1;36mShowing all output\\e[0m"
			fi 
			shift ;;
			
		-o | --output)
			shift
			OUTPATH=$(echo "$1" | sed 's:/*$::')
			if  [ ! -d $OUTPATH ]
			then
				mkdir -p $OUTPATH
			fi
			/bin/echo -e "\e[1;36mOutput path set to \""$OUTPATH"\"\\e[0m";;
			
		-*)
			/bin/echo ""
			/bin/echo "AVAILABLE ARGUMENTS:"
			/bin/echo "-o /foo/bar  --output /foo/bar  Set output directory (defaults to \"path_to_build_sh/publish\")"
			/bin/echo "-q [0/1]     --quiet [0/1]      0: show output, 1: remove output (defaults to 0)"
			/bin/echo "-h           --help             Show this dialog"
			/bin/echo "";;
			
		*)
			/bin/echo -e "\e[33mUnknown argument: "$1"\e[0m";;
			
	esac
	shift;
done

cd /home/*
DIR=$PWD
BUILDUSER=$(basename $DIR)

endloop=false
STEP=1
while [ ${endloop} = false ]; do
	case ${STEP} in
		1)	# Fetch latest BACnet update
			exe chmod -R 777 /media/BACnet ;;

		2)	# Make necessary preparations in /ptxproj
			exe cd /home/$BUILDUSER/wago/ptxproj/
			exe ln -sf /media/BACnet src/BACnet
			exe ln -sf /media/BACnet/BACnetCodeSys2ExtLib/rules/libbacnet.in rules/libbacnet.in
			exe ln -sf /media/BACnet/BACnetCodeSys2ExtLib/rules/libbacnet.make rules/libbacnet.make
			exe ln -sf /media/BACnet/BACnetCodeSys2ExtLib/bin platform-wago-pfcXXX/build-target/libbacnet
			exe ln -sf /home/$BUILDUSER/wago/ptxproj/configs/wago-pfcXXX/ptxconfig_generic selected_ptxconfig
			exe ln -sf /home/$BUILDUSER/wago/ptxproj/configs/wago-pfcXXX/platformconfig selected_platformconfig
			
			exe sed -i 's+# PTXCONF_LIBBACNET is not set+PTXCONF_LIBBACNET=y+g' configs/wago-pfcXXX/ptxconfig_generic
			
			echo "HOME=/home/$BUILDUSER">makebacnet.sh
			echo "ptxdist clean libbacnet $QUIET_INTERNAL">>makebacnet.sh
			echo "ptxdist go libbacnet $QUIET_INTERNAL">>makebacnet.sh
			chmod -R 777 makebacnet.sh ;;

		3) # Run file
			/bin/echo -e "\e[1;36m\$ Start build\\e[0m"
			exe sudo -u $BUILDUSER ./makebacnet.sh
			/bin/echo -e "\e[1;36m\$ Copying files to $OUTPATH\\e[0m"
			cp -f src/BACnet/BACnetCodeSys2ExtLib/bin/BACnet-dev-newest.ipk $OUTPATH/$RESULT
			cp -f src/BACnet/BACnetCodeSys2ExtLib/bin/libbacnet.so $OUTPATH/libbacnet.so
			cp -f src/BACnet/BACnetCodeSys2ExtLib/bin/libbacnet.check.bin $OUTPATH/libbacnet.check.bin ;;

		*) endloop=true ;;
	esac
	STEP=`expr $STEP + 1`;
done;
/bin/echo -e "\e[32m\$ Build successful\\e[0m"