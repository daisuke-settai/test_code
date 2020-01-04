#!/bin/bash

# install gcc, make, git, tmux, virsh
# virt-clone --original ed-01 --name ed-03 --file ~/libvirt/images/ed-03.img:  VMをクローン
# hostnameを設定
# edit vm netedit: ネットワークを構成

# 導入
sudo apt-get install -y kvm qemu-system libvirt-bin bridge-utils virt-manager
sudo service libvirt-bin start

# 実行準備
workspace=~/libvirt/images
image_name=linux4.18
disk_size_gb=50
ram_size_mb=4096
os_location=http://jp.archive.ubuntu.com/ubuntu/dists/trusty/main/installer-amd64/

mkdir -p ${workspace}
cd ${workspace}

# 実行
qemu-img create -f qcow2 ${image_name}.img ${disk_size_gb}G
sudo virt-install \
  --name ${image_name} \
  --virt-type kvm \
  --disk ${image_name}.img,format=qcow2,bus=virtio \
  --accelerate \
  --ram ${ram_size_mb} \
  --vcpus 2 \
  --arch x86_64 \
  --graphics none \
  --location ${os_location} \
  --extra-args "console=ttyS0, 115200n8"


