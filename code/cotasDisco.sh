# useradd -c "Novo Usuario Cotas" novousuariocotas -m -s /bin/bash -g staff
# passwd novousuariocotas
apt-get install quota
echo "UUID=deb5e4ba-4656-4331-8bf2-6a3450425c3e /	ext4	defaults,usrjquota=aquota.user,grpjquota=aquota.group,jqfmt=vfsv0,errors=remount-ro	0	1" >> /etc/fstab
mount -vo remount /
quotacheck -vguma
quotaon -va
edquota -u nuevousuariocuotas -f /
	#Engadimos /dev/vda1	2416	10000	100000	14	0	0
