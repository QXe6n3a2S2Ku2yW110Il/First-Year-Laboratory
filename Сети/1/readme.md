# 1\. Привет

Для выполнения этого и всех следующих домашних заданий вам нужно будет подключиться к VPN-серверу. Для этого скачайте и установите [OpenVPN](https://openvpn.net/community-downloads/). Для MacOS подойдёт [Tunnelblick](https://tunnelblick.net/).

Ваш персональный конфиг находится в меню под заданиями. Используйте его, чтобы подключиться к серверу. Например, на Linux можно зайти в терминал в директории с конфигом и ввести: `sudo openvpn --config networking-labs.ovpn`. На Windows и Mac OS вам, скорее всего, будет удобнее пользоваться графическим интерфейсом.

**Важно**: команды здесь и далее будут приведены для Linux. Вы можете использовать любую другую операционную систему: сдать задания на полный балл можно с использованием любой современной ОС, однако, действия будут отличаться.

После подключения на компьютере появится новый сетевой интерфейс. Найдите его. Под линуксом он скорее всего называется `tap0`. Это L2-интерфейс — обычное Ethernet-соединение между вашим компьютером и проверяющим сервером.

По умолчанию интерфейс выключен с вашей стороны. Поднимите его:

`ip link set up dev tap0`

Теперь на интерфейсе можно настроить адреса. Вам нужно настроить вот такие:

*   IPv4: `10.0.0.123/8`
*   IPv6: `fd91:3abf:626b:1::1337/48`

<details><summary>Подсказка</summary> Используйте команду `ip address add`, подробнее можно почитать в `ip address help` и `man ip`.</details>

1.  Проверьте, что всё работает, попинговав `10.0.0.1` и `fd91:3abf:626b:1::1`. Определите, какие MAC-адреса имеют эти два узла.
2.  В этом же интерфейсе доступен узел с адресом `fd91:3abf:626b:1::2`, но до него не доходят большие пакеты. Определите максимальный размер IP-пакета, который доходит до этого узла.
3.  На этом же интерфейсе в подсети `10.1.0.0/16` есть много узлов. Все они имеют **последовательные** IP-адреса, начиная с `10.1.0.1` и отвечают на ICMP-пакеты. Найдите последний доступный узел в этой подсети (то есть узел с лексикографически максимальным IP-адресом).
4.  На этом же интерфейсе в подсети `fd91:3abf:626b:2::/64` также есть много узлов. Они также имеют последовательные IP-адреса, начиная с `fd91:3abf:626b:2::1/64`. Найдите последний доступный узел в этой подсети.

<hr />

## Вопросы по заданию

<label class="form-label" for="question_0">MTU до `fd91:3abf:626b:1::2`</label> <input class="form-control" id="question_0" name="question_0" type="text" value="1313">

<label class="form-label" for="question_1">MAC-адрес `10.0.0.1` (в формате `aa:bb:cc:dd:ee:ff`)</label> <input class="form-control" id="question_1" name="question_1" type="text" value="26:d0:72:be:4e:04">

<label class="form-label" for="question_2">MAC-адрес `fd91:3abf:626b:1::1` (в формате `aa:bb:cc:dd:ee:ff`)</label> <input class="form-control" id="question_2" name="question_2" type="text" value="c6:d4:cc:4b:9f:29">

<label class="form-label" for="question_3">Адрес последнего доступного узла из `10.1.0.0/16`</label> <input class="form-control" id="question_3" name="question_3" type="text" value="10.1.132.27">

<label class="form-label" for="question_4">Адрес последнего доступного узла из `fd91:3abf:626b:2::0/64`</label> <input class="form-control" id="question_4" name="question_4" type="text" value="fd91:3abf:626b:2:48f1:da8c:657:841b">

Расскажите, как вы делали эту лабораторную
```
Для выполнения первых заданий достаточно было прочитать man ip, man ip-address, и правильно настроить адреса.
Для получения mac адреса использовалась команда ip neigh.
Для нахождения mtu использовалась программа.
#include &lt;stdio.h&gt;

int main() {
    int left = 1, right = 65507;
    while (right - left &gt; 1) {
        int const middle = left + (right - left) / 2;
        printf("middle = %d\n", middle);
        int x;
        scanf("%d", &amp;x);
        if (x != 0) {
            left = middle;
        } else {
            right = middle;
        }
        printf("curr: [%d..%d)\n", left, right);
    }

    printf("%d\n", left);

    return 0;
}
Программа ищет верхнюю границу принятия пакетов узла. Проверка делается ручками. К полученному результату нужно прибавить 8 + 20 + 20 байтов дополнительной информации, потому что так работает ping.

На получение адреса последнего узла нужно было найти самый большой лексикографически адрес, от которого можно получить ответ.
Скрипт, выдающий ответ
#!/bin/bash

left=1
let right=255*256+255

while [[ $((right-left)) -gt 1 ]]; do
    let middle=$((left+((right-left))/2))
    echo "checking 10.1.$(($middle/256)).$(($middle%256))"
    result=$(ping -c 1 -s $middle -w 1 10.1.$(($middle/256)).$(($middle%256)) | grep received | cut -d ' ' -f 4)
    echo "result is "$result
    if [[ result -eq 1 ]]; then
        left=$middle
    else
        right=$middle
    fi
done

echo "10.1.$(($left/256)).$(($left%256))"

На последнее задание тоже писался скрипт
#!/bin/bash

res=(0 0 0 0)

for (( i=0; i&lt;=3; ++i )); do
    left=0
    right=65536
    while [[ $((right-left)) -gt 1 ]]; do
        res[$i]=$(printf '%x' $((left+((right-left))/2)))
        echo "checking fd91:3abf:626b:2:${res[0]}:${res[1]}:${res[2]}:${res[3]}"
        result=$(ping -c 1 -w 1 fd91:3abf:626b:2:${res[0]}:${res[1]}:${res[2]}:${res[3]} | grep received | cut -d ' ' -f 4)
        echo "result is "$result
        if [[ result -eq 1 ]]; then
            left=$(printf "%d" $((16#${res[$i]})))
        else
            right=$(printf "%d" $((16#${res[$i]})))
        fi
        printf '[%d..%d)\n' $left $right
    done
    res[$i]=$(printf '%x' $left)
done

echo "fd91:3abf:626b:2:${res[0]}:${res[1]}:${res[2]}:${res[3]}"
```

## Подзадания

* Подключиться к VPN-серверу 1.5 балла
* Сделать `ping 10.0.0.1`	3 балла
* Сделать `ping [fd91:3abf:626b:1::1]`	3 балла
* MAC-адрес `10.0.0.1`	3 балла
* MAC-адрес `fd91:3abf:626b:1::1`	4.5 балла
* MTU до узла `fd91:3abf:626b:1::2`	4.5 балла
* Последний доступный узел из `10.1.0.0/16`	4.5 балла
* Последний доступный узел из `fd91:3abf:626b:2::0/64`	4.5 балла
