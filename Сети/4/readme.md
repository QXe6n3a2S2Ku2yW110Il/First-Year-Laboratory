# 4\. L2: Episode Two

В этом задании вам предстоит провести настоящее киберрасследование.

В нашей корпоративной сети завёлся злоумышленник — он поднял свой DHCP-сервер и выдаёт всем неправильные интернет-настройки. Узнайте, какие DHCP-сервера есть в локальной сети, и получите правильный IP-адрес.

## Вопросы по заданию

<label class="form-label" for="question_0">IP-адрес DHCP-сервера злоумышленника</label> <input class="form-control" id="question_0" name="question_0" type="text" value="10.0.0.1">

<label class="form-label" for="question_1">IP-адрес настоящего DHCP-сервера</label> <input class="form-control" id="question_1" name="question_1" type="text" value="10.113.222.1">

Расскажите, как вы делали эту лабораторную
```
sudo dhclient -v

sudo cat /var/lib/dhcp/dhclient.leases
result:
lease {
  interface "tap0";
  fixed-address 10.37.113.110;
  option subnet-mask 255.255.255.0;
  option dhcp-lease-time 43129;
  option dhcp-message-type 5;
  option dhcp-server-identifier 10.37.113.1;
  renew 4 2021/06/24 14:45:29;
  rebind 4 2021/06/24 20:20:47;
  expire 4 2021/06/24 21:50:39;
}
...
lease {
  interface "tap0";
  fixed-address 10.0.0.110;
  option subnet-mask 255.255.255.0;
  option dhcp-lease-time 43200;
  option dhcp-message-type 5;
  option dhcp-server-identifier 10.0.0.1;  <-- IP злоумышленника
  renew 5 2021/06/25 11:19:40;
  rebind 5 2021/06/25 16:04:35;
  expire 5 2021/06/25 17:34:35;
}

edit /etc/dhcp/dhclient.conf:
-#reject 192.33.137.209;
+reject 10.0.0.1;

sudo rm /var/lib/dhcp/dhclient.leases

sudo dhclient -v

wait several seconds..

sudo cat /var/lib/dhcp/dhclient.leases
result:
...
lease {
  interface "tap0";
  fixed-address 10.113.222.110;
  option subnet-mask 255.255.255.0;
  option dhcp-lease-time 41189;
  option dhcp-message-type 5;
  option dhcp-server-identifier 10.113.222.1;   <-- Настоящий IP
  renew 5 2021/06/25 11:18:11;
  rebind 5 2021/06/25 16:19:37;
  expire 5 2021/06/25 17:45:26;
}
```

## Подзадания
* IP-адрес DHCP-сервера злоумышленника	1.5 балла
* Получить IP-адрес от злоумышленника	1.5 балла
* IP-адрес настоящего DHCP-сервера	3 балла
* Получить IP-адрес от настоящего сервера	4.5 балла
