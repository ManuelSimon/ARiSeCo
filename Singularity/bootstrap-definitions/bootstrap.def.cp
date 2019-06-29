BootStrap: docker
From: ubuntu
IncludeCmd: yes

OPEN_MPI_VERSION=1.10.2
MAIN_VERSION=1.10

%post
	# Get the system ready
	sed -i 's/main/main restricted universe/g' /etc/apt/sources.list
	apt-get update
	apt-get install -y --no-install-recommends         apt-utils 		bash 		build-essential 		curl 		gcc 	    git 		python         python-pip         pkg-config         python-dev         python-setuptools         rsync         software-properties-common 		time         unzip         vim 		wget         zip 
	# Need to be split in 2 different apts
	apt-get install -y --no-install-recommends 		zlib1g-dev         libopenblas-dev 		libc6-dev         libcurl4-openssl-dev         libfreetype6-dev 		libgcc-5-dev         libpng-dev         libzmq3-dev 
	apt-get clean
	# Update to the latest pip (newer than repo)
	pip install --no-cache-dir --upgrade pip
	# Install other commonly-needed packages
	pip install --no-cache-dir --upgrade         future         matplotlib 		scipy 
	# IB stuff, based on https://community.mellanox.com/docs/DOC-2431 !!!!!NOT SURE IF NEEDED!!!!!
	apt-get install -y dkms infiniband-diags libibverbs* ibacm librdmacm* libmlx4* libmlx5* mstflint libibcm.* libibmad.* libibumad* opensm srptools libmlx4-dev librdmacm-dev rdmacm-utils ibverbs-utils perftest vlan ibutils
	apt-get install -y libtool autoconf automake build-essential ibutils ibverbs-utils rdmacm-utils infiniband-diags perftest librdmacm-dev libibverbs-dev libmlx4-1 numactl libnuma-dev autoconf automake gcc g++ git libtool pkg-config
	apt-get install -y libnl-3-200 libnl-route-3-200 libnl-route-3-dev libnl-utils
	# OpenMPI dependencies
	apt-get install -y libopenmpi-dev openmpi-common openmpi-bin openmpi-doc dapl2-utils libdapl-dev libdapl2 libibverbs1 libibverbs-dev librdmacm1 libcxgb3-1 libipathverbs1 libmlx4-1 libmlx5-1 libmthca1 libnes1 libpmi0 libpmi0-dev libslurm29 libslurm-dev libsysfs2 libsysfs-dev
	# Install OpenMPI
	cd /tmp
	wget 'https://www.open-mpi.org/software/ompi/$MAIN_VERSION/downloads/openmpi-$OPEN_MPI_VERSION.tar.gz' -O openmpi-$OPEN_MPI_VERSION.tar.gz
	tar -xzf openmpi-$OPEN_MPI_VERSION.tar.gz
	mkdir -p /tmp/openmpi-$OPEN_MPI_VERSION/build
	cd /tmp/openmpi-$OPEN_MPI_VERSION/build
	../configure --prefix=/usr --with-slurm --enable-shared --enable-mpi-thread-multiple --with-verbs --enable-mpirun-prefix-by-default --with-hwloc --disable-dlopen --with-pmi --with-pmi-libdir=/usr/lib/x86_64-linux-gnu
	make clean
	make all install
	export LD_LIBRARY_PATH=/usr/local/lib:
	# Create some folders
	mkdir -p /scratch /tmp /home /opt/cesga /mnt /usr/local/openmpi /usr/lib64/slurm /opt/mellanox /host/lib64 /host/filtered/lib64 /host/usr/lib64 /host/filtered/usr/lib64 /etc/libibverbs.d /run/munge /etc/slurm /.singularity.d/libs
	# Last 
        echo "driver mlx4" > /etc/libibverbs.d/mlx4.driver
        echo "driver mlx5" > /etc/libibverbs.d/mlx5.driver
        adduser slurm || echo "User exists"
        cat /etc/usr_lib64.txt | xargs -I{} ln -fs /host/usr/lib64/{} /host/filtered/usr/lib64/{}
        cat /etc/lib64.txt | xargs -I{} ln -fs /host/lib64/{} /host/filtered/lib64/{}



%runscript
	# Installing mpi4py
	cd /tmp/
	wget https://codeload.github.com/mpi4py/mpi4py/zip/master -o mpi4py-master.zip
        unzip mpi4py-master.zip
        cd mpi4py-master/
        make
		