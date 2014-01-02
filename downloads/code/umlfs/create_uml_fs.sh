#!/bin/bash
DSTDIR=/tmp
IMAGE_FS=/tmp/image

if [ ! -d $IMAGE_FS ]; then
	echo "Creating $IMAGE_FS"
	mkdir -p $IMAGE_FS
fi

echo "Create 2 GB virtual disk"
dd if=/dev/zero of=$DSTDIR/imagefile seek=2 count=0 bs=1G
mkfs.ext3 -F $DSTDIR/imagefile

echo "Loop mount the imagefile"
mount -o loop $DSTDIR/imagefile $IMAGE_FS

echo "Debootstrap hardy"
debootstrap --verbose --arch=i386 --include=aptitude,nano,vim hardy $IMAGE_FS

echo "Mount devpts and proc"
mount -t devpts none $IMAGE_FS/dev/pts
mount -t proc none $IMAGE_FS/proc

df -h 


echo "Create sources.list"
cat > $IMAGE_FS/etc/apt/sources.list << EOF
deb http://archive.ubuntu.com/ubuntu hardy main restricted
deb http://archive.ubuntu.com/ubuntu hardy-updates main restricted universe
deb http://archive.ubuntu.com/ubuntu hardy-security main restricted
deb http://archive.ubuntu.com/ubuntu hardy universe multiverse
deb http://archive.ubuntu.com/ubuntu hardy-security universe multiverse
EOF

echo "Create /etc/hostname"
echo localhost > $IMAGE_FS/etc/hostname

cat > $IMAGE_FS/etc/hosts << EOF
127.0.0.1       localhost
EOF

echo "Create /etc/fstab"
cat > $IMAGE_FS/etc/fstab << EOF
/dev/ubd0       /               ext3    defaults        0       1
proc            /proc           proc    defaults        0       0
tmpfs           /tmp            tmpfs   defaults        0       0
none            /host           hostfs  defaults,noauto 0       0
EOF

mkdir -p $IMAGE_FS/host

sed -i '/ACTIVE_CONSOLES/s/.-./1-2/' $IMAGE_FS/etc/default/console-setup
for i in $IMAGE_FS/etc/event.d/tty[3-9]
do
	sed -i 's/start/stop/' ${i}
done

cat > $IMAGE_FS/root/setup_uml.sh << EOF
#!/bin/bash

export LANG=C

cd /dev
mknod ubd0 b 98 0
aptitude update && aptitude -y dist-upgrade

ln -sf /usr/share/zoneinfo/Europe/Stockholm /etc/localtime

aptitude -y install less locales console-data
update-locale LANG=C

aptitude -y install tcpdump telnet openssh-client

# Prepare for optional image compression
apt-get clean

echo "Filling up the image ... this takes some time ..."
dd if=/dev/zero of=remove-this bs=8k
rm -f remove-this 

echo "Change password, suggesting root/root"
passwd

echo "Exit from chroot, by simply typing \"exit\""

exit
EOF

echo "Creating .vimrc"
cat > $IMAGE_FS/root/.vimrc << EOF
syn on
set nocompatible
set incsearch smartcase
set bs=2
set wildmenu
set ts=8
set cindent
set smartindent
EOF

echo "export HOME=/root" >> $IMAGE_FS/root/.bashrc

# Go into chroot and perform some configuration
echo "Run the script /root/setup_uml.sh when chroot."
chroot $IMAGE_FS /bin/bash

echo "Unmounting fs"
umount $IMAGE_FS/dev/pts
umount $IMAGE_FS/proc
umount $IMAGE_FS

df -h

ls -alh $DSTDIR/imagefile

mv $DSTDIR/imagefile $DSTDIR/imagefile_uml_hardy.fs
time tar -C $DSTDIR -czvf image.tar.gz imagefile_uml_hardy.fs

echo "Creating a tar.gz of the filesystem ..."
mv $DSTDIR/imagefile_uml_hardy.fs .
mv image.tar.gz image_uml_hard_fs.tar.gz 

ls -alh image*
