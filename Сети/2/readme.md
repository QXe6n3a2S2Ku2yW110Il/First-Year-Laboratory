# 2\. L2

Для решения этого (и всех следующих) заданий используется тот же VPN-конфиг. Напоминаем, что перед тем, как решать каждое из заданий, нужно нажимать на кнопку «Подготовить» внизу страницы. По техническим причинам эта лабораторная работа разбита на три задания, и параллельно решать их не получится: каждое задание подготавливается отдельно.

В этом задании мы разберёмся с тем, как компьютеры получают IP-адреса. Мы запустили для вас DHCP и DHCPv6-серверы.

1.  Начнём с простого: получите IPv4-адрес по DHCP.
2.  Найдите в этой сети какой-нибудь узел, который можно пинговать, и пропингуйте его.
3.  Наш роутер анонсирует префиксы для [автоконфигурации IPv6-адресов](https://ru.wikipedia.org/wiki/IPv6#%D0%90%D0%B2%D1%82%D0%BE%D0%BA%D0%BE%D0%BD%D1%84%D0%B8%D0%B3%D1%83%D1%80%D0%B0%D1%86%D0%B8%D1%8F_(Stateless_Address_Autoconfiguration_%E2%80%94_SLAAC)). Получите адрес с помощью SLAAC, и отправьте `ping` на адрес _внутри_ этой сети, заканчивающийся на `....:abcd:ef01:2345:6789`.
4.  Получите IPv6-адрес от DHCPv6-сервера.
5.  В сети, настройки которой вы получили, работает DNS-сервер. Его адрес — `....::xxxx`, где `xxxx` совпадает с номером стандартного порта протокола DNS. Обратите внимание, что `xxxx` — шестнадцатеричное число. Попингуйте этот DNS-сервер.
6.  Этот DNS-сервер знает, где находится хост `example.localdomain`. Узнайте и вы. На этом хосте работает HTTP-сервер. Зайдите на главную страницу.

Подумайте над этими вопросами и расскажите, что думаете, в отчёте:

*   Почему мы не добавили задание, проверяющее, что вы смогли получить адрес с использованием SLAAC?
*   Какие именно «технические причины» заставили нас разбить это задание на несколько частей?

* * *

## Вопросы по заданию

<label class="form-label" for="question_0">IP-адрес `example.localdomain`</label>
<input class="form-control" id="question_0" name="question_0" type="text" value="fd87:52ab:6efc:71:8887:5ecd:a395:cae">

Расскажите, как делали эту лабораторную
```
1.
sudo dhclient -v tap0
2.
ping -c 1 10.37.113.1
3.
ip -6 a
ping -c 1 -w 1 fd87:5764:ab01:71:abcd:ef01:2345:6789
4.
sudo dhclient -6 -v tap0
5.
ping -c 1 -w 3 fd87:52ab:6efc:71::53
6.
sudo apt-get install dnsutils

nslookup example.localdomain fd87:52ab:6efc:71::53

curl -g -6 --interface tap0 http://[fd87:52ab:6efc:71:8887:5ecd:a395:cae]/

edit /etc/hosts:
+fd87:52ab:6efc:71:8887:5ecd:a395:cae example.localdomain

curl example.localdomain
```

## Подзадания

* Получить IPv4-адрес	3 балла
* IPv4: `ping`	1.5 балла
* SLAAC: `ping`	1.5 балла
* Получить адрес по DHCPv6	1.5 балла
* DHCPv6: `ping`	3 балла
* IP-адрес `example.localdomain`	3 балла
* HTTP-запрос на `example.localdomain`	4.5 балла
 
