# WireGuard-Manager

## (EN) Description

The main purpose is to create comfortable administrator tool to manage WireGuard peers. Application has no and will have no GUI

## (RU) Описание

Цель проекта -- сделать удобный инструмент менеджмента WireGuard соединений для администратора. Т.к. в большинстве случаев это SSH подключение (в том числе и для меня) GUI для этого проекта делаться не будет.

#### Status: Developing MVP

#### Stack: c++, clang, cmake, ninja

## Workflows

WireGuard-Manager does not syncronize your configuration file automatically. So if you want it to apply changes use:
```bash
wgm --command apply-changes
```
or
```bash
wg syncconf wgm0 /etc/wireguard/wgm0.conf
```

### Create peers

```bash
wgm --command add-peer --peer MyFriendAlex # [--group <groupname> (PUBLIC)]
```


### Get peer config

```bash
wgm --command get-config --peer MyFriendAlex
```
```conf
[Interface]
# MyFriendAlex
Address = 10.0.2.1/24
PrivateKey = wBDEsKjmBgmZHdHytCkmKX0w02O1FjL0mwvy3EUqHlI=

[Peer]
Endpoint = 123.123.123.123:9876
PublicKey = cE5H/X+m66hQAhhw2q1aPmiYma4Dp5dnHTB20KaVC1I=
# PUBLIC
AllowedIPs = 10.0.1.0/24,10.0.2.0/24
```

### Get peer config qrcode (for phone) (qrencode needed)

QR code prints right in the terminal

```bash
wgm --command get-config --peer MyFriendAlex | qrencode -t utf8
```

QR code png saves as file (at your fileserver for example)

```bash
wgm --command get-config --peer MyFriendAlex | qrencode -t png -o /srv/http/data/MyFriendAlex-qrcode.png
```

### Remove peers

```bash
wgm --command delete-peer --peer MyFriendAlex
```

### Remove interface

```bash
wgm --command delete-interface
```
or
```bash
ip link del wgm0
```

## Groups

### Description

Group is a pool if ip addresses with the same AllowedIPs option.

### Default groups

- SECURE: Can see SECURE, SERVICE.
- SERVICE: Can see SECURE, SERVICE, PUBLIC, PRIVATE, GUEST.
- PUBLIC: Can see SERVICE, PUBLIC.
- PRIVATE: Can see SERVICE, PUBLIC.
- GUEST: Can see SERVICE.

### Default groups explanation

- SECURE: Underlying services that can be reached only by another services (databases, prometheus, etc.)
- SERVICE: Services, that can be reached global (http/https, Grafana, Minecraft server, etc.)
- PUBLIC: Clients, that want to be reached by another clients (Your friend Oleg hosted Minecraft server for you and another friends. You adds him to PUBLIC group)
- PRIVATE: Clients, that can see another clients (Your friend Misha wants to play at your friend Alex's Minecraft server)
- GUEST: Clients, that can see services only (Your teacher wants to check your project, hosted at SERVICE)

### Modify or custom groups

There is a groups config file at /etc/wireguard-manager/groups.conf. Feel free to modify it. Backup file is at /etc/wireguard-manager/backup/groups.conf. 