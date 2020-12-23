sudo apt-get update && sudo apt-get install -y apt-transport-https gnupg2 

curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add - 
echo "deb https://apt.kubernetes.io kubernetes-xenial main" | sudo tee -a /etc/apt/sources.list.d/kubernetes.list 

sudo apt-get update 
sudo apt-get install -y kubectl kubeadm kubernetes-cni docker.io conntrack 
sudo systemctl enable docker.service 
sudo systemctl enable kubelet.service
sudo kubeadm init 
mkdir -p $HOME/.kube 
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config 
sudo chown $(id -u):$(id -g) $HOME/.kube/config 
sudo curl -L git.io/weave -o /usr/local/bin/weave 
sudo chmod a+x /usr/local/bin/weave 
kubectl apply -f "https://cloud.weave.works/k8s/net?k8s-version=$(kubectl version | base64 | tr -d '\n')" 
kubectl get nodes 
#sudo kubeadm reset <-- Only execute this in slaves