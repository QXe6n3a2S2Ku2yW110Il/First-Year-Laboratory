# 3\. L2: Episode One

В этом задании вам придётся перейти на обратную сторону интернета: теперь вам самим придётся выдавать IP-адреса. Ваша цель — запустить свой собственный DHCP-сервер, а наши боты будут запрашивать у него адреса.

Вы можете реализовать DHCP-сервер самостоятельно или взять любой готовый. Мы намеренно не подсказываем вам, что выбирать, в надежде на то, что в решениях будут представлены различные варианты, а не только [ДАННЫЕ УДАЛЕНЫ].

Настройте сервер так, чтобы он выдавал клиентам адреса из сети `10.0.113.0/24`. Нажмите кнопку «Проверить задание», чтобы наш бот попробовал получить адрес и сообщил вам результат.

Осталось настроить IPv6: выдайте адрес из сети `fd91:3abf:626b:113::/64`. Вам будет недостаточно просто поменять DHCP на DHCPv6 — придётся столкнуться с протоколом NDP и пакетами Router Advertisement.

## Вопросы по заданию

Расскажите, как вы делали эту лабораторную
```
sudo apt-get install isc-dhcp-server

sudo ip address add 10.0.113.0/24 dev tap0

edit /etc/default/isc-dhcp-server:
-INTERFACESv4=""
-INTERFACESv6=""
+INTERFACESv4="tap0"
+INTERFACESv6="tap0"

edit /etc/dhcp/dhcpd.conf:
+subnet 10.0.113.0 netmask 255.255.255.0 {
+  range 10.0.113.10 10.0.113.80;
+  option subnet-mask 255.255.255.0;
+  option broadcast-address 10.0.113.255;
+  option routers 10.0.113.1
+}

edit /etc/dhcp/dhcpd6.conf:
+subnet6 fd91:3abf:626b:113::/64 {
+    range6 fd91:3abf:626b:113::128 fd91:3abf:626b:113:ffff:ffff:ffff:ffff;
+}

edit /etc/network/interfaces:
+auto tap0

if there is dhcp processes already running, then kill them:
ps aux | grep dhcp
sudo kill <pid>
sudo rm /run/dhcpd.pid

if all conditions satisfies, then run:
sudo dhcpd -4
sudo dhcpd -6 -cf /etc/dhcp/dhcpd6.conf
```

## Подзадания
* Выдайте IPv4-адрес	7.5 балла
* Выдайте IPv6-адрес	7.5 балла
