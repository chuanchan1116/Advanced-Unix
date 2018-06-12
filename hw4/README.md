# Homework 4
## Compile
### Build
```
make
```

### Run
```
make run
```
or
```
sudo ./lanchat
```

**The program must be runned as root**

### Clean
```
make clean
```

## Feature

The program will check for ethernet compatible network interface and broadcast message on those interface.

###### Sample Output
```
Enumerated network interfaces:
2 -  ens33  IP 172.16.66.213    Netmask 255.255.255.0   MAC 00:0C:29:E7:96:1C
3 -  ens38  IP 192.168.73.132   Netmask 255.255.255.0   MAC 00:0C:29:E7:96:26
2 -  ens33  IP fe80::1e3d:9b1e:3cf2:b068    Netmask ffff:ffff:ffff:ffff::   MAC 00:0C:29:E7:96:1C
3 -  ens38  IP fe80::e230:8438:e60c:5c20    Netmask ffff:ffff:ffff:ffff::   MAC 00:0C:29:E7:96:26
Enter your name: test2
Welcome, 'test2'!
>>> <00:0C:29:F2:35:41> [test1]: hello
<00:0C:29:F2:35:4B> [test1]: hello
hello world!
>>> 
```
