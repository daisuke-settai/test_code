lsf:
	gcc linux_socket_filtering.c -o lsf

lsf-tcpdump:
	gcc -DTCPDUMP linux_socket_filtering.c  -o lsf-tcpdump

lsf-pcap:
	gcc linux_socket_filtering.c -DPCAP -lpcap -o lsf-pcap

seccomp-black:
	gcc seccomp.c -o seccomp-prohibit-getpid -DBLACK

seccomp-white:
	gcc seccomp.c -o seccomp-permit-getpid

seccomp-libseccomp:
	gcc seccomp-libseccomp.c -o seccomp-libseccomp -lseccomp

clean:
	rm -f lsf lsf-tcpdump lsf-pcap seccomp-prohibit-getpid seccomp-permit-getpid seccomp-libseccomp
