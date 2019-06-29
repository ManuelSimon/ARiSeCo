useradd -c "User 1" user1 -m -s /bin/bash
useradd -c "User 2" user2 -m -s /bin/bash
# passwd user1
# passwd user2
tc qdisc add dev eth0 root handle 1:prio
tc qdisc add dev eth0 parent 1:1 handle 10:tbf limit 1514b burst 1514 b rate 40kbit
tc qdisc add dev eth0 parent 1:2 handle 20:tbf limit 1514b burst 1514 b rate 10kbit
iptables -A OUTPUT -t mangle -m owner --uid -owner user1 -j MARK --set-mark 5
iptables -A OUTPUT -t mangle -m owner --uid -owner user2 -j MARK --set-mark 10
tc filter add dev eth0 parent 1:0 protocol ip prio 1 handle 5 fw flowid 1:1
tc filter add dev eth0 parent 1:0 protocol ip prio 1 handle 10 fw flowid 1:2
