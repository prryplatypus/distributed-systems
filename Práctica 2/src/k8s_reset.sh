sudo kubeadm reset
sudo apt-get purge -y kubectl kubeadm kubernetes-cni
sudo rm -r /etc/kubernetes/
sudo rm -r /var/lib/etcd/
rm -r ~/.kube