# This is a startup script executed on the target Linux- platform every time the PLC boots and loads
# up the bacnet.so library into CodeSys. This may be used for any OS- initialization required.

# NOTE: Linux on PFC200 will refuse to execute this file if it contains any Windows line-endings
#       If you edit it in Windows, use Notepad++ to remove CR using Edit -> EOL Conversion -> Unix (LF)


# Log the startup time to Zaphire.log
now=$(date)
echo "Zaphire boot script startup: $now" >>/media/sd/Zaphire.log


# Replace the mime_types.conf file in the Lighttpd webserver with zaphire_mime_types.conf IF they are different.
if cmp -s "/etc/bacnet/zaphire_mime_types.conf" "/etc/lighttpd/mime_types.conf" ; then
	echo "Webserver is using the Zaphire MIME- config." >>/media/sd/Zaphire.log
else
	# Overwrite the webserver config.
	echo "Different MIME- config than webserver detected! Replacing config ..." >>/media/sd/Zaphire.log
	cp -fr /etc/bacnet/zaphire_mime_types.conf /etc/lighttpd/mime_types.conf
	echo "MIME- config replaced!" >>/media/sd/Zaphire.log

	# Reboot the webserver so the changes take effect.
	echo "Rebooting the webserver ..." >>/media/sd/Zaphire.log
	/etc/init.d/lighttpd stop >>/media/sd/Zaphire.log
	/etc/init.d/lighttpd start >>/media/sd/Zaphire.log
fi


# Log the startup script finished to Zaphire.log
echo "Zaphire boot script finished." >>/media/sd/Zaphire.log
